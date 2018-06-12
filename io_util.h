// io_util.h
//
// Author: Qihao Leng
// Date: June 12, 2018

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

std::vector<std::string> readCourses(std::filebuf*);

void writeResult(std::vector<std::string> result, std::filebuf *output);
