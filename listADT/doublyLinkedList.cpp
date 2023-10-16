/***********************************************
 * DoublyLinkedList.h
 *
 * Doubly linked list implementation of List ADT.
 *
 * Authors: Juan O. Lopez and Enrique A. Pereira Montalvo
 **********************************************/

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "ListADT.h"
#include <ostream>
using namespace std;

/***********
 * nodeType
 ***********/
template <class Type>
struct nodeType
{
    Type data;
    nodeType *next;
    nodeType *prev; // Add a previous pointer for doubly linked list
};

/**********************
 * DoublyLinkedListIterator
 **********************/
template <class Type>
class DoublyLinkedListIterator
{
public:
    DoublyLinkedListIterator(); // default constructor
    DoublyLinkedListIterator(nodeType<Type>*); // constructor with a parameter
    Type operator*(); // overload the dereferencing operator *
    DoublyLinkedListIterator<Type> operator++(); // overload the pre-increment operator
    DoublyLinkedListIterator<Type> operator--(); // Add operator-- for reverse iteration
    bool operator==(const DoublyLinkedListIterator<Type>& right) const; // overload equality operator
    bool operator!=(const DoublyLinkedListIterator<Type>& right) const; // overload inequality operator
private:
    nodeType<Type> *current; // points to the current node in the doubly linked list
};

template <class Type>
DoublyLinkedListIterator<Type>::DoublyLinkedListIterator()
{
    current = nullptr;
}

template <class Type>
DoublyLinkedListIterator<Type>::DoublyLinkedListIterator(nodeType<Type> *ptr)
{
    current = ptr;
}

template <class Type>
Type DoublyLinkedListIterator<Type>::operator*()
{
    return current->data;
}

template <class Type>
DoublyLinkedListIterator<Type> DoublyLinkedListIterator<Type>::operator++()
{
    current = current->next;
    return *this;
}

template <class Type>
DoublyLinkedListIterator<Type> DoublyLinkedListIterator<Type>::operator--()
{
    current = current->prev;
    return *this;
}

template <class Type>
bool DoublyLinkedListIterator<Type>::operator==(const DoublyLinkedListIterator<Type>& right) const
{
    return (current == right.current);
}

template <class Type>
bool DoublyLinkedListIterator<Type>::operator!=(const DoublyLinkedListIterator<Type>& right) const
{
    return (current != right.current);
}

/*************
 * DoublyLinkedList
 *************/

template <class Type>
class DoublyLinkedList : public ListADT<Type>
{
    template <class T>
    friend std::ostream& operator<<(std::ostream&, const DoublyLinkedList<T>&);

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<Type>&);
    const DoublyLinkedList<Type>& operator=(const DoublyLinkedList<Type>&);
    ~DoublyLinkedList();

    void add(const Type&);
    void addAt(int, const Type&);
    bool remove(const Type&);
    bool removeAt(int);
    int removeAll(const Type&);
    Type getAt(int) const;
    void setAt(int, const Type&);
    Type getFirst() const;
    Type getLast() const;
    int firstIndex(const Type&) const;
    int lastIndex(const Type&) const;
    int count(const Type&) const;
    void clear();

    int size() const;
    bool isEmpty() const;

    DoublyLinkedListIterator<Type> begin();
    DoublyLinkedListIterator<Type> end();
    DoublyLinkedListIterator<Type> rbegin(); // Add rbegin for reverse iteration
    DoublyLinkedListIterator<Type> rend(); // Add rend for reverse iteration
private:
    nodeType<Type> *head, *tail;
    void copyList(const DoublyLinkedList<Type>&);
    nodeType<Type>* getNodeAt(int) const;
    void removeNode(nodeType<Type> *node);
};

/* Constructor */
template <class Type>
DoublyLinkedList<Type>::DoublyLinkedList()
{
    head = tail = nullptr;
    this->currentSize = 0;
}

/* Copy constructor */
template <class Type>
DoublyLinkedList<Type>::DoublyLinkedList(const DoublyLinkedList<Type>& otherList)
{
    head = tail = nullptr;
    copyList(otherList);
}

