TF_INCLUDES:=-ltensorflow-lite -lpthread -ldl -O3 -g 
DEP_LIBS:= -L/home/diego/codes-local/switch-inference
CV_INCLUDES:=-lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs
WARNINGS:=-Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-security
CFLAGS:= -std=c++11 $(TF_INCLUDES) $(CV_INCLUDES) $(WARNINGS)
CFLAGS_INC += \
-I/home/diego/codes-local/switch-inference/tensorflow \
-I/home/diego/codes-local/switch-inference/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/include \
-I/home/diego/codes-local/switch-inference/tensorflow/tensorflow/lite/tools/make/downloads/absl/ \
-I$(SDKTARGETSYSROOT)/usr/include/tensorflow/contrib/lite/tools/make/downloads/flatbuffers/include/ 

SOURCES:= $(wildcard src/*.cc)
PROGRAM:= switch-demo
all: $(PROGRAM)
$(PROGRAM): $(SOURCES) Makefile
	$(CXX) $(SOURCES) -o $(PROGRAM) $(CFLAGS) $(DEP_LIBS) $(CFLAGS_INC) $(INC)
clean:
	$(RM) $(PROGRAM)
