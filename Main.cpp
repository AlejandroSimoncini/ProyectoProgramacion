#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "GestorDeDatos.h"
#include"FuncionesOrd_and_Valores.h"
#include"FuncionesDeMenu.h"
#include "Hash/HashMapList.h"
#include "Hash/Lista.h"
using namespace std;
//!!Crear contador de condicionales en cada funcion que use ifs


void CargaVector(vector<Data>& ReferenceList);
void Top5Goleadas(const vector<Data>& ReferenceList);
void GolesTotales(const vector<Data>& ReferenceList);
void PromedioGoles(const vector<Data>& ReferenceList);
void TriunfosDerrotas(const vector<Data>& ReferenceList);
void FechaMaxMinGoles(const vector<Data>& ReferenceList);
void CompeticionConMasGoles(const vector<Data>& ReferenceList);


int main()
{
    Data Datos;
    vector<Data> List;                     // Base de datos en formato lista para un mejor manejo en calculos
    HashMapList<int, Data> DataBase(9001); // Base de datos fuente en formato HashMapList para Busqueda y eliminacion de datos


    bool quicksortused = false;
    int key, yesOrNo;
    string equipo, competicion;
    vector<Data> TeamMatches;
    bool SeguirDelMenu = true;

    CargaVector(List);             // Funcion Carga de la Base en formato Lista
    CargaBaseHash(DataBase, List); // Funcion Carga de la Base en formato HashMapList

    int op;

    do
    {

    MainMenu();
    cin >> op;
    switch (op)
    {
    case 0:

        break;
    case 1:
        if ( quicksortused == false)
        {
            /* codigo top 5 goleadas quicksort */
        }else
        {
            //codigo top 5 goleadas buble
        }
        
        break;
    case 2:
        bool seguir = true;
        do
        {
            system("cls");
            cout << "Ingrese el nombre del equipo que desea ver " << endl;
            cin >> equipo;
            cout << "Ingrese la competicion" << endl;
            cin >> competicion;
            key = GenerateKey(equipo, competicion); // funcion que genera la llave, esta en archivo aparte
            
            TeamMatches = DataBase.getDatosPorClave(key); // vector del equipo solicitado
            // aca va lo tuyo marti

            system("pause");
            system("cls");
            cout << "Desea ver los datos de otro equipo ?" << endl;
            cout << "Ingrese 1 para Si" << endl;
            cin >> yesOrNo;

            if (yesOrNo != 1)
            {
                seguir == false;
            }
            
        } while (seguir == true);
        
        break;
    case 3:
        bool seguir = true;
        do
        {
            system("cls");
            cout << "Ingrese el nombre del equipo que desea saber su promedio de goles " << endl;
            cin >> equipo;
            cout << "Ingrese la competicion" << endl;
            cin >> competicion;
            key = GenerateKey(equipo, competicion); // funcion que genera la llave, esta en archivo aparte
            
            TeamMatches = DataBase.getDatosPorClave(key); // vector del equipo solicitado
            // aca va lo tuyo marti

            system("pause");
            system("cls");
            cout << "Desea ver los datos de otro equipo ?" << endl;
            cout << "Ingrese 1 para Si" << endl;
            cin >> yesOrNo;

            if (yesOrNo != 1)
            {
                seguir == false;
            }
        } while (seguir == true);
        
        break;
    case 4:
        bool seguir = true;
        do
        {
            system("cls");
            cout << "Ingrese el nombre del equipo que desea saber sus derrotas y victorias " << endl;
            cin >> equipo;
            cout << "Ingrese la competicion" << endl;
            cin >> competicion;
            key = GenerateKey(equipo, competicion); // funcion que genera la llave, esta en archivo aparte
            
            TeamMatches = DataBase.getDatosPorClave(key); // vector del equipo solicitado
            // aca va lo tuyo marti

            system("pause");
            system("cls");
            cout << "Desea ver los datos de otro equipo ?" << endl;
            cout << "Ingrese 1 para Si" << endl;
            cin >> yesOrNo;

            if (yesOrNo != 1)
            {
                seguir == false;
            }
        } while (seguir == true);
        break;  
    case 5:

        break;  
    case 6:

        break;
    case 7:

        break;
    default:
        system("cls");
        cout << "Opcion no valida, intentelo nuevamente " << endl;
        system("pause");
        system("cls");

        break;
    }
    } while (SeguirDelMenu == true);
    
    


    
    return 0;
}







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
//5.1)
/*Los primeros 5 partidos con mayor cantidad de goles (sumar goles de ambos
equipos) y de cada competición que haya en la base de datos. De haber más de 5
por igualdad en cantidad de goles, filtrar por fecha, dejando los más recientes. De
haber similitud de fechas, filtrar por criterio programador.
*/
//para usar siempre 
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
//bubble sort 
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
//hacer top5goleadas con un quick sort para usar 1 vez



