# Diego Dorta <diego.dorta@nxp.com>
build:
	mkdir -p models media
	wget -qN https://github.com/diegohdorta/models/raw/master/tensorflow/inception_v3_2016_08_28_frozen_transformed.pb -P models/

deploy:
	scp -r 2-example/* media/ root@${IMX_INET_ADDR}:/opt/armnn
	scp -r models/* root@${IMX_INET_ADDR}:/opt/armnn/models

