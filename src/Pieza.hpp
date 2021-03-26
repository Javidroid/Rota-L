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
	enum class Movimiento{
		ABAJO, ARRIBA, IZQUIERDA, DERECHA
	};

	enum class TipoMovimiento{
		VERTICAL, HORIZONTAL
	};

	/**
	 * Obtiene el signo necesario para moverse en la direccion indicada.
	 */
	static signed int getSignoMovimiento(Movimiento m);

	/**
	 * DEVUELVE: PIEZA_TIPOMOVIMIENTO_HORIZONTAL si es movimiento horizontal ; PIEZA_TIPOMOVIMIENTO_VERTIAL si es vertical
	 */
	static TipoMovimiento getTipoMovimiento(Movimiento m);

	Pieza(int origenX, int origenY, int ancho, int alto);
	Pieza(const Pieza &pieza);
	void definir(int origenX, int origenY, int ancho, int alto);
	int getOrigenX() const; 	int getOrigenY() const;
	int getAncho() const;		int getAlto() const;

	bool operator==(Pieza &p) const ;

	/**
 	* Calcula los nuevos picos de la L sin aplicar cambios
	* ENTRADA:SALIDA: nuevaX, nuevaY
 	*/	
	void getCoordenadasRotacion(int &nuevoAncho, int &nuevoAlto) const;

	/**
 	* Calcula los nuevos picos de la L y SI aplica los cambios
	* Rotacion hacia la derecha (sentido horario)
 	*/
	void rotar();
	Pieza* getPiezaRotada() const;

	/**
	 * Mueve la pieza una casilla en la dirección indicada
	 * @param dir
	 */
	void mover(Movimiento dir);
	Pieza* getPiezaMovida(Movimiento dir) const;

	/**
	* Obtiene el movimiento reciproco al indicado
	* ENTRADA: m
	*/
	Movimiento getMovimientoReciproco(Movimiento m) const;


	~Pieza();
};
#endif