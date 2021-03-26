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
	 */
	void limpiar(); 

	/**
	 * Aplica la pieza dada al tablero dinamico
	 * @param p (ENTRADA)
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

	 * @param coordenadaPicoHorizontal (ENTRADA) 
	 * @param coordenadaPicoVertical (ENTRADA)
	 * @return true si la pieza se saldria de los limites al aplicarse en el tablero; false en caso contrario
	 */
	bool saleDeLosLimites(int coordenadaPicoHorizontal, int coordenadaPicoVertical) const ;

	/**
	 * Comprueba que la pieza puede rotar hacia la derecha en la posicion en la que esta
	 * Rotar sin evaluar previamente esta funcion puede dar lugar a estados incorrectos
	 * 
	 * @param p (ENTRADA)
	 * @return true si la pieza puede rotarse en esa posicion; false en caso contrario
	 */ 
	bool puedeRotar(const Pieza &p) const ;

	/**
	 * @brief Comprueba que la pieza puede rotar sin encontrarse obstaculos de por medio

	 * @param p (ENTRADA)
	 * @return true Si la pieza puede rotarse ; false en caso contrario
	 */
	bool puedeRotarEstrictamente(const Pieza &p) const ;
		/**
		 * Comprueba si la pieza se sale del tablero al rotar.
		 * Continuar evaluando sin antes comprobar esta funcion puede dar lugar a accesos fuera de la matriz (violacion de segmento)
		 * 
		 * @param p (ENTRADA)
		 * @return true si la pieza se sale de los limites si rota (y no deberia hacerse ninguna otra evaluacion); false en caso contrario
		 */
		bool saleDeLosLimitesAlRotar(const Pieza &p) const ;

		/**
		 * Comprueba si la pieza va a estar en una posicion IMPOSIBLE al rotar
		 * 
		 * @param p (ENTRADA) La pieza en cuestion
		 * @return true si la pieza choca al rotar ; false en caso contrario
		 */
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
	 * @param p (ENTRADA)
	 * @param dir (ENTRADA)
	 * @return true si el movimiento es posible; false en caso contrario
	 */
	bool puedeMover(const Pieza &p, Pieza::Movimiento dir) const ;

		/**
	 	* Comprueba si la pieza se saldria de los limites al moverse en la direccion especificada
	 	* @param p (ENTRADA)
	 	* @param dir (ENTRADA)
	 	* @return true si la pieza va a salir de los limites (y no deberia hacerse ninguna otra evaluacion); false en caso contrario
		 */		
		bool saleDeLosLimitesAlMover(const Pieza &p, Pieza::Movimiento dir) const ;

		/**
	 	* Comprueba si la pieza va a estar en una posicion IMPOSIBLE al moverse.
		* @param p (ENTRADA)
		* @param dir (ENTRADA)
	 	* @return true si colisiona al moverse; false en caso contrario
	 	*/		
		bool chocaAlMover(const Pieza &p, Pieza::Movimiento dir) const ;
	
	/**
	 * Muestra el tablero DIBUJABLE por pantalla. Debe haberse llamado previamente a limpiar() para que el tablero dibujable tenga la base del tablero.
	 * Opcionalmente puede llamarse a aplicarPieza() si quiere dibujarse tambien
	 */
	void dibujar();

	/**
	 * Dibuja el tablero con sus obstaculos, la pieza y la meta. No necesita llamadas previas
	 * @param p (ENTRADA) La pieza que va a ser dibujada en el tablero
	 */
	void dibujar(const Pieza &p);


};
#endif