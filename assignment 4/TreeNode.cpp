#include "TreeNode.h"
using namespace std;

//constructor
TreeNode :: TreeNode(DBentry* _entryPtr){
    left = NULL;
    right = NULL;
    entryPtr = _entryPtr;
}
//destructor
TreeNode :: ~TreeNode(){
    delete entryPtr;
    entryPtr = NULL;
    left = NULL;
    right = NULL;
}
//mutators
void TreeNode :: setLeft(TreeNode* newLeft){
    left = newLeft;
}
void TreeNode :: setRight(TreeNode* newRight){
    right = newRight;
}
//accessors
TreeNode* TreeNode :: getLeft() const{
    return left;
}
TreeNode* TreeNode :: getRight() const{
    return right;
}
DBentry* TreeNode :: getEntry() const{
    return entryPtr;
}