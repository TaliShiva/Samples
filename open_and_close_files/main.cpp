#include <iostream>
#include <fstream>
#include "human.hpp"
int main() {

    human *pidor = new human("Вася","Пупкин");
    std::string cock = pidor->get_full_name();
    std::ofstream mycock;
    mycock.open("example_cock.txt");
    mycock << "FUCK YOU!\n";
    mycock << cock << std::endl;
    mycock << "FUCK YOU!\n";
    mycock.close();
    delete pidor;
    return 0;
}