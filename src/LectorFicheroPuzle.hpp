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
	Pieza * objetivo;
	tableroMatriz tableroLeido;
	Tablero * tablero;

	LectorFicheroPuzle();

	Pieza* identificarPieza(int tipoPieza);
public:
	static LectorFicheroPuzle * getSingleton();
	~LectorFicheroPuzle();
	Tablero* obtenerTablero();
	Pieza* obtenerPieza();
	Pieza* obtenerObjetivo();
	void cargarTableroPrueba();

};
#endif
