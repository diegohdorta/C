#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "common.h"

struct message {
	struct medipix_header header;
	char data[SIZE_IMAGE_DATA];
};

#define NUM_MESSAGES 64

static struct message ordered[NUM_MESSAGES];
static struct message unordered[NUM_MESSAGES];

int main(void)
{
	FILE *f1, *f2;

	static struct {
		struct acquisition_info info;
		char data[SIZE_IMAGE_DATA*NUM_MESSAGES];
		char c;
	} raw1, raw2;

	int s1, s2;
	unsigned i, j;
	struct acquisition_info info = { 0, 1, 0, 1 };
	struct sockaddr_in addr = { AF_INET, htons(1234), { htonl(INADDR_LOOPBACK) } };
	ssize_t ss1, ss2;

	log_error = stderr;

	s1 = create_udp_socket();
	s2 = create_udp_socket();

	binding_udp_socket(s1, 1234);

	for (i = 0; i < NUM_MESSAGES; i++) {
		ordered[i].header.packet_number = i;
		memset(ordered[i].data, i, SIZE_IMAGE_DATA);
		unordered[i] = ordered[i];
	}

	unordered[2].header.packet_number = 5;
	unordered[5].header.packet_number = 2;
	unordered[NUM_MESSAGES-1].header.packet_number = 10;
	unordered[10].header.packet_number = NUM_MESSAGES-1;
	memset(unordered[2].data, 5, SIZE_IMAGE_DATA);
	memset(unordered[5].data, 2, SIZE_IMAGE_DATA);
	memset(unordered[10].data, NUM_MESSAGES-1, SIZE_IMAGE_DATA);
	memset(unordered[NUM_MESSAGES-1].data, 10, SIZE_IMAGE_DATA);

	for (i = 0; i < NUM_MESSAGES; i++) {
		sendto(s2, &ordered[i], sizeof(struct message), 0,
			(struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	}

	strcpy(info.filename, "ordered.data");

	receive_bytes_from_medipix(s1, &info);

	for (i = 0; i < NUM_MESSAGES; i++)
		sendto(s2, &unordered[i], sizeof(struct message), 0,
			(struct sockaddr *)&addr, sizeof(struct sockaddr_in));

	strcpy(info.filename, "unordered.data");
	receive_bytes_from_medipix(s1, &info);

	close(s1);
	close(s2);

	f1 = fopen("ordered.data", "r");
	f2 = fopen("unordered.data", "r");
	ss1 = fread(&raw1, 1, sizeof(raw1), f1);
	ss2 = fread(&raw2, 1, sizeof(raw2), f2);
	fclose(f1);
	fclose(f2);

	if (ss1 != SIZE_IMAGE_DATA*NUM_MESSAGES + sizeof(struct acquisition_info)) {
		fprintf(stderr, "Error: file size mismatch: read %zd bytes.\n", ss1);
		return -1;
	}

	if (ss2 != SIZE_IMAGE_DATA*NUM_MESSAGES + sizeof(struct acquisition_info)) {
		fprintf(stderr, "Error: file size mismatch: read %zd bytes.\n", ss2);
		return -1;
	}

	for (i = 0; i < NUM_MESSAGES; i++) {
		for (j = 0; j < SIZE_IMAGE_DATA; j++) {
			if ((unsigned)raw1.data[j+SIZE_IMAGE_DATA*i] != i) {
				debug(stderr, "Error: ordered file is incorrect.\n");
				return -1;
			}

			if ((unsigned)raw2.data[j+SIZE_IMAGE_DATA*i] != i) {
				debug(stderr, "Error: unordered file is incorrect.\n");
				return -1;
			}
		}
	}

	debug(stderr, "Message was successfully reordered.\n");

	return 0;
}
