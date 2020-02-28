# Diego Dorta <diego.dorta@nxp.com>
build:
	mkdir -p media model
	wget -qN https://github.com/diegohdorta/models/raw/master/caffe/MobileNetSSD_deploy.caffemodel -P model/
	wget -qN https://github.com/diegohdorta/models/raw/master/caffe/MobileNetSSD_deploy.prototxt -P model/

deploy:
	scp -r 1-example.py 2-example.py model/ media/ root@${IMX_INET_ADDR}:/opt/opencv
	
