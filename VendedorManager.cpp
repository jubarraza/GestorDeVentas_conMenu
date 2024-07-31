#include <iostream>
#include <cstring>
#include <iomanip>
#include "VendedorManager.h"
#include "FuncionesGenerales.h"
#include "rlutil.h"
using namespace std;

VendedorManager::VendedorManager(): _archivo("Vendedores.dat"){

}

void VendedorManager::Menu()
{

        int opc = 1;
        int y = 0;
        system("cls");
        rlutil::hidecursor();

        do {

            rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
            rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
            rlutil::locate(35, 9);
            cout << (char)149 << " Sistema de Gestion de Ventas e Inventario " << (char)149 << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            rlutil::locate(45, 11);
            cout << "* Modulo de VENDEDORES *" << endl;
            showItem(" Crear vendedor ", 47, 14, y == 0);
            showItem(" Listado de vendedores ", 47, 15, y == 1);
            showItem(" Buscar vendedor ", 47, 16, y == 2);
            showItem(" Editar vendedor ", 47, 17, y == 3);
            showItem(" Eliminar vendedor ", 47, 18, y == 4);
            showItem(" Backup de archivo de Vendedores ", 47, 20, y == 6);
            showItem(" Restauracion de backup de Vendedores ", 47, 21, y == 7);
            showItem2("Volver al menu principal ", 47, 23, y == 9);


            switch (rlutil::getkey()) {
            case 14: //UP
                rlutil::locate(49, 14 + y);
                cout << " " << endl;
                y--;
                if (y < 0) {
                    y = 0;
                }
                if (y == 8 || y == 5) {
                    y--;
                }
                break;
            case 15: //DOWN
                rlutil::locate(49, 14 + y);
                cout << " " << endl;
                y++;
                if (y > 8) {
                    y = 8;
                }
                if (y == 8 || y == 5) {
                    y++;
                }
                break;
            case 1: //ENTER

                switch (y) {
                case 0:
                    system("cls");
                    AgregarVendedor();
                    system("pause");
                    system("cls");
                    break;
                case 1:
                    system("cls");
                    menuListado();
                    system("cls");
                    break;
                case 2:
                    system("cls");
                    BuscarVendedor();
                    system("pause");
                    system("cls");
                    break;
                case 3:
                    system("cls");
                    EditarVendedor();
                    system("cls");
                    break;
                case 4:
                    system("cls");
                    borrarVendedor();
                    system("cls");
                    break;
                case 6:
                    system("cls");
                    realizarBackup();
                    system("cls");
                    break;
                case 7:
                    system("cls");
                    restaurarBackup();
                    system("cls");
                    break;
                case 9:
                    opc = 0;
                    system("cls");
                    break;

                default:
                    break;
                }

                break;

            default:

                break;
            }
        } while (opc != 0);

}



