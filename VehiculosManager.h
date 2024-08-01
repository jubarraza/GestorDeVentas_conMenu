#pragma once
#include "VehiculosArchivo.h"

class VehiculosManager {
private:
    VehiculosArchivo _vehiculosArchivo;
public:
    VehiculosManager();
    void Menu();
    void tituloVehiculo();
    Vehiculo cargarVehiculo();
    void agregarVehiculo();
    void mostrarVehiculoEnLinea(Vehiculo reg);
    void mostrarVehiculo(Vehiculo reg);
    void listarVehiculos();
    void listarPorId();
    void listarPorPrecio();
    void buscarVehiculo();
    void buscarPorID();
    void buscarPorMarca();
    void buscarPorModelo();
    void buscarPorAnio();
    void buscarPorColor();
    void editarVehiculo();
    void editarMarca(Vehiculo& reg, int pos);
    void editarModelo(Vehiculo& reg, int pos);
    void editarVersion(Vehiculo& reg, int pos);
    void editarColor(Vehiculo& reg, int pos);
    void editarAnio(Vehiculo& reg, int pos);
    void editarStock(Vehiculo& reg, int pos);
    void editarPrecio(Vehiculo& reg, int pos);
    void editarTodo(Vehiculo& reg, int pos);
    void eliminarVehiculo();
    void restaurarVehiculo();
    void realizarBackup();
    void restaurarBackup();
}; 