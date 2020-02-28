#!/usr/bin/env python3
'''
Neural Network to recognize handwritten digits.
'''
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import os, time
from PIL import Image
import numpy as np
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

mmnist_path = "MMNIST_data/"

print("\n\n## Dataset ##\n\n")
print("Importing data from: " + mmnist_path)
mnist = input_data.read_data_sets(mmnist_path, one_hot=True)

print("\n\n## Dataset Info ##\n\n")
n_train = mnist.train.num_examples
print("mmnist_data examples   >> %d" % n_train)
n_validation = mnist.validation.num_examples
print("mmnist_data validation >> %d" % n_validation)
n_test = mnist.test.num_examples
print("mmnist_data test       >> %d" % n_test)

print("\n\n## Layers ##\n\n")
n_input = 784
print("(0) Input Layer  >> %d (28x28 pixels)" % n_input)
n_hidden1 = 512
print("(1) Hidden layer >> %d" % n_hidden1)
n_hidden2 = 256
print("(2) Hidden layer >> %d" % n_hidden2)
n_hidden3 = 128
print("(3) Hidden layer >> %d" % n_hidden3)
n_output = 10
print("(4) Output layer >> %d (0-9 digits)" % n_output)

print("\n\n## Parameters ##\n\n")
learning_rate = 1e-4
print("Learning rate     >> %e" % learning_rate)
n_iterations = 1000
print("Iterations number >> %d" % n_iterations)
batch_size = 128
print("batch_size number >> %d" % batch_size)
dropout = 1.0
print("dropout number    >> %f" % dropout)

X = tf.placeholder("float", [None, n_input])
Y = tf.placeholder("float", [None, n_output])
keep_prob = tf.placeholder(tf.float32)

weights = {
    'w1': tf.Variable(tf.truncated_normal([n_input, n_hidden1], stddev=0.1)),
    'w2': tf.Variable(tf.truncated_normal([n_hidden1, n_hidden2], stddev=0.1)),
    'w3': tf.Variable(tf.truncated_normal([n_hidden2, n_hidden3], stddev=0.1)),
    'out': tf.Variable(tf.truncated_normal([n_hidden3, n_output], stddev=0.1)),
}

biases = {
    'b1': tf.Variable(tf.constant(0.1, shape=[n_hidden1])),
    'b2': tf.Variable(tf.constant(0.1, shape=[n_hidden2])),
    'b3': tf.Variable(tf.constant(0.1, shape=[n_hidden3])),
    'out': tf.Variable(tf.constant(0.1, shape=[n_output]))
}

layer_1 = tf.add(tf.matmul(X, weights['w1']), biases['b1'])
layer_2 = tf.add(tf.matmul(layer_1, weights['w2']), biases['b2'])
layer_3 = tf.add(tf.matmul(layer_2, weights['w3']), biases['b3'])
layer_drop = tf.nn.dropout(layer_3, keep_prob)
output_layer = tf.matmul(layer_3, weights['out']) + biases['out']

cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits
			(labels=Y, logits=output_layer))
train_step = tf.train.AdamOptimizer(learning_rate).minimize(cross_entropy)

correct_pred = tf.equal(tf.argmax(output_layer, 1), tf.argmax(Y, 1))
accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))

init = tf.global_variables_initializer()
saver = tf.train.Saver()
sess = tf.Session()
sess.run(init)

print("\n\n## Training ##\n\n")

t = time.process_time()
for i in range(n_iterations):
    batch_x, batch_y = mnist.train.next_batch(batch_size)
    sess.run(train_step, feed_dict={X: batch_x, Y: batch_y, keep_prob:dropout})

    if((i % 100) == 0):
        minibatch_loss, minibatch_accuracy = sess.run([cross_entropy, accuracy],
        	feed_dict={X: batch_x, Y: batch_y, keep_prob:1.0})
        print("Iteration", str(i), "\t| Loss =", str(minibatch_loss),
        	"\t| Accuracy =", str(minibatch_accuracy))
elapsed_time = time.process_time() - t

print("\nTraining time: %f seconds" % elapsed_time)

test_accuracy = sess.run(accuracy, feed_dict={X: mnist.test.images,
	Y: mnist.test.labels, keep_prob:1.0})

print("\n\n## Results ##\n\n")
print("Accuracy on test set: %f percent" % test_accuracy)

#print("\n\n## Save ##\n\n")
#save_path = saver.save(sess, "/tmp/model.ckpt")
#print("Model saved in path: %s\n" % save_path)

IMAGE_PATH = "media/test_img.png"
img = np.invert(Image.open(IMAGE_PATH).convert('L')).ravel()

prediction = sess.run(tf.argmax(output_layer,1), feed_dict={X: [img]})
print ("Prediction for test image:", np.squeeze(prediction))
