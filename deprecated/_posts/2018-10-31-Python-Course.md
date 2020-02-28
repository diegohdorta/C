---
layout: post
title: Introductory ML Course for iMX8
author: "Diego Dorta"
categories: artificial
tags: [artificial, intelligence, machine, learning, code, AI, python, introductory, course]
---

This course was prepared to offer concepts/knowledge to be further used in the
[`Machine Learning`](https://diegodorta.com.br/artificial/ML-Course.html) course.
The acquired theoretical and practical understanding of this module can help
getting a better comprehension of the next modules.

<center><img src="{{site.url}}{{site.baseurl}}/assets/python.png"/></center>

The _Python_ programming language is probably one of the _most popular in the world_.
From smaller companies as well as large ones use this language, many universities
also include _Python_ as the introductory programming language in their computer
science courses. _Python_ is very easy to learn and its natural quality of having
a very simple syntax offers simplicity for writing codes.
_Python_ is an open-source project and having a general purpose can also be used
as scripting roles. It is a multi-paradigm programming language supporting
object-oriented, procedural, and its powerfuls features are:

- [`Dynamic typing`](https://wiki.python.org/moin/Why%20is%20Python%20a%20dynamic%20language%20and%20also%20a%20strongly%20typed%20language);
- [`Built-in types and tools`](https://docs.python.org/3/library/stdtypes.html);
- [`Library utilities`](https://docs.python.org/3/c-api/utilities.html);
- [`Third party utilities`](https://wiki.python.org/moin/UsefulModules) (e.g. [Numpy](http://www.numpy.org/), [Scipy](https://www.scipy.org/));
- [`Automatic memory management`](https://docs.python.org/3/c-api/memory.html).

_Python_ runs _virtually_ in every major platform used today, as long as have a compatible
_Python_ interpreter installed, _Python_ programs can run in exactly same manner,
irrespective of platform. This feature makes of _Python_ an extremely portable language.

_Python_ was developed by [`Guido van Rossum`](https://gvanrossum.github.io/) at
[`CWI`](https://en.wikipedia.org/wiki/Centrum_Wiskunde_&_Informatica) in Netherlands.

### Python Applications

You can use [`Python`](https://en.wikipedia.org/wiki/List_of_Python_software) for
the following applications:

- `Web and Internet Development`;
- `Desktop GUI Applications`;
- `Scientific and Numeric`;
- `Software Development`;
- `Education`;
- `Business Applications`;
- `Games and 3D Graphics`;
- `Network Programming`;
- `Database Access`.

### Python and C Language

The following table is describing the main differences between these two programming
languages in several aspects:

|                           |                          Python                           |                               C Language                                |
|---------------------------|:---------------------------------------------------------:|:-----------------------------------------------------------------------:|
| **Paradigm**              | _Multi-paradigm_                                          | _Structured_                                                            |
| **Language Type**         | _Interpreter based language, reads the code line by line_ | _Compiled language, the source code is converted into machine language_ |
| **Memory Management**     | _Use automatic garbage collector for memory management_   | _Needs to handle memory management manually_                            |
| **Applications**          | _General-Purpose programming language_                    | _Mainly used for hardware related applications_                         |
| **Speed**                 | _Slow_                                                    | _Fast_                                                                  |
| **Variable Declaration**  | _No need to declare variable type_                        | _Compulsory to declare variable type_                                   |
| **Complexity**            | _Easy to learn, write and read_                           | _Harder than Python_                                                    |
| **Testing and Debugging** | _Easy_                                                    | _Harder than Python_                                                    |

### Brief Summary of ML Course

This section explains briefly why _Python_ is important for 
[`Machine Learning`](https://diegodorta.com.br/artificial/ML-Course.html) course. Most
of the framework/libraries for `ML` were written in _Python_, even some of those that
were written in _C_ and _C++_ and not _Python_, they still have a `sophisticated`
front-end for _Python_ so it can be easy to develop an application.

You can check the following posts to learn more about `Machine Learning`:
 
- 1 - [`Overview of AI/ML`](https://diegodorta.com.br/artificial/Overview.html)
- 2 - [`ML Rules`](https://diegodorta.com.br/artificial/Machine-Learning-Rules.html)
- 3 - [`Supervised Learning`](https://diegodorta.com.br/artificial/Scikit-Learn.html) 

You can check the following posts to learn how to install the `Machine Learning`
libraries/frameworks on `iMX6/7/8` boards:

- 1 - [`Installing ML Libraries on iMX8 (Debian system)`](https://diegodorta.com.br/artificial/Installing-Libraries-ML.html)
- 2 - [`Installing ML Libraries on iMX8 (Yocto BSP)`]()
*no date to release.*
- 3 - [`Installing ML Libraries on iMX8 (Buildroot)`]()
*will be released in Jan/2019.*

Briefly, `ML` is the art and science of giving computers the ability to learn and
make decisions from data without being explicitly programmed. For instance, use
`ML` to predict whether and e-mail is _spam_ or not, and use the same code to predict
if a fruit is an _apple_ or an _orange_.

The [`ML`](https://diegodorta.com.br/artificial/ML-Course.html) course has more details
about these technologies, for now follow a list of the most used `ML` frameworks
and a quickly description:

- [`Scikit-learn`](http://scikit-learn.org/stable/)

*Scikit-learn is a Python module integrating a wide range of state-of-the-art machine
learning algorithms for medium-scale supervised and unsupervised problems.*

- [`Tensorflow`](https://www.tensorflow.org/)

*Tensorflow is just a computational framework for expressing algorithms
involving large number of Tensor operations, since Neural networks can be expressed
as computational graphs they can be implemented using Tensorflow as a series of
operations on Tensors.*

- [`Numpy`](http://www.numpy.org/)

*Knowledge of Numpy is very much important for Machine Learning and Data Science.*

- [`Keras`](https://keras.io/)

*It provides an easy way to express Neural networks. It also provides some of the
utilities for processing data sets, compiling models, evaluating results,
visualization of graphs and many more.*

- [`Theano`](http://deeplearning.net/software/theano/tutorial/)

*Theano is a computational framework for computing multidimensional arrays. Theano
is similar to Tensorflow , but Theano is not as efficient as Tensorflow because
of its inability to suit into production environments. Theano can be used on a
parallel or distributed environments just like Tensorflow.*

### Issues

At the moment we are struggling a bit to run these frameworks in an `embedded system`,
the support behind these libraries has several dependencies and porting it to
`Yocto Project` has been quite of a hard work.

Having a full environment to start developing may take a while, but in the meanwhile
these courses can provide an overview of `ML`.

### Hardware Acceleration using GPU

To run and accelerate `ML` on `iMX` is necessary to use
[`OpenCL`](https://www.khronos.org/opencl/), the following post can explain how
to get there (still under constrution):

- [`OpenCL on iMX processors`](https://diegodorta.com.br/gpu/OpenCL-Overview.html).

## Installing Python

This module uses _Python3_ and _GNU/Linux_ as its platform. _Python_ is very easy
to be installed that the installation will be briefly approached in this module.
Just by using the `package manager` from your host machine or following the
instructions on [`Python3 Webite`](https://www.python.org/download/releases/3.0/):

```bash
$ <your_package_manager> install python3
```
If you are using `Yocto Project` to deploy images into your `iMX`, include the next
line into your `local.conf` file:

```bash
CORE_IMAGE_EXTRA_INSTALL = "python3 python3-pip"
```
If you are wondering what is `pip`, see [`this`](https://en.wikipedia.org/wiki/Pip_(package_manager)).

Further information about `Yocto iMX BSP releases` follow the post:

- [`Setting Up Yocto`](https://diegodorta.com.br/yocto/Seeting-Up-Yocto-for-iMX-BSP-releases.html)

## Python IDE

People frequently use `IDE` (*Integrated Development Environment*) for writing
and testing their codes. You can get a debugger also and make your life easier.
If you have preference for IDE, the recommendation for _`Python`_ is `PyCharm`.
You can download from:

- [`PyCharm Community Edition`](https://www.jetbrains.com/pycharm/)

This course is based in short codes, then it was used
[`gedit`](https://wiki.gnome.org/Apps/Gedit) editor.

### Python Shell and Python Interpreter

Before starting, you need to know that you can use the _Python_ *shell* to write
and run your _scripts_ or write the code in a _file_ and run it by executing it.

_Python_ *interpreter* is more of a program that goes through your `.py` code or
statements written in _Python Shell_ line by line and produces appropriate output.

_Python_ *shell* works exactly like _OS_ shells like _bash shell_, but in this
case, it acts as a medium between you and _Python_ *interpreter* by submitting your
code to the *interpreter*.

### Indentation

You do not need to use `[]` or `{}` to denote blocks in _Python_, but you must
use the right [`indentation`](https://docs.python.org/2.0/ref/indentation.html),
see the following examples:

```python
1    name = "Python Course"
2    if len(name) > 0:
3        new_message = "Yay! Cool course!"
4        print new_message
```
The action above are the two lines of code or block of code after the colon ":".
_Python_ was told that the two statements or block of code should be run only if
length of name is greater than 0.

However, how does python get to know what all lines of code are to be executed?

One typical way to do it in other languages is this:

```c
1   if len(name) > 0 {
2       new_message = "Yay! Cool course"
3       print new_message
4   }
```
Python relies on `indentation` for this. To know which lines or block of code is
contained under the `if` condition. How is the `indentation` created?

- 4 spaces to the right of the condition statement.
- Why 4 spaces? Convention, just the preferred number of spaces.
- Will my code work if `indentation` is not given? No!

In fact one of the most common error in python is the:

```output
Indentation Error: Unexpected Indent
```
Why did python make this choice of forced `indentation`? Remember that _Python_
lays a lot of stress on *beauty* and *readability*? 
([*Zen of Python*](https://www.python.org/dev/peps/pep-0020/))

### Python Performance

The _performance_ between `C` and `Python`:

* [`Benchmarks Games`](https://benchmarksgame-team.pages.debian.net/benchmarksgame/faster/gcc-python3.html)

Follow the difference while calculating a `binary-tree` in a few aspects:

<center><img src="{{site.url}}{{site.baseurl}}/assets/binary-tree.png"/></center>

### Python Course Modules

Follow the sequence of `Python Course`:

- [`Python Course 101`](https://diegodorta.com.br/artificial/Python-Course-101.html)
- [`Python Course 201`](https://diegodorta.com.br/artificial/Python-Course-201.html)
- [`Python Course 301`](https://diegodorta.com.br/artificial/Python-Course-301.html)
- [`ML Course`](https://diegodorta.com.br/artificial/ML-Course.html)

