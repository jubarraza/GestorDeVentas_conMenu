#pragma once
#include "ClienteArchivo.h"

class ClienteManager
{
private:
	ClienteArchivo _archivo;
public:
	ClienteManager();
	void Menu();
	Cliente crearCliente();
	Cliente crearCliente(long long dni);
	void mostrarCliente(Cliente reg);
	void mostrarClienteEnLinea(Cliente reg);
	void agregarCliente();
	void encabezadoClientes();
	void menuListado();
	void listarClientes();
	void listarClientesXApellido();
	void ordenar(std::vector <Cliente>& vec, int cant);
	int buscarCliente(long long dni);
	void editarCliente();
	void editarEmail(Cliente &reg, int pos);
	void editarTelefono(Cliente &reg, int pos);
	void editarDireccion(Cliente &reg, int pos);
	void realizarBackup();
	void restaurarBackup();
	void borrarCliente();
	void resturarCliente();
	void resturarCliente(long long dni, int pos);
	void buscadorDeClientes();
	bool DniRepetido(long long idPersona);
};

