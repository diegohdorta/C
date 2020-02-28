## Getting Models

On the board, run the following commands:

```bash
root@imx8mmevk:# mkdir /opt/opencv
root@imx8mmevk:# mkdir /opt/opencv/media
root@imx8mmevk:# chmod 777 /opt/opencv
```
### Building

Build for retrieving models:

```bash
$ make build
```
Your folder structure must be equal to:

```bash
$ tree
├── 1-example.py
├── Makefile
├── media
│   └── <images>
├── model
│   ├── MobileNetSSD_deploy.caffemodel
│   └── MobileNetSSD_deploy.prototxt
```
### Deploying

```bash
$ export IMX_INET_ADDR=<boards_ip>
$ make deploy
```
## Running

### 1-Example using Caffe with Images

This example comes with one picture for example, but you can download as 
many pictures as you want too and save them inside `media/` folder. Then,
the application tries to recognize all the objects in the picture:

```bash
root@imx8mmevk:/opt/opencv/media# wget <imageLink>
```

Testing the example picture:

<center><img src="https://bitbucket.sw.nxp.com/users/nxf47857/repos/ml-applications/raw/examples-opencv/media/image.jpg?at=refs%2Fheads%2Fmaster" alt="Normal Image" align="middle" width="640"/></center>

```bash
root@imx8mmevk:/opt/opencv# ./1-example.py
```
This examples uses OpenCL:

```bash
root@imx8mmevk:/opt/opencv# ./1-example.py 
[ INFO:0] Initialize OpenCL runtime...
root@imx8mmevk:/opt/opencv# 
```
The images are available in `media-labeled/` folder:

<center><img src="https://bitbucket.sw.nxp.com/users/nxf47857/repos/ml-applications/raw/examples-opencv/media-labeled/image.jpg?at=refs%2Fheads%2Fmaster" alt="Labeled Image" align="middle" width="640"/></center>

### 2-Example using Caffe with Camera

This example enables the `MIPI` camera and runs an inference on each captured
frame, then it displays as output video:

```bash
root@imx8mmevk:/opt/opencv# ./2-example.py
```
`MIPI` camera screenshot running `Caffe` model and `OpenCV`:

<center><img src="https://bitbucket.sw.nxp.com/users/nxf47857/repos/ml-applications/raw/examples-opencv/media/mipiCamera.png?at=refs%2Fheads%2Fmaster" alt="Labeled Image" align="middle" width="640"/></center>



