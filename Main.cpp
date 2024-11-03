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

void CargaVector(vector<Data>& ReferenceList);
void Top5GoleadasBubbleSort (const vector<Data>& ReferenceList);
//void Top5GoleadasQuickSort(const vector<Data>& ReferenceList);
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
            //Top5GoleadasQuickSort(DataBase, competicion);
        }else
        {
            Top5GoleadasBubbleSort(DataBase, competicion);
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
            
            GolesTotales(DataBase, equipo, competicion); // funcion que calcula los goles totales de un equipo en una competicion   
            
            system("pause");
            system("cls");
            cout << "Desea ver los datos de otro equipo ?" << endl;
            cout << "Ingrese 1 para Si" << endl;
            cin >> yesOrNo;

            if (yesOrNo != 1)
            {
                seguir = false;
            }
            
        } while (seguir == true);
        
        break;
    case 3:
        seguir = true;
        do
        {
            system("cls");
            cout << "Ingrese el nombre del equipo que desea saber su promedio de goles " << endl;
            cin >> equipo;
            cout << "Ingrese la competicion" << endl;
            cin >> competicion;
            key = GenerateKey(equipo, competicion); // funcion que genera la llave, esta en archivo aparte
            
            TeamMatches = DataBase.getDatosPorClave(key); // vector del equipo solicitado
            
            PromedioGoles(DataBase, equipo, competicion); // funcion que calcula el promedio de goles de un equipo en una competicion

            system("pause");
            system("cls");
            cout << "Desea ver los datos de otro equipo ?" << endl;
            cout << "Ingrese 1 para Si" << endl;
            cin >> yesOrNo;

            if (yesOrNo != 1)
            {
                seguir = false;
            }
        } while (seguir == true);
        
        break;
    case 4:
        seguir = true;
        do
        {
            system("cls");
            cout << "Ingrese el nombre del equipo que desea saber sus derrotas y victorias " << endl;
            cin >> equipo;
            cout << "Ingrese la competicion" << endl;
            cin >> competicion;
            key = GenerateKey(equipo, competicion); // funcion que genera la llave, esta en archivo aparte
            
            TeamMatches = DataBase.getDatosPorClave(key); // vector del equipo solicitado

            TriunfosDerrotas(DataBase, equipo, competicion); // funcion que calcula las victorias y derrotas de un equipo en una competicion            
            
            system("pause");
            system("cls");
            cout << "Desea ver los datos de otro equipo ?" << endl;
            cout << "Ingrese 1 para Si" << endl;
            cin >> yesOrNo;

            if (yesOrNo != 1)
            {
                seguir = false;
            }
        } while (seguir == true);
        break;  
        /*
    case 5:
        seguir = true;
        do
        {
            system("cls");
            cout << "Ingrese el nombre del equipo que desea saber sus fechas con mas y menos goles " << endl;
            cin >> equipo;
            cout << "Ingrese la competicion" << endl;
            cin >> competicion;
            key = GenerateKey(equipo, competicion); // funcion que genera la llave, esta en archivo aparte
            
            TeamMatches = DataBase.getDatosPorClave(key); // vector del equipo solicitado

            FechaMaxMinGoles(DataBase, equipo, competicion); // funcion que calcula las fechas con mas y menos goles de un equipo en una competicion

            system("pause");
            system("cls");
            cout << "Desea ver los datos de otro equipo ?" << endl;
            cout << "Ingrese 1 para Si" << endl;
            cin >> yesOrNo;

            if (yesOrNo != 1)
            {
                seguir = false;
            }
        } while (seguir == true);

        break;  
        */
    case 6:
        seguir = true;
        do
        {
            system("cls");
            cout << "Ingrese la competicion" << endl;
            cin >> competicion;
            key = GenerateKey("", competicion); // funcion que genera la llave, esta en archivo aparte
            
            TeamMatches = DataBase.getDatosPorClave(key); // vector del equipo solicitado

            CompeticionConMasGoles(DataBase, "", competicion); // funcion que calcula los goles convertidos por un equipo en una competicion

            system("pause");
            system("cls");
            cout << "Desea ver los datos de otro equipo ?" << endl;
            cout << "Ingrese 1 para Si" << endl;
            cin >> yesOrNo;

            if (yesOrNo != 1)
            {
                seguir = false;
            }
        } while (seguir == true);
        break;
        /*
    case 7:
        seguir = true;
        do 
        {
            system("cls");
            cout << "";
        } while (seguir == true);

*/

        
    default:
    
        break;
    } 
    return 0;
    }while(op != 0);

}
















