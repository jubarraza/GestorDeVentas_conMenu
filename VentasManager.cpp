#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "ClienteManager.h"
#include "FuncionesGenerales.h"
#include "VentasManager.h"
#include "SucursalManager.h"
#include "VendedorManager.h"
#include "VehiculosManager.h"
#include "rlutil.h"
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
                system("pause");
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

    dni = validarLong("* INGRESE DNI DEL CLIENTE: ");
    cout << endl;
    
    //Validacion del cliente
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
    
    idSucursal = validarInt("* Ingrese ID de Sucursal: ");
    cout << endl;
    
    //Validacion Sucursal
    int posSucursal = validarSucursal(idSucursal);
    if (posSucursal >= 0) {
        reg.setIdSucursal(idSucursal);
    }
    else {
        do {
            cout << "* La sucursal no existe. Intente nuevamente *" << endl;
            idSucursal = validarInt("* Ingrese ID de Sucursal: ");
            posSucursal = validarSucursal(idSucursal); 
        } while (posSucursal < 0);
        system("cls");
        reg.setIdSucursal(idSucursal);
        
    }
    mostrarSucursalAsociada(posSucursal);
    cout << endl;

    
    
    nroLegajo = validarInt("* Ingrese Legajo del Vendedor: ");
    cout << endl; 

    //Validacion Vendedor
    int posVendedor = validarVendedor(nroLegajo);
    if (posVendedor >= 0) {
        reg.setNroLegajo(nroLegajo);
    }
    else {
        do {
            cout << "* El vendedor no existe. Intente nuevamente *" << endl;
            nroLegajo = validarInt("* Ingrese Legajo del Vendedor: ");
            posVendedor = validarVendedor(nroLegajo);
        } while (posVendedor < 0);
        system("cls");
        reg.setNroLegajo(nroLegajo); 

    }
    mostrarVendedorAsociado(posVendedor);
    cout << endl;
    
    idVehiculo = validarInt("* Ingrese ID del Vehiculo adquirido: ");
    cout << endl;

    //Validacion Vehiculo
    bool vehiculoDisponible = validarVehiculo(idVehiculo);
    
    if (vehiculoDisponible == true) { 
        reg.setIdVehiculo(idVehiculo);
    }
    mostrarVehiculoAsociado(idVehiculo);
    cout << endl; 
    
    gastos = pedirNumeroFloat("* Ingrese Gastos Administrativos: $");
    reg.setGastosAdm(gastos); 

    total = calcularPrecioTotal(reg.getGastosAdm(), obtenerPrecioVehiculo(idVehiculo));
    reg.setTotalVentas(total);
    cout << endl;
    cout << "* Total Venta: $" << formatearNumero(reg.getTotalVenta()) << endl; 
    cout << endl;
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
    cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
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
    int opc;
    cout << "Como desea ordenar el listado de Ventas?" << endl;
    cout << "1 - por ID" << endl;
    cout << "2 - por Fecha de Venta " << endl << endl;
    cout << "0 - Volver al menu anterior" << endl << endl;
    opc = validarInt("Ingrese opcion: ");
    cout << endl;

    switch (opc)
    {
    case 1:
        listarVentas();
        system("pause");
        break;

    case 2:
        listarVentasXFecha();
        system("pause");
        break;

    case 0:
        break;

    default:
        cout << endl << "* Selecione una Opcion Correcta! *" << endl << endl;
        system("pause");
    }
}

