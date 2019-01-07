#include <iostream>
#include "DBentry.h"
using namespace std;

//constructors
DBentry :: DBentry(){
}
DBentry :: DBentry (string _name, unsigned int _IPaddress, bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

//destructor
DBentry :: ~DBentry(){
}

//mutators
void DBentry :: setName(string _name){
    name = _name;
}
void DBentry :: setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}
void DBentry :: setActive (bool _active){
    active = _active;
}
//accessors
string DBentry :: getName() const{
    return name;
}
unsigned int DBentry :: getIPaddress() const{
    return IPaddress;
}
bool DBentry :: getActive() const{
    return active;
}
//friend member function
ostream& operator<< (ostream& out, const DBentry& rhs){
    string temp;
    if(rhs.active)
        temp = "active";
    else
        temp = "inactive";
    out << rhs.name << " : " << rhs.IPaddress << " : " <<temp << endl;
    return(out);
}