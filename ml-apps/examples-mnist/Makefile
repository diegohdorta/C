# Diego Dorta <diego.dorta@nxp.com>
all: 1-example 2-example 3-example

1-example: src/1-example.cpp armnn/mnist_loader.hpp
	${CXX} -Wall -Wextra -O3 -std=c++14 src/1-example.cpp -o bin/1-example -larmnn -larmnnCaffeParser

2-example: src/2-example.cpp armnn/mnist_loader.hpp
	${CXX} -Wall -Wextra -O3 -std=c++14 src/2-example.cpp -o bin/2-example -larmnn -larmnnTfParser

3-example: src/3-example.cpp armnn-draw/mnist_loader.hpp
	${CXX} -Wall -Wextra -O3 -std=c++14 src/3-example.cpp -o bin/3-example -larmnn -larmnnTfParser
	
build:
	mkdir -p bin data model
	wget -qN https://github.com/ARM-software/ML-examples/raw/master/armnn-mnist/data/t10k-images-idx3-ubyte -P data/
	wget -qN https://github.com/ARM-software/ML-examples/raw/master/armnn-mnist/data/t10k-labels-idx1-ubyte -P data/
	wget -qN https://github.com/ARM-software/ML-examples/raw/master/armnn-mnist/model/lenet_iter_9000.caffemodel -P model/
	wget -qN https://github.com/ARM-software/ML-examples/raw/master/armnn-mnist/model/simple_mnist_tf.pb -P model/
	wget -qN https://github.com/ARM-software/ML-examples/raw/master/armnn-mnist/model/simple_mnist_tf.prototxt -P model/
	wget -qN https://github.com/ARM-software/Tool-Solutions/raw/master/ml-tool-examples/mnist-draw/model/optimized_mnist_tf.pb -P model/

deploy:
	scp -r bin/* html/* data/ model/ root@${IMX_INET_ADDR}:/opt/mnist

clean:
	rm -rf bin/*
	
	