void VendedorManager::AgregarVendedor(){
    if(_archivo.GuardarRegistro(CrearVendedor())){
        rlutil::setColor(rlutil::COLOR::GREEN);
        cout<<"* El vendedor se guardo correctamente *"<<endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }else{
        rlutil::setColor(rlutil::COLOR::RED);
        cout<<"* No se pudo guardar el vendedor *"<<endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

Vendedor VendedorManager::CrearVendedor(){
    int numLegajo, anioAntiguedad;
    Fecha fechaI;
    Vendedor vendedor;
    int opc;

regreso:
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENDEDORES *" << endl << endl;
    cout << "Carga de nuevo vendedor" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    vendedor.CargarPersona();
    bool resultado = DniRepetido(vendedor.getDni());
    if (resultado) {

        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* Vendedor ya existente *";
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();
        int opcion = 1, y = 0;

        do {
            rlutil::locate(47, 15);
            cout << "* ¿Desea cargar otro vendedor? *" << endl;
            showItem(" Si ", 51, 17, y == 0);
            showItem(" No ", 51, 18, y == 1);


            switch (rlutil::getkey()) {
            case 14: //UP
                rlutil::locate(49, 17 + y);
                cout << " " << endl;
                y--;
                if (y < 0) {
                    y = 0;
                }
                break;
            case 15: //DOWN
                rlutil::locate(49, 17 + y);
                cout << " " << endl;
                y++;
                if (y > 1) {
                    y = 1;
                }
                break;
            case 1: //ENTER

                switch (y) {
                case 0:
                    system("cls");
                    goto regreso;
                    break;
                case 1:
                    system("cls");
                    Menu();
                    system("cls");
                    break;
                case 3:
                    opc = 0;
                    system("cls");
                    break;

                default:
                    break;
                }

                break;

            default:

                break;
            }

        } while (opcion != 0);

    }

    rlutil::showcursor();
    numLegajo = validarInt("NUMERO DE LEGAJO: ");
    vendedor.setNroLegajo(numLegajo);
    cout<<"FECHA INGRESO: "<<endl;
    fechaI.Cargar();
    vendedor.setFechaIngreso(fechaI);
    cout<<"ANTIGUEDAD: ";
    anioAntiguedad=vendedor.calcularAntiguedad();
    cout << anioAntiguedad << " años" << endl;
    vendedor.setAntiguedad(anioAntiguedad);
    vendedor.setEliminado(false);
    cout<<endl;
    rlutil::hidecursor();

    return vendedor;
}

void VendedorManager::mostrarVendedor(Vendedor reg) 
{
    rlutil::setColor(rlutil::COLOR::WHITE);
    reg.MostrarPersona();
    cout << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "LEGAJO: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getNroLegajo() << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "FECHA INGRESO: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getFechaIngreso().toString() << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "ANTIGUEDAD: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getAntiguedad();
}

void VendedorManager::PlanillaVendedor(){
    cout<<left;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << setw(55) << " " << "* Listado de Vendedores *" << endl << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout<<setw(14)<<" DNI ";
    cout<<setw(20)<<"NOMBRE";
    cout<<setw(20)<<"APELLIDO ";
    cout<<setw(23)<<"FECHA NACIMIENTO ";
    cout<<setw(10)<<"LEGAJO ";
    cout<<setw(20)<<"FECHA INGRESO ";
    cout<<setw(10)<<"ANTIGUEDAD ";
    cout<<endl;
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
}

void VendedorManager::mostrarVendedorEnLinea(Vendedor vendedor){

    rlutil::setColor(rlutil::COLOR::WHITE);
    vendedor.MostrarPersonaEnLinea();

    cout<<left;
    cout<<setw(10)<<vendedor.getNroLegajo();
    cout<<setw(20)<<vendedor.getFechaIngreso().toString();
    cout << setw(0) << vendedor.getAntiguedad() << " años"; 
}



void VendedorManager::menuListado() 
{
    int opcion = 1, y = 0;
    do {
        rlutil::locate(39, 9);
        rlutil::setColor(rlutil::COLOR::WHITE);
        cout << "* ¿Como desea ordenar el listado de Vendedores? *" << endl;
        showItem(" por Antiguedad ", 51, 11, y == 0);
        showItem(" por Apellido ", 51, 12, y == 1);
        showItem2(" Volver ", 51, 14, y == 3);


        switch (rlutil::getkey()) {
        case 14: //UP
            rlutil::locate(49, 11 + y);
            cout << " " << endl;
            y--;
            if (y < 0) {
                y = 0;
            }
            if (y == 2) {
                y--;
            }
            break;
        case 15: //DOWN
            rlutil::locate(49, 11 + y);
            cout << " " << endl;
            y++;
            if (y > 3) {
                y = 3;
            }
            if (y == 2) {
                y++;
            }
            break;
        case 1: //ENTER

            switch (y) {
            case 0:
                system("cls");
                ListarAntiguedad();
                system("pause");
                system("cls");
                break;
            case 1:
                system("cls");
                ListarApellido();
                system("pause");
                system("cls");
                break;
            case 3:
                opcion = 0;
                system("cls");
                break;

            default:
                break;
            }

            break;

        default:

            break;
        }

    } while (opcion != 0);


}

void VendedorManager::OrdenarPorAntiguedad(Vendedor* obj, int cantidad, bool criterio(int, int)) {
    Vendedor aux;

    for (int i = 0; i < cantidad; i++) {
        for (int j = i + 1; j < cantidad; j++) {
            if (criterio(obj[j].getAntiguedad(), obj[i].getAntiguedad())) {
                aux = obj[j];
                obj[j] = obj[i];
                obj[i] = aux;
            }
        }
    }
}

void VendedorManager::ListarAntiguedad() {
    int cantidad = _archivo.ContarRegistro();
    Vendedor* vec, reg;

    vec = new Vendedor[cantidad];
    if (vec == nullptr) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay memoria *";
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

    if (cantidad == 0) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay Vendedores para mostrar *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
         PlanillaVendedor(); 
        for (int i = 0; i < cantidad; i++) {
            reg = _archivo.leerRegistro(i);
            vec[i] = reg;
        }

        OrdenarPorAntiguedad(vec, cantidad, creciente);  

        for (int i = 0; i < cantidad; i++) {
            if (vec[i].getEliminado() == false) {
                mostrarVendedorEnLinea(vec[i]);
                cout << endl;
            }
        }
        cout << endl;
    }
    delete[]vec;
}

void VendedorManager::OrdenarPorApellido(Vendedor* obj, int cantidad, bool criterio(string, string)) {
    Vendedor aux;

    for (int i = 0; i < cantidad; i++) {
        for (int j = i + 1; j < cantidad; j++) {
            if (criterio(obj[j].getApellido(), obj[i].getApellido())) {
                aux = obj[j];
                obj[j] = obj[i];
                obj[i] = aux;
            }
        }
    }
}

void VendedorManager::ListarApellido() {
    int cantidad = _archivo.ContarRegistro();
    Vendedor* vec, reg;

    vec = new Vendedor[cantidad];
    if (vec == nullptr) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay memoria *";
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

    if (cantidad == 0) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay Vendedores para mostrar *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        PlanillaVendedor();
        for (int i = 0; i < cantidad; i++) {
            reg = _archivo.leerRegistro(i);
            vec[i] = reg;
        }

        OrdenarPorApellido(vec, cantidad, creciente);

        for (int i = 0; i < cantidad; i++) {
            if (vec[i].getEliminado() == false) {
                mostrarVendedorEnLinea(vec[i]);
                cout << endl;
            }
        }
        cout << endl;
    }
    delete[]vec;
}



