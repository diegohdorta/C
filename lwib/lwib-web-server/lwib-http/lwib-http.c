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


#include "../lwib/lwib.h"
#include "lwib-http.h"
#include "../lwib-debug/lwib-debug.h"

 
/* this is a child web server process, so we can exit on errors */
void web(int fd, int hit, dict_ext_t *extensions)
{
	int j, file_fd, buflen, len;
	long i, ret;
	char * fstr;
	static char buffer[BUFSIZE+1]; /* static so zero filled */
 	ssize_t lenght = 0;

	ret =read(fd,buffer,BUFSIZE); 	/* read Web request in one go */
 
	if(ret == 0 || ret == -1) {	/* read failure stop now */
		lwb_debug(SORRY,"failed to read browser request","",fd);
	}
 
	if(ret > 0 && ret < BUFSIZE)	/* return code is valid chars */
		buffer[ret]=0;		/* terminate the buffer */
	else
		buffer[0]=0;
 
	for(i=0;i<ret;i++)	/* remove CF and LF characters */
		if(buffer[i] == '\r' || buffer[i] == '\n')
			buffer[i]='*';
 
	lwb_debug(LOG,"request",buffer,hit);
 
	if( strncmp(buffer,"GET ",4) && strncmp(buffer,"get ",4) )
		lwb_debug(SORRY,"Only simple GET operation supported",buffer,fd);
 
	for(i=4;i<BUFSIZE;i++) { /* null terminate after the second space to ignore extra stuff */
		if(buffer[i] == ' ') { /* string is "GET URL " +lots of other stuff */
			buffer[i] = 0;
			break;
		}
	}
 
	for(j=0;j<i-1;j++) 	/* check for illegal parent directory use .. */
		if(buffer[j] == '.' && buffer[j+1] == '.')
			lwb_debug(SORRY,"Parent directory (..) path names not supported",buffer,fd);
 
	if( !strncmp(&buffer[0],"GET /\0",6) || !strncmp(&buffer[0],"get /\0",6) ) /* convert no filename to index file */
		(void)strcpy(buffer,"GET /index.html");
 
	/* work out the file type and check we support it */
	buflen=strlen(buffer);
	fstr = (char *)0;
	for(i=0;extensions[i].ext != 0;i++) {
		len = strlen(extensions[i].ext);
		if( !strncmp(&buffer[buflen-len], extensions[i].ext, len)) {
			fstr =extensions[i].filetype;
			break;
		}
	}
	if(fstr == 0) lwb_debug(SORRY,"file extension type not supported",buffer,fd);
 
	if(( file_fd = open(&buffer[5],O_RDONLY)) == -1) /* open the file for reading */
		lwb_debug(SORRY, "failed to open file",&buffer[5],fd);
 
	lwb_debug(LOG,"SEND",&buffer[5],hit);
 
	(void)sprintf(buffer,"HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", fstr);
	lenght = write(fd,buffer,strlen(buffer));
 	if (lenght < 0) {
	 	fprintf(stderr, "Failed to write %s.\n", strerror(errno));
	 	exit(EXIT_FAILURE);
 	}
 
	/* send file in 8KB block - last block may be smaller */
	while (	(ret = read(file_fd, buffer, BUFSIZE)) > 0 ) {
		lenght = write(fd, buffer, ret);
		 	if (lenght < 0) {
	 	fprintf(stderr, "Failed to write %s.\n", strerror(errno));
	 	exit(EXIT_FAILURE);
 	}
 
	}
#ifdef LINUX
	sleep(1);	/* to allow socket to drain */
#endif
	exit(1);
}
 
