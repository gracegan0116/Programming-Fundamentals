#include "TreeDB.h"
#include <iostream>
using namespace std;

//constructor
TreeDB :: TreeDB(){
    root = NULL;
    probesCount = 0;
}
//delete all entries 
TreeDB :: ~TreeDB(){
    delete root;
}
void TreeDB :: clear(){
    if(root == NULL)
        return;
    delete_tree(root);
    root = NULL;
    return;
}
void TreeDB :: delete_tree(TreeNode* top){
    if (top == NULL)
        return;
    delete_tree(top->getLeft());
    delete_tree(top->getRight());
    delete top;
}
//insertion and helper functions
bool TreeDB :: insert(DBentry* newEntry){
    bool success;
    if (root == NULL){  
        root = new TreeNode(newEntry);
        return true;
    }
    else{
        TreeNode* ptr = new TreeNode(newEntry);
        success = insert_to_tree(ptr, root);
        if (success == false){ 
            delete ptr;
        }
        return success;
    }
}
bool TreeDB :: insert_to_tree(TreeNode* new_entry, TreeNode* head){
    if(new_entry->getEntry()->getName() == head->getEntry()->getName())
        return false;
    else if (new_entry->getEntry()->getName() < head->getEntry()->getName()){
        if(head->getLeft() == NULL){
            head->setLeft(new_entry);
            return true;
        }
        else
            return insert_to_tree(new_entry, head->getLeft());
    }
    else if(new_entry->getEntry()->getName() > head->getEntry()->getName()){
        if(head->getRight() == NULL){
            head->setRight(new_entry);
            return true;
        }
        else
            return insert_to_tree(new_entry,head->getRight());
    }
}
//find by name and sets probesCount
DBentry* TreeDB :: find(string name){
    int count_search = 0;
    bool exit = false;
    DBentry* out = NULL;
    while (!exit){
        if(root == NULL){
            exit = true;
            out = NULL;
        }
        else if (root->getEntry()->getName() == name){
            exit = true;
            count_search++;
            out = root->getEntry();
        }
        else{
            out = find_helper(root, count_search, name);
            exit = true;
        }
    }
    probesCount = count_search;
    return out;
}
DBentry* TreeDB :: find_helper(TreeNode* head, int& count, string key){
    count ++;
    DBentry* out;
    if(head == NULL)
        return NULL;
    else if(head->getEntry()->getName() == key){
        return head->getEntry();
    }
    if(key < head->getEntry()->getName())
        out = find_helper(head->getLeft(), count, key);
    else
        out = find_helper(head->getRight(), count, key);
    return out;
}
//remove
bool TreeDB :: remove(string name){
    if(root == NULL)
        return false;
    //check for existence
    DBentry* dup = find(name);
    if (dup==NULL)
        return false;
    
    TreeNode* parent_node_to_remove = find_parent_node(dup,root);
    if(parent_node_to_remove!=NULL){
        TreeNode* leaf;
        //true is left branch and false is right branch 
        bool branch;
        
        //leaf removal
        if(parent_node_to_remove->getLeft() != NULL && 
           parent_node_to_remove->getLeft()->getEntry()->getName() == dup->getName()){
            branch = true;
            leaf = parent_node_to_remove->getLeft();
            if(leaf->getLeft() == NULL && leaf->getRight() == NULL){
                delete leaf;
                parent_node_to_remove->setLeft(NULL);
                return true;
            }
        }
        //leaf removal
        else if(parent_node_to_remove->getRight() !=NULL && 
           parent_node_to_remove->getRight()->getEntry()->getName() == dup->getName()){
            branch = false;
            leaf = parent_node_to_remove->getRight();
            if(leaf->getLeft() == NULL && leaf->getRight() == NULL){
                delete leaf;
                parent_node_to_remove->setRight(NULL);
                return true;
            }
        }
        //when leaf has one subtree
        TreeNode* temp;
        if(leaf->getLeft()!=NULL && leaf->getRight()==NULL){
            temp = leaf->getLeft();
            delete leaf;
            if(branch)
                parent_node_to_remove->setLeft(temp);
            else
                parent_node_to_remove->setRight(temp);
            return true;
        }
        //when leaf has one subtree
        else if(leaf->getRight()!=NULL && leaf->getLeft()==NULL){
            temp = leaf->getRight();
            delete leaf;
            if(branch)
                parent_node_to_remove->setLeft(temp);
            else
                parent_node_to_remove->setRight(temp);
            return true;
        }
        //when leaf has two subtrees (replace by maximum node in the left subtree)
        if (leaf->getLeft()!=NULL && leaf->getRight()!=NULL){
            TreeNode* select = find_rightmost(leaf->getLeft());
            TreeNode* select_parent = find_parent_node(select->getEntry(),root);
            bool select_parent_branch;
            TreeNode* leaf_left;
            TreeNode* leaf_right;
            //true for left branch, false for right branch
            if(select_parent->getLeft() != NULL && 
               select_parent->getLeft()->getEntry()->getName()==select->getEntry()->getName())
                select_parent_branch = true;
            else if(select_parent->getRight() != NULL &&
                    select_parent->getRight()->getEntry()->getName()==select->getEntry()->getName())
                select_parent_branch = false;
            //removal
            if(select_parent != leaf){
                if(select_parent_branch){
                    leaf_left = leaf->getLeft();
                    leaf_right = leaf->getRight();
                    delete leaf;
                    select_parent->setLeft(select->getLeft());
                    select->setLeft(leaf_left);
                    select->setRight(leaf_right);
                    if(branch)
                        parent_node_to_remove->setLeft(select);
                    else
                        parent_node_to_remove->setRight(select);
                }
                else{
                    leaf_left = leaf->getLeft();
                    leaf_right = leaf->getRight();
                    delete leaf;
                    select_parent->setRight(select->getLeft());
                    select->setLeft(leaf_left);
                    select->setRight(leaf_right);
                    if(branch)
                        parent_node_to_remove->setLeft(select);
                    else
                        parent_node_to_remove->setRight(select);
                }
                return true;
            }
            else{
                if(branch){
                    select->setLeft(NULL);
                    select->setRight(leaf->getRight());
                    parent_node_to_remove->setLeft(select);
                }
                else{
                    select->setLeft(leaf->getLeft());
                    select->setRight(NULL);
                    parent_node_to_remove->setRight(select);
                }
                delete leaf;
            }
        }
    }
    else{
        //removal of a root without any child
        if(root->getLeft() == NULL && root->getRight() == NULL){
            delete root;
            root = NULL;
            return true;  
        }
        //removal of a root with one child or subtree
        if (root->getLeft()==NULL && root->getRight()!=NULL){
            TreeNode* temp = root->getRight();
            delete root;
            root = temp;
            return true;
        }
        else if(root->getRight()==NULL && root->getLeft()!=NULL){
            TreeNode* temp = root->getLeft();
            delete root;
            root = temp;
            return true;
        }
        //removal of a root with two child or subtree
        else{
            TreeNode* select = find_rightmost(root->getLeft());
            TreeNode* select_parent = find_parent_node(select->getEntry(),root);
            TreeNode* leaf_left = root->getLeft();
            TreeNode* leaf_right = root->getRight();
            if(select_parent!=root){
                if(select_parent->getLeft() != NULL && 
                   select_parent->getLeft()->getEntry()->getName()==select->getEntry()->getName())
                    select_parent->setLeft(select->getRight());
                else if(select_parent->getRight() != NULL &&
                        select_parent->getRight()->getEntry()->getName()==select->getEntry()->getName())
                    select_parent->setRight(select->getLeft());
                delete root;
                root = select;
                root->setLeft(leaf_left);
                root->setRight(leaf_right);
            }
            else{
                if(root->getLeft()==select){
                    delete root;
                    root = select;
                    select->setRight(leaf_right);
                }
                else{
                    delete root;
                    root = select;
                    select->setLeft(leaf_left);
                }
            }
            return true;
        }
    }
}
TreeNode* TreeDB :: find_parent_node(DBentry* data, TreeNode* head){
    if(head->getLeft()!=NULL && head->getLeft()->getEntry()->getName() == data->getName()||
       head->getRight()!=NULL && head->getRight()->getEntry()->getName() == data->getName())
        return head;
    if(head->getEntry()->getName() > data->getName())
        return find_parent_node(data,head->getLeft());
    if(head->getEntry()->getName() < data->getName())
        return find_parent_node(data,head->getRight());
    return NULL;
}

TreeNode* TreeDB :: find_rightmost(TreeNode* left_head){
    TreeNode* out;
    if(left_head->getRight() == NULL)
        return left_head;
    else
        out = find_rightmost(left_head->getRight());
    return out;
}

//optional print
ostream& operator<< (ostream& out, TreeNode* rhs){
    if (rhs==NULL)
        return out;
    operator<<(out,rhs->getLeft());
    operator<<(out,*(rhs->getEntry()));
    operator<<(out,rhs->getRight());
}
ostream& operator<< (ostream& out, const TreeDB& src){
    if(src.root == NULL)
        return out;
    operator<<(out,src.root);
    return out;
}

void TreeDB :: printProbes() const{
    cout<<probesCount<<endl;
}

void TreeDB :: countActive () const{
    int num = 0;
    if(root==NULL){
        cout<<0<<endl;
        return;
    }
    else{
        count_helper(root, num);
        cout<<num<<endl;
        return;
    }
}
void TreeDB :: count_helper(TreeNode* head, int& count)const{
    if (head == NULL)
        return;
    if(head->getEntry()->getActive())
        count++;
    count_helper(head->getLeft(), count);
    count_helper(head->getRight(), count);
}
