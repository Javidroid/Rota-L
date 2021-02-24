#include "LectorFicheroPuzle.hpp"  
LectorFicheroPuzle * LectorFicheroPuzle::instancia = nullptr;

LectorFicheroPuzle *LectorFicheroPuzle::getInstancia(){
    if(instancia == nullptr) instancia = new LectorFicheroPuzle();
    return instancia;
}

LectorFicheroPuzle::LectorFicheroPuzle(){

	tamanoTablero = 10; // Siempre va a ser 10 en todos los ficheros???
	pieza = nullptr;

	/**
	 * Parte quitada para probar identificador de pieza
	std::ifstream in(FICHERO_PUZLE_NOMBRE, std::ifstream::in);
	std::string line;

	if(in.is_open()){
		for(int i=0;i<tamanoTablero;i++){
			for(int j=0;j<tamanoTablero;j++){
				getline(in,line,',');
				tableroLeido[i][j]=std::stoi(line.c_str());
			}
		}
		in.close();
	}*/
}

Tablero* LectorFicheroPuzle::obtenerTablero(){
	return new Tablero(tamanoTablero, tableroLeido);
}

Pieza* LectorFicheroPuzle::obtenerPieza(){
	if(pieza == nullptr) identificarPieza();
	return pieza;
}

void LectorFicheroPuzle::identificarPieza(){
	int coordenadaPaloHorizontal = -1, // Sera la coordenada Y del vertice (el palo horizontal puede disponerse en parte superior / inferior)
		coordenadaPaloVertical = -1;   // Sera la coordenada X del vertice (el palo vertical puede disponerse en parte izq / der)

	int anchoPieza = 0,
		altoPieza = 0;
	
	// No evaluar los bordes del tablero porque siempre seran muros ( tampoco se haran accesos fuera de la matriz !! )
	// Primero buscar el palo horizontal. Las casillas se evaluaran de arriba hacia abajo y de izquierda a derecha.
	int coordenadaPrimeraPorcionPaloHorizontal; // Coordenada X (columna) del pico izq del palo horizontal

	// Encontrar una casilla pieza y una a la derecha indica que es el palito horizontal porque comprobamos de izuiqerda a derecha
	bool paloHorizontalEncontrado = false; // paloHorizontalEncontrado sii (coordenadaPaloHorizontal != -1)
	for(int i = 1; !paloHorizontalEncontrado && i < tamanoTablero-1; i++){
		for(int j = 1; !paloHorizontalEncontrado && j < tamanoTablero-1; j++){
			if(tableroLeido[i][j] == CASILLA_PIEZA && tableroLeido[i][j+1] == CASILLA_PIEZA){
				// Se ha encontrado el palo horizontal
				coordenadaPaloHorizontal = i; // Fila donde esta el palo horizontal
				coordenadaPrimeraPorcionPaloHorizontal = j; // Columna de la parte izquierda del palo horizontal

				paloHorizontalEncontrado = true;
			}
		}
	}

	if(!paloHorizontalEncontrado){//if(coordenadaPaloHorizontal == -1){
		std::cout << "[DEBUG] El palo horizontal de la L no se ha encontrado. Tablero incorrecto ??" << std::endl;
		std::terminate();
	}
	// Una vez encontrado el palo horizontal buscar el vertical evaluando solo las partes superiores/inferiores de ese
	int candidatoCoordenadaPaloVertical = coordenadaPrimeraPorcionPaloHorizontal;
	while(tableroLeido[coordenadaPaloHorizontal]	// Mantenerse en la misma fila: coordenada palo horizontal
					  [candidatoCoordenadaPaloVertical] == CASILLA_PIEZA){	// Ir comprobando las columnas: distintas coordenadas palo vertical

		if(tableroLeido[coordenadaPaloHorizontal+1][candidatoCoordenadaPaloVertical] == CASILLA_PIEZA || // Hay mas pieza arriba ??
							tableroLeido[coordenadaPaloHorizontal-1][candidatoCoordenadaPaloVertical] == CASILLA_PIEZA){ // Hay mas pieza abajo ??
			// Se ha encontrado el palo vertical: es candidatoCoordenadaPaloVertical (coordenada X del vertice)
			coordenadaPaloVertical = candidatoCoordenadaPaloVertical;
			break;
		}else{
			// Seguir buscando, de izquierda a derecha
			candidatoCoordenadaPaloVertical++;
		}
	}

	if(coordenadaPaloVertical == -1){
		std::cout << "[DEBUG] El palo vertical de la L no se ha encontrado. Tablero incorrecto ?? x=" << coordenadaPaloHorizontal << std::endl;
		std::terminate();
	}

	std::cout << "[DEBUG] Se ha encontrado el vertice de la pieza en: (x=" << coordenadaPaloVertical << ", y=" << coordenadaPaloHorizontal << ')' << std::endl;
	
	// Una vez encontrado el vertice, determinar el ancho y alto de la pieza
	
	// Determinar ancho
		// Determinar signo de ancho
		int signoAncho = (tableroLeido[coordenadaPaloHorizontal][coordenadaPaloVertical+1] == CASILLA_PIEZA) ? 1 : -1;
		// Explorar ancho de la pieza
		int indiceAncho = 0;
		while(tableroLeido[coordenadaPaloHorizontal][coordenadaPaloVertical + indiceAncho] == CASILLA_PIEZA){
			indiceAncho += signoAncho;
		}
	anchoPieza = indiceAncho - signoAncho; // Como el indice contiene la casilla SIGUIENTE a la ultima, quitar una casilla

	// Determinar alto
		// Determinar signo de alto (recordar que y positiva es hacia ARRIBA)
		int signoAlto = (tableroLeido[coordenadaPaloHorizontal-1][coordenadaPaloVertical] == CASILLA_PIEZA) ? 1 : -1;
		// Explorar alto de la pieza
		int indiceAlto = 0;
		while(tableroLeido[coordenadaPaloHorizontal - indiceAlto][coordenadaPaloVertical] == CASILLA_PIEZA){
			indiceAlto += signoAlto;
		}
	altoPieza = indiceAlto - signoAlto; // Como el indice contiene la casilla SIGUIENTE a la ultima, quitar una casilla

	// Pieza identificada completamente. Construir
	pieza = new Pieza(coordenadaPaloVertical, coordenadaPaloHorizontal,
						anchoPieza, altoPieza);

	// DEBUG: indicar pieza
	std::cout << "[DEBUG] Se ha encontrado una pieza en (x=" << coordenadaPaloVertical << ", y=" << coordenadaPaloHorizontal << ")\n"
				<< "\tAncho: " << anchoPieza << " | Alto: " << altoPieza << std::endl;					

}

void LectorFicheroPuzle::cargarTableroPrueba(){
	/**
	// vertice @ (x=1, y=1) [ Mejor caso ]
	int matriz[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						 {1, 2, 2, 2, 0, 0, 0, 0, 0, 1},
						 {1, 2, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 2, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	**/

	/**
	// vertice @ (x=6, y=2)
	int matriz[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						 {1, 0, 0, 0, 0, 0, 2, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 2, 2, 2, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	*/

	
	// vertice @ (x=8, y=8) [ Peor caso ]
	int matriz[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 2, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 2, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 2, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 2, 1},
						 {1, 0, 0, 0, 0, 2, 2, 2, 2, 1},
						 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
			tableroLeido[i][j] = matriz[i][j];
}
	
LectorFicheroPuzle::~LectorFicheroPuzle(){delete pieza;}