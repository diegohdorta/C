---
layout: post
title: "From Auxerre to the World"
author: "Diego Dorta"
categories: python
tags: [ python, fourier, series, math, auxerre, world, code ]
---

This code was written for plotting the terms of Fourier series for a `Square Wave`.

## Installation

You must have the following `python packages` installed on your running machine:

* Matplotlib
* Numpy

You may need `root` privileges:

```
 $ apt-get install python python-matplotlib python-numpy
```

This code was developed and tested over `Ubuntu 18.04 LTS`.

## Running

You can `clone` the repository:

```bash
$ git clone https://github.com/diegohdorta/python-fourier
```

Or you can use this code:

```python
#!/usr/bin/env python

import sys

from numpy import pi
from numpy import sin
from numpy import cos
from numpy import arange

import matplotlib.pyplot as plt

def nindex():
    '''
    nindex: function for defining the initial coordinates,
    getting the n-terms entered by user, and sum all the Fourier terms.
    '''
    y = (0.5)
    x = arange(-2 * pi, 2 * pi, 0.0001)
    if len(sys.argv) < 2:
        terms = 2
    else:
        terms = int(sys.argv[1]) + 1

    for i in range(1, terms):
        if (i % 2):
# Where magic happens:
            y += (2 / (pi*i)) * sin(i*x)
    return x, y, terms

def main():
# Defining and calculating the n-terms of Fourier Series
    x, y, terms = nindex()
    term = str(terms-1)

# All the above commands can be found examples 
# here: https://matplotlib.org/gallery/index.html
# Building the graphics with Matplotlib
    y2 = [1, 0, 1, 0, 1]
    x2 = [(-2*pi), (-pi), 0, (pi), (2*pi)]
    y3 = [0, 1, 0, 1, 0]

# Defining the graphic area:
    figure = plt.figure()
    ax = figure.add_subplot(111)

# Changing the x label coordinate to radians:
    ax_label = [r"$-{2\pi}$", r"$-\pi$", r"$0$", r"$\pi$", r"${2\pi}$"]
    ax.set_xticks(x2)
    ax.set_xticklabels(ax_label)

# Following it plots the terms on the graphic and overlaying 
# it with square wave.
# Plotting the Fourier series terms:
    ax.plot(x, y, label=r'$S_{'+term+'}(x)$', zorder=999)

# Plotting f(x) which is the square wave:
    ax.step([(-2*pi), (-pi)], [1, 1], 'r', [(-pi), 0], [0, 0], 'r', 
    [0, (pi)], [1, 1], 'r', [(pi), (2*pi)], [0, 0], 'r')

# Plotting label for f(x):
    ax.step(0,0,'r',label=r'$f(x)$')

# Left and right boundaries for f(x):
    ax.scatter(x2, y2, s = 30, c = 'r', edgecolors ='r')
    ax.scatter(x2, y3, s = 30, c = 'w', edgecolors ='r')
    ax.legend(bbox_to_anchor=(0, 1.02, 1, .102), loc=3,ncol=2, 
    mode="expand", borderaxespad=0.)

# Showing the graphic on screen:
    plt.title("From Auxerre to the World")
    plt.axes().set_ylim([-0.4, 1.4])
    plt.axes().set_aspect(pi, 'box')
    plt.grid()

# Saving plot to png image:
    plt.savefig('square_'+term+'_.png') 
    plt.show()

if __name__ == "__main__":
    main()
```

You must enter the `n-index` term to be calculated. For instance, if you want to
simulate the result of the first 2 terms of fourier series:

### 2 Terms

```
 $ python code.py 2
```
The code will sum all the terms until 2 and overlay it with a square wave.

<center><img src="{{site.url}}{{site.baseurl}}/assets/square_2_.png"/></center>

Take a look into other examples, as the input increases:

### 15 Terms

```
 $ python code.py 15
```
<center><img src="{{site.url}}{{site.baseurl}}/assets/square_15_.png"/></center>

You can see that as you increase the input terms the more accurate the result gets.
