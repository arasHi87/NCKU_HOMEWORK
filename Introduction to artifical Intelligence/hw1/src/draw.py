import numpy as np
from function import func
from matplotlib import pyplot
from mpl_toolkits.mplot3d import Axes3D

x_min, x_max = -50, 60
y_min, y_max = -50, 50
xaxis = np.arange(x_min, x_max, 0.1)
yaxis = np.arange(y_min, y_max, 0.1)

x, y = np.meshgrid(xaxis, yaxis)
results = np.vectorize(func)(x, y)

figure = pyplot.figure()
axis = figure.gca(projection='3d')
axis.plot_surface(x, y, results, cmap='jet')
pyplot.show()
