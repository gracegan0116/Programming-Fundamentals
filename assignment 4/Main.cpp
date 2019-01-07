#include <iostream>
#include <sstream>

#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"
using namespace std;

int main(){    
    //useful variables
    string name;
    string activeS;
    unsigned int IP;
    bool active;
    bool succeed;
    
    //start
    string line;
    string command;
    TreeDB database;
    cout << "> ";
    getline(cin, line);
    while (!cin.eof()){
        stringstream lineStream (line);
        lineStream >> command;
        //check foe the command and respond accordingly
        if (command == "insert"){
            lineStream >> name;
            lineStream >> IP;
            lineStream >> activeS;
            
            if(activeS == "active")
                active = true;
            else if(activeS == "inactive")
                active = false;
            DBentry* temp = new DBentry(name,IP,active);
            succeed = database.insert(temp);
            if(succeed)
                cout << "Success\n";
            else
                cout << "Error: entry already exists\n";
        }
        else if(command == "find"){
            lineStream >> name;
            DBentry* ptr = database.find(name);
            if(ptr!=NULL)
                cout << *ptr; 
            else
                cout << "Error: entry does not exist\n";
        }
        else if(command == "remove"){
            lineStream >> name;
            succeed = database.remove(name);
            if(succeed)
                cout <<"Success\n";
            else
                cout <<"Error: entry does not exist\n";
        }
        else if(command == "printall")
            cout<<database;
        else if(command =="printprobes"){
            lineStream >> name;
            DBentry* ptr = database.find(name);
            if(ptr == NULL)
                cout<<"Error: entry does not exist\n";
            else
                database.printProbes();
        }
        else if(command == "removeall"){
            database.clear();
            cout<<"Success\n";
        }
        else if(command == "countactive"){
            database.countActive();
        }
        else if(command == "updatestatus"){
            lineStream >> name;
            lineStream >> activeS;
            if(activeS == "active")
                active = true;
            else if(activeS == "inactive")
                active = false;
            DBentry* ptr = database.find(name);
            if(ptr == NULL)
                cout<<"Error: entry does not exist\n";
            else{
                ptr->setActive(active);
                cout<<"Success\n";
            }
        }
        //ready for another input
        cout << "> ";         
        getline(cin, line);
    }
}

