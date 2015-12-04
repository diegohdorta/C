#  Medipix Server - Developed by Diego Dorta
#  Makefile to compile the medipix server
#  How to compile: scan-build clang -Wall -Wextra -Werror -Wno-unused-parameter -std=c11 -g 
#  -DDEBUG main.c network.c image.c medipix.c utils.c -o server
#  In case clang was not installed: sudo yum install clang
CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers -g -std=c11 -DDEBUG
ENGINE_SOURCES:= network.c image.c utils.c medipix.c
RAW_IMAGE_SOURCES:= raw.c
TIFF_IMAGE_SOURCES:= tiff.c conversions.c
LIBTIFF_LDFLAGS:= -ltiff
HEADERS:= common.h
PROGRAM:= server
all: $(PROGRAM)-raw $(PROGRAM)-tiff
$(PROGRAM)-raw: main.c $(ENGINE_SOURCES) $(RAW_IMAGE_SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) main.c $(ENGINE_SOURCES) $(RAW_IMAGE_SOURCES) -o $(PROGRAM)-raw
$(PROGRAM)-tiff: main.c $(ENGINE_SOURCES) $(TIFF_IMAGE_SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) main.c $(ENGINE_SOURCES) $(TIFF_IMAGE_SOURCES) -o $(PROGRAM)-tiff \
		$(LIBTIFF_LDFLAGS)
test-reorder: test-reorder.c $(ENGINE_SOURCES) $(RAW_IMAGE_SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) test-reorder.c $(ENGINE_SOURCES) $(RAW_IMAGE_SOURCES) -o test-reorder
	./test-reorder
test-tiff: $(TIFF_IMAGE_SOURCES) $(HEADERS) utils.c test-tiff.c Makefile
	$(CC) $(CFLAGS) $(TIFF_IMAGE_SOURCES) utils.c test-tiff.c -o test-tiff \
		$(LIBTIFF_LDFLAGS)
clean:
	$(RM) $(PROGRAM)-raw $(PROGRAM)-tiff test-reorder ordered.data unordered.data test-tiff
