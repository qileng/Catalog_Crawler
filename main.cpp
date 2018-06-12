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

vector<string> readCourses(filebuf *input) {
    vector<string> result;

    input->open("./name", ios_base::in);

    while (input->sgetc() != EOF) {
        string temp = "";
        cout << "outer\n";

        while (input->sgetc() != '\n') {
            cout << "inner\n";
            temp.push_back(input->sbumpc());
        }
        result.push_back(temp);
        input->sbumpc();
    }

    input->close();

    return result;
}

int main(int argc, char** argv) {

    ifstream is;
    ofstream os;

    filebuf *input = is.rdbuf();
    filebuf *output = os.rdbuf();

    // Read list of course names first.
    vector<string> name = readCourses(input);

    input->open("./content.html", ios_base::in);
    output->open("./requirements", ios_base::out);

    // Scan for <h2>Courses</h2> and <!-- #EndEditable -->
    string firstKey = "id=\"";
    string secondKey = "<a";
    filter *begin = new filter(firstKey.size(), firstKey);
    filter *end = new filter(secondKey.size(), secondKey);

    // Result
    vector<string> result;

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
    string buf;
    // Controls searching span stepping.
    int flag = 1;
    for (auto it = name.begin(); it != name.end(); it++) {
        cout << "\n" << "Fetching " << *it;

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
        if (buf.find(*it) == string::npos) {
            cout << "No description for " << *it;
            cout << "In " << buf;
            result.push_back("None\n");
            // Pause seeking while stepping to next course.
            flag = 0;
        } else if (buf.find("course-descriptions") == -1) {
            // No description block,
            // probably means invalid seeking result due to poor html coding.
            cout << "Unexpected html pattern @ " << *it;
            it--;
            flag = 1;
        } else {
            // Continue seeking, save buffer.
            result.push_back(buf + "\n");
            cout << "Fetched " << buf.substr(0, 6) << "\n";
            if ((*it).find("222") > -1 ) {
                cout << "Detailed " << buf;
            }
            buf.clear();
            flag = 1;
        }
    }

    delete begin;
    delete end;

    for (auto i = result.begin(); i != result.end(); i++) {
        for (auto j = (*i).begin(); j != (*i).end(); j++) {
            output->sputc(*j);
        }
        output->sputn("\n--------\n", 10);
    }

    input->close();
    output->close();
    return 0;
}
