---
layout: post
title: Python Course 101
author: "Diego Dorta"
categories: artificial
tags: [artificial, intelligence, machine, learning, code, AI, python, introductory, course]
---

In most of the programming languages a variable is a named location used to store
data in the _memory_. Each variable must have a unique name called _identifier_.
It is helpful to think of variables as container that hold data which can be
changed later _throughout programming_.

Non technically, you can suppose variable as a bag to store books in it and those
books can be replaced at anytime.

**Note**: In _Python_ we don't assign values to the variables, whereas _Python_
gives the reference of the object (value) to the variable.

In _Python_, variables do not need declaration to reserve memory space.
The "variable declaration" or "variable initialization" happens automatically
when we assign a value to a variable.¹

[1] - [Reference](https://www.programiz.com/)

### Hello World Example

Follow the `Hello World` example in _C_ language:

```c
#include <stdio.h>

int main(void)
{
	printf("Hello World!\n");
	return 0;
}
```
To compile this example you just need to use _gcc_:

```bash
$ gcc -Wall example.c -o helloworld
```
Run the generated binary code by:

```bash
$ ./helloworld
```
The same example in _Python3_:

```python
#!/usr/bin/env python3

print("Hello World!")
```
_Python_ is interpreted, so you have two ways for running this code. One way is
using the _Python_ in the terminal:

```bash
$ python3 example.py
```
The other way and most appropriate one is to set _**shebang**_ line that defines where
the interpreter is located. A _**shebang**_ line can be written in two forms:

```python
#!/usr/bin/python3
```
This case specifies that the _Python3_ interpreter is located in `/usr/bin/python3`,
and this can be used for _**bash**_, _**ruby**_, _**perl**_ or any other _scripting languages interpreter_.

The _OS_ does not know it is a _Python_ script if you do not set the execution _flag_ in
the script, give it permission to execute and run it like:

```bash
$ chmod +x example.py
$ ./example.py
```
You can use `/usr/bin/env python3` for portability across different platforms.
This can guarantee the execution even if the `language interpreter` is installed
in different locations.

*Recommended*:

```python
#!/usr/bin/env python3
```

Even if the process for these two programming languages are different, the
`Hello World` codes are equivalent and have the same output:

```output
Hello World
```

### Data types in Python

There are many data types in _Python_, and everything is an object in _Python_
programming, data types are actually classes and variables are instance of these
classes.

_Python_ has *six* standard data types. Some of the important types are listed below:

- [`Numbers`](https://docs.python.org/2/library/numbers.html)

_Python numbers_ are integers, floating point numbers and complex numbers that
falls under _Python_ numbers category. They are defined as `int`, `float` and
complex class in _Python_.

We can use the _type()_ function to know which class a variable or a value belongs to:

```python
#!/usr/bin/env python3

var = 10
print(var)
print(type(var))
```
The output:

```output
10
<class 'int'>
```
- [`String`](https://docs.python.org/2/library/string.html#module-string)

_Python string_ is a sequence of `Unicode` characters. We can use single quotes
or double quotes to represent _strings_. Multi-line strings can be denoted using
triple quotes, `'''` or `"""`. Index starts form **0** in _Python_. Follow an example:

```python
var = 'Hello world!'

print("var[4] = ", var[4])
print("var[6:11] = ", var[6:11])
```
The output:

```output
var[4] =  o
var[6:11] =  world
```
_Strings are_ _**immutable**_. This means that you should think variable in _Python_ as
a _tag_. You can move the _tag_ to different objects:

```python
#!/usr/bin/env python3

var = "course"
print(var)
print(type(var))

var = 10
print(var)
print(type(var))
```
The output:

```output
course
<class 'str'>
10
<class 'int'>
```

_var_ can point to different objects, since all variables in _Python_ are objects.
However, immutability refers to the object, not the _tag_. If you try to
`var[1] = "a"` to turn `Hello` into `Hallo` you would get the error:

```error
TypeError: 'str' object does not support item assignment"
```

This is because _strings_ in _Python_ does not support *item assignment*, thus
they are _**immutable**_.

- [`List`](https://docs.python.org/3/tutorial/datastructures.html#more-on-lists)

_Python list_ is an ordered sequence of items. It is one of the most used `data type`
in _Python_ and is very `flexible`. All the items in a list do not need to be of
the same type. Declaring a list is **pretty straight forward**. Items separated
by _commas_ are enclosed within _brackets_ `[]`.

```python
>>> list = [1, 2.2, 'python']
```
We can use the slicing operator `[]` to extract an item or a range of items
from a list. Example:

```python
var = [5,10,15,20,25,30,35,40]

print("var[2] = ", var[2])
print("var[0:3] = ", var[0:3])
print("var[5:] = ", var[5:])
```

The output:

```output
var[2] =  15
var[0:3] =  [5, 10, 15]
var[5:] =  [30, 35, 40]
```
_Lists are_ _**mutable**_, meaning, value of elements of a list can be altered.

- [`Tuple`](https://docs.python.org/3/tutorial/datastructures.html#tuples-and-sequences)

_Python tuple_ is an ordered sequence of items same as list. The only difference
is that _tuples are_ _**immutable**_. Tuples once created **can not be modified**.

Tuples are used to _write-protect_ data and are usually `faster` than list as it
**can not change dynamically**.

It is defined within parentheses `()` where items are separated by commas:

```python
>>> t = (10,'course', 1+10j)
```
We can use the slicing operator `[]` to extract items, but we can not change its
_value_.

```python
t = (10,'course', 1+10j)

print("t[1] = ", t[1])
print("t[0:3] = ", t[0:3])
```
The output:

```output
t[1] =  course
t[0:3] =  (10, 'course', (1+10j))
```
- [`Dictionary`](https://docs.python.org/3/tutorial/datastructures.html#dictionaries)

_Python dictionary_ is an unordered collection of `key-value pairs`. It is generally
used when we have a huge _amount of data_. Dictionaries are optimized for _retrieving data_.
We must know the key to retrieve the value.

In _Python_, dictionaries are defined within braces `{}` with each item being a
pair in the form `key:value`. Key and value can be of any type.

```python
>>> d = {1:'value','key':2}
>>> type(d)
<class 'dict'>
```
We use `key` to retrieve the respective value, but _**not**_ _the other way around_.

```python
d = {1:'value','key':2}

print(type(d))
print("d[1] = ", d[1]);
print("d['key'] = ", d['key']);
```
The output:

```output
<class 'dict'>
d[1] =  value
d['key'] =  2
```
- [`Set`](https://docs.python.org/3/tutorial/datastructures.html#sets)

_Python set_ is an unordered collection of unique items. Set is defined by values
separated by comma inside braces `{}`. Items in a set are not ordered.

We can perform set operations like union, intersection on two sets. Set have
unique values. They eliminate duplicates:

```python
>>> a = {1,2,2,3,3,3}
>>> a
{1, 2, 3}
```
Set in _Python_ are unordered collection, indexing has **no meaning**. Hence the
slicing operator [] does not work:

```python
>>> a = {1,2,3}
>>> a[1]
Traceback (most recent call last):
  File "<string>", line 301, in runcode
  File "<interactive input>", line 1, in <module>
TypeError: 'set' object does not support indexing
```

### Rules and Naming Convention

Follow **rules** and **naming** convention for variables and constants:

- Create a name that **makes sense**. Suppose, _vowel_ makes more sense than _v_.
- Use [`camelCase`](https://en.wikipedia.org/wiki/Camel_case) notation to declare
a variable. It starts with _lowercase_ letter. For example:

```output
myName
myAge
myAddress
```
- Use capital letters where possible to declare a constant. For example:

```output
PI
G
MASS
TEMP
```
- Never use special symbols like `!, @, #, $, %`, etc.
- Don't start name with a digit.
- Constants are put into _Python_ modules and meant not be changed.
- Constant and variable names should have combination of letters in lowercase
`(a to z)` or uppercase `(A to Z)` or digits `(0 to 9)` or an underscore `(_)`.

```output
snake_case
MACRO_CASE
camelCase
CapWords
```
### File, Functions, Exception

The following code shows a few concepts of a programming language. In this example,
it is explore how to *open* a file, *writing* and *reading* it. _Python_ has a `built-in`
function `open()` to open a file. This function returns a `file object`, also called
a handle, as it is used to read or modify the file accordingly:

```python
1  #!/usr/bin/env python3
2
3  def open_file(file):
4    try:
5      fd = open(file, "w", encoding = "utf-8")
6      fd.write("Python Course\n")
7    except:
8      raise ValueError
9    finally:
10      fd.close()
11   return
12
13 def read_file(file):
14   with open(file, "r", encoding = "utf-8") as f:
15     print(f.read())
16   return
17
18 def main():
19   print("Calling open_file() function")
20   open_file("test.txt")
21
22   print("Calling read_file() function")
23   read_file("test.txt")
24
25 if __name__ == "__main__":
26   main()
```
This code you can probably see `encoding = "utf-8"`, unlike other languages, the
character `a` does not imply the number `97` until it is encoded using `ASCII`
(or other equivalent encoding). Moreover, the default encoding is platform dependent.

In _Windows_, it is used `cp1252`, but in *GNU/Linux* is `utf-8`. So, we must not
rely on the default encoding or else our code will behave differently in different
platforms.¹ Hence, when working with files in text mode, it is highly recommended
to specify the encoding type.

We need to properly close the file, closing a file will free up the resources that
were tied with the file and is done using _Python_ `close()` method as line _10_.

_Python_ has a
[`garbage collector`](https://en.wikipedia.org/wiki/Garbage_collection_(computer_science))
to clean up _unreferenced objects_, but we must not rely on it to close the file.

This method is not _entirely safe_. If an exception occurs when we are performing
some operation with the file, the code exits without closing the file.

A safer way is to use a _try_ and _finally_ block. This way, we are guaranteed that
the file is properly closed even if an `exception` is raised, causing program flow
to stop.

The best way to do this is using the `with` statement as line _14_. This ensures
that the file is closed when the block inside with is exited. We don't need to
explicitly call the `close()` method. It is done _internally_.

- [`Python Course 201`](https://diegodorta.com.br/artificial/Python-Course-201.html)

