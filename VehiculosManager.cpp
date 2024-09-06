#include "VehiculosManager.h"
#include <iostream>
#include "Fecha.h"
#include <iomanip>
#include <string>  
#include <vector>
#include "rlutil.h"
#include "FuncionesGenerales.h"
//using namespace std;

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
        std::cout << (char)254 << " Sistema de Gestion de Ventas e Inventario " << (char)254 << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(45, 11);
        std::cout << "* Modulo de VEHICULOS *" << std::endl;
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
            std::cout << " " << std::endl;
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
            std::cout << " " << std::endl;
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
        std::cout << std::endl << "* El vehiculo se guard¢ correctamente *" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* No se pudo guardar el vehiculo *" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

Vehiculo VehiculosManager::cargarVehiculo() {
    std::string marca, modelo, version, color;
    int id, anio, stock;
    float precio;
    Fecha anioF;
    VehiculosArchivo archivo;
    Vehiculo reg;

    int cantReg = archivo.contarRegistros();
    if (cantReg == -1) {
        cantReg = 0;
    }

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    std::cout << "* Modulo de VEHICULOS *" << std::endl << std::endl;
    std::cout << "Carga de nuevo vehiculo" << std::endl << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    id = ++cantReg;
    std::cout << "ID: # " << id << std::endl << std::endl;
    reg.setIdVehiculo(id);

    rlutil::showcursor();

    std::cout << "* MARCA: ";
    getline(std::cin, marca);
    reg.setMarca(marca);
    std::cout << std::endl;

    std::cout << "* MODELO: ";
    getline(std::cin, modelo);
    reg.setModelo(modelo);
    std::cout << std::endl;

    std::cout << "* VERSION: ";
    getline(std::cin, version);
    reg.setVersion(version);
    std::cout << std::endl;

    std::cout << "* COLOR: ";
    getline(std::cin, color);
    reg.setColor(color);
    std::cout << std::endl;

    while (true) {
        anio = validarInt("* INGRESE EL A¥O DE FABRICACION: ");
        
        if (anio > anioF.obtenerAnioActual()) {
            rlutil::setColor(rlutil::COLOR::RED);
            std::cout << "* El a¤o de fabricacion no puede ser mayor al a¤o actual *" << std::endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            std::cout << std::endl;
        }
        if (anio < 2000) {
            rlutil::setColor(rlutil::COLOR::RED);
            std::cout << "* El a¤o de fabricacion no puede ser menor a 2000 *" << std::endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            std::cout << std::endl;
        }
        if (anio <= anioF.obtenerAnioActual() && anio >= 2000) {
            break;
        }
    }
    reg.setAnioFabricacion(anio);
    std::cout << std::endl;

    stock = validarInt("* STOCK: ");
    reg.setStock(stock);
    std::cout << std::endl;

    precio = validarInt("* PRECIO POR UNIDAD: $ ");
    reg.setPrecioUnidad(precio);
    std::cout << std::endl;

    reg.setEstado(true);

    rlutil::hidecursor();

    return reg;
}

void VehiculosManager::tituloVehiculo() 
{
    std::cout << std::left;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    std::cout << std::setw(27) << " " << "* Listado de Vehiculos *" << std::endl << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    
    std::cout << std::setw(4) << "ID ";
    std::cout << std::setw(10) << "MARCA ";
    std::cout << std::setw(14) << "MODELO ";
    std::cout << std::setw(12) << "VERSION ";
    std::cout << std::setw(10) << "COLOR ";
    std::cout << std::setw(8) << "A¥O ";
    std::cout << std::setw(8) << "STOCK ";
    std::cout << std::setw(20) << "PRECIO POR UNIDAD ";
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------------------" << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
}

void VehiculosManager::mostrarVehiculoEnLinea(Vehiculo reg) {
    if (reg.getEstado() == true) {
        rlutil::setColor(rlutil::COLOR::WHITE);
        std::cout << std::left;
        std::cout << std::setw(4) << reg.getIdVehiculo();
        std::cout << std::setw(10) << reg.getMarca();
        std::cout << std::setw(14) << reg.getModelo();
        std::cout << std::setw(12) << reg.getVersion();
        std::cout << std::setw(10) << reg.getColor();
        std::cout << std::setw(8) << reg.getAnioFabricacion();
        std::cout << std::setw(8) << reg.getStock();
        std::string numeroFormateado = formatearNumero(reg.getPrecioUnidad());
        std::cout << std::setw(2) << "$ " << std::setw(18) << numeroFormateado;
        std::cout << std::endl;
    }
}

