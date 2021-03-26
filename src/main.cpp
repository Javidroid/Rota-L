#include "Tablero.hpp"
#include "Pieza.hpp"
#include "LectorFicheroPuzle.hpp"

#include <fstream>

#define DEBUG // Con desactivar esta definicion ya se deshabilitan todas las pruebas

#ifdef DEBUG
//	#define DEBUG_ROTACIONES
	#define DEBUG_MOVIMIENTOS
#endif

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
#ifdef DEBUG_ROTACIONES
	/**
	 * PROBAR ROTACIONES (giro completo)
	 */
	t->dibujar(*p);
	int r; // Fases de la rotacion
	for(r = 1; r <= 4; r++){
		if(t->piezaRotable(*p)) p->rotar();
		else { cout << "No puede hacer la rotacion numero " << r << endl; break; }

		cout << "------------------" << endl;
		t->dibujar(*p);
	}
	if(r > 4) cout << endl << "Se ha podido hacer una rotacion completa con esta configuracion :O" << endl;
#endif

#ifdef DEBUG_MOVIMIENTOS
	/**
	 * PROBAR MOVIMIENTOS
	 */
	bool banderaBucleMenu = true;
	bool banderaMovimiento;
	Pieza::Movimiento dir;
	int decision;
	while(banderaBucleMenu){
		t->dibujar(*p);
		cout << "Introduce la direccion en la que quieras moverte:" << endl;
			cout << "\t[1]: ABAJO" << endl;
			cout << "\t[2]: ARRIBA" << endl;
			cout << "\t[3]: IZQUIERDA" << endl;
			cout << "\t[4]: DERECHA" << endl;
			cout << "\t[5]: ROTAR A LA DERECHA" << endl;
		cin >> decision;
			switch(decision){
				case 1: dir = Pieza::Movimiento::ABAJO; 	banderaMovimiento = true; break;
				case 2: dir = Pieza::Movimiento::ARRIBA; 	banderaMovimiento = true; break;
				case 3: dir = Pieza::Movimiento::IZQUIERDA; banderaMovimiento = true; break;
				case 4: dir = Pieza::Movimiento::DERECHA; 	banderaMovimiento = true; break;

				case 5: banderaMovimiento = false; break; // Rotar
				default: banderaBucleMenu = false;
			}

			if(banderaMovimiento){
				if(t->puedeMover(*p, dir)){
					cout << "PUEDES MOVERTE :D" << endl;
					p->mover(dir);
				}else cout << "NO PUEDES MOVERTE >_<" << endl;				
			}else{
				if(t->puedeRotar(*p)){
					cout << "ROTANDO..." << endl;
					p->rotar();
				}else cout << "NO PUEDES ROTAR >_<" << endl;
			}
	}


	return 0;
}
#endif