#define _CRT_SECURE_NO_WARNINGS 
#include "SucursalManager.h"
#include "FuncionesGenerales.h"
#include <iostream>
#include <iomanip>
#include "rlutil.h"
using namespace std;

SucursalManager::SucursalManager() : _archivo()
{

}

void SucursalManager::Menu()
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
        cout << "* Modulo de SUCURSALES *" << endl;
        showItem(" Crear Sucursal ", 47, 14, y == 0);
        showItem(" Listado de Sucursales ", 47, 15, y == 1);
        showItem(" Buscar Sucursal ", 47, 16, y == 2);
        showItem(" Editar Sucursal ", 47, 17, y == 3);
        showItem(" Eliminar Sucursal ", 47, 18, y == 4);
        showItem(" Backup de archivo de Sucursales ", 47, 20, y == 6);
        showItem(" Restauracion de backup de Sucursales ", 47, 21, y == 7);
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
                agregarRegistro();
                system("pause");
                system("cls");
                break;
            case 1:
                system("cls");
                listarRegistros();
                system("cls");
                break;
            case 2:
                system("cls");
                buscarSucursal();
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                editarRegistro();
                system("cls");
                break;
            case 4:
                system("cls");
                borrarSucursal();
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


bool SucursalManager::validarIDUnico(int id)
{
    Sucursal reg;

    int cant = _archivo.contarRegistro();
    for (int i = 0; i < cant; i++) {
        reg = _archivo.leerRegistro(i);
        if (reg.getIdSucursal() == id) {
            return true;
        }
    }
    return false;
}

