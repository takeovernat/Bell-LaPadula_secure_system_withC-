#include <string>
#include <iostream>
#include <map>
#include "SUB.h"
#include "OBJ.h"
using namespace std;


class RefMon
{
private:
    map<SUB*, int> SubjectsWithAccessList;
    map<OBJ*, int> ObjectsWithAccessList;
public:
    RefMon(/* args */);
    ~RefMon();
    void AddSub(string name, int sec);
    void AddObj(string name, int sec);
    SUB* FindSubByName(string name);
    OBJ* FindObjByName(string name);
    int FindSubAccessByName(string name);
    int FindObjAccessByName(string name);
    void read(string subname, string objname);
    void write(string subname, string objname, int val);
    void status();
    void finalstatus();
    
};

RefMon::RefMon(/* args */)
{
}

RefMon::~RefMon()
{
    for (auto it = SubjectsWithAccessList.begin(); it!=SubjectsWithAccessList.end(); it++){
        delete(it->first);
    }


}

void RefMon::AddSub(string name, int sec){
    SUB* sub = new SUB(name);
    SubjectsWithAccessList.insert({sub, sec});
}
void RefMon::AddObj(string name, int sec){
    OBJ* obj = new OBJ(name);
    ObjectsWithAccessList.insert({obj, sec});
}

SUB* RefMon::FindSubByName(string name){
//null too
    for (auto it = SubjectsWithAccessList.begin(); it!=SubjectsWithAccessList.end(); it++){
        if (it->first->GetName() == name){
            return it->first;
        }
    }
    return nullptr;
}
OBJ* RefMon::FindObjByName(string name){
    for (auto it = ObjectsWithAccessList.begin(); it!=ObjectsWithAccessList.end(); it++){
        if (it->first->GetName() == name){
            return it->first;
        }
    }
    return nullptr;
}

int RefMon::FindSubAccessByName(string name){
    int val;
    for (auto it = SubjectsWithAccessList.begin(); it!=SubjectsWithAccessList.end(); it++){
        if(it->first->GetName() == name){
            val = it->second;
            break;
        }
    }
    return val;   
}
int RefMon::FindObjAccessByName(string name){
      int access;
      for (auto it = ObjectsWithAccessList.begin(); it!=ObjectsWithAccessList.end(); it++){
        if(it->first->GetName() == name){
            access = it->second;
        }
    }

return access;
}

void RefMon::read(string subname, string objname){
    if(FindSubByName(subname) == nullptr || FindObjByName(objname) == nullptr)
        {
            cout << "Bad Instruction: read "<< subname << " "<< objname << endl;
        }
    else{
        if(FindSubAccessByName(subname) >= FindObjAccessByName(objname)){
            cout << "Access granted: " << subname << " reads " << objname << endl;
            OBJ *obj = FindObjByName(objname);
            int val = obj->GetVal();
            SUB *sub = FindSubByName(subname);
            sub->SetVal(val);
        }
        else{
            cout << "Access denied: read " << subname << " " << objname << endl;

        }
    }
}
void RefMon::write(string subname, string objname, int val){
    //can write up but not down
       if(FindSubByName(subname) == nullptr || FindObjByName(objname) == nullptr)
        {
            cout << "Bad Instruction: write " << subname << " " << objname << " " << val << endl;
        }
    else{
        if(FindSubAccessByName(subname) <= FindObjAccessByName(objname)){
            cout << "Access granted " << subname << " writes value " << val << " to " << objname << endl;
            OBJ *obj = FindObjByName(objname);
            obj->SetVal(val);
        }
        else{
            cout << "Access denied: write " << subname << " " << objname << " "<< val <<endl;
        }
    }
}
void RefMon::status(){
    string val;
    cout << "+---------current state----------+\n";
    cout << "|-subject--|--level--|--value---|\n";
     for (auto it = SubjectsWithAccessList.begin(); it!=SubjectsWithAccessList.end(); it++){
       
       if(it->second == 1){val = "LOW";}
       else if(it->second == 2){val = "MEDIUM";}
       else if(it->second == 3){val = "HIGH";}
       cout << "|" <<it->first->GetName() << "\t" << val << "\t" << it->first->GetVal() << "\t" << endl;
    }
    cout << "|-object---|--level--|--value---|\n";
    for (auto it = ObjectsWithAccessList.begin(); it!=ObjectsWithAccessList.end(); it++){
       if(it->second == 1){val = "LOW";}
       else if(it->second == 2){val = "MEDIUM";}
       else if(it->second == 3){val = "HIGH";}
       cout << "|" << it->first->GetName() << "\t" << val << "\t" << it->first->GetVal() << "\t" << endl;
    }
     cout << "+--------------------------------+\n";

}

void RefMon::finalstatus(){
    string val;
    cout << "+---------Final state----------+\n";
    cout << "|-subject--|--level--|--value---|\n";
     for (auto it = SubjectsWithAccessList.begin(); it!=SubjectsWithAccessList.end(); it++){

       if(it->second == 1){val = "LOW";}
       else if(it->second == 2){val = "MEDIUM";}
       else if(it->second == 3){val = "HIGH";}
       cout << "|" <<it->first->GetName() << "\t" << val << "\t" << it->first->GetVal() << "\t" << endl;
    }
    cout << "|-object---|--level--|--value---|\n";
    for (auto it = ObjectsWithAccessList.begin(); it!=ObjectsWithAccessList.end(); it++){
       if(it->second == 1){val = "LOW";}
       else if(it->second == 2){val = "MEDIUM";}
       else if(it->second == 3){val = "HIGH";}
       cout << "|" << it->first->GetName() << "\t" << val << "\t" << it->first->GetVal() <<  "\t" << endl;
    }
     cout << "+--------------------------------+\n";

}


//////////////////////////////////


