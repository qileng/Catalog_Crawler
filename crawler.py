# Web crawler built for crawling course info from UCSD General Catalog
#
# Author: Qihao Leng
# Date: June.8, 2018
# Contact: qileng@ucsd.edu
#
#

from httpGet import HTTPGet
from parse import trimHeader, trimFooter, filterDescription, filterName, stripName

def main():
	data = HTTPGet().split('\n')
	data = trimHeader(data)
	data = trimFooter(data)
	des = filterDescription(data)
	nam = filterName(data)
	nam = stripName(nam)

	name = open("./name", mode = 'w', encoding = 'utf8')
	descriptions = open("./descriptions", mode = 'w', encoding = 'utf8')

	for entry in des:
		descriptions.write(entry + '\n')
	
	for entry in nam:
		name.write(entry + '\n')


if __name__ == "__main__":
	main()

