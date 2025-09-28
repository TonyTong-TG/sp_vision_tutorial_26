#include <iostream>
using namespace std;

class Material
{
    public:
    Material(){
        cout << "Material Default Constructor!" << endl;
    }
    void print(){
        cout << "This is a Material object!" << endl;
    }
    ~Material(){
        cout << "Material Destructor!" << endl;
    }
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