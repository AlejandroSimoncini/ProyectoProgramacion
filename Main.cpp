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

// Función que usa Bubble Sort para ordenar los partidos por cantidad de goles
void Top5GoleadasBubbleSort(HashMapList<int, Data>& DataBase, const string& competicion) {
    int ConditionalCounter = 0;
    int key = GenerateKey("", competicion); // Llave para acceder a la competición
    vector<Data> CompeticionMatches = DataBase.getDatosPorClave(key);

    vector<pair<int, Data>> golesPartidos;

    // Llenar el vector con pares de cantidad de goles y datos del partido
    for (const Data& partido : CompeticionMatches) {
        int goles = stoi(partido.golesLocal) + stoi(partido.golesVisitante);
        golesPartidos.push_back(make_pair(goles, partido));
    }

    // Ordenar usando Bubble Sort (orden descendente)
    for (size_t i = 0; i < golesPartidos.size(); i++) {
        for (size_t j = 0; j < golesPartidos.size() - i - 1; j++) {
            ConditionalCounter++;
            if (golesPartidos[j].first < golesPartidos[j + 1].first) {
                swap(golesPartidos[j], golesPartidos[j + 1]);
            }
        }
    }

    // Mostrar los 5 partidos con más goles
    cout << "Top 5 partidos con más goles en la competición " << competicion << ":" << endl;
    for (size_t i = 0; i < 5 && i < golesPartidos.size(); i++) {
        const Data& partido = golesPartidos[i].second;
        cout << partido.local << " " << partido.golesLocal << " vs " << partido.visitante 
             << " " << partido.golesVisitante << " [" << partido.fecha << "] - Total de goles: " 
             << golesPartidos[i].first << endl;
    }

    cout << "Cantidad de IFs en Top5GoleadasBubbleSort: " << ConditionalCounter << endl;
}
//falta la de quick sort


