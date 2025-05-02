#pragma once
#include <vector>
#include "algorithm"

template<typename T, typename COMP>
class PQueue {
public:
    PQueue(COMP* sort_key) : sort_key(sort_key), contents({}), sorted(false) { }
    
    void sort() { 
        std::sort(contents.begin(), contents.end(), sort_key); 
        sorted = true;
    }

    void push(const T& o) {
        contents.push_back(o);
        sorted = false;
    }

    T pop() {
        if (!sorted) {
            sort();
        }
        
        T result = contents.back();
        contents.pop_back();
        return result;
    }

    int size() {return contents.size();}
    std::vector<T> get_contents() {return contents;}

private:
    std::vector<T> contents;
    COMP* sort_key;
    bool sorted;
};