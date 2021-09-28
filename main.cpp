#include <iostream>
#include <vector>
#include <list>
#include <array>
#include "print_ip.h"

int main(int , char**)
{
    try {
        // std::cout << print<char>(-1) << std::endl;
        // std::cout << print<short>(0) << std::endl;
        // std::cout << print<int>(2130706433) << std::endl;
        // std::cout << print<long>(8875824491850138409) << std::endl;
        int integer = 134556;
        int* pinteger = &integer;
        const int cinteger = 567488;
        const int* cpinteger = &cinteger;
        std::cout << print(integer) << std::endl;
        std::cout << print(pinteger) << std::endl;
        std::cout << print(cinteger) << std::endl;
        std::cout << print(cpinteger) << std::endl;
        std::cout << print(978) << std::endl;
        std::cout << print(std::move(978)) << std::endl;
        
        short short_integer{6};
        std::cout << print(short_integer) << std::endl;

        long long_integer{298323};
        std::cout << print(long_integer) << std::endl;
    
        // char char_integer{-1};
        // std::cout << print(char_integer) << std::endl;

        std::string str = "trololo";
        const std::string cstr = "trololo";
        std::string tmpstr = "trololo";
        std::cout << print(str) << std::endl;
        std::cout << print(cstr) << std::endl;
        std::cout << print(std::move(tmpstr)) << std::endl;
        // std::cout << print("trololo") << std::endl;

        std::vector<int> vv{10,11,12,13,14};
        std::cout << print(vv) << std::endl;

        std::list<short> ll{5,6,7,8,9};
        std::cout << print(ll) << std::endl;

        std::array<int, 1> aa{576};
        std::cout << print(aa) << std::endl;

        // std::cout << print<std::list<short>>({1, 4, 8, 10, 3, 6}) << std::endl;
        // - Опционально. Печать адреса как std::tuple
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        return 1;
    }
    return 0;
}