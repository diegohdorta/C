/*
 * lwib - Simple Lightweight and Speedy Low Latency iMX Web Server
 * Copyright (c) 2019 Diego Dorta <diego.dorta@nxp.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * https://tools.ietf.org/html/rfc2616#section-9.3
 */
#define _GNU_SOURCE
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "lwib.h"
#include "../lwib-http/lwib-http.h"
#include "../lwib-debug/lwib-debug.h"
#include "../lwib-helper/lwib-helper.h"

static int check_arguments(int *argc)
{
	return (*argc != CORRECT_ARGUMENTS) ? INCORRECT_ARGUMENTS : CORRECT_ARGUMENTS;
}

static int check_port(int *port)
{
    return (*port < PORT_MINIMUM || *port > PORT_MAXIMUM) ? 0 : 1;
}

int main(int argc, char **argv)
{
	static struct sockaddr_in caddr;
	static struct sockaddr_in saddr;
    char *ft_file = FILE_TYPES_NAME;
    char *wwwdir = argv[2];
	unsigned int length;
	unsigned int ft_size = 0;
	int port = atoi(argv[1]);
	int enable = 1;
	int pid;
	int s;
	int socketfd;
	int hit;
	dict_ext_t *dext = NULL;	

	if (check_arguments(&argc) == INCORRECT_ARGUMENTS) {
	    fprintf(stderr, "[!] arguments error, please read the document.\n");
	    return EXIT_FAILURE;   
	}
    
    if (!check_port(&port)) {
        fprintf(stderr, "[!] Invalid Port <1-65000>\n");
        return EXIT_FAILURE;
    }

	
	get_file_size(ft_file, &ft_size);	
	dext = malloc(sizeof(dict_ext_t) * ft_size);
	if (dext == NULL) {
	    fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
	    return EXIT_FAILURE;
	}
	load_file_types(ft_file, dext, &ft_size);
	check_forbidden_directories(wwwdir);
	

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);

	if (chdir(wwwdir)) {
		fprintf(stderr, "[!] chdir() failed: %s\n", wwwdir);
		exit(EXIT_FAILURE);		
	}
 
	//lwb_debug(LOG,"nweb starting",argv[1],getpid());
	printf("lwib starting %d %d\n", port, getpid());
 
	/* setup the network socket */
 
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		lwb_debug(ERROR, "system call","socket",0);
	}

    if (setsockopt(s, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), &enable, sizeof(int)) < 0) {
        fprintf(stderr, "[!] arguments error, please read the document.\n");    
        exit(EXIT_FAILURE);
    }  
	//lwb_debug(LOG, "socket listen", NULL, s);
	printf("lwib socket listening %d\n", s);
	 
	if (bind(s, (struct sockaddr *)&saddr,sizeof(saddr)) <0) {
		lwb_debug(ERROR,"system call","bind",0);
    }
 
	if (listen(s, 16) < 0) {
		lwb_debug(ERROR,"system call","listen",0);
    }
    
	for (hit = 1;; hit++) {
		length = sizeof(caddr);
		if((socketfd = accept(s, (struct sockaddr *)&caddr, &length)) < 0)
			lwb_debug(ERROR,"system call","accept",0);
 
		lwb_debug(LOG, "socketfd", NULL, socketfd);
 
		if((pid = fork()) < 0) {
			lwb_debug(ERROR,"system call","fork",0);
		}
		else {
			if (pid == CHILD) {
				close(s);
				web(socketfd, hit, dext); /* never returns */
			}
			else { 	/* parent */
				close(socketfd);
			}
		}
	}
	free(dext);
}
