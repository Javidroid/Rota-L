/*
 * Nodo.cpp
 * 
 * Implementacion de la clase Nodo
 * @author Raúl Alvarado Díaz
 * @author Javier Florido Cartolano
 * @author Iván Sánchez Cordero
 */

#include "Nodo.hpp"

using namespace std;
namespace algoritmos{
Nodo::Nodo() {
	estado = nullptr;
	padre = nullptr;
	movimiento = "";
	coste = 0;
	h = 99;
	id = 0;
}

Nodo::~Nodo() {delete estado;}

Nodo::Nodo(Nodo* padre, Pieza *estado, string movimiento, int h, int id){
	this->estado = estado;
	this->padre = padre;
	this->movimiento = movimiento;
	this->h = h;
	this->id = id;
	if(padre != nullptr)
		coste = padre->getCoste()+1;
	else coste = 0;
}

Nodo::Nodo(Pieza * estado, int h){
	this->estado = estado;
	padre = nullptr;
	movimiento = "";
	coste = 0;
	id = 0;
	this->h = h;
}

void Nodo::setCoste(int coste){
	this->coste = coste;
}

int Nodo::getCoste(){
	return coste;
}

int Nodo::getH(){
	return h;
}

void Nodo::setPadre(Nodo* padre){
	this->padre = padre;
}

Nodo* Nodo::getPadre(){
	return padre;
}

void Nodo::setMovimiento(string movimiento){
	this->movimiento = movimiento;
}

string Nodo::getMovimiento(){
	return movimiento;
}

void Nodo::setEstado(Pieza *p){
	estado = p;
}

Pieza* Nodo::getEstado(){
	return estado;
}

int Nodo::getId(){
	return id;
}

void Nodo::mostrar(){
	string idPadre;
	if(padre != nullptr){
		idPadre = to_string(padre->getId());
	}
	else{
		idPadre = "null";
	}
	cout<<id<<"(^"<<idPadre<<","<<h<<"+"<<coste<<")";
}
}
