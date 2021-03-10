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
	LectorFicheroPuzle * lec = LectorFicheroPuzle::getInstancia();
	Pieza* p = lec->obtenerPieza();

	Tablero *t = lec->obtenerTablero();
	t->dibujar(*p);

	// Hacer un giro completo paso a paso
	int r; // Fases de la rotacion
	for(r = 1; r <= 4; r++){
		if(t->piezaRotable(*p)) p->rotar();
		else { cout << "No puede hacer la rotacion numero " << r << endl; break; }

		cout << "------------------" << endl;
		t->dibujar(*p);
	}

	if(r > 4) cout << endl << "Se ha podido hacer una rotacion completa con esta configuracion :O" << endl;
	
	return 0;

}