void VehiculosManager::mostrarVehiculo(Vehiculo reg)
{
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "ID: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    std::cout << "# " << reg.getIdVehiculo() << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "Marca: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    std::cout << reg.getMarca() << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "Modelo: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    std::cout << reg.getModelo() << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "Version: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    std::cout << reg.getVersion() << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "Color: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    std::cout << reg.getColor() << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "A¤o de fabricaci¢n: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    std::cout << reg.getAnioFabricacion() << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "Stock disponible: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    std::cout << reg.getStock() << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "Precio unidad: ";
    rlutil::setColor(rlutil::COLOR::WHITE);
    std::cout << "$ " << formatearNumero(reg.getPrecioUnidad());
    std::cout << std::endl;
}



void VehiculosManager::listarVehiculos() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* Error de Archivo *" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg == 0) {
        rlutil::setColor(rlutil::COLOR::WHITE);
        std::cout << std::endl << "* No hay vehiculos en el inventario *" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg > 0) {
        int opcion = 1, y = 0;
        do {
            rlutil::locate(39, 9);
            rlutil::setColor(rlutil::COLOR::WHITE);
            std::cout << "* ¨Como desea ordenar el listado de Vehiculos? *" << std::endl;
            showItem(" por ID de vehiculo ", 51, 11, y == 0);
            showItem(" por Precio ", 51, 12, y == 1);
            showItem2(" Volver ", 51, 14, y == 3);


            switch (rlutil::getkey()) {
            case 14: //UP
                rlutil::locate(49, 11 + y);
                std::cout << " " << std::endl;
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
                std::cout << " " << std::endl;
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
    std::cout << std::endl;
}

void VehiculosManager::listarPorId() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    Vehiculo reg;
    tituloVehiculo();
    for (int i = 0; i < cantReg; i++) {
        reg = _vehiculosArchivo.leerRegistro(i);
        if (reg.getEstado() == true) {
            mostrarVehiculoEnLinea(reg);
        }
    }
    std::cout << std::endl;
} 

void VehiculosManager::listarPorPrecio() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    Vehiculo reg, aux;
    std::vector<Vehiculo> ordenado;
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
            mostrarVehiculoEnLinea(ordenado[i]);
        }
    }
    std::cout << std::endl;
} 



