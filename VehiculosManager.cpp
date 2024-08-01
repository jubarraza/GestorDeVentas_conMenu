#include "VehiculosManager.h"
#include "FuncionesGenerales.h"
#include "Fecha.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "rlutil.h"
using namespace std;

VehiculosManager::VehiculosManager() : _vehiculosArchivo("Vehiculos.dat")
{

}

void VehiculosManager::Menu() {

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
        cout << "* Modulo de VEHICULOS *" << endl;
        showItem(" Cargar vehiculo ", 47, 14, y == 0);
        showItem(" Listado de vehiculos ", 47, 15, y == 1);
        showItem(" Buscar vehiculo ", 47, 16, y == 2);
        showItem(" Editar vehiculo ", 47, 17, y == 3);
        showItem(" Eliminar vehiculo ", 47, 18, y == 4);
        showItem(" Recuperar vehiculo eliminado", 47, 19, y == 5);
        showItem(" Backup de archivo de Vehiculos ", 47, 21, y == 7);
        showItem(" Restauracion de backup de Vehiculos ", 47, 22, y == 8);
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
                agregarVehiculo();
                system("pause");
                system("cls");
                break;
            case 1:
                system("cls");
                listarVehiculos();
                system("cls");
                break;
            case 2:
                system("cls");
                buscarVehiculo();
                system("cls");
                break;
            case 3:
                system("cls");
                editarVehiculo();
                system("cls");
                break;
            case 4:
                system("cls");
                eliminarVehiculo();
                system("cls");
                break;
            case 5:
                system("cls");
                restaurarVehiculo();
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

void VehiculosManager::agregarVehiculo() {
    if (_vehiculosArchivo.guardarRegistro(cargarVehiculo())) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        cout << endl << "* El vehiculo se guardó correctamente *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se pudo guardar el vehiculo *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

Vehiculo VehiculosManager::cargarVehiculo() {
    string marca, modelo, version, color;
    int id, anio, stock;
    float precio;
    Fecha año;
    VehiculosArchivo archivo;
    Vehiculo reg;

    int cantReg = archivo.contarRegistros();
    if (cantReg == -1) {
        cantReg = 0;
    }

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VEHICULOS *" << endl << endl;
    cout << "Carga de nuevo vehiculo" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    id = ++cantReg;
    cout << "ID: # " << id << endl << endl;
    reg.setIdVehiculo(id);

    rlutil::showcursor();

    cout << "* MARCA: ";
    getline(cin, marca);
    reg.setMarca(marca);
    cout << endl;

    cout << "* MODELO: ";
    getline(cin, modelo);
    reg.setModelo(modelo);
    cout << endl;

    cout << "* VERSION: ";
    getline(cin, version);
    reg.setVersion(version);
    cout << endl;

    cout << "* COLOR: ";
    getline(cin, color);
    reg.setColor(color);
    cout << endl;

    while (true) {
        anio = validarInt("* INGRESE EL AÑO DE FABRICACION: ");
        
        if (anio > año.obtenerAnioActual()) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* El año de fabricacion no puede ser mayor al año actual *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            cout << endl;
        }
        if (anio < 2000) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* El año de fabricacion no puede ser menor a 2000 *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            cout << endl;
        }
        if (anio <= año.obtenerAnioActual() && anio >= 2000) {
            break;
        }
    }
    reg.setAnioFabricacion(anio);
    cout << endl;

    stock = validarInt("* STOCK: ");
    reg.setStock(stock);
    cout << endl;

    precio = validarInt("* PRECIO POR UNIDAD: $ ");
    reg.setPrecioUnidad(precio);
    cout << endl;

    reg.setEstado(true);

    rlutil::hidecursor();

    return reg;
}

void VehiculosManager::tituloVehiculo() 
{
    cout << left;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << setw(27) << " " << "* Listado de Vehiculos *" << endl << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    
    cout << setw(4) << "ID ";
    cout << setw(10) << "MARCA ";
    cout << setw(14) << "MODELO ";
    cout << setw(12) << "VERSION ";
    cout << setw(10) << "COLOR ";
    cout << setw(8) << "AÑO ";
    cout << setw(8) << "STOCK ";
    cout << setw(20) << "PRECIO POR UNIDAD ";
    cout << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
}

