---
layout: post
title: "Creating a NN from Scratch - Part 3"
author: "Diego Dorta"
categories: artificial
tags: [ artificial, intelligence, machine, learning, NN, tensorflow, imx8 ]
---

### Defining the Neural Network Architecture

The architecture of a _Neural Network_ refers to elements as the number of layers,
unit numbers in each layer and how those units are connected between the layers.
As the _Neural Networks_ are briefly inspired by the functioning of the human brain,
the term unit is used to represent what would be _biologically a neuron_.

The _neurons_ transmit signals through the brain, the units take some values from
the previous units as input, does some computation, then transmit the new value
as output to other units.

These units are arranged to form the network, initiating at least one layer for
input values, and one layer for output values. The term _hidden_ layer is used
for all layers between the input and output layers, that is, those "hidden"
from the real world.

Different architectures can produce drastically divergent results, since
performance can be thought of as a function of architecture among other
things, such as parameters, data and training time.

Add the following lines into your code to store the unit numbers per layer
in the global variables. This allows us to change the architecture network
in only one place and, by the end of the tutorial, you can test by yourself
with different numbers of layers and units that will affect the model:

```python
n_input = 784   # input layer (28x28 pixels)
n_hidden1 = 512 # 1st hidden layer
n_hidden2 = 256 # 2nd hidden layer
n_hidden3 = 128 # 3rd hidden layer
n_output = 10   # output layer (0-9 digits)
```
The following diagram shows a preview of the architecture we designed, with each
layer fully connected to the adjacent layers:

<center><img src="{{site.url}}{{site.baseurl}}/assets/layers.png"/></center>

The _Deep Neural Network_ term is related with the number of hidden layers,
with _surface_ generally meaning only a _deep_ hidden layer, referring to
several hidden layers. When provided enough data training, a surface neural
network with enough number of units must theoretically be able to represent
any function as a _deep neural network_.

However, it is more computationally efficient to use a smaller deep neural network
to get the same that would require a superficial network with exponentially more
hidden units. Surface neural network also often find over fitting, where the network
essentially memorizes the training data which has seen and it is not able to 
generalize the knowledge to new data.

This makes the deep neural network be more commonly used. The many layers between
the raw input label allows the network to learn features at many levels of abstraction,
making the network itself more capable of generalizing.

Other elements from the `NN` need to be defined here are the hyper parameters, unlike
the other parameters which are used during the training, these values are defined
initially and remain constant throughout the process. Define in your file the following
variables and values:

```python
learning_rate = 1e-4
n_iterations = 1000
batch_size = 128
dropout = 0.5
```
The learning rate represents how much parameters will be adjusted at each stage
of the learning process. These adjustments are a key component for training: after
each step through the net, we adjust the weight slightly to try to reduce the loss.
Higher learning rates may converge more quickly, but it has also the potential 
to exceed ideal values while updating it.

The iterations number, refers to how many times we went through the training
step, and the batch size refers to how many training examples we are using at
each step. The dropout variable represents a threshold which it is eliminate some 
units randomly. We will be using dropout in our last hidden layer to provide each
unit 50% chance of being eliminated at each stage of the training. This helps
prevent over fitting.

Defined the architecture of _Neural Network_ and the _hyper parameters_ which impact
the learning process, the next step is to build the Network as a Tensorflow graphic.

- [`Creating a NN from Scratch - Part 4`](https://diegodorta.com.br/artificial/Creating-NN-using-Tensorflow-4.html)

