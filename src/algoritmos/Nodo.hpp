#ifndef SRC_NODO_HPP_
#define SRC_NODO_HPP_

#include <cmath>
#include <iostream>
#include <string>
#include "..\Pieza.hpp"
using namespace std;

/**
 * Se recogen algunos de los algoritmos vistos en clase para la resolución del puzle
 */
namespace algoritmos{

/*
 * Clase Nodo
 * @author Raúl Alvarado Díaz
 * @author Javier Florido Cartolano
 * @author Iván Sánchez Cordero
 */
class Nodo {
private:
	Nodo *padre;
	Pieza *estado;
	string movimiento; //Movimiento que se ha realizado para llegar a ese estado
	int coste;
	int h;
	int id; //Número para diferenciar al nodo del resto

public:
	Nodo();
	Nodo(Nodo* padre, Pieza *estado, string movimiento, int h, int id);
	Nodo(Pieza* estado, int h);
	void setCoste(int coste);
	int getCoste();
	int getH();
	void setPadre(Nodo* padre);
	Nodo* getPadre();
	void setMovimiento(string movimiento);
	string getMovimiento();
	void setEstado(Pieza *p);
	Pieza* getEstado();
	int getId();
	void mostrar();
	~Nodo();
};
}

#endif /* SRC_NODO_HPP_ */
