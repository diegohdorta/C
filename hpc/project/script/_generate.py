#!/usr/bin/env python

import plotly.plotly as py
import plotly.graph_objs as go

PATH = "../data/data.hole"

def file_len(fname):
    with open(fname) as f:
        for i, l in enumerate(f):
            pass
    return i + 1


n_lines = file_len(PATH)
fd = open(PATH, "r")

t1 = fd.readline()
nt1 = fd.readline()
r1 = fd.readline()
c1 = fd.readline()
r2 = fd.readline()
c2 = fd.readline()

t2 = fd.readline()
nt2 = fd.readline()
r1 = fd.readline()
c1 = fd.readline()
r2 = fd.readline()
c2 = fd.readline()

t3 = fd.readline()
nt3 = fd.readline()
r1 = fd.readline()
c1 = fd.readline()
r2 = fd.readline()
c2 = fd.readline()


t4 = fd.readline()
nt4 = fd.readline()
r1 = fd.readline()
c1 = fd.readline()
r2 = fd.readline()
c2 = fd.readline()

x = [nt1, nt2, nt3, nt4]
y = [t1, t2, t3, t4]

trace0 = go.Scatter(
    x = x,
    y = y,
    name = 'x',
    line = dict(color = ('rgb(205, 12, 24)'), width = 2)
)

data = [trace0]

layout = dict(title = 'Multithreading for Matrix Multiplication on Unix/Linux',
              xaxis = dict(domain = [0, 10], title = 'Number of Threads'),
              yaxis = dict(domain = [0, 10], title = 'Time in seconds'),
              )

fig = dict(data=data, layout=layout)
py.plot(fig, filename='styled-line')