void VehiculosManager::mostrarVehiculo(Vehiculo reg) {
    if (reg.getEstado() == true) {
        rlutil::setColor(rlutil::COLOR::WHITE);
        cout << left;
        cout << setw(4) << reg.getIdVehiculo();
        cout << setw(10) << reg.getMarca();
        cout << setw(14) << reg.getModelo();
        cout << setw(12) << reg.getVersion();
        cout << setw(10) << reg.getColor();
        cout << setw(8) << reg.getAnioFabricacion();
        cout << setw(8) << reg.getStock();
        string numeroFormateado = formatearNumero(reg.getPrecioUnidad());
        cout << setw(2) << "$ " << setw(18) << numeroFormateado;
        cout << endl;
    }
}



void VehiculosManager::listarVehiculos() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* Error de Archivo *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg == 0) {
        rlutil::setColor(rlutil::COLOR::WHITE);
        cout << endl << "* No hay vehiculos en el inventario *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg > 0) {
        int opcion = 1, y = 0;
        do {
            rlutil::locate(39, 9);
            rlutil::setColor(rlutil::COLOR::WHITE);
            cout << "* ¿Como desea ordenar el listado de Vehiculos? *" << endl;
            showItem(" por ID de vehiculo ", 51, 11, y == 0);
            showItem(" por Precio ", 51, 12, y == 1);
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
                    listarPorId();
                    system("pause");
                    system("cls");
                    break;
                case 1:
                    system("cls");
                    listarPorPrecio();
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

void VehiculosManager::listarPorId() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    Vehiculo reg;
    tituloVehiculo();
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            mostrarVehiculo(reg);
        }
    }
    cout << endl;
    system("pause");
} 

void VehiculosManager::listarPorPrecio() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    Vehiculo reg, aux;
    vector<Vehiculo> ordenado;
    tituloVehiculo();
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        ordenado.push_back(reg);
    }
    for (int i = 0; i < cantReg; i++) {
        for (int j = i; j < cantReg; j++) {
            if (ordenado[i].getPrecioUnidad() > ordenado[j].getPrecioUnidad()) {
                aux = ordenado[i];
                ordenado[i] = ordenado[j];
                ordenado[j] = aux;
            }
        }
    }
    for (int i = 0; i < cantReg; i++) {
        if (ordenado[i].getEstado() == true) {
            mostrarVehiculo(ordenado[i]);
        }
    }
    cout << endl;
    system("pause");
} 



