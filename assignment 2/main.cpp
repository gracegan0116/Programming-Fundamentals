//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <valarray>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;
// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;
// ECE244 Student: you may want to add the prototype of
// helper functions you write here
//functions to ensure input is valid
void check_ar_name(string, bool&);
void check_ar_type(string, bool&);
void check_positive_int(int, bool&);
void check_angle(int, bool&);
bool check_duplicate_name_in_array(shape**, string);
void check_positive_exists(shape**, string, bool&);
void check_few(std::stringstream&, bool&);
void fail_then_invalid(std::stringstream&, bool&);
void fail_then_invalid_last_input(std::stringstream&, bool&);
void check_white_space(string, bool&);
//functions to manipulate objects of type shape
void draw_all(shape**);
shape* create_shape(int,string,string,int,int,int,int,bool);
void draw(shape**,string);
void delete_shape(shape**,string);
void delete_all(shape**);
void move_shape(shape**, string, int, int);
void rotate_shape(shape**,string,int);

int main() {
    
    string line;
    string command;
    //READING INPUT USING Cin
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);
        if (!lineStream.peek()){
            cout << "Error: invalid command\n";
        }
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        string ar_name, ar_type;
        int ar_locx,ar_locy,ar_sizex,ar_sizey,ar_value,ar_angle;

        if (command == "maxShapes"){
            lineStream >> ar_value;
            bool valid = true;
            //CHECK VALID ARGUMENT; few, invalid type, too many, invalid value
            if (lineStream.fail()){
                if (lineStream.eof()){
                    cout << "Error: too few arguments\n";
                    valid = false;
                }
                else{
                    cout << "Error: invalid argument\n";
                    valid = false;
                }
            }
            else if (!lineStream.eof()){
                cout<< "Error: too many arguments\n";
                valid = false;
            }
            check_positive_int(ar_value,valid);
            
            //SUCCESS, NO ERROR
            if(valid){
                max_shapes = ar_value;
                cout << "New database: max shapes is " << ar_value<<endl;
                //dynamically allocate the shapes array pointer and initialize each one to null
                shapesArray = new shape*[max_shapes];
                for (int i = 0; i<max_shapes; i++){
                    shapesArray[i] = NULL;
                }
            }
            
        }
        else if (command == "create"){
            bool valid = true;
            
            //GETTING ALL THE ARGUMENTS AND MAKE SURE THEY ARE VALID 
            check_few(lineStream, valid);
            if(valid){
                lineStream >> ar_name;
                check_ar_name(ar_name, valid);
                check_white_space(ar_name,valid);
                bool duplicate = check_duplicate_name_in_array(shapesArray,ar_name);
                if(duplicate){
                    cout <<"Error: shape "<<ar_name<<" exists\n";
                    valid = false;
                }
                check_few(lineStream, valid);
                
                if (valid){
                    lineStream >> ar_type;
                    check_ar_type(ar_type, valid);
                    check_few(lineStream, valid);
                    
                    if(valid){
                        lineStream >> ar_locx;
                        fail_then_invalid(lineStream,valid);
                        check_positive_int(ar_locx, valid);
                        check_few(lineStream,valid);
                        
                        if(valid){
                            lineStream >> ar_locy;
                            fail_then_invalid(lineStream,valid);
                            check_positive_int(ar_locy, valid);
                            check_few(lineStream,valid);
                            
                            if(valid){
                                lineStream >> ar_sizex;
                                fail_then_invalid(lineStream,valid);
                                check_positive_int(ar_sizex, valid);
                                check_few(lineStream,valid);
                                
                                if(valid){
                                    lineStream >> ar_sizey;
                                    fail_then_invalid_last_input(lineStream,valid);
                                    check_positive_int(ar_sizey, valid);
                                }
                            }
                        }    
                    }
                }
            }
            if (!lineStream.eof() && valid){
                cout<< "Error: too many arguments\n";
                valid = false;
            }
            if (valid){
                //creates the shape object and appends its address to shapesArray
                shape* temp=create_shape(shapeCount,ar_name,ar_type,ar_locx,ar_locy,ar_sizex,ar_sizey,valid);
                shapesArray[shapeCount] = temp;
                shapeCount = shapeCount + 1;
                temp = NULL;
            }
        }
        else if(command == "move"){
            bool valid = true;
            
            check_few(lineStream, valid);
            if(valid){
                lineStream >> ar_name;
                check_ar_name(ar_name, valid);
                check_positive_exists(shapesArray,ar_name,valid);
                check_few(lineStream,valid);
                
                if (valid){
                    lineStream >> ar_locx;
                    fail_then_invalid(lineStream,valid);
                    check_positive_int(ar_locx, valid);
                    check_few(lineStream,valid);
                
                    if (valid){
                        lineStream >> ar_locy;
                        fail_then_invalid_last_input(lineStream,valid);
                        check_positive_int(ar_locy, valid);
                    }
                }
            }
            if (!lineStream.eof() && valid){
                cout<< "Error: too many arguments\n";
                valid = false;
            }
            
            if(valid){
                move_shape(shapesArray,ar_name,ar_locx,ar_locy);
            }
        }
        else if(command == "rotate"){
            bool valid = true;
            
            check_few(lineStream,valid);
            if(valid){
                lineStream >> ar_name;
                check_ar_name(ar_name, valid);
                check_positive_exists(shapesArray,ar_name,valid);
                check_few(lineStream,valid);
                
                if(valid){
                    lineStream >> ar_angle;
                    fail_then_invalid_last_input(lineStream, valid);
                    check_angle(ar_angle, valid);
                }
            }
            if (!lineStream.eof() && valid){
                cout<< "Error: too many arguments\n";
                valid = false;
            }
            
            if(valid){
                cout << "Rotated "<<ar_name<<" "<<"by "<<ar_angle<<" degrees\n";
            }
        }
        else if(command == "draw"){
            bool valid = true;
            
            check_few(lineStream,valid);
            if(valid){
                lineStream >> ar_name;
                fail_then_invalid_last_input(lineStream,valid);
                check_positive_exists(shapesArray, ar_name,valid);
                if (!lineStream.eof() && valid){
                    cout<< "Error: too many arguments\n";
                    valid = false;
                }
                
                if (ar_name == "all"&&valid){
                    cout << "Drew all shapes\n";
                    draw_all(shapesArray);
                }
                else{
                    check_ar_name(ar_name, valid);
                    if (valid){
                        draw(shapesArray, ar_name);
                    }
                }
            }
        }
        else if (command == "delete"){
            bool valid = true;
            
            check_few(lineStream,valid);
            if(valid){
                lineStream >> ar_name;
                fail_then_invalid_last_input(lineStream,valid);
                check_positive_exists(shapesArray, ar_name,valid);
                if (!lineStream.eof() && valid){
                    cout<< "Error: too many arguments\n";
                    valid = false;
                }

                if (ar_name == "all"&&valid){
                    delete_all(shapesArray);
                    cout << "Deleted: all shapes\n";
                }
                else{
                    check_ar_name(ar_name, valid);
                    if (valid){
                        delete_shape(shapesArray, ar_name);
                    }
                }
            }
        }
        else{
            cout<< "Error: invalid command\n";
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
    }  // End input loop until EOF.
}
//helper functions to manipulate objects of class type shape
shape* create_shape(int current_total_shape, string name, string type, int lx, int ly, int sx, int sy, bool valid){
    if (current_total_shape<max_shapes){
        shape* dummy = new shape(name,type,lx,ly,sx,sy);
        cout << "Created " << name << ": " <<type << " " << lx << " " << ly << " " << sx << " " << sy<<endl;
        return (dummy);
    }
    else if(valid){
        cout<<"Error: shape array is full\n";
    }
}
void draw(shape** list, string name){
    string temp;
    for (int i =0; i<shapeCount; i++){
        temp = (*list[i]).getName();
        if (temp.compare(name) == 0){
            cout<< "Drew "<<name<<endl;
            (*list[i]).draw();
        }
    }
}
void draw_all(shape**list){
    for (int i =0; i<shapeCount; i++){
        (*list[i]).draw();
    }
}
void delete_shape(shape** list, string name){
    string temp;
    for (int i =0; i<shapeCount; i++){
        temp = (*list[i]).getName();
        if (temp.compare(name) == 0){
            cout << "Deleted shape "<<name<<endl;
            list[i]==NULL;
        }
    }
}
void delete_all(shape**list){
    for (int i =0; i<shapeCount; i++){
        list[i]==NULL;
    }
}
void move_shape(shape** list, string name, int x, int y){
    string temp;
    for (int i =0; i<shapeCount; i++){
        temp = (*list[i]).getName();
        if (temp.compare(name) == 0){
            (*list[i]).setXlocation(x);
            (*list[i]).setYlocation(y);
            cout << "Moved " << name<< " "<< "to "<<x<< " "<<y<<endl;
        }
    }
}
void rotate_shape(shape** list, string name, int angle){
    string temp;
    for (int i =0; i<shapeCount; i++){
        temp = (*list[i]).getName();
        if (temp.compare(name) == 0){
            (*list[i]).setRotate(angle);
        }
    }
}
//helper functions to check for input value errors
bool check_duplicate_name_in_array(shape** list,string name){
    string temp;
    for (int i =0; i<shapeCount; i++){
        temp = (*list[i]).getName();
        if (temp.compare(name) == 0){
            return true;
        }
    }
    return false;
}
void fail_then_invalid(std::stringstream& input, bool& valid){
    if (input.fail() && valid && !input.eof()){
        cout << "Error: invalid argument\n";
        valid = false;
    }
}
void fail_then_invalid_last_input(std::stringstream& input, bool& valid){
    //fail flag is true when eof is true
    bool many = false;;
    if (input.fail() && valid){
        if(!input.eof()){
            many = true;
        }
        else{
            cout << "Error: invalid argument\n";
            valid = false;
        }
    }
    if (many && valid){
        valid = false;
        cout << "Error: too many arguments\n";
    }
}
void check_few(std::stringstream& input, bool& valid){
    if(valid){
        if (input.eof()){
            cout << "Error: too few arguments\n";
            valid = false;
        }
    }
}
void check_ar_name(string name, bool& valid){
    bool found = false;
    if (valid){
        for (int i=0; i<NUM_TYPES; i++){
            if(name == shapeTypesList[i]){
                found = true;
            }
        }
        for(int i=0; i<NUM_KEYWORDS; i++){
            if(name == keyWordsList[i]){
                found = true;
            }
        }
        if(found){
            cout << "Error: invalid shape name\n";
            valid = false;
        }
    }
}
void check_ar_type(string type, bool& valid){
    bool found = false;
    if (valid){
        for (int i=0; i<NUM_TYPES; i++){
            if (type == shapeTypesList[i]){
                found = true;
            }
        }
        if(!found){
            cout<<"Error: invalid shape type\n";
            valid = false;
        }
    }
}
void check_positive_int(int num, bool& valid){
    if (valid){
        if (num < 0){
            valid = false;
            cout << "Error: invalid value\n";
        }
    }
}
void check_angle(int angle, bool& valid){
    if (valid){
        if (angle >= 0 && angle <= 360){
            valid = true;
        }
        else{
            cout << "Error: invalid value\n";
            valid = false;
        }
    }
}
void check_positive_exists(shape** list, string name, bool&valid){
    if(name == "all"){
        return;
    }
    bool exists = check_duplicate_name_in_array(list, name);
    if(!exists){
        valid = false;
        cout << "Error: shape "<<name<<" not found\n";
    }
}
void check_white_space(string str, bool&valid){
    for (int i = 0; i<str.length(); i++){
        if(str[i]=='\t' || str[i] == '\n' || str[i] == ' '){
            valid = false;
            cout << "Error: invalid shape name\n";
        }
    }
}