#ifndef SRC_PRIMEROMEJOR_HPP_
#define SRC_PRIMEROMEJOR_HPP_

#include <iostream>
#include <list>
#include <functional>
#include "Nodo.hpp"
#include "..\Pieza.hpp"
#include "..\Tablero.hpp"

using namespace std;

/**
 * Se recogen algunos de los algoritmos vistos en clase para la resolución del puzle
 */
namespace algoritmos{

/*
 * Generador de secuencias de movimientos que forman la solución del puzle
 * Se encuentran usando el algoritmo Primero Mejor y se muestran por pantalla
 * 
 * @author Raúl Alvarado Díaz
 * @author Javier Florido Cartolano
 * @author Iván Sánchez Cordero
 */
class PrimeroMejor {
private:
	list<Nodo*> *colaExpansion;
	list<Nodo*> *expandidos;
	Tablero *t;
	Nodo *solucion; //Será distinto de nullptr cuando se encuentre una
	int num; //Sirve para saber que id ponerle al siguiente hijo

	//Expande el nodo n descartando repetidos
	void expandir(Nodo* n);

	//Comprueba si un nodo está repetido y si se da el caso cambia los costes de sus hijos si le favorece
	bool repetido(Nodo* n);

	//Devuelve un string con todos los pasos seguidos hasta llegar al nodo n
	void pasosSeguidos(Nodo* n, string &s);

	//Muestra todos los nodos generados hasta el momento
	void mostrarTodo();
public:
	PrimeroMejor();
	PrimeroMejor(Tablero *t, Pieza *p);
	~PrimeroMejor();

	//Compara dos nodos en función de la suma de su h y coste para ordenar los abiertos
	bool compare(const Nodo *first,const Nodo *second);

	//Genera una secuencia de caracteres que es mostrada en pantalla que son los pasos necesarios
	// para resolver el tablero t
	void Principal();

};
}

#endif /* SRC_PRIMEROMEJOR_HPP_ */