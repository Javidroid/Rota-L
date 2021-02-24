//============================================================================
// Name        : LectorFicheroPuzle.hpp
// Author      : Ra�l Alvarado D�az, Javier Florido Cartolano & Iv�n S�nchez Cordero
// Version     :
// Copyright   : Proyecto IASI 2020/21
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef LECTORFICHEROPUZLE_H
#define LECTORFICHEROPUZLE_H

#include <fstream>
#include "Pieza.hpp"
#include "Tablero.hpp"

#define FICHERO_PUZLE_NOMBRE "ROTAL.txt"

class LectorFicheroPuzle  {
private:
	static LectorFicheroPuzle * instancia;

	int tamanoTablero;
	Pieza * pieza;
	tableroMatriz tableroLeido;

	LectorFicheroPuzle();

	void identificarPieza();
public:
	static LectorFicheroPuzle * getInstancia();
	~LectorFicheroPuzle();

	Tablero* obtenerTablero();

	Pieza* obtenerPieza();

	void cargarTableroPrueba();

};
#endif
