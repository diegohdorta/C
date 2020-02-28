---
layout: post
title: "Recurrent Neural Network Sketching"
author: "Diego Dorta"
categories: artificial
tags: [ neural, network, deep, ML, demo, imx8, javascript, python, server, http, recurrent ]
---

This post shows a very simple video of a `RNN` demo written in _Javascript_ running
over a _Python Server_ on a `iMX8 QXP MEK board`. The board does not processes any data
regarding the _hidden layers_ of this _neural network_, it only hosts the web page
that supports the demo on it.

`Recurrent Neural Network` is used in applications such as _handwriting analysis_,
_video analysis_, _translation_, and other interpretation of various human tasks.
Since, it is very difficult to train a `RNN` model, this demo was just applied in
form of a `http server` to show how it works and be funny.

* Video on [YouTube](https://www.youtube.com/watch?v=oyllpkWqq0Q).

<iframe width="560" height="315" src="https://www.youtube.com/embed/oyllpkWqq0Q" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen align="center"></iframe>

This `RNN` was copied from `Google`, but the project is hosted on
[`GitHub`](https://github.com/diegohdorta/feynman/tree/master/ml-demos).

```bash
$ python3 -m http.server
```
<center><img src="{{site.url}}{{site.baseurl}}/assets/webserver.gif"/></center>

The page is available on your local `http://0.0.0.0:8000`.
