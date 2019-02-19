#ifndef TESTS_THREADSAVELIST_HPP
#define TESTS_THREADSAVELIST_HPP


#include <list>
#include <mutex>

class ThreadSafeList {
private:
    std::list<int> l;
    mutable std::mutex m;
public:
    void push(int);
    void pop();
    unsigned long len() { return l.size();}
};

#endif //TESTS_THREADSAVELIST_HPP
