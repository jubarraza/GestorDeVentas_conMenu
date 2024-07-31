#pragma once
#include <string>


int validarInt(const std::string& mensaje);
long long validarLong(const std::string& mensaje);
float validarFloat(const std::string& mensaje); //no esta funcionando el stof
float pedirNumeroFloat(const std::string& mensaje); 
std::string validarStringNumerico(const std::string& mensaje);
std::string validarString(const std::string& mensaje);

int contarDigitos(int num);

std::string formatearNumero(float numero);
std::string aMinuscula(std::string cadena);

bool creciente(int num, int num2);
bool decreciente(int num, int num2);
bool creciente(std::string  n, std::string m);
bool decreciente(std::string n, std::string m);

void showItem(const char* text, int posX, int posY, bool selected);
void showItem2(const char* text, int posX, int posY, bool selected);
 