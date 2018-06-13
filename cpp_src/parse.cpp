// parse.cpp
// Utility functions for parsing data.
//
// Author: Qihao Leng
// Date: June.12, 2018

#ifndef PARSE_H
#define PARSE_H
#include "parse.h"
#endif

std::vector<std::string>
parseRequirements(std::string firstKey, std::string secondKey,
                  std::filebuf *input, std::vector<std::string> name) {
    // Result
    std::vector<std::string> result;
    std::string buf;

    filter *begin = new filter(firstKey.size(), firstKey);
    filter *end = new filter(secondKey.size(), secondKey);

    // Controls searching span stepping.
    int flag = 1;
    for (auto it = name.begin(); it != name.end(); it++) {
        std::cout << "\n" << "Fetching " << *it;

        if (flag) {
            while (input->sgetc() != EOF && !begin->push(input->sbumpc()));
            // while (input->sgetc() != EOF && (buf.push_back(input->sgetc()),!end->push(input->sdumpc())));
            // Expand into loop body for readability
            while (input->sgetc() != EOF ) {
                // Put content into a buffer to avoid tampering with seek pos.
                buf.push_back(input->sgetc());
                if (end->push(input->sbumpc())) {
                    // cout << buf << "\n";
                    break;
                }
            }
            // cout << int(input->pubseekoff(0, ios_base::cur, ios_base::in)) << "\n";
        }
        // Search in buffer
        // cout << int(buf.find("cse3")) << "\n";
        // cout << int(buf.find((*it).c_str())) << "\n";
        // cout << int(buf.find((*it).data())) << "\n";
        if (buf.find(*it) == std::string::npos) {
            std::cout << "No description for " << *it;
            std::cout << "In " << buf;
            result.push_back("None\n");
            // Pause seeking while stepping to next course.
            flag = 0;
        } else if (buf.find("course-descriptions") == -1) {
            // No description block,
            // probably means invalid seeking result due to poor html coding.
            std::cout << "Unexpected html pattern @ " << *it;
            it--;
            flag = 1;
        } else {
            // Continue seeking, save buffer.
            result.push_back(buf + "\n");
            std::cout << "Fetched " << buf.substr(0, 6) << "\n";
            if ((*it).find("222") > -1 ) {
                std::cout << "Detailed" << buf;
            }
            buf.clear();
            flag = 1;
        }
    }

    delete begin;
    delete end;

    return result;
}
