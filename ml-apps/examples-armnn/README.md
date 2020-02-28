## Getting Models

On the board, run the following commands:

```bash
root@imx8mmevk:# mkdir /opt/armnn
root@imx8mmevk:# mkdir /opt/armnn/media
root@imx8mmevk:# chmod 777 /opt/armnn
```
### Building

```bash
$ make build
```

### Deploying

```bash
$ export IMX_INET_ADDR=<boards_ip>
$ make deploy
```
## Running

### Example Inception

Put your photo inside `media` folder, and then run:

```bash
root@imx8mmevk:/opt/armnn/1-example# ./armnn-inception.py
```
