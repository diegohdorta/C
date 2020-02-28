#ifndef _LWBDEBUG_H_
#define _LWBDEBUG_H_

#define BUFSIZE 8096
#define ERROR 42
#define SORRY 43
#define LOG   44
#define LOGFILE "slwib-running.log"

void lwb_debug(int type, char *s1, char *s2, int num);


#endif /* _LWBDEBUG_H_DEFINED_ */
