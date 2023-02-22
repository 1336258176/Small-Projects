#include "Bignum.h"

int main()
{
    Bignum a, b, c;
    std::cin >> a;
    std::cin >> b;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    // c="0100";
    c = a - b;
    std::cout << c << std::endl;

    std::cin.get();
    std::cin.get();
    return 0;
}