void VentasManager::listarVentas()
{
    int i, cantidad = _archivo.contarVentas();
    Venta reg;

    if (cantidad == -1) {
        cout << "* No hay Ventas para mostrar *" << endl;
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
        cout << "* No hay Ventas para mostrar *" << endl;
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

void VentasManager::editarVenta()
{
    int id, opcion;
    
    id = validarInt("Ingrese ID de Venta a editar: ");
    cout << endl;
    
    int pos = buscarVenta(id);
    
    if (pos >= 0) {
        Venta reg;
        reg = _archivo.leerVenta(pos);

        if (reg.getEliminado() == false) {
            cout << endl << "Venta a Editar: " << endl;
            mostrarVenta(reg);

            cout << endl;
            cout << "¿Que dato desea editar?" << endl;
            cout << "1 - Fecha de Venta" << endl;
            cout << "2 - Gastos Administrativos" << endl << endl;
            cout << "0 - Volver al menu anterior" << endl << endl;
            opcion = validarInt("Opcion: ");
            cout << endl;

            switch (opcion) {
            case 1:
            {
                Fecha f;
                f.Cargar();
                reg.setFechaVenta(f);
                break;
            }
            case 2:
            {
                float gastos;
				gastos = validarFloat("Ingrese nuevo valor de Gastos Administrativos: $");
				reg.setGastosAdm(gastos);
				break;
            
            case 0:
                break;

            default:
                cout << "* Opcion invalida *";
                break;
            }
            }
            cout << endl;
            bool result = _archivo.sobreescribirVenta(reg, pos);

            if (result == true && opcion != 0) {
                cout << "* Se edito correctamente la venta *" << endl;
            }
            else {
                cout << "* No se edito la venta *" << endl;
            }


        }
        else {
            cout << "* La venta buscada se encuentra eliminada *" << endl;
        }
    
    }
    else {
        cout << "* Error al buscar la venta. Codigo: (";
        if (pos == -1) {
            cout << pos << ") La venta no existe *" << endl;
        }
        if (pos == -2) {
            cout << pos << ") No se pudo abrir el archivo *" << endl;

        }
    }
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
        cout << "* Backup realizado con exito *" << endl;
    }
    else {
        cout << "* Hubo un error al copiar el archivo *" << endl;
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
        cout << "* Restauracion de backup realizada con exito *" << endl;
    }
    else {
        cout << "* Hubo un error al copiar el archivo *" << endl;
    }

    rlutil::locate(35, 11);
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    system("pause");

}

void VentasManager::borrarVenta()
{
    int id;
    int opc;

    id = validarInt("Ingrese ID de Venta a borrar: ");
    cout << endl; 

    int pos = buscarVenta(id); 

    if (pos >= 0) {
        Venta reg;
        reg = _archivo.leerVenta(pos);

        cout << endl << "Venta a Borrar: " << endl;
        mostrarVenta(reg);
        cout << endl;

        opc =  validarInt("Confirma que desea borrar esta venta? (1)Si - (2)No");

        if (opc == 1) {
            reg.setEliminado(true);
            bool result = _archivo.sobreescribirVenta(reg, pos);
            if (result) {
                cout << "* La venta se ha borrado correctamente *" << endl;
            }
            else {
                cout << "* No se pudo eliminar la venta *" << endl;
            }
        }
        else {
            cout << endl << "* Se cancelo el borrado de la venta *" << endl;
        }

    }
    else {
        cout << "* La venta buscada no existe *" << endl;
    }

}

void VentasManager::restaurarVentaBorrada() {
    int cantReg = _archivo.contarVentas();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl;
    }
    else {
        int id, pos, opc;
        id = validarInt("Ingrese el ID de la Venta: ");
        system("cls");
        
        pos = buscarVenta(id);
        if (pos == -1) {
            cout << endl << "* No Existe ese ID de Venta *" << endl << endl;
        }
        if (pos >= 0) {
            Venta reg;
            reg = _archivo.leerVenta(pos);
            if (reg.getEliminado() == true) {
                cout << "Desea Restaurar el Registro? (1)Si (2)NO " << endl;
                opc = validarInt("Seleccione una Opcion: ");
                system("cls");

                switch (opc) {
                case 1: {
                    reg.setEliminado(false);
                    cout << endl;
                    mostrarVenta(reg);
                    bool restaurar = _archivo.sobreescribirVenta(reg, pos);
                    if (restaurar == true) {
                        cout << endl << setw(25) << " " << "* Registro Restaurado con Exito *" << endl << endl;
                    }
                    else {
                        cout << endl << "* No se Pudo Restaurar el Registro *" << endl;
                    }
                        system("pause");
                }
                case 2:
                    break;
                default:cout << endl << "* Opcion Incorrecta! *" << endl << endl;
                    return;
                }
            }
            else {
                cout << endl << "* El Registro Se Restauro con Exito *" << endl << endl;
                system("pause");
            }
        }
    }
    cout << endl;
}


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

