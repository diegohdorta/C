#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lwib/lwib.h"
#include "lwib-helper.h"

void check_forbidden_directories(char *dir)
{   
    FILE *fp = NULL;
    const char *delimiter = DELIMITER;
    char *fd_file = FORBIDDEN_DIRS_NAME;
    char *token;
    char line[SIZE_LINE];
    unsigned int i = 0;
	unsigned int t = 0;
	unsigned int fd_size = 0;
	
	get_file_size(fd_file, &fd_size);
 	dict_fdirs_t *fdirs = malloc(sizeof(dict_fdirs_t) * fd_size);
	if (!fdirs) {
	    fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
	    exit(EXIT_FAILURE);
	}
    fp = fopen(fd_file, "r");
    if (!fp) {
        fprintf(stderr, "fopen() failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    while (fgets(line, sizeof(line), fp)) {        
        token = strtok(line, delimiter);
        if (sscanf(token, "%s", fdirs[t].dir) != 1) {
            fprintf(stderr, "sscanf() failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < 2; i++) {
            if (sscanf(token, "%s", fdirs[t].lenght) != 1) {
                fprintf(stderr, "sscanf() failed: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, delimiter);
        }
        t++;
    }
    fclose(fp);	
	for (i = 0; i < fd_size; i++) {
		if (!strncmp(dir, fdirs[i].dir, atoi(fdirs[i].lenght))) {
			fprintf(stderr, "[!] Cant run this directory: %s\n",  dir);
			exit(EXIT_FAILURE);		
		}	
	}
	free(fdirs);
}

void get_file_size(char *file, unsigned int *size)
{
    FILE *fp =  NULL;
    char ch;    
    
    fp = fopen(file, "r");
    if (!fp) {
        fprintf(stderr, "fopen() failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    do {
        ch = fgetc(fp);
        if (ch == '\n') {
            (*size)++;
        } 
    } while (ch != EOF);
    if (ferror(fp)) {
        fprintf(stderr, "fgetc() failed: %s\n", strerror(errno));
        fclose(fp);
        exit(EXIT_FAILURE);    
    }
    fclose(fp);
}

void load_file_types(char *file, dict_ext_t *dext, unsigned int *ft_size)
{
    FILE *fp =  NULL;
    int i = 0;
    int t = 0;
    const char *delimiter = DELIMITER;
    char *token;
    char line[SIZE_LINE];

    fp = fopen(file, "r");
    if (!fp) {
        fprintf(stderr, "fopen() failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    while (fgets(line, sizeof(line), fp)) {        
        token = strtok(line, delimiter);
        if (sscanf(token, "%s", dext[t].ext) != 1) {
            fprintf(stderr, "sscanf() failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < 2; i++) {
            if (sscanf(token, "%s", dext[t].filetype) != 1) {
                fprintf(stderr, "sscanf() failed: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, delimiter);
        }
        t++;
    }
    fclose(fp);
}