/* Overloading assignment operator (=) */
template <class Type>
const DoublyLinkedList<Type>& DoublyLinkedList<Type>::operator=(const DoublyLinkedList<Type>& otherList)
{
    if (this != &otherList)
    {
        copyList(otherList);
    }
    return *this;
}

/* Destructor */
template <class Type>
DoublyLinkedList<Type>::~DoublyLinkedList()
{
    clear();
}

template <class Type>
void DoublyLinkedList<Type>::copyList(const DoublyLinkedList<Type>& otherList)
{
    if (head != nullptr)
        clear();

    if (otherList.head != nullptr)
    {
        nodeType<Type> *currentPtr = otherList.head;

        nodeType<Type> *newNodePtr = new nodeType<Type>;
        newNodePtr->data = currentPtr->data;
        newNodePtr->next = nullptr;
        newNodePtr->prev = nullptr;
        tail = head = newNodePtr;

        currentPtr = currentPtr->next;

        while (currentPtr != nullptr)
        {
            newNodePtr = new nodeType<Type>;
            newNodePtr->data = currentPtr->data;
            newNodePtr->next = nullptr;
            newNodePtr->prev = tail;

            tail->next = newNodePtr;
            tail = newNodePtr;

            currentPtr = currentPtr->next;
        }
        this->currentSize = otherList.currentSize;
    }
}

template <class Type>
DoublyLinkedListIterator<Type> DoublyLinkedList<Type>::rbegin()
{
    DoublyLinkedListIterator<Type> temp(tail); // Start at the tail
    return temp;
}

template <class Type>
DoublyLinkedListIterator<Type> DoublyLinkedList<Type>::rend()
{
    DoublyLinkedListIterator<Type> temp; // Iterator before the beginning (nullptr)
    return temp;
}

/* add */
template <class Type>
void DoublyLinkedList<Type>::add(const Type& e)
{
    nodeType<Type> *newNodePtr = new nodeType<Type>;
    newNodePtr->data = e;
    newNodePtr->next = nullptr;

    if (this->isEmpty())
    {
        head = tail = newNodePtr;
    }
    else
    {
        newNodePtr->prev = tail;
        tail->next = newNodePtr;
        tail = newNodePtr;
    }

    this->currentSize++;
}

/* addAt */
template <class Type>
void DoublyLinkedList<Type>::addAt(int pos, const Type& e)
{
    if (pos < 0 || pos > this->currentSize)
    {
        throw std::out_of_range("Invalid position.");
    }

    if (pos == this->currentSize)
    {
        add(e);
    }
    else
    {
        nodeType<Type> *newNodePtr = new nodeType<Type>;
        newNodePtr->data = e;
        newNodePtr->next = nullptr; // Initialize the next pointer

        if (pos == 0)
        {
            newNodePtr->prev = nullptr; // Special case: Add at the beginning
            head->prev = newNodePtr;
            newNodePtr->next = head;
            head = newNodePtr;
        }
        else
        {
            nodeType<Type> *prevPtr = getNodeAt(pos - 1);
            newNodePtr->prev = prevPtr;
            newNodePtr->next = prevPtr->next;
            prevPtr->next->prev = newNodePtr;
            prevPtr->next = newNodePtr;
        }

        this->currentSize++;
    }
}

/* removeNode */
template <class Type>
void DoublyLinkedList<Type>::removeNode(nodeType<Type> *node)
{
    if (node == nullptr)
        return;

    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        tail = node->prev;

    delete node;
    this->currentSize--;
}

/* remove */
template <class Type>
bool DoublyLinkedList<Type>::remove(const Type& e)
{
    nodeType<Type> *currentPtr = head;

    while (currentPtr != nullptr && currentPtr->data != e)
    {
        currentPtr = currentPtr->next;
    }

    if (currentPtr == nullptr)
        return false;

    removeNode(currentPtr);
    return true;
}

/* removeAt */
template <class Type>
bool DoublyLinkedList<Type>::removeAt(int pos)
{
    if (pos < 0 || pos >= this->currentSize)
    {
        throw std::out_of_range("Invalid position.");
    }

    nodeType<Type> *target = getNodeAt(pos);
    removeNode(target);
    return true;
}

