#ifndef BIGNUM_H
#define BIGNUM_H // define保护

#include <iostream>
#include <vector>
#include <string>

class Bignum
{

private:
    std::vector<int> num; // 储存数字

    /**
     * To do
     * 添加正负判断
     */
    // bool flag;

public:
    Bignum() {}
    ~Bignum() {}

    inline Bignum operator=(const std::string t);
    inline void operator=(const Bignum &t);
    inline void operator=(const long long t);

    friend std::istream &operator>>(std::istream &in, Bignum &t);
    friend std::ostream &operator<<(std::ostream &out, Bignum &t);

    inline Bignum operator+(const long long t);
    inline Bignum operator+(Bignum &t);

    inline Bignum operator-(const long long t);
    inline Bignum operator-(const Bignum &t);

    inline Bignum operator*(const long long t);
    inline Bignum operator*(const Bignum &t);

    inline Bignum operator/(const long long t);
    inline Bignum operator/(const Bignum &t);
};

Bignum Bignum::operator=(const std::string t)
{
    this->num.clear();

    // 倒装——从低位到高位压入vector
    for (int i = t.length() - 1; i >= 0; i--)
    {
        // 数字和与其对应的ASCII码转换——(num + 48 = ASCII)
        this->num.push_back(t[i] - 48);
    }
    return *this;
}

void Bignum::operator=(const Bignum &t)
{
    this->num.clear();
    this->num = t.num;
}

void Bignum::operator=(const long long t)
{
    *this = std::to_string(t);
}

std::istream &operator>>(std::istream &in, Bignum &t)
{
    std::string m;
    in >> m;
    t = m;
    return in;
}

std::ostream &operator<<(std::ostream &out, Bignum &t)
{
    // 注意逆序输出
    for (int i = t.num.size() - 1; i >= 0; i--)
    {
        out << t.num[i];
    }
    return out;
}

Bignum Bignum::operator+(const long long t)
{
    Bignum a;
    a = std::to_string(t);
    return (a + *this);
}

Bignum Bignum::operator+(Bignum &t)
{
    // 取最大位数
    int MAX = this->num.size() > t.num.size() ? this->num.size() : t.num.size();

    // 用0补位
    if (MAX == this->num.size())
    {
        for (int i = 1; i <= MAX - t.num.size(); i++)
        {
            t.num.push_back(0);
        }
    }
    else
    {
        for (int i = 1; i <= MAX - this->num.size(); i++)
        {
            this->num.push_back(0);
        }
    }

    // 构造返回函数
    Bignum a;
    for (int i = 0; i < MAX; i++)
    {
        a.num.push_back(this->num[i] + t.num[i]);
    }

    // 加法计算
    for (int i = 0; i < MAX; i++)
    {
        if (a.num[i] >= 10)
        {
            // 判断最高位是否需要进位
            if (i == MAX - 1)
            {
                a.num.push_back(a.num[i] / 10);
                a.num[i] = a.num[i] % 10;
            }
            else
            {
                a.num[i + 1] += a.num[i] / 10;
                a.num[i] = a.num[i] % 10;
            }
        }
    }
    return a;
}

Bignum Bignum::operator*(const long long t)
{
    Bignum a;
    for (int i = 0; i < this->num.size(); i++)
    {
        a.num.push_back(t * this->num[i]);
    }

    // 动态进位
    for (int i = 0; i < a.num.size(); i++)
    {
        if (a.num[i] / 10 > 0)
        {
            if (i == a.num.size() - 1)
            {
                a.num.push_back(a.num[i] / 10);
                a.num[i] = a.num[i] % 10;
            }
            else
            {
                a.num[i + 1] += a.num[i] / 10;
                a.num[i] = a.num[i] % 10;
            }
        }
    }

    return a;
}

Bignum Bignum::operator*(const Bignum &t)
{
    Bignum a;
    for (int i = 0; i < this->num.size() + t.num.size(); i++)
    {
        a.num.push_back(0);
    }

    for (int i = 0; i < this->num.size(); i++)
    {
        for (int j = 0; j < t.num.size(); j++)
        {
            a.num[i + j] += this->num[i] * t.num[j];
        }
    }

    for (int i = 0; i < a.num.size(); i++)
    {
        if (a.num[i] > 9)
        {
            a.num[i + 1] += a.num[i] / 10;
            a.num[i] %= 10;
        }
    }

    // 除去前面的0
    while (a.num.size() > 0 && a.num[a.num.size() - 1] == 0)
    {
        a.num.pop_back();
    }

    return a;
}

Bignum Bignum::operator-(const long long t)
{
    Bignum m;
    m = t;
    *this = *this - m;
    return *this;
}

Bignum Bignum::operator-(const Bignum &t)
{
    for (int i = 0; i < t.num.size(); i++)
    {
        // 处理借位
        if (this->num[i] > t.num[i])
        {
            this->num[i] -= t.num[i];
        }
        else
        {
            int a = i;
            while (this->num[a + 1] == 0)
            {
                this->num[a + 1] = 9;
                a++;
            }
            this->num[a + 1] -= 1;
            this->num[i] = this->num[i] + 10 - t.num[i];
        }
    }

    // 清除前面的0
    while (this->num.size() > 0 && this->num[this->num.size() - 1] == 0)
    {
        this->num.pop_back();
    }

    return *this;
}

Bignum Bignum::operator/(const Bignum &t)
{
    
}

#endif