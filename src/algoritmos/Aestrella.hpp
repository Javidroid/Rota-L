/*
 * Aestrella.hpp
 *
 *  Created on: 28 mar. 2021
 *      Author: alumno
 */

#ifndef SRC_AESTRELLA_HPP_
#define SRC_AESTRELLA_HPP_

#include <iostream>
#include <list>
#include <functional>
#include "Nodo.hpp"
#include "..\Pieza.hpp"
#include "..\Tablero.hpp"

using namespace std;

namespace algoritmos{
	class Aestrella {
	private:
		list<Nodo*> *colaExpansion;
		list<Nodo*> *expandidos;
		Tablero *t;
		int num; //Sirve para saber que id ponerle al siguiente hijo

		//Expande el nodo n descartando repetidos
		bool expandir(Nodo* n);

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
