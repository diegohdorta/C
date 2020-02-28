---
layout: post
title: "Creating a NN from Scratch - Part 5"
author: "Diego Dorta"
categories: artificial
tags: [ artificial, intelligence, machine, learning, NN, tensorflow, imx8 ]
---

### Training

The training process involves feeding the training dataset through the graph and
optimizing the loss function. Every time the network iterates a batch of more
training images, it updates the parameters to reduce the loss in order to be a
more accurately predict the displayed digits. The test process involves running
our test dataset through the trained chart and tracking the number of images
that are correctly predicted so that we can calculate the accuracy.

Before beginning the training process, we must define our precision evaluation
method so that we can print it in mini-batches of data while we train. These
printed statements allow us to verify that, from the first iteration to the
last one, the loss decreases and the accuracy increases. They also allow us
to track whether or not we perform enough repetitions to achieve a consistent
and optimal result:

```python
correct_pred = tf.equal(tf.argmax(output_layer, 1), tf.argmax(Y, 1))
accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))
```
In correct_pred, we use the arg_max function to compare which images are being
predicted correctly by looking at output_layer (predictions) and Y (labels),
and use the equal function to return this as a list of Booleans. We can then
convert this list into floats and calculate the mean to get a total score
of precision.

Now we are ready to initialize a session to execute the graph. In this session,
we feed the network with our training examples and, once trained, feed the same
graph with new test samples to determine the accuracy of the model. Add the
following lines of code to your file:

```python
init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)
```
The essence of the deep learning training process is to optimize the loss function.
Here, we want to minimize the difference between the predicted labels of the images
and the true labels of the images. The process involves four steps that are repeated
for a defined number of iterations:

* Propagate values ​​forward through the network
* Computing the loss
* Propagate values ​​back through the network
* Update parameters

At each training stage, the parameters are slightly adjusted to try to reduce the
loss to the next step. As learning progresses, we should see a reduction in loss
and eventually we can stop training and use the network as a template to test our
new data:

```python
for i in range(n_iterations):
    batch_x, batch_y = mnist.train.next_batch(batch_size)
    sess.run(train_step, feed_dict={X: batch_x, Y: batch_y, keep_prob:dropout})

    if ((i % 100) == 0):
        minibatch_loss, minibatch_accuracy = sess.run([cross_entropy, accuracy],
        	feed_dict={X: batch_x, Y: batch_y, keep_prob:1.0})
        print("Iteration", str(i), "\t| Loss =", str(minibatch_loss), "\t|
        	Accuracy =", str(minibatch_accuracy))
```

After _100_ iterations of each training step in which we feed a mini-batch of images
through the network, we print the loss and accuracy of this batch. Note that we
should not expect a decreasing loss and increasing precision here, since the values
​​are per batch, not for the entire model. We use mini-batches of images instead of
feeding them individually to speed up the training process and allow the network
to see several different examples before updating the parameters.

When the training is complete, we can run the session on the test images. This time
we're using a keep_prob dropout rate of 1.0 to ensure that all drives are active in
the test process.

```python
test_accuracy = sess.run(accuracy,
	feed_dict={X: mnist.test.images, Y: mnist.test.labels, keep_prob:1.0})
print("\nAccuracy on test set:", test_accuracy)
```
Now is the time to run our program and see how accurately our neural network can
recognize these handwritten digits. Save the main.py file and run the following
command on the terminal to run the script:

```bash
$ python3 imx-nn.py
```
You will see output similar to the following, although individual loss and accuracy
results may vary slightly:

```output
Iteration 0     | Loss = 3.67079    | Accuracy = 0.140625
Iteration 100   | Loss = 0.492122   | Accuracy = 0.84375
Iteration 200   | Loss = 0.421595   | Accuracy = 0.882812
Iteration 300   | Loss = 0.307726   | Accuracy = 0.921875
Iteration 400   | Loss = 0.392948   | Accuracy = 0.882812
Iteration 500   | Loss = 0.371461   | Accuracy = 0.90625
Iteration 600   | Loss = 0.378425   | Accuracy = 0.882812
Iteration 700   | Loss = 0.338605   | Accuracy = 0.914062
Iteration 800   | Loss = 0.379697   | Accuracy = 0.875
Iteration 900   | Loss = 0.444303   | Accuracy = 0.90625

Accuracy on test set: 0.9206
```
- [`Creating a NN from Scratch - Part 6`](https://diegodorta.com.br/artificial/Creating-NN-using-Tensorflow-6.html)

