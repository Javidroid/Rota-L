#define DEBUG // Con desactivar esta definicion ya se deshabilitan todas las pruebas

#include "Tablero.hpp"
#include "Pieza.hpp"
#include "LectorFicheroPuzle.hpp"

#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{	
	/**
	 * PRUEBA DE IDENTIFICADOR DE PIEZA
	 * ( El constructor de LectorFicheroPuzle no debe ponerse a leer ningun fichero )
	 **/
	LectorFicheroPuzle * lec = LectorFicheroPuzle::getSingleton();
		Pieza* p = lec->obtenerPieza();
		Tablero *t = lec->obtenerTablero();
	delete lec;

	/**
	 * MODO INTERACTIVO
	 */
	cout << "=========================================" << endl;
	cout << "===========[MODO INTERACTIVO]============" << endl;
	cout << "=========================================" << endl;
	bool continuarModoInteractivo = true;
	Pieza::Movimiento dir;
	int decision;

	bool banderaRealizarMovimiento;
	bool banderaRealizarRotacion;
	while(continuarModoInteractivo){
		t->dibujar(*p);
		cout << "Introduce la direccion en la que quieras moverte:" << endl;
			if(t->puedeMover(*p, Pieza::Movimiento::ABAJO)) 	cout << "\t[1]: ABAJO" << endl;
			if(t->puedeMover(*p, Pieza::Movimiento::ARRIBA)) 	cout << "\t[2]: ARRIBA" << endl;
			if(t->puedeMover(*p, Pieza::Movimiento::IZQUIERDA)) cout << "\t[3]: IZQUIERDA" << endl;
			if(t->puedeMover(*p, Pieza::Movimiento::DERECHA)) 	cout << "\t[4]: DERECHA" << endl;
			if(t->puedeRotar(*p)) 								cout << "\t[5]: ROTAR A LA DERECHA" << endl;
		cin >> decision;
			banderaRealizarMovimiento = false;
			banderaRealizarRotacion = false;
			switch(decision){
				case 1: dir = Pieza::Movimiento::ABAJO; 	banderaRealizarMovimiento = true; break;
				case 2: dir = Pieza::Movimiento::ARRIBA; 	banderaRealizarMovimiento = true; break;
				case 3: dir = Pieza::Movimiento::IZQUIERDA; banderaRealizarMovimiento = true; break;
				case 4: dir = Pieza::Movimiento::DERECHA; 	banderaRealizarMovimiento = true; break;

				case 5: 									banderaRealizarRotacion = true; break;
				
				default: continuarModoInteractivo = false;
			}

		if(banderaRealizarMovimiento){
			if(t->puedeMover(*p, dir)) 
				p->mover(dir);
		}else if(banderaRealizarRotacion){
			if(t->puedeRotar(*p)) 
				p->rotar();
		}else cout << "Adios :(" << endl;
	}

	return 0;
}