// parse.h
//
// Author: Qihao Leng
// Date: June.12, 2018

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifndef FILTER_H
#define FILTER_H
#include "filter.h"
#endif

std::vector<std::string> parseRequirements(std::string, std::string, 
										   std::filebuf*, 
										   std::vector<std::string>);
