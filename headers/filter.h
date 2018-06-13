// filter.h
//
// Author: Qihao Leng
// Date: June.12, 2018

#include <string>

class filter {
	private:
		std::string data;
		std::string key;
		int size;

	public:
		filter(int, std::string);

		int push(char);

		std::string getKey();
		std::string getData();
		int getSize();
};