void SucursalManager::agregarRegistro()
{
    if (_archivo.guardarRegistro(crearRegistro())) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << endl << "* La Sucursal se guardo correctamente *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se pudo guardar la sucursal *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

Sucursal SucursalManager::crearRegistro()
{
    Sucursal reg;
    string id;
    int idSucursal = _archivo.leerUltimoId() + 1;
    string nombre;
    string telefono;
    Direccion d;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de Sucursales *" << endl << endl;
    cout << "Carga de nueva sucursal" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    cout << "ID de Sucursal: #" << idSucursal << endl << endl;
    reg.setIdSucursal(idSucursal);
    cout << "* NOMBRE DE SUCURSAL: ";
    getline(cin, nombre);
    reg.setNombre(nombre);
    cout << "DIRECCIÓN DE LA SUCURSAL: " << endl;
    d.Cargar();
    reg.setDireccion(d);
    cout << "TELEFONO: ";
    getline(cin, telefono);
    reg.setTelefono(telefono);

    return reg;
}



void SucursalManager::salidaEnPantalla()
{
    cout << left;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << setw(5) << "ID";
    cout << setw(21) << "NOMBRE";
    cout << setw(54) << "DIRECCION";
    cout << setw(20) << "TELEFONO";
    cout << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
}

void SucursalManager::mostrarEnLinea(Sucursal reg)
{
    cout << left;
    cout << setw(5) << reg.getIdSucursal();
    cout << setw(21) << reg.getNombre();
    cout << setw(54) << reg.getDireccion().toString();
    cout << setw(20) << reg.getTelefono();

}

void SucursalManager::mostrar(Sucursal reg)
{ 
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "ID SUCURSAL: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "# " << reg.getIdSucursal() << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "NOMBRE: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getNombre() << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "DIRECCION: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getDireccion().toString() << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "TELEFONO: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getTelefono() << endl << endl;
}

void SucursalManager::listarRegistros()
{
    Sucursal reg;

    int opcion = 1, y = 0;
    do {
        rlutil::locate(39, 9);
        rlutil::setColor(rlutil::COLOR::WHITE);
        cout << "* ¿Como desea ordenar el listado de Sucursales? *" << endl;
        showItem(" por ID ", 51, 11, y == 0);
        showItem(" por Nombre ", 51, 12, y == 1);
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
                listarPorID();
                system("pause");
                system("cls");
                break;
            case 1:
                system("cls");
                listarPorNombre();
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

void SucursalManager::listarPorID() 
{
    int cant = _archivo.contarRegistro();
    Sucursal reg;

    salidaEnPantalla();

    for (int i = 0; i < cant; i++) {
        reg = _archivo.leerRegistro(i);
        if (reg.getEstado() == false) {
            mostrarEnLinea(reg);
            cout << endl;
        }
    }
    cout << endl;

}

void SucursalManager::listarPorNombre() 
{
    int cantidad = _archivo.contarRegistro(); 
    Sucursal *vec, reg; 

    vec = new Sucursal[cantidad]; 
    if (vec == nullptr) {

        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay memoria *";
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

    if (cantidad == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay Sucursales para mostrar *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        salidaEnPantalla(); 
        for (int i = 0; i < cantidad; i++) { 
            reg = _archivo.leerRegistro(i); 
            vec[i] = reg; 
        }

        ordenarNombre(vec, cantidad); 
        for (int i = 0; i < cantidad; i++) { 
            if (vec[i].getEstado() == false) { 
                mostrarEnLinea(vec[i]); 
                std::cout << std::endl; 
            }
        }
        std::cout << std::endl;
    }
    delete[]vec;
    cout << endl;

}

void SucursalManager::ordenarNombre(Sucursal obj[], int tam)
{
    Sucursal aux;
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (obj[j].getNombre() > obj[j + 1].getNombre()) {
                aux = obj[j];
                obj[j] = obj[j + 1];
                obj[j + 1] = aux;
            }
        }
    }
}


void SucursalManager::buscarSucursal()
{

    int opcion = 1, y = 0;
    do {
        rlutil::locate(39, 9);
        rlutil::setColor(rlutil::COLOR::WHITE);
        cout << "* Buscador de Sucursales *" << endl;
        showItem(" Buscar por ID ", 45, 11, y == 0);
        showItem(" Buscar por Nombre ", 45, 12, y == 1);
        showItem2(" Volver ", 51, 14, y == 3);


        switch (rlutil::getkey()) {
        case 14: //UP
            rlutil::locate(43, 11 + y);
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
            rlutil::locate(43, 11 + y);
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
                buscarSucursalID();
                system("pause");
                system("cls");
                break;
            case 1:
                system("cls");
                buscarSucursalNombre();
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

void SucursalManager::buscarSucursalID()
{
    int id, pos;
    Sucursal reg;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de SUCURSALES *" << endl << endl;
    cout << "Buscador de Sucursal por ID" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    id = validarInt("Ingrese ID de la Sucursal que desea Buscar: ");
    cout << endl;

    pos = _archivo.buscarPosicion(id);

    if (pos >= 0) {
        reg = _archivo.leerRegistro(pos);
        if (reg.getIdSucursal() == id) {
            mostrar(reg);
        }
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se encontro la sucursal *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

    }
}

void SucursalManager::buscarSucursalNombre()
{
    string nombre;
    Sucursal reg;
    int cant = _archivo.contarRegistro();

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de SUCURSALES *" << endl << endl;
    cout << "Buscador de Sucursal por Nombre" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    cout << "Ingrese Nombre de la Sucursal que desea Buscar: ";
    getline(cin, nombre);
    cout << endl;

    if (cant >= 0) {
        salidaEnPantalla();

        for (int i = 0; i < cant; i++) {
            reg = _archivo.leerRegistro(i);
            if (reg.getNombre() == nombre) {
                mostrarEnLinea(reg);
            }
        }
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se encontro la sucursal *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

    }
    cout << endl;

}



void SucursalManager::editarRegistro()
{
    int id, pos, opcion;
    Sucursal reg;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de SUCURSALES *" << endl << endl;
    cout << "Editar Sucursal" << endl << endl;

    rlutil::setColor(rlutil::COLOR::WHITE);
    rlutil::showcursor();
    id = validarInt("Ingrese ID de la Sucursal que desea editar: ");
    cout << endl;

    pos = _archivo.buscarPosicion(id);

    if (pos >= 0) {
        
        reg = _archivo.leerRegistro(pos);

        if (reg.getEstado() == false) {
            rlutil::hidecursor();
            rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
            cout << endl << "Sucursal a Editar: " << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            mostrar(reg);

            int opc = 1, y = 0;
            do {
                rlutil::setColor(rlutil::COLOR::WHITE);
                rlutil::locate(43, 15);
                cout << "* ¿Que dato desea editar? *" << endl;
                showItem(" Nombre   ", 51, 17, y == 0);
                showItem(" Direccion  ", 51, 18, y == 1);
                showItem(" Telefono  ", 51, 19, y == 2);
                showItem2(" Volver  ", 51, 21, y == 4);


                switch (rlutil::getkey()) {
                case 14: //UP
                    rlutil::locate(49, 17 + y);
                    cout << " " << endl;
                    y--;
                    if (y < 0) {
                        y = 0;
                    }
                    if (y == 3) {
                        y--;
                    }
                    break;
                case 15: //DOWN
                    rlutil::locate(49, 17 + y);
                    cout << " " << endl;
                    y++;
                    if (y > 4) {
                        y = 4;
                    }
                    if (y == 3) {
                        y++;
                    }
                    break;
                case 1: //ENTER

                    switch (y) {
                    case 0: {
                        system("cls");
                        editarNombre(reg, pos);
                        system("pause");
                        opc = 0;
                        system("cls");
                        break;
                    }
                    case 1: {
                        system("cls");
                        editarDireccion(reg, pos);
                        system("pause");
                        opc = 0;
                        system("cls");
                        break;
                    }

                    case 2: {
                        system("cls");
                        editarTelefono(reg, pos);
                        system("pause");
                        opc = 0;
                        system("cls");
                        break;
                    }

                    case 4:
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
            cout << "* La sucursal buscada se encuentra eliminada *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");

        }
    }
    else {
        if (pos == -1) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* La sucursal buscada no existe *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");
        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* No se pudo abrir el archivo *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");
        }
    }
}

void SucursalManager::editarNombre(Sucursal &reg, int pos) 
{
    string n;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << endl << "Sucursal a Editar: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrar(reg);
    cout << endl << endl;
    
    rlutil::showcursor();
    cout << "* Ingrese nuevo Nombre: ";
    getline(cin, n);
    reg.setNombre(n);
    rlutil::hidecursor();
    cout << endl;

    bool modificacion = _archivo.sobreescribirRegistro(reg, pos);

    if (modificacion = true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        cout << "* La sucursal se modifico correctamente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        cout << "Sucursal modificada: " << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        mostrar(reg);
        cout << endl;
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se pudo modificar la sucursal *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

}

void SucursalManager::editarDireccion(Sucursal& reg, int pos)
{
    Direccion d;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << endl << "Sucursal a Editar: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrar(reg);
    cout << endl << endl;
    rlutil::showcursor();

    cout << "* Ingrese nueva direccion: ";
    d.Cargar();
    reg.setDireccion(d);
    rlutil::hidecursor();
    cout << endl;

    bool modificacion = _archivo.sobreescribirRegistro(reg, pos);

    if (modificacion = true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        cout << "* La sucursal se modifico correctamente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        cout << "Sucursal modificada: " << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        mostrar(reg);
        cout << endl;
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se pudo modificar la sucursal *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

void SucursalManager::editarTelefono(Sucursal &reg, int pos) 
{
    string tel;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << endl << "Sucursal a Editar: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrar(reg);
    cout << endl << endl;
    rlutil::showcursor();
    
    cout << "* Ingrese nuevo telefono: ";
    getline(cin, tel);
    reg.setTelefono(tel);
    rlutil::hidecursor();
    cout << endl;

    bool modificacion = _archivo.sobreescribirRegistro(reg, pos);

    if (modificacion = true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        cout << "* La sucursal se modifico correctamente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        cout << "Sucursal modificada: " << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        mostrar(reg);
        cout << endl;
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se pudo modificar la sucursal *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }


}


void SucursalManager::borrarSucursal()
{
    int id, pos;
    Sucursal reg;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de SUCURSALES *" << endl << endl;
    cout << "Borrar Sucursal" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    rlutil::showcursor();

    id = validarInt("Ingrese ID de la Sucursal que desea borrar: ");
    rlutil::hidecursor();
    cout << endl;

    pos = _archivo.buscarPosicion(id);

    if (pos >= 0) {
        reg = _archivo.leerRegistro(pos);

        if (reg.getEstado() == true) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* La sucursal ya se encuentra eliminada *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");

        }
        else {
            rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
            cout << endl << "Sucursal a Borrar: " << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            mostrar(reg);
            cout << endl;

            int opc = 1, y = 0;

            do {
                rlutil::hidecursor();
                rlutil::setColor(rlutil::COLOR::WHITE);
                rlutil::locate(35, 18);
                cout << "* ¿Confirma que desea borrar esta Sucursal? *" << endl;
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
                        reg.setEstado(true);
                        bool modificacion = _archivo.sobreescribirRegistro(reg, pos);

                        if (modificacion = true) {
                            rlutil::setColor(rlutil::COLOR::GREEN);
                            rlutil::locate(39, 25);
                            cout << "* La sucursal se ha borrado correctamente *" << endl;
                            rlutil::setColor(rlutil::COLOR::WHITE);
                            opc = 0;
                        }
                        else {
                            rlutil::setColor(rlutil::COLOR::RED);
                            rlutil::locate(39, 25);
                            cout << "* No se pudo eliminar la sucursal *" << endl;
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
                        cout << "* Se cancelo el borrado de la sucursal *" << endl;
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
        cout << "* La sucursal buscada no existe *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");

    }
}

void SucursalManager::realizarBackup()
{
    string origen = "Sucursales.dat";
    string copia = "Sucursales.bkp";

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

void SucursalManager::restaurarBackup()
{
    string origen = "Sucursales.dat";
    string copia = "Sucursales.bkp";

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
