/**
 * 	Definicion de la clase Tablero
 */
#ifndef TABLERO_H
#define TABLERO_H

#include "Pieza.hpp"
#include <cmath>
#include <iostream>


#define TABLERO_TAM 10 // Capacidad del tablero: TABLERO_TAM * TABLERO_TAM casillas

#define CASILLA_VACIA 0
#define CASILLA_MURO 1
#define CASILLA_PIEZA 2
#define CASILLA_META 3

typedef int tableroMatriz[TABLERO_TAM][TABLERO_TAM];

class Tablero  {
private:
	int n;
	tableroMatriz tableroFijo; // Contiene la disposicion de los obstaculos cargada al leer el fichero.
	tableroMatriz tableroDibujable; // Se dibujaran las posicion de L y META en este tablero (borrar)
public:
	Tablero(int tam);
	Tablero(int tam, tableroMatriz matriz);
	~Tablero();

	void fijarObstaculo(int x, int y);
	void test_fijarObstaculosPrueba();

	/**
	 * Reestablece el tablero dinamico al tablero fijo
	 * TODO: borrar
	 */
	void limpiar(); 

	/**
	 * Aplica la pieza dada al tablero dinamico
	 * ENTRADA: p
	 */
	void aplicarPieza(const Pieza &p);

	/**
	 * @brief Comprueba si existe obstaculo en la casilla indicada
	 * 
	 * @param x (ENTRADA)
	 * @param y (ENTRADA)
	 * @return true si hay un obstaculo en x,y ; false en caso contrario
	 */
	bool hayObstaculo(int x, int y) const ;

	/**
	 * Evalua si la pieza esta en una posicion del tablero posible
	 * @param p (ENTRADA) La pieza a evaluar
	 * @return true, si la pieza NO colisiona con ningun obstaculo ; false en caso contrario
	 */
	bool posicionPosible(const Pieza &p) const ;
	
	/**
	 * Evalua si la pieza esta en una posicion del tablero posible
	 * @param origenX (ENTRADA) Coordenada X del vertice de la pieza
	 * @param origenY (ENTRADA) Coordenada Y del vertice de la pieza
	 * @param ancho (ENTRADA) anchura de la pieza
	 * @param alto (ENTRADA) altura de la pieza
	 * @return true, si la pieza NO colisiona con ningun obstaculo ; false en caso contrario
	 */
	bool posicionPosible(int origenX, int origenY, int ancho, int alto) const ;

	/**
	 * Comprueba si la posicion y dimensiones actuales de la pieza se salen del tablero
	 *  ! Es muy importante corregir esta posicion antes de hacer cualquier transformacion o evaluacion a la pieza !
	 * 	NO deberia usarse para controlar que la pieza no este mal colocada inicialmente porque el enunciado supone que todos los ficheros son correctos
	 * 	DEVUELVE: true si la pieza se saldria de los limites al aplicarse en el tablero; false en caso contrario
	 * 	ENTRADA: coordenadaPicoHorizontal, coordenadaPicoVertical
	 */
	bool saleDeLosLimites(int coordenadaPicoHorizontal, int coordenadaPicoVertical) const ;

	/**
	 * Comprueba que la pieza puede rotar hacia la derecha en la posicion en la que esta
	 * Rotar sin evaluar previamente esta funcion puede dar lugar a estados incorrectos
	 * 
	 * DEVUELVE: true si la pieza puede rotarse en esa posicion; false en caso contrario
	 * ENTRADA: p
	 */ 
	bool puedeRotar(const Pieza &p) const ;

	/**
	 * @brief Comprueba que la pieza puede rotar sin encontrarse obstaculos de por medio
	 * Rotar 
	 * 
	 * @param p (ENTRADA) Pieza a rot
	 * @return true Si la pieza puede rotarse
	 * @return false En caso contrario
	 */
	bool puedeRotarEstrictamente(const Pieza &p) const ;
		/**
		 * Comprueba si la pieza se sale del tablero al rotar.
		 * Continuar evaluando sin antes comprobar esta funcion puede dar lugar a accesos fuera de la matriz (violacion de segmento)
		 * 
		 * DEVUELVE: true si la pieza se sale de los limites si rota; false en caso contrario
		 * 		 * ! Es muy importante que la pieza NO rote si esto devuelve true !
		 * ENTRADA: p
		 */
		bool saleDeLosLimitesAlRotar(const Pieza &p) const ;

		bool chocaAlRotar(const Pieza &p) const ;
		/**
		 *  Comprueba si la pieza colisiona con un muro al rotar
		 * 	Hay que asegurarse de que la pieza no salga de los limites del tablero al rotar
		 * 
		 * 	DEVUELVE: true si la pieza va a chocar si rota; false en caso contrario
		 * 	ENTRADA: p
		 */
		bool chocaAlRotarEstrictamente(const Pieza &p) const ;

	
	/**
	 * Comprueba si la pieza puede moverse tantas veces en la direccion que se especifique.
	 * DEVUELVE: true si el movimiento es posible; false en caso contrario
	 * ENTRADA: p, dir, numeroCasillas
	 */
	bool puedeMover(const Pieza &p, Pieza::Movimiento dir) const ;

		bool saleDeLosLimitesAlMover(const Pieza &p, Pieza::Movimiento dir) const ;
		bool chocaAlMover(const Pieza &p, Pieza::Movimiento dir) const ;
	
	/**
	 * Muestra el tablero DIBUJABLE por pantalla. Debe haberse llamado previamente a limpiar() para que el tablero dibujable tenga la base del tablero.
	 * Opcionalmente puede llamarse a aplicarPieza() si quiere dibujarse tambien
	 */
	void dibujar();

	/**
	 * Dibuja el tablero con sus obstaculos, la pieza y la meta. No necesita llamadas previas
	 * ENTRADA: p
	 */
	void dibujar(const Pieza &p);


};
#endif