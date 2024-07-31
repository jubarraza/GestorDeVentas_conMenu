#include <iostream>
#include <iomanip>
#include "rlutil.h"
#include "Informes.h"
#include "VentasManager.h"
#include "VehiculosManager.h"
#include "SucursalManager.h"
#include "VendedorManager.h"
#include "FuncionesGenerales.h"
using namespace std;


void Informes::Menu()
{
    int opc = 1;
    int y = 0;
    system("cls");

    do {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(35, 9);
        cout << (char)149 << " Sistema de Gestion de Ventas e Inventario " << (char)149 << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(47, 11);
        cout << "* Informes *" << endl;
        showItem("Informe del Inventario - Estado Actual ", 44, 14, y == 0);
        showItem("Informe de Recaudación - Anual ", 44, 15, y == 1);
        showItem("Informe Ventas por Vendedor - Anual ", 44, 16, y == 2);
        showItem("Informe Ventas de todos los Vendedores - Mensual ", 44, 17, y == 3);
        showItem("Informe Ventas por Sucursal - Anual ", 44, 18, y == 4);
        showItem("Informe Ventas de todas las Sucursales - Mensual/Anual ", 44, 19, y == 5);
        showItem("Ranking Anual de Ventas por Modelo ", 44, 20, y == 6);
        showItem2("Volver al menu principal ", 44, 22, y == 8);


        switch (rlutil::getkey()) {
        case 14: //UP
            rlutil::locate(49, 14 + y);
            cout << " " << endl;
            y--;
            if (y < 0) {
                y = 0;
            }
            if (y == 7) {
                y--;
            }
            break;
        case 15: //DOWN
            rlutil::locate(49, 14 + y);
            cout << " " << endl;
            y++;
            if (y > 8) {
                y = 8;
            }
            if (y == 7) {
                y++;
            }
            break;
        case 1: //ENTER

            switch (y) {
            case 0:
                system("cls");
                Inventario();
                system("pause");
                system("cls");
                break;
            case 1:
                system("cls");
                recaudacionAnual();
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                ventasXVendedorAnual();
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                ventasXVendedoresMensual();
                system("pause");
                system("cls");
                break;
            case 4:
                system("cls");
                ventasXSucursalAnual();
                system("pause");
                system("cls");
                break;
            case 5:
                system("cls");
                submenuVentasXTodasLasSucursales();
                system("cls");
                break;
            case 6:
                system("cls");
                rankingVentasXModelo();
                system("pause");
                system("cls");
                break;
            case 8:
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

//1
void Informes::Inventario()
{
    VehiculosArchivo archiV;
    Vehiculo regVeh;
    int cantReg, contDisp = 0, contAgo = 0;
    cantReg = archiV.contarRegistros();
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << left;
    cout << (char)149 << "   Informe de Inventario   " << (char)149 << endl << endl;
    rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
    cout << "-------- Disponibles --------" << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << setw(9) << "Marca";
    cout << setw(15) << "Modelo";
    cout << setw(6) << "Stock";
    cout << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    for (int i = 0; i < cantReg; i++) {
        regVeh = archiV.leerRegistro(i);
        if (regVeh.getEstado() == true) {
            if (regVeh.getStock() != 0) {
                cout << setw(9) << regVeh.getMarca();
                cout << setw(15) << regVeh.getModelo();
                cout << setw(6) << regVeh.getStock();
                cout << endl;
                contDisp += regVeh.getStock();
            }
        }
    }
    cout << endl;
    rlutil::setColor(rlutil::COLOR::LIGHTRED);
    cout << "--------- Agotados ----------" << endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << setw(9) << "Marca";
    cout << setw(15) << "Modelo";
    cout << setw(6) << "Stock";
    cout << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    for (int j = 0; j < cantReg; j++) {
        regVeh = archiV.leerRegistro(j);
        if (regVeh.getEstado() == true) {
            if (regVeh.getStock() == 0) {
                cout << setw(9) << regVeh.getMarca();
                cout << setw(15) << regVeh.getModelo();
                cout << setw(6) << regVeh.getStock();
                cout << endl;
                contAgo++;
            }
        }
    }
    cout << endl << endl;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "---------- Totales ----------" << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "- Autos Disponibles:    " << contDisp << endl;
    cout << "- Autos Agotados:       " << contAgo << endl;
    cout << endl;

}

//2
void Informes::recaudacionAnual()
{
    VentasManager vm;
    VentasArchivo va;
    Fecha f;
    int i;
    double recaudacion[13] = {0};
    string meses[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

    int anio;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << left;
    cout << (char)149 << "  Informe de Recaudacion  - Anual  " << (char)149 << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    do {
        rlutil::showcursor();
        anio = validarInt("Ingrese año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "Año no valido." << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    } while (anio > f.obtenerAnioActual());

    system("cls");

    int cantidad = va.contarVentas();
    if (cantidad >= 0) {
        for (i = 0; i < cantidad; i++) {
            Venta reg = va.leerVenta(i);
            if (reg.getFechaVenta().getAnio() == anio) {
                recaudacion[reg.getFechaVenta().getMes() - 1] += reg.getTotalVenta();
                recaudacion[12] += reg.getTotalVenta();
            }

        }

        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        cout << left;
        cout << (char)149 << "  Informe de Recaudacion  - Anual  " << (char)149 << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        cout << "Año: " << anio << endl << endl;

        cout << left;
        rlutil::setColor(rlutil::COLOR::DARKGREY);
        cout << setw(12) << " MES";
        cout << setw(20) << "RECAUDACION" << endl;
        cout << "------------------------------------------------" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);

        for (i = 0; i < 12; i++) {

            cout << setw(12) << meses[i];
            if (recaudacion[i] == 0) {
                rlutil::setColor(rlutil::COLOR::RED);
            }
            else {
                rlutil::setColor(rlutil::COLOR::GREEN);

            }
            cout << "$ " << setw(20) << vm.formatearNumero(recaudacion[i]);
            rlutil::setColor(rlutil::COLOR::WHITE);
            cout << endl;

        }
        cout << endl << endl;

        cout << "  Total Anual : ";
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        cout << "$ " << vm.formatearNumero(recaudacion[12]) << endl << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::hidecursor();

    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se encontro el archivo de Ventas *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        
    }

    
}

//3
void Informes::ventasXVendedorAnual()
{
     int numLegajo, anio, id = 0;
    Vendedor vendedor;
    Venta venta;
    VendedorArchivo va;
    VentasArchivo vs;
    VentasManager vm;
    Fecha f;

    int cantidadVendedor = va.ContarRegistro();
    int cantidadVentas = vs.contarVentas();

    string meses[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };
    double recaudacion[13] = {};

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << left;
    cout << (char)149 << "  Informe de Ventas por Vendedor  - Anual  " << (char)149 << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    numLegajo = validarInt("Ingrese el numero de legajo del vendedor: ");
    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "Año no valido." << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    } while (anio > f.obtenerAnioActual());
    
    system("cls");

    if (cantidadVendedor > 0) {
        for (int i = 0; i < cantidadVendedor; i++)
        {
            vendedor = va.leerRegistro(i);
            id = va.BuscarId(numLegajo);

        }

        if (id > -1)
        {
            if (cantidadVentas >= 0) {
                for (int i = 0; i < cantidadVentas; i++)
                {
                    venta = vs.leerVenta(i);
                    if (venta.getFechaVenta().getAnio() == anio && venta.getNroLegajo() == numLegajo) {

                        recaudacion[venta.getFechaVenta().getMes() - 1] += venta.getTotalVenta();
                        recaudacion[12] += venta.getTotalVenta();

                    }
                }
                rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
                cout << left;
                cout << (char)149 << "  Informe de Ventas por Vendedor  - Anual  " << (char)149 << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                cout << "Vendedor: " << vm.mostrarNombreVendedor(id) << endl;
                cout << "Nro Legajo: " << numLegajo << endl;
                cout << "Año: " << anio << endl << endl;

                cout << left;
                rlutil::setColor(rlutil::COLOR::DARKGREY);
                cout << setw(12) << "MES";
                cout << setw(20) << "RECAUDACION" << endl;
                cout << "------------------------------------------------------------" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);

                for (int i = 0; i < 12; i++) {

                    cout << setw(12) << meses[i];
                    if(recaudacion[i] == 0){
                        rlutil::setColor(rlutil::COLOR::RED);
                    }
                    else {
                        rlutil::setColor(rlutil::COLOR::GREEN);

                    }
                    cout << "$ " << setw(20) << vm.formatearNumero(recaudacion[i]);
                    rlutil::setColor(rlutil::COLOR::WHITE);
                    cout << endl;

                }
                cout << endl << endl;

                rlutil::setColor(rlutil::COLOR::WHITE);
                cout << "  Total Anual : ";
                rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
                cout << "$ " << vm.formatearNumero(recaudacion[12]);
                rlutil::setColor(rlutil::COLOR::WHITE);
                cout << endl << endl;

            }
            else {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << "* No se encontro el archivo de Ventas *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);

            }
           

        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* No se encontro Vendedor con el numero de legajo buscado *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se encontro el archivo de Vendedores *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }


    
}

//4
void Informes::ventasXVendedoresMensual()
{
    int anio, mes, pos = 0;
    int ventaRealizada = 0;
    Vendedor vendedor;
    Venta venta, * vecVenta;
    VendedorArchivo va;
    VentasArchivo vs;
    VentasManager vm;
    Fecha f;

    int cantidadVendedor = va.ContarRegistro();
    int cantidadVentas = vs.contarVentas();

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << left;
    cout << (char)149 << "  Informe de Ventas de todos los Vendedores - Mensual " << (char)149 << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "Año no valido." << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    } while (anio > f.obtenerAnioActual());

    do {
        mes = validarInt("Ingrese el mes a revisar: ");

        if (mes < 1 || mes > 12) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "Mes no valido." << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    } while (mes < 1 || mes > 12);

    system("cls");

    if (cantidadVentas >= 0) {

        if (cantidadVendedor >0)
        {
            for (int i = 0; i < cantidadVentas; i++)
            {
                venta = vs.leerVenta(i);
                if (venta.getFechaVenta().getAnio() == anio && venta.getFechaVenta().getMes() == mes)
                {
                    ventaRealizada++;
                }
            }

            if (ventaRealizada > 0) {
                vecVenta = new Venta[ventaRealizada];
                if (vecVenta == nullptr)
                {
                    return;
                }

                for (int i = 0; i < cantidadVentas; i++)
                {
                    venta = vs.leerVenta(i);
                    if (venta.getFechaVenta().getAnio() == anio && venta.getFechaVenta().getMes() == mes)
                    {
                        vecVenta[pos] = venta;
                        pos++;
                    }
                }

                
				Vendedor* vendedores = new Vendedor[cantidadVendedor];
				if (vendedores == nullptr)
				{
					return;
				}

				int* cantidades = new int[cantidadVendedor];
				if (cantidades == nullptr)
				{
					return;
				}

				double* recaudaciones = new double[cantidadVendedor];
				if (recaudaciones == nullptr)
				{
					return;
				}
				for (int i = 0; i < cantidadVendedor; i++)
				{
					vendedores[i] = va.leerRegistro(i);
					cantidades[i] = 0;
					recaudaciones[i] = 0.0;
				}

				for (int i = 0; i < cantidadVendedor; i++)
				{
					for (int j = 0; j < ventaRealizada; j++)
					{
						if (vecVenta[j].getNroLegajo() == vendedores[i].getNroLegajo())
						{
							recaudaciones[i] += vecVenta[j].getTotalVenta();
							cantidades[i]++;
						}
					}
				}

				for (int i = 0; i < cantidadVendedor - 1; i++)
				{
					for (int j = 0; j < cantidadVendedor - i - 1; j++)
					{
						if (cantidades[j] < cantidades[j + 1])
						{
							// Intercambiar cantidades
							int auxVenta = cantidades[j];
							cantidades[j] = cantidades[j + 1];
							cantidades[j + 1] = auxVenta;

							// Intercambiar recaudaciones
							double auxMonto = recaudaciones[j];
							recaudaciones[j] = recaudaciones[j + 1];
							recaudaciones[j + 1] = auxMonto;

							// Intercambiar vendedores
							Vendedor auxVendedor = vendedores[j];
							vendedores[j] = vendedores[j + 1];
							vendedores[j + 1] = auxVendedor;
						}
					}
				}

				rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
				cout << left;
				cout << (char)149 << "  Informe de Ventas de todos los Vendedores - Mensual " << (char)149 << endl << endl;
				rlutil::setColor(rlutil::COLOR::WHITE);
				cout << "Año: " << anio << endl;
				cout << "Mes: " << mes << endl << endl;

				cout << left;
				rlutil::setColor(rlutil::COLOR::DARKGREY);
				cout << setw(20) << "VENDEDOR";
				cout << setw(14) << "CANTIDAD";
				cout << setw(20) << "RECAUDACION" << endl;
				cout << "------------------------------------------------------------" << endl;
				rlutil::setColor(rlutil::COLOR::WHITE);

				for (int i = 0; i < cantidadVendedor; i++)
				{
					if (cantidades[i] > 0)
					{
						cout << setw(22) << vendedores[i].getApellidoNombre();
						cout << setw(12) << cantidades[i];
						rlutil::setColor(rlutil::COLOR::LIGHTGREEN);
						cout << "$ " << setw(20) << vm.formatearNumero(recaudaciones[i]);
						rlutil::setColor(rlutil::COLOR::WHITE);
						cout << endl;
					}
				}
				cout << endl << endl;

				delete[] vecVenta;
				delete[] vendedores;
				delete[] cantidades;
				delete[] recaudaciones;
                

            }
            else {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << "* No se encontraron ventas en el mes y año ingresado *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }

        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* No se encontro el archivo de Vendedores *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se encontro el archivo de Ventas *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

    
}

//5
void Informes::ventasXSucursalAnual()
{
    VentasManager vm; 
    VentasArchivo va; 
    SucursalArchivo sa;
    SucursalManager sm;
    Sucursal s;
    int i, cant;
    double recaudacion[13] = { 0 };
    string meses[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };
    Fecha f;
    bool existeSucursal = false;

    int anio, id;
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << left;
    cout << (char)149 << "  Informe de Ventas por Sucursal  - Anual  " << (char)149 << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "Año no valido." << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    } while (anio > f.obtenerAnioActual());
    
    id = validarInt("Ingrese Id de Sucursal: ");

    cant = sa.contarRegistro();
    if (cant >= 0) {
        for (i = 0; i < cant; i++) {
            s = sa.leerRegistro(i);
            if (s.getIdSucursal() == id) {
                existeSucursal = true;
            }
        }

        if (existeSucursal == true) {

            int cantidad = va.contarVentas();
            if (cantidad >= 0) {
                for (i = 0; i < cantidad; i++) {
                    Venta reg = va.leerVenta(i);
                    if (reg.getFechaVenta().getAnio() == anio && reg.getIdSucursal() == id) {
                        recaudacion[reg.getFechaVenta().getMes() - 1] += reg.getTotalVenta();
                        recaudacion[12] += reg.getTotalVenta();

                    }

                }

                system("cls");

                rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
                cout << left;
                cout << (char)149 << "  Informe de Ventas por Sucursal  - Anual  " << (char)149 << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                cout << "Año: " << anio << endl;
                cout << "Sucursal: " << vm.mostrarNombreSucursal(id) << endl;
                cout << endl;

                cout << left;
                rlutil::setColor(rlutil::COLOR::DARKGREY);
                cout << setw(12) << "MES";
                cout << setw(20) << "RECAUDACION" << endl;
                cout << "------------------------------------------------------------" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);

                for (i = 0; i < 12; i++) {

                    cout << setw(12) << meses[i];
                    if (recaudacion[i] == 0) {
                        rlutil::setColor(rlutil::COLOR::RED);
                    }
                    else {
                        rlutil::setColor(rlutil::COLOR::GREEN);

                    }
                    cout << "$ " << setw(20) << vm.formatearNumero(recaudacion[i]);
                    rlutil::setColor(rlutil::COLOR::WHITE);
                    cout << endl;

                }
                cout << endl << endl;

                cout << " Total Anual : ";
                rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
                cout << "$ " << vm.formatearNumero(recaudacion[12]) << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);

            }
            else {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << "* No se encontro el archivo de Ventas *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }

            

        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* No se encontro una Sucursal con el id buscado *" << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se encontro el archivo de Sucursales *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    

}

//submenu para el reporte 6.1 y 6.2
void Informes::submenuVentasXTodasLasSucursales() 
{
    int opc = 1, y = 0;

    system("cls");

    do {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(35, 9);
        cout << (char)149 << " Sistema de Gestion de Ventas e Inventario " << (char)149 << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(38, 11);
        cout << "* Informe Ventas de todas las Sucursales *" << endl;
        showItem(" Mensual   ", 51, 14, y == 0);
        showItem(" Anual  ", 51, 15, y == 1);
        showItem2(" Volver  ", 51, 17, y == 3);


        switch (rlutil::getkey()) {
        case 14: //UP
            rlutil::locate(49, 14 + y);
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
            rlutil::locate(49, 14 + y);
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
                ventasTodasLasSucursalesMensual();
                system("pause");
                system("cls");
                break;
            case 1:
                system("cls");
                ventasTodasLasSucursalesAnual();
                system("pause");
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
    } while (opc != 0);

}

//6.1
void Informes::ventasTodasLasSucursalesMensual()
{
    int anio, mes, contVentas;
    double acuMes;
    Fecha f;

    Venta regV;
    VentasArchivo va;
    VentasManager vm;
    int cantV = va.contarVentas();

    Sucursal reg;
    SucursalArchivo sa;
    int cont = sa.contarRegistro();

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "* Informe Ventas de todas las Sucursales Mensual *" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) { 
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "Año no valido." << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        } 

    } while (anio > f.obtenerAnioActual()); 

    do {
        mes = validarInt("Ingrese el mes a revisar: ");

        if (mes < 1 || mes > 12) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "Mes no valido." << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    } while (mes < 1 || mes > 12);
    system("cls");

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "* Informe Ventas de todas las Sucursales Mensual *" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "Año: " << anio << endl;
    cout << "Mes: " << mes << endl;

    cout << endl;

    cout << left;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << setw(25) << "SUCURSAL";
    cout << setw(20) << "CANTIDAD DE VENTAS";
    cout << setw(20) << "RECAUDACION" << endl;
    cout << "------------------------------------------------------------" << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    double total = 0;
    int totalCantV = 0;

    if (cont >= 0) { //valido sucursales

        if (cantV >= 0) {
            for (int i = 0; i < cont; i++)
            {
                reg = sa.leerRegistro(i);
                acuMes = 0;
                contVentas = 0;


                for (int j = 0; j < cantV; j++)
                {
                    regV = va.leerVenta(j);
                    if (regV.getFechaVenta().getAnio() == anio && regV.getFechaVenta().getMes() == mes) {
                        if (regV.getIdSucursal() == reg.getIdSucursal()) {
                            acuMes += regV.getTotalVenta();
                            contVentas++;
                        }
                    }
                }
                if (acuMes > 0) {
                    cout << setw(25) << reg.getNombre();
                    cout << setw(20) << contVentas;
                    cout << "$ " << setw(20) << vm.formatearNumero(acuMes);
                    cout << endl;
                }

                total += acuMes;
                totalCantV += contVentas;
            }
            cout << endl;
            cout << "------------------------------------------------------------" << endl;
            cout << setw(25) << "TOTAL : ";
            cout << setw(20) << totalCantV;
            cout << "$ " << setw(20) << vm.formatearNumero(total);
            cout << endl << endl;

        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* No se encontro el archivo de Ventas *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se encontro el archivo de Sucursales *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

//6.2
void Informes::ventasTodasLasSucursalesAnual()
{
    int anio, cantAnual;
    double acuAnio;
    Fecha f;

    Venta regV;
    VentasArchivo va;
    VentasManager vm;
    int cantV = va.contarVentas();

    Sucursal reg;
    SucursalArchivo sa;
    int cont = sa.contarRegistro();

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "* Informe Ventas de todas las Sucursales Anual *" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "Año no valido." << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    } while (anio > f.obtenerAnioActual());
    system("cls");

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "* Informe Ventas de todas las Sucursales Anual *" << endl << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "Año: " << anio << endl;

    cout << endl;

    rlutil::setColor(rlutil::COLOR::DARKGREY);
    cout << left;
    cout << setw(20) << "SUCURSAL";
    cout << setw(27) << "CANTIDAD DE VENTAS";
    cout << setw(20) << "RECAUDACION" << endl;
    cout << "------------------------------------------------------------" << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    double totalAnio = 0;
    int totalAnual = 0;

    if (cont >= 0) {
        
        if (cantV >= 0) {

            for (int i = 0; i < cont; i++)
            {
                reg = sa.leerRegistro(i);
                cantAnual = 0;
                acuAnio = 0;

                for (int j = 0; j < cantV; j++)
                {
                    regV = va.leerVenta(j);
                    if (regV.getFechaVenta().getAnio() == anio) {
                        if (regV.getIdSucursal() == reg.getIdSucursal()) {
                            acuAnio += regV.getTotalVenta();
                            cantAnual++;
                        }
                    }
                }
                if (acuAnio > 0) {
                    cout << setw(25) << reg.getNombre();
                    cout << setw(20) << cantAnual;
                    cout << "$ " << setw(20) << vm.formatearNumero(acuAnio);
                    cout << endl;
                }

                totalAnio += acuAnio;
                totalAnual += cantAnual;

            }
            if (totalAnio > 0) {
                cout << endl;
                cout << "------------------------------------------------------------" << endl;
                cout << setw(25) << "TOTAL : ";
                cout << setw(20) << totalAnual;
                cout << "$ " << setw(20) << vm.formatearNumero(totalAnio);
                cout << endl << endl;
            }
            else {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << "* No se encontraron ventas para el año buscado *" << anio << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }

        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* No se encontro el archivo de Ventas *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se encontro el archivo de Sucursales *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }

}

//7
void Informes::rankingVentasXModelo()
{
    int anio, cantVen, cantVeh;
    bool sinVentas = true;
    Fecha f;

    VentasArchivo archiVen;
    Venta venReg;
    cantVen = archiVen.contarVentas();

    VehiculosArchivo archiVeh;
    Vehiculo vehReg;
    cantVeh = archiVeh.contarRegistros();

    vector<int> ventas(cantVeh, 0);
    vector<string> marca(cantVeh);
    vector<string> modelo(cantVeh);

    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "* Ranking Anual de Ventas por Modelo *" << endl;
    rlutil::setColor(rlutil::COLOR::WHITE);

    do {
        anio = validarInt("Ingrese el año a revisar: ");

        if (anio > f.obtenerAnioActual()) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "Año no valido." << endl << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }

    } while (anio > f.obtenerAnioActual());
    system("cls");

    if (cantVen >= 0) {

        if (cantVeh > 0) {

            for (int i = 0; i < cantVen; i++) {
                venReg = archiVen.leerVenta(i);
                if (venReg.getFechaVenta().getAnio() == anio) {
                    ventas[venReg.getIdVehiculo() - 1] += 1;
                    sinVentas = false;
                    for (int j = 0; j < cantVeh; j++) {
                        vehReg = archiVeh.leerRegistro(j);
                        if (venReg.getIdVehiculo() == vehReg.getIdVehiculo()) {
                            marca[venReg.getIdVehiculo() - 1] = vehReg.getMarca();
                            modelo[venReg.getIdVehiculo() - 1] = vehReg.getModelo();
                        }
                    }
                }
            }
            if (sinVentas) {
                rlutil::setColor(rlutil::COLOR::RED);
                cout << endl << "* No existen Registros de Ventas para ese Año *" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
            }
            else {
                for (int i = 0; i < cantVeh - 1; ++i) {
                    for (int j = 0; j < cantVeh - i - 1; ++j) {
                        if (ventas[j] < ventas[j + 1]) {
                            // Intercambiar ventas
                            int auxVentas = ventas[j];
                            ventas[j] = ventas[j + 1];
                            ventas[j + 1] = auxVentas;
                            // Intercambiar marca
                            string auxMarca = marca[j];
                            marca[j] = marca[j + 1];
                            marca[j + 1] = auxMarca;
                            // Intercambiar modelo
                            string auxModelo = modelo[j];
                            modelo[j] = modelo[j + 1];
                            modelo[j + 1] = auxModelo;
                        }
                    }
                }
                system("cls");

                rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
                cout << "* Ranking Anual de Ventas por Modelo *" << endl << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);
                cout << " Año: " << anio << endl << endl;

                rlutil::setColor(rlutil::COLOR::DARKGREY);
                cout << left;
                cout << setw(12) << "MARCA";
                cout << setw(15) << "MODELO";
                cout << setw(10) << "CANTIDAD";
                cout << endl;
                cout << "---------------------------------------------" << endl;
                rlutil::setColor(rlutil::COLOR::WHITE);

                for (int j = 0; j < cantVeh; j++) {
                    if (ventas[j] > 0) {
                        cout << setw(12) << marca[j];
                        cout << setw(18) << modelo[j];
                        cout << setw(10) << ventas[j];
                        cout << endl;
                    }
                }
            }
            cout << endl;

        }
        else {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* No se encontro el archivo de Vehiculos *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
        


    }
    else {
        rlutil::setColor(rlutil::COLOR::RED);
        cout << "* No se encontro el archivo de Ventas *" << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
    
    
}