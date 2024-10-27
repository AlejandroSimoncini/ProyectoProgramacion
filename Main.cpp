#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "GestorDeDatos.h"
#include "Hash/HashMapList.h"
#include "Hash/Lista.h"

//!!Crear contador de condicionales en cada funcion que use ifs
// agregue     cout << "Cantidad de IFs en ...: " << ConditionalCounter << endl; en las funciones 
//porq vi q lo pusiste en la funcion de carga de la base de datos
//no se si está bien, avisame sino lo saco

using namespace std;

void CargaVector(vector<Data> &ReferenceList)
{
    int ConditionalCounter; // contador de condicionales
    string jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion;
    Data Parameters;

    string line;
    ifstream file("Base_Datos_COMA.csv");

    if (!file.is_open())
    {
        cerr << "No se pudo abrir el archivo " << endl;
    }
    ConditionalCounter++;

    getline(file, line); // ignorar la primera fila del archivo csv
    while (getline(file, line))
    {
        ConditionalCounter++;
        stringstream ss(line);

        getline(ss, jornada, ',');
        getline(ss, fecha, ',');
        getline(ss, local, ',');
        getline(ss, golesLocal, ',');
        getline(ss, golesVisitante, ',');
        getline(ss, visitante, ',');
        getline(ss, competicion, ',');
    }

    Parameters.Carga(jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion); // Usando el metodo de carga para asignar los valores extraidos de la base de datos en una clase parametro
    ReferenceList.push_back(Parameters);                                                         // Poner los valores dentro del vector List pasado como referencia

    system("cls");

    cout << "Carga de la base de datos realizada, cantidad de IFs: " << ConditionalCounter << endl;
    system("pause");
}

void CargaBaseHash(HashMapList<int, Data> &LoadDataBase, vector<Data> ReferenceList) // Funcion que carga la base de datos HashMapList
// Coliciones basadas en base a la clave directa, formadas por codigo ASCII en el proceso
{

    Data auxDataBase;         // Base de datos auxiliar para obtener la clave Hash
    int LocalKey, VisitorKey; // claves para introduir en distintas posiciones;
    string StringToASCII;     // variable para pasar las palabras a ASCII

    for (int i = 0; i < ReferenceList.size(); ++i)
    {
        auxDataBase = ReferenceList[i];
        for (char c : auxDataBase.competicion)
        {
            LocalKey += c;
            VisitorKey += c;
        }
        for (char c : auxDataBase.local)
        {
            LocalKey += c;
        }
        for (char c : auxDataBase.visitante)
        {
            VisitorKey += c;
        }

        LoadDataBase.put(LocalKey, ReferenceList[i]);
        LoadDataBase.put(VisitorKey, ReferenceList[i]);
    }
}

/*Los primeros 5 partidos con mayor cantidad de goles (sumar goles de ambos
equipos) y de cada competición que haya en la base de datos. De haber más de 5
por igualdad en cantidad de goles, filtrar por fecha, dejando los más recientes. De
haber similitud de fechas, filtrar por criterio programador.
*/

void Top5Goleadas(vector<Data> ReferenceList)
{
    int ConditionalCounter = 0;
    vector<pair<int, Data>> golesPartidos;

    for (Data &partido : ReferenceList)
    {
        ConditionalCounter++;
        int goles = stoi(partido.golesLocal) + stoi(partido.golesVisitante);
        golesPartidos.push_back(make_pair(goles, partido));
    }

    // Ordena los partidos por cantidad de goles en orden descendente
    sort(golesPartidos.begin(), golesPartidos.end(), [](const pair<int, Data> &a, const pair<int, Data> &b)
         { return a.first > b.first; });

    cout << "Top 5 partidos con más goles: " << endl;
    for (int i = 0; i < 5 && i < golesPartidos.size(); i++)
    {
        ConditionalCounter++;
        cout << golesPartidos[i].second.local << " " << golesPartidos[i].second.golesLocal
             << " vs " << golesPartidos[i].second.visitante << " "
             << golesPartidos[i].second.golesVisitante << " [" << golesPartidos[i].second.fecha << "] "
             << golesPartidos[i].second.competicion << " - Total de goles: " << golesPartidos[i].first << endl;
    }
    cout << "Cantidad de IFs en Top5Goleadas: " << ConditionalCounter << endl;
}

