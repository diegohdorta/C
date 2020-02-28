---
layout: post
title: "Machine Learning for Noob"
author: "Diego Dorta"
categories: artificial
tags: [ artificial, intelligence, machine, learning, code, AI, introductory, noob, quick ]
---

Driving cars were made only by humans at least until a few years ago, but with the
computer learning and its advance making improvements over the years we are now
having autonomous car in test and also talking driver assistants.

If we need to write a program to play the [_**Tic-Tac-Toe.exe**_](https://playtictactoe.org/)
we would need to give all the instructions, for example:

* _If opponent occupies two houses in a row, then do the third;_
* _else if there is any movement that creates two lines with two fill houses, do it;_
* _else if the center is empty, do it;_
* _else if the opponent fills the corner, do the opposite fifth;_
* _else if there is a fifth empty, do it;_
* _else if none of the rules applies, do any empty house._

_Pedro Domingos_ explains on his book [_The Master Algorithm_](https://en.wikipedia.org/wiki/The_Master_Algorithm)
that this _algorithm_ does not lose in the _Tic-Tac-Toe_  game. However, this
game is simple and now imagine a _Chess_ game, where each move has an average of
**35** possible possibilities, to make a program that cover all the possibities
it is almost impossible, or worse, impracticable.

More complex problems, such as recognizing 
[_**Sarah_Connor.exe**_](https://en.wikipedia.org/wiki/Sarah_Connor_(Terminator)) would require
tunes of rules:

* _classify if is it a human being;_
* _if positive, then classify if it is a female;_
* _if positive, then classify if it is _Sarah Connor;_
* _if positive, then kill her._

It gets harder to create the rules as the problem increases it, but we do not need
to create rules, we can allow the computer to learn and create its own programs,
after all ourselves needed to learn either.

## Supervised Learning

We spent a good time with our parents and friends pointing to a _cat_ until we learn
to know the difference between a _dog_ and a _cat_, this is the
[`Supervised Learning`](https://en.wikipedia.org/wiki/Supervised_learning), where somebody already knew and trained us.

The same happens with _Google_ while we point the people in a photo, or which image
has a car/bus in a captcha, which that we are supervising the _Google Algorithms_
to learn and training them at the same time. This probably works as well to train
the [_Skynet_](https://en.wikipedia.org/wiki/Skynet_(Terminator)) to pursuit the
right [_rebel_](https://www.microsoft.com/).

_Machine Learning uses data and_tests to make improvements in a program, so
the computer can analyses using all the collected data._

It has many types of _supervised learning algorithms_ to process texts, numbers
and images. Even on more complex situations than
[_The Terminator_](https://en.wikipedia.org/wiki/The_Terminator) time line,
such as looking into your e-mail content to detect if the e-mail is spam, or
something that can avoid a bank or credit card fraud.

This does not need to always be _supervised_, even not being a fan of
[_Pokemons_](https://en.wikipedia.org/wiki/Pok%C3%A9mon)
it is easy to look from the original game and define/gather those from
_water_, _fire_ or _psychic_. If no one tell us which groups to create or look for, 
we can create ourselves the groups and gather it. The same way when a computer
learn how to cluster and give different responses.

The _**Netflix**_ does not need to offers only one list of movies, it can let the
algorithm learn based on your previous tastes then offering you a more personal
list that you might enjoy.

## Reinforcement Learning

Other type of learning that we use are the 
[`Reinforcement Learning`](https://en.wikipedia.org/wiki/Reinforcement_learning),
which is when your parents may had tell that a flame of a candle hurts, but touching
the flame also teaches quickly, and we can do the same to teach computers using _Neural
Networks_, like the [`Deep Learning`](https://en.wikipedia.org/wiki/Deep_learning)
that emulates how our brain works.

For instance, to recognize if someone is _Sarah Connor_, a `NN` (_Neural Network_)
can use the first layer of data to broke the photo into pixels, the second to
compare the pixels with its neighbors to ignore the equals ones and gets 
the ones that change and define a edge (like the _face contours_). The third
layer of processing compares the edges to get if they form a pattern like the eyes
or eyes brown.

The next layer compares these patterns with the original photo of _Sarah Connor_.
If identifies a perfect match with the face, the connections which gave this
correct data are reinforcement and gain more weight than others.

One `NN` trained using reinforcement learning can quickly improve itself to 
recognize patterns being able to drive an autonomous car, or put a snap filter
into your face. This type of `NN` strategy of deep neural networks became well
known around _2012_, and from now on changed what machines can do.

If a _Chess_ game has **35** possible movements a [`_Go_`](https://en.wikipedia.org/wiki/Go_(game))
game has more than **250**
positions. Even the _Deep Blue_ computer won from the _World Chess Champion_,
_Kasparov_ in _1997_, imagined the computers would take decades to beat _Go_, until
a program called _Alpha Go_ use deep neural network to analyze human behavior
and won from the _World Champing_, _Lee Sedol_ in _2016_ from _4_ to _1_.

It was probably the last victory from a human against the machines in _GO_, because
the next version called _Alpha Go Zero_ does not even used _supervised learning_, it was
just coded with regular rules of _Go_, and without never had seen a human move, play
with itself innumerable times reinforcing its strategies which were success
and forgetting the ones that failed. After being trained won from _Alpha Go_ from _100_
to _0_.

The next challenge will probably be to win a strategy game, like
[`DOTA 2`](https://en.wikipedia.org/wiki/Dota_2) or [`Starcraft`](https://en.wikipedia.org/wiki/StarCraft)
which are much more closer to real life than _Go_. Which play has thousands of
possible movements that are not so clear like in the Chess, and you can not see
the whole map and know everything about the opponent.

No program until today could handle more than a few minutes against a professional
starcraft player, and this could still take decades, until we have a machine learning
method able to handle problems that include goals and long thoughts, but this was
what we thoughts about _Go_ until a little time ago.