void VehiculosManager::buscarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* Error de Archivo *" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg == 0) {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* El archivo de vehiculos esta vac¡o *" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::RED);
        system("pause");
    }
    if (cantReg > 0) {

		int opcion = 1, y = 0;
		do {
			rlutil::locate(44, 9);
			rlutil::setColor(rlutil::COLOR::WHITE);
			std::cout << "* Buscador de Vehiculos *" << std::endl;
			showItem("   Por ID ", 45, 11, y == 0);
			showItem("   Por Marca ", 45, 12, y == 1);
			showItem("   Por Modelo ", 45, 13, y == 2);
			showItem("   Por A¤o de fabricacion ", 45, 14, y == 3);
			showItem("   Por Color ", 45, 15, y == 4);
			showItem2(" Volver ", 51, 17, y == 6);


			switch (rlutil::getkey()) {
			case 14: //UP
				rlutil::locate(43, 11 + y);
				std::cout << " " << std::endl;
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
				std::cout << " " << std::endl;
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
    std::cout << std::endl;
}

void VehiculosManager::buscarPorID() {
    int id, pos;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    std::cout << "* Modulo de VEHICULOS *" << std::endl << std::endl;
    std::cout << "Buscador de vehiculos" << std::endl << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();

    id = validarInt("Ingrese el ID a buscar: ");
    std::cout << std::endl;

    pos = _vehiculosArchivo.buscarRegistro(id);
    
    if (pos == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* No se encontraron vehiculos con el ID buscado *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    if (pos >= 0) {
        Vehiculo reg;
        reg = _vehiculosArchivo.leerRegistro(pos);
        if (reg.getEstado() == true) {
            std::cout << std::endl;
            mostrarVehiculo(reg);
            std::cout << std::endl;
        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            std::cout << "* El vehiculo buscado se encuentra eliminado *" << std::endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
    }
    std::cout << std::endl;
    rlutil::hidecursor();
}

void VehiculosManager::buscarPorMarca() {
    std::string marca, cadena1, cadena2;
    int cantReg;
    Vehiculo reg;
    std::vector<Vehiculo> resultado;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    std::cout << "* Modulo de VEHICULOS *" << std::endl << std::endl;
    std::cout << "Buscador de vehiculos" << std::endl << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();
    
    std::cout << "Ingrese la Marca a buscar: ";
    getline(std::cin, marca);
    
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
        std::cout << std::endl << "* No se encontraron vehiculos de la marca buscada *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        std::cout << std::endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculoEnLinea(resultado[j]);
        }
    }
    std::cout << std::endl;
    rlutil::hidecursor();
}

void VehiculosManager::buscarPorModelo() {
    std::string modelo, cadena1, cadena2;
    int cantReg;
    Vehiculo reg;
    std::vector<Vehiculo> resultado;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    std::cout << "* Modulo de VEHICULOS *" << std::endl << std::endl;
    std::cout << "Buscador de vehiculos" << std::endl << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();
    
    std::cout << "Ingrese el Modelo a buscar: ";
    getline(std::cin, modelo);

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
        std::cout << std::endl << "* No se encontraron vehiculos del modelo buscado *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        std::cout << std::endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculoEnLinea(resultado[j]);
        }
    }
    std::cout << std::endl;
    rlutil::hidecursor();
}

void VehiculosManager::buscarPorAnio() {
    int anio, cantReg;
    Fecha anioF;
    Vehiculo reg;
    std::vector<Vehiculo> resultado;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    std::cout << "* Modulo de VEHICULOS *" << std::endl << std::endl;
    std::cout << "Buscador de vehiculos" << std::endl << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    rlutil::showcursor();
    
    while (true) {
        anio = validarInt("Ingrese el A¤o de Fabricacion a buscar: ");
        
        if (anio > anioF.obtenerAnioActual()) {
            rlutil::setColor(rlutil::COLOR::RED);
            std::cout << "* El a¤o de fabricacion no puede ser mayor al a¤o actual *" << std::endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
        if (anio < 2000) {
            rlutil::setColor(rlutil::COLOR::RED);
            std::cout << "* El a¤o de fabricacion no puede ser menor a 2000 *" << std::endl;
            rlutil::setColor(rlutil::COLOR::RED);
        }
        if (anio <= anioF.obtenerAnioActual() && anio >= 2000) {
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
        std::cout << std::endl << "* No se encontraron vehiculos del A¤o buscado *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        std::cout << std::endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculoEnLinea(resultado[j]);
        }
    }
    std::cout << std::endl;
    rlutil::hidecursor();
}

void VehiculosManager::buscarPorColor() {
    int cantReg;
    std::string color, cadena1, cadena2;
    Vehiculo reg;
    std::vector<Vehiculo> resultado;

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    std::cout << "* Modulo de VEHICULOS *" << std::endl << std::endl;
    std::cout << "Buscador de vehiculos" << std::endl << std::endl;
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
        std::cout << std::endl << "* No se encontraron ventas con el Color buscado *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        std::cout << std::endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculoEnLinea(resultado[j]);
        }
    }
    std::cout << std::endl;
    rlutil::hidecursor();
}