/*5.2) Los goles totales a favor y en contra de cada equipo por competición. El usuario
pedirá que se muestren por pantalla, de un equipo por vez y deberá mostrar
discriminando por competición.*/

struct GolesPorCompeticion
{
    string competicion;
    int golesAFavor = 0;
    int golesEnContra = 0;
};

void GolesTotales(vector<Data> ReferenceList)
{
    int ConditionalCounter = 0;
    string equipo;
    vector<GolesPorCompeticion> resultados; // Vector q almacena goles por competicion

    cout << "Ingrese el equipo: ";
    cin >> equipo;

    for (Data &partido : ReferenceList)
    {
        ConditionalCounter++;
        bool encontrado = false;

        for (auto &resultado : resultados)
        {
            if (resultado.competicion == partido.competicion)
            {
                encontrado = true;

                if (partido.local == equipo)
                { // Equipo juega como local
                    resultado.golesAFavor += stoi(partido.golesLocal);
                    resultado.golesEnContra += stoi(partido.golesVisitante);
                }
                else if (partido.visitante == equipo)
                { // Equipo juega como visitante
                    resultado.golesAFavor += stoi(partido.golesVisitante);
                    resultado.golesEnContra += stoi(partido.golesLocal);
                }
                break;
            }
        }

        // Si la competición no estaba en el vector ->>se agrega una nueva entrada
        if (!encontrado)
        {
            GolesPorCompeticion nuevoResultado;
            nuevoResultado.competicion = partido.competicion;

            if (partido.local == equipo)
            { // Equipo juega como local
                nuevoResultado.golesAFavor += stoi(partido.golesLocal);
                nuevoResultado.golesEnContra += stoi(partido.golesVisitante);
            }
            else if (partido.visitante == equipo)
            { // Equipo juega como visitante
                nuevoResultado.golesAFavor += stoi(partido.golesVisitante);
                nuevoResultado.golesEnContra += stoi(partido.golesLocal);
            }
            resultados.push_back(nuevoResultado);
        }
    }

    cout << "Goles a favor y en contra de " << equipo << " por competición:" << endl;
    for (const auto &resultado : resultados)
    {
        cout << "Competición: " << resultado.competicion << endl;
        cout << "   Goles a favor: " << resultado.golesAFavor << endl;
        cout << "   Goles en contra: " << resultado.golesEnContra << endl;
    }
    cout << "Cantidad de IFs en GolesTotales: " << ConditionalCounter << endl;
}

/* 5.3) Promedio de goles a favor y en contra de cada equipo por competición. El
usuario pedirá que se muestren por pantalla, de un equipo por vez y deberá
mostrar discriminando por competición.*/
struct PromedioGolesPorCompeticion
{
    string competicion;
    int golesAFavor = 0;
    int golesEnContra = 0;
    int partidosJugados = 0;
};

