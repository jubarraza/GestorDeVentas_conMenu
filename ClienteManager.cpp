#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <vector>
#include <locale>
#include "ClienteManager.h"
#include "FuncionesGenerales.h"
#include "rlutil.h"
using namespace std;

ClienteManager::ClienteManager() : _archivo("Clientes.dat")
{
}

void ClienteManager::Menu()
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
        cout << "* Modulo de CLIENTES *" << endl;
        showItem(" Crear cliente ", 47, 14, y == 0);
        showItem(" Listado de clientes ", 47, 15, y == 1);
        showItem(" Buscar cliente ", 47, 16, y == 2);
        showItem(" Editar cliente ", 47, 17, y == 3);
        showItem(" Eliminar cliente ", 47, 18, y == 4);
        showItem(" Recuperar cliente eliminado", 47, 19, y == 5);
        showItem(" Backup de archivo de Clientes ", 47, 21, y == 7);
        showItem(" Restauracion de backup de Clientes ", 47, 22, y == 8);
        showItem2("Volver al menu principal ", 47, 24, y == 10);


        switch (rlutil::getkey()) {
        case 14: //UP
            rlutil::locate(49, 14 + y);
            cout << " " << endl;
            y--;
            if (y < 0) {
                y = 0;
            }
            if (y == 6 || y == 9) {
                y--;
            }
            break;
        case 15: //DOWN
            rlutil::locate(49, 14 + y);
            cout << " " << endl;
            y++;
            if (y > 10) {
                y = 10;
            }
            if (y == 6 || y == 9) {
                y++;
            }
            break;
        case 1: //ENTER

            switch (y) {
            case 0:
                system("cls");
                agregarCliente();
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
                buscadorDeClientes();
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                editarCliente();
                system("cls");
                break;
            case 4:
                system("cls");
                borrarCliente();
                system("cls");
                break;
            case 5:
                system("cls");
                resturarCliente(); 
                system("cls");
                break;
            case 7:
                system("cls");
                realizarBackup();
                system("cls");
                break;
            case 8:
                system("cls");
                restaurarBackup();
                system("cls");
                break;
            case 10:
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

void ClienteManager::agregarCliente()
{
    if (_archivo.guardarCliente(crearCliente())) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << endl << "* El cliente se guardó correctamente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se pudo guardar el cliente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

Cliente ClienteManager::crearCliente()
{
    string email, tel;
    Direccion d;
    Cliente reg;
    int opc;
regreso:
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de CLIENTES *" << endl << endl;
    cout << "Carga de nuevo cliente" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    
    reg.CargarPersona();
    bool resultado = DniRepetido(reg.getDni());
    if (resultado) {

        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* Cliente ya existente *";
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();
        int opcion =1, y = 0;

        do {
            rlutil::locate(47, 15);
            cout << "* ¿Desea cargar otro cliente? *" << endl;
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
    cout << "EMAIL: ";
    getline(cin, email);
    reg.setEmail(email);
    tel = validarStringNumerico("TELEFONO: ");
    reg.setTelefono(tel);
    cout << "DIRECCION: " << endl;
    d.Cargar();
    reg.setDireccion(d);
    reg.setEliminado(false);
    rlutil::hidecursor();

    return reg;
}

Cliente ClienteManager::crearCliente(long long dni) //variacion cuando ya tenemos DNI ingresado
{
    string email, tel;
    Direccion d;
    Cliente reg;
    char opc;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de CLIENTES *" << endl << endl;
    cout << "Carga de nuevo cliente" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    
    reg.CargarPersona(dni);
    cout << "EMAIL: ";
    getline(cin, email);
    reg.setEmail(email);
    tel = validarStringNumerico("TELEFONO: ");
    reg.setTelefono(tel);
    cout << "DIRECCION: " << endl;
    d.Cargar();
    reg.setDireccion(d);
    reg.setEliminado(false);

    return reg;
}

void ClienteManager::mostrarCliente(Cliente reg)
{
    rlutil::setColor(rlutil::COLOR::WHITE);
    reg.MostrarPersona();
    cout << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "EMAIL: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getEmail() << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "TELEFONO: ";
    rlutil::setColor(rlutil::COLOR::WHITE); 
    cout << reg.getTelefono() << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "DIRECCION: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getDireccion().toString();
    cout << endl << "ESTADO: " << reg.getEliminado();
}

void ClienteManager::mostrarClienteEnLinea(Cliente reg) 
{
    rlutil::setColor(rlutil::COLOR::WHITE);
    reg.MostrarPersonaEnLinea();
    cout << setw(33) << reg.getEmail();
    cout << setw(20) << reg.getTelefono();
    cout << setw(30) << reg.getDireccion().toString();
    cout << endl;
}

void ClienteManager::encabezadoClientes()
{
    cout << left;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << setw(55) << " " << "* Listado de Clientes *" << endl << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);

    cout << setw(14) << "DNI";
    cout << setw(20) << "NOMBRE ";
    cout << setw(20) << "APELLIDO ";
    cout << setw(23) << "FECHA DE NACIMIENTO ";
    cout << setw(33) << "EMAIL ";
    cout << setw(20) << "TELEFONO ";
    cout << setw(30) << "DIRECCION ";
    cout << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
}

void ClienteManager::menuListado()
{
    int opcion = 1, y = 0;
    do {
        rlutil::locate(39, 9);
        rlutil::setColor(rlutil::COLOR::WHITE);
        cout << "* ¿Como desea ordenar el listado de Clientes? *" << endl;
        showItem(" por Orden de Carga ", 51, 11, y == 0);
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
                listarClientes();
                system("pause");
                system("cls");
                break;
            case 1:
                system("cls");
                listarClientesXApellido();
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

void ClienteManager::listarClientes() //por oden de carga
{
    int i, cantidad = _archivo.contarClientes();
    Cliente reg;

    if (cantidad == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay Clientes para mostrar *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        encabezadoClientes();

        for (i = 0; i < cantidad; i++) {
            reg = _archivo.leerCliente(i);
            if (reg.getEliminado() == false) {
                mostrarClienteEnLinea(reg);
            }

        }

    }
    cout << endl;

}

void ClienteManager::listarClientesXApellido()
{

    int i, cantidad = _archivo.contarClientes();
    Cliente reg;
    vector <Cliente> vec;

    if (cantidad == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay Clientes para mostrar *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        encabezadoClientes();
        for (i = 0; i < cantidad; i++) {
            reg = _archivo.leerCliente(i);
            vec.push_back(reg);
        }
        ordenar(vec, cantidad);
        for (i = 0; i < cantidad; i++) {
            if (vec[i].getEliminado() == false) {
                mostrarClienteEnLinea(vec[i]);
            }
        }
        cout << endl;

    }
}

void ClienteManager::ordenar(vector<Cliente>& vec, int cantidad) {
    Cliente aux;

    for (int i = 0; i < cantidad; i++) {

        for (int j = i; j < cantidad; j++) {

            if (vec[i].getApellido() > vec[j].getApellido()) {

                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;

            }
        }
    }

}

int ClienteManager::buscarCliente(long long dni)
{
    Cliente reg;
    FILE* p;
    int pos = 0;
    p = fopen(_archivo.getNombreArchivo().c_str(), "rb");
    if (p == nullptr) {
        return -2; //no se abrio el archivo
    }
    while (fread(&reg, sizeof reg, 1, p) == 1) {
        if (reg.getDni() == dni) {
            fclose(p); //cierro el archivo porque ya encontre el cliente
            return pos;
        }
        pos++;
    }
    fclose(p);

    return -1; //se recorrio el archivo y no existe el cliente
}

void ClienteManager::buscadorDeClientes()
{
    int cantReg = _archivo.contarClientes();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* Error de Archivo *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        int pos;
        long long dni;

        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(10, 1);
        cout << "* Modulo de CLIENTES *" << endl << endl;
        cout << "Buscador de clientes" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        
        rlutil::showcursor();
        dni = validarLong("Ingrese el DNI a buscar: ");
        cout << endl;
        
        pos = buscarCliente(dni);
        if (pos == -1) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << endl << "* No se Encontraron Clientes con el DNI buscado *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
        if (pos >= 0) {
            Cliente reg = _archivo.leerCliente(pos);
            if (reg.getEliminado() == false) {
                mostrarCliente(reg);
                cout << endl;
            }
            else {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << "* El Registro se Encuentra Eliminado *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }
        }
        cout << endl;

    }
}

void ClienteManager::editarCliente()
{
    long long dni;
    int opcion;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de CLIENTES *" << endl << endl;
    cout << "Editar cliente" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();
    dni = validarLong("Ingrese DNI del Cliente a editar: ");
    cout << endl;

    int pos = buscarCliente(dni);

    if (pos >= 0) {
        Cliente reg;
        reg = _archivo.leerCliente(pos);

        if (reg.getEliminado() == false) {
            rlutil::hidecursor();
            rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
            cout << endl << "Cliente a Editar: " << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            mostrarCliente(reg);

            int opc = 1, y = 0;
            do {
                rlutil::setColor(rlutil::COLOR::WHITE);
                rlutil::locate(43, 17);
                cout << "* ¿Que dato desea editar? *" << endl;
                showItem(" Email   ", 51, 19, y == 0);
                showItem(" Telefono  ", 51, 20, y == 1);
                showItem(" Direccion  ", 51, 21, y == 2);
                showItem2(" Volver  ", 51, 23, y == 4);


                switch (rlutil::getkey()) {
                case 14: //UP
                    rlutil::locate(49, 19 + y);
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
                    rlutil::locate(49, 19 + y);
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
                        editarEmail(reg, pos);
                        system("pause");
                        opc = 0;
                        system("cls");
                        break;
                    }
                    case 1: {
                        system("cls");
                        editarTelefono(reg, pos);
                        system("pause");
                        opc = 0;
                        system("cls");
                        break;
                    }
                        
                    case 2: {
                        system("cls");
                        editarDireccion(reg, pos);
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

            cout << endl;

        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* El cliente buscado se encuentra eliminado *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");
        }

    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* Error al buscar el cliente. Codigo error " << pos << " *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
}

void ClienteManager::editarEmail(Cliente &reg, int pos) 
{
    string e;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << endl << "Cliente a Editar: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarCliente(reg);
    cout << endl;
    rlutil::showcursor();
    cout << endl << "Ingrese nuevo email: ";
    getline(cin, e);
    reg.setEmail(e);
    rlutil::hidecursor();
    cout << endl;
    

    bool result = _archivo.sobreescribirCliente(reg, pos);

    if (result == true) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << endl << "* El cliente se editó correctamente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        cout << "Cliente modificado: " << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        mostrarCliente(reg);
        cout << endl << endl;
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se pudo editar el cliente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

void ClienteManager::editarTelefono(Cliente &reg, int pos) 
{
    string tel;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << endl << "Cliente a Editar: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarCliente(reg);
    cout << endl << endl;
    rlutil::showcursor();

    tel = validarStringNumerico("Ingrese nuevo telefono: ");
    reg.setTelefono(tel);
    rlutil::hidecursor();
    cout << endl;

    bool result = _archivo.sobreescribirCliente(reg, pos);

    if (result == true) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << endl << "* El cliente se editó correctamente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        cout << "Cliente modificado: " << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        mostrarCliente(reg);
        cout << endl << endl;
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se pudo editar el cliente *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

void ClienteManager::editarDireccion(Cliente &reg, int pos) 
{
    Direccion d;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << endl << "Cliente a Editar: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarCliente(reg);
    cout << endl << endl;
    rlutil::showcursor();
    cout << "Ingrese nueva dirección: ";
    d.Cargar();
    reg.setDireccion(d);
    rlutil::hidecursor();

    cout << endl;

    bool result = _archivo.sobreescribirCliente(reg, pos);

    if (result == true) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << endl << "* El cliente se editó correctamente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        cout << "Cliente modificado: " << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        mostrarCliente(reg);
        cout << endl << endl;
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se pudo editar el cliente *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}


void ClienteManager::borrarCliente()
{
    long long dni;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de CLIENTES *" << endl << endl;
    cout << "Eliminar cliente" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    rlutil::showcursor();

    dni = validarLong("Ingrese DNI del Cliente a borrar: ");
    rlutil::hidecursor();
    cout << endl; 

    int pos = buscarCliente(dni);

    if (pos >= 0) {
        Cliente reg;
        reg = _archivo.leerCliente(pos);

        if (reg.getEliminado() == true) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* El cliente ya se encuentra eliminado *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");

        }
        else {
            rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
            cout << endl << "Cliente a Borrar: " << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            mostrarCliente(reg);
            cout << endl;

            int opc = 1, y = 0;

            do {
                rlutil::hidecursor();
                rlutil::setColor(rlutil::COLOR::WHITE);
                rlutil::locate(35, 18);
                cout << "* ¿Confirma que desea borrar este Cliente? *" << endl;
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
                        bool result = _archivo.sobreescribirCliente(reg, pos);
                        if (result) {
                            rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
                            rlutil::locate(39, 25);
                            cout << "* El cliente se ha borrado correctamente *" << endl;
                            rlutil::setColor(rlutil::COLOR::WHITE);
                            opc = 0;
                        }
                        else {
                            rlutil::setColor(rlutil::COLOR::RED);
                            rlutil::locate(39, 25);
                            cout << "* No se pudo eliminar el cliente *" << endl;
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
                        cout << "* Se cancelo el borrado del cliente *" << endl;
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
        cout << "* El cliente buscado no existe *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
}

void ClienteManager::resturarCliente()
{
    int cantReg = _archivo.contarClientes();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No existe archivo de Clientes *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    else {
        int id, pos;
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(10, 1);
        cout << "* Modulo de Clientes *" << endl << endl;
        cout << "Restauracion de cliente eliminado" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::showcursor();

        id = validarInt("Ingrese el DNI del cliente a restaurar: ");
        rlutil::hidecursor();
        cout << endl;

        pos = buscarCliente(id);

        if (pos >= 0) {
            Cliente reg;
            reg = _archivo.leerCliente(pos);

            if (reg.getEliminado() == true) {
                
                system("cls");
                rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
                cout << endl << "Cliente a Restaurar: " << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                mostrarCliente(reg);
                cout << endl;

                int opc = 1, y = 0;

                do {
                    rlutil::hidecursor();
                    rlutil::setColor(rlutil::COLOR::WHITE);
                    rlutil::locate(35, 18);
                    cout << "* ¿Confirma que desea restaurar este Cliente? *" << endl;
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
                        case 0: { //SI
                            reg.setEliminado(false);
                            cout << endl;
                            bool restaurar = _archivo.sobreescribirCliente(reg, pos);
                            if (restaurar == true) {
                                rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
                                rlutil::locate(39, 25);
                                cout << "* Cliente restaurado con Exito *" << endl << endl;
                                rlutil::setColor(rlutil::COLOR::WHITE);
                                opc = 0;
                            }
                            else {
                                rlutil::setColor(rlutil::COLOR::RED);
                                rlutil::locate(39, 25);
                                cout << "* No se pudo restaurar el cliente *" << endl;
                                rlutil::setColor(rlutil::COLOR::WHITE);
                            }
                            rlutil::locate(39, 26);
                            system("pause");
                            system("cls");
                            break;
                        }
                        case 1: // NO
                            rlutil::setColor(rlutil::COLOR::RED);
                            rlutil::locate(39, 25);
                            cout << "* Se cancelo la restauracion del cliente *" << endl;
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
            else {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << endl << "* El cliente a restaurar no se encuentra eliminado *" << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                system("pause");
            }

        }
        else {
            if (pos == -1) {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << endl << "* No existen clientes con el DNI buscado *" << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }
            if (pos == -2) {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << endl << "* No se pudo abrir el archivo de Clientes *" << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }
            system("pause");
        }

    }

}

void ClienteManager::resturarCliente(long long dni, int pos)
{
    int opc = 1, y = 0;
	Cliente reg;

	reg = _archivo.leerCliente(pos);

    cout << endl;
    mostrarCliente(reg);
	
    do {
        rlutil::hidecursor();
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(35, 15);
        cout << "* ¿Confirma que desea restaurar este Cliente? *" << endl;
        showItem(" Si   ", 51, 17, y == 0);
        showItem(" No  ", 51, 18, y == 1);


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
            case 0: {
                reg.setEliminado(false);
                cout << endl;

                bool restaurar = _archivo.sobreescribirCliente(reg, pos);

                if (restaurar == true) {
                    cout << endl << "* Registro Restaurado con Exito *" << endl << endl;
                }
                else {
                    cout << endl << "* No se Pudo Restaurar el Registro *" << endl;
                }
                opc = 0;
                system("pause");
                break;
            }
            case 1:
                rlutil::setColor(rlutil::COLOR::RED);
                rlutil::locate(39, 25);
                cout << "* Se cancelo la restauracion del cliente *" << endl;
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
    cout << endl;
}


void ClienteManager::realizarBackup()
{
    string origen = "Clientes.dat";
    string copia = "Clientes.bkp";

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

void ClienteManager::restaurarBackup()
{
    string origen = "Clientes.bkp";
    string copia = "Clientes.dat";

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


bool ClienteManager::DniRepetido(long long idPersona) {
    ClienteArchivo ca;
    Cliente registro;
    int cantidad = ca.contarClientes();

    for (int i = 0; i < cantidad; i++) {
        registro = ca.leerCliente(i);

        if (registro.getDni() == idPersona) {
            return true;
        }
    }
    return false;
}