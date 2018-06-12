// C++ program used to genearte requirments.
//
// Author: Qihao Leng
// Date: June.11, 2018
// Contact: qileng@ucsd.edu
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <typeinfo>


#ifndef FILTER_H
#define FILTER_H
#include "filter.h"
#endif

#ifndef PARSE_H
#define PARSE_H
#include "parse.h"
#endif

#ifndef IO_UTIL_H
#define IO_UTIL_H
#include "io_util.h"
#endif

using namespace std;

int main(int argc, char** argv) {

    ifstream is;
    ofstream os;

    filebuf *input = is.rdbuf();
    filebuf *output = os.rdbuf();

    // Read list of course names first.
    vector<string> name = readCourses(input);

    input->open("./content.html", ios_base::in);
    output->open("./requirements", ios_base::out);

    string firstKey = "id=\"";
    string secondKey = "<a";

    // read from raw
    // while (input->sbumpc() != EOF) {
    //     // TODO: Parse input
    //     // output->sputc(input->sbumpc());
    //
    //     // Scan simultaneously.
    //     if (begin == NULL || begin->push(input->sgetc())) {
    //         // First Key matched
    //         delete begin;
    //         begin = NULL;
    //         description.push_back(input->sgetc());
    //         if (end->push(input->sgetc())) {
    //             // Second Key matched
    //             delete end;
    //             result.push_back(description);
    //             begin = new filter(firstKey.size(), firstKey);
    //             end = new filter(secondKey.size(), secondKey);
    //             description = "";
    //         }
    //     }
    // }

    // Original approach too ugly.
    // First scan for key matching pair,
    // then pause & search inbetween the pair.
    vector<string> req = parseRequirements(firstKey, secondKey, input, name);
    writeResult(req, output);

    input->close();
    output->close();
    return 0;
}
