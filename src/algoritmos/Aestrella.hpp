#ifndef SRC_AESTRELLA_HPP_
#define SRC_AESTRELLA_HPP_

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
 * Se encuentran usando el algoritmo A* y se muestran por pantalla
 * 
 * @author Raúl Alvarado Díaz
 * @author Javier Florido Cartolano
 * @author Iván Sánchez Cordero
 */
class Aestrella {
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

	//Cambia los costes de los hijos de n y tambien de sus descendientes si hay
	void cambiarCostesHijos(Nodo* n);

	//Muestra todos los nodos generados hasta el momento
	void mostrarTodo();
public:
	Aestrella();
	Aestrella(Tablero *t, Pieza *p);
	~Aestrella();

	//Compara dos nodos en función de la suma de su h y coste para ordenar los abiertos
	bool compare(const Nodo *first,const Nodo *second);

	//Genera una secuencia de caracteres que es mostrada en pantalla que son los pasos necesarios
	// para resolver el tablero t
	void Principal();

};
}

#endif /* SRC_AESTRELLA_HPP_ */