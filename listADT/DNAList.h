#include <iostream>
#include <iterator>
#include "doublyLinkedList.cpp"
using namespace std;
#ifndef DNALIST_H
#define DNALIST_H

template <class Type>
class DNAList : public DoublyLinkedList<Type>
{
    public:

    DNAList(string);
    
    DNAList(DNAList &);//copy constructor
    float get_GC();
    void append(char);
    void appendString(string);
    void appendObject(DNAList);
    Type complement();
    Type reverse_complement();
    private:
    DoublyLinkedList<Type> OBJ;
    
};
template <class Type>
DNAList<Type> :: DNAList(string Sequence)
{
    for(int c=0;c<Sequence.length();c++)
    {
        if(Sequence[c] != 'A' || 'T' || 'C' || 'G')
        {
            cout << "Incorrect character found";
        }
        else {
            OBJ.add(Sequence[c]);
        }
    }
}
template <class Type>
DNAList<Type> :: DNAList(DNAList &other)
{
    DoublyLinkedListIterator<Type> it = other.OBJ.begin();
    while(it!=other.OBJ.end())
    {
        OBJ.add(*it);
    }

}
template <class Type>
float DNAList<Type> :: get_GC()
{
    float result=0;
    float amount_G=OBJ.count('G');
    float amount_C=OBJ.count('C');
    float Nucleotoids= this->currentSize;
    result = (amount_C + amount_G)/Nucleotoids;
    return result;

}
template <class Type>
void DNAList<Type>::appendString (string DNA)//appends a string to the end of list
{
    DoublyLinkedListIterator<Type> it = OBJ.end();
    it=OBJ.end();
    for(char character : DNA )
    {
        OBJ.add(character);
    }
}
template <class Type>
void DNAList<Type> :: appendObject(DNAList<Type> other)
{
{
    for (DoublyLinkedListIterator<Type> it = other.OBJ.begin(); it != other.OBJ.end(); ++it)
    {
        OBJ.add(*it);
    }
}
}

template <class Type>
Type DNAList<Type> :: complement()
{
    DNAList<Type> complementedSequence;
    for (DoublyLinkedListIterator<Type> it = OBJ.begin(); it != OBJ.end(); ++it)
    {
        if (*it == 'A')
        {
            complementedSequence.append('T');
        }
        else if (*it == 'T')
        {
            complementedSequence.append('A');
        }
        else if (*it == 'G')
        {
            complementedSequence.append('C');
        }
        else if (*it == 'C')
        {
            complementedSequence.append('G');
        }
    }
    return complementedSequence;
}
template<class Type>
Type DNAList<Type> :: reverse_complement()
{
    DNAList<Type> reversedComplement;
    for (DoublyLinkedListIterator<Type> it = OBJ.rbegin(); it != OBJ.rend(); ++it)
    {
        if (*it == 'A')
        {
            reversedComplement.append('T');
        }
        else if (*it == 'T')
        {
            reversedComplement.append('A');
        }
        else if (*it == 'G')
        {
            reversedComplement.append('C');
        }
        else if (*it == 'C')
        {
            reversedComplement.append('G');
        }
    }
    return reversedComplement;
}
