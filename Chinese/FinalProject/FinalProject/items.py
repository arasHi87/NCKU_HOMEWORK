# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class PostItem(scrapy.Item):
    title = scrapy.Field()
    content = scrapy.Field()
    index = scrapy.Field()
    createdAt = scrapy.Field()
    updatedAt = scrapy.Field()
    likeCount = scrapy.Field()
    commentCount = scrapy.Field()
    topics = scrapy.Field()
    gender = scrapy.Field()

