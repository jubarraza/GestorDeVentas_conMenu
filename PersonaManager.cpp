#include <iostream>
#include <cstring>
#include <iomanip>
#include "rlutil.h"

#include "PersonaManager.h"
#include "FuncionesGenerales.h"


void PersonaManager::CargarPersona() {
    long long dni;
    std::string nombre, apellido;
    Fecha fechaN;

    dni = validarLong("DNI: ");
    setDni(dni);
    std::cout << "NOMBRE: ";
    std::getline(std::cin, nombre);
    setNombre(nombre);
    std::cout << "APELLIDO: ";
    std::getline(std::cin, apellido);
    setApellido(apellido);
    std::cout << "FECHA NACIMIENTO: " << std::endl;
    fechaN.Cargar();
    setFechaNacimiento(fechaN);
}

void PersonaManager::CargarPersona(long long dni) {
    std::string nombre, apellido;
    Fecha fechaN;

    setDni(dni);
    std::cout << "DNI: " << getDni() << std::endl;
    std::cin.ignore();
    std::cout << "NOMBRE: ";
    std::getline(std::cin, nombre);
    setNombre(nombre);
    std::cout << "APELLIDO: ";
    std::getline(std::cin, apellido);
    setApellido(apellido);
    std::cout << "FECHA NACIMIENTO: " << std::endl;
    fechaN.Cargar();
    setFechaNacimiento(fechaN);
}

void PersonaManager::MostrarPersona() 
{
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "DNI: ";
    rlutil::setColor(rlutil::COLOR::WHITE); 
    std::cout << getDni() << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "NOMBRE: ";
    rlutil::setColor(rlutil::COLOR::WHITE); 
    std::cout << getNombre() << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "APELLIDO: ";
    rlutil::setColor(rlutil::COLOR::WHITE); 
    std::cout << getApellido() << std::endl;
    rlutil::setColor(rlutil::COLOR::DARKGREY);
    std::cout << "FECHA NACIMIENTO: ";
    rlutil::setColor(rlutil::COLOR::WHITE); 
    std::cout << getFechaNacimiento().toString();
}

void PersonaManager::MostrarPersonaEnLinea() {

    std::cout << std::left;
    std::cout << std::setw(14) << getDni();
    std::cout << std::setw(20) << getNombre();
    std::cout << std::setw(20) << getApellido();
    std::cout << std::setw(23) << getFechaNacimiento().toString();

}

