---
layout: post
title: "Creating a NN from Scratch - Part 2"
author: "Diego Dorta"
categories: artificial
tags: [ artificial, intelligence, machine, learning, NN, tensorflow, imx8 ]
---

This part explains how to use a `MMNIST` dataset:

### Importing the DataSet MMIST

The [`MMNIST`](http://yann.lecun.com/exdb/mnist/) dataset is a _classic_ in the
`Machine Learning` world, and it is filled with _28x28_ (_size pixels_) _handwritten digits_ images. Few examples included in this dataset:

<center><img src="{{site.url}}{{site.baseurl}}/assets/mmnist.png"/></center>

To use this _dataset_ we must create a file:

```bash
$ touch imx-nn.py
```
This file is used during the entire tutorial. Open it and add the following line
to import _Tensorflow_ library:

```python
import tensorflow as tf
```
To import the `MMNIST` and store the data into a variable (_mnist_) add the following
lines into your code:

```python
from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_read_sets("MMNIST_data/", one_hot=True)
```
When reading the data, we use
[_one-hot-encoding_](https://en.wikipedia.org/wiki/One-hot) to represent the images
labels (original digit, e.g. _3_). The _one-hot-encoding_ uses a array values to
represent numeric or categorical values. As our labels are for 0 to 9 digits, the
array has ten values, one for each possible digit.

One of these values is define
as _1_, to represent the digit in this array index, and the remaining ones are
define as _0_. For instance, the 3 digit number is represent using the following
array:

```bash
[0, 0, 0, 1, 0, 0, 0, 0, 0, 0]
```
In the index value _3_ is stored _1_, so the array represents the number _3_.
To represent all images, the _28x28_ pixels are compressed into a _1D_ array with
784 size pixels. Each one of the _784_ pixels that form the image is stored as a
value between _0_ and _255_.

This determines the pixel's gray scale, due our images
be represented only in black and white. Therefore, one black pixel is represent
by _255_ and one white pixels by _0_, with several shades of gray somewhere
between them.

We can use a `mnist` variable to figure out the dataset size that was imported.
Add the following lines to analyze the _num_examples_ for each one of the three
subsets:

```python
n_train = mnist.train.num_examples
n_validation = mnist.validation.num_examples
n_test = mnist.test.num_examples

# Temporarily (only for debbuging)
print(n_train)
print(n_validation)
print(n_test)
```
Take a look into the result:

```bash
(imx-handwritten-digit-demo) diego@dorta:~$ python3 imx-nn.py 
Extracting MMNIST_data/train-images-idx3-ubyte.gz
Extracting MMNIST_data/train-labels-idx1-ubyte.gz
Extracting MMNIST_data/t10k-images-idx3-ubyte.gz
Extracting MMNIST_data/t10k-labels-idx1-ubyte.gz
55000
5000
10000
```
The results determine the dataset was divided in _55.000_ images for training,
_5.000_ for validation and _10.000_ for testing. With the data imported we are
ready for thinking about our _Neural Network_ from now.

- [`Creating a NN from Scratch - Part 3`](https://diegodorta.com.br/artificial/Creating-NN-using-Tensorflow-3.html)
