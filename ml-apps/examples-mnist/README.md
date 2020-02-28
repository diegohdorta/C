## Getting Models

On `iMX` board, run the following commands:

```bash
# mkdir /opt/mnist
# chmod 777 /opt/mnist
```
### Building

The following command-line will create data and model folders retrieving the mnist
data set with 10K images test, and also the models for Caffe and TensorFlow:

```bash
$ make build
```
Your folder structure must be equal to:

```bash
$ tree
...
├── armnn
│   └── mnist_loader.hpp
├── data
│   ├── t10k-images-idx3-ubyte
│   └── t10k-labels-idx1-ubyte
├── model
│   ├── lenet_iter_9000.caffemodel
│   ├── optimized_mnist_tf.pb
│   ├── simple_mnist_tf.pb
│   └── simple_mnist_tf.prototxt
|...
```
### Compiling

For compiling these examples, run the following command-lines:

```bash
$ source /opt/fsl-imx-xwayland/4.14-sumo/environment-setup-aarch64-poky-linux
$ make
```
This generates the binaries.

### Deploying

This is just an easy alternative for deploying the binaries to the board, feel
free to use others methods. For using this helper deploy feature, you must
modify the `Makefile` adding your boards ip, then run the following command-line:

```bash
$ export IMX_INET_ADDR=<boards_ip>
$ make deploy
```
## Running

### 1-Example using Caffe

```bash
$ ./1-example 100
```

### 2-Example using TensorFlow

```bash
$ ./2-example 100
```

### 3-Example Drawing HTML Page

```bash
$ python3 -m http.server --cgi 8000
```
