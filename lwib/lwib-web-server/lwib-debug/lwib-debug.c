#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "lwib-debug.h"

void lwb_debug(int type, char *s1, char *s2, int num)
{
	int fd ;
	char logbuffer[BUFSIZE*2];
	ssize_t lenght = 0;
	const char *logFile = LOGFILE;
	 
	switch (type) {
	case ERROR: (void)sprintf(logbuffer,"ERROR: %s:%s Errno=%d exiting pid=%d",s1, s2, errno,getpid()); break;
	case SORRY:
		(void)sprintf(logbuffer, "<HTML><BODY><H1>nweb Web Server Sorry: %s %s</H1></BODY></HTML>\r\n", s1, s2);
		lenght = write(num,logbuffer,strlen(logbuffer));
		 	if (lenght < 0) {
	 	fprintf(stderr, "Failed to write %s.\n", strerror(errno));
	 	exit(EXIT_FAILURE);
 	}
 
		(void)sprintf(logbuffer,"SORRY: %s:%s",s1, s2);
		break;
	case LOG: (void)sprintf(logbuffer," INFO: %s:%s:%d",s1, s2,num); break;
	}
	/* no checks here, nothing can be done a failure anyway */
	if((fd = open(logFile, O_CREAT| O_WRONLY | O_APPEND,0644)) >= 0) {
		lenght = write(fd,logbuffer,strlen(logbuffer));
		 	if (lenght < 0) {
	 	fprintf(stderr, "Failed to write %s.\n", strerror(errno));
	 	exit(EXIT_FAILURE);
 	}
 
		lenght = write(fd,"\n",1);
		 	if (lenght < 0) {
	 	fprintf(stderr, "Failed to write %s.\n", strerror(errno));
	 	exit(EXIT_FAILURE);
 	}
 
		(void)close(fd);
	}
	if(type == ERROR || type == SORRY) exit(3);
}
