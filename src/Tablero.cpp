/**
 *  Implementacion de la clase Tablero
 */

#include "Tablero.hpp" 

Tablero::Tablero(int tam){
    n = tam;
    // Aplicar espacio vacio
    for(int i = 1; i < n-1; i++)
	    for(int j = 1; j < n-1; j++)
		    tableroFijo[i][j] = CASILLA_VACIA;
    
    // Aplicar bordes
    for(int i = 0; i < n; i++){
        tableroFijo[i][0] = CASILLA_MURO;
        tableroFijo[0][i] = CASILLA_MURO;
        tableroFijo[i][n-1] = CASILLA_MURO;
        tableroFijo[n-1][i] = CASILLA_MURO;
    }
    objetivo = nullptr;
}

Tablero::Tablero(int tam, tableroMatriz matriz){
	n = tam;
	objetivo = nullptr;
    // Copiar matriz
    for(int i = 0; i < n; i++)
	    for(int j = 0; j < n; j++)
		    tableroFijo[i][j] = matriz[i][j];
}

void Tablero::fijarObstaculo(int x, int y){
    tableroFijo[y][x] = CASILLA_MURO;
}

void Tablero::test_fijarObstaculosPrueba(){
	tableroFijo[1][2] = CASILLA_MURO;
	tableroFijo[2][2] = CASILLA_MURO;
	tableroFijo[4][4] = CASILLA_MURO;
	tableroFijo[4][3] = CASILLA_MURO;
}

void Tablero::limpiar(){
    for(int i = 0; i < n; i++)
	    for(int j = 0; j < n; j++)
		   tableroDibujable[i][j] = (tableroFijo[i][j] == CASILLA_PIEZA) ? CASILLA_VACIA : tableroFijo[i][j];
}

void Tablero::aplicarPieza(const Pieza &p){
	int desplz;

	// Dibujemos el vertice
	tableroDibujable[p.getOrigenY()][p.getOrigenX()] = CASILLA_PIEZA;

	// Aplica la parte horizontal de la L (x, columnas)
	// -> Vamos a suponer que POSITIVO: derecha y NEGATIVO: izquierda (como se ha hecho siempre xd)
	int horizontal = abs(p.getAncho());
	for(int h = 1; h <= horizontal; h++){
		desplz = (p.getAncho() > 0) ? h : -h; // Hacia donde dibujar...? Izquierda o derecha...?
		tableroDibujable[p.getOrigenY()][p.getOrigenX() + desplz] = CASILLA_PIEZA;
	}

	// Aplica la parte vertical de la L
	// -> Vamos a suponer que POSITIVO: arriba y NEGATIVO: abajo (xd)
	int vertical = abs(p.getAlto());
	for(int v = 1; v <= vertical; v++){
		desplz = (p.getAlto() > 0) ? v : -v; // Hacia donde dibujar...? Arriba o abajo...?
		tableroDibujable[p.getOrigenY() + desplz][p.getOrigenX()] = CASILLA_PIEZA;
	}
}

bool Tablero::hayObstaculo(int x, int y) const {
	return tableroFijo[y][x] == CASILLA_MURO;
}

bool Tablero::posicionPosible(const Pieza &p) const {
	return posicionPosible(p.getOrigenX(), p.getOrigenY(), p.getAncho(), p.getAlto());
}

bool Tablero::posicionPosible(int origenX, int origenY, int ancho, int alto) const {
	if(hayObstaculo(origenX, origenY)) return false; // No se puede colocar el vertice

	int coordenadaIterada, signoCoordenadaIterada; 

	// Evaluar ancho de la L
	signoCoordenadaIterada = (ancho > 0) ? 1 : -1;
	coordenadaIterada = 1;

	while(coordenadaIterada <= abs(ancho)){
		if(hayObstaculo(origenX + coordenadaIterada*signoCoordenadaIterada, origenY)) return false;
		coordenadaIterada++;
	}
	
	// Evaluar alto de la L
	signoCoordenadaIterada = (alto > 0) ? 1 : -1;
	coordenadaIterada = 1;
	
	while(coordenadaIterada <= abs(alto)){
		if(hayObstaculo(origenX, origenY + coordenadaIterada*signoCoordenadaIterada)) return false;
		coordenadaIterada++;
	}

	return true;
}

bool Tablero::puedeRotar(const Pieza &p) const {
	if(saleDeLosLimitesAlRotar(p)) return false;

	return !chocaAlRotar(p);
}

bool Tablero::puedeRotarEstrictamente(const Pieza &p) const {
	if(saleDeLosLimitesAlRotar(p)) return false;

	return !chocaAlRotar(p);
}

bool Tablero::saleDeLosLimites(int coordenadaPicoHorizontal, int coordenadaPicoVertical) const {
	if(coordenadaPicoHorizontal < 0 || coordenadaPicoHorizontal >= n 
		|| coordenadaPicoVertical < 0 || coordenadaPicoVertical >= n) 
			return true;
	else return false;
}