void VendedorManager::BuscarVendedor(){
    int numLegajo, indice;
    Vendedor vendedor;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENDEDORES *" << endl << endl;
    cout << "Buscador de vendedores" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();

    numLegajo = validarInt("Ingrese el numero de legajo del vendedor que desea buscar: ");
    cout << endl << endl;

    indice=_archivo.BuscarId(numLegajo);

    if(indice != -1){
        vendedor=_archivo.leerRegistro(indice);
        mostrarVendedor(vendedor);

    }else{
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se Encontraron Vendedores con el numero de legajo buscado *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    cout << endl << endl;
}



void VendedorManager::EditarVendedor(){
    int legajo;
    int opcion;
    
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENDEDORES *" << endl << endl;
    cout << "Editar vendedor" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();
    legajo = validarInt("Ingrese numero de legajo del Vendedor a editar: ");
    cout << endl;

    int indice = _archivo.BuscarId(legajo);

    Vendedor vendedor;
    vendedor = _archivo.leerRegistro(indice);

    if(indice != -1){
        vendedor=_archivo.leerRegistro(indice);

        if (vendedor.getEliminado() == false) {
            rlutil::hidecursor(); 
            rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
            cout << endl << "Vendedor a Editar: " << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            mostrarVendedor(vendedor);
            
            int opc = 1, y = 0;

            do {
                rlutil::setColor(rlutil::COLOR::WHITE);
                rlutil::locate(43, 17);
                cout << "* ¿Que dato desea editar? *" << endl;
                showItem(" Fecha de Ingreso   ", 51, 19, y == 0);
                showItem2(" Volver  ", 51, 21, y == 2);


                switch (rlutil::getkey()) {
                case 14: //UP
                    rlutil::locate(49, 19 + y);
                    cout << " " << endl;
                    y--;
                    if (y < 0) {
                        y = 0;
                    }
                    if (y == 1) {
                        y--;
                    }
                    break;
                case 15: //DOWN
                    rlutil::locate(49, 19 + y);
                    cout << " " << endl;
                    y++;
                    if (y > 2) {
                        y = 2;
                    }
                    if (y == 1) {
                        y++;
                    }
                    break;

                case 1: //ENTER
                    switch (y) {
                    case 0: {
                        system("cls");
                        editarFechaIngreso(vendedor, indice); 
                        system("pause");
                        opc = 0;
                        system("cls");
                        break;
                    }

                    case 2: 
                        opc = 0;
                        system("cls");
                        break;

                    default:
                        break;
                    }

                    break;

                default:

                    break;
                }

            } while (opc != 0);
    
        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* El vendedor buscado se encuentra eliminado *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");
        }
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* El numero de legajo buscado no existe *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
}

void VendedorManager::editarFechaIngreso(Vendedor reg, int pos) 
{
    Fecha f;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << endl << "Vendedor a Editar: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarVendedor(reg);
    cout << endl << endl;

    rlutil::showcursor();
    cout << "Ingrese nueva fecha: " << endl;
    f.Cargar();
    reg.setFechaIngreso(f); 
    int newA = reg.calcularAntiguedad();
    reg.setAntiguedad(newA);

    rlutil::hidecursor();

    bool result = _archivo.Sobreescribir(reg, pos); 

    if (result == true) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << endl << "* El vendedor se editó correctamente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        cout << "Vendedor modificado: " << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        mostrarVendedor(reg);
        cout << endl << endl;
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se pudo editar el vendedor *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}



void VendedorManager::borrarVendedor(){
    int numLegajo, indice;
    Vendedor reg;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENDEDORES *" << endl << endl;
    cout << "Eliminar vendedor" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    rlutil::showcursor();

    numLegajo = validarInt("Ingrese el numero de Legajo del vendedor a borrar: ");
    rlutil::hidecursor();
    cout << endl;

    indice = _archivo.BuscarId(numLegajo);

    if(indice != -1){
        reg = _archivo.leerRegistro(indice);

        if (reg.getEliminado() == true) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* El vendedor ya se encuentra eliminado *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");

        }
        else {
            rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
            cout << endl << "Vendedor a Borrar: " << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            mostrarVendedor(reg);
            cout << endl;

            int opc = 1, y = 0;

            do {
                rlutil::hidecursor();
                rlutil::setColor(rlutil::COLOR::WHITE);
                rlutil::locate(35, 18);
                cout << "* ¿Confirma que desea borrar este Vendedor? *" << endl;
                showItem(" Si   ", 51, 20, y == 0);
                showItem(" No  ", 51, 21, y == 1);


                switch (rlutil::getkey()) {
                case 14: //UP
                    rlutil::locate(49, 20 + y);
                    cout << " " << endl;
                    y--;
                    if (y < 0) {
                        y = 0;
                    }
                    break;
                case 15: //DOWN
                    rlutil::locate(49, 20 + y);
                    cout << " " << endl;
                    y++;
                    if (y > 1) {
                        y = 1;
                    }
                    break;
                case 1: //ENTER

                    switch (y) {
                    case 0: {
                        reg.setEliminado(true);
                        bool result = _archivo.Sobreescribir(reg, indice);
                        if (result) {
                            rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
                            rlutil::locate(39, 25);
                            cout << "* El vendedor se ha borrado correctamente *" << endl;
                            rlutil::setColor(rlutil::COLOR::WHITE);
                            opc = 0;
                        }
                        else {
                            rlutil::setColor(rlutil::COLOR::RED);
                            rlutil::locate(39, 25);
                            cout << "* No se pudo eliminar el vendedor *" << endl;
                            rlutil::setColor(rlutil::COLOR::WHITE);
                        }

                        rlutil::locate(39, 26);
                        system("pause");
                        system("cls");
                        break;
                    }
                    case 1:
                        rlutil::setColor(rlutil::COLOR::RED);
                        rlutil::locate(39, 25);
                        cout << "* Se cancelo el borrado del vendedor *" << endl;
                        rlutil::setColor(rlutil::COLOR::WHITE);
                        opc = 0;

                        rlutil::locate(39, 26);
                        system("pause");
                        system("cls");
                        break;

                    default:
                        break;
                    }

                    break;

                default:

                    break;
                }

            } while (opc != 0);

        }

    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* El vendedor buscado no existe *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
}



void VendedorManager::realizarBackup() {

    string origen = "Vendedores.dat";
    string copia = "Vendedores.bkp";

    string comando = "copy " + origen + " " + copia;

    rlutil::setColor(rlutil::COLOR::WHITE);
    rlutil::locate(35, 9);
    int resultado = system(comando.c_str());

    rlutil::locate(35, 10);
    if (resultado == 0) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << "* Backup realizado con exito *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* Hubo un error al copiar el archivo *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

    rlutil::locate(35, 11);
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    system("pause");
}

void VendedorManager::restaurarBackup() 
{
    string origen = "Vendedores.bkp";
    string copia = "Vendedores.dat";

    string comando = "copy " + origen + " " + copia;

    rlutil::setColor(rlutil::COLOR::WHITE);
    rlutil::locate(35, 9);
    int resultado = system(comando.c_str());

    rlutil::locate(35, 10);
    if (resultado == 0) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << "* Restauracion de backup realizada con exito *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << "* Hubo un error al copiar el archivo *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

    rlutil::locate(35, 11);
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    system("pause");
}



bool VendedorManager::LegajoRepetido(int idLegajo) {
    Vendedor registro;
    int cantidad = _archivo.ContarRegistro();

    for (int i = 0; i < cantidad; i++) {
        registro = _archivo.leerRegistro(i);

        if (registro.getNroLegajo() == idLegajo) {
            return true;
        }
    }
    return false;
}

bool VendedorManager::DniRepetido(long long idPersona) {
    VendedorArchivo va;
    Vendedor registro;
    int cantidad = va.ContarRegistro();

    for (int i = 0; i < cantidad; i++) {
        registro = va.leerRegistro(i);

        if (registro.getDni() == idPersona) {
            return true;
        }
    }
    return false;
}

