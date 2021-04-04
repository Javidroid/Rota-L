#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#define MENU_OPCION_INTERACTIVO 0
#define MENU_OPCION_AESTRELLA 1

#include <iostream>
#include <ctime>

#include "../Pieza.hpp"
#include "../Tablero.hpp"

#include "../LectorFicheroPuzle.hpp"

#include "../algoritmos/Aestrella.hpp"

using namespace std;

class MenuPrincipal{
public:
    enum class Seleccion{
        AESTRELLA, INTERACTIVO,
        SEL_INVALIDA
    };
private:
    Pieza* p;
    Tablero* t;

    void mostrarinfo();
    Seleccion elegirOpcion();

    void modoInteractivo();
    void resolucionAestrella();
public:
    MenuPrincipal();
    ~MenuPrincipal();

    void abrirMenu();
};

#endif