---
layout: post
title: "Python Course 201"
author: "Diego Dorta"
categories: artificial
tags: [ artificial, intelligence, machine, learning, code, AI, python, introductory, course ]
---

This section approaches the _list_ concept in _Python_ and jumps a head a little
to demonstrate how `data structures` are important while developing applications
for `ML` projects. 

A _list_ in _Python_ can be written as a _list_ of `comma-separated` values (_items_)
between _square brackets_. In _Python_ a _list_ does not need to be of the same type.

The following examples demonstrate how to handle _lists_, and how you use _list_
in a simple `ML` code example.

### Example 1

```python
#!/usr/bin/env python3

team = ["Breno", "Daiane", "Diego", "Fabio", "Marcelo",
	"Marco", "Renato", "Rogerio", "Vanessa"]

print(len(team))
print(team)
print(team[4])
print(team[0:4])

for member in team:
  print(member)
```
Running the above code the result is:

```output
9

['Breno', 'Daiane', 'Diego', 'Fabio', 'Marcelo', 'Marco', 'Renato', 'Rogerio', 'Vanessa']

Marcelo

['Breno', 'Daiane', 'Diego', 'Fabio']

Breno
Daiane
Diego
Fabio
Marcelo
Marco
Renato
Rogerio
Vanessa
```
### Example 2

This code shows how can you put a _list_ inside of a _list_:

```python
#!/usr/bin/env python3

team = [["Breno", "Security"],
	["Daiane", "Yocto"],
	["Diego", "ML"],
	["Fabio", "UBoot"],
	["Marcelo", "Pico"],
	["Marco", "Gstreamer"],
	["Renato", "KDE"],
	["Rogerio", "VPU"],
	["Vanessa", "Hardware"]]
	
for member in team:
  print("Name: " + member[0])

for member in team:
  print("Job description: " + member[1])
```
Output:

```output
Name: Breno
Name: Daiane
Name: Diego
Name: Fabio
Name: Marcelo
Name: Marco
Name: Renato
Name: Rogerio
Name: Vanessa


Job description: Security
Job description: Yocto
Job description: ML
Job description: UBoot
Job description: Pico
Job description: Gstreamer
Job description: KDE
Job description: VPU
Job description: Hardware
```
### Example 3

With the _list_ concept explained above, we can run a simple `ML` program. This program
is just to tell the difference between a `Border Collie` and a `Gold Retriever`.
It is the same example from `types of fruits`, so to learn more about
`Supervised Learning` read this [`post`](https://diegodorta.com.br/artificial/Scikit-Learn.html).

The `UCI` has a [`Machine Learning Repository`](http://archive.ics.uci.edu/ml/index.php)
that you can download data sets from their community. It is done to use in your code.

Well, we need to create a model to be used to predict whether is a `Border Collie`
or a `Golden Retriever`. Collecting data like its weight and color can probably be
enough to train a model:

```python
import sklearn

features = [["yellow", 55],
	    ["yellow", 66],
	    ["yellow", 75],
	    ["yellow", 69],
	    ["black", 30],
	    ["black", 36],
	    ["black", 38],
	    ["black", 33],
	    ["white", 41],
	    ["white", 33],
	    ["white", 35],
	    ["white", 45]]

labels = ["Golden Retriever",
          "Golden Retriever",
          "Golden Retriever",
          "Golden Retriever",
          "Border Collie",
          "Border Collie",
          "Border Collie",
          "Border Collie",
          "Border Collie",
          "Border Collie",
          "Border Collie",
          "Border Collie"]
```
This _framework_ `Scikit-learn` uses real-valued features, it is required to change
the variable types of all features to `ints` types instead of `strings` types.
The _yellow_ color for `Golden Retriever` is `0`, and _black_ or _white_ for
`Border Collie` is `1`. Also, `0` defines a `Golden Retriever` and `1` defines
a `Border Collie`. The _weight_ is given in `pounds`.

```python
import sklearn

features = [[0, 55],
	    [0, 66],
	    [0, 75],
	    [0, 69],
	    [1, 30],
	    [1, 36],
	    [1, 38],
	    [1, 33],
	    [1, 41],
	    [1, 33],
	    [1, 35],
	    [1, 45]]

labels = [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
```
An `embedded systems` most of the time does not have a high performance like a
`cloud server`. This statement goes over our mind of how can a small system
train a `model` for `Machine Learning`? 

The answer is that **we should not train the model** in the `embedded system` we
just need to use it. Think in a car example:

_The model must not be trained in a car, it needs to train this model in a 
`Cloud Server`. The only thing the car must do is to collect `data` while driving
on the streets, and when it gets home upload all the collected data to the
`Cloud Server` so it can be trained during the night, once it was re-trained
the car download this new model and it is done to go on the streets again._

The following code trains a _classifier_ using a _decision tree_ and a _fit_
function. Then, it saves the trained model to be further used.

```python
#!/usr/bin/env python3

from sklearn import tree
import pickle as pk

features = [[0, 55],
	    [0, 66],
	    [0, 75],
	    [0, 69],
	    [1, 30],
	    [1, 36],
	    [1, 38],
	    [1, 33],
	    [1, 41],
	    [1, 33],
	    [1, 35],
	    [1, 45]]

labels = [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]

model = tree.DecisionTreeClassifier()
model = model.fit(features, labels)

pk.dump(model, open("trained_model.sav", "wb"))
```
The next code opens the `pre-built model` and use it to predict which `dog` is:

```python
#!/usr/bin/env python3

import sys
from sklearn import tree
import pickle as pk

colour = sys.argv[1]
weight = sys.argv[2]

loaded_model = pk.load(open("trained_model.sav", 'rb'))

prediction = loaded_model.predict([[colour, weight]])

if(prediction == 0):
  print("[%d], so it is Golden Retriever.\n" % prediction)
elif(prediction == 1):
  print("[%d], so it is Border Collie.\n" % prediction)
```
Executing this code and passing `0` (_Yellow_) and any weight `60` pounds,
this is probably a `Golden Retriever`:

```python
$ ./example.py 0 60
[1], so it is Golden Retriever.
```
- [`Python Course 301`](https://diegodorta.com.br/artificial/Python-Course-301.html)