void PromedioGoles(vector<Data> ReferenceList)
{
    int ConditionalCounter = 0;
    string equipo;
    vector<PromedioGolesPorCompeticion> resultados;

    cout << "Ingrese el equipo: ";
    cin >> equipo;

    for (Data &partido : ReferenceList)
    {
        ConditionalCounter++;
        bool encontrado = false;

        for (auto &resultado : resultados)
        {
            if (resultado.competicion == partido.competicion)
            {
                encontrado = true;

                if (partido.local == equipo)
                {
                    resultado.golesAFavor += stoi(partido.golesLocal);
                    resultado.golesEnContra += stoi(partido.golesVisitante);
                }
                else if (partido.visitante == equipo)
                {
                    resultado.golesAFavor += stoi(partido.golesVisitante);
                    resultado.golesEnContra += stoi(partido.golesLocal);
                }
                resultado.partidosJugados++;
                break;
            }
        }

        if (!encontrado)
        {
            PromedioGolesPorCompeticion nuevoResultado;
            nuevoResultado.competicion = partido.competicion;

            if (partido.local == equipo)
            {
                nuevoResultado.golesAFavor += stoi(partido.golesLocal);
                nuevoResultado.golesEnContra += stoi(partido.golesVisitante);
            }
            else if (partido.visitante == equipo)
            {
                nuevoResultado.golesAFavor += stoi(partido.golesVisitante);
                nuevoResultado.golesEnContra += stoi(partido.golesLocal);
            }
            nuevoResultado.partidosJugados++;
            resultados.push_back(nuevoResultado);
        }
    }

    cout << "Promedio de goles a favor y en contra de " << equipo << " por competición:" << endl;
    for (const auto &resultado : resultados)
    {
        cout << "Competición: " << resultado.competicion << endl;
        if (resultado.partidosJugados > 0)
        {
            cout << "   Promedio de goles a favor: " << static_cast<double>(resultado.golesAFavor) / resultado.partidosJugados << endl;
            cout << "   Promedio de goles en contra: " << static_cast<double>(resultado.golesEnContra) / resultado.partidosJugados << endl;
        }
        else
        {
            cout << "   El equipo no jugó ningún partido en esta competición" << endl;
        }
    }
    cout << "Cantidad de IFs en PromedioGoles: " << ConditionalCounter << endl;
}

/*La cantidad total de derrotas y de triunfos de cada equipo por competición. El
usuario pedirá que se muestren por pantalla, de un equipo por vez y deberá
mostrar discriminando por competición.*/

struct ResultadoCompeticion
{
    string competicion;
    int triunfos;
    int derrotas;
};

void TriunfosDerrotas(vector<Data> ReferenceList)
{
    int ConditionalCounter = 0;
    string equipo;
    vector<ResultadoCompeticion> resultados; // Vector q almacena resultados por competicion

    cout << "Ingrese el nombre del equipo: ";
    cin >> equipo;

    // Recorre todos los partidos para acumular triunfos y derrotas por competición
    for (Data &partido : ReferenceList)
    {
        ConditionalCounter++;
        bool encontrado = false;

        // Busca si la competición ya existe en el vector
        for (auto &resultado : resultados)
        {
            if (resultado.competicion == partido.competicion)
            {
                encontrado = true;
                if (partido.local == equipo)
                { // Equipo juega como local
                    if (stoi(partido.golesLocal) > stoi(partido.golesVisitante))
                    {
                        resultado.triunfos++; 
                    }
                    else if (stoi(partido.golesLocal) < stoi(partido.golesVisitante))
                    {
                        resultado.derrotas++; 
                    }
                }
                else if (partido.visitante == equipo)
                { // Equipo juega como visitante
                    if (stoi(partido.golesVisitante) > stoi(partido.golesLocal))
                    {
                        resultado.triunfos++; 
                    }
                    else if (stoi(partido.golesVisitante) < stoi(partido.golesLocal))
                    {
                        resultado.derrotas++;
                    }
                }
                break;
            }
        }

        // Si la competición no estaba en el vector ->> se agrega una nueva entrada
        if (!encontrado)
        {
            ResultadoCompeticion nuevoResultado;
            nuevoResultado.competicion = partido.competicion;
            nuevoResultado.triunfos = 0;
            nuevoResultado.derrotas = 0;

            if (partido.local == equipo)
            { // Equipo juega como local
                if (stoi(partido.golesLocal) > stoi(partido.golesVisitante))
                {
                    nuevoResultado.triunfos++;
                }
                else if (stoi(partido.golesLocal) < stoi(partido.golesVisitante))
                {
                    nuevoResultado.derrotas++;
                }
            }
            else if (partido.visitante == equipo)
            { // Equipo juega como visitante
                if (stoi(partido.golesVisitante) > stoi(partido.golesLocal))
                {
                    nuevoResultado.triunfos++;
                }
                else if (stoi(partido.golesVisitante) < stoi(partido.golesLocal))
                {
                    nuevoResultado.derrotas++;
                }
            }
            resultados.push_back(nuevoResultado);
        }
    }

    cout << "Triunfos y derrotas de " << equipo << " por competición:" << endl;
    for (const auto &resultado : resultados)
    {
        cout << "Competición: " << resultado.competicion << endl;
        cout << "   Triunfos: " << resultado.triunfos << endl;
        cout << "   Derrotas: " << resultado.derrotas << endl;
    }
    cout << "Cantidad de IFs en TriunfosDerrotas: " << ConditionalCounter << endl;
}

