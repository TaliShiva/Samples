#include <iostream>
#include <thread>
#include "gtest/gtest.h"

#include "ThreadSafeList.hpp"

typedef std::vector<std::thread> thread_vector;

/**
 * @brief push and pop to ThreadSafeList
 * @param list - ThreadSaveList's object
 * @param x - item that is push to the list
 */
void pushAndPop(ThreadSafeList & list, int x)
{
    list.push(x);
    list.pop();
}

/**
 * @brief push to list
 * @param list - ThreadSafeList's object
 * @param x item that is pop from the list
 */
void push(ThreadSafeList & list, int x)
{
    list.push(x);
}

/**
 * @brief pop from list
 * @param list - ThreadSafeList's object
 */
void pop(ThreadSafeList & list)
{
    list.pop();
}

/**
 * @brief test checks thread safety of pop method
 * @param t - vector of threads
 * @param list - ThreadSaveList' object
 * @return length of list's list
 */
unsigned long pushTest(thread_vector & t, ThreadSafeList & list)
{
    unsigned long i = 0;
    thread_vector::iterator iter;
    for (iter = t.begin(), i = 0; iter != t.end(); iter++, i++)
    {
        *iter = std::thread(push, std::ref(list), i);
    }
    for (iter = t.begin(); iter != t.end(); iter++)
    {
        iter->join();
    }
    return list.len();
}

/**
 * @brief test checks thread safety of pop and push methods
 * @param t - vector of threads
 * @param list - ThreadSafeList's object 
 * @return length of list's list
 */
unsigned long pushAndPopTest(thread_vector & t, ThreadSafeList & list)
{
    unsigned long i = 0;
    thread_vector::iterator iter;
    for (iter = t.begin(), i = 0; iter != t.end(); iter++, i++)
    {
        *iter = std::thread(pushAndPop, std::ref(list), i);
    }
    for (iter = t.begin(); iter != t.end(); iter++)
    {
        iter->join();
    }

    return list.len();
}

/**
 * @brief test checks thread safety of pop method
 * @param t - vector of threads
 * @param list - ThreadSafeList's object
 * @return length of list's list
 */
unsigned long popTest(thread_vector & t, ThreadSafeList & list)
{
    thread_vector::iterator iter;
    for (iter = t.begin(); iter != t.end(); iter++)
    {
        *iter = std::thread(pop, std::ref(list));
    }
    for (iter = t.begin(); iter != t.end(); iter++)
    {
        iter->join();
    }
    return list.len();
}



TEST(listTests, correct_push_len)
{
    ThreadSafeList test_list;
    thread_vector test_vector(30000);

    EXPECT_EQ(30000, pushTest(test_vector, test_list));
}


TEST(listTests, correct_push_pop_len)
{
    ThreadSafeList test_list;
    thread_vector test_vector(30000);
    EXPECT_EQ(0, pushAndPopTest(test_vector, test_list));
}

TEST(listTests, correct_pop_len)
{
    ThreadSafeList test_list;
    for (unsigned long i = 0; i < 30000; i++)
        test_list.push(0);
    thread_vector test_vector(30000);
    EXPECT_EQ(0, popTest(test_vector, test_list));
}

