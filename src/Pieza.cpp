/**
 * Implementacion de la clase Pieza
 */ 

#include "Pieza.hpp"  
	
signed int Pieza::getSignoMovimiento(Movimiento m){
	switch(m){
		case Movimiento::ABAJO		: 	return 1; // y positiva: abajo  
		case Movimiento::ARRIBA		: 	return -1; // y negativa: arriba

		case Movimiento::IZQUIERDA	: 	return -1; // x negativa: izquierda
		case Movimiento::DERECHA	: 	return 1; // x positiva: derecha

		default: return 0; // No moverse si el valor introducido es invalido.
	}
}

Pieza::TipoMovimiento Pieza::getTipoMovimiento(Movimiento m){
	if(m == Movimiento::ARRIBA || m == Movimiento::ABAJO) 			return TipoMovimiento::VERTICAL;
	else 															return TipoMovimiento::HORIZONTAL;
}

Pieza::Pieza(int origenX, int origenY, int ancho, int alto){
	definir(origenX, origenY, ancho, alto);
}

Pieza::Pieza(const Pieza &p){
	this->origenX = p.origenX; this->origenY = p.origenY;
    this->ancho = p.ancho; this->alto = p.alto;	
}

void Pieza::definir(int origenX, int origenY, int ancho, int alto) {
	this->origenX = origenX; this->origenY = origenY;
    this->ancho = ancho; this->alto = alto;
}

bool Pieza::operator==(Pieza &p) const {
	return (this->origenX == p.origenX) && (this->origenY == p.origenY) && (this->ancho == p.ancho) && (this->alto == p.alto);
}

void Pieza::getCoordenadasRotacion(int &nuevoAncho, int &nuevoAlto) const {
    // Rotacion hacia la derecha
	nuevoAncho = -alto;
	nuevoAlto = ancho;
}

void Pieza::rotar() { 
	int nuevoAncho, nuevoAlto;
	getCoordenadasRotacion(nuevoAncho, nuevoAlto);

	ancho = nuevoAncho;
	alto = nuevoAlto;
}

Pieza* Pieza::getPiezaRotada() const {
	Pieza* copia = new Pieza(*this);
		copia->rotar();
	return copia;
}

void Pieza::mover(Pieza::Movimiento dir) {
	if(Pieza::getTipoMovimiento(dir) == Pieza::TipoMovimiento::HORIZONTAL) 
		definir(getOrigenX() + Pieza::getSignoMovimiento(dir), getOrigenY(), getAncho(), getAlto());
	else
		definir(getOrigenX(), getOrigenY() + Pieza::getSignoMovimiento(dir), getAncho(), getAlto());
}

Pieza* Pieza::getPiezaMovida(Pieza::Movimiento dir) const{
	Pieza* copia = new Pieza(*this);
		copia->mover(dir);
	return copia;
}

int Pieza::getOrigenX() const {return origenX;}
int Pieza::getOrigenY() const {return origenY;}
int Pieza::getAncho() 	const {return ancho;}
int Pieza::getAlto() 	const {return alto;}

Pieza::Movimiento Pieza::getMovimientoReciproco(Movimiento m) const {
	switch(m){
		case Movimiento::ABAJO		: 	return Movimiento::ARRIBA;
		case Movimiento::ARRIBA		: 	return Movimiento::ABAJO;

		case Movimiento::IZQUIERDA	: 	return Movimiento::DERECHA;
		case Movimiento::DERECHA	: 	return Movimiento::IZQUIERDA;

		default: return Movimiento::ABAJO; // Callar el aviso del compilador asi...
	}
}
	
Pieza::~Pieza(){}