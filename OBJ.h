#include <string>

class OBJ
{
private:
    std::string name;
    int val;
public:
    OBJ(std::string name);
    ~OBJ();
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

OBJ::OBJ(std::string name)
{
    this->name = name;
    this->val = 0;
}

OBJ::~OBJ()
{
}

void OBJ::ChangeVal(int val){
    this->val = val;
}