import pymongo
import numpy as np
import matplotlib.pyplot as plt

from matplotlib import style

style.use('dark_background')

client = pymongo.MongoClient("mongodb://{}:{}".format('127.0.0.1', 27017))
db = client['Dcard']
col = db['content']

x_pt = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
y_pt = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

for data in col.find({}):
    time = data['createdAt'].split('T')[0].split('-')
    
    if time[0] == '2020':
        y_pt[int(time[1])-1] += 1

y_pt[7], y_pt[10] = y_pt[10], y_pt[7]

plt.figure(figsize=(16, 9))
plt.plot(x_pt, y_pt)
plt.savefig('fig.png')
