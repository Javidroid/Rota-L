#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#define MENU_OPCION_INTERACTIVO 0
#define MENU_OPCION_AESTRELLA 1
#define MENU_OPCION_PRIMEROMEJOR 2

#include <iostream>
#include <ctime>

#include "../Pieza.hpp"
#include "../Tablero.hpp"

#include "../LectorFicheroPuzle.hpp"

#include "../algoritmos/Aestrella.hpp"
#include "../algoritmos/PrimeroMejor.hpp"

using namespace std;

class MenuPrincipal{
public:
    enum class Seleccion{
        AESTRELLA, INTERACTIVO, PRIMERO_MEJOR,
        SEL_INVALIDA
    };
private:
    Pieza* p;
    Tablero* t;

    void mostrarinfo();
    Seleccion elegirOpcion();

    void modoInteractivo();
    void resolucionAestrella();
    void resolucionPrimeroMejor();
public:
    MenuPrincipal();
    ~MenuPrincipal();

    void abrirMenu();
};

#endif