## Building

The following command-line creates model folder and retrieves models for 'Caffe'
and 'TensorFlow' frameworks:

```bash
$ make build
```
## Compiling

For compiling these examples, run the following command-line:

```bash
$ source /opt/fsl-imx-xwayland/4.14-sumo/environment-setup-aarch64-poky-linux
$ make
```
## Deploying

Run the following command-lines replacing <boards_ip> for respective IP address:

```bash
$ export IMX_INET_ADDR=<boards_ip>
$ make deploy
```

# Install on Ubuntu

```bash
$ git clone https://github.com/opencv/opencv.git
$ git clone https://github.com/opencv/opencv_contrib.git
```

```bash
$ mkdir build
$ cd build
$ cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D INSTALL_C_EXAMPLES=OFF \
-D INSTALL_PYTHON_EXAMPLES=ON \
-D WITH_TBB=ON \
-D WITH_V4L=ON \
-D WITH_QT=ON \
-D WITH_OPENGL=ON \
-D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
-D BUILD_EXAMPLES=OFF ..
```
