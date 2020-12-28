import re
import jieba
import numpy
import pymongo
import wordcloud
import collections
import jieba.posseg

import matplotlib.pyplot as plt

from tqdm import tqdm
from PIL import Image
from logger import logger

client = pymongo.MongoClient("mongodb://{}:{}".format('127.0.0.1', 27017))
db = client['Dcard']
col = db['content']
datas = col.find({})

object_list = list()
progress = None 
number = 500

for data in datas:
    # split and remove useless word
    strings = [x for x in data['content'].split('\n') if x]
    strings.extend(data['topics'])
    pattern = re.compile(u'\t|\n|\.|-|:|;|\)|\(|\?|"')
    strings = [re.sub(pattern, '', x) for x in strings]

    # remove url
    pattern = re.compile(u'^(?:http|ftp)s?')
    strings = [re.sub(pattern, '', x) for x in strings]
    strings = [x for x in strings if x]

    # jieba
    seg_list = list()

    for string in strings:
        seg_list.extend(jieba.cut(string, cut_all=False, HMM=True))

    # remove stop word
    with open('stopwords.txt', 'r') as fp:
        stopwords = set(fp.read().split('\n'))

    stopwords.add(' ')

    for word in seg_list:
        if word not in stopwords:
            object_list.append(word)

    if progress is None:
        progress = tqdm(total=datas.count())

    progress.update(1)

# count words
count = 1
word_counts = collections.Counter(object_list)
word_counts_top = word_counts.most_common(number)

result = open('result.txt', 'w+')

for TopWord, Frequency in word_counts_top:
    for POS in jieba.posseg.cut(TopWord):
        if count == number:
            break
        if POS.flag.startswith(('a', 'v', 'n')):
            result.write('{} {} {}\n'.format(TopWord, Frequency, POS.flag))
            count += 1

# generate world cloud
mask = numpy.array(Image.open('bg.jpg'))
wc = wordcloud.WordCloud(
    background_color = 'white',
    mask = mask,
    max_words = number,
    max_font_size = 150,
    font_path = '/mnt/c/Windows/Fonts/msyh.ttc',
)

wc.generate_from_frequencies(word_counts)
wc.recolor(color_func=wordcloud.ImageColorGenerator(mask))

plt.figure('詞雲')
plt.subplots_adjust(top=0.99, bottom=0.01, right=0.99, left=0.01, hspace=0, wspace=0)
plt.imshow(wc, cmap=plt.cm.gray, interpolation='bilinear')
plt.axis('off')
plt.show()
