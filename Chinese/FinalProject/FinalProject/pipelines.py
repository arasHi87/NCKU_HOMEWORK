# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
import pymongo
from itemadapter import ItemAdapter


class FinalprojectPipeline:
    def process_item(self, item, spider):
        client = pymongo.MongoClient("mongodb://{}:{}".format('127.0.0.1', '27017'))
        db = client['Dcard']
        col = db['content']

        if not col.find({'index': item['index']}).count():
            col.insert_one({
                'title': item['title'],
                'content': item['content'],
                'index': item['index'],
                'createdAt': item['createdAt'],
                'updatedAt': item['updatedAt'],
                'likeCount': item['likeCount'],
                'commentCount': item['commentCount'],
                'topics': item['topics'],
                'gender': item['gender'],
            })

        return item
