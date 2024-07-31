#pragma once
#include "VendedorArchivo.h"

class VendedorManager {
private:
    VendedorArchivo _archivo;
public:
    VendedorManager();

    void PlanillaVendedor();

    void AgregarVendedor();
    Vendedor CrearVendedor();
    void mostrarVendedor(Vendedor reg);
    void mostrarVendedorEnLinea(Vendedor vendedor);
    void BuscarVendedor();
    void EditarVendedor();
    void editarFechaIngreso(Vendedor reg, int pos);
    void borrarVendedor();
    void realizarBackup();
    void restaurarBackup();

    void Menu();
    void menuListado();
    bool LegajoRepetido(int idLegajo);
    bool DniRepetido(long long idPersona);

    void OrdenarPorAntiguedad(Vendedor* obj, int cantidad, bool criterio(int, int));
    void ListarAntiguedad();
    void OrdenarPorApellido(Vendedor* obj, int cantidad, bool criterio(std::string, std::string));
    void ListarApellido();
    void MostrarPantalla();
}; 
