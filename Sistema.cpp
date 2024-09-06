#include "Sistema.h"
#include "FuncionesGenerales.h"
#include "rlutil.h"
using namespace std;

void Sistema::Menu()
{
    int opc = 1;
    int y = 0;
    rlutil::hidecursor();

    do {
       
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
        rlutil::locate(35, 9);
        cout << (char)254 << " Sistema de Gestion de Ventas e Inventario " << (char)254 << endl;
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(47, 11);
        cout << "* Men£ Principal *" << endl;
        showItem("Veh¡culos  ", 51, 14, y == 0);
        showItem("Ventas  ", 51, 15, y == 1);
        showItem("Vendedores  ", 51, 16, y == 2);
        showItem("Sucursales  ", 51, 17, y == 3);
        showItem("Clientes  ", 51, 18, y == 4);
        showItem("Informes  ", 51, 19, y == 5);
        showItem("Configuraci¢n  ", 51, 20, y == 6);
        showItem("Cr‚ditos  ", 51, 21, y == 7);
        showItem2("Salir del Programa  ", 47, 23, y == 9);
       

        switch(rlutil::getkey()) { //getkey() devuelve un int con el valor presionado

        case 14: //UP
            rlutil::locate(46, 14 + y);
            cout << " " << endl;
            y--;
            if (y < 0) {
                y = 0;
            }
            if (y == 8) {
                y--;
            }
            break;
        case 15: //DOWN
            rlutil::locate(46, 14 + y);
            cout << " " << endl;
            y++;
            if (y > 9) {
                y = 9;
            }
            if (y == 8) {
                y++;
            }
            break;
        case 1: //ENTER

            switch (y) {
            case 0:
                _vehiculo.Menu();
                break;
            case 1:
                _venta.Menu();
                break;
            case 2:
                _vendedor.Menu();
                break;
            case 3:
                _sucursal.Menu();
                break;
            case 4:
                _cliente.Menu();
                break;
            case 5:
                _informes.Menu();
                break;
            case 6:
                _configuracion.Menu();
                system("cls");
                break;
            case 7:
                Creditos();
                break;

            case 9:
                opc = 0;
                rlutil::locate(45, 27);
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

void Sistema::Creditos()
{
    system("cls");
    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
    rlutil::locate(40, 9);
    rlutil::setColor(rlutil::COLOR::LIGHTMAGENTA);
    cout << "Programa realizado por Julieta Barraza" << (char)169 << endl;
    rlutil::locate(40, 10);
    cout << "Julio/Agosto 2024" << endl;
    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
    rlutil::anykey();

    system("cls");
}