// Carga de las bases de dato








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
    int ConditionalCounter = 0;
    Data auxDataBase;         // Base de datos auxiliar para obtener la clave Hash
    int LocalKey, VisitorKey; // claves para introduir en distintas posiciones;
    string StringToASCII;     // variable para pasar las palabras a ASCII

    for (int i = 0; i < ReferenceList.size(); ++i)
    {
        auxDataBase = ReferenceList[i];
        for (char c : auxDataBase.competicion)
        {
            ConditionalCounter++;
            LocalKey += c;
            VisitorKey += c;
        }
        for (char c : auxDataBase.local)
        {
            ConditionalCounter++;
            LocalKey += c;
        }
        for (char c : auxDataBase.visitante)
        {
            ConditionalCounter++;
            VisitorKey += c;
        }

        LoadDataBase.put(LocalKey, ReferenceList[i]);
        LoadDataBase.put(VisitorKey, ReferenceList[i]);
        cout << "Base de datos cargada " << endl;
        cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
        system("pause");
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
            if ((golesPartidos[j].first < golesPartidos[j + 1].first) ||
                (golesPartidos[j].first == golesPartidos[j + 1].first && 
                golesPartidos[j].second.fecha < golesPartidos[j + 1].second.fecha)) {
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
/*
void Top5GoleadasQuickSort(HashMapList<int, Data>& DataBase, const string& competicion) {
    int ConditionalCounter = 0;
    int key = GenerateKey("", competicion); // Llave para acceder a la competición
    vector<Data> CompeticionMatches = DataBase.getDatosPorClave(key);

    vector<pair<int, Data>> golesPartidos;
    for (const Data& partido : CompeticionMatches) {
        int goles = stoi(partido.golesLocal) + stoi(partido.golesVisitante);
        golesPartidos.push_back(make_pair(goles, partido));
    }
        auto compare = [&] (const pair<int, Data>& a, const pair<int, Data>& b) {
        ConditionalCounter++;
        return (a.first < b.first) || (a.first == b.first && a.second.fecha > b.second.fecha);
    };

      auto quickSort = [&](int inicio, int fin) {
        if (inicio < fin) {
            int pivot = golesPartidos[(inicio + fin) / 2].first; // Elegir el pivote
            int i = inicio;
            int j = fin;

            while (i <= j) {
                while (i< golesPartidos.size() && compare (golesPartidos [i], make_pair (pivot, Data{}))) i++;
                while (j>=0 && compare (make_pair (pivot, Data{}), golesPartidos [j])) j--;
                if (i <= j) {
                    swap(golesPartidos[i], golesPartidos[j]);
                    i++;
                    j--;
                }
            }

            if (inicio <j) quickSort(inicio, j); // Subarreglo izquierdo
            if (i<fin ) quickSort(i, fin);    // Subarreglo derecho
        }
    };

    quickSort(0, golesPartidos.size() - 1); // Llamada inicial al QuickSort

    // Mostrar los 5 partidos con más goles
    cout << "Top 5 partidos con más goles en la competición " << competicion << ":" << endl;
    for (size_t i = 0; i < 5 && i < golesPartidos.size(); i++) {
        const Data& partido = golesPartidos[i].second;
        cout << partido.local << " " << partido.golesLocal << " vs " << partido.visitante 
             << " " << partido.golesVisitante << " [" << partido.fecha << "] - Total de goles: " 
             << golesPartidos[i].first << endl;
    }

    cout << "Cantidad de IFs en Top5GoleadasQuickSort: " << ConditionalCounter << endl;
}
*/

/*5.2) Los goles totales a favor y en contra de cada equipo por competición. El usuario
pedirá que se muestren por pantalla, de un equipo por vez y deberá mostrar
discriminando por competición.*/
void GolesTotales (HashMapList<int, Data>& DataBase, const string& equipo, const string& competicion) {
    int ConditionalCounter = 0;
    int key = GenerateKey(equipo, competicion);
    vector<Data> TeamMatches = DataBase.getDatosPorClave(key);

    int golesAFavor = 0, golesEnContra = 0;

    for (const Data& partido : TeamMatches) {
        ConditionalCounter++;
        bool esLocal = (partido.local == equipo);
        golesAFavor += esLocal ? stoi(partido.golesLocal) : stoi(partido.golesVisitante);
        golesEnContra += esLocal ? stoi(partido.golesVisitante) : stoi(partido.golesLocal);
    }

    cout << "Goles a favor de " << equipo << ": " << golesAFavor << endl;
    cout << "Goles en contra de " << equipo << ": " << golesEnContra << endl;
    cout << "Cantidad de IFs en GolesTotales: " << ConditionalCounter << endl;
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

void FechaMaxMinGoles(HashMapList<int, Data>& DataBase, const string& equipo, const string& competicion) {
    int ConditionalCounter = 0;
    int key = GenerateKey(equipo, competicion);
    vector<Data> TeamMatches = DataBase.getDatosPorClave(key);

    string fechaMaxGoles;
    int maxGoles = -1;
    string fechaMinGoles;
    int minGoles = 10000;

    for (const Data& partido : TeamMatches) {
        ConditionalCounter++;
        // Calcula los goles del equipo específico (local o visitante)
        int golesEquipo = (partido.local == equipo) ? stoi(partido.golesLocal) : stoi(partido.golesVisitante);
        // Actualiza la fecha de máximo y mínimo goles del equipo
        if (golesEquipo > maxGoles) {
            maxGoles = golesEquipo;
            fechaMaxGoles = partido.fecha;
        }
        if (golesEquipo < minGoles) {
            minGoles = golesEquipo;
            fechaMinGoles = partido.fecha;
        }
    }
    cout << "Fecha con más goles de " << equipo << " en " << competicion << ": " << fechaMaxGoles << " (" << maxGoles << " goles)" << endl;
    cout << "Fecha con menos goles de " << equipo << " en " << competicion << ": " << fechaMinGoles << " (" << minGoles << " goles)" << endl;
    cout << "Cantidad de IFs en FechaMaxMinGoles: " << ConditionalCounter << endl;
}















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
void EquipoConMasYMenosGoles(HashMapList<int, Data>& DataBase) {
    int ConditionalCounter = 0;

    GolesEquipo equipoMax, equipoMin;
    equipoMin.totalGoles = 10000; // Inicializar con un valor alto
    equipoMax.totalGoles = 0;      // Inicializar con cero

    for (unsigned int key = 0; key < 10000; ++key) { // Cambia 10000 por el rango esperado
        ConditionalCounter++;
        vector<Data> TeamMatches = DataBase.getDatosPorClave(key); // Obtener partidos del equipo

        int totalGoles = 0;

        for (const Data& partido : TeamMatches) {
            totalGoles += stoi(partido.golesLocal) + stoi(partido.golesVisitante); // Sumar goles
        }
        // Actualizar el equipo con más y menos goles
        if (totalGoles > equipoMax.totalGoles) {
            equipoMax.equipo = "Equipo" + to_string(key); // Asignar nombre del equipo
            equipoMax.totalGoles = totalGoles; // Actualizar total de goles
        }
        if (totalGoles < equipoMin.totalGoles && totalGoles > 0) { // Asegurarse que totalGoles no sea negativo
            equipoMin.equipo = "Equipo" + to_string(key); // Asignar nombre del equipo
            equipoMin.totalGoles = totalGoles; // Actualizar total de goles
        }
    }

    cout << "Equipo con más goles: " << equipoMax.equipo << " - Total de goles: " << equipoMax.totalGoles << endl;
    cout << "Equipo con menos goles: " << equipoMin.equipo << " - Total de goles: " << equipoMin.totalGoles << endl;
    cout << "Cantidad de IFs en EquipoConMasYMenosGoles: " << ConditionalCounter << endl; // Mostrar el contador
}


/*6) agregar,eliminar,modificar*/
void AgregarPartido(vector<Data> &ReferenceList, HashMapList <int, Data> &DataBase)
{
    system("cls");
    int ConditionalCounter = 0;
    string jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion;
    Data Parameters;

    cout << "Ingrese la jornada: ";
    getline (cin, jornada);
    cout << endl <<"Ingrese la fecha: ";
    getline(cin, fecha);
    cout << endl << "Ingrese el equipo local: ";
    getline(cin, local);
    cout << endl << "Ingrese los goles del equipo local: ";
    getline (cin, golesLocal);  
    cout << endl <<"Ingrese los goles del equipo visitante: ";
    getline (cin, golesVisitante);
    cout << endl << "Ingrese el equipo visitante: ";
    getline (cin, visitante);
    cout << endl<<  "Ingrese la competicion: ";
    getline (cin, competicion);

    Parameters.Carga(jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion);
    ReferenceList.push_back(Parameters);


    int LocalKey;
    int VisitorKey;

    for (char c : Parameters.competicion)
    {
        ConditionalCounter++;
        LocalKey += c;
        VisitorKey += c;
    }
    for (char c : Parameters.local)
    {
        ConditionalCounter++;
        LocalKey += c;
    }
    for (char c : Parameters.visitante)
    {
        ConditionalCounter++;
        VisitorKey += c;
    }
    
    DataBase.put(LocalKey, Parameters);
    DataBase.put(VisitorKey, Parameters);

    cout << "Partido agregado correctamente" << endl;
    cout << "Cantidad de condicionales: " << ConditionalCounter; 
}

void EliminarPartido(HashMapList<int, Data> &DataBase, vector<Data> &ReferenceList)
{
    system("cls");
    int ConditionalCounter = 0;
    string equipo;
    string competicion;
    string fecha;
    string juegaDe;
    cout << "Ingrese el nombre del equipo que jugo ese partido " << endl;
    getline(cin, equipo);
    cout << "Ingrese el nombre de la competicion que jugo ese equipo " << endl;
    getline(cin, competicion);
    int key = GenerateKey(equipo, competicion);
    vector<Data> ListaDelEquipo = DataBase.getDatosPorClave(key);

    
    
    for (size_t i = 0; i < ListaDelEquipo.size(); i++)
    {
        ConditionalCounter++;
        cout << ListaDelEquipo[i].jornada << " ";
        cout << ListaDelEquipo[i].fecha << " ";
        cout << ListaDelEquipo[i].local << " ";
        cout << ListaDelEquipo[i].golesLocal << " ";
        cout << ListaDelEquipo[i].golesVisitante << " ";
        cout << ListaDelEquipo[i].visitante << " ";
        cout << ListaDelEquipo[i].competicion << endl;
    }

    cout << "Ingrese la fecha en la que se jugo el partido " << endl;
    getline(cin, fecha);
    for (int i = 0; i < ListaDelEquipo.size(); i++)
    {
        ConditionalCounter++;
        if (ListaDelEquipo[i].fecha == fecha)
        {
            ConditionalCounter++;
            if (ListaDelEquipo[i].local == equipo)
            {
                juegaDe = ListaDelEquipo[i].visitante;
            }else
            {
                juegaDe = ListaDelEquipo[i].local;
            }
            ListaDelEquipo.erase(ListaDelEquipo.begin() + i);
            return;
        }
        ConditionalCounter++;
    }


    DataBase.remove(key);
    for (int i = 0; i < ListaDelEquipo.size(); i++)
    {
        ConditionalCounter++;
      DataBase.put(key, ListaDelEquipo[i]);
    }
    EliminarContrario(DataBase, juegaDe, competicion, fecha, ConditionalCounter);
    system("cls");
    cout << "Cantidad de condicionales " << ConditionalCounter << endl;
    system("pause");
}


























void ModificarPartido(HashMapList<int, Data> &DataBase)
{
    system("cls");

    int ConditionalCounter = 0;
    int key;
    string equipo, competicion;
    string fechaDelPartido;
    vector<Data> ListaDelEquipo;

    cout << "Ingrese el equipo del partido que desea modificar: ";
    getline(cin, equipo);
    cout << endl << "Ahora ingrese la competicion en la que juega ese equipo " << endl;
    getline(cin, competicion);
    key = GenerateKey(equipo, competicion);

    ListaDelEquipo = DataBase.getDatosPorClave(key);

    cout << "Ahora ingrese la fecha del partido: " << endl;
    getline(cin, fechaDelPartido);



    bool SeEncontro = false;
    int op;
    Data PartidoAModificar, PartidoSinModificar;

    for (int i = 0; i < ListaDelEquipo.size(); i++)
    {
        ConditionalCounter++;
        if (ListaDelEquipo[i].fecha == fechaDelPartido)
        {
            SeEncontro = true;
            
            PartidoAModificar = ListaDelEquipo[i];


            string Cancha;
            string competicion = ListaDelEquipo[i].competicion;
            string fecha = ListaDelEquipo[i].fecha;
            ConditionalCounter++;

            if (equipo == ListaDelEquipo[i].local)
            {
                Cancha = ListaDelEquipo[i].visitante;
            }else
            {
                Cancha = ListaDelEquipo[i].local;
            }


            ListaDelEquipo.erase(ListaDelEquipo.begin() + i);
            MenuDeModificaciones();
            cin >> op;

            string nuevaJornada, nuevaFecha, nuevoEquipoLocal, nuevosGolesLocales, nuevosGolesVisitantes, nuevoEquipoVisitante, nuevaCompeticion;
            do
            {
            ConditionalCounter++;
            switch (op)
            {
            case 0:
                op = 0;
                break;
            case 1:
                cout << "Ingrese la nueva jornada " << endl;
                getline(cin, nuevaJornada);
                PartidoAModificar.jornada = nuevaJornada;
                break;
            case 2:
                cout << "Ingrese la nueva fecha " << endl;
                getline(cin, nuevaFecha);
                PartidoAModificar.fecha = nuevaFecha;
                break;
            case 3:
                cout << "Ingrese el nuevo equipo local " << endl;
                getline(cin, nuevoEquipoLocal);
                PartidoAModificar.local = nuevoEquipoLocal;
                break;
            case 4:
                cout << "Ingrese la nueva cantidad de goles locales" << endl;
                getline(cin, nuevosGolesLocales);
                PartidoAModificar.golesLocal = nuevosGolesLocales;
                break;
            case 5:
                cout << "Ingrese la nueva cantidad de goles visitante " << endl;
                getline(cin, nuevosGolesVisitantes);
                PartidoAModificar.golesVisitante = nuevosGolesVisitantes;
                break;
            case 6:
                cout << "Ingrese el nuevo equipo visitante " << endl;
                getline(cin, nuevoEquipoVisitante);
                PartidoAModificar.visitante = nuevoEquipoVisitante;
                break;

            case 7:
                cout << "Ingrese la nueva competicion " << endl;
                getline(cin, nuevaCompeticion);
                PartidoAModificar.competicion = nuevaCompeticion;
                break;
            default:
                cout << "Opcion no valida, intente nuevamente " << endl;
                break;
            } 
            } while (op != 0);

            DataBase.remove(key);
            for (int i = 0; i < ListaDelEquipo.size(); i++)
            {
                ConditionalCounter++;
                DataBase.put(key, ListaDelEquipo[i]);
            }
            
            
            ControlDeBase(ConditionalCounter, DataBase, Cancha, fecha, competicion, PartidoAModificar);
            return;
        }
        ConditionalCounter++;
    }
    
    system("cls");
    cout << "Cantidad de condicionales: " << ConditionalCounter;
    system("pause");
}






































/*7) consultas dinamicas */
/*a) Todos los Resultados de un equipo y en una competición específica ingresado por el
usuario.*/
void ResultadosEquipoCompeticion(HashMapList<int, Data>& DataBase, const string& equipo, const string& competicion) {
    system("cls");
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
    system("pause");
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
void ComparacionRendimientoEquipos(HashMapList<int, Data>& DataBase) {
    system("cls");
    int ConditionalCounter = 0;
    string equipo1, equipo2;
    string competicion1, competicion2;
    cout << "Ingrese el nombre del primer equipo: ";
    getline(cin, equipo1);
    cout << "Ingrese la competicion en la que jugo: ";
    getline(cin, competicion1);


    cout << "Ingrese el nombre del segundo equipo: ";
    getline(cin, equipo2);
    cout << "Ingrese la competicion en la que jugo: ";
    getline(cin, competicion2);

    int key1 = GenerateKey(equipo1, competicion1);
    int key2 = GenerateKey(equipo2, competicion2);
    vector<Data> ListaEquipo1 = DataBase.getDatosPorClave(key1);
    vector<Data> ListaEquipo2 = DataBase.getDatosPorClave(key2);

    int golesAfavorEquipo1;
    int golesEnContraEquipo1;
    int golesAfavorEquipo2;
    int golesEnContraEquipo2;

    
    for (int i = 0; i < ListaEquipo1.size(); i++)
    {
        if (equipo1 == ListaEquipo1[i].local)
        {
            for (char c : ListaEquipo1[i].golesLocal)
            {
                ConditionalCounter++;
                if (c != '(' || c != ')')
                {
                    golesAfavorEquipo1 += c - '0';
                }
            }
            for (char c : ListaEquipo1[i].golesVisitante)
            {
                if (c != '(' || c != ')')
                {
                    golesEnContraEquipo1 += c - '0';
                }
            }
            
        }else
        {
            for (char c : ListaEquipo1[i].golesVisitante)
            {
                ConditionalCounter++;
                if (c != '(' || c != ')')
                {
                    golesAfavorEquipo1 += c - '0';
                }
            }
            for (char c : ListaEquipo1[i].golesLocal)
            {
                if (c != '(' || c != ')')
                {
                    golesEnContraEquipo1 += c - '0';
                }
            }
        }   

        

        for (int i = 0; i < ListaEquipo2.size(); i++)
        {
            if (equipo1 == ListaEquipo2[i].local)
            {
                for (char c : ListaEquipo2[i].golesLocal)
                {
                ConditionalCounter++;
                if (c != '(' || c != ')')
                {
                    golesAfavorEquipo2 += c - '0';
                }
                ConditionalCounter++;
                }
                for (char c : ListaEquipo2[i].golesVisitante)
                {
                ConditionalCounter++;
                if (c != '(' || c != ')')
                {
                    golesEnContraEquipo2 += c - '0';
                }
                ConditionalCounter++;
            }
            
        }else
        {
            for (char c : ListaEquipo2[i].golesVisitante)
            {
                ConditionalCounter++;
                if (c != '(' || c != ')')
                {
                    golesAfavorEquipo2 += c - '0';
                }
                ConditionalCounter++;
            }
            for (char c : ListaEquipo2[i].golesLocal)
            {
                ConditionalCounter++;
                if (c != '(' || c != ')')
                {
                    golesEnContraEquipo2 += c - '0';
                }
                ConditionalCounter++;
            }
        }
             
    }
    
    cout << "Rendimiento de los equipos " << endl;
    cout << "Equipo 1: " << equipo1 << endl;
    cout << "Goles a favor: " << golesAfavorEquipo1 << endl;
    cout << "Goles en contra " << golesEnContraEquipo1 << endl;
    
    cout << endl << "Equipo 2: " << equipo2 << endl;
    cout << "Goles a favor: " << golesAfavorEquipo2 << endl;
    cout << "Goles en contra : " << golesEnContraEquipo2 << endl;

    cout << endl << endl << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
    
}
}

/*d) Comparación de rendimiento particular de dos equipos. Analizando sólo los partidos en
los que se han enfrentado esos dos equipos indicar cantidad de partidos que han jugado
en contra, la cantidad de empates y cuál de los dos ha ganado más partidos.*/
void ComparacionRendimientoEquiposParticular(HashMapList<int, Data>& DataBase, const string& equipo1, const string& equipo2) {
    int ConditionalCounter = 0;
    int key1 = GenerateKey(equipo1, "");
    int key2 = GenerateKey(equipo2, "");
    vector<Data> TeamMatches1 = DataBase.getDatosPorClave(key1);
    vector<Data> TeamMatches2 = DataBase.getDatosPorClave(key2);

    int partidosContra = 0;
    int empates = 0;
    int victorias1 = 0;
    int victorias2 = 0;

    for (const Data &partido1 : TeamMatches1) {
        for (const Data &partido2 : TeamMatches2) {
            ConditionalCounter++;
            if (partido1.fecha == partido2.fecha&& partido1.competicion == partido2.competicion) {
                partidosContra++;
                // Se determina los goles dependiendo de si el equipo es local o visitante
                int golesEquipo1 = (partido1.local == equipo1) ? stoi(partido1.golesLocal) : stoi(partido1.golesVisitante);
                int golesEquipo2 = (partido2.local == equipo2) ? stoi(partido2.golesLocal) : stoi(partido2.golesVisitante);

                // Comparación de goles
                if (golesEquipo1 == golesEquipo2) {
                    empates++;
                } else if (golesEquipo1 > golesEquipo2) {
                    victorias1++;
                } else {
                    victorias2++;
                }
            }
        }
    }

    cout << "Cantidad de partidos jugados entre " << equipo1 << " y " << equipo2 << ": " << partidosContra << endl;
    cout << "Cantidad de empates: " << empates << endl;
    cout << "Cantidad de victorias de " << equipo1 << ": " << victorias1 << endl;
    cout << "Cantidad de victorias de " << equipo2 << ": " << victorias2 << endl;
    cout << "Cantidad de IFs en ComparacionRendimientoEquiposParticular: " << ConditionalCounter << endl;
}


/*e) Umbral: el usuario podrá ingresar un umbral de cantidad de goles convertidos por
partido en promedio, especificar si quiere por arriba o por debajo de ese umbral y el
programa deberá filtrar a todos los equipos de todas las competiciones que hayan
convertido dentro de ese umbral, incluyéndose. Discriminar por competición*/
void FiltrarEquiposPorUmbral(HashMapList<int, Data>& DataBase) {
    int ConditionalCounter = 0;
    double umbral;
    string filtro;
    
    cout << "Ingrese el umbral de goles promedio por partido: ";
    cin >> umbral;
    cin.ignore();
    cout << "Ingrese el filtro (arriba o debajo): ";
    getline(cin, filtro);

    // Contador de goles y partidos por equipo y competición
    vector<string> equipos;
    vector<string> competiciones;
    vector<int> totalGoles;
    vector<int> totalPartidos;

    // Recorremos los partidos en la base de datos usando un bucle tradicional
    for (int i = 0; i < 9001; ++i) { 
        vector<Data> listaPartidos = DataBase.getDatosPorClave(i);
        for (const Data& partido : listaPartidos) {
            ConditionalCounter++;

            // Para cada partido, se procesan el local y el visitante
            string competicion = partido.competicion;
            int golesLocal = stoi(partido.golesLocal);
            int golesVisitante = stoi(partido.golesVisitante);
            
            // Actualizamos ambos equipos en una sola llamada a la función
            actualizarGoles(equipos, competiciones, totalGoles, totalPartidos, partido.local, competicion, golesLocal);
            actualizarGoles(equipos, competiciones, totalGoles, totalPartidos, partido.visitante, competicion, golesVisitante);
        }
    }

    // Filtrado basado en el umbral y presentación de resultados
    cout << "Equipos que cumplen con el umbral de goles promedio (" << filtro << " " << umbral << "):" << endl;
    for (size_t i = 0; i < equipos.size(); ++i) {
        double promedioGoles = static_cast<double>(totalGoles[i]) / totalPartidos[i];
        ConditionalCounter++;
        // Uso de un solo if para evaluar el filtro
        if ((filtro == "arriba" && promedioGoles >= umbral) || (filtro == "debajo" && promedioGoles <= umbral)) {
            cout << "Equipo: " << equipos[i] << ", Competicion: " << competiciones[i] 
                 << ", Promedio de Goles: " << promedioGoles << endl;
        }
    }

    cout << endl << "Cantidad de condicionales: " << ConditionalCounter << endl;
}

// Función auxiliar para actualizar goles y partidos
void actualizarGoles(vector<string>& equipos, vector<string>& competiciones, vector<int>& totalGoles, vector<int>& totalPartidos, const string& equipo, const string& competicion, int goles) {
    // Uso de un solo bucle para encontrar y actualizar el equipo
    for (size_t i = 0; i < equipos.size(); ++i) {
        if (equipos[i] == equipo && competiciones[i] == competicion) {
            totalGoles[i] += goles;
            totalPartidos[i]++;
            return;
        }
    }
    // Si el equipo no existe, lo añadimos
    equipos.push_back(equipo);
    competiciones.push_back(competicion);
    totalGoles.push_back(goles);
    totalPartidos.push_back(1);
}
