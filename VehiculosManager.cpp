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

void VehiculosManager::tituloVehiculo() {
    cout << left;
    cout << setw(26) << " " << "- Datos del Vehiculo -" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << setw(4) << "ID ";
    cout << setw(10) << "Marca ";
    cout << setw(14) << "Modelo ";
    cout << setw(12) << "Version ";
    cout << setw(10) << "Color ";
    cout << setw(8) << "Año ";
    cout << setw(8) << "Stock ";
    cout << setw(20) << "Precio por Unidad ";
    cout << endl;

}

void VehiculosManager::Menu() {
    int opc;
    do {
        system("cls");
        cout << "----- Menu Vehiculos -----" << endl;
        cout << "--------------------------" << endl;
        cout << "1) Cargar " << endl;
        cout << "2) Listar " << endl;
        cout << "3) Buscar " << endl;
        cout << "4) Editar " << endl;
        cout << "5) Eliminar registro" << endl;
        cout << "6) Reestablecer registro " << endl;
        cout << "7) Realizar Backup " << endl;
        cout << "8) Restaurar Backup " << endl;
        cout << "0) Regresar al Menu Principal " << endl;
        cout << "-----------------------------" << endl;
        opc = validarInt("Selecione una Opcion: ");
        system("cls");
        
        switch (opc) {
        case 1: agregarVehiculo();
            break;
        case 2: listarVehiculos();
            break;
        case 3: buscarVehiculo();
            break;
        case 4: editarVehiculo();
            break;
        case 5: eliminarVehiculo();
            break;
        case 6: resturarVehiculo();
            break;
        case 7: realizarBackup();
            break;
        case 8: restaurarBackup();
            break;
        case 0:
            break;
        default:cout << endl << "* Selecione una Opcion Correcta! *" << endl << endl;;
            system("pause");
        }
    } while (opc != 0);
}

void VehiculosManager::agregarVehiculo() {
    if (_vehiculosArchivo.guardarRegistro(cargarVehiculo())) {
        cout << "* Registro Agregado! *" << endl;
    }
    else {
        cout << "* No se Pudo Agregar el Registro *" << endl;
    }
    system("pause");
}

Vehiculo VehiculosManager::cargarVehiculo() {
    string marca, modelo, version, color;
    int id, anio, stock;
    float precio;
    Fecha año;
    VehiculosArchivo archivo;
    int cantReg = archivo.contarRegistros();
    if (cantReg == -1) {
        cantReg = 0;
        cout << "* Archivo Nuevo *" << endl;
    }
    Vehiculo reg;
    id = ++cantReg;
    cout << "- Ingrese Los Datos del Vehiculo -" << endl;
    cout << "- ID: ";
    cout << id << endl;
    reg.setIdVehiculo(id);
    cout << "- Marca: ";
    getline(cin, marca);
    reg.setMarca(marca);
    cout << "- Modelo: ";
    getline(cin, modelo);
    reg.setModelo(modelo);
    cout << "- Version: ";
    getline(cin, version);
    reg.setVersion(version);
    cout << "- Color: ";
    getline(cin, color);
    reg.setColor(color);
    while (true) {
        anio = validarInt("- Ingrese el Año de Fabricacion: ");
        
        if (anio > año.obtenerAnioActual()) {
            cout << "* El Año de Fabricacion No puede ser Mayor al Año Actual *" << endl;
        }
        if (anio < 2000) {
            cout << "* El Año de Fabricacion No puede ser Menor a 2000 *" << endl;
        }
        if (anio <= año.obtenerAnioActual() && anio >= 2000) {
            break;
        }
    }
    reg.setAnioFabricacion(anio);
    stock = validarInt("- Stock: ");
    reg.setStock(stock);
    precio = validarInt("- Precio por Unidad: $ ");
    reg.setPrecioUnidad(precio);
    reg.setEstado(true);
    return reg;
}

void VehiculosManager::mostrarVehiculo(Vehiculo reg) {
    if (reg.getEstado() == true) {
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
    else {
        cout << reg.getIdVehiculo() << "   Este Registro se Encuentra Eliminado! " << endl;
    }
}

void VehiculosManager::listarVehiculos() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    if (cantReg == -1) {
        cout << endl << "* Error de Archivo *" << endl << endl;
        system("pause");
    }
    if (cantReg == 0) {
        cout << endl << "* No Hay Registros para Mostrar *" << endl << endl;
        system("pause");
    }
    if (cantReg > 0) {
        int opc;
        do {
            system("cls");
            cout << "- Como desea Visualizar los Registros? " << endl;
            cout << " 1) por ID " << endl;
            cout << " 2) Por Precio " << endl;
            cout << " 0) Regresar " << endl;
            opc = validarInt("- Seleccione una opcion: ");
            system("cls");
            
            switch (opc) {
            case 1: listarPorId();
                break;
            case 2: listarPorPrecio();
                break;
            case 0:
                break;
            default:cout << endl << "* Opcion Incorrecta! *" << endl << endl;
                break;
            }
        } while (opc != 0);

    }
    cout << endl;
}

