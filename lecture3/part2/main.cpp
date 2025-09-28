#include <iostream>
using namespace std;

class Material
{
public:
    Material()
    {
        cout << "Material Default Constructor!" << endl;
    }
    void print()
    {
        cout << "This is a Material object!" << endl;
        count_++;
    }
    ~Material()
    {
        cout << "Material Destructor! It has been read " << count_ << " times!" << endl;
    }

private:
    int count_ = 0;
};

int main()
{
    cout << "--- 构造函数 ---" << endl;
    Material m;

    cout << "\n--- print函数 ---" << endl;
    m.print();

    cout << "\n--- 自动进行析构函数 ---" << endl;
    return 0;
}