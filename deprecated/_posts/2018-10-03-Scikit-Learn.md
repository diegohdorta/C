---
layout: post
title: "Fruits Code - Supervised Learning"
author: "Diego Dorta"
categories: artificial
tags: [artificial, intelligence, marchine, learning, code, AI]
---

This post consists to collect training data. For solving this problem, we are going to write a function to classify
a piece of fruit. For starters, it will take a description of the fruit as input and predict whether it's an **apple**
or an **orange** as output, based on features like its weight and texture.

Imagine you go to the mall and stop your car at the front door. Then, your car goes park by itself. When the car is parked, it keeps monitoring your steps by GPS. When you get to the front door of the mall again, your car goes where you are to pick up you. This examples can be implement using _ML_ for training data, such as learning the way, obstacles, where is the front door and etc. To use the _supervised learning_, let's follow a recipe with a few standard steps:

## Collect Training Data

This first step consists on collecting the training data, these are examples of the problem that needs to be solved. To collect this data, imagine an orchard, you look at different **apples** and **oranges**,
and write down measurements that describe them in a table. In _ML_ these measurements are called _features_.


### Features as Training Data

| Weight   |      Texture      |  Label |
|:----------:|:-------------:|:------:|
| 150g |  bumpy  | orange |
| 170g |  bumpy  | orange |
| 140g |  smooth | apple |
| 130g |  smooth | apple |


This example must be simple, so let's just use two types. A good feature makes it easy to discriminate between types of fruits, the features in this case are the weight and texture, and each row in the training data is an example describing a piece of fruit.
How much does each fruit **weights** in grams? And about its **texture**? Is it be **bumpy** or **smooth**?

The last column is called the label, that identifies what type of fruit is in each row, and there are just two possibilities - **apple** and **orange**.
The entire table is the training data, think of these as all the examples we want the classifier to learn from. The more training data you have, the better a classifier you can create.

### Writing the code

Let's write down our training data in code:

```python
 import sklearn
 features = [[140, "smooth"], [130, "smooth"], [150, "bumpy"], [170, "bumpy"]]
 labels = ["apple","apple","orange","orange"]
```

Two variables _features_ and _labels_ were used, features contains the first two columns, and the labels contains the last. You can think of features as the input, and the classifier and labels as the output we want it.

_Scikit-learn_ uses real-valued features, so let's change the variable tupes of all features to _ints_ types intead of _strings_ types.
Here let's use **0** for **bumpy** and **1** for **smooth**. Doing the same for labels, we have **0** for **apple** and **1** for **orange**.

```python
 import sklearn
 features = [[140, 1], [130, 1], [150, 0], [170, 0]]
 labels = [0, 0, 1, 1]
```

## Training a classifier

This second step uses the written features to train a classifier. This particular case, the type of classifier that will be used is called _decision tree_.

### Decision tree

More details about the mechanism of this _Decision tree_ will be explain on the next section. For now, think of a classifier as a **box of rules**. That's because there are many different types of classifier, but the input and ouput are always the same.

### Importing the tree

To import this _decision tree_, change the _import_ line in the code, and call the function as follows:

```python
 from sklearn import tree
 features = [[140, 1], [130, 1], [150, 0], [170, 0]]
 labels = [0, 0, 1, 1]
 clf = tree.DecisionTreeClassifier()
```

At this point, it's just an empty box of rules. It does not know anything about **apples** and **oranges** yet. To train it, we will need to use a learning algorithm. If the classifier is a box of rules, you can think of learning algorithm as the **procedure that creates them**. It does that just by finding patterns in the training data. For example, it might notice *oranges* tend to weight more, so it will create a rule saying that the **heavier** fruits are more likely to be an **orange**.

### Fit Function

In this _scikit_ library, the training algorithm is included in the classifier object, and it's called _Fit_, as follows:

```python
 from sklearn import tree
 features = [[140, 1], [130, 1], [150, 0], [170, 0]]
 labels = [0, 0, 1, 1]
 clf = tree.DecisionTreeClassifier()
 clf = clf.fit(features, labels)
```

You can think of _Fit_ as being a synonym for "find patterns in data". The next section get into the details of how this happens under the hood.

At this point, the classifier is trained. So let's take it for a spin and use it to classify a new fruit. The input to the classifier is the features for a new example, let's also
pass the _argument variables_ to make it easier, for measuring how much time the board took for training the data.

```python
 import sys, time
 from sklearn import tree
 features = [[140, 1], [130, 1], [150, 0], [170, 0]]
 labels = [0, 0, 1, 1]
 start_time = time.time()
 clf = tree.DecisionTreeClassifier()
 clf = clf.fit(features, labels)
 weight = sys.argv[1]
 texture = sys.argv[2]
 print clf.predict([[weight, texture]])
 print ("Time for training data: %s seconds" % (time.time() - start_time))
```

## Output fruit

Let's say the fruit we want to classify is **160 grams** and **bumpy**, the output will be **0** if it's an **apple** or **1** it's an **orange**. Before hiting enter and see what the classifier predicts, let's think for a second.

If you had to guess, what would you say the output should be? To figure that out, compare this fruit to our training data. It looks like it's similiar to an orange, because it's heavy and bumpy. That is what I'd guess anyway, and if we hit enter:

<center><img src="{{site.url}}{{site.baseurl}}/assets/result.png"/></center>

The result is **[1]**. It's what our classifier predicts as well (recall we used **0** for **apple**, and **1** for **orange**).
The first _Machine Learning_ program is created. It is possible to create a new classifier for a new program, just by changing the training data. That makes this approach more reusable than writing new rules for each problem.

This fruit example uses a table of features instead of pictures to be simple. It is possible to use pictures as training data. It would be something like:

### Picture as Training Data

| Picture     |  Label |
|:----------:|:-------------:|:------:|
| orange_image.jpg | orange |
| orange_image.jpg | orange |
| apple_image.jpg | apple |
| apple_image.jpg | apple |


This training data will be approchead on further examples. This code is more general, the neat thing is that programming for _Machine Learning_ is not hard, but to get it right, you need to understand a few important concepts on the next section.

The next document will contain examples for: unsupervised learning, semi supervised learning and reinforcement.
