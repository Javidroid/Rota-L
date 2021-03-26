#ifndef LECTORFICHEROPUZLE_H
#define LECTORFICHEROPUZLE_H

#include <fstream>
#include "Pieza.hpp"
#include "Tablero.hpp"

#define FICHERO_PUZLE_NOMBRE "ROTAL.txt"

class LectorFicheroPuzle  {
private:
	static LectorFicheroPuzle * singleton;

	int tamanoTablero;
	Pieza * pieza;
	tableroMatriz tableroLeido;
	Tablero * tablero;

	LectorFicheroPuzle();

	void identificarPieza();
public:
	static LectorFicheroPuzle * getSingleton();
	~LectorFicheroPuzle();
	Tablero* obtenerTablero();
	Pieza* obtenerPieza();
	void cargarTableroPrueba();

};
#endif