void VehiculosManager::editarVehiculo() 
{
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    std::cout << "* Modulo de VEHICULOS *" << std::endl << std::endl;
    std::cout << "Editar vehiculo" << std::endl << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* Error de Archivo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg == 0) {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* No hay vehiculos en el inventario *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg > 0) {
        int id, pos;
        Vehiculo reg;
        
        id = validarInt("Ingrese el ID del Vehiculo a editar: ");
        std::cout << std::endl;
        pos = _vehiculosArchivo.buscarRegistro(id);
        
		if (pos >= 0) {

			Vehiculo reg;
			reg = _vehiculosArchivo.leerRegistro(pos);

			if (reg.getEstado() == true) {
				rlutil::hidecursor();
				rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
				std::cout << std::endl << "Vehiculo a Editar: " << std::endl;
				rlutil::setColor(rlutil::COLOR::WHITE);
				mostrarVehiculo(reg);

				int opc = 1, y = 0;
				do {
					rlutil::setColor(rlutil::COLOR::WHITE);
					rlutil::locate(43, 17);
					std::cout << "* ¨Que dato desea editar? *" << std::endl;
					showItem(" Marca", 51, 19, y == 0);
					showItem(" Modelo", 51, 20, y == 1);
					showItem(" Version ", 51, 21, y == 2);
					showItem(" Color", 51, 22, y == 3);
					showItem(" A¤o de fabricacion", 51, 23, y == 4);
					showItem(" Stock", 51, 24, y == 5);
					showItem(" Precio", 51, 25, y == 6);
					showItem(" Todos", 51, 26, y == 7);
					showItem2(" Volver  ", 51, 28, y == 9);


					switch (rlutil::getkey()) {
					case 14: //UP
						rlutil::locate(49, 19 + y);
						std::cout << " " << std::endl;
						y--;
						if (y < 0) {
							y = 0;
						}
						if (y == 8) {
							y--;
						}
						break;
					case 15: //DOWN
						rlutil::locate(49, 19 + y);
						std::cout << " " << std::endl;
						y++;
						if (y > 9) {
							y = 9;
						}
						if (y == 8) {
							y++;
						}
						break;
					case 1: //ENTER
						switch (y) {
						case 0:
							system("cls");
							editarMarca(reg, pos);
							system("pause");
							opc = 0;
							system("cls");
							break;
						case 1:
							system("cls");
							editarModelo(reg, pos);
							system("pause");
							opc = 0;
							system("cls");
							break;
						case 2:
							system("cls");
							editarVersion(reg, pos);
							system("pause");
							opc = 0;
							system("cls");
							break;
						case 3:
							system("cls");
							editarColor(reg, pos);
							system("pause");
							opc = 0;
							system("cls");
							break;
						case 4:
							system("cls");
							editarAnio(reg, pos);
							system("pause");
							opc = 0;
							system("cls");
							break;
						case 5:
							system("cls");
							editarStock(reg, pos);
							system("pause");
							opc = 0;
							system("cls");
							break;
						case 6:
							system("cls");
							editarPrecio(reg, pos);
							system("pause");
							opc = 0;
							system("cls");
							break;
						case 7:
                            system("cls");
                            editarTodo(reg, pos);
                            system("pause");
                            opc = 0;
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
					
				}while (opc != 0);



			}
			else {
				rlutil::setColor(rlutil::COLOR::RED);
				std::cout << pos << "* El vehiculo buscado esta eliminado *" << std::endl;
				rlutil::setColor(rlutil::COLOR::WHITE);
			}
		}
		else {
			rlutil::setColor(rlutil::COLOR::RED);
			std::cout << pos << "* El vehiculo buscado no existe *" << std::endl;
			rlutil::setColor(rlutil::COLOR::WHITE);
		}
	}

    std::cout << std::endl;
}

void VehiculosManager::editarMarca(Vehiculo& reg, int pos)
{
    std::string nuevaMarca;
    rlutil::hidecursor();
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    std::cout << std::endl << "Vehiculo a Editar: " << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarVehiculo(reg);
    std::cout << std::endl << std::endl;

    rlutil::showcursor();
    std::cout << "Ingrese nueva Marca: ";
    getline(std::cin, nuevaMarca);
    reg.setMarca(nuevaMarca);
    std::cout << std::endl;

    bool modifico = _vehiculosArchivo.modificarRegistro(reg, pos);
    if (modifico == true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        std::cout << "* Se edito correctamente el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* No se edito el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

}

void VehiculosManager::editarModelo(Vehiculo& reg, int pos)
{
    rlutil::hidecursor();
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    std::cout << std::endl << "Vehiculo a Editar: " << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarVehiculo(reg);
    std::cout << std::endl << std::endl;

    rlutil::showcursor();
    std::string nuevoModelo;
    std::cout << "Ingrese nuevo Modelo: ";
    getline(std::cin, nuevoModelo);
    reg.setModelo(nuevoModelo);
    std::cout << std::endl;

    bool modifico = _vehiculosArchivo.modificarRegistro(reg, pos);
    if (modifico == true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        std::cout << "* Se edito correctamente el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* No se edito el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

void VehiculosManager::editarVersion(Vehiculo& reg, int pos)
{
    rlutil::hidecursor();
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    std::cout << std::endl << "Vehiculo a Editar: " << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarVehiculo(reg);
    std::cout << std::endl << std::endl;

    rlutil::showcursor();
    std::string nuevaVersion;
    std::cout << "Ingrese nueva Version: ";
    getline(std::cin, nuevaVersion);
    reg.setVersion(nuevaVersion);
    std::cout << std::endl;

    bool modifico = _vehiculosArchivo.modificarRegistro(reg, pos);
    if (modifico == true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        std::cout << "* Se edito correctamente el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* No se edito el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

void VehiculosManager::editarColor(Vehiculo& reg, int pos)
{
    rlutil::hidecursor();
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    std::cout << std::endl << "Vehiculo a Editar: " << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarVehiculo(reg);
    std::cout << std::endl << std::endl;

    rlutil::showcursor();
    std::string nuevoColor;
    nuevoColor = validarString("Ingrese nuevo Color: ");
    reg.setColor(nuevoColor);
    std::cout << std::endl;

    bool modifico = _vehiculosArchivo.modificarRegistro(reg, pos);
    if (modifico == true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        std::cout << "* Se edito correctamente el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* No se edito el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

void VehiculosManager::editarAnio(Vehiculo& reg, int pos)
{
    rlutil::hidecursor();
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    std::cout << std::endl << "Vehiculo a Editar: " << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarVehiculo(reg);
    std::cout << std::endl << std::endl;

    rlutil::showcursor();
    int nuevoAnio;
    nuevoAnio = validarInt("Ingrese nuevo A¤o de fabricacion : ");
    reg.setAnioFabricacion(nuevoAnio);
    std::cout << std::endl;

    bool modifico = _vehiculosArchivo.modificarRegistro(reg, pos);
    if (modifico == true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        std::cout << "* Se edito correctamente el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* No se edito el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

void VehiculosManager::editarStock(Vehiculo& reg, int pos)
{
    rlutil::hidecursor();
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    std::cout << std::endl << "Vehiculo a Editar: " << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarVehiculo(reg);
    std::cout << std::endl << std::endl;

    rlutil::showcursor();
    int nuevoStock;
    nuevoStock = validarInt("Ingrese Stock actualizado: ");
    reg.setStock(nuevoStock);
    std::cout << std::endl;

    bool modifico = _vehiculosArchivo.modificarRegistro(reg, pos);
    if (modifico == true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        std::cout << "* Se edito correctamente el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* No se edito el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

void VehiculosManager::editarPrecio(Vehiculo& reg, int pos)
{
    rlutil::hidecursor();
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    std::cout << std::endl << "Vehiculo a Editar: " << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarVehiculo(reg);
    std::cout << std::endl << std::endl;

    rlutil::showcursor();
    float nuevoPrecio;
    nuevoPrecio = validarInt("Ingrese Precio actualizado: ");
    reg.setPrecioUnidad(nuevoPrecio);
    std::cout << std::endl;

    bool modifico = _vehiculosArchivo.modificarRegistro(reg, pos);
    if (modifico == true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        std::cout << "* Se edito correctamente el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* No se edito el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

void VehiculosManager::editarTodo(Vehiculo& reg, int pos)
{
    rlutil::hidecursor();
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    std::cout << std::endl << "Vehiculo a Editar: " << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    mostrarVehiculo(reg);
    std::cout << std::endl << std::endl;

    rlutil::showcursor();

    std::string nuevaMarca, nuevoModelo, nuevaVersion, nuevoColor;
    int nuevoAnio, nuevoStock;
    float nuevoPrecio;

    std::cout << "Ingrese nueva Marca: ";
    getline(std::cin, nuevaMarca);
    std::cout << std::endl;
    std::cout << "Ingrese nuevo Modelo: ";
    getline(std::cin, nuevoModelo);
    std::cout << std::endl;
    std::cout << "Ingrese nueva Version: ";
    getline(std::cin, nuevaVersion);
    std::cout << std::endl;
    nuevoColor = validarString("Ingrese nuevo Color: ");
    std::cout << std::endl;
    nuevoAnio = validarInt("Ingrese nuevo A¤o de fabricacion: ");
    std::cout << std::endl;
    nuevoStock = validarInt("Ingrese Stock actualizado: ");
    std::cout << std::endl;
    nuevoPrecio = validarInt("Ingrese Precio actualizado: ");
    std::cout << std::endl;
    
    reg.setMarca(nuevaMarca);
    reg.setModelo(nuevoModelo);
    reg.setVersion(nuevaVersion);
    reg.setColor(nuevoColor);
    reg.setAnioFabricacion(nuevoAnio);
    reg.setStock(nuevoStock);
    reg.setPrecioUnidad(nuevoPrecio);

    bool modifico = _vehiculosArchivo.modificarRegistro(reg, pos);
    if (modifico == true) {
        rlutil::setColor(rlutil::COLOR::GREEN);
        std::cout << "* Se edito correctamente el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* No se edito el vehiculo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}



void VehiculosManager::eliminarVehiculo() 
{

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::locate(10, 1);
    std::cout << "* Modulo de VENTAS *" << std::endl << std::endl;
    std::cout << "Borrar Venta" << std::endl << std::endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* Error de Archivo *" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg == 0) {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* No hay vehiculos para eliminar *" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg > 0) {
        int id, pos, opc;

        rlutil::showcursor();
        id = validarInt("Ingrese el ID del Vehiculo a borrar: ");
        rlutil::hidecursor();
        std::cout << std::endl;

        pos = _vehiculosArchivo.buscarRegistro(id);
        
        if (pos >= 0) {

            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            
            if (reg.getEstado() == true) {

                rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
                std::cout << std::endl << "Vehiculo a Borrar: " << std::endl << std::endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                mostrarVehiculo(reg);
                std::cout << std::endl;

                int opc = 1, y = 0;

                do {
                    rlutil::hidecursor();
                    rlutil::setColor(rlutil::COLOR::WHITE);
                    rlutil::locate(35, 18);
                    std:: cout << "* ¨Confirma que desea borrar este Vehiculo? *" << std::endl;
                    showItem(" Si   ", 51, 20, y == 0);
                    showItem(" No  ", 51, 21, y == 1);


                    switch (rlutil::getkey()) {
                    case 14: //UP
                        rlutil::locate(49, 20 + y);
                        std::cout << " " << std::endl;
                        y--;
                        if (y < 0) {
                            y = 0;
                        }
                        break;
                    case 15: //DOWN
                        rlutil::locate(49, 20 + y);
                        std::cout << " " << std::endl;
                        y++;
                        if (y > 1) {
                            y = 1;
                        }
                        break;
                    case 1: //ENTER

                        switch (y) {
                        case 0: {
                            reg.setEstado(false);
                            bool result = _vehiculosArchivo.modificarRegistro(reg, pos);
                            if (result = true) {
                                rlutil::setColor(rlutil::COLOR::GREEN);
                                rlutil::locate(39, 25);
                                std::cout << "* El vehiculo se ha borrado correctamente *" << std::endl;
                                rlutil::setColor(rlutil::COLOR::WHITE);
                                opc = 0;
                            }
                            else {
                                rlutil::setColor(rlutil::COLOR::RED);
                                rlutil::locate(39, 25);
                                std::cout << "* No se pudo eliminar el vehiculo *" << std::endl;
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
                            std::cout << "* Se cancelo el borrado del vehiculo *" << std::endl;
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
                std::cout << "* El vehiculo ya se encuentra eliminado *" << std::endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                system("pause");
            }
        }
        else {
            if (pos == -1) {
                rlutil::setColor(rlutil::COLOR::RED);
                std::cout << std::endl << "* No existen vehiculos con el ID ingresado *" << std::endl << std::endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                system("pause");
            }
            if (pos == -2) {

                rlutil::setColor(rlutil::COLOR::RED);
                std::cout << std::endl << "* Error de Archivo *" << std::endl << std::endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                system("pause");
            }
        }
    }
    std::cout << std::endl;
}

void VehiculosManager::restaurarVehiculo() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* Error de Archivo *" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg == 0) {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << std::endl << "* No hay vehiculos en el inventario *" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        system("pause");
    }
    if (cantReg > 0) {

        int id, pos;
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(10, 1);
        std::cout << "* Modulo de VEHICULOS *" << std::endl << std::endl;
        std::cout << "Restauracion de vehiculo eliminado" << std::endl << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::showcursor();

        id = validarInt("Ingrese el ID del vehiculo a restaurar: ");
        rlutil::hidecursor();
        std::cout << std::endl;

        pos = _vehiculosArchivo.buscarRegistro(id);

        if (pos >= 0) {
            
            Vehiculo reg;
            reg = _vehiculosArchivo.leerRegistro(pos);
            
            if (reg.getEstado() == false) {
                system("cls");
                rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
                std::cout << std::endl << "Vehiculo a Restaurar: " << std::endl << std::endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                mostrarVehiculo(reg);
                std::cout << std::endl;

                int opc = 1, y = 0;

                do {
                    rlutil::hidecursor();
                    rlutil::setColor(rlutil::COLOR::WHITE);
                    rlutil::locate(35, 18);
                    std::cout << "* ¨Confirma que desea restaurar este Vehiculo? *" << std::endl;
                    showItem(" Si   ", 51, 20, y == 0);
                    showItem(" No  ", 51, 21, y == 1);


                    switch (rlutil::getkey()) {
                    case 14: //UP
                        rlutil::locate(49, 20 + y);
                        std::cout << " " << std::endl;
                        y--;
                        if (y < 0) {
                            y = 0;
                        }
                        break;
                    case 15: //DOWN
                        rlutil::locate(49, 20 + y);
                        std::cout << " " << std::endl;
                        y++;
                        if (y > 1) {
                            y = 1;
                        }
                        break;

                    case 1: //ENTER

                        switch (y) {
                        case 0: { //SI
                            reg.setEstado(true);
                            std::cout << std::endl;
                            bool restaurar = _vehiculosArchivo.modificarRegistro(reg, pos);
                            
                            if (restaurar == true) {
                                rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
                                rlutil::locate(39, 25);
                                std::cout << "* Vehiculo restaurado con Exito *" << std::endl << std::endl;
                                rlutil::setColor(rlutil::COLOR::WHITE);
                                opc = 0;
                            }
                            else {
                                rlutil::setColor(rlutil::COLOR::RED);
                                rlutil::locate(39, 25);
                                std::cout << "* No se pudo restaurar el vehiculo *" << std::endl;
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
                            std::cout << "* Se cancelo la restauracion del vehiculo *" << std::endl;
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
                std::cout << std::endl << "* El vehiculo a restaurar no se encuentra eliminado *" << std::endl << std::endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                system("pause");
            }
        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            std::cout << std::endl << "* El ID de Vehiculo buscado no existe *" << std::endl << std::endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            system("pause");
        }
    }
    std::cout << std::endl;
}



void VehiculosManager::realizarBackup() {
    std::string origen = "Vehiculos.dat";
    std::string copia = "Vehiculos.bkp";

    std::string comando = "copy " + origen + " " + copia;

    rlutil::setColor(rlutil::COLOR::WHITE);
    rlutil::locate(35, 9);
    int resultado = system(comando.c_str());

    rlutil::locate(35, 10);
    if (resultado == 0) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        std::cout << "* Backup realizado con exito *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        std::cout << "* Hubo un error al copiar el archivo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

    rlutil::locate(35, 11);
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    system("pause");
}

void VehiculosManager::restaurarBackup() {
    std::string origen = "Vehiculos.bkp";
    std::string copia = "Vehiculos.dat";

    std::string comando = "copy " + origen + " " + copia;

    rlutil::setColor(rlutil::COLOR::WHITE);
    rlutil::locate(35, 9);
    int resultado = system(comando.c_str());

    rlutil::locate(35, 10);
    if (resultado == 0) {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        std::cout << "* Restauracion de backup realizada con exito *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    else {
        rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
        std::cout << "* Hubo un error al copiar el archivo *" << std::endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

    rlutil::locate(35, 11);
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    system("pause");
}
