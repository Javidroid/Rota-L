//============================================================================
// Name        : LectorFicheroPuzle.cpp
// Author      : Raúl Alvarado Díaz, Javier Florido Cartolano & Iván Sánchez Cordero
// Version     :
// Copyright   : Proyecto IASI 2020/21
// Description : Hello World in C++, Ansi-style
//============================================================================

/**
 *  Implementacion de la clase Tablero
 */

#include <iostream>
#include "Tablero.hpp"

using namespace std;


Tablero::Tablero(int tam){
    n = tam;
    // Aplicar espacio vacio
    for(int i = 1; i < n-1; i++)
	    for(int j = 1; j < n-1; j++)
		    tableroFijo[i][j] = CASILLA_VACIA;

    // Aplicar bordes
    for(int i = 0; i < n; i++){
        tableroFijo[i][0] = CASILLA_MURO;
        tableroFijo[0][i] = CASILLA_MURO;
        tableroFijo[i][n-1] = CASILLA_MURO;
        tableroFijo[n-1][i] = CASILLA_MURO;
    }
}

Tablero::Tablero(int tam, tableroMatriz matriz){
	n = tam;
    // Copiar matriz
    for(int i = 1; i < n-1; i++)
	    for(int j = 1; j < n-1; j++)
		    tableroFijo[i][j] = matriz[i][j];
}

void Tablero::fijarObstaculo(int x, int y){
    tableroFijo[y][x] = CASILLA_MURO;
}

void Tablero::test_fijarObstaculosPrueba(){
	tableroFijo[1][2] = CASILLA_MURO;
	tableroFijo[2][2] = CASILLA_MURO;
	tableroFijo[4][4] = CASILLA_MURO;
	tableroFijo[4][3] = CASILLA_MURO;
}

void Tablero::limpiar(){
    for(int i = 0; i < n; i++)
	    for(int j = 0; j < n; j++)
		    tableroDinamico[i][j] = tableroFijo[i][j];
}

void Tablero::aplicarPieza(const Pieza &p){
	int desplz;

	// Dibujemos el vertice
	tableroDinamico[p.getOrigenY()][p.getOrigenX()] = CASILLA_PIEZA;

	// Aplica la parte horizontal de la L (x, columnas)
	// -> Vamos a suponer que POSITIVO: derecha y NEGATIVO: izquierda (como se ha hecho siempre xd)
	int horizontal = abs(p.getAncho());
	for(int h = 1; h <= horizontal; h++){
		desplz = (p.getAncho() > 0) ? h : -h; // Hacia donde dibujar...? Izquierda o derecha...?
		tableroDinamico[p.getOrigenY()][p.getOrigenX() + desplz] = CASILLA_PIEZA;
	}

	// Aplica la parte vertical de la L
	// -> Vamos a suponer que POSITIVO: arriba y NEGATIVO: abajo (xd)
	int vertical = abs(p.getAlto());
	for(int v = 1; v <= vertical; v++){
		desplz = (p.getAlto() > 0) ? v : -v; // Hacia donde dibujar...? Arriba o abajo...?
		tableroDinamico[p.getOrigenY() - desplz][p.getOrigenX()] = CASILLA_PIEZA; // El - para que se dibuje como hemos dicho >:v
	}
}

bool Tablero::piezaRotable(const Pieza &p){
	if(saleDeLosLimitesAlRotar(p)) return false;

	return !chocaAlRotar(p);
}

bool Tablero::saleDeLosLimites(int coordenadaPicoHorizontal, int coordenadaPicoVertical){
	if(coordenadaPicoHorizontal < 0 || coordenadaPicoHorizontal >= n
		|| coordenadaPicoVertical < 0 || coordenadaPicoVertical >= n)
			return true;
	else return false;
}

bool Tablero::saleDeLosLimitesAlRotar(const Pieza &p){
	int posibleNuevaX, posibleNuevaY;
    p.getCoordenadasRotacion(posibleNuevaX, posibleNuevaY);

	int coordenadaPicoHorizontal = p.getOrigenX() + posibleNuevaX;
	int coordenadaPicoVertical = p.getOrigenY() + posibleNuevaY;

	return saleDeLosLimites(coordenadaPicoHorizontal, coordenadaPicoVertical);
}

bool Tablero::chocaAlRotar(const Pieza &p){
	int posibleNuevaX, posibleNuevaY;
    p.getCoordenadasRotacion(posibleNuevaX, posibleNuevaY);

	const int signoX = (p.getAncho() 			> 0) ? 1 : -1;
	const int signoY = (p.getAlto() 			> 0) ? 1 : -1;
	const int signoNuevaX = (posibleNuevaX 		> 0) ? 1 : -1;
	const int signoNuevaY = (posibleNuevaY 		> 0) ? 1 : -1;

	bool choca = false;
	int dx, dy; // Se usara para calcular los limites del area encerrada al rotar

	// Nos basamos en que | Ancho actual | = | Nuevo alto | (Horizontal -> Vertical) y | Alto actual | = | Nuevo ancho | (Vertical -> Horizontal)

	// Comprobar cuadrante horizontal -> vertical
	dx = 1;
	while(!choca && dx <= abs(p.getAncho())){
		dy = 1;
		while(dy <= abs(p.getAncho())){
			if(tableroFijo[p.getOrigenY() - signoNuevaY*dy] // Resto para orientar Y positivba hacia arriba (hacia menores valores en la matriz)
							[p.getOrigenX() + signoX*dx] == CASILLA_MURO){
				choca = true;
				std::cout << "[DEBUG]: Se detecta colision H->V en la casilla (x=" << p.getOrigenX() + signoX*dx << ", y=" << p.getOrigenY() - signoNuevaY*dy << std::endl;
				break;
			}
			dy++;
		}
		dx++;
	}
	if(choca) return true;

	// Comprobar cuadrante vertical -> horizontal
	dx = 1;
	while(!choca && dx <= abs(p.getAlto())){
		dy = 1;
		while(dy <= abs(p.getAlto())){
			if(tableroFijo[p.getOrigenY() - signoY*dy] // Resto para orientar Y positivba hacia arriba (hacia menores valores en la matriz)
				[p.getOrigenX() + signoNuevaX*dx] == CASILLA_MURO){
				choca = true;
				std::cout << "[DEBUG]: Se detecta colision V->H en la casilla (x=" << p.getOrigenX() + signoNuevaX*dx << ", y=" << p.getOrigenY() - signoY*dy << std::endl;
				break;
			}
			dy++;
		}
		dx++;
	}

    return choca;
}

void Tablero::dibujar(){
	for(int i = 0; i< n; i++){
		for(int j = 0; j < n; j++){
			std::cout << tableroDinamico[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void Tablero::dibujar(const Pieza &p){
    limpiar();
	aplicarPieza(p);
    // aplicarObstaculos();
	dibujar();
}

Tablero::~Tablero(){}
