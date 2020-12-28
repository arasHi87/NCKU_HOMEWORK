import wordcloud
import numpy as np

from PIL import Image

number = 500
mask = np.array(Image.open('bg.jpg'))
word_counts = dict()
wc = wordcloud.WordCloud(
        background_color = 'white',
        mask = mask,
        max_words = number,
        max_font_size = 150
)

with open('result.txt', 'r') as fp:
    strings = fp.read()
    strings = strings.split('\n')

    for string in strings:
        data = string.split(' ')
        
        if len(data) >= 3:
            word_counts[data[0]] = data[1]

wc.generate_from_frequencies(word_counts)

