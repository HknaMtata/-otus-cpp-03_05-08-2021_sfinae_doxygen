#include <iostream>
#include <vector>
#include <list>
#include <array>
#include "print_ip.h"

int main(int , char**)
{
    try {
        print<char>(-1);
        print<short>(0);
        print<int>(2130706433);
        print<long>(8875824491850138409);
        print("trololo");

        std::vector<int> vv{10,11,12,13,14};
        print(vv);

        std::list<long> ll{2130706,2135436,25635436,34343434,23234356};
        print(ll);

        int integer = 134556;
        const int cinteger = 567488;
        print(integer);
        // print(&integer); // compile error
        print(cinteger);
        print(std::move(978));

        std::string str = "std::string";
        const std::string cstr = "const std::string";
        std::string mstr = "moved std::string";
        print(str);
        print(cstr);
        print(std::move(mstr));

    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        return 1;
    }
    return 0;
}