void AgregarPartido(vector<Data> &ReferenceList)
{
    int ConditionalCounter = 0;
    string jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion;
    Data Parameters;

    cout << "Ingrese la jornada: ";
    cin >> jornada;
    cout << "Ingrese la fecha: ";
    cin >> fecha;
    cout << "Ingrese el equipo local: ";
    cin >> local;
    cout << "Ingrese los goles del equipo local: ";
    cin >> golesLocal;
    cout << "Ingrese los goles del equipo visitante: ";
    cin >> golesVisitante;
    cout << "Ingrese el equipo visitante: ";
    cin >> visitante;
    cout << "Ingrese la competicion: ";
    cin >> competicion;

    Parameters.Carga(jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion);
    ReferenceList.push_back(Parameters);

    cout << "Partido agregado correctamente" << endl;
}

void EliminarPartido(vector<Data> &ReferenceList)
{
    int ConditionalCounter = 0;
    string fecha;
    cout << "Ingrese la fecha del partido a eliminar: ";
    cin >> fecha;

    for (int i = 0; i < ReferenceList.size(); i++)
    {
        ConditionalCounter++;
        if (ReferenceList[i].fecha == fecha)
        {
            ReferenceList.erase(ReferenceList.begin() + i);
            cout << "Partido eliminado correctamente" << endl;
            return;
        }
    }
    cout << "No se encontro el partido" << endl;
}
/*La fecha con más goles y la fecha con menos goles de cada equipo por
competición. El usuario pedirá que se muestren por pantalla, de un equipo por
vez y deberá mostrar discriminando por competición.
*/
struct FechaGoles
{
    string competicion;
    string fechaMaxGoles;
    int maxGoles;
    string fechaMinGoles;
    int minGoles;
};