void VehiculosManager::buscarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* Error de Archivo *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg == 0) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* El archivo de vehiculos esta vacío *" << endl << endl;
        rlutil::setColor(rlutil::COLOR::RED);
        system("pause");
    }
    if (cantReg > 0) {

		int opcion = 1, y = 0;
		do {
			rlutil::locate(44, 9);
			rlutil::setColor(rlutil::COLOR::WHITE);
			cout << "* Buscador de Vehiculos *" << endl;
			showItem(" Buscar por ID ", 45, 11, y == 0);
			showItem(" Buscar por Marca ", 45, 12, y == 1);
			showItem(" Buscar por Modelo ", 45, 13, y == 2);
			showItem(" Buscar por Año de fabricacion ", 45, 14, y == 3);
			showItem(" Buscar por Color ", 45, 15, y == 4);
			showItem2(" Volver ", 51, 17, y == 6);


			switch (rlutil::getkey()) {
			case 14: //UP
				rlutil::locate(43, 11 + y);
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
				rlutil::locate(43, 11 + y);
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
					system("cls");
					buscarPorID();
					system("pause");
					system("cls");
					break;
				case 1:
					system("cls");
					buscarPorMarca();
					system("pause");
					system("cls");
					break;
				case 2:
					system("cls");
					buscarPorModelo();
					system("pause");
					system("cls");
					break;
				case 3:
					system("cls");
					buscarPorAnio();
					system("pause");
					system("cls");
					break;
				case 4:
					system("cls");
					buscarPorColor();
					system("pause");
					system("cls");
					break;
				case 6:
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

void VehiculosManager::buscarPorID() {
    int id, pos;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENTAS *" << endl << endl;
    cout << "Buscador de ventas" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();

    id = validarInt("Ingrese el ID a buscar: ");
    cout << endl;

    pos = _vehiculosArchivo.buscarRegistro(id);
    
    if (pos == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se encontraron vehiculos con el ID buscado *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    if (pos >= 0) {
        Vehiculo reg;
        reg = _vehiculosArchivo.leerRegistro(pos);
        if (reg.getEstado() == true) {
            cout << endl;
            tituloVehiculo();
            mostrarVehiculo(reg);
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

void VehiculosManager::buscarPorMarca() {
    string marca, cadena1, cadena2;
    int cantReg;
    Vehiculo reg;
    vector<Vehiculo> resultado;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENTAS *" << endl << endl;
    cout << "Buscador de ventas" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();
    
    cout << "Ingrese la Marca a buscar: ";
    getline(cin, marca);
    
    cadena1 = aMinuscula(marca);
    cantReg = _vehiculosArchivo.contarRegistros();
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            cadena2 = aMinuscula(reg.getMarca());
            if (cadena2 == cadena1) {
                resultado.push_back(reg);
            }
        }
    }
    if (resultado.empty() == true) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se encontraron vehiculos de la marca buscada *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
    rlutil::hidecursor();
}

void VehiculosManager::buscarPorModelo() {
    string modelo, cadena1, cadena2;
    int cantReg;
    Vehiculo reg;
    vector<Vehiculo> resultado;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENTAS *" << endl << endl;
    cout << "Buscador de ventas" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();
    
    cout << "Ingrese el Modelo a buscar: ";
    getline(cin, modelo);

    cadena1 = aMinuscula(modelo);
    cantReg = _vehiculosArchivo.contarRegistros();
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            cadena2 = aMinuscula(reg.getModelo());
            if (cadena2 == cadena1) {
                resultado.push_back(reg);
            }
        }
    }

    if (resultado.empty() == true) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se encontraron vehiculos del modelo buscado *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
    rlutil::hidecursor();
}

void VehiculosManager::buscarPorAnio() {
    int anio, cantReg;
    Fecha año;
    Vehiculo reg;
    vector<Vehiculo> resultado;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENTAS *" << endl << endl;
    cout << "Buscador de ventas" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();
    
    while (true) {
        anio = validarInt("Ingrese el Año de Fabricacion a buscar: ");
        
        if (anio > año.obtenerAnioActual()) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* El año de fabricacion no puede ser mayor al año actual *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
        if (anio < 2000) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* El año de fabricacion no puede ser menor a 2000 *" << endl;
            rlutil::setColor(rlutil::COLOR::RED);
        }
        if (anio <= año.obtenerAnioActual() && anio >= 2000) {
            break;
        }
    }

    cantReg = _vehiculosArchivo.contarRegistros();

    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            if (reg.getAnioFabricacion() == anio) {
                resultado.push_back(reg);
            }
        }
    }
    if (resultado.empty() == true) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se encontraron vehiculos del Año buscado *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
    rlutil::hidecursor();
}

void VehiculosManager::buscarPorColor() {
    int cantReg;
    string color, cadena1, cadena2;
    Vehiculo reg;
    vector<Vehiculo> resultado;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    cout << "* Modulo de VENTAS *" << endl << endl;
    cout << "Buscador de ventas" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();
    
    color = validarString("Ingrese el Color a buscar: ");
    
    cadena1 = aMinuscula(color);
    cantReg = _vehiculosArchivo.contarRegistros();
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            cadena2 = aMinuscula(reg.getColor());
            if (cadena2 == cadena1) {
                resultado.push_back(reg);
            }
        }
    }

    if (resultado.empty() == true) {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << endl << "* No se encontraron ventas con el Color buscado *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
    rlutil::hidecursor();
}