/*5.2) Los goles totales a favor y en contra de cada equipo por competición. El usuario
pedirá que se muestren por pantalla, de un equipo por vez y deberá mostrar
discriminando por competición.*/

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
void PromedioGoles(HashMapList<int, Data>& DataBase, const string& equipo, const string& competicion) {
    int ConditionalCounter = 0;
    int key = GenerateKey(equipo, competicion);
    vector<Data> TeamMatches = DataBase.getDatosPorClave(key);

    int golesAFavor = 0, golesEnContra = 0, partidosJugados = 0;

    for (const Data& partido : TeamMatches) {
        ConditionalCounter++;
        bool esLocal = (partido.local == equipo);
        golesAFavor += esLocal ? stoi(partido.golesLocal) : stoi(partido.golesVisitante);
        golesEnContra += esLocal ? stoi(partido.golesVisitante) : stoi(partido.golesLocal);
        partidosJugados++;
    }

    if (partidosJugados > 0) {
        cout << "Promedio de goles a favor: " << static_cast<double>(golesAFavor) / partidosJugados << endl;
        cout << "Promedio de goles en contra: " << static_cast<double>(golesEnContra) / partidosJugados << endl;
    } else {
        cout << "No hay partidos registrados para " << equipo << " en la competición " << competicion << endl;
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
void TriunfosDerrotas(HashMapList<int, Data>& DataBase, const string& equipo, const string& competicion) {
    int ConditionalCounter = 0;
    int key = GenerateKey(equipo, competicion);
    vector<Data> TeamMatches = DataBase.getDatosPorClave(key);

    int triunfos = 0, derrotas = 0;

    for (const Data& partido : TeamMatches) {
        ConditionalCounter++;
        bool esLocal = (partido.local == equipo);
        int golesEquipo = esLocal ? stoi(partido.golesLocal) : stoi(partido.golesVisitante);
        int golesOponente = esLocal ? stoi(partido.golesVisitante) : stoi(partido.golesLocal);
        
        triunfos += (golesEquipo > golesOponente);
        derrotas += (golesEquipo < golesOponente);
    }

    cout << "Triunfos de " << equipo << ": " << triunfos << endl;
    cout << "Derrotas de " << equipo << ": " << derrotas << endl;
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

void FechaMaxMinGoles()

/*5.6) La competición con más goles convertidos.*/
struct GolesCompeticion
{
    string competicion;
    int totalGoles = 0;
};

void CompeticionConMasGoles(HashMapList<int, Data>& DataBase, const string& equipo, const string& competicion){
    int ConditionalCounter = 0;
    int key = GenerateKey(equipo, competicion);
    vector<Data> TeamMatches = DataBase.getDatosPorClave(key);

    int totalGoles = 0;

    for (const Data& partido : TeamMatches) {
        ConditionalCounter++;
        totalGoles += stoi(partido.golesLocal) + stoi(partido.golesVisitante);
    }

    cout << "Total de goles convertidos por " << competicion << ": " << totalGoles << endl;
    cout << "Cantidad de IFs en CompeticionConMasGoles: " << ConditionalCounter << endl;
}

/* 5.7) El equipo con más goles convertidos y el equipo con menos goles convertidos de
todas las competiciones y por competición.*/
struct GolesEquipo
{
    string equipo;
    int totalGoles = 0;
};
void EquipoConMasGoles(HashMapList<int, Data>& DataBase, const string& equipo, const string& competicion){
    int ConditionalCounter = 0;
    int key = GenerateKey(equipo, competicion);
    vector<Data> TeamMatches = DataBase.getDatosPorClave(key);

    int totalGoles = 0;

    for (const Data& partido : TeamMatches) {
        ConditionalCounter++;
        totalGoles += stoi(partido.golesLocal) + stoi(partido.golesVisitante);
    }

    cout << "Total de goles convertidos por " << competicion << ": " << totalGoles << endl;
    cout << "Cantidad de IFs en CompeticionConMasGoles: " << ConditionalCounter << endl;
}

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
void EliminarPartido(HashMapList<int, Data> &DataBase, vector<Data> &ReferenceList)
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

void ModificarPartido(HashMapList<int, Data> &DataBase, vector<Data> &ReferenceList)
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
void ResultadosEquipoCompeticion(HashMapList<int, Data>& DataBase, const string& equipo, const string& competicion) {
    int ConditionalCounter = 0;
    int key = GenerateKey(equipo, competicion);
    vector<Data> TeamMatches = DataBase.getDatosPorClave(key);

    cout << "Resultados del equipo " << equipo << " en la competición " << competicion << ":" << endl;
    for (const Data &partido : TeamMatches) {
        ConditionalCounter++;
        cout << "Jornada: " << partido.jornada << " Fecha: " << partido.fecha 
             << " Local: " << partido.local << " Goles Local: " << partido.golesLocal 
             << " Goles Visitante: " << partido.golesVisitante << " Visitante: " 
             << partido.visitante << " Competición: " << partido.competicion << endl;
    }

    cout << "Cantidad de IFs en ResultadosEquipoCompeticion: " << ConditionalCounter << endl;
}



/*b) Resultados de un equipo entre dos fechas ingresadas por el usuario.*/
void ResultadosEquipoFechas(HashMapList<int, Data>& DataBase, const string& equipo, const string& fechaInicio, const string& fechaFin) {
    int ConditionalCounter = 0;
    int key = GenerateKey(equipo, "");
    vector<Data> TeamMatches = DataBase.getDatosPorClave(key);

    cout << "Resultados del equipo " << equipo << " entre " << fechaInicio << " y " << fechaFin << ":" << endl;
    for (const Data &partido : TeamMatches) {
        ConditionalCounter++;
        if (partido.fecha >= fechaInicio && partido.fecha <= fechaFin) {
            cout << "Jornada: " << partido.jornada << " Fecha: " << partido.fecha 
                 << " Local: " << partido.local << " Goles Local: " << partido.golesLocal 
                 << " Goles Visitante: " << partido.golesVisitante << " Visitante: " 
                 << partido.visitante << " Competición: " << partido.competicion << endl;
        }
    }

    cout << "Cantidad de IFs en ResultadosEquipoFechas: " << ConditionalCounter << endl;
}
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



