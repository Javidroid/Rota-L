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
	lec->cargarTableroPrueba(); 
	Pieza* p = lec->obtenerPieza();

	/**
	 * PRUEBA DE ROTACIONES
	Pieza p(1, 5,
		  2, 1);
	Tablero t(7);

	// Prueba
	t.test_fijarObstaculosPrueba();

	t.dibujar(p);

	// Hacer un giro completo paso a paso
	int r = 1;
	for(r = 1; r <= 4; r++){
		if(t.piezaRotable(p)) p.rotar();
		else { cout << "No puede hacer la rotacion numero " << r << endl; break; }

		cout << "------------------" << endl;
		t.dibujar(p);
	}

	if(r > 4) cout << endl << "Se ha podido hacer una rotacion completa con esta configuracion :O" << endl;
	**/
	return 0;

}