#include <uC++.h>
#include <iostream>
#include <queue>
#include "BMP.cpp"
using namespace std;
#ifndef BOUNDEDBUFFER_CPP
#define BOUNDEDBUFFER_CPP
_Monitor BoundedBuffer
{
	uCondition full, empty;
	int front, back, count, buf_size;
	queue<BMP> elements;
	string name;

  public:
	BoundedBuffer(int buf_size, string name) : front(0), back(0), count(0), buf_size(buf_size), name(name) {}
	_Nomutex int query() { return count; }
	/*Procedimiento que agrega una imagen a la cola del buffer.
	Entrada: Objeto con la informacion de la imagen.
	Salida: void. */
	void insert(BMP elem)
	{
		if (count == buf_size)
			empty.wait();
		elements.push(elem);
		count += 1;
		full.signal();
		if (elem.getName() != "-1")
		{
			queue<BMP> aux = this->elements;
			int i = 1;
			cout << "+++++++++++++++++++++++++++++++++" << endl;
			cout << "Se inserto un nuevo elemento" << endl;
			cout << "Buffer: " << this->name << endl;
			cout << "Cant. elementos: " << this->count << endl;
			while (!aux.empty())
			{
				cout << i << ") " << aux.front().getName() << "." << endl;
				aux.pop();
				i++;
			}
			cout << "+++++++++++++++++++++++++++++++++" << endl << endl;
		}
	}
	/*Funcion que quita una imagen del buffer.
	Entrada: void.
	Salida: La primera imagen del buffer. */
	BMP remove()
	{
		if (count == 0)
			full.wait();
		BMP img = elements.front();
		elements.pop();
		count -= 1;
		empty.signal();
		if (img.getName() != "-1")
		{
			cout << "---------------------------------" << endl;
			cout << "Se quito un nuevo elemento" << endl;
			cout << "Buffer: " << this->name << endl;
			cout << "Cant. elementos: " << this->count << endl;
			cout << "---------------------------------" << endl
				 << endl;
		}
		return img;
	}
	void setName(string name)
	{
		this->name = name;
	}
	string getName()
	{
		return this->name;
	}
};
#endif