/*5.2) Los goles totales a favor y en contra de cada equipo por competición. El usuario
pedirá que se muestren por pantalla, de un equipo por vez y deberá mostrar
discriminando por competición.*/

//vector de estructuras
/*
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
*/

// Estructura para almacenar promedios de goles por competición
struct PromedioGolesPorCompeticion {
    string competicion;
    int golesAFavor = 0;
    int golesEnContra = 0;
    int partidosJugados = 0;
};

// Función para filtrar datos del equipo en el vector, basada en la competición
vector<Data> getDatosPorClaveVector(const vector<Data> &ReferenceList, const string &competicion) {
    vector<Data> datosFiltrados;

    for (const Data &partido : ReferenceList) {
        if (partido.competicion == competicion) {
            datosFiltrados.push_back(partido);
        }
    }
    return datosFiltrados;
}

// Función principal para calcular el promedio de goles por competición
void PromedioGoles(const vector<Data> &ReferenceList) {
    int ConditionalCounter = 0;
    string equipo;
    vector<PromedioGolesPorCompeticion> resultados;

    cout << "Ingrese el equipo: ";
    cin >> equipo;

    // Agrupamos las competiciones únicas
    for (const auto &partido : ReferenceList) {
        vector<Data> datosCompeticion = getDatosPorClaveVector(ReferenceList, partido.competicion);
        PromedioGolesPorCompeticion promedio;

        promedio.competicion = partido.competicion;

        // Calcula el promedio para cada competición
        for (const auto &match : datosCompeticion) {
            bool esLocal = match.local == equipo;
            bool esVisitante = match.visitante == equipo;

            ConditionalCounter += esLocal || esVisitante ? 1 : 0;

            if (esLocal || esVisitante) {
                promedio.golesAFavor += esLocal ? stoi(match.golesLocal) : stoi(match.golesVisitante);
                promedio.golesEnContra += esLocal ? stoi(match.golesVisitante) : stoi(match.golesLocal);
                promedio.partidosJugados++;
            }
        }
        // Solo se agregan competiciones en las que el equipo haya jugado
        if (promedio.partidosJugados > 0) {
            resultados.push_back(promedio);
        }
    }

    cout << "Promedio de goles a favor y en contra de " << equipo << " por competición:" << endl;
    for (const auto &resultado : resultados) {
        cout << "Competición: " << resultado.competicion << endl;
        if (resultado.partidosJugados > 0) {
            cout << "   Promedio de goles a favor: " 
                 << static_cast<double>(resultado.golesAFavor) / resultado.partidosJugados << endl;
            cout << "   Promedio de goles en contra: " 
                 << static_cast<double>(resultado.golesEnContra) / resultado.partidosJugados << endl;
        } else {
            cout << "   El equipo no jugó ningún partido en esta competición" << endl;
        }
    }
    cout << "Cantidad de IFs en PromedioGoles: " << ConditionalCounter << endl;
}


/* 5.3) Promedio de goles a favor y en contra de cada equipo por competición. El
usuario pedirá que se muestren por pantalla, de un equipo por vez y deberá
mostrar discriminando por competición.*/ 