void VehiculosManager::listarPorId() {
    int cantReg = _vehiculosArchivo.contarRegistros();
    Vehiculo reg;
    cout << left;
    cout << setw(26) << " " << "- Datos de los Vehiculos -" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << setw(4) << "ID ";
    cout << setw(10) << "Marca ";
    cout << setw(14) << "Modelo ";
    cout << setw(12) << "Version ";
    cout << setw(10) << "Color ";
    cout << setw(8) << "Año ";
    cout << setw(8) << "Stock ";
    cout << setw(20) << "Precio por Unidad ";
    cout << endl;
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
    cout << left;
    cout << setw(26) << " " << "- Datos de los Vehiculos -" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << setw(4) << "ID ";
    cout << setw(10) << "Marca ";
    cout << setw(14) << "Modelo ";
    cout << setw(12) << "Version ";
    cout << setw(10) << "Color ";
    cout << setw(8) << "Año ";
    cout << setw(8) << "Stock ";
    cout << setw(20) << "Precio por Unidad ";
    cout << endl;
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
        cout << endl << "* Error de Archivo *" << endl << endl;
        system("pause");
    }
    if (cantReg == 0) {
        cout << endl << "* No Hay Registros para Buscar *" << endl << endl;
        system("pause");
    }
    if (cantReg > 0) {
        int opc;
        do {
            system("cls");
            cout << "---- Buscar Vehiculo ----" << endl;
            cout << "-------------------------" << endl;
            cout << "1) Por ID " << endl;
            cout << "2) Por Marca " << endl;
            cout << "3) Por Modelo " << endl;
            cout << "4) Por Año de Fabricacion " << endl;
            cout << "5) Por Color " << endl;
            cout << "0) Regresar " << endl;
            cout << "------------------------" << endl;
            opc = validarInt("Ingrese una Opcion: ");
            system("cls");
            
            switch (opc) {
            case 1:buscarPorID();
                break;
            case 2:buscarPorMarca();
                break;
            case 3:buscarPorModelo();
                break;
            case 4:buscarPorAnio();
                break;
            case 5:buscarPorColor();
                break;
            case 0:
                break;
            default:cout << endl << "* Opcion Incorrecta! *" << endl << endl;
                break;
            }
        } while (opc != 0);
    }
    cout << endl;
}

void VehiculosManager::buscarPorID() {
    int id, pos;
    id = validarInt("- Ingrese el ID: ");
    system("cls");
    pos = _vehiculosArchivo.buscarRegistro(id);
    
    if (pos == -1) {
        cout << endl << "* No se Encontraron Registros *" << endl;
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
            cout << endl << "* El Registro se Encuentra Eliminado *" << endl;
        }
    }
    cout << endl;
    system("pause");
}

void VehiculosManager::buscarPorMarca() {
    string marca, cadena1, cadena2;
    int cantReg;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    
    cout << "- Ingrese la Marca: ";
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
        cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
    system("pause");
}

void VehiculosManager::buscarPorModelo() {
    string modelo, cadena1, cadena2;
    int cantReg;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    
    cout << "- Ingrese el Modelo: ";
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
        cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
    system("pause");
}

void VehiculosManager::buscarPorAnio() {
    int anio, cantReg;
    Fecha año;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    
    while (true) {
        anio = validarInt("- Ingrese el Año de Fabricacion: ");
        
        if (anio > año.obtenerAnioActual()) {
            cout << "* El Año de Fabricacion No puede ser Mayor al Año Actual *" << endl;
        }
        if (anio < 2000) {
            cout << "* El Año de Fabricacion No puede ser Menor a 2000 *" << endl;
        }
        if (anio <= año.obtenerAnioActual() && anio >= 2000) {
            break;
        }
    }
    system("cls");
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
        cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
    system("pause");
}

void VehiculosManager::buscarPorColor() {
    int cantReg;
    string color, cadena1, cadena2;
    Vehiculo reg;
    vector<Vehiculo> resultado;
    
    color = validarString("- Ingrese el Color: ");
    system("cls");
    
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
        cout << endl << "* No se encontraron Registros *" << endl;
    }
    else {
        cout << endl;
        tituloVehiculo();
        for (size_t j = 0; j < resultado.size(); j++) {
            mostrarVehiculo(resultado[j]);
        }
    }
    cout << endl;
    system("pause");
}

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

void VehiculosManager::resturarVehiculo() {
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
        cout << "* Backup realizado con exito *" << endl;
    }
    else {
        cout << "* Hubo un error al copiar el archivo *" << endl;
    }

    rlutil::locate(35, 11);
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    rlutil::anykey();
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
        cout << "* Restauracion de backup realizada con exito *" << endl;
    }
    else {
        cout << "* Hubo un error al copiar el archivo *" << endl;
    }

    rlutil::locate(35, 11);
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    system("pause");
}