/* removeAll */
template <class Type>
int DoublyLinkedList<Type>::removeAll(const Type& e)
{
    int counter = 0;
    while (remove(e))
    {
        counter++;
    }
    return counter;
}

/* getNodeAt */
template <class Type>
nodeType<Type>* DoublyLinkedList<Type>::getNodeAt(int pos) const
{
    nodeType<Type> *currentPtr;

    if (pos < 0 || pos >= this->currentSize)
    {
        throw std::out_of_range("Invalid position.");
    }

    if (pos < this->currentSize / 2)
    {
        currentPtr = head;
        for (int i = 0; i < pos; i++)
        {
            currentPtr = currentPtr->next;
        }
    }
    else
    {
        currentPtr = tail;
        for (int i = this->currentSize - 1; i > pos; i--)
        {
            currentPtr = currentPtr->prev;
        }
    }
    return currentPtr;
}

/* getAt */
template <class Type>
Type DoublyLinkedList<Type>::getAt(int pos) const
{
    nodeType<Type> *target = getNodeAt(pos);
    return target->data;
}

/* setAt */
template <class Type>
void DoublyLinkedList<Type>::setAt(int pos, const Type& e)
{
    nodeType<Type> *target = getNodeAt(pos);
    target->data = e;
}

/* getFirst */
template <class Type>
Type DoublyLinkedList<Type>::getFirst() const
{
    if (this->isEmpty())
    {
        return Type(); // Return a default-constructed Type (you can change this behavior)
    }
    return head->data;
}

/* getLast */
template <class Type>
Type DoublyLinkedList<Type>::getLast() const
{
    if (this->isEmpty())
    {
        return Type(); // Return a default-constructed Type (you can change this behavior)
    }
    return tail->data;
}

/* firstIndex */
template <class Type>
int DoublyLinkedList<Type>::firstIndex(const Type& e) const
{
    nodeType<Type> *currentPtr = head;
    int pos = 0;

    while (currentPtr != nullptr && currentPtr->data != e)
    {
        currentPtr = currentPtr->next;
        pos++;
    }

    if (currentPtr != nullptr)
    {
        return pos;
    }
    else
    {
        return -1;
    }
}

/* lastIndex */
template <class Type>
int DoublyLinkedList<Type>::lastIndex(const Type& e) const
{
    nodeType<Type> *currentPtr = tail;
    int pos = this->currentSize - 1;

    while (currentPtr != nullptr && currentPtr->data != e)
    {
        currentPtr = currentPtr->prev;
        pos--;
    }

    if (currentPtr != nullptr)
    {
        return pos;
    }
    else
    {
        return -1;
    }
}

/* count */
template <class Type>
int DoublyLinkedList<Type>::count(const Type& e) const
{
    int counter = 0;

    nodeType<Type> *currentPtr = head;

    while (currentPtr != nullptr)
    {
        if (currentPtr->data == e)
        {
            counter++;
        }
        currentPtr = currentPtr->next;
    }

    return counter;
}

/* clear */
template <class Type>
void DoublyLinkedList<Type>::clear()
{
    while (!this->isEmpty())
    {
        removeNode(head);
    }
}

/* begin */
template <class Type>
DoublyLinkedListIterator<Type> DoublyLinkedList<Type>::begin()
{
    DoublyLinkedListIterator<Type> temp(head);
    return temp;
}

/* end */
template <class Type>
DoublyLinkedListIterator<Type> DoublyLinkedList<Type>::end()
{
    DoublyLinkedListIterator<Type> temp;
    return temp;
}

/* size */
template <class Type>
int DoublyLinkedList<Type>::size() const
{
    return this->currentSize;
}

/* isEmpty */
template <class Type>
bool DoublyLinkedList<Type>::isEmpty() const
{
    return this->currentSize == 0;
}

/* operator<< */
template <class Type>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<Type>& list)
{
    for (nodeType<Type> *curPtr = list.head; curPtr != nullptr; curPtr = curPtr->next)
    {
        os << curPtr->data << " ";
    }
    os << "\n";
    return os;
}

#endif