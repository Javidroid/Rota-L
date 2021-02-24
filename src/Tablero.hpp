//============================================================================
// Name        : Tablero.hpp
// Author      : Raúl Alvarado Díaz, Javier Florido Cartolano & Iván Sánchez Cordero
// Version     :
// Copyright   : Proyecto IASI 2020/21
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef TABLERO_H
#define TABLERO_H

#include "Pieza.hpp"
#include <cmath>
#include <iostream>


#define TABLERO_TAM 100 // Capacidad del tablero: TABLERO_TAM * TABLERO_TAM casillas

#define CASILLA_VACIA 0
#define CASILLA_MURO 1
#define CASILLA_PIEZA 2
#define CASILLA_META 3

typedef int tableroMatriz[TABLERO_TAM][TABLERO_TAM];

class Tablero  {
private:
	int n;
	tableroMatriz tableroFijo; // Contiene la disposicion de los obstaculos cargada al leer el fichero.
	tableroMatriz tableroDinamico; // Se dibujaran las posicion de L y META en este tablero
public:
	Tablero(int tam);
	Tablero(int tam, tableroMatriz matriz);
	~Tablero();

	void fijarObstaculo(int x, int y);

	void test_fijarObstaculosPrueba();

	/**
	 * Reestablece el tablero dinamico al tablero fijo
	 */
	void limpiar();

	/**
	 * Aplica la pieza dada al tablero dinamico
	 */
	void aplicarPieza(const Pieza &p);

	/**
	 * Comprueba si la posicion y dimensiones actuales de la pieza se salen del tablero
	 * 
	 * Devuelve true si la pieza se saldria de los limites al aplicarse en el tablero
	 * 			false en caso contrario
	 * 
	 *  ! Es muy importante corregir esta posicion antes de hacer cualquier transformacion o evaluacion a la pieza !
	 * 
	 * 
	 * 	NO deberia usarse para controlar que la pieza no este mal colocada inicialmente porque el enunciado supone que todos los ficheros son correctos
	 */
	bool saleDeLosLimites(int coordenadaPicoHorizontal, int coordenadaPicoVertical);

	/**
	 * Comprueba que la pieza puede rotar hacia la derecha en la posicion en la que esta
	 * Rotar sin evaluar previamente esta funcion puede dar lugar a estados incorrectos
	 * 
	 * Devuelve true si la pieza puede rotarse en esa posicion.
	 * 			false en caso contrario
	 */ 
	bool piezaRotable(const Pieza &p);
		/**
		 * Comprueba si la pieza se sale del tablero al rotar.
		 * Continuar evaluando sin antes comprobar esta funcion puede dar lugar a accesos fuera de la matriz (violacion de segmento)
		 * 
		 * Devuelve true si la pieza se sale de los limites si rota.
		 * 			false en caso contrario
		 * 
		 * ! Es muy importante que la pieza NO rote si esto devuelve true !
		 */
		bool saleDeLosLimitesAlRotar(const Pieza &p);

		/**
		 *  Comprueba si la pieza colisiona con un muro al rotar
		 * 	Hay que asegurarse de que la pieza no salga de los limites del tablero al rotar
		 * 
		 * 	Devuelve true si la pieza va a chocar si rota
		 * 			 false en caso contrario
		 */
		bool chocaAlRotar(const Pieza &p);
	
	/**
	* Comprueba si alguna casilla de la pieza coincide con algun muro
	*/
	//	bool posicionPosible(const Pieza &p);
	//	X -> Descarto la implementacion de este metodo porque comprobar que las transformaciones son validas antes de aplicarlas sera mas eficiente.

	void dibujar();
	void dibujar(const Pieza &p); // Tambien tomar capa de obstaculos


};
#endif