bool Tablero::saleDeLosLimitesAlRotar(const Pieza &p) const {
	int posibleNuevaX, posibleNuevaY;
    p.getCoordenadasRotacion(posibleNuevaX, posibleNuevaY);

	int coordenadaPicoHorizontal = p.getOrigenX() + posibleNuevaX;
	int coordenadaPicoVertical = p.getOrigenY() + posibleNuevaY;
	
	return saleDeLosLimites(coordenadaPicoHorizontal, coordenadaPicoVertical);
}

bool Tablero::chocaAlRotar(const Pieza &p) const{
	Pieza* copia = new Pieza(p);
					copia->rotar();
	bool posible =	posicionPosible(*copia);
	delete copia;

	return !posible;
}

bool Tablero::chocaAlRotarEstrictamente(const Pieza &p) const {
	int posibleNuevaX, posibleNuevaY;
    p.getCoordenadasRotacion(posibleNuevaX, posibleNuevaY);

	const int signoX 		= (p.getAncho() 		> 0) ? 1 : -1;
	const int signoY 		= (p.getAlto() 			> 0) ? 1 : -1;
	const int signoNuevaX 	= (posibleNuevaX 		> 0) ? 1 : -1;
	const int signoNuevaY 	= (posibleNuevaY 		> 0) ? 1 : -1;

	bool choca = false;
	int dx, dy; // Se usara para calcular los limites del area encerrada al rotar

	// Nos basamos en que | Ancho actual | = | Nuevo alto | (Horizontal -> Vertical) y | Alto actual | = | Nuevo ancho | (Vertical -> Horizontal)

	// Comprobar cuadrante horizontal -> vertical
	dx = 1;
	while(!choca && dx <= abs(p.getAncho())){
		dy = 1;
		while(dy <= abs(p.getAncho())){
			if(hayObstaculo(p.getOrigenX() + signoX*dx,
				p.getOrigenY() + signoNuevaY*dy)){
				choca = true;
				std::cout << "[DEBUG]: Se detecta colision H->V en la casilla (x=" << p.getOrigenX() + signoX*dx << ", y=" << p.getOrigenY() + signoNuevaY*dy << std::endl;
				break;
			}
			dy++;
		} 
		dx++;
	}
	if(choca) return true;

	// Comprobar cuadrante vertical -> horizontal
	dx = 1;
	while(!choca && dx <= abs(p.getAlto())){
		dy = 1;
		while(dy <= abs(p.getAlto())){
			if(hayObstaculo(p.getOrigenX() + signoNuevaX*dx,
				p.getOrigenY() + signoY*dy)){
				choca = true;
				std::cout << "[DEBUG]: Se detecta colision V->H en la casilla (x=" << p.getOrigenX() + signoNuevaX*dx << ", y=" << p.getOrigenY() + signoY*dy << std::endl;
				break;
			}
			dy++;
		} 
		dx++;
	}

    return choca;
}

bool Tablero::puedeMover(const Pieza &p, Pieza::Movimiento dir) const {
	if(saleDeLosLimitesAlMover(p, dir)) return false;
	return !chocaAlMover(p, dir);
}

bool Tablero::saleDeLosLimitesAlMover(const Pieza &p, Pieza::Movimiento dir) const {
	if(Pieza::getTipoMovimiento(dir) == Pieza::TipoMovimiento::HORIZONTAL){
		int posibleNuevoExtremoX1 = p.getOrigenX() + Pieza::getSignoMovimiento(dir);
		int posibleNuevoExtremoX2 = posibleNuevoExtremoX1 + p.getAncho();
		if((posibleNuevoExtremoX1 < 0 || posibleNuevoExtremoX1 >= n) || (posibleNuevoExtremoX2 < 0 || posibleNuevoExtremoX2 >= n))
				return true; // Sale de los limites horizontales...
			else return false; // No sale de los limites 
	}else{
		int posibleNuevoExtremoY1 = p.getOrigenY() + Pieza::getSignoMovimiento(dir);
		int posibleNuevoExtremoY2 = posibleNuevoExtremoY1 + p.getAlto();
		if((posibleNuevoExtremoY1 < 0 || posibleNuevoExtremoY1 >= n) || (posibleNuevoExtremoY2 < 0 || posibleNuevoExtremoY2 >= n))
			return true; // Sale de los limites verticales...
		else return false; // No sale de los limites
	}
}

bool Tablero::chocaAlMover(const Pieza &p, Pieza::Movimiento dir) const {
	Pieza* pt = p.getPiezaMovida(dir);
	bool posible = posicionPosible(*pt);
	delete pt;
	return !posible;
}

void Tablero::dibujar(){
	for(int i = 0; i< n; i++){
		for(int j = 0; j < n; j++){
			std::cout << tableroDibujable[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void Tablero::dibujar(const Pieza &p){
    limpiar();
	aplicarPieza(p);
	dibujar();
}

void Tablero::setObjetivo(Pieza* p){
	objetivo = p;
}

int Tablero::h(const Pieza &p){
	int h = abs(p.getOrigenX()-objetivo->getOrigenX()) + abs(p.getOrigenY() - objetivo->getOrigenY());
	if(h == 0){
		if(p.getAncho() == objetivo->getAncho()) h = 0;
		else h = 1;
	}
	return h;
}
	
Tablero::~Tablero(){delete objetivo;}
