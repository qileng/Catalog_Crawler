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

using namespace std;

// A fixed-sized string filter which can be used to maintain fixed-sized
// continuous data. This helps to find a certain continuous pattern
// in a larger set of data.
// Internally use a std::string as a queue.
class filter {
    private:
        std::string data;
        std::string key;
        int size;

    public:
        // Size is the size of the filter;
        // key is the key to match.
        // Data is initialized to empty.
        filter(int size, std::string key) : size(size), key(key) {
            data = std::string();
        }

        // Append parameter to the end while pop the first character to
        // maintain internal queue's size.
        // Return 1 if data matches key; 0 otherwise.
        int push(char c) {
            if (data.size() < this->size) {
                data.push_back(c);
                return 0;
            } else {
                data.erase(data.begin());
                data.push_back(c);
                if (data != key) {
                    return 0;
                }
            }

            return 1;
        }

        std::string getKey() {
            return this->key;
        }

        std::string getData() {
            return this->data;
        }

        int getSize() {
            return this->size;
        }
};


int main(int argc, char** argv) {

    ifstream is;
    ofstream os;

    filebuf *input = is.rdbuf();
    filebuf *output = os.rdbuf();

    input->open("./raw.html", ios_base::in);
    output->open("./requirements", ios_base::out);

    // Scan for <h2>Courses</h2> and <!-- #EndEditable -->
    string firstKey = "<p class=\"course-descriptions\">";
    string secondKey = "</p>";
    filter *begin = new filter(firstKey.size(), firstKey);
    filter *end = new filter(secondKey.size(), secondKey);

    // Result
    vector<string> result;
    string description;

    // read from raw
    while (input->sbumpc() != EOF) {
        // TODO: Parse input
        // output->sputc(input->sbumpc());

        // Scan simultaneously.
        if (begin == NULL || begin->push(input->sgetc())) {
            // First Key matched
            delete begin;
            begin = NULL;
            description.push_back(input->sgetc());
            if (end->push(input->sgetc())) {
                // Second Key matched
                delete end;
                result.push_back(description);
                begin = new filter(firstKey.size(), firstKey);
                end = new filter(secondKey.size(), secondKey);
                description = "";
            }
        }
    }

    for (auto i = result.begin(); i != result.end(); i++) {
        for (auto j = (*i).begin(); j != (*i).end(); j++) {
            output->sputc(*j);
        }
        output->sputn("\n////////\n", 10);
    }

    input->close();
    output->close();
    return 0;
}
