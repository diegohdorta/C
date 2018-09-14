---
layout: default
---

If you are ~~weak/leech~~ mainstream guy or give up too easily, I highly recommended to you to close this github page and never come back.

I can not change your life, actually no one can do it for you, but there is something I might be able to help you to get it.

Most of the **discombobulated** things in the Universe, I can explain it. I can also guide you to the unlimited.

[comment]: <> ####### (START POST NUMBER: 3) #######

# [](#header-1)Post #3: Have Tup ~~Makefile~~ fought the law?

[Tup](http://gittup.org/tup) is a file-based build system for Linux, OSX, and Windows.
It inputs a list of file changes and a directed acyclic graph (DAG), then processes the
DAG to execute the appropriate commands required to update dependent files. Updates are
performed with very little overhead since tup implements powerful build algorithms to
avoid doing unnecessary work. This means you can stay focused on your project rather
than on your build system.

A simple code for getting time shows that Tup really works:

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 100

#ifdef __GNUC__ /* The __GNUC__ also works with clang compiler */
static void debug(FILE *output, const char *format, ...)
	__attribute__((format (printf, 2, 3)));
#else
static void debug(FILE *output, const char *format, ...);
#endif

int main(void)
{
	debug(stderr, "Have you ever fought the law?\n");
	return EXIT_SUCCESS;
}

void debug(FILE *output, const char *format, ...)
{
	unsigned int r;
	char now_text[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	va_list args;

	struct tm now_struct;
	time_t now;

	time(&now);
	localtime_r(&now, &now_struct);
	strftime(now_text, sizeof(now_text),
		"%A %d %B %Y %H:%M:%S %Z # ", &now_struct);

	va_start(args, format);
	r = vsnprintf(buffer, BUFFER_SIZE, format, args);
	va_end(args);

	if (r >= 0) {
		strncat(now_text, buffer, BUFFER_SIZE - 1);
		fputs(now_text, output);
	}
}
```

Inside **Tupfile**:
```
: example.c |> gcc example.c -o example |> example
```
For building, type __tup upd__:

```
diego@dorta:~/tup$ tup upd
[ tup ] [0.000s] Scanning filesystem...
[ tup ] [0.000s] Reading in new environment variables...
[ tup ] [0.001s] No Tupfiles to parse.
[ tup ] [0.001s] No files to delete.
[ tup ] [0.001s] Executing Commands...
 1) [0.062s] gcc example.c -o example
 [ ] 100%
[ tup ] [0.170s] Updated.
diego@dorta:~/tup$ ./example
Monday 02 October 2017 15:39:45 BRT # Have you ever fought the law?
```

Think about the output message! [Tup examples](http://gittup.org/tup/ex_a_first_tupfile.html).

[comment]: <> ####### (END POST NUMBER: 3) #######


[comment]: <> ####### (START POST NUMBER: 2) #######

# [](#header-1)Post #2: Not just GCC

Have you heard about _Clang compiler_?

[Clang](https://clang.llvm.org/) compiles C, C++ and Objective-C. It is based on [LLVM](https://llvm.org/). I won't get into details, all I have to say is that Clang rocks!
Most people does not know about this unknown compiler, they only uses GCC.

For a few years I have been using it, I had quite an experience helping me to get errors that I was not able before.

Try it:

```
$ sudo apt-get install clang
```

The error messages clearly make impossible not to solve it.

The simplest code in the world will show it:

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	unsigned int n = 2017;
	printf("Hello World %s", n);
	return EXIT_SUCCESS;
}
```

Compiling with GCC:

```
main.c: In function ‘main’:
main.c:8:9: warning: format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘unsigned int’ [-Wformat=]
  printf("Hello World %s", n);
         ^
```
Compiling with Clang:

```
main.c:8:27: warning: format specifies type 'char *' but the argument has type 'unsigned int' [-Wformat]
        printf("Hello World %s", n);
                            ~~   ^
                            %u
1 warning generated.
```
Equal? Except for the fact that Clang tries to give you a nice hint, printing out what you should do it.

One more extra tip: try to use _scan-build_ when you compile the program. Figure out by yourself.

```c

$ scan-build clang main.c
```

Have nothing else to say. Enjoy it.

[comment]: <> ####### (END POST NUMBER: 2) #######




[comment]: <> ####### (START POST NUMBER: 1) #######

# [](#header-1)Post #1: Dinosaur Comics

You've got to learn to crawl before you can run, T-Rex. True.

![](https://raw.githubusercontent.com/diegohdorta/diegohdorta.github.io/master/images/dinosaurcomics.png)

[comment]: <> ####### (END POST NUMBER: 1) #######
