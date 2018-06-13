# Web crawler built for crawling course info from UCSD General Catalog
#
# Author: Qihao Leng
# Date: June.8, 2018
# Contact: qileng@ucsd.edu
#
#

import requests
from time import localtime, strftime

LOG_PATH = "../log"

# Make http get request and do the logging.
def HTTPGet():
	# HTTP get request. 
	r = requests.get('http://www.ucsd.edu/catalog/courses/CSE.html')

	# Logging
	t = strftime("%H:%M:%S Local Time, %b %d %Y")
	Log = open(LOG_PATH, mode= 'w', encoding = 'utf8')
	Log.write(t + '\n')
	Log.write(str(r.status_code) + '\n')
	Log.write(r.encoding + '\n')

	# Logging header from request
	Log.write("HTTP GET REQUEST: --------------------------------------\n")
	for key in r.headers:
		Log.write(key + " : ")
		Log.write(r.headers[key] + '\n')

	# Save the entire html
	#rawFile = open("./raw.html", mode='w', encoding = 'utf8')
	#rawFile.write(r.text)

	return r.text
