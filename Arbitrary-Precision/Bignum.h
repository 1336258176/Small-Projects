#ifndef BIGNUM_H
#define BIGNUM_H // define保护

#include <iostream>
#include <vector>
#include <string>

class Bignum
{

private:
    std::vector<int> num; // 储存数字
    // bool flag;              //判断正负，真为正，假为负

public:
    Bignum() {}
    ~Bignum() {}

    // 比较大小：大于等于返回true，否则返回false
    bool compare(const long long t); // 高精与低精间比较大小
    bool compare(const Bignum &t);   // 高精度间比较大小

    Bignum operator=(const std::string t); // 字符串赋值
    void operator=(const long long t);     // 低精赋值
    void operator=(const Bignum &t);       // 高精赋值

    friend std::istream &operator>>(std::istream &in, Bignum &t);  // 重载输入
    friend std::ostream &operator<<(std::ostream &out, Bignum &t); // 重载输出

    Bignum operator+(const long long t); // 高精加低精
    Bignum operator+(Bignum &t);         // 高精加高精

    Bignum operator-(const long long t); // 高精减低精
    Bignum operator-(const Bignum &t);   // 高精减高精

    Bignum operator*(const long long t); // 高精乘低精
    Bignum operator*(const Bignum &t);   // 高精乘高精

    Bignum operator/(const long long t); // 高精除以低精
    Bignum operator/(const Bignum &t);   // 高精除以高精  ????

    Bignum operator%(const long long t); // 高精取模低精
    Bignum operator%(const Bignum &t);   // 高精取模高精  ????

    bool operator>(const Bignum &t);
    bool operator<(const Bignum &t);
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

Bignum Bignum::operator/(const long long t)
{
    int count = this->num.size();
    int r[count + 1] = {0}; // 各位置上的余数
    int m[count + 1] = {0}; // 用于计算各位置上的商

    // 按照从高位到低位的顺序，逐位相除。在除到第i位时，该位在接受了来自第i+1位的余数后与除数相除
    for (int i = count - 1; i >= 0; i--)
    {
        m[i] = this->num[i];
        m[i] += r[i + 1] * 10;
        r[i] = m[i] % t;
        this->num[i] = m[i] / t;
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
    Bignum n;
    Bignum re;
    int x = 0;
    int l1 = this->num.size();
    int l2 = t.num.size();

    for (int i = l1 - l2 - 1; i < l1; i++)
    {
        n.num.push_back(this->num[i]);
    }

    int j = l1 - l2 - 1;
    while (j >= 0)
    {
        do
        {
            n = n - t;
            x++;
        } while (n < t);

        if (x > 9)
        {
            std::string s = std::to_string(x);
            x = 0;
            for (int i = 0; i < s.size(); i++)
            {
                re.num.push_back(s[i]);
            }
        }else
        {
            re.num.push_back(x);
            x = 0;
        }

        if (j < l1 - l2 - 1)
        {
            do
            {
                Bignum tem;
                tem = n;
                n.num.clear();
                n.num.push_back(this->num[j]);
                for (int i = 0; i < tem.num.size(); i++)
                {
                    n.num.push_back(tem.num[i]);
                }
            } while (!n.compare(t));
        }

        j--;
    }

    Bignum q;
    q = re;
    re.num.clear();
    for (int i = q.num.size() - 1; i >= 0; i--)
    {
        re.num.push_back(q.num[i]);
    }

    return re;
}

Bignum Bignum::operator%(const long long t)
{
    int count = this->num.size();
    int r[count + 1] = {0}; // 各位置上的余数
    int m[count + 1] = {0}; // 用于计算各位置上的商
    Bignum p;

    for (int i = count - 1; i >= 0; i--)
    {
        m[i] = this->num[i];
        m[i] += r[i + 1] * 10;
        r[i] = m[i] % t;
        this->num[i] = m[i] / t;
    }

    p.num.push_back(r[0]);
    return p;
}

bool Bignum::compare(const long long t)
{
    Bignum m;
    m = t;
    return this->compare(m);
}

bool Bignum::compare(const Bignum &t)
{
    // 位数比较
    if (this->num.size() < t.num.size())
    {
        return false;
    }
    else if (this->num.size() > t.num.size())
    {
        return true;
    }
    // 逐位比较
    else
    {
        int i = this->num.size() - 1;
        while (i >= 0)
        {
            if (this->num[i] < t.num[i])
            {
                return false;
            }
            else if (this->num[i] > t.num[i])
            {
                return true;
            }
            else
            {
                i--;
            }
        }
        return true;
    }
}

bool Bignum::operator>(const Bignum &t)
{
    if (this->compare(t))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Bignum::operator<(const Bignum &t)
{
    if (this->compare(t))
    {
        return false;
    }
    else
    {
        return true;
    }
}

#endif