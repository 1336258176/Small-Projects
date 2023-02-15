#include"Bignum.h"


Bignum Bignum::operator= (const std::string t)
{
    for(int i = t.length()-1; i >= 0; i--)
    {
        this->num.push_back(t[i] - 48);
    }
    return *this;
}

void Bignum::operator= (const Bignum &t)
{
    this->num = t.num;
}

std::istream &operator>> (std::istream &in, Bignum &t)
{
    std::string m;
    in >> m;
    t = m;
    return in;
}

std::ostream &operator<< (std::ostream &out, const Bignum &t)
{
    for(int i = t.num.size()-1; i >= 0; i--)
    {
        out << t.num[i];
    }
    return out;
}