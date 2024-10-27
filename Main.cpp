#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>


#include"GestorDeDatos.h"
#include"Hash/HashMapList.h"
#include"Hash/Lista.h"

//!!Crear contador de condicionales en cada funcion que use ifs 

using namespace std;

void CargaVector(vector<Data> &ReferenceList)
{
    int ConditionalCounter;// contador de condicionales 
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
    
    Parameters.Carga(jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion); //Usando el metodo de carga para asignar los valores extraidos de la base de datos en una clase parametro
    ReferenceList.push_back(Parameters); //Poner los valores dentro del vector List pasado como referencia

    system("cls");

    cout << "Carga de la base de datos realizada, cantidad de IFs: " << ConditionalCounter << endl;
    system("pause");
}

void CargaBaseHash(HashMapList<int, Data> &LoadDataBase, vector<Data> ReferenceList) //Funcion que carga la base de datos HashMapList 
//Coliciones basadas en base a la clave directa, formadas por codigo ASCII en el proceso
{

    Data auxDataBase; //Base de datos auxiliar para obtener la clave Hash
    int LocalKey, VisitorKey; // claves para introduir en distintas posiciones;
    string StringToASCII; // variable para pasar las palabras a ASCII

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


void Top5Goleadas (vector<Data> ReferenceList)
{
    int ConditionalCounter;
    vector <pair<int, Data>> golesPartidos;
    
    for (Data &partido : ReferenceList)
    {
        ConditionalCounter++;
        int goles = stoi(partido.golesLocal) + stoi(partido.golesVisitante);
        golesPartidos.push_back(make_pair(goles, partido));       
    }
    /* ordenar los partidos por cantidad de goles en orden descendente
    sort (golesPartidos.begin(), golesPartidos.end(), []const (pair<int, Data> &a, const pair<int, Data> &b)
    {
        return a.first > b.first;
    });*/
    cout << "Top 5 partidos con más goles: " << endl;
    for (int i=0; i<5 && i<golesPartidos.size(); i++)
    {
        ConditionalCounter++;
        cout << golesPartidos[i].second.local << " " << golesPartidos[i].second.golesLocal
        << " vs " << golesPartidos[i].second.golesVisitante << " " 
        << golesPartidos[i].second.golesVisitante << "[" << golesPartidos[i].second.fecha << "]" 
        << golesPartidos[i].second.competicion << "Total de goles: " << golesPartidos[i].first << endl;
    }
    

}
/*5.2) Los goles totales a favor y en contra de cada equipo por competición. El usuario
pedirá que se muestren por pantalla, de un equipo por vez y deberá mostrar
discriminando por competición.*/


/* 5.3) Promedio de goles a favor y en contra de cada equipo por competición. El
usuario pedirá que se muestren por pantalla, de un equipo por vez y deberá
mostrar discriminando por competición.*/

/* 
void AgregarPartido (vector<Data> &ReferenceList)
{
    int ConditionalCounter;
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
void EliminarPartido (vector)
*/











int main()
{
    Data Datos;
    vector<Data> List; //Base de datos en formato lista para un mejor manejo en calculos
    HashMapList < int, Data> DataBase(9001); //Base de datos fuente en formato HashMapList para Busqueda y eliminacion de datos

    CargaVector(List); // Funcion Carga de la Base en formato Lista
    CargaBaseHash(DataBase, List); // Funcion Carga de la Base en formato HashMapList   
    
    DataBase.print();
    return 0;
}