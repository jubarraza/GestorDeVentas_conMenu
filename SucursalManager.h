#pragma once
#include "SucursalArchivo.h"

class SucursalManager
{
private:
	SucursalArchivo _archivo;
public:
	SucursalManager();
	
	bool validarIDUnico(int id);
	void agregarRegistro();
	void listarRegistros();
	void listarPorID();
	void listarPorNombre();
	void ordenarNombre(Sucursal obj[], int tam);
	void buscarSucursal();
	void buscarSucursalID();
	void buscarSucursalNombre();
	void Menu();
	void salidaEnPantalla();
	Sucursal crearRegistro();
	void mostrarEnLinea(Sucursal reg);
	void mostrar(Sucursal reg);
	void editarRegistro();
	void editarNombre(Sucursal& reg, int pos);
	void editarDireccion(Sucursal& reg, int pos);
	void editarTelefono(Sucursal& reg, int pos);
	void borrarSucursal();
	void realizarBackup();
	void restaurarBackup();
}; 