# Diego Dorta <diego.dorta@nxp.com>
PKGCONFIG:= `pkg-config opencv --cflags --libs`
all: ssd-caffe ssd-tensorflow

ssd-caffe: caffe/ssd-caffe.cpp
	${CXX} -Wall -Wextra -O3 -std=c++14 caffe/ssd-caffe.cpp -o bin/ssd-caffe ${PKGCONFIG}

ssd-tensorflow: tensorflow/ssd-tensorflow.cpp
	${CXX} -Wall -Wextra -O3 -std=c++14 tensorflow/ssd-tensorflow.cpp -o bin/ssd-tensorflow ${PKGCONFIG}

build:
	mkdir -p bin model
	wget -qN https://github.com/diegohdorta/models/raw/master/caffe/MobileNetSSD_deploy.caffemodel -P model/
	wget -qN https://github.com/diegohdorta/models/raw/master/caffe/MobileNetSSD_deploy.prototxt -P model/
	wget -qN https://github.com/diegohdorta/models/raw/master/tensorflow/frozen_inference_graph.pb -P model/
	wget -qN https://github.com/diegohdorta/models/raw/master/tensorflow/graph.pbtxt -P model/
	wget -qN https://github.com/diegohdorta/models/raw/master/tensorflow/labels.txt -P model/

deploy:
	scp -r bin/* model/ root@${IMX_INET_ADDR}:/opt/

clean:
	rm -rf bin/*
