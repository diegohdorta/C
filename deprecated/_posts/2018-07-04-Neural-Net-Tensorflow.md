---
layout: post
title: "Neural Network using Tensorflow"
author: "Diego Dorta"
categories: artificial
tags: [artificial, intelligence, marchine, learning, code, AI, neural, network, tensorflow]
---

This post approaches a way to create a very simple `Neural Network` using `Tensorflow` library.

The follow `Neural` consists of an input layer of tree nodes, a hidden layer with two nodes, and an output layer with one node:

<center><img src="{{site.url}}{{site.baseurl}}/assets/neural.png"/></center>

The `neurons` are fully connected, the inputs are simple such as: 1, 2 and 3, 
and the `Sigmoid` function is use in the hidden and output layers. Also, `weight` and `bias` parameters
to this model are respectively, 1 and 0, to be easy to calculate.

## Sigmoid Function

Sigmoid function is an `activation` function that transform linear inputs to nonlinear outputs, 
and its bound outputs are between 0 and 1 which can be interpreted as a probability.

This is a written `Sigmoid` function in Python:

```python
import numpy as np

def sigmoid(x):
        return 1/(1 + np.exp(-x))
```

## Calculating

With the `Neural` defined and all the other parameters specified, we can manually calculate. So, a normal equation of a straight line is represented by:

```math
y = m*x + c
```
Where, `m` is the slope, `c` is the constant. In `linear` regression model, slope is the `weight`, and the constant is the `bias`.
So, the basic model turn into:

```math
h = weight*x + bias
```
Where, `x` is `input` variable or features, and `y` is `output` variable or target variable.

The math for this model can be written as:

```math
1: 1.1 + 1.2 + 1.3 = 6 + 0 = 6
2: S(6).1 + S(6) + 0
3: S(S(6).1 + S(6) + 0) 
4: S(2.S(6))
```
With the `Sigmoid` function written in Python, we can calculate the results:

<center><img src="{{site.url}}{{site.baseurl}}/assets/sigmoid.png"/></center>

## Using Tensorflow

To install `Tensorflow` on your `iMX` board, you can follow this post:

- [`Machine Learning Libraries for iMX`](https://diegodorta.com.br/artificial/Installing-Libraries-ML.html).

After following all the steps from the previous post, you can run:

```bash
$ pip install -U tensorflow --index-url=https://pypi.python.org/simple/
```
Using `Tensforflow` to calculate:

```python
import numpy as np
import tensorflow as tf

number_input = 3
number_hidden = 2
number_output = 1

W = { "h1": tf.Variable(tf.ones([number_input,
	number_hidden]),name="h1"),
        "out": tf.Variable(tf.ones(
        [number_hidden, number_output]))
}

B = { "b1": tf.Variable(tf.zeros
	([number_hidden])),
        "bout": tf.Variable
        (tf.zeros([number_output]))
}

x = tf.placeholder("float", [None, number_input])
y = tf.placeholder("float", [None, number_output])


l1 = tf.add(tf.matmul(x,W["h1"]),B["b1"])
l1_act = tf.sigmoid(l1)

out = tf.add(tf.matmul(l1_act,W["out"]),B["bout"])
out_act = tf.sigmoid(out)

cost = tf.reduce_mean(tf.abs(tf.subtract(out_act,y)))
train_step = (tf.train.AdadeltaOptimizer
		(learning_rate=1.0).minimize(cost))

x_raw = np.array([[1,2,3]])
y_raw = np.array([3])
y_raw = np.reshape(y_raw,(1,1))

with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        pred = out_act.eval({x: x_raw})

        for epoch in range(100):
		k = sess.run(train_step,
			feed_dict={x: x_raw,y: y_raw})

print(pred)
```
<center><img src="{{site.url}}{{site.baseurl}}/assets/code.png"/></center>

It seems that all have worked out. The next posts will explain more detailed how `tensorflow` works.




