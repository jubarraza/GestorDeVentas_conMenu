#include <limits>
#include <iomanip>
#include <iostream>
#include "FuncionesGenerales.h"
#include <string> 
#include <sstream>
#include "rlutil.h"
using namespace std;   

#undef max 

int validarInt(const std::string& mensaje) {
    string ingreso;
    int num;
    while (true) {
        bool esValido = true;
        cout << mensaje; //mensaje que pide el ingreso
        getline(cin, ingreso);
        for (int i = 0; i < ingreso.size(); i++) {//Recorre cada Caracter del Ingreso
            if (!isdigit(ingreso[i])) {//Si encuentra un caracter que no es un digito
                esValido = false;//Bandera en False
                break;//Sale del Bucle
            }
        }
        if (!esValido) {//Vuelve a pedir el Ingreso
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* Ingreso No Valido, Solo se Admiten Numeros Positivos *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            cout << endl;
        }
        else {//Si es Valido
            num = stoi(ingreso);//Convierte el ingreso en tipo String a un a un Int y lo guarda en Num
            break;//Sale del Bucle
        }
    }
    cin.ignore(numeric_limits<size_t>::max(), '\n'); 
    return num;///Si el bucle completa la iteracion sin encontrar caracteres no Numericos, la funcion devuelve Num.
}

long long validarLong(const std::string& mensaje) {
    string ingreso;
    long long num;
    while (true) {
        bool esValido = true;
        cout << mensaje; //mensaje que pide el ingreso
        getline(cin, ingreso);
        for (int i = 0; i < ingreso.size(); i++) {//Recorre cada Caracter del Ingreso
            if (!isdigit(ingreso[i])) {//Si encuentra un caracter que no es un digito
                esValido = false;//Bandera en False
                break;//Sale del Bucle
            }
        }
        if (!esValido) {//Vuelve a pedir el Ingreso
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* Ingreso No Valido, Solo se Admiten Numeros Positivos *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
        else {//Si es Valido
            num = stoll(ingreso);//Convierte el ingreso en tipo String a un a un Int y lo guarda en Num
            break;//Sale del Bucle
        }
    }
    cin.ignore(numeric_limits<size_t>::max(), '\n');
    return num;///Si el bucle completa la iteracion sin encontrar caracteres no Numericos, la funcion devuelve Num.
}

// la funcion de stof no me devuelve la parte de los decimales por lo que no la estoy usando en el codigo. La dejo por si podemos revisarla.
float validarFloat(const std::string& mensaje) 
{
    string ingreso; 
    float num;
    bool puntoEncontrado = false;
    while (true) {
        bool esValido = true;
        cout << mensaje; //mensaje que pide el ingreso
        getline(cin, ingreso);
        for (int i = 0; i < ingreso.size(); i++) {//Recorre cada Caracter del Ingreso
            if (!isdigit(ingreso[i])) { //Si encuentra un caracter que no es un digito
                if (ingreso[i] == '.' && puntoEncontrado == false) {
                    puntoEncontrado = true;
                }
                else {
                    esValido = false;//Bandera en False
                    break;//Sale del Bucle

                }
            }
        }
        if (!esValido) {//Vuelve a pedir el Ingreso
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* Ingreso No Valido, Solo se Admiten Numeros Positivos (acepta decimales) *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');///Lipia el Buffer de Entrada por completo
        }
        else {//Si es Valido
            num = stof(ingreso);//Convierte el String a un a un float y lo guarda en Num
            break;//Sale del Bucle
        }
    }
    
    return num;///Si el bucle completa la iteracion sin encontrar caracteres no Numericos, la funcion devuelve Num.
}

float pedirNumeroFloat(const string& mensaje) { 
    float valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) { //pregunta si hay error en el cin y si es negativo
            cin.clear(); // Limpia el estado de error
            cin.ignore(100000000, '\n'); //ignora la entrada invalida limpiando el buffer para que podamos hacer un nuevo ingreso
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "Ingreso invalido. Por favor, ingrese un numero valido." << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
        else {
            cin.ignore(numeric_limits<size_t>::max(), '\n');
            return valor;
        }
    }
}

