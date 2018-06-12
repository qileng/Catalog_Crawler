# Web crawler built for crawling course info from UCSD General Catalog
#
# Author: Qihao Leng
# Date: June.8, 2018
# Contact: qileng@ucsd.edu
#
#

import requests
from time import localtime, strftime

# Make http get request and do the logging.
def HTTPGet():
	# HTTP get request. 
	r = requests.get('http://www.ucsd.edu/catalog/courses/CSE.html')

	# Logging
	t = strftime("%H:%M:%S Local Time, %b %d %Y")
	Log = open("./log", mode= 'w', encoding = 'utf8')
	Log.write(t + '\n')
	Log.write(str(r.status_code) + '\n')
	Log.write(r.encoding + '\n')

	# Logging header from request
	headerFile = open("./header", mode= 'w', encoding = 'utf8')
	for key in r.headers:
		headerFile.write(key + " : ")
		headerFile.write(r.headers[key] + '\n')

	# Save the entire html
	#rawFile = open("./raw.html", mode='w', encoding = 'utf8')
	#rawFile.write(r.text)

	return r.text
