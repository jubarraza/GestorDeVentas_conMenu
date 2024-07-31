#pragma once
#include "VehiculosManager.h"
#include "VentasManager.h"
#include "VentasManager.h"
#include "VendedorManager.h"
#include "SucursalManager.h"
#include "ClienteManager.h"
#include "Informes.h"
#include "Configuracion.h"
class Sistema
{
private: 
	VehiculosManager _vehiculo;
	VentasManager _venta;
	VendedorManager _vendedor;
	SucursalManager _sucursal;
	ClienteManager _cliente;
	Informes _informes;
	Configuracion _configuracion;

public:
	void Menu();
	void Creditos();
};

