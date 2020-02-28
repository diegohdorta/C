---
layout: post
title: "Creating a NN from Scratch - Part 4"
author: "Diego Dorta"
categories: artificial
tags: [ artificial, intelligence, machine, learning, NN, tensorflow, imx8 ]
---

### Building the TensorFlow Graph

To build the `NN`, we must configure a computational graphic so the Tensorflow can
execute it. The main concept of _Tensorflow_ is the _Tensor_ - a data structure  similar
to a matrix ou initialized list, which are managed as it passes through the graphic
and updated through the learning process.

We start defining three tensors as placeholders, which are tensors in which will
feed the values later. Add the following lines into your code:

```python
X = tf.placeholder("float", [None, n_input])
Y = tf.placeholder("float", [None, n_output])
keep_prob = tf.placeholder(tf.float32)
```
The only parameters that needs to be specified is the data size which we will
be feeding. For `X` uses the format `[None, 784]`, where `None` represents
any amount, because we will be feeding in an undefined images number of 784 pixels.
The `Y` format is `[None, 10]` because we will use it as an undefined number of
labels output, with 10 possibles classes.

The _keep_prob_ tensor is used to control the dropout rate, and we initialize as
a placeholder instead of an imutable variable because we want to use the same
tensor for training (_when dropout is defined to 0.5_) and for tests (_while dropout
is defined to 1.0_).

The `NN` uses _weight_ and _bias_ during the process training, therefore we need
to define an initial value instead of an empty placeholder. These values ​​are
essentially where the network does its learning because they are used in the
neurons activations functions, representing the strength of the connections
between the units.

As the values are optimized during the training, we can set them to zero for now,
but the initial value actually has a significant impact on the final precision of
the model. We use random values from a regular truncated distribution to the weights.
We want them to be close to zero, so it can adjust in a positive or negative 
direction, and a little bit differently to generate different errors.
This ensures that the model learns something useful. Add the following lines into
your code:

```python
weights = {
    'w1': tf.Variable(tf.truncated_normal([n_input, n_hidden1], stddev=0.1)),
    'w2': tf.Variable(tf.truncated_normal([n_hidden1, n_hidden2], stddev=0.1)),
    'w3': tf.Variable(tf.truncated_normal([n_hidden2, n_hidden3], stddev=0.1)),
    'out': tf.Variable(tf.truncated_normal([n_hidden3, n_output], stddev=0.1)),
}
```
For the _bias_, we use a small constant value to ensure the tensors activate
in the initial stages and thus contribute to the propagation. The _weights_ and
_bias_ tensors are stored in dictionary objects for easy access. Add this code
into your code to define each _bias_:

```python
biases = {
    'b1': tf.Variable(tf.constant(0.1, shape=[n_hidden1])),
    'b2': tf.Variable(tf.constant(0.1, shape=[n_hidden2])),
    'b3': tf.Variable(tf.constant(0.1, shape=[n_hidden3])),
    'out': tf.Variable(tf.constant(0.1, shape=[n_output]))
}
```
Then, configure the network layers by defining the operations that manipulates
the tensors. Add these lines to your file:

```python
layer_1 = tf.add(tf.matmul(X, weights['w1']), biases['b1'])
layer_2 = tf.add(tf.matmul(layer_1, weights['w2']), biases['b2'])
layer_3 = tf.add(tf.matmul(layer_2, weights['w3']), biases['b3'])
layer_drop = tf.nn.dropout(layer_3, keep_prob)
output_layer = tf.matmul(layer_3, weights['out']) + biases['out']
```
Each hidden layer performs multiplying the array on the end of the previous layers
and the weights from current layer, and add the bias to those values. In the last
hidden layer it will be applied a kill operation using the value 0.5 from _keep_prob_.  

The final step from the graphic building is to define the loss function to optimize.
The most common choice of this function is _cross-entropy_, also known as _log-cross_,
which quantifies the difference between two distribution probability (preditions and labels).
A perfect classfication would result in a cross entropy of _0_, with the loss
completely minimized.

We also need to choose the optimization algorithm to minimize the loss function.
A process called descent gradient optimization is a common method for finding
the minimum (local) of a function, taking iterative steps along the gradient in
a negative (downstream) direction. There are several options for descending
gradient optimization algorithms implemented in _TensorFlow_, and here we use
the _Adam optimizer_. This extends to the descent gradient optimization using
the time to accelerate the process by calculating an exponentially weighted
average of the gradients and using it in the adjustments. Add the following
lines into your code::

```python
cross_entropy = tf.reduce_mean
    (tf.nn.softmax_cross_entropy_with_logits
    (labels=Y, logits=output_layer))
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
```
We defined our `NN` and build it using _Tensorflow_. The next step is to feed
the data through the graphic for training them. Then, test if actually learned
anything.

- [`Creating a NN from Scratch - Part 5`](https://diegodorta.com.br/artificial/Creating-NN-using-Tensorflow-5.html)
