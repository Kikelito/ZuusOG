/***********************************************
 * ListADT.h
 *
 * List ADT defined as an abstract base class.
 *
 * Author: Juan O. Lopez
 **********************************************/

#ifndef LISTADT_H
#define LISTADT_H

template <class Type>
class ListADT
{
	/* The "= 0" indicates that these are "pure virtual functions", meaning that
	 * the functions will not be defined in this class.  Once a class contains
	 * one ore more pure virtual functions, then it becomes an "abstract class",
	 * meaning no objects of that class may be defined.
	 * Abstract classes may have constructors to initialize its private fields,
	 * which in this case would only be to initialize currentSize to 0.
	 * Note that it's possible to use virtual functions that aren't pure to
	 * achieve run-time binding (also known as dynamic binding). */
	public:
		virtual void add(const Type&) = 0; // append at the end
		virtual void addAt(int, const Type&) = 0; // add at position
		virtual bool remove(const Type&) = 0; // remove first copy of element
		virtual bool removeAt(int) = 0; // remove at position
		virtual int removeAll(const Type&) = 0; // remove all copies of element
		virtual Type getAt(int) const = 0; // retrieve at position
		virtual void setAt(int, const Type&) = 0; // set at position
		virtual Type getFirst() const = 0; // retrieve first element
		virtual Type getLast() const = 0; // retrieve last element
		virtual int firstIndex(const Type&) const = 0;
		virtual int lastIndex(const Type&) const = 0;
		virtual int count(const Type&) const = 0; // # of times element appears in list
		virtual void clear() = 0; // empty the list

		/* Non-virtual functions */
		int size() const;
		bool isEmpty() const;
		bool contains(const Type&) const;

	protected:
		int currentSize;
};

/*
 * size
 *
 * Provides the amount of elements in the list.
 *
 * Returns: Amount of elements in the list
 */
template <class Type>
int ListADT<Type>::size() const
{
	return currentSize;
}

/*
 * isEmpty
 *
 * Determines whether the list is empty.
 *
 * Returns: True if the list is empty, false otherwise
 */
template <class Type>
bool ListADT<Type>::isEmpty() const
{
	return size() == 0;
}

/*
 * contains
 *
 * Determines if an element is present in the list.
 *
 * Parameters: e - Element to look for
 * Returns: True if the element is in the list, false otherwise
 */
template <class Type>
bool ListADT<Type>::contains(const Type& e) const
{
	return firstPos(e) >= 0; // Assuming firstPos returns -1 if not found
}

#endif