//TODO: me quede aca 1/8
void VehiculosManager::editarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl << endl;
    }
    if (cantReg == 0) {
        cout << endl << "* No Hay Registros para Editar *" << endl << endl;
    }
    if (cantReg > 0) {
        int id, opc, pos;
        Vehiculo reg;
        
        id = validarInt("- Ingrese el ID del Vehiculo que desea Editar: ");
        cout << endl;
        pos = _vehiculosArchivo.buscarRegistro(id);
        
        if (pos == -1) {
            cout << "* No Existe ese ID de Vehiculo *" << endl;
        }
        if (pos >= 0) {
            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            if (reg.getEstado() == true) {
                tituloVehiculo();
                mostrarVehiculo(reg);
                cout << endl << "- Que desea Editar? -" << endl;
                cout << "1) Marca " << endl;
                cout << "2) Modelo " << endl;
                cout << "3) Version " << endl;
                cout << "4) Color " << endl;
                cout << "5) Anio " << endl;
                cout << "6) Stock " << endl;
                cout << "7) Precio " << endl;
                cout << "8) Todo " << endl;
                cout << "0) Salir " << endl;
                opc = validarInt("Seleccion una Opcion: ");
                
                switch (opc) {
                case 1: {
                    string nuevaMarca;
                    cout << "- Ingrese Nueva Marca: ";
                    getline(cin, nuevaMarca);
                    reg.setMarca(nuevaMarca);
                    break;
                }
                case 2: {
                    string nuevoModelo;
                    cout << "- Ingrese Nuevo Modelo: ";
                    getline(cin, nuevoModelo);
                    reg.setModelo(nuevoModelo);
                    break;
                }
                case 3: {
                    string nuevaVersion;
                    cout << "- Ingrese Nueva Version: ";
                    getline(cin, nuevaVersion);
                    reg.setVersion(nuevaVersion);
                    break;
                }
                case 4: {
                    string nuevoColor;
                    nuevoColor = validarString("- Ingrese Nuevo Color: ");
                    reg.setColor(nuevoColor);
                    break;
                }
                case 5: {
                    int nuevoAnio;
                    nuevoAnio = validarInt(" - Ingrese Nuevo Anio : ");
                    reg.setAnioFabricacion(nuevoAnio);
                    break;
                }
                case 6: {
                    int nuevoStock;
                    nuevoStock = validarInt("-Ingrese Nuevo Stock: ");
                    reg.setStock(nuevoStock);
                    break;
                }
                case 7: {
                    float nuevoPrecio;
                    nuevoPrecio = validarInt("-Ingrese Nuevo Precio: ");
                    reg.setPrecioUnidad(nuevoPrecio);
                    break;
                }
                case 8: {
                    string nuevaMarca, nuevoModelo, nuevaVersion, nuevoColor;
                    int nuevoAnio, nuevoStock;
                    float nuevoPrecio;
                    cout << "- Nueva Marca: ";
                    getline(cin, nuevaMarca);
                    cout << "- Nuevo Modelo: ";
                    getline(cin, nuevoModelo);
                    cout << "- Nueva Version: ";
                    getline(cin, nuevaVersion);
                    nuevoColor = validarString("- Nuevo Color: ");
                    nuevoAnio = validarInt("- Nuevo Año: ");
                    nuevoStock = validarInt("- Nuevo Stock: ");
                    nuevoPrecio = validarInt("- Precio: ");
                    reg.setMarca(nuevaMarca);
                    reg.setModelo(nuevoModelo);
                    reg.setVersion(nuevaVersion);
                    reg.setColor(nuevoColor);
                    reg.setAnioFabricacion(nuevoAnio);
                    reg.setStock(nuevoStock);
                    reg.setPrecioUnidad(nuevoPrecio);
                    break;
                }
                case 0:
                    return;
                default:cout << endl << "* Opcion Incorrecta! *" << endl << endl;
                    return;
                }
                bool modifico = _vehiculosArchivo.modificarRegistro(reg, pos);
                if (modifico == true) cout << endl << "* Registro Modificado con Exito *" << endl;
                else cout << endl << "* No se Pudo Modificar el Registro *" << endl;
            }
            else {
                cout << "* El Registro se Encuentra Eliminado *" << endl;
            }
        }
    }
    cout << endl;
    system("pause");
}