string validarStringNumerico(const std::string& mensaje) {
    string ingreso;
    
    while (true) {
        bool esValido = true;
        cout << mensaje; //mensaje que pide el ingreso
        getline(cin, ingreso);
        for (int i = 0; i < ingreso.size(); i++) {//Recorre cada Caracter del Ingreso
            if (!isdigit(ingreso[i])) {//Si encuentra un caracter que no es un digito
                esValido = false;//Bandera en False
                break;//Sale del Bucle
            }
        }
        if (!esValido) {//Vuelve a pedir el Ingreso
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* Ingreso No Valido, Solo se Admiten Numeros Positivos *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
        else {//Si es Valido
            break;//Sale del Bucle
        }
    }
    cin.ignore(numeric_limits<size_t>::max(), '\n');
    return ingreso;///Si el bucle completa la iteracion sin encontrar caracteres no Numericos, la funcion devuelve ingreso
}

string validarString(const std::string& mensaje) {
    string ingreso;
    
    while (true) {
        bool esValido = true;
        
        cout << mensaje; //mensaje que pide el ingreso
        getline(cin, ingreso);
        
        for (int i = 0; i < ingreso.size(); i++) {//Recorre cada caracter de la cadena desde el indice 0 al final
            if (!isalpha(ingreso[i]) && ingreso[i] != ' ') {//Si se encuentra un caracter no alfabetico
                esValido = false;
                break;//Sale del Bucle
            }
        }
        if (!esValido) {
            rlutil::setColor(rlutil::COLOR::RED);
            cout << "* Ingreso No Valido, Solo se Admiten Caracteres *" << endl;
            rlutil::setColor(rlutil::COLOR::WHITE);
        }
        else {
            break;//Sale del Bucle
        }
    }
    cin.ignore(numeric_limits<size_t>::max(), '\n');///Lipia el Buffer de Entrada por completo
    return ingreso;///Si el bucle completa la iteracion sin encontrar caracteres no alfabaticos, la funcion devuelve true.
}



int contarDigitos(int num)
{
    int contador = 0;
    while (num > 0) {
        num /= 10;
        contador++;
    }
    return contador;
}

string formatearNumero(float numero) {
    ostringstream oss{};//ostringstream llamado oss
    oss << fixed << setprecision(2) << numero;
    //fixed asegura de que el numero se formatee en notacion decimal fija. setprecision(2) establece que se usen dos decimales
    string numeroStr = oss.str();//oss.str() convierte el flujo oss a una cadena (string) y se guarda en numeroStr
    size_t punto = numeroStr.find('.');//find('.') encuentra la posicion del punto decimal en numeroStr
    string parteEntera = numeroStr.substr(0, punto);//substr(0, punto) obtiene la parte entera de la cadena(todo antes del punto)
    string parteDecimal = numeroStr.substr(punto);//substr(punto) obtiene la parte decimal de la cadena (incluyendo el punto).
    string parteEnteraFormateada;
    int longitud = parteEntera.length();//longitud guarda la longitud de parteEntera
    for (int i = 0; i < longitud; ++i) {
        parteEnteraFormateada += parteEntera[i];
        if ((longitud - i - 1) % 3 == 0 && (i != longitud - 1)) {
            //(longitud - i - 1) % 3 == 0 verifica si el caracter actual esta en una posicion de mil.
            //(i != longitud - 1) asegura que no se agrega una coma al final de la cadena.
            parteEnteraFormateada += ',';
        }
    }
    return parteEnteraFormateada + parteDecimal;//retorna la parte entera formateada concatenada con la parte decimal.
}

string aMinuscula(string cadena) {
    for (string::size_type i = 0; i < cadena.length(); i++) {
        //size_t, y se usa para asegurar la compatibilidad con el tama¤o de la cadena.
        //cadena.length() asegura que el bucle se ejecute desde el primer caracter(i = 0) hasta el ultimo caracter
        cadena[i] = tolower(cadena[i]);
        //tolower(cadena[i]) convierte el caracter actual a minusculas.
    }
    return cadena;//Devuelve cadena completamente en minuscula
}



bool creciente(int num, int num2) {
    return num < num2;
}

bool decreciente(int num, int num2) {
    return num > num2;
}

bool creciente(std::string  n, std::string m) {
    return n < m;
}

bool decreciente(std::string n, std::string m) {
    return n > m;
}

void showItem(const char* text, int posX, int posY, bool selected)
{
    if (selected) {
        rlutil::setBackgroundColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(posX - 2, posY);
        cout << (char)175 << " " << text << endl;
    }
    else {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::locate(posX - 2, posY);
        cout << "  " << text << endl;
    }

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
}
void showItem2(const char* text, int posX, int posY, bool selected)
{
    if (selected) {
        rlutil::setBackgroundColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(posX - 2, posY);
        cout << (char)175 << " " << text << endl;
    }
    else {
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(posX - 2, posY);
        cout << "  " << text << endl;
    }

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
}