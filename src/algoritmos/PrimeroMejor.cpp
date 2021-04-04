/*
 * PrimeroMejor.cpp
 * 
 * Implementacion de la clase PrimeroMejor
 * @author Raúl Alvarado Díaz
 * @author Javier Florido Cartolano
 * @author Iván Sánchez Cordero
 */

#include "PrimeroMejor.hpp"
using namespace std;

namespace algoritmos
{
	PrimeroMejor::PrimeroMejor()
	{
		colaExpansion = new list<Nodo *>();
		expandidos = new list<Nodo *>();
		t = nullptr;
		solucion = nullptr;
		num = 1;
	}

	PrimeroMejor::PrimeroMejor(Tablero *t, Pieza *p)
	{
		colaExpansion = new list<Nodo *>();
		expandidos = new list<Nodo *>();
		this->t = t;
		colaExpansion->push_back(new Nodo(p, t->h(*p)));
		solucion = nullptr;
		num = 1;
	}

	bool PrimeroMejor::compare(const Nodo *first, const Nodo *second)
	{
		Nodo *n1 = (Nodo *)first;
		Nodo *n2 = (Nodo *)second;
		return (n1->getH() < n2->getH());
	}

	void PrimeroMejor::expandir(Nodo *n)
	{
		Pieza *p = n->getEstado();
		Pieza *aux = nullptr;
		Nodo *nuevo;
		for (int i = 0; i < 5; i++)
		{
			aux = nullptr;
			switch (i)
			{
			case 0:
				if (t->puedeMover(*p, Pieza::Movimiento::ABAJO))
				{
					aux = new Pieza(*p);
					aux->mover(Pieza::Movimiento::ABAJO);
					nuevo = new Nodo(n, aux, "ABAJO", t->h(*aux), num);
				}
				break;
			case 1:
				if (t->puedeMover(*p, Pieza::Movimiento::ARRIBA))
				{
					aux = new Pieza(*p);
					aux->mover(Pieza::Movimiento::ARRIBA);
					nuevo = new Nodo(n, aux, "ARRIBA", t->h(*aux), num);
				}
				break;
			case 2:
				if (t->puedeMover(*p, Pieza::Movimiento::DERECHA))
				{
					aux = new Pieza(*p);
					aux->mover(Pieza::Movimiento::DERECHA);
					nuevo = new Nodo(n, aux, "DERECHA", t->h(*aux), num);
				}
				break;
			case 3:
				if (t->puedeMover(*p, Pieza::Movimiento::IZQUIERDA))
				{
					aux = new Pieza(*p);
					aux->mover(Pieza::Movimiento::IZQUIERDA);
					nuevo = new Nodo(n, aux, "IZQUIERDA", t->h(*aux), num);
				}
				break;
			case 4:
				if (t->puedeRotar(*p))
				{
					aux = new Pieza(*p);
					aux->rotar();
					nuevo = new Nodo(n, aux, "ROTAR", t->h(*aux), num);
				}
				break;
			}
			if (aux != nullptr)
			{
				if (!repetido(nuevo))
				{
					colaExpansion->push_back(nuevo);
					num++;
					if (t->h(*aux) == 0)
					{
						solucion = nuevo;
					}
				}
				else
				{
					delete nuevo;
				}
			}
		}
	}

	void PrimeroMejor::Principal()
	{
		bool fin = false;
		Nodo *n;
		while (!fin)
		{
			using namespace std::placeholders;
			colaExpansion->sort(std::bind(&PrimeroMejor::compare, this, _1, _2));
			mostrarTodo();

			if (solucion != nullptr)
			{
				fin = true;
				string s = "";
				pasosSeguidos(solucion, s);
				cout << s;
			}
			else
			{
				expandir(colaExpansion->front());
				n = colaExpansion->front();
				colaExpansion->pop_front();
				expandidos->push_back(n);
				if (colaExpansion->empty())
				{
					fin = true;
					cout << "No se ha podido encontrar una solución :(";
				}
			}
		}
	}

	bool PrimeroMejor::repetido(Nodo *n)
	{
		Pieza *p = n->getEstado();
		Pieza *aux = nullptr;
		bool encontrado = false;
		for (list<Nodo *>::iterator it = colaExpansion->begin(); it != colaExpansion->end() && !encontrado; it++)
		{
			Nodo *n2 = *it;
			aux = n2->getEstado();
			if (*p == *aux)
			{
				encontrado = true;
			}
		}
		for (list<Nodo *>::iterator it = expandidos->begin(); it != expandidos->end() && !encontrado; it++)
		{
			Nodo *n2 = *it;
			aux = n2->getEstado();
			if (*p == *aux)
			{
				encontrado = true;
			}
		}
		return encontrado;
	}

	void PrimeroMejor::pasosSeguidos(Nodo *n, string &s)
	{
		if (n != nullptr)
		{
			pasosSeguidos(n->getPadre(), s);
			s = s + n->getMovimiento() + " ";
		}
	}

	void PrimeroMejor::mostrarTodo()
	{
		Nodo *n2;
		cout << "ABIERTOS" << endl;
		for (list<Nodo *>::iterator it = colaExpansion->begin(); it != colaExpansion->end(); it++)
		{
			n2 = *it;
			n2->mostrarPM();
			cout << ", ";
		}

		cout << endl
			 << "CERRADOS" << endl;
		for (list<Nodo *>::iterator it = expandidos->begin(); it != expandidos->end(); it++)
		{
			n2 = *it;
			n2->mostrarPM();
			cout << ", ";
		}
		cout << endl
			 << endl;
	}

	PrimeroMejor::~PrimeroMejor()
	{
		Nodo *n;
		while (!colaExpansion->empty())
		{
			n = colaExpansion->front();
			colaExpansion->pop_front();
			delete n;
		}
		delete colaExpansion;
		while (!expandidos->empty())
		{
			n = expandidos->front();
			expandidos->pop_front();
			delete n;
		}
		delete expandidos;
	}
}