/*vector de tipo promedios por competicion */
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

/*5.4) La cantidad total de derrotas y de triunfos de cada equipo por competición. El
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
            { 
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
            { 
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

/*5.5) La fecha con más goles y la fecha con menos goles de cada equipo por
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

/*5.6) La competición con más goles convertidos.*/
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
/* 5.7) El equipo con más goles convertidos y el equipo con menos goles convertidos de
todas las competiciones y por competición.*/
struct GolesEquipo
{
    string equipo;
    int totalGoles = 0;
};
//falta




/*6) agregar,eliminar,modificar*/
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
// cambiar metodo de busqueda -> hash
/**/
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
void ModificarPartido(vector<Data> &ReferenceList)
{
    int ConditionalCounter = 0;
    string fecha;
    cout << "Ingrese la fecha del partido a modificar: ";
    cin >> fecha;

    for (int i = 0; i < ReferenceList.size(); i++)
    {
        ConditionalCounter++;
        if (ReferenceList[i].fecha == fecha)
        {
            cout << "Ingrese la jornada: ";
            cin >> ReferenceList[i].jornada;
            cout << "Ingrese la fecha: ";
            cin >> ReferenceList[i].fecha;
            cout << "Ingrese el equipo local: ";
            cin >> ReferenceList[i].local;
            cout << "Ingrese los goles del equipo local: ";
            cin >> ReferenceList[i].golesLocal;
            cout << "Ingrese los goles del equipo visitante: ";
            cin >> ReferenceList[i].golesVisitante;
            cout << "Ingrese el equipo visitante: ";
            cin >> ReferenceList[i].visitante;
            cout << "Ingrese la competicion: ";
            cin >> ReferenceList[i].competicion;

            cout << "Partido modificado correctamente" << endl;
            return;
        }
    }
    cout << "No se encontro el partido" << endl;
}
/*7) consultas dinamicas */
/*a) Todos los Resultados de un equipo y en una competición específica ingresado por el
usuario.*/

//!!! si te gusta asi, hago las otras 
void ResultadosEquipoCompeticion(vector<Data> ReferenceList)
{
    int ConditionalCounter = 0;
    string equipo, competicion;
    cout << "Ingrese el nombre del equipo: ";
    cin >> equipo;
    cout << "Ingrese el nombre de la competición: ";
    cin >> competicion;

    for (Data &partido : ReferenceList)
    {
        ConditionalCounter++;
        if ((partido.local == equipo || partido.visitante == equipo) && partido.competicion == competicion)
        {
            cout << "Jornada: " << partido.jornada << " Fecha: " << partido.fecha << " Local: " << partido.local << " Goles Local: " << partido.golesLocal << " Goles Visitante: " << partido.golesVisitante << " Visitante: " << partido.visitante << " Competición: " << partido.competicion << endl;
        }
    }
    cout << "Cantidad de IFs en ResultadosEquipoCompeticion: " << ConditionalCounter << endl;
}


/*b) Resultados de un equipo entre dos fechas ingresadas por el usuario.*/

/*c) Comparación de rendimiento general (cantidad de goles a favor y en contra) entre dos
equipos ingresados por el usuario. Ambos equipos no necesariamente se han enfrentado
entre ellos y pueden estar en diferentes competiciones. Discriminar por competición.*/

/*d) Comparación de rendimiento particular de dos equipos. Analizando sólo los partidos en
los que se han enfrentado esos dos equipos indicar cantidad de partidos que han jugado
en contra, la cantidad de empates y cuál de los dos ha ganado más partidos.*/

/*e) Umbral: el usuario podrá ingresar un umbral de cantidad de goles convertidos por
partido en promedio, especificar si quiere por arriba o por debajo de ese umbral y el
programa deberá filtrar a todos los equipos de todas las competiciones que hayan
convertido dentro de ese umbral, incluyéndose. Discriminar por competición*/



