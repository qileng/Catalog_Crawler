# Web crawler built for crawling course info from UCSD General Catalog
#
# Author: Qihao Leng
# Date: June.8, 2018
# Contact: qileng@ucsd.edu
#
#

def trimHeader(data):
	key = "<h2>Courses</h2>"

	if key not in data:
		print("Key not found!\n")
	else:
		index = data.index(key)
		result = data[index:len(data)]
	
	return result


def trimFooter(data):
	key = "<!-- #EndEditable -->"

	if key not in data:
		print("Key not found!\n")
	else:
		index = data.index(key)
		result = data[0:index]

	return result

def filterDescription(data):
	key = "<p class=\"course-descriptions\">"
	result = []

	for entry in data:
		if key in entry:
			result.append(entry)

	return result


def filterName(data):
	key = "<a id=\""
	result = []

	for entry in data:
		if key in entry:
			result.append(entry)

	return result
