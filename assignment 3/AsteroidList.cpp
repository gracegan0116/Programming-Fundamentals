#include <galaxy-explorer/AsteroidList.hpp>

#include "MyAIData.hpp"


AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
	this->next = nullptr;
        //since a is passed by value, the copy will be destroyed at the end
        //of the function call
        this->data = new Asteroid(a.getID(),a.getMass(),a.getHealth(),
                a.getCurrentHitbox(),a.getVelocity());

}

AsteroidListItem::~AsteroidListItem() {
    //deleting the pointer that points to the data (Asteroid), keeps the next pointer
    delete data;
    data = NULL;
}

AsteroidList::AsteroidList()
{ 
    //default AsteroidListItem constructor
    head.setNext(nullptr);
}

AsteroidList::AsteroidList(const AsteroidList& src)
{
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the destructor (because you should put all your constructors together).
    
    //this is the copy constructor
    const AsteroidListItem* ptr = src.begin();
    AsteroidListItem* nptr = NULL;
    AsteroidListItem* terminal = NULL;
    
    while(ptr!=NULL){
        nptr = new AsteroidListItem(ptr->getData());
        if (terminal == NULL){
            head.setNext(nptr);
        }
        else{
            terminal->~AsteroidListItem();
        }
        ptr = ptr->getNext();
        terminal = nptr;
    }
    nptr = NULL;
    delete nptr;
}

AsteroidList::~AsteroidList() {
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
    //free all elements in the AsteroidList, making it empty
    AsteroidListItem* current_ptr = head.getNext();
    AsteroidListItem* temp = current_ptr;
    while(current_ptr!=NULL){
        temp = current_ptr->getNext();
        current_ptr->~AsteroidListItem();
        delete current_ptr;
        current_ptr = temp;
    }
    head.~AsteroidListItem();
    head.setNext(NULL);
}

void AsteroidList::pushFront(Asteroid e) {
    //adding to the beginning of the list
    
    AsteroidListItem* temp = new AsteroidListItem(e);
    temp->setNext(head.getNext());
    head.setNext(temp);
    temp = NULL;
    delete temp;
}

Asteroid& AsteroidList::front() {
    //return reference to the first asteroid 
    
   return (head.getNext()->getData());
}

const Asteroid& AsteroidList::front() const {
    //return reference (const) to the first asteroid
    
    return (head.getNext()->getData());
}

bool AsteroidList::isEmpty() const {
    //checks if the AsteroidList is empty, returns boolean
    if (head.getNext()==NULL)
        return true;
    return false;
}

int AsteroidList::size() const {
    //return number of AsteroidListItem in the AsteroidList
    int count = 0;
    if ((this)->isEmpty())
        return 0;
    //since head is constant
    const AsteroidListItem* temp = head.getNext();
    while(temp!=NULL){
        count ++;
        temp = temp->getNext();
    }
    return count;
}

AsteroidListItem* AsteroidList::beforeBegin() {
    //return the an AsteroidListItem pointer pointing to the head
    AsteroidListItem* pointer_h = &head;
    return pointer_h;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
    //return an AsteroidListItem pointer (const) pointing to the head
    const AsteroidListItem* pointer_h = &head;
    return pointer_h;
}

AsteroidListItem* AsteroidList::begin() {
    //return an AsteroidListItem pointer pointing to the first element in the
    //AsteroidList
    AsteroidListItem* ptr_next = head.getNext();
    return ptr_next;
}

const AsteroidListItem* AsteroidList::begin() const {
    //return an AsteroidListItem pointer (const) pointing to the first element in the
    //AsteroidList
    const AsteroidListItem* ptr_next = head.getNext();
    return ptr_next;
}

AsteroidListItem* AsteroidList::beforeEnd() {
    //return an AsteroidListItem pointer pointing to the last element in the
    //AsteroidList
    
    if((*this).isEmpty())
        return (*this).beforeBegin();
    AsteroidListItem* ptr = head.getNext();
    while(ptr->getNext()!=NULL)
        ptr = ptr->getNext();
    return ptr;
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    //return an AsteroidListItem pointer (const) pointing to the last element in the
    //AsteroidList
    
    if((*this).isEmpty())
        return(*this).beforeBegin();
    const AsteroidListItem* ptr = head.getNext();
    while(ptr->getNext()!=NULL)
        ptr = ptr->getNext();
    return ptr;
}

AsteroidListItem* AsteroidList::end() {
    //return an AsteroidListItem pointer pointing to the element after the last
    //element in the AsteroidList
    AsteroidListItem* ptr = NULL;
    return ptr;
}

const AsteroidListItem* AsteroidList::end() const {
    //return an AsteroidListItem pointer (const) pointing to the element after the last
    //element in the AsteroidList
    const AsteroidListItem* ptr = NULL;
    return ptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    //insert e at the position right after prev and return an AsteroidListElement
    //pointer that points to e
    
    //making a new AsteroidListItem with  a copy of e 
    AsteroidListItem* new_element = new AsteroidListItem(e);
    AsteroidListItem* temp = (*prev).setNext(new_element);
    (*prev).getNext()->setNext(temp);
    new_element = NULL;
    delete new_element;
    return prev->getNext();
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    //if other is empty, return prev(insertion point)
    if(others.isEmpty())
        return prev;

    //make copies of elements in others and insert after prev
    const AsteroidListItem* temp = others.beforeBegin();
    while(temp->getNext()!=NULL){
        prev = insertAfter(prev,temp->getNext()->getData());
        temp = temp->getNext();
    }
    //return last element in others that was inserted earlier
    return prev;
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    //delete the asteroid of the element after prev location and return an AsteroidListitem
    //pointer that points to the next value after prev
    AsteroidListItem* temp_ptr = prev->getNext();
    prev->setNext(prev->getNext()->getNext());
    temp_ptr->~AsteroidListItem();
    delete temp_ptr;
    return (prev->getNext());
}

void AsteroidList::clear() {
    //free all elements in the AsteroidList, making it empty
    AsteroidListItem* current_ptr = head.getNext();
    AsteroidListItem* temp = current_ptr;
    while(current_ptr!=NULL){
        temp = current_ptr->getNext();
        current_ptr->~AsteroidListItem();
        delete current_ptr;
        current_ptr = temp;
    }
    delete current_ptr;
    delete temp;
    head.~AsteroidListItem();
    head.setNext(NULL);
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    //copies the src to the current object
    
//    clear the current list first
    (this)->clear();
    //copy starts here
    const AsteroidListItem* ptr = src.begin();
    AsteroidListItem* nptr = NULL;
    AsteroidListItem* terminal = NULL;
    while(ptr!=NULL){
        nptr = new AsteroidListItem(ptr->getData());
        if(terminal == NULL)
            head.setNext(nptr);
        else
            terminal->setNext(nptr);
        ptr = ptr->getNext();
        terminal = nptr;
    }
    nptr = NULL;
    delete nptr;
    return (*this);
}
