#include<iostream>
#include<string>
using namespace std;
 /*

 Los primeros 5 partidos con mayor cantidad de goles (sumar goles de ambos
 equipos) y de cada competición que haya en la base de datos. De haber más de 5
 por igualdad en cantidad de goles, filtrar por fecha, dejando los más recientes. De
 haber similitud de fechas, filtrar por criterio programador.

 Los goles totales a favor y en contra de cada equipo por competición. El usuario
 pedirá que se muestren por pantalla, de un equipo por vez y deberá mostrar
 discriminando por competición.

 Promedio de goles a favor y en contra de cada equipo por competición. El
 usuario pedirá que se muestren por pantalla, de un equipo por vez y deberá
 mostrar discriminando por competición.

 La cantidad total de derrotas y de triunfos de cada equipo por competición. El
 usuario pedirá que se muestren por pantalla, de un equipo por vez y deberá
 mostrar discriminando por competición.

 La fecha con más goles y la fecha con menos goles de cada equipo por
 competición. El usuario pedirá que se muestren por pantalla, de un equipo por
 vez y deberá mostrar discriminando por competición.

 La competición con más goles convertidos.

 El equipo con más goles convertidos y el equipo con menos goles convertidos de
 todas las competiciones y por competición*/

void MainMenu()
{
    system("cls");

    cout << "________________________________________MenuPrincipal____________________________________________________" << endl;
    cout << "1. Ver los primeros 5 partidos con mayor cantidad de goles" << endl;
    cout << "2. Ver goles totales de un equipo" << endl;
    cout << "3. Promedio de goles a favor y en contra de un equipo" << endl;
    cout << "4. La cantidad total de derrotas y triunfos de cada equipo por competicion " << endl;
    cout << "5. La fecha con mas goles y la fecha con menos goles de cada equipo por competicion " << endl;
    cout << "6. La competicion que tiene mayor cantidad de goles " << endl;
    cout << "7. El equipo con mas goles hechos y el equipo con menos goles hecho de todas las tablas de competiciones " << endl;
    cout << endl;
    cout << "0. Salir"
}


