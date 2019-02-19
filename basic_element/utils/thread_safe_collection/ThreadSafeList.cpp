#include <iostream>
#include <iterator>

#include "ThreadSafeList.hpp"

/**
 * @brief push item into list
 * @param elem - item that is added to the list
 * object lock_guard locks and frees resource
 */
void ThreadSafeList::push(int elem)
{
    std::lock_guard<std::mutex> lock(m);
    l.push_back(elem);
}

/**
 * @brief pop item from list
 * object lock_guard locks and frees resource
 */
void ThreadSafeList::pop()
{
    std::lock_guard<std::mutex> lock(m);
    l.pop_back();
}