#include "Bignum.h"

int main()
{
    Bignum a,b,c;
    std::cin >> a;
    // std::cin >> b;

    if (a.compare(100))
    {
        std::cout << "1" << std::endl;
    }
    else
    {
        std::cout << "0" << std::endl;
    }
    

    std::cin.get();
    std::cin.get();
    return 0;
}