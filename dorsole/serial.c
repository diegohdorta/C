#define _XOPEN_SOURCE
#include "debug.h"
#include "serial.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

static const tcflag_t lflags = ISIG | ICANON | IEXTEN;
static const tcflag_t oflags = 0;
static const tcflag_t iflags = BRKINT | ICRNL | IXON;

static struct termios old_terminal;
static int tty;

static void restore_terminal(void);
static void translate(char *s, ssize_t count);
static void print_tty_bits(int status);

int 
main(int argc, char *argv[])
{
	char buffer[BUFFER];
	char *device, *pts;
	fd_set set;
	int ready;
	ssize_t count;
	struct timeval update;
	struct termios new_terminal;
	int status;

	if (argc < 2)
		device = TTYS0;
	else
		device = argv[1];

	tty = open(device, O_RDWR);
	if (tty < 0) err_quit("%s open() failed!", trace);

	if (grantpt(tty) < 0) {
		if (errno == EINVAL) fprintf(stderr, "Opened %s...\n", device);
		else {
			close(tty);
			err_quit("%s grantpt() failed!", trace);
		}
	}
	else {
		if (unlockpt(tty) < 0) {
			close(tty);
			err_quit("%s unlockpt() failed!", trace);
		}
		pts = ptsname(tty);
		fprintf(stderr, "Created new pts %s...\n", pts);
	}

	if (tcgetattr(tty, &old_terminal) < 0) {
		close(tty);
		err_quit("%s tcgetattr() failed!", trace);

	}

	atexit(restore_terminal);
	memmove(&new_terminal, &old_terminal, sizeof(struct termios));
	new_terminal.c_iflag = iflags;
	new_terminal.c_oflag = oflags;
	new_terminal.c_lflag = lflags;
	tcsetattr(tty, TCSANOW, &new_terminal);
	FD_ZERO(&set);

	while(true) {

		FD_SET(STDIN_FILENO, &set);
		FD_SET(tty, &set);
		update.tv_sec = 0;
		update.tv_usec = 20000;
		
		ready = select(tty + 1, &set, NULL, NULL, &update);
		if (ready < 0) {
			if (errno == EINTR)
				continue;
			close(tty);
			err_quit("%s select() failed!", trace);
		}

		if (FD_ISSET(tty, &set)) {
			count = read(tty, buffer, sizeof(buffer));
			if (count == 0)	break;
			else if (count < 0) {
				if (errno == EIO) break;
					err_quit("%s tty read() failed!", trace);
			}
			else write(STDOUT_FILENO, buffer, count);
		}

		if (FD_ISSET(STDIN_FILENO, &set)) {
			count = read(STDIN_FILENO, buffer, sizeof(buffer));
			if (count < 0) err_quit("%s stdin read() failed!", trace);
			else if (count > 0) {
		       		translate(buffer, count);
				write(tty, buffer, count);
			}
			else break;
		}
	
		if (ioctl(tty, TIOCMGET, &status) == -1) {
			close(tty);
		    	err_quit("%s ioctl() failed!", trace);
	    	}
		print_tty_bits(status);
	}
	return EXIT_SUCCESS;
}

static void
restore_terminal(void)
{
	tcsetattr(tty, TCSANOW, &old_terminal);
	tcdrain(tty);
	close(tty);
}

/* stty flag "onlret" is not working, so translate manually */
static void
translate(char *s, ssize_t count)
{
        ssize_t i;

        for (i = 0; i < count; i++) {
                if (s[i] == '\n') s[i] = '\r';
        }
}

static void
print_tty_bits(int status)
{
    static int old = 0;
    
    if (status == old)
        return;
    
    if (status & TIOCM_LE)
        printf("DSR ");
    
    if (status & TIOCM_DTR)
        printf("DTR ");
    
    if (status & TIOCM_RTS)
        printf("RTS ");
    
    if (status & TIOCM_ST)
        printf("STXD ");
    
    if (status & TIOCM_SR)
        printf("SRXD ");
    
    if (status & TIOCM_CTS)
        printf("CTS ");
    
    if (status & TIOCM_CAR)
        printf("DCD ");
    
    if (status & TIOCM_RNG)
        printf("RNG ");
    
    if (status & TIOCM_DSR)
        printf("DSR ");

    puts("");
    
    old = status;
}
