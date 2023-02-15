#include <iostream>
#include <vector>
#include <string>

class Bignum
{

private:
    std::vector<int> num;

public:
    Bignum() {}
    ~Bignum() {}

    Bignum operator=(const std::string t);
    void operator=(const Bignum &t);

    friend std::istream &operator>>(std::istream &in, Bignum &t);
    friend std::ostream &operator<<(std::ostream &out, const Bignum &t);

    Bignum operator+ (const Bignum &t);

    Bignum operator- (const Bignum &t);
};

Bignum Bignum::operator=(const std::string t)
{
    this->num.clear();
    for (int i = t.length() - 1; i >= 0; i--)
    {
        this->num.push_back(t[i] - 48);
    }
    return *this;
}

void Bignum::operator=(const Bignum &t)
{
    this->num = t.num;
}

std::istream &operator>>(std::istream &in, Bignum &t)
{
    std::string m;
    in >> m;
    t = m;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Bignum &t)
{
    for (int i = t.num.size() - 1; i >= 0; i--)
    {
        out << t.num[i];
    }
    return out;
}

Bignum Bignum::operator+ (const Bignum &t)
{

}