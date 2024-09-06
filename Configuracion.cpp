#include <iostream>
#include "VehiculosManager.h"
#include "VentasManager.h"
#include "SucursalManager.h"
#include "VendedorManager.h"
#include "ClienteManager.h"
#include "Configuracion.h"
#include "FuncionesGenerales.h"
#include "rlutil.h"
using namespace std;

void Configuracion::Menu() {

    int opc = 1;
    int y = 0;

        system("cls");
    do {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(35, 9);
        cout << (char)254 << " Sistema de Gestion de Ventas e Inventario " << (char)254 << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(47, 11);
        cout << "* Menu Configuraci¢n *" << endl;
        showItem("Archivo Veh¡culos  ", 51, 14, y == 0);
        showItem("Archivo Ventas  ", 51, 15, y == 1);
        showItem("Archivo Vendedores  ", 51, 16, y == 2);
        showItem("Archivo Sucursales  ", 51, 17, y == 3);
        showItem("Archivo Clientes  ", 51, 18, y == 4);
        showItem2("Regresar al menu principal  ", 51, 20, y == 6);

        
        switch(rlutil::getkey()){
            case 14: //UP
            rlutil::locate(49, 14 + y);
            cout << " " << endl;
            y--;
            if (y < 0) {
                y = 0;
            }
            if (y == 5) {
                y--;
            }
            break;
        case 15: //DOWN
            rlutil::locate(49, 14 + y);
            cout << " " << endl;
            y++;
            if (y > 6) {
                y = 6;
            }
            if (y == 5) {
                y++;
            }
            break;
        case 1: //ENTER

            switch (y) {
            case 0:
                subMenuVehiculos();
                system("cls");
                break;
            case 1:
                subMenuVentas();
                break;
            case 2:
                subMenuVendedores();
                break;
            case 3:
                subMenuSucursales();
                break;
            case 4:
                subMenuClientes();
                break;
            case 6:
                opc = 0;
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

void Configuracion::subMenuVehiculos() {
    VehiculosManager vehiculos;

    int opc = 1, y = 0;

    system("cls");
    
    do {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(35, 9);
        cout << (char)149 << " Sistema de Gestion de Ventas e Inventario " << (char)149 << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(47, 11);
        cout << "* Configuraci¢n / Veh¡culos *" << endl;
        showItem(" Realizar backup   ", 51, 14, y == 0);
        showItem(" Restaurar backup  ", 51, 15, y == 1);
        showItem2(" Volver  ", 51, 17, y == 3);


        switch (rlutil::getkey()) {
        case 14: //UP
            rlutil::locate(49, 14 + y);
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
            rlutil::locate(49, 14 + y);
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
                vehiculos.realizarBackup();
                system("cls");
                break;
            case 1:
                system("cls");
                vehiculos.restaurarBackup();
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
    } while (opc != 0);
}

void Configuracion::subMenuVentas() {
    VentasManager ventas;

    int opc = 1, y = 0;

    system("cls");

    do {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(35, 9);
        cout << (char)149 << " Sistema de Gestion de Ventas e Inventario " << (char)149 << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(47, 11);
        cout << "* Configuraci¢n / Ventas *" << endl;
        showItem(" Realizar backup   ", 51, 14, y == 0);
        showItem(" Restaurar backup  ", 51, 15, y == 1);
        showItem2(" Volver  ", 51, 17, y == 3);


        switch (rlutil::getkey()) {
        case 14: //UP
            rlutil::locate(49, 14 + y);
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
            rlutil::locate(49, 14 + y);
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
                ventas.realizarBackup();
                system("cls");
                break;
            case 1:
                system("cls");
                ventas.restaurarBackup();
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
    } while (opc != 0);
}
void Configuracion::subMenuVendedores() {
    VendedorManager vendedores;

    int opc = 1, y = 0;

    system("cls");

    do {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(35, 9);
        cout << (char)149 << " Sistema de Gestion de Ventas e Inventario " << (char)149 << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(47, 11);
        cout << "* Configuraci¢n / Vendedores *" << endl;
        showItem(" Realizar backup   ", 51, 14, y == 0);
        showItem(" Restaurar backup  ", 51, 15, y == 1);
        showItem2(" Volver  ", 51, 17, y == 3);


        switch (rlutil::getkey()) {
        case 14: //UP
            rlutil::locate(49, 14 + y);
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
            rlutil::locate(49, 14 + y);
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
                vendedores.realizarBackup();
                system("cls");
                break;
            case 1:
                system("cls");
                vendedores.restaurarBackup();
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
    } while (opc != 0);
}

void Configuracion::subMenuSucursales() {
    SucursalManager sucursales;

    int opc = 1, y = 0;

    system("cls");

    do {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(35, 9);
        cout << (char)149 << " Sistema de Gestion de Ventas e Inventario " << (char)149 << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(47, 11);
        cout << "* Configuraci¢n / Sucursales *" << endl;
        showItem(" Realizar backup   ", 51, 14, y == 0);
        showItem(" Restaurar backup  ", 51, 15, y == 1);
        showItem2(" Volver  ", 51, 17, y == 3);


        switch (rlutil::getkey()) {
        case 14: //UP
            rlutil::locate(49, 14 + y);
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
            rlutil::locate(49, 14 + y);
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
                sucursales.realizarBackup();
                system("cls");
                break;
            case 1:
                system("cls");
                sucursales.restaurarBackup(); 
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
    } while (opc != 0);
}


void Configuracion::subMenuClientes() {
    ClienteManager clientes;

    int opc = 1, y = 0;

    system("cls");

    do {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(35, 9);
        cout << (char)149 << " Sistema de Gestion de Ventas e Inventario " << (char)149 << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(47, 11);
        cout << "* Configuraci¢n / Clientes *" << endl;
        showItem(" Realizar backup   ", 51, 14, y == 0);
        showItem(" Restaurar backup  ", 51, 15, y == 1);
        showItem2(" Volver  ", 51, 17, y == 3);


        switch (rlutil::getkey()) {
        case 14: //UP
            rlutil::locate(49, 14 + y);
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
            rlutil::locate(49, 14 + y);
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
                clientes.realizarBackup();
                system("cls");
                break;
            case 1:
                system("cls");
                clientes.restaurarBackup();
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
    } while (opc != 0);
}