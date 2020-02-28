---
layout: post
title: "Creating a NN from Scratch - Part 1"
author: "Diego Dorta"
categories: artificial
tags: [ artificial, intelligence, machine, learning, NN, tensorflow, imx8 ]
---

This post intents to explain how to build from scratch a `NN` (_Neural Network_) using 
[_Tensorflow_](https://www.tensorflow.org/) for recognizing handwritten digits
and be further executed it on a [`iMX8 QXP MEK`](https://www.nxp.com/products/processors-and-microcontrollers/arm-based-processors-and-mcus/i.mx-applications-processors/i.mx-8-processors/i.mx-8x-family-arm-cortex-a35-3d-graphics-4k-video-dsp-error-correcting-code-on-ddr:i.MX8X) board. Before starting to read this post,
it is highly recommend a previous reading of these ones:

* [`Machine Learning Overview`](https://diegodorta.com.br/artificial/Overview.html)
* [`Neural Network Overview`](https://diegodorta.com.br/artificial/Neural-Network-Overview.html)
* [`Introductory Python Course`](https://diegodorta.com.br/artificial/Python-Course.html)

The [_Tensorflow_](https://www.tensorflow.org/) is an open-source software library developed by
[_Google Brain Team_](https://ai.google/research/teams/brain) which provides a
flexible _architecture_ and can run on the _GPU_, _CPU_
and many other devices including _mobiles devices_.

This is a library for _Deep Learning Research_, and using it we can implement a small subsection of _object recognition_ (_digit recognition_). _Tensorflow_ can build and train our own `NN` to recognize and predict digits entered
as an input for our _Neural Network_.


The only requirements you must have to follow aloing with this tutorial is a familiaritary
with `ML` terms and concepts such as training and testing, features and labels, evaluation
and optimization.


The `pre-requisites` to complete this tutorial consists on a _local environment_
to develop using the following tools, that includes: _python_, _pip_ and _venv_. 
To install these tools and packages on `Ubuntu 18.04`:

```bash
$ apt-get install python3 python3-pip python3-venv
```
### Configuring the Project

Before starting to develop the _recognition digit_ program, it is required to install
a few dependencies and create a workspace to store the files. We use a _virtual Python
environment_ to manage all the dependencies of this project:

```bash
$ mkdir imx-handwritten-digit-demo
$ cd imx-handwritten-digit-demo/
```
Run the following commands to configure the _virtual environment_:

```bash
$ python3 -m venv imx-handwritten-digit-demo
$ source imx-handwritten-digit-demo/bin/activate
(imx-handwritten-digit-demo) diego@dorta:~$ 
```
Then, install the libraries for this tutorial. We use specific versions of
these libraries creating a `requirements.txt` file in the project directory, 
that specifies the requisites and the required version. Create the `requirements.txt` file:

```bash
$ touch requirements.txt
```
Open it and add the following lines:

```bash
image==1.5.20
numpy==1.14.3
tensorflow==1.4.0
```
Save it and exit. Then, install the libraries:

```bash
$ pip3 install -r requirements.txt
```
After installing the dependencies, move to the next step to start the project.

- [`Creating a NN from Scratch - Part 2`](https://diegodorta.com.br/artificial/Creating-NN-using-Tensorflow-2.html)
