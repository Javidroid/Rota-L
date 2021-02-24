//============================================================================
// Name        : Tablero.cpp
// Author      : Raúl Alvarado Díaz, Javier Florido Cartolano & Iván Sánchez Cordero
// Version     :
// Copyright   : Proyecto IASI 2020/21
// Description : Hello World in C++, Ansi-style
//============================================================================

/**
 * Implementacion de la clase Pieza
 */

#include <iostream>
#include "Pieza.hpp"

using namespace std;


Pieza::Pieza(int origenX, int origenY, int ancho, int alto){
	this->origenX = origenX; this->origenY = origenY;
    this->ancho = ancho; this->alto = alto;
}


void Pieza::getCoordenadasRotacion(int &nuevaX, int &nuevaY) const {
    // Rotacion hacia la derecha
	nuevaX = alto;
	nuevaY = -ancho;
}

void Pieza::rotar(){
	int nuevaX, nuevaY;
	getCoordenadasRotacion(nuevaX, nuevaY);

	ancho = nuevaX;
	alto = nuevaY;
}

int Pieza::getOrigenX() const {return origenX;}
int Pieza::getOrigenY() const {return origenY;}
int Pieza::getAncho() 	const {return ancho;}
int Pieza::getAlto() 	const {return alto;}

Pieza::~Pieza(){}