void FechaMaxMinGoles(vector<Data> ReferenceList)
{
    int ConditionalCounter = 0;
    string equipo;
    vector<FechaGoles> resultados; // Vector q almacena los resultados por competicion

    cout << "Ingrese el nombre del equipo: ";
    cin >> equipo;

    // Recorre todos los partidos para calcular la fecha con + y - goles por competición
    for (Data &partido : ReferenceList)
    {
        ConditionalCounter++;
        bool encontrado = false;

        // Busca si la competición ya existe en el vector
        for (auto &resultado : resultados)
        {
            if (resultado.competicion == partido.competicion)
            {
                encontrado = true;
                int golesEquipo = 0;

                // goles del equipo en el partido actual
                if (partido.local == equipo)
                {
                    golesEquipo = stoi(partido.golesLocal);
                }
                else if (partido.visitante == equipo)
                {
                    golesEquipo = stoi(partido.golesVisitante);
                }

                // Actualiza las fechas de max y min goles para esta competición
                if (golesEquipo > resultado.maxGoles)
                {
                    resultado.maxGoles = golesEquipo;
                    resultado.fechaMaxGoles = partido.fecha;
                }
                if (golesEquipo < resultado.minGoles)
                {
                    resultado.minGoles = golesEquipo;
                    resultado.fechaMinGoles = partido.fecha;
                }
                break;
            }
        }

        // Si la competición no estaba en el vector ->> se agrega una nueva entrada
        if (!encontrado)
        {
            FechaGoles nuevoResultado;
            nuevoResultado.competicion = partido.competicion;

            if (partido.local == equipo)
            {
                nuevoResultado.maxGoles = nuevoResultado.minGoles = stoi(partido.golesLocal);
                nuevoResultado.fechaMaxGoles = nuevoResultado.fechaMinGoles = partido.fecha;
            }
            else if (partido.visitante == equipo)
            {
                nuevoResultado.maxGoles = nuevoResultado.minGoles = stoi(partido.golesVisitante);
                nuevoResultado.fechaMaxGoles = nuevoResultado.fechaMinGoles = partido.fecha;
            }
            resultados.push_back(nuevoResultado);
        }
    }

    cout << "Fecha con más y menos goles de " << equipo << " por competición:" << endl;
    for (const auto &resultado : resultados)
    {
        cout << "Competición: " << resultado.competicion << endl;
        cout << "   Fecha con más goles: " << resultado.fechaMaxGoles << " - Goles: " << resultado.maxGoles << endl;
        cout << "   Fecha con menos goles: " << resultado.fechaMinGoles << " - Goles: " << resultado.minGoles << endl;
    }
    cout << "Cantidad de IFs en FechaMaxMinGoles: " << ConditionalCounter << endl;
}

/*La competición con más goles convertidos.*/
struct GolesCompeticion
{
    string competicion;
    int totalGoles = 0;
};

void CompeticionConMasGoles(vector<Data> ReferenceList)
{
    int ConditionalCounter = 0;
    vector<GolesCompeticion> resultados; // Vector que almacena los goles por competición

    // Recorre todos los partidos para acumular los goles por competición
    for (Data &partido : ReferenceList)
    {
        ConditionalCounter++;
        bool encontrado = false;

        // Buscar si la competición ya existe en el vector resultados
        for (auto &resultado : resultados)
        {
            if (resultado.competicion == partido.competicion)
            {
                encontrado = true;
                resultado.totalGoles += stoi(partido.golesLocal) + stoi(partido.golesVisitante);
                break;
            }
        }

        // Si la competición no estaba en el vector -> se agrega una nueva entrada
        if (!encontrado)
        {
            GolesCompeticion nuevoResultado;
            nuevoResultado.competicion = partido.competicion;
            nuevoResultado.totalGoles = stoi(partido.golesLocal) + stoi(partido.golesVisitante);
            resultados.push_back(nuevoResultado);
        }
    }

    string competicionMaxGoles;
    int maxGoles = 0;

    for (const auto &resultado : resultados)
    {
        if (resultado.totalGoles > maxGoles)
        {
            maxGoles = resultado.totalGoles;
            competicionMaxGoles = resultado.competicion;
        }
    }

    cout << "La competición con más goles convertidos es: " << competicionMaxGoles << " con un total de " << maxGoles << " goles." << endl;
    cout << "Cantidad de IFs en CompeticionConMasGoles: " << ConditionalCounter << endl;
}
/* El equipo con más goles convertidos y el equipo con menos goles convertidos de
todas las competiciones y por competición.*/
struct GolesEquipo
{
    string equipo;
    int totalGoles = 0;
};


int main()
{
    Data Datos;
    vector<Data> List;                     // Base de datos en formato lista para un mejor manejo en calculos
    HashMapList<int, Data> DataBase(9001); // Base de datos fuente en formato HashMapList para Busqueda y eliminacion de datos

    CargaVector(List);             // Funcion Carga de la Base en formato Lista
    CargaBaseHash(DataBase, List); // Funcion Carga de la Base en formato HashMapList

    DataBase.print();
    return 0;
}