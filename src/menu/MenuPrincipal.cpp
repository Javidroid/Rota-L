#include "MenuPrincipal.hpp"

MenuPrincipal::MenuPrincipal(){
	LectorFicheroPuzle * lec = LectorFicheroPuzle::getSingleton();
		p = lec->obtenerPieza();
		t = lec->obtenerTablero();
		t->setObjetivo(lec->obtenerObjetivo());
	delete lec; // Ya no es necesario el lector de ficheros	
}

MenuPrincipal::~MenuPrincipal(){
	delete t;
	delete p;
}

void MenuPrincipal::abrirMenu(){
	bool bNecesarioMostrarInfo = true;	
	Seleccion sel;
	do{
		if(bNecesarioMostrarInfo){
			mostrarinfo();
			bNecesarioMostrarInfo = false;
		}
		sel = elegirOpcion();
		switch(sel){
			case Seleccion::INTERACTIVO: 	 modoInteractivo(); 
										 	 bNecesarioMostrarInfo = true;
										 	 break;
			case Seleccion::AESTRELLA:	 	 resolucionAestrella(); 
										 	 bNecesarioMostrarInfo = true; 
										 	 break;
			case Seleccion::PRIMERO_MEJOR:	 resolucionPrimeroMejor(); 
										 	 bNecesarioMostrarInfo = true; 
										 	 break;
			
		}
	}while(sel != Seleccion::SEL_INVALIDA);
	cout << "Adios :)" << endl;
}

void MenuPrincipal::mostrarinfo(){
    cout << "=========================================" << endl;
	cout << "================[ROTA-L]=================" << endl;
	cout << "=========================================" << endl;

    cout << '[' << MENU_OPCION_INTERACTIVO << "] Resolver manualmente" << endl;
    cout << '[' << MENU_OPCION_AESTRELLA << "] Resolver automaticamente con A*" << endl;
	cout << '[' << MENU_OPCION_PRIMEROMEJOR << "] Resolver automaticamente con PRIMERO MEJOR" << endl;
}
    
MenuPrincipal::Seleccion MenuPrincipal::elegirOpcion(){
    int decision;
    cin >> decision;
    switch(decision){
        case MENU_OPCION_INTERACTIVO:   	return Seleccion::INTERACTIVO;
        case MENU_OPCION_AESTRELLA:     	return Seleccion::AESTRELLA;
		case MENU_OPCION_PRIMEROMEJOR:     return Seleccion::PRIMERO_MEJOR;
        default:    break;
    }
    return Seleccion::SEL_INVALIDA;
}

void MenuPrincipal::modoInteractivo(){
    bool continuarModoInteractivo = true;
	Pieza::Movimiento dir;
	int decision;

	bool banderaRealizarMovimiento;
	bool banderaRealizarRotacion;
	while(continuarModoInteractivo){
	    t->dibujar(*p);
	    cout << "Introduce la direccion en la que quieras moverte:" << endl;
	    	if(t->puedeMover(*p, Pieza::Movimiento::ABAJO)) 	cout << "\t[1]: ABAJO" << endl;
	    	if(t->puedeMover(*p, Pieza::Movimiento::ARRIBA)) 	cout << "\t[2]: ARRIBA" << endl;
		    if(t->puedeMover(*p, Pieza::Movimiento::IZQUIERDA)) cout << "\t[3]: IZQUIERDA" << endl;
		    if(t->puedeMover(*p, Pieza::Movimiento::DERECHA)) 	cout << "\t[4]: DERECHA" << endl;
		    if(t->puedeRotar(*p)) 								cout << "\t[5]: ROTAR A LA DERECHA" << endl;
	    cin >> decision;
		    banderaRealizarMovimiento = false;
		    banderaRealizarRotacion = false;
		    switch(decision){
		    	case 1: dir = Pieza::Movimiento::ABAJO; 	banderaRealizarMovimiento = true; break;
			    case 2: dir = Pieza::Movimiento::ARRIBA; 	banderaRealizarMovimiento = true; break;
		    	case 3: dir = Pieza::Movimiento::IZQUIERDA; banderaRealizarMovimiento = true; break;
			    case 4: dir = Pieza::Movimiento::DERECHA; 	banderaRealizarMovimiento = true; break;

			    case 5: 									banderaRealizarRotacion = true; break;
				
			    default: continuarModoInteractivo = false;
		    }

		    if(banderaRealizarMovimiento){
			    if(t->puedeMover(*p, dir)) 
				    p->mover(dir);
		    }else if(banderaRealizarRotacion){
			    if(t->puedeRotar(*p)) 
				    p->rotar();
		    }else cout << "Adios :(" << endl;
	    }         
    }

void MenuPrincipal::resolucionAestrella(){
	Pieza* piezaAlgoritmo = new Pieza(*p);
	algoritmos::Aestrella* aestrella = new algoritmos::Aestrella(t, piezaAlgoritmo);
	unsigned int t0 = clock();
	{
		aestrella->Principal();
	}
	unsigned int t1 = clock();

	delete aestrella;
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout<<endl<<"Tiempo de ejecucion: "<<time<<" segundos";
}

void MenuPrincipal::resolucionPrimeroMejor(){
	Pieza* piezaAlgoritmo = new Pieza(*p);
	algoritmos::PrimeroMejor* primeroMejor = new algoritmos::PrimeroMejor(t, piezaAlgoritmo);
	unsigned int t0 = clock();
	{
		primeroMejor->Principal();
	}
	unsigned int t1 = clock();

	delete primeroMejor;
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout<<endl<<"Tiempo de ejecucion: "<<time<<" segundos";
}
