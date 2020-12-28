import json
import scrapy

from FinalProject.items import PostItem

class DcardSpider(scrapy.Spider):
    name = 'Dcard'
    
    def start_requests(self):
        _url = 'https://www.dcard.tw/_api/search/posts?limit=100&query={}&offset={}'
        start_urls = list()
        keywords = [
                '想自殺',
                '想去死',
                '想輕生',
                '不想活',
                '想結束生命',
                '想結束一切',]
        self.headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.88 Safari/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
            'Cookie': '__cfduid=ddbb5aae4f86be6ffb6f0166f6b00d21b1609043430; dcsrd=Rk3DBwG-Ml5YaNcX4XfBHb1J; dcsrd.sig=wDYeppHZF2zBPsPl2A0LQRP2hIg; cf_chl_1=a894552c7137d30; cf_chl_prog=a17; cf_clearance=098bc17b2c98933d17d28280c028368e9c1de701-1609049879-0-250', 
            'Sec-ch-ua': '"Google Chrome";v="87", " Not;A Brand";v="99", "Chromium";v="87"'
        }

        for keyword in keywords:
            for offset in range(0, 8000, 100):
                yield scrapy.Request(url=_url.format(keyword, offset), headers=self.headers, callback=self.parse)

    def parse(self, response):
        posts = json.loads(response.text)
        PostURL = 'https://www.dcard.tw/_api/posts/{}' 

        for post in posts:
            yield scrapy.Request(PostURL.format(post['id']), headers=self.headers, callback=self.parse_post)

    def parse_post(self, response):
        items = PostItem()
        post = json.loads(response.text)

        items['title'] = post['title']
        items['content'] = post['content']
        items['index'] = post['id']
        items['createdAt'] = post['createdAt']
        items['updatedAt'] = post['updatedAt']
        items['likeCount'] = post['likeCount']
        items['commentCount'] = post['commentCount']
        items['topics'] = post['topics']
        items['gender'] = post['gender']

        yield items
