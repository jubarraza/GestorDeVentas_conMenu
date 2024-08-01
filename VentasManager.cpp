#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "ClienteManager.h"
#include "FuncionesGenerales.h"
#include "VentasManager.h"
#include "SucursalManager.h"
#include "rlutil.h"
#include "VendedorManager.h"
#include "VehiculosManager.h"
using namespace std;


VentasManager::VentasManager() : _archivo("Ventas.dat")
{

}

void VentasManager::Menu()
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
        cout << "* Modulo de VENTAS *" << endl;
        showItem(" Cargar venta ", 47, 14, y == 0);
        showItem(" Listado de ventas ", 47, 15, y == 1);
        showItem(" Buscar venta ", 47, 16, y == 2);
        showItem(" Editar venta ", 47, 17, y == 3);
        showItem(" Eliminar venta ", 47, 18, y == 4);
        showItem(" Recuperar venta eliminada", 47, 19, y == 5);
        showItem(" Backup de archivo de Ventas ", 47, 21, y == 7);
        showItem(" Restauracion de backup de Ventas ", 47, 22, y == 8);
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
                agregarVenta();
                system("pause");
                system("cls");
                break;
            case 1:
                system("cls");
                menuListados();
                system("cls");
                break;
            case 2:
                system("cls");
                buscadorDeVentas();
                system("cls");
                break;
            case 3:
                system("cls");
                editarVenta();
                system("cls");
                break;
            case 4:
                system("cls");
                borrarVenta();
                system("cls");
                break;
            case 5:
                system("cls");
                restaurarVentaBorrada();
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


