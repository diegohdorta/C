---
layout: post
title: "Creating a NN from Scratch - Part 6"
author: "Diego Dorta"
categories: artificial
tags: [ artificial, intelligence, machine, learning, NN, tensorflow, imx8 ]
---

### Testing

To try to improve the accuracy of our model, or to learn more about the impact of
tuning hyperparameters, we can test the effect of changing the learning rate,
dropout limit, batch size, and number of iterations. We can also change the number
of units in our hidden layers and change the amount of their own hidden layers
to see how different architectures increase or decrease the accuracy of the model.

To demonstrate that the network is really recognizing hand-drawn images, let's
test it in a single image of ours.

First, download
[_this_](https://raw.githubusercontent.com/diegohdorta/chroniclesincoding/master/assets/test_img.png)
sample test image or open a graphic editor and create your own 28x28 pixel one-digit image.

<center><img src="{{site.url}}{{site.baseurl}}/assets/test_img.png"/></center>

Open the main.py file in your editor and add the following lines of code to the
top of the file to import two libraries needed for image manipulation.

```python
import numpy as np
from PIL import Image
```
Then, at the end of the file, add the following line of code to load the test
image of the handwritten digit:

```python
img = np.invert(Image.open("test_img.png").convert('L')).ravel()
```
The open function of the Image library loads the test image as a 4D array containing
the three RGB color channels and the Alpha transparency. This is not the same
representation we used earlier when reading the dataset with TensorFlow, so we
need to do some extra work to match the format.

First, we use the convert function with the L parameter to reduce the 4D RGBA
representation to a grayscale color channel. We store this as a numpy array
and invert it using np.invert, because the current array represents black as
0 and white as 255, but we need the opposite. Finally, we call ravel to
flatten the array.

Now that the image data is structured correctly, we can run a session in the
same way as before, but this time just feeding a single image to test. Add
the following code to your file to test the image and print the output label.

```python
prediction = sess.run(tf.argmax(output_layer,1), feed_dict={X: [img]})
print ("Prediction for test image:", np.squeeze(prediction))
```
The np.squeeze function is called in the prediction to return the single integer
of the array (ie to go from [2] to 2). The resulting output demonstrates that
the network recognized this image as digit 2.

<center><img src="{{site.url}}{{site.baseurl}}/assets/predict.gif"/></center>

You can try testing the network with more complex images - digits that look like
other digits, for example, or digits that have been poorly drawn or drawn
incorrectly - to see how it goes.

In this tutorial you have successfully trained a neural network to classify
the MNIST dataset with about 92% accuracy and tested on your own image.
The state of the art in current research reaches about 99% in this same problem,
using more complex network architectures involving convolutional layers.
They use the 2D structure of the image to better represent the content,
unlike our method that flattens all pixels in a array of 784 units. You can
read more about this topic on the TensorFlow website, and see the research
papers detailing the most accurate results in the MNIST site.

Now that you know how to build and train a neural network, you can try to
use that implementation in your own data or test it on other popular datasets,
such as Google StreetView House Numbers, or the CIFAR-10 dataset for more
generic image recognition.


#### IMPORTANT NOTE

This tutorial does not recognize the digits as we normally write them, all the
digits inside _MNIST_ has a certain format, however no one writes with a perfect
white pen on a black background. If you use your camera or a photo where the digit
is not in the center, then it will not work properly. 

If we use another digit as the input for our _NN_ with will result in some random
numbers. Even the accuracy is around > _90%_ you still get something close to _10%_ (_random_).

The next article will demonstrate how to avoid this by improving the _NN_ and using
tools such as [_OpenCV_](https://opencv.org/) to get more accurate results.
