// A fixed-sized string filter which can be used to maintain fixed-sized
// continuous data. This helps to find a certain continuous pattern
// in a larger set of data.
// Internally use a std::string as a queue.
//
// Author: Qihao Leng
// Date: June.12, 2018

#ifndef FILTER_H
#define FILTER_H
#include "filter.h"
#endif

// Size is the size of the filter;
// key is the key to match.
// Data is initialized to empty.
filter::filter(int size, std::string key) : size(size), key(key) {
    data = std::string();
}

// Append parameter to the end while pop the first character to
// maintain internal queue's size.
// Return 1 if data matches key; 0 otherwise.
int filter::push(char c) {
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

std::string filter::getKey() {
    return this->key;
}

std::string filter::getData() {
    return this->data;
}

int filter::getSize() {
    return this->size;
}
