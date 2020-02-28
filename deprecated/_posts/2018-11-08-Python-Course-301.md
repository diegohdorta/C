---
layout: post
title: "Python Course 301"
author: "Diego Dorta"
categories: artificial
tags: [ artificial, intelligence, mar=chine, learning, code, AI, python, introductory, course ]
---

Before jumping to `Machine Learning` course, there are a few fundamental concepts
of _Python_ that is desired to know and review it due its intensive use during the
course. If you get _Python_ or it is already familiar, feel free to skip this `301`
section. If you still are a beginner it will be very helpful to learn the following
examples before moving on.

## Variables

You can assign any item in _Python_ to a `variable`, to refer to or operate on later:

```python
var = "Hello Course"
print(var)
```
**Output**:

```output
Hello Course
```
## Lists

We start with the most _basic_ `data containers` in _Python_, `lists`:

```python
list = [2, 5, 7, -2, 0, 8, 13]
```
Lists are *0-indexed*, so index _2_ is the _third element_ in `list`:

```python
print(list[2])
```
**Output**:

```output
7
```
### Slicing

Referring to `subsets` of `lists` (_remember the 0 indexing_):

```python
y = list[0:2]
print(y)
```
**Output**:

```output
[2, 5]
```
### List Operations

Various methods for lists:

Find `index` of element with value `5`:

```python
print(list.index(7))
```
**Output**:

```output
2
```
Count `number` of elements in `list`:

```python
print(len(list))
```
**Output**:

```output
7
```
Add element to the end of the `list`:

```python
list.append(99)
print(list)
```
**Output**:

```output
[2, 5, 7, -2, 0, 8, 13, 99]
```
Insert element at index `2`:

```python
list.insert(1, 55)
print(list)
```
**Output**:

```output
[2, 55, 5, 7, -2, 0, 8, 13, 99]
```
### List Comprehensions

Convenient way in _Python_ to make lists which are functions of other lists.
Note the `**` operator is an exponent, so `x**2` means `x square 2`.
 
New list is _squares_ of `z`:

```python
z = [x**2 for x in list]
print(z)
```
**Output**:

```output
[4, 3025, 25, 49, 4, 0, 64, 169, 9801]
```
New list is `True/False` if element is `> 3` or not:

```python
z = [x>3 for x in list]
print(z)
```
**Output**:

```output
[False, True, True, True, False, False, True, True, True]
```
## Dictionaries

Another way of _storing data_, which can be looked up using keys:

```python
z = {'name':'Systems', 'apples':5, 'oranges':8}
print(z['name'])
print(z['oranges'])
if("apples" in z):
    print('yes, the key apples is in the dict z')
```
**Output**:

```output
Systems
8
yes, the key apples is in the dict z
```
## Loops

`For-loops` are simple, but we will learn powerful ways to avoid them with _Numpy_,
because they are not optimized for _speed_:

```python
names = ['Breno', 'Diego', 'Marco', 'Vanessa']
for name in names:
    print('Hi %s' % name)
```
**Output**:

```output
Hi Breno
Hi Diego
Hi Marco
Hi Vanessa
```
Get a `list` of integers between two _endpoints_ with range:

```python
for i in range(5, 9):
    print(i)
```
**Output**:

```output
5
6
7
8
```
## Functions

A function is a _reusable block of code_:

```python
def myFunction(myArgument):
    print("Hello " + myArgument)
    
myFunction('Diego')
myFunction('Vanessa')
```
**Output**:

```output
Hello Diego
Hello Vanessa
```
## Classes

Classes bring `object-oriented` programming to Python:

```python
class MyClass(object):
    def __init__(self, message):
        self.message = message
    
    def print_message(self, n_times=2):
        for i in range(n_times):
            print('%s' % self.message)

M = MyClass('Hello from Course!')
M.print_message(3)
```
**Output**:

```output
Hello from Course!
Hello from Course!
Hello from Course!
```
## Libraries

There are many available libraries for Python for various functions. Import
two libraries: `math` and `matplotlib.pyplot` (_alias to plt_). Use the `math`
function to calculate the _cosine_ of `1`.

```python
import matplotlib.pyplot as plt
import math

z = math.cos(1)
print(z)
```
**Output**:

```output
0.5403023058681398
```

## Plotting

_Plot_ our sine curve. We'll be plotting a lot to make concepts more visually
clear in the future.

```python
X = [0.1*x for x in range(-50,50)]
Y = [math.sin(x) for x in X]

plt.figure(figsize=(6,6))
plt.plot(X, Y)
plt.xlabel('x')
plt.ylabel('y = sin(x)')
plt.title('My plot title')
```
**Output**:

```output
<matplotlib.text.Text at 0x109130860>
```
You can also save your plot as `png` image:

```python
plt.savefig("test.png")
```
<center><img src="{{site.url}}{{site.baseurl}}/assets/plot.png"/></center>

- [`Machine Learning Course`](https://diegodorta.com.br/artificial/ML-Course.html)
