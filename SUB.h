
#include <string>
#include <iostream>

class SUB
{
private:
    std::string name;
    int val;

public:
    SUB(std::string name);
    ~SUB();
    void ChangeVal(int val);
    int GetVal() const{
        return this->val;
    }
    void SetVal(int val){
        this->val = val;
    }
    std::string GetName() const{
        return this->name;
    }
};


SUB::SUB(std::string name)
{
    this->name = name;
    this->val = 0;
}

SUB::~SUB()
{
}

void SUB::ChangeVal(int val){
    this->val = val;
}