int VentasManager::validarSucursal(int id)
{
    SucursalArchivo sa;
    int resultado = sa.buscarPosicion(id);
    if (resultado >= 0) {
        return resultado;
    }
    else {
        return -1;
    }
}

void VentasManager::mostrarSucursalAsociada(int pos)
{
    SucursalArchivo sa;
    Sucursal aux;

    aux = sa.leerRegistro(pos); 
    cout << "Sucursal asignada: " << endl;
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

int VentasManager::validarVendedor(int nroLegajo)
{
    VendedorArchivo va;

    int resultado = va.BuscarId(nroLegajo);
    if (resultado >= 0) {
        return resultado;
    }
    else {
        return -1;
    }
}

void VentasManager::mostrarVendedorAsociado(int pos)
{
    VendedorManager vm; 
    VendedorArchivo va; 
    Vendedor aux; 

    aux = va.leerRegistro(pos);
    cout << "Vendedor asignado: " << endl;
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
                cout << "* El vehiculo no tiene stock y no puede ser vendido. *" << endl;
                id = validarInt("* Ingrese un nuevo id de vehiculo: ");
                resultado = validarVehiculo(id);

            } while (resultado == false);
            system("cls");
        }
        

    }
    else {
        do {
            cout << "* El vehiculo ingresado no existe *" << endl;
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
    cout << "Vehiculo vendido: " << endl;
    cout << "ID Vehiculo: " << aux.getIdVehiculo() << endl;
    cout << "Marca y Modelo: " << aux.getMarca() << " " << aux.getModelo() << endl;
    cout << "Version: " << aux.getVersion() << endl;
    cout << "Color: " << aux.getColor() << endl;
    cout << "Año de fabricación: " << aux.getAnioFabricacion() << endl;
    //cout << "Stock actualizado: " << aux.getStock() << endl;
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

void VentasManager::buscadorDeVentas()
{
    int cantReg = _archivo.contarVentas();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl;
    }
    else {
        int opc;
        cout << "- Buscar Venta -" << endl;
        cout << "-------------------" << endl;
        cout << "1) Por ID " << endl;
        cout << "2) Por Fecha de Venta " << endl;
        cout << endl;
        cout << "0) Salir " << endl << endl;
        opc = validarInt("Opcion: ");
        system("cls");
        switch (opc) {
        
        case 1:buscarVentaPorID();
            break;
        case 2:buscarVentaPorFecha();
            break;
        case 0:
            break;

        default:cout << endl << "* Opcion Incorrecta! *" << endl << endl;
            return;
        }
    }
    cout << endl;
}

void VentasManager::buscarVentaPorID()
{
    int id, pos; 
    id = validarInt("Ingrese el ID a buscar: ");
    cout << endl;
    pos = buscarVenta(id);
    if (pos == -1) {
        cout << endl << "* No se Encontraron Registros *" << endl;
    }
    if (pos >= 0) {
        Venta reg;
        reg = _archivo.leerVenta(pos);
        if (reg.getEliminado() == false) {
            mostrarVenta(reg);
            cout << endl;
        }
        else {
            cout << "* El Registro se Encuentra Eliminado *" << endl;
        }
    }
    cout << endl;
}

void VentasManager::buscarVentaPorFecha()
{
    Fecha f;
    Venta reg;
    int cantReg, contador = 0;

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
        cout << "* No hay ventas para la fecha buscada * " << endl;
    }

}

 