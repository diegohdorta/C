#  Medipix Server - Developed by Diego Dorta
#  Makefile to compile the medipix server
#  How to compile: scan-build clang -Wall -Wextra -Werror -Wno-unused-parameter -std=c11 -g 
#  -DDEBUG main.c network.c image.c medipix.c utils.c -o server
#  In case clang was not installed: sudo yum install clang
CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers -g -std=c11 -DDEBUG
ENGINE_SOURCES:= network.c image.c utils.c medipix.c
RAW_IMAGE_SOURCES:= raw.c
HEADERS:= common.h
PROGRAM:= server
all: $(PROGRAM)
$(PROGRAM): main.c $(ENGINE_SOURCES) $(RAW_IMAGE_SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) main.c $(ENGINE_SOURCES) $(RAW_IMAGE_SOURCES) -o $(PROGRAM)
test-reorder: test-reorder.c $(ENGINE_SOURCES) $(RAW_IMAGE_SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) test-reorder.c $(ENGINE_SOURCES) $(RAW_IMAGE_SOURCES) -o test-reorder
	./test-reorder
clean:
	$(RM) $(PROGRAM) test-reorder ordered.data unordered.data