void VehiculosManager::eliminarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl << endl;
        system("pause");
    }
    if (cantReg == 0) {
        cout << endl << "* No Hay Registros para Eliminar *" << endl << endl;
        system("pause");
    }
    if (cantReg > 0) {
        int id, pos, opc;
        id = validarInt("- Ingrese el ID del Vehiculo: ");
        system("cls");
        pos = _vehiculosArchivo.buscarRegistro(id);
        
        if (pos == -1) {
            cout << endl << "* No Existe ese ID de Vehiculo *" << endl << endl;
            system("pause");
        }
        if (pos == -2) {
            cout << endl << "* Error de Archivo *" << endl;
        }
        if (pos >= 0) {
            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            if (reg.getEstado() == true) {
                cout << endl;
                tituloVehiculo();
                mostrarVehiculo(reg);
                cout << endl;
                cout << "- Desea Eliminar el Registro? (1)Si (2)NO " << endl;
                opc = validarInt("- Seleccione una Opcion: ");
                
                switch (opc) {
                case 1: {
                    reg.setEstado(false);
                    bool elimino = _vehiculosArchivo.modificarRegistro(reg, pos);
                    if (elimino == true) cout << endl << "* Registro Eliminado con Exito *" << endl << endl;
                    else cout << "* No se Pudo Eliminar el Registro *" << endl;
                    system("pause");
                    break;
                }
                case 2:
                    break;
                default:cout << "* Opcion Incorrecta! *" << endl;
                }
            }
            else {
                cout << endl << "* El Registro ya se Encuentra Eliminado *" << endl << endl;
                system("pause");
            }
        }
    }
    cout << endl;
}

void VehiculosManager::restaurarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl << endl;
        system("pause");
    }
    if (cantReg == 0) {
        cout << endl << "* No Hay Registros para Restaurar *" << endl << endl;
        system("pause");
    }
    if (cantReg > 0) {
        int id, pos, opc;
        id = validarInt("- Ingrese el ID del Vehiculo: ");
        system("cls");
        pos = _vehiculosArchivo.buscarRegistro(id);

        if (pos == -1) {
            cout << endl << "* No Existe ese ID de Vehiculo *" << endl << endl;
        }
        if (pos >= 0) {
            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            if (reg.getEstado() == false) {
                cout << "- Desea Restaurar el Registro? (1)Si (2)NO " << endl;
                opc = validarInt("- Seleccione una Opcion: ");
                system("cls");
                
                switch (opc) {
                case 1: {
                    reg.setEstado(true);
                    cout << endl;
                    tituloVehiculo();
                    mostrarVehiculo(reg);
                    bool restaurar = _vehiculosArchivo.modificarRegistro(reg, pos);
                    if (restaurar == true) cout << endl << setw(25) << " " << "* Registro Restaurado con Exito *" << endl << endl;
                    else cout << endl << "* No se Pudo Restaurar el Registro *" << endl;
                    system("pause");
                }
                case 2:
                    break;
                default:cout << endl << "* Opcion Incorrecta! *" << endl << endl;
                    return;
                }
            }
            else {
                cout << endl << "* El Registro ya Se Encuentra Disponible *" << endl << endl;
                system("pause");
            }
        }
    }
    cout << endl;
}



void VehiculosManager::realizarBackup() {
    string origen = "Vehiculos.dat";
    string copia = "Vehiculos.bkp";

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

void VehiculosManager::restaurarBackup() {
    string origen = "Vehiculos.bkp";
    string copia = "Vehiculos.dat";

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
