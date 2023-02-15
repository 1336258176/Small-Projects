#include<iostream>
#include<vector>
#include<string>

class Bignum
{

private:
    std::vector<int> num;

public:
    Bignum(){}
    ~Bignum(){}

    Bignum operator= (const std::string t);
    void operator= (const Bignum &t);
    friend std::istream &operator>> (std::istream &in, Bignum &t);
    friend std::ostream &operator<< (std::ostream &out, const Bignum &t);

};