/**
 * 	Definicion de la clase Pieza
 */
#ifndef PIEZA_H
#define PIEZA_H
	
class Pieza  {
private:
	int origenX, origenY;
	int ancho, alto;

public:
	Pieza(int origenX, int origenY, int ancho, int alto);
	int getOrigenX() const; 	int getOrigenY() const;
	int getAncho() const;		int getAlto() const;

	/**
 	* Calcula los nuevos picos de la L sin aplicar cambios
 	*/	
	void getCoordenadasRotacion(int &nuevaX, int &nuevaY) const;

	/**
 	* Calcula los nuevos picos de la L y SI aplica los cambios
 	*/
	void rotar();

	~Pieza();
};
#endif