void VentasManager::agregarVenta()
{
    if (_archivo.guardarVenta(crearVenta())) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << endl << "* La venta se guardó correctamente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se pudo guardar la venta *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

Venta VentasManager::crearVenta()
{
    int id = _archivo.leerUltimoId() + 1;
    int nroLegajo, idSucursal, idVehiculo;
    long long dni;
    float gastos, total = 0;
    Fecha f;
    Venta reg;
    bool clienteValido;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENTAS *" << endl << endl;
    cout << "Carga de nueva venta" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    cout << "VENTA: #" << id << endl << endl;
    reg.setIdVenta(id);

    rlutil::showcursor();
    
    cout << "* INGRESE FECHA DE VENTA: " << endl;
    f.Cargar();
    reg.setFechaVenta(f);
    cout << endl;    

    //Validacion del cliente
    dni = validarLong("* INGRESE DNI DEL CLIENTE: ");
    cout << endl;
    
    int posCliente = validarCliente(dni);

    if (posCliente >= 0) {

        Cliente cliente;
        ClienteArchivo archivoClientes;
        ClienteManager managerClientes;
        cliente = archivoClientes.leerCliente(posCliente);

        if (cliente.getEliminado() == true) {
            
            int opcion = 1, y = 0;
            do {
                rlutil::locate(40, 15);
                cout << "* El cliente ingresado esta eliminado ¿Desea restaurarlo? *" << endl;
                showItem(" Restaurar cliente eliminado ", 51, 17, y == 0);
                showItem(" Cargar nuevo Cliente ", 51, 18, y == 1);


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
                        managerClientes.resturarCliente(dni, posCliente);
                        opcion = 0;
                        system("cls");
                        break;
                    case 1:
                        system("cls");
                        cliente = crearNuevoCliente();
                        reg.setDniCliente(cliente.getDni());
                        posCliente = validarCliente(cliente.getDni());
                        opcion = 0;
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
        else {
            reg.setDniCliente(dni);
        }
    }
    else {
        int opcion = 1, y = 0;

        do {
            rlutil::locate(47, 15);
            cout << "* El cliente ingresado no existe ¿Desea cargarlo? *" << endl;
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
                    crearNuevoClienteConDNI(dni);
                    reg.setDniCliente(dni);
                    posCliente = validarCliente(dni);
                    system("cls");
                    break;
                case 1:
                    rlutil::locate(45, 21);
                    rlutil::setColor(rlutil::COLOR::RED);
                    cout << "* No se pudo finalizar la creacion de la venta *" << endl;
                    rlutil::setColor(rlutil::COLOR::WHITE);
                    rlutil::locate(45, 22);
                    system("pause");
                    opcion = 0;
                    system("cls");
                    Menu();
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

    mostrarClienteAsociado(posCliente);
    cout << endl;
    
    //Validacion Sucursal
    idSucursal = validarInt("* INGRESE ID DE SUCURSAL: ");
    cout << endl;
    
    int posSucursal = validarSucursal(idSucursal);
    if (posSucursal >= 0) {
        reg.setIdSucursal(idSucursal);
    }
    else {
        do {
            if (posSucursal == -1) {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << "* La sucursal no existe. Intente nuevamente *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }
            if (posSucursal == -2) {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << "* La sucursal se encuentra eliminada. Solo se permiten sucursales existentes *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }
            cout << endl;
            idSucursal = validarInt("* Ingrese ID de Sucursal: ");
            posSucursal = validarSucursal(idSucursal); 
        } while (posSucursal < 0);
        system("cls");
        reg.setIdSucursal(idSucursal);
        
    }
    mostrarSucursalAsociada(posSucursal);
    cout << endl;

    
    //Validacion Vendedor
    nroLegajo = validarInt("* INGRESE LEGAJO DEL VENDEDOR: ");
    cout << endl; 

    int posVendedor = validarVendedor(nroLegajo);
    if (posVendedor >= 0) {
        reg.setNroLegajo(nroLegajo);
    }
    else {
        do {
            if (posVendedor == -1) {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << "* El vendedor no existe. Intente nuevamente *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }
            if (posVendedor == -2) {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << "* El vendedor se encuentra eliminado. Solo se permiten vendedores activos *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }
            cout << endl;
            nroLegajo = validarInt("* Ingrese Legajo del Vendedor: ");
            posVendedor = validarVendedor(nroLegajo);
        } while (posVendedor < 0);
        system("cls");
        reg.setNroLegajo(nroLegajo); 

    }
    mostrarVendedorAsociado(posVendedor);
    cout << endl;
    
    //Validacion Vehiculo
    idVehiculo = validarInt("* INGRESE ID DEL VEHICULO ADQUIRIDO: ");
    cout << endl;

    bool vehiculoDisponible = validarVehiculo(idVehiculo);
    
    if (vehiculoDisponible == true) { 
        reg.setIdVehiculo(idVehiculo);
    }
    mostrarVehiculoAsociado(idVehiculo);
    cout << endl; 
    
    //carga Datos Administrativos
    gastos = pedirNumeroFloat("* INGRESE GASTOS ADMINISTRATIVOS: $");
    reg.setGastosAdm(gastos); 

    //mostrar Resumen final de la Venta
    system("cls");
    rlutil::hidecursor();
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(0, 10);
    cout << "* Datos de la venta *" << endl << endl;
    cout << "Venta: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "# " << reg.getIdVenta() << endl;
    cout << endl;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "Fecha de Venta: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getFechaVenta().toString() << endl;
    cout << endl;
    mostrarClienteAsociado(reg.getDniCliente());
    cout << endl;
    mostrarSucursalAsociada(reg.getIdSucursal());
    mostrarVendedorAsociado(reg.getNroLegajo());
    cout << endl;
    mostrarVehiculoAsociado(reg.getIdVehiculo());
    cout << endl;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "Gastos Administrativos: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "$ " << formatearNumero(reg.getGastosAdm()) << endl;

    //calculo Total
    total = calcularPrecioTotal(reg.getGastosAdm(), obtenerPrecioVehiculo(idVehiculo));
    reg.setTotalVentas(total);
    cout << endl;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "* Total Venta: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "$ " << formatearNumero(reg.getTotalVenta()) << endl;
    cout << endl;

    //estado de venta: Activa
    reg.setEliminado(false);

    return reg;
}


void VentasManager::mostrarVenta(Venta reg)
{
    cout << left;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << setw(0) << "VENTA: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "# " << reg.getIdVenta() << "         ";
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "FECHA DE VENTA: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getFechaVenta().toString();
    cout << endl << endl;

    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "CLIENTE: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << mostrarNombreCliente(reg.getDniCliente());
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << " - DNI: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << reg.getDniCliente() << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "SUCURSAL: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << mostrarNombreSucursal(reg.getIdSucursal()) << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "VENDEDOR: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << mostrarNombreVendedor(reg.getNroLegajo()) << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "VEHICULO COMPRADO: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << mostrarNombreVehiculo(reg.getIdVehiculo()) << endl;
    
    string gastosFormateado = formatearNumero(reg.getGastosAdm());
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "GASTOS ADMINISTRATIVOS: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "$ " << gastosFormateado << endl;
    
    string totalFormateado = formatearNumero(reg.getTotalVenta());
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << "TOTAL VENTA: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "$ " << totalFormateado << endl;
}

void VentasManager::encabezadoListadoVentas() 
{
    cout << left;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << setw(55) << " " << "* Listado de Ventas *" << endl << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);

    cout << setw(5) << "#ID";
    cout << setw(14) << "FECHA VENTA ";
    cout << setw(19) << "CLIENTE ";
    cout << setw(25) << "SUCURSAL ";
    cout << setw(20) << "VENDEDOR ";
    cout << setw(26) << "VEHICULO COMPRADO ";
    cout << setw(19) << "GASTOS ADM ";
    cout << setw(16) << "TOTAL VENTA ";
    cout << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

}

void VentasManager::mostrarVentaEnLinea(Venta reg)
{
    cout << left;
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << endl;
    cout << setw(5) << reg.getIdVenta();
    cout << setw(14) << reg.getFechaVenta().toString();
    cout << setw(19) << mostrarNombreCliente(reg.getDniCliente());
    cout << setw(25) << mostrarNombreSucursal(reg.getIdSucursal());
    cout << setw(20) << mostrarNombreVendedor(reg.getNroLegajo());
    cout << setw(26) << mostrarNombreVehiculo(reg.getIdVehiculo());
    string gastosFormateado = formatearNumero(reg.getGastosAdm());
    cout << setw(2) << "$ " << setw(16) << gastosFormateado;
    string totalFormateado = formatearNumero(reg.getTotalVenta());
    cout << setw(2) << "$ " << setw(16) << totalFormateado;
    
    
}



void VentasManager::menuListados()
{

    int opcion = 1, y = 0;
    do {
        rlutil::locate(39, 9);
        rlutil::setColor(rlutil::COLOR::WHITE);
        cout << "* ¿Como desea ordenar el listado de Ventas? *" << endl;
        showItem(" por ID de Venta ", 51, 11, y == 0);
        showItem(" por Fecha de Venta ", 51, 12, y == 1);
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
                listarVentas();
                system("pause");
                system("cls");
                break;
            case 1:
                system("cls");
                listarVentasXFecha();
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

void VentasManager::listarVentas()
{
    int i, cantidad = _archivo.contarVentas();
    Venta reg;

    if (cantidad == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay Ventas para mostrar *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        encabezadoListadoVentas();

        for (i=0; i < cantidad; i++) {
        
            reg = _archivo.leerVenta(i);
            if (reg.getEliminado() == false) {
                mostrarVentaEnLinea(reg); 
            }
        
        }
        cout << endl;

    }
    cout << endl;
    
}

void VentasManager::ordenar(vector<Venta>& vec, int cantidad) {
    Venta aux;

    for (int i = 0; i < cantidad; i++) {

        for (int j = i; j < cantidad; j++) {

            if (vec[i].getFechaVenta() > vec[j].getFechaVenta()) {
                 
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;

            }
        }
    }
}

void VentasManager::listarVentasXFecha()
{
    int i, cantidad = _archivo.contarVentas();
    Venta reg;
    vector <Venta> vec;

    if (cantidad == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay Ventas para mostrar *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        encabezadoListadoVentas();
        for (i = 0; i < cantidad; i++) {
            reg = _archivo.leerVenta(i);
            vec.push_back(reg);
        }

        ordenar(vec, cantidad); 
        for (i = 0; i < cantidad; i++) {
            if (vec[i].getEliminado() == false) {
                mostrarVentaEnLinea(vec[i]);
            }
        }
        cout << endl;

    }
    cout << endl;
}



int VentasManager::buscarVenta(int idVenta)
{
    Venta reg;
    FILE* p;
    int pos = 0;
    p = fopen(_archivo.getNombreArchivo().c_str(), "rb");
    if (p == nullptr) {
        return -2; //no se abrio el archivo
    }
    while (fread(&reg, sizeof reg, 1, p) == 1) {
        if (reg.getIdVenta() == idVenta) {
            fclose(p); //cierro el archivo porque ya encontre la empresa
            return pos;
        }
        pos++;
    }
    fclose(p);

    return -1; //se recorrio el archivo y no existe el codigo
}

void VentasManager::buscadorDeVentas()
{
    int cantReg = _archivo.contarVentas();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* Error de Archivo *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    else {
        int opcion = 1, y = 0;
        do {
            rlutil::locate(44, 9);
            rlutil::setColor(rlutil::COLOR::WHITE);
            cout << "* Buscador de Ventas *" << endl;
            showItem(" Buscar por ID ", 45, 11, y == 0);
            showItem(" Buscar por Fecha de Venta ", 45, 12, y == 1);
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
                    buscarVentaPorID();
                    system("pause");
                    system("cls");
                    break;
                case 1:
                    system("cls");
                    buscarVentaPorFecha();
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
    cout << endl;
}

void VentasManager::buscarVentaPorID()
{
    int id, pos;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENTAS *" << endl << endl;
    cout << "Buscador de ventas" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();

    id = validarInt("Ingrese el ID a buscar: ");
    cout << endl;

    pos = buscarVenta(id);

    if (pos == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se encontraron ventas con el ID buscado *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    if (pos >= 0) {
        Venta reg;
        reg = _archivo.leerVenta(pos);
        if (reg.getEliminado() == false) {
            mostrarVenta(reg);
            cout << endl;
        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* La venta buscada se encuentra eliminada *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
    }
    cout << endl;
    rlutil::hidecursor();
}

void VentasManager::buscarVentaPorFecha()
{
    Fecha f;
    Venta reg;
    int cantReg, contador = 0;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENTAS *" << endl << endl;
    cout << "Buscador de ventas" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();

    cout << "Ingrese fecha a buscar:" << endl;
    f.Cargar();
    cout << endl;

    cantReg = _archivo.contarVentas();
    for (int i = 0; i < cantReg; i++) {
        reg = _archivo.leerVenta(i);
        if (reg.getEliminado() == false && reg.getFechaVenta().getAnio() == f.getAnio() && reg.getFechaVenta().getMes() == f.getMes() && reg.getFechaVenta().getDia() == f.getDia()) {
            if (contador == 0) {
                encabezadoListadoVentas();
                mostrarVentaEnLinea(reg);
                contador++;
            }
            else {
                mostrarVentaEnLinea(reg);
                contador++;

            }
        }
    }
    if (contador == 0) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No hay ventas para la fecha buscada * " << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

    cout << endl;
    rlutil::hidecursor();
}



void VentasManager::editarVenta()
{
    int id;
    int opcion;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENTAS *" << endl << endl;
    cout << "Editar venta" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();
    id = validarInt("Ingrese ID de Venta a editar: ");
    cout << endl;
    
    int pos = buscarVenta(id);
    
    if (pos >= 0) {
        Venta reg;
        reg = _archivo.leerVenta(pos);

        if (reg.getEliminado() == false) {
            rlutil::hidecursor();
            rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
            cout << endl << "Venta a Editar: " << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            mostrarVenta(reg);

            int opc = 1, y = 0;
            do {
                rlutil::setColor(rlutil::COLOR::WHITE);
                rlutil::locate(43, 17);
                cout << "* ¿Que dato desea editar? *" << endl;
                showItem(" Fecha de Venta", 51, 19, y == 0);
                showItem(" Gastos Administrativos", 51, 20, y == 1);
                showItem2(" Volver  ", 51, 23, y == 3);


                switch (rlutil::getkey()) {
                case 14: //UP
                    rlutil::locate(49, 19 + y);
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
                    rlutil::locate(49, 19 + y);
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
                    case 0: {
                        system("cls");
                        editarFechaVenta(reg, pos);
                        system("pause");
                        opc = 0;
                        system("cls");
                        break;
                    }
                    case 1: {
                        system("cls");
                        editarGastosAdm(reg, pos);
                        system("pause");
                        opc = 0;
                        system("cls");
                        break;
                    }

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

            cout << endl;

        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* La venta buscada se encuentra eliminada *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");
        }
    
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* Error al buscar la venta. Codigo: (";
        if (pos == -1) {
            cout << pos << ") La venta no existe *" << endl;
        }
        if (pos == -2) {
            cout << pos << ") No se pudo abrir el archivo *" << endl;

        }
    }
    rlutil::setColor(rlutil::COLOR::WHITE);
}

void VentasManager::editarFechaVenta(Venta &reg, int pos) {
        Fecha f;
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        cout << endl << "Venta a Editar: " << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        mostrarVenta(reg);
        cout << endl << endl;

        rlutil::showcursor();
        cout << "Ingrese la nueva fecha de venta:" << endl;
        f.Cargar();
        reg.setFechaVenta(f);
        cout << endl;

        bool result = _archivo.sobreescribirVenta(reg, pos); 

        if (result == true) {
            rlutil::setColor(rlutil::COLOR::GREEN);
            cout << "* Se edito correctamente la venta *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* No se edito la venta *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
}

void VentasManager::editarGastosAdm(Venta &reg, int pos) {
    float gastos;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << endl << "Venta a Editar: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarVenta(reg);
    cout << endl << endl;

    rlutil::showcursor();
    gastos = validarFloat("Ingrese nuevo valor de Gastos Administrativos: $ ");
    reg.setGastosAdm(gastos);

    bool result = _archivo.sobreescribirVenta(reg, pos);
    if (result == true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        cout << "* Se edito correctamente la venta *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se edito la venta *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

}


void VentasManager::borrarVenta()
{
    int id;
    int opc;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENTAS *" << endl << endl;
    cout << "Borrar Venta" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    rlutil::showcursor();

    id = validarInt("Ingrese ID de Venta a borrar: ");
    rlutil::hidecursor();
    cout << endl; 

    int pos = buscarVenta(id); 

    if (pos >= 0) {
        Venta reg;
        reg = _archivo.leerVenta(pos);

        if (reg.getEliminado() == true) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* La venta ya se encuentra eliminada *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");
        }
        else {
            rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
            cout << endl << "Venta a Borrar: " << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            mostrarVenta(reg);
            cout << endl;

            int opc = 1, y = 0;

            do {
                rlutil::hidecursor();
                rlutil::setColor(rlutil::COLOR::WHITE);
                rlutil::locate(35, 18);
                cout << "* ¿Confirma que desea borrar esta Venta? *" << endl;
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
                        bool result = _archivo.sobreescribirVenta(reg, pos);
                        if (result = true) {
                            rlutil::setColor(rlutil::COLOR::GREEN);
                            rlutil::locate(39, 25);
                            cout << "* La venta se ha borrado correctamente *" << endl;
                            rlutil::setColor(rlutil::COLOR::WHITE);
                            opc = 0;
                        }
                        else {
                            rlutil::setColor(rlutil::COLOR::RED);
                            rlutil::locate(39, 25);
                            cout << "* No se pudo eliminar la venta *" << endl;
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
                        cout << "* Se cancelo el borrado de la venta *" << endl;
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
        cout << "* La venta buscada no existe *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }

}

void VentasManager::restaurarVentaBorrada() {
    int cantReg = _archivo.contarVentas();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No existe archivo de Ventas *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    else {
        int id, pos;
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(10, 1);
        cout << "* Modulo de VENTAS *" << endl << endl;
        cout << "Restauracion de venta eliminada" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::showcursor();

        id = validarInt("Ingrese el ID de la Venta a restaurar: ");
        rlutil::hidecursor();
        cout << endl;
        
        pos = buscarVenta(id);

        if (pos >= 0) {
            Venta reg;
            reg = _archivo.leerVenta(pos);
            if (reg.getEliminado() == true) {
                system("cls");
                rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
                cout << endl << "Venta a Restaurar: " << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                mostrarVenta(reg);
                cout << endl;

                int opc = 1, y = 0;

                do {
                    rlutil::hidecursor();
                    rlutil::setColor(rlutil::COLOR::WHITE);
                    rlutil::locate(35, 18);
                    cout << "* ¿Confirma que desea restaurar esta Venta? *" << endl;
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
                            bool restaurar = _archivo.sobreescribirVenta(reg, pos);
                            if (restaurar == true) {
                                rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
                                rlutil::locate(39, 25);
                                cout << "* Venta restaurada con Exito *" << endl << endl;
                                rlutil::setColor(rlutil::COLOR::WHITE);
                                opc = 0;
                            }
                            else {
                                rlutil::setColor(rlutil::COLOR::RED);
                                rlutil::locate(39, 25);
                                cout << "* No se pudo restaurar la venta *" << endl;
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
                            cout << "* Se cancelo la restauracion de la venta *" << endl;
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
                cout << endl << "* La venta a restaurar no se encuentra eliminada *" << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                system("pause");
            }
        }
        else {
            if (pos == -1) {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << endl << "* El ID de Venta buscado no existe *" << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }
            if (pos == -2) {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << endl << "* No se pudo abrir el archivo de Ventas *" << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }
            system("pause");
            
        }
    }
    cout << endl;
}


void VentasManager::realizarBackup() 
{
    string origen = "Ventas.dat";
    string copia = "Ventas.bkp";

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

void VentasManager::restaurarBackup()
{
    string origen = "Ventas.bkp";
    string copia = "Ventas.dat";

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


//func Clientes

int VentasManager::validarCliente(long long dni)
{
    ClienteManager cm; 
    int resultado = cm.buscarCliente(dni);
    if (resultado >= 0) {
        return resultado;
    }
    else {
        return -1;
    }
}

void VentasManager::crearNuevoClienteConDNI(long long dni)
{
    ClienteManager cm;
    ClienteArchivo ca;
    
    ca.guardarCliente(cm.crearCliente(dni));

    
}

Cliente VentasManager::crearNuevoCliente() 
{
    Cliente c;
    ClienteManager cm;
    ClienteArchivo ca;

    c = cm.crearCliente();
    ca.guardarCliente(c);

    return c;
}

void VentasManager::mostrarClienteAsociado(int pos)
{
    ClienteManager cm;
    ClienteArchivo ca; 
    Cliente aux;

    aux = ca.leerCliente(pos); 
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "Cliente que realiza la compra: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    cm.mostrarCliente(aux);
    cout << endl;

}

std::string VentasManager::mostrarNombreCliente(long long dni)
{
    ClienteManager cm;
    ClienteArchivo ca;
    

    int pos = cm.buscarCliente(dni);

    Cliente aux = ca.leerCliente(pos);
    
    return aux.getApellidoNombre();


}

//func Sucursales

int VentasManager::validarSucursal(int id)
{
    SucursalArchivo sa;
    int resultado = sa.buscarPosicion(id);
    if (resultado >= 0) {
        Sucursal reg;
        reg = sa.leerRegistro(resultado);
        if (reg.getEstado() == true) {
            return -2;//sucursal eliminada
        }
        else {
            return resultado;
        }
    }
    else {
        return -1; //sucursal no existe
    }
}

void VentasManager::mostrarSucursalAsociada(int pos)
{
    SucursalArchivo sa;
    Sucursal aux;

    aux = sa.leerRegistro(pos); 
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "Sucursal asignada: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "Id Sucursal: #" << aux.getIdSucursal() << endl;
    cout << "Nombre: " << aux.getNombre() << endl;
    cout << "Dirección: " << aux.getDireccion().toString();
    cout << endl;
    cout << "Telefono: " << aux.getTelefono() << endl << endl;
}

std::string VentasManager::mostrarNombreSucursal(int id)
{
    SucursalManager sm;
    SucursalArchivo sa; 
    

    int pos = sa.buscarPosicion(id);

    Sucursal aux = sa.leerRegistro(pos); 

    string valor = to_string(aux.getIdSucursal()) + " - " + aux.getNombre();
    
    return valor;
}

//func Vendedores

int VentasManager::validarVendedor(int nroLegajo)
{
    VendedorArchivo va;

    int resultado = va.BuscarId(nroLegajo);
    if (resultado >= 0) {
        Vendedor reg; 
        reg = va.leerRegistro(resultado); 
        if (reg.getEliminado() == true) {
            return -2;//vendedor eliminado
        }
        else {
            return resultado;
        }
    }
    else {
        return -1; //vendedor no existe
    }
}

void VentasManager::mostrarVendedorAsociado(int pos)
{
    VendedorManager vm; 
    VendedorArchivo va; 
    Vendedor aux; 

    aux = va.leerRegistro(pos);
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "Vendedor asignado: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    aux.MostrarPersona();
    cout << endl;
    cout << "NRO LEGAJO: " << aux.getNroLegajo() << endl;
    cout << "FECHA DE INGRESO: " << aux.getFechaIngreso().toString() << endl;
    cout << "ANTIGUEDAD: " << aux.getAntiguedad();
    cout << endl;
}

std::string VentasManager::mostrarNombreVendedor(int nrolegajo)
{
    VendedorArchivo va;
    int pos = va.BuscarId(nrolegajo);

    Vendedor aux = va.leerRegistro(pos);

    string valor = aux.getApellido() + ", " + aux.getNombre();

    return valor;
}

//func Vehiculos

bool VentasManager::validarVehiculo(int& id)
{
    VehiculosArchivo va;
    bool resultado = false;

    int pos = va.buscarRegistro(id);
    
    if (pos >= 0) {
        Vehiculo aux = va.leerRegistro(pos);
        if (aux.getStock() > 0) {
            aux.setStock(aux.getStock() - 1);
            va.modificarRegistro(aux, pos);
            return true;

        }
        else {
            do {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << "* El vehiculo no tiene stock y no puede ser vendido. *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                id = validarInt("* Ingrese un nuevo id de vehiculo: ");
                resultado = validarVehiculo(id);

            } while (resultado == false);
            system("cls");
        }
        

    }
    else {
        do {
                rlutil::setColor(rlutil::COLOR::RED);
            cout << "* El vehiculo ingresado no existe *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            id = validarInt("* Ingrese un nuevo id de vehiculo: ");
            resultado = validarVehiculo(id);
        } while (resultado == false);
        
    }
    
}

void VentasManager::mostrarVehiculoAsociado(int id)
{
    VehiculosManager vm;
    VehiculosArchivo va;
    Vehiculo aux;
    int pos = va.buscarRegistro(id);

    aux = va.leerRegistro(pos); 
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "Vehiculo vendido: " << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "ID Vehiculo: " << aux.getIdVehiculo() << endl;
    cout << "Marca y Modelo: " << aux.getMarca() << " " << aux.getModelo() << endl;
    cout << "Version: " << aux.getVersion() << endl;
    cout << "Color: " << aux.getColor() << endl;
    cout << "Año de fabricación: " << aux.getAnioFabricacion() << endl;
    cout << "Precio unidad: $" << formatearNumero(aux.getPrecioUnidad());
    cout << endl;
}

std::string VentasManager::mostrarNombreVehiculo(int id)
{
    VehiculosArchivo va;
    VehiculosManager vm;

    int pos = va.buscarRegistro(id);

    Vehiculo aux = va.leerRegistro(pos);

    string valor = to_string(id)+ " - " + aux.getMarca() + " " + aux.getModelo();

    return valor;
}

float VentasManager::obtenerPrecioVehiculo(int id)
{
    VehiculosArchivo va;
    Vehiculo aux;
    int pos = va.buscarRegistro(id);
    aux = va.leerRegistro(pos); 

    return aux.getPrecioUnidad();
}

//calc auxiliares

float VentasManager::calcularPrecioTotal(float gastos, float precio)
{
    return gastos + precio;
}

std::string VentasManager::formatearNumero(double numero)
{
    ostringstream oss{};
    oss << fixed << setprecision(2) << numero;
    string numeroStr = oss.str();
    size_t punto = numeroStr.find('.');
    string parteEntera = numeroStr.substr(0, punto);
    string parteDecimal = numeroStr.substr(punto);
    string parteEnteraFormateada;
    int longitud = parteEntera.length();
    for (int i = 0; i < longitud; ++i) {
        parteEnteraFormateada += parteEntera[i];
        if ((longitud - i - 1) % 3 == 0 && (i != longitud - 1)) {
            parteEnteraFormateada += ',';
        }
    }
    return parteEnteraFormateada + parteDecimal;
}

