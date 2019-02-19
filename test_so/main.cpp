#include <iostream>
#include <dlfcn.h>

int main() {
    void *handle = dlopen("/home/user/CLionProjects/test_so/libstupid_sort.so", RTLD_LAZY);
    void (*test)() = (void(*)())dlsym(handle,"HWD");//переменная которая указывается на функцию с такой сигнатурой
    test();
    void (*test2)() = (void(*)())dlsym(handle,"DICK");//переменная которая указывается на функцию с такой сигнатурой
    test2();
    return 0;
}