/*
 * Aestrella.cpp
 *
 *  Created on: 28 mar. 2021
 *      Author: alumno
 */
#include "Aestrella.hpp"
using namespace std;

namespace algoritmos{
	Aestrella::Aestrella() {
	colaExpansion = new list<Nodo*>();
	expandidos = new list<Nodo*>();
	t = nullptr;
	num = 1;
}

Aestrella::Aestrella(Tablero *t, Pieza *p){
	colaExpansion = new list<Nodo*>();
	expandidos = new list<Nodo*>();
	this->t = t;
	colaExpansion->push_back(new Nodo(p,t->h(*p)));
	num = 1;
}

Aestrella::~Aestrella() {
	Nodo *n;
	while(!colaExpansion->empty()){
		n = colaExpansion->front();
		colaExpansion->pop_front();
		delete n;
	}
	while(!expandidos->empty()){
		n = expandidos->front();
		expandidos->pop_front();
		delete n;
	}
	delete t;

	// Borrar las estructuras de datos
	delete colaExpansion;
	delete expandidos;
}

bool Aestrella::compare(const Nodo * first, const Nodo * second){
	Nodo * n1 = (Nodo*) first;
	Nodo *n2 = (Nodo*) second;
	return (n1->getH()+  n1->getCoste()) < (n2->getH()+n2->getCoste());
}

bool Aestrella::expandir(Nodo* n){
	Pieza * p = n->getEstado();
	Pieza *aux = nullptr;
	Nodo *nuevo;
	for(int i = 0; i < 5; i++){
		aux = nullptr;
		switch(i){
		case 0:
			if(t->puedeMover(*p,Pieza::Movimiento::ABAJO)){
				aux = new Pieza(*p);
				aux->mover(Pieza::Movimiento::ABAJO);
				nuevo = new Nodo(n,aux,"ABAJO",t->h(*aux),num);
			}
			break;
		case 1:
			if(t->puedeMover(*p,Pieza::Movimiento::ARRIBA)){
				aux = new Pieza(*p);
				aux->mover(Pieza::Movimiento::ARRIBA);
				nuevo = new Nodo(n,aux,"ARRIBA",t->h(*aux),num);
			}
			break;
		case 2:
			if(t->puedeMover(*p,Pieza::Movimiento::DERECHA)){
				aux = new Pieza(*p);
				aux->mover(Pieza::Movimiento::DERECHA);
				nuevo = new Nodo(n,aux,"DERECHA",t->h(*aux),num);
			}
			break;
		case 3:
			if(t->puedeMover(*p,Pieza::Movimiento::IZQUIERDA)){
				aux = new Pieza(*p);
				aux->mover(Pieza::Movimiento::IZQUIERDA);
				nuevo = new Nodo(n,aux,"IZQUIERDA",t->h(*aux),num);
			}
			break;
		case 4:
			if(t->puedeRotar(*p)){
				aux = new Pieza(*p);
				aux->rotar();
				nuevo = new Nodo(n,aux,"ROTAR",t->h(*aux),num);
			}
			break;
		}
		if(aux != nullptr){
			if(!repetido(nuevo)){
				colaExpansion->push_back(nuevo);
				num ++;
				if(t->h(*aux) == 0){
					return true;
				}
			}
			else{
				delete nuevo;
			}
		}
	}
	return false;
}


void Aestrella::Principal(){
	bool fin = false;
	Nodo *n;
	while(!fin){
		using namespace std::placeholders;
		colaExpansion->sort(std::bind(&Aestrella::compare,this,_1,_2));
		mostrarTodo();
		if(expandir(colaExpansion->front())){
			fin = true;
			string s = "";
			pasosSeguidos(colaExpansion->back(),s);
			cout<<s;
		}
		else{
			n = colaExpansion->front();
			colaExpansion->pop_front();
			expandidos->push_back(n);
			if(colaExpansion->empty()){
				fin = true;
				cout<<"No se ha podido encontrar una solución :(";
			}
		}
	}

}




bool Aestrella::repetido(Nodo* n){
	Pieza* p = n->getEstado();
	Pieza* aux = nullptr;
	bool encontrado = false;
	for(list<Nodo*>::iterator it = colaExpansion->begin(); it != colaExpansion->end() && !encontrado; it++){
		Nodo *n2 = *it;
		aux = n2->getEstado();
		if(*p==*aux){
			encontrado = true;
			if(n2->getCoste() < n->getCoste()){
				n->setCoste(n2->getCoste());
				n->setMovimiento(n2->getMovimiento());
				n->setPadre(n2->getPadre());
				cambiarCostesHijos(n);
			}
		}
	}
	for(list<Nodo*>::iterator it = expandidos->begin(); it != expandidos->end() && !encontrado; it++){
		Nodo *n2 = *it;
		aux = n2->getEstado();
		if(*p==*aux){
			encontrado = true;
			if(n2->getCoste() < n->getCoste()){
				n->setCoste(n2->getCoste());
				n->setMovimiento(n2->getMovimiento());
				n->setPadre(n2->getPadre());
				cambiarCostesHijos(n);
			}
		}
	}
	return encontrado;
}

void Aestrella::pasosSeguidos(Nodo* n, string &s){
	if(n != nullptr){
		pasosSeguidos(n->getPadre(), s);
		s = s + n->getMovimiento() + " ";
	}
}

void Aestrella::cambiarCostesHijos(Nodo* n){
	Nodo *n2;
	for(list<Nodo*>::iterator it = colaExpansion->begin(); it != colaExpansion->end() ; it++){
		n2 = *it;
		if(n2->getPadre() == n){
			n2->setCoste(n->getCoste()+1);
			cambiarCostesHijos(n2);
		}
	}
	for(list<Nodo*>::iterator it = expandidos->begin(); it != expandidos->end() ; it++){
		n2 = *it;
		if(n2->getPadre() == n){
			n2->setCoste(n->getCoste()+1);
			cambiarCostesHijos(n2);
		}
	}
}

void Aestrella::mostrarTodo(){
	Nodo *n2;
	cout<<"ABIERTOS"<<endl;
	for(list<Nodo*>::iterator it = colaExpansion->begin(); it != colaExpansion->end() ; it++){
		n2 = *it;
		n2->mostrar();
		cout<<", ";
	}

	cout<<endl<<"CERRADOS"<<endl;
	for(list<Nodo*>::iterator it = expandidos->begin(); it != expandidos->end() ; it++){
		n2 = *it;
		n2->mostrar();
		cout<<", ";
	}
	cout<<endl<<endl;
}
}

