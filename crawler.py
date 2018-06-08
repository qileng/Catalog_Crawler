# A web crawler for UCSD general catalog
import scrapy
from scrapy.spiders import CrawlSpider, Rule
from scrapy.linkextractor import LinkExtractor

class CatalogCrawler(CrawlSpider):
    name = "CatalogCrawler"
    allowed_domains = ["www.ucsd.edu"]
    start_urls = ['http://www.ucsd.edu/catalog/courses/CSE.html']

    # Parsing rules
    rules = [Rule(LinkExtractor(allow = (), restrict_css = '.course-name', ), callback="parse_item", follow = True),]

    def parse_item(self, response):
        print('Processing..' + response.url)
        #print('Course name is: ' + response.)
