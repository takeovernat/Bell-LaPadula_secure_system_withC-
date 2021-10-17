#include "RefMon.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;


struct Instruction{
string object;
string subject;
string Action;
int writeval;
int accesslevel;
};
string removeSpaces(string str);
void BadInstruction(vector<string> tokens);
int findAccesslevel(string ac);
vector<string> tokensVector(string line);
            
int main(int argc, char *argv[]){

//int c = linecount("write kel0004 file002 20");


if(argc != 2){
	cout << "usage: " << argv[0] << " <instructionlist>\n";
	exit(0);
	}
Instruction ins;
//ParseInstructions(argv[1]); 
RefMon Monitor = RefMon();
vector<string> Tokens;

    ifstream fin;
    fin.open(argv[1]);
    
    if (fin.is_open())
    {
	    string line;
	    while (getline(fin, line))
        {
            Tokens = tokensVector(line);
            int accesslevel;

                if( (Tokens[0] == "addsub" || Tokens[0] == "ADDSUB") ){
                    if(Tokens.size() == 3 || (Tokens.size() == 4 && Tokens[3]=="")){
			 if(Monitor.FindSubByName(Tokens[1]) != nullptr){
                            BadInstruction(Tokens);
                            continue;
                        }
		
                    ins.Action = Tokens[0];
                    ins.subject = Tokens[1];
                    accesslevel = findAccesslevel(Tokens[2]);
                    ins.accesslevel = accesslevel;
                    Monitor.AddSub(ins.subject, ins.accesslevel);
                    cout << "Subject Added: " << ins.Action << " " << ins.subject << " " << Tokens[2] << endl;
                	}
	
		}//first if
                else if((Tokens[0] == "addobj" || Tokens[0] == "ADDOBJ")){
                    if((Tokens.size() == 3)){
			//handle subjects being added again with different access level
                         ins.Action = Tokens[0];
                        ins.object = Tokens[1];
                        accesslevel = findAccesslevel(Tokens[2]);
                        ins.accesslevel = accesslevel;
                        Monitor.AddObj(ins.object, ins.accesslevel);
                        cout << "Object Added: " << ins.Action << " " << ins.object << " " << Tokens[2] << endl;

                    }
                    else{
                        BadInstruction(Tokens);
                    }
                   
                }
                else if((Tokens[0] == "status" || Tokens[0] == "STATUS") ){
                    if((Tokens.size() == 1)){
                        Monitor.status();
                    }
		   else if(Tokens.size() == 2 && Tokens[1] == "\n"){
			Monitor.status();
			}
                    else{
                        BadInstruction(Tokens);
                    }
                    
                }
                else if(Tokens[0] == "read" || Tokens[0] == "READ"){
                    if((Tokens.size() == 3)){
                        ins.Action = Tokens[0];
                        ins.subject = Tokens[1];
                        ins.object = Tokens[2];
                        Monitor.read(ins.subject, ins.object);
                    }
		   else if(Tokens.size() == 4 && Tokens[3] == "\n"){
			ins.Action = Tokens[0];
                        ins.subject = Tokens[1];
                        ins.object = Tokens[2];
                        Monitor.read(ins.subject, ins.object);
			}
                    else{
                        BadInstruction(Tokens);
                    }

                }
                else if (Tokens[0] == "write" || Tokens[0] == "WRITE"){
                    if(Tokens.size() == 4){
                        ins.Action = Tokens[0];
                        ins.subject = Tokens[1];
                        ins.object = Tokens[2];
                        try
                        {
                           ins.writeval = stoi(Tokens[3]);
                           Monitor.write(ins.subject, ins.object, ins.writeval);
                        }
                        catch(const std::exception& e)
                        {
                            cout << "Bad Instruction: ";
                            for(int i=0; i<Tokens.size(); i++){cout << Tokens[i] << " ";}
                            cout << endl;
                        }  
                    }
                    else{
                        BadInstruction(Tokens);
                    }
                    
                }
                   
            Tokens.clear();
        }//while
		Monitor.finalstatus();
    }//if
    else{
        cout << "Error. can't open file, exiting....\n";
        exit(0);
    }

    return 0;
}

int findAccesslevel(string ac){
    if(ac == "low" || ac == "LOW"){
        return 1;
    }
    else if(ac == "medium" || ac == "MEDIUM"){
        return 2;
    }
    else if(ac == "high" || ac == "HIGH"){
        return 3;
    }
    else{
        return 0;
    }
}
vector<string> tokensVector(string line){
	vector<string> tokens;
    	char delimit[]=" \t\r\n\v\f";
    char *token = strtok((char*) line.c_str(), delimit);
    tokens.push_back(token);
    while(token != NULL)
            {
                token = strtok(NULL, delimit);
                if(token != NULL)
                    tokens.push_back(token);
            }

    return tokens;
 }

void BadInstruction(vector<string> tokens){
    cout << "Bad Instruction: ";
    for(int i=0; i<tokens.size(); i++){cout << tokens[i] << " ";}
    cout << endl;

}

