// io_util.cpp
// Utility functions for file io.
//
// Author: Qihao Leng
// Date: June 12, 2018

#ifndef IO_UTIL_H
#define IO_UTIL_H
#include "io_util.h"
#endif

std::vector<std::string> readCourses(std::filebuf *input) {
    std::vector<std::string> result;

    input->open("./name", std::ios_base::in);

    while (input->sgetc() != EOF) {
        std::string temp = "";
        std::cout << "outer\n";

        while (input->sgetc() != '\n') {
            std::cout << "inner\n";
            temp.push_back(input->sbumpc());
        }
        result.push_back(temp);
        input->sbumpc();
    }

    input->close();

    return result;
}

void writeResult(std::vector<std::string> result, std::filebuf *output) {

    for (auto i = result.begin(); i != result.end(); i++) {
        for (auto j = (*i).begin(); j != (*i).end(); j++) {
            output->sputc(*j);
        }
        output->sputn("\n--------\n", 10);
    }
}
