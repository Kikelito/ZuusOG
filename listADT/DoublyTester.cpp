#include <iostream>
#include "doublyLinkedList.cpp"
using namespace std;
int main()
{
	DoublyLinkedList<string> OBJ;
	string value;
	int opcion=0;
	int pos=0;
	bool END = false;
	do {
	cout << "DOUBLY LINKED LIST TESTER\n";
	cout << "1.Add to the doublyLinkedList\n";
	cout << "2.Remove from the doublyLinkedList\n";
	cout << "3.Remove all data from doublyLinkedList\n";
	cout << "4.Add to the doublyLinkedList at a certain position\n";
	cout << "5.Get data at the first position\n";
	cout << "6.Get data at the last position\n";
	cout << "7.Print all data from the doublyLinkedList\n";
	cout << "8.Get the last position, of the element.\n";
	cout << "9.Get the first position of the element.\n";
	cout << "10.Count the amount of items in the Doubly.\n";
	cout << "Ingresa el numero a donde desea entrar:";
	cin >> opcion;

	switch(opcion)
	{
		case 1:
		{
			cout << "Inserte un valor tipo string al doublyLinkedList:\n";
			cin >> value;
			OBJ.add(value);
			break;
		}
		case 2:
		{
			if(OBJ.isEmpty())
			{
				cout << "WARNING: No hay elemento para remover del doublyLinkedList\n";
				system("CLS");
			}
			else {
				cout << "Inserte la posicion del elemento que desea eliminar:";
				cin >> pos;
				OBJ.removeAt(pos);
			}	
			break;
		}
		case 3:
		{
			OBJ.clear();
			break;
		}
		case 4:
		{
			cout << "Add the position you want to insert the element:";
			cin >> pos;
			cout << "Add the element:";
			cin >> value;
			system("CLS");
			break;
		}
		case 5:
		{	
			cout << "The first element in the doubly is:";
			OBJ.getFirst();
			system("CLS");
			break;
		}
		case 6:
		{
			cout << "The first element in the doubly is:";
			OBJ.getLast();
			system("CLS");
			break;
		}
		case 7:
		{
			for(int c=0;c<OBJ.size();c++)
			{
				cout << " " << OBJ.getAt(c);
			}
			break;
		}
		case 8:
		{
			cout << "Insert el elemento que desea buscar:";
			cin >> value;
			OBJ.lastIndex(value);
			break;
		}
		case 9:
		{
			cout << "Insert el elemento que desea buscar:";
			cin >> value;
			OBJ.firstIndex(value);
			break;
		}
		case 10:
		{
			cout << "The object count is:"<< OBJ.size();
			break;
		}
		default :
		{
			END =true;
			break;
		}
	}
	}while (!END);

}