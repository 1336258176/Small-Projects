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

    Bignum operator+ (Bignum &t);

    Bignum operator- (const Bignum &t);
};

Bignum Bignum::operator=(const std::string t)
{
    this->num.clear();
    
    //倒装——从低位到高位压入vector
    for (int i = t.length() - 1; i >= 0; i--)
    {
        //数字和与其对应的ASCII码转换——(num + 48 = ASCII) 
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
    //注意逆序输出
    for (int i = t.num.size() - 1; i >= 0; i--)
    {
        out << t.num[i];
    }
    return out;
}

Bignum Bignum::operator+ (Bignum &t)
{
    //取最大位数
    int MAX = this->num.size() > t.num.size() ? this->num.size() : t.num.size();

    //用0补位
    if(MAX == this->num.size())
    {
        for(int i = 1; i <= MAX-t.num.size(); i++)
        {
            t.num.push_back(0);
        }
    }else
    {
        for(int i = 1; i <= MAX-this->num.size(); i++)
        {
            this->num.push_back(0);
        }
    }

    //构造返回函数
    Bignum a;
    for(int i = 0; i < MAX; i++)
    {
        a.num.push_back(this->num[i] + t.num[i]);
    }

    //加法计算
    for(int i = 0; i < MAX; i++)
    {
        if(a.num[i] >= 10)
        {
            //判断最高位是否需要进位
            if(i == MAX-1)
            {
                a.num.push_back(a.num[i] / 10);
                a.num[i] = a.num[i] % 10;
            }else
            {
                a.num[i+1] += a.num[i] / 10;
                a.num[i] = a.num[i] % 10;
            }
        }
    }
    return a;
}