#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<set>
#include<map>
#include<climits>

#include"Data.h"
#include"../Hash/HashMapList.h"
#include"Menu.h"


using namespace std;

int GenerarClave(const string& competicion, const string& equipo1, const string& equipo2);
int partitionCustom(vector<Data>& datos, int low, int high);
void FechaMaxMinGoles (vector<Data> PartidosJugados, string equipoASaber, string competicion);






//muestra y devolucion de datos
void LeerDatosVector(const vector<Data>& datos) {
    for (const auto& item : datos) {
        cout << item.jornada << " "
             << item.fecha << " "
             << item.local << " "
             << item.golesLocal << " "
             << item.golesVisitante << " "
             << item.visitante << " "
             << item.competicion << endl;
    }
}

vector<string> ObtenerEquiposUnicos(const vector<Data>& ReferenceList) {
    int ConditionalCounter = 0;
    set<string> equiposUnicos; // Usamos un set para evitar duplicados

    // Recorremos todos los partidos en ReferenceList
    for (const auto& partido : ReferenceList) {
        ConditionalCounter++;
        equiposUnicos.insert(partido.local);      // Agregamos el equipo local
        equiposUnicos.insert(partido.visitante);  // Agregamos el equipo visitante
    }

    // Convertimos el set en un vector
    vector<string> vectorEquiposUnicos(equiposUnicos.begin(), equiposUnicos.end());

    cout << "Cantidad de condicionales " << ConditionalCounter <<endl;
    system("pause");
    return vectorEquiposUnicos;
}

vector<Data> ArmadoDelVector(HashMapList<int, Data> &DataBase, string equipoASaber, string Competicion, vector<string> Equipos)
{
    int ConditionalCounter = 0;

    vector<Data> VectorDeRetorno, VectorAuxiliar;
    
    // Llenamos VectorDeRetorno con los partidos correspondientes
    for (int i = 0; i < Equipos.size(); i++)
    {
        ConditionalCounter++;
        VectorAuxiliar = DataBase.getDatosPorClave(GenerarClave(Competicion, equipoASaber, Equipos[i]));
        VectorDeRetorno.insert(VectorDeRetorno.end(), VectorAuxiliar.begin(), VectorAuxiliar.end());
    }
    
    // Recorremos VectorDeRetorno de atrás hacia adelante y eliminamos los elementos no deseados
    for (int i = VectorDeRetorno.size() - 1; i >= 0; i--)
    {
        ConditionalCounter += 3;
        if (VectorDeRetorno[i].local != equipoASaber && VectorDeRetorno[i].visitante != equipoASaber || VectorDeRetorno[i].competicion != Competicion)
        {
            VectorDeRetorno.erase(VectorDeRetorno.begin() + i);
        }
        ConditionalCounter++;
    }
    
    cout << "Vector retornado " << endl;
    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
    return VectorDeRetorno;
}


































//carga
void CargaBaseHash(HashMapList<int, Data> &LoadDataBase, const vector<Data> &ReferenceList) {
    int ConditionalCounter = 0;

    for (const auto &auxDataBase : ReferenceList) {
        // Genera una clave única para "competicion + equipo local + equipo visitante"
        int clave = GenerarClave(auxDataBase.competicion, auxDataBase.local, auxDataBase.visitante);

        // Insertar en el HashMapList usando la clave generada
        LoadDataBase.put(clave, auxDataBase);   // Inserta el partido bajo la clave combinada
        ConditionalCounter++; // Contador de condicionales (por cada inserción)
    }

    cout << "Base de datos cargada" << endl;
    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
}


void CargaVector(vector<Data> &ReferenceList) {
    int ConditionalCounter = 0; // Contador de condicionales
    string jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion;
    Data Parameters;

    string line;
    ifstream file("Base_Datos_COMA.csv");

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo " << endl;
        return;
    }

    getline(file, line); // Ignorar la primera fila del archivo CSV (supuestamente encabezados)
    
    while (getline(file, line)) {
        stringstream ss(line);

        // Extraer cada valor del registro CSV
        getline(ss, jornada, ',');
        getline(ss, fecha, ',');
        getline(ss, local, ',');
        getline(ss, golesLocal, ',');
        getline(ss, golesVisitante, ',');
        getline(ss, visitante, ',');
        getline(ss, competicion, ',');

        // Cargar los valores en el objeto Parameters y agregarlo al vector
        Parameters.Carga(jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion);
        ReferenceList.push_back(Parameters); // Agregar cada registro a la lista
        ConditionalCounter++; // Contador de registros cargados, no de condicionales en este caso
    }

    // Información de carga
    system("cls");
    cout << "Carga de la base de datos realizada, cantidad de registros: " << ConditionalCounter << endl;
    system("pause");
}


int GenerarClave(const string& competicion, const string& equipo1, const string& equipo2) {
    int clave = 0;
    const int prime = 31;  // Número primo para reducir colisiones

    // Ordenar los equipos alfabéticamente para que la clave sea la misma independientemente de quién sea local o visitante
    string equipoLocal = equipo1 < equipo2 ? equipo1 : equipo2;
    string equipoVisitante = equipo1 < equipo2 ? equipo2 : equipo1;

    // Concatenar competicion, equipoLocal, y equipoVisitante
    string combinacion = competicion + equipoLocal + equipoVisitante;

    // Generar clave hash
    for (char c : combinacion) {
        clave = prime * clave + static_cast<int>(c);  // Acumular usando un multiplicador primo
    }

    return clave;
}






























//calculos del punto 5
void Top5GoleadasQuickSort(vector<Data>& datos, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionCustom(datos, low, high);
        Top5GoleadasQuickSort(datos, low, pivotIndex - 1);
        Top5GoleadasQuickSort(datos, pivotIndex + 1, high);
    }
    
    for (int i = 0; i < 5; i++)
    {
        cout << datos[i].jornada << " " << datos[i].fecha << " " << datos[i].local << " " << datos[i].golesLocal << " " << datos[i].golesVisitante << " " << datos[i].visitante << " " << datos[i].competicion << endl; 
    }
}

int partitionCustom(vector<Data>& datos, int low, int high) {
    int pivotGolesLocal = stoi(datos[high].golesLocal);
    int pivotGolesVisitante = stoi(datos[high].golesVisitante);
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        int golesLocal = stoi(datos[j].golesLocal);
        int golesVisitante = stoi(datos[j].golesVisitante);

        if (golesLocal > pivotGolesLocal || (golesLocal == pivotGolesLocal && golesVisitante > pivotGolesVisitante)) {
            ++i;
            swap(datos[i], datos[j]);
        }
    }
    swap(datos[i + 1], datos[high]);
    return i + 1;
}

// bubblesort por si ya esta ordenado 

void Top5GoleadasBubbleSort(vector<Data>& datos) {
    bool swapped;
    int n = datos.size();

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            int golesLocal1 = stoi(datos[j].golesLocal);
            int golesVisitante1 = stoi(datos[j].golesVisitante);
            int golesLocal2 = stoi(datos[j + 1].golesLocal);
            int golesVisitante2 = stoi(datos[j + 1].golesVisitante);

            // Primero compara goles de local; si son iguales, usa goles de visitante
            if (golesLocal1 < golesLocal2 || (golesLocal1 == golesLocal2 && golesVisitante1 < golesVisitante2)) {
                swap(datos[j], datos[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Optimización si el vector ya está ordenado
    }

    for (int i = 0; i < 5; i++)
    {
        cout << datos[i].jornada << " " << datos[i].fecha << " " << datos[i].local << " " << datos[i].golesLocal << " " << datos[i].golesVisitante << " " << datos[i].visitante << " " << datos[i].competicion << endl; 
    }
    
}














void GolesTotales(vector<Data> PartidosJugados, string equipoASaber, string competicion)
{
    system("cls");
    int golesTotales = 0;
    int ConditionalCounter = 0;
    for (int i = 0; i < PartidosJugados.size(); i++)
    {
        ConditionalCounter++;
        if (PartidosJugados[i].local == equipoASaber)
        {
            golesTotales += stoi(PartidosJugados[i].golesLocal);
        }else
        {
            golesTotales += stoi(PartidosJugados[i].golesVisitante);   
        }
        ConditionalCounter++;
    }

    cout << "Goles totales de " << equipoASaber << " en " << competicion << ": " << golesTotales << endl;
    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
}

/*promedio goles*/

void PromedioGoles(vector<Data> PartidosJugados, string equipoASaber, string competicion)
{
    system("cls");
    int golesAfavor = 0;
    int golesEnContra =0;
    int ConditionalCounter = 0;
    for (int i = 0; i < PartidosJugados.size(); i++)
    {
        ConditionalCounter++;
        if (PartidosJugados[i].local == equipoASaber)
        {
            golesAfavor += stoi(PartidosJugados[i].golesLocal);
            golesEnContra += stoi(PartidosJugados[i].golesVisitante);
        }else
        {
            golesAfavor+= stoi(PartidosJugados[i].golesVisitante);
            golesEnContra += stoi(PartidosJugados[i].golesLocal);
        }
        ConditionalCounter++;
    }

    cout << "Promedio de goles de " << equipoASaber << " en " << competicion << " a favor: " << golesAfavor/PartidosJugados.size() << endl;
    cout << "Promedio de goles de " << equipoASaber << " en " << competicion << " en contra: " << golesEnContra/PartidosJugados.size() << endl;
    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
}










void CantidadDeDerrotas(vector<Data> PartidosJugados, string equipoASaber, string competicion)
{
    system("cls");
    int ConditionalCounter = 0;
    int cantidadDeDerrotas = 0;
    int CantidadDeTriunfos = 0;

    int golesAfavor, golesEnContra;
    for (int i = 0; i < PartidosJugados.size(); i++)
    {
        golesAfavor = 0;
        golesEnContra = 0;
        ConditionalCounter++;
        if (PartidosJugados[i].local == equipoASaber)
        {
            golesAfavor += stoi(PartidosJugados[i].golesLocal);
            golesEnContra += stoi(PartidosJugados[i].golesVisitante);
        }else
        {
            golesAfavor += stoi(PartidosJugados[i].golesVisitante);
            golesEnContra += stoi(PartidosJugados[i].golesLocal);         
        }
        ConditionalCounter++;
        if (golesAfavor > golesEnContra)
        {
            CantidadDeTriunfos++;
        }else{cantidadDeDerrotas++;}
        ConditionalCounter++;
    }

    cout << "Datos del " << equipoASaber << " en " << competicion << endl;
    cout << "Cantidad de triunfos " << CantidadDeTriunfos << endl;
    cout << "Cantidad de derrotas " << cantidadDeDerrotas << endl;
    cout << endl << "Cantidad de condicionales " << ConditionalCounter << endl;
    system("pause"); 
}

void FechaMaxMinGoles (vector<Data> PartidosJugados, string equipoASaber, string competicion)
{
    int ConditionalCounter = 0;
    int golesTotales = 0;
    int golesMaximos = 0;
    int golesMinimos = 1000;
    string fechaMaxima, fechaMinima;
    for (int i = 0; i < PartidosJugados.size(); i++)
    {
        if (PartidosJugados[i].competicion == competicion) 
        {
            ConditionalCounter++;
            golesTotales = 0; 

            if (PartidosJugados[i].local == equipoASaber) {
                // Sumar goles a favor y en contra cuando el equipo es local
                golesTotales += stoi(PartidosJugados[i].golesLocal);
            } else if (PartidosJugados[i].visitante == equipoASaber) {
                // Sumar goles a favor y en contra cuando el equipo es visitante
                golesTotales += stoi(PartidosJugados[i].golesVisitante);
            }


        if (golesTotales > golesMaximos)
        {
            golesMaximos = golesTotales;
            fechaMaxima = PartidosJugados[i].fecha;
        }
        if (golesTotales < golesMinimos)
        {
            golesMinimos = golesTotales;
            fechaMinima = PartidosJugados[i].fecha;
        }
        ConditionalCounter++;
    }

    cout << "Fecha con mas goles de " << equipoASaber << " en " << competicion << ": " << fechaMaxima << endl;
    cout << "Fecha con menos goles de " << equipoASaber << " en " << competicion << ": " << fechaMinima << endl;
    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
}
}




void CompeticionConMasYMenosGoles(const vector<Data>& Partidos)
{
    map<string, int> golesPorCompeticion;
    int ConditionalCounter = 0;

    // Acumular goles por competición en el map
    for (const auto& partido : Partidos) {
        ConditionalCounter++;

        // Sumar goles locales y visitantes usando stoi directamente
        golesPorCompeticion[partido.competicion] += stoi(partido.golesLocal) + stoi(partido.golesVisitante);
    }

    // Variables para almacenar la competición con más y menos goles
    string competicionConMasGoles, competicionConMenosGoles;
    int maxGoles = -1;
    int minGoles = INT_MAX;

    // Recorrer el map para encontrar las competiciones con el máximo y mínimo de goles
    for (const auto& entry : golesPorCompeticion) {
        ConditionalCounter++;
        
        if (entry.second > maxGoles) {
            maxGoles = entry.second;
            competicionConMasGoles = entry.first;
        }
        ConditionalCounter++;
        if (entry.second < minGoles) {
            minGoles = entry.second;
            competicionConMenosGoles = entry.first;
        }
        ConditionalCounter++;
    }

    // Imprimir resultados
    cout << "Competición con más goles: " << competicionConMasGoles << " con " << maxGoles << " goles." << endl;
    cout << "Competición con menos goles: " << competicionConMenosGoles << " con " << minGoles << " goles." << endl;
    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
}


void EquipoConMasYMenosGoles(const vector<Data>& Partidos)
{
    map<string, int> golesPorEquipo;
    int ConditionalCounter = 0;

    // Acumular goles por equipo en el map
    for (const auto& partido : Partidos) {
        ConditionalCounter++;

        // Sumar goles del equipo local
        golesPorEquipo[partido.local] += stoi(partido.golesLocal);

        // Sumar goles del equipo visitante
        golesPorEquipo[partido.visitante] += stoi(partido.golesVisitante);
    }

    // Variables para almacenar el equipo con más y menos goles
    string equipoConMasGoles, equipoConMenosGoles;
    int maxGoles = -1;
    int minGoles = INT_MAX;

    // Recorrer el map para encontrar los equipos con el máximo y mínimo de goles
    for (const auto& entry : golesPorEquipo) {
        ConditionalCounter++;
        
        if (entry.second > maxGoles) {
            maxGoles = entry.second;
            equipoConMasGoles = entry.first;
        }
        
        if (entry.second < minGoles) {
            minGoles = entry.second;
            equipoConMenosGoles = entry.first;
        }
    }

    // Imprimir resultados
    cout << "Equipo con más goles: " << equipoConMasGoles << " con " << maxGoles << " goles." << endl;
    cout << "Equipo con menos goles: " << equipoConMenosGoles << " con " << minGoles << " goles." << endl;
    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
}




 

























 //Modificacion de datos
void AgregarPartido(HashMapList<int, Data> &DataBase, vector<Data> &ReeferenceList) {
    system("cls");
    string jornada, fecha, Local, Visitante, golesLocal, golesVisitante, competicion;
    Data Parameter;
    cin.ignore();

    cout << "Ingrese la jornada: ";
    getline(cin, jornada);

    cout << "Ingrese la fecha: ";
    getline(cin, fecha);

    cout << "Ingrese el equipo local: ";
    getline(cin, Local);

    cout << "Ingrese los goles locales: ";
    getline(cin, golesLocal);

    cout << "Ingrese el equipo visitante: ";
    getline(cin, Visitante);

    cout << "Ingrese los goles visitantes: ";
    getline(cin, golesVisitante);

    cout << "Ingrese la competicion: ";
    getline(cin, competicion);

    Parameter.Carga(jornada, fecha, Local, golesLocal, golesVisitante, Visitante, competicion);
    int clave = GenerarClave(competicion, Local, Visitante);
    DataBase.put(clave, Parameter);
    ReeferenceList.push_back(Parameter);
    cout << "Partido Cargado " << endl;
    system("pause");
}


void EliminarPartido(HashMapList<int, Data> &DataBase) 
{
    system("cls");
    int ConditionalCounter = 0;
    string equipo1, equipo2, competicion, fecha;

    vector<Data> vectorAuxuiliar;
    

    cin.ignore();

    cout << "Ingrese el enfrentamiento concurrido en ese partido " << endl;
    cout << "Equipo 1: ";
    getline(cin, equipo1);
    cout << "Equipo 2: ";
    getline(cin, equipo2);
    cout << "Competicion: " << endl;
    getline(cin, competicion);

    int clave = GenerarClave(competicion, equipo1, equipo2);
    vectorAuxuiliar = DataBase.getDatosPorClave(clave);
    LeerDatosVector(vectorAuxuiliar);
    cout << endl;
    cout << "Ingrese la fecha del partido a modificar " << endl;
    getline(cin, fecha);

    for (int i = 0; i < vectorAuxuiliar.size(); i++)
    {
        ConditionalCounter++;
        if (vectorAuxuiliar[i].fecha == fecha)
        {
            vectorAuxuiliar.erase(vectorAuxuiliar.begin() + i);
            return;
        }
        ConditionalCounter++;
    }

    DataBase.remove(clave);
    for (int i = 0; i < vectorAuxuiliar.size(); i++)
    {
        ConditionalCounter++;
        DataBase.put(clave, vectorAuxuiliar[i]);
    }
    
    cout << "Partido eliminado" << endl;
    cout << "Cantidad de condicionales " << ConditionalCounter << endl;
}


void ModificarPartido(HashMapList<int, Data> &DataBase) {
    system("cls");
    int ConditionalCounter = 0;
    string equipo1, equipo2, competicion, fecha;

    vector<Data> vectorAuxiliar;
    cin.ignore();

    cout << "Ingrese el enfrentamiento concurrido en ese partido" << endl;
    cout << "Equipo 1: ";
    getline(cin, equipo1);
    cout << "Equipo 2: ";
    getline(cin, equipo2);
    cout << "Competicion: ";
    getline(cin, competicion);

    int clave = GenerarClave(competicion, equipo1, equipo2);
    vectorAuxiliar = DataBase.getDatosPorClave(clave);
    LeerDatosVector(vectorAuxiliar);

    cout << "Ingrese la fecha del partido a modificar: ";
    getline(cin, fecha);

    Data PartidoAModificar;
    bool encontrado = false;

    for (int i = 0; i < vectorAuxiliar.size(); i++) {
        ConditionalCounter++;
        if (vectorAuxiliar[i].fecha == fecha) {
            PartidoAModificar = vectorAuxiliar[i];
            vectorAuxiliar.erase(vectorAuxiliar.begin() + i);
            encontrado = true;
            break;
        }
        ConditionalCounter++;
    }
    ConditionalCounter++;
    if (!encontrado) {
        
        cout << "Partido no encontrado." << endl;
        system("pause");
        return;
    }

    int op;
    do {
        ConditionalCounter++;
        MenuDeModificaciones();
        cin >> op;
        cin.ignore();  
        cout << endl;
        switch (op) {
        case 1:
            cout << "Ingrese la nueva jornada: ";
            getline(cin, PartidoAModificar.jornada);
            break;
        case 2:
            cout << "Ingrese la nueva fecha: ";
            getline(cin, PartidoAModificar.fecha);
            break;
        case 3:
            cout << "Ingrese el nuevo equipo local: ";
            getline(cin, PartidoAModificar.local);
            break;
        case 4:
            cout << "Ingrese los nuevos goles locales: ";
            getline(cin, PartidoAModificar.golesLocal);
            break;
        case 5: 
            cout << "Ingrese los nuevos goles visitante: ";
            getline(cin, PartidoAModificar.golesVisitante);
            break;
        case 6:
            cout << "Ingrese el nuevo equipo visitante: ";
            getline(cin, PartidoAModificar.visitante);
            break;
        case 7:
            cout << "Ingrese la nueva competicion: ";
            getline(cin, PartidoAModificar.competicion);
            break;
        default:
            op = 0;
            break;
        }
        ConditionalCounter++;
    } while (op != 0);

    DataBase.remove(clave);
    for (const auto& partido : vectorAuxiliar) {
        ConditionalCounter++;
        DataBase.put(clave, partido);
    }
    
    clave = GenerarClave(PartidoAModificar.competicion, PartidoAModificar.local, PartidoAModificar.visitante);
    DataBase.put(clave, PartidoAModificar);

    cout << "Partido Modificado" << endl;
    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
}































// Función para comparar dos fechas en formato "dd/mm/yyyy"
bool CompararFechas(const string &fecha1, const string &fecha2, int &ContCond) {
    int dia1 = stoi(fecha1.substr(0, 2));
    int mes1 = stoi(fecha1.substr(3, 2));
    int anio1 = stoi(fecha1.substr(6, 4));

    int dia2 = stoi(fecha2.substr(0, 2));
    int mes2 = stoi(fecha2.substr(3, 2));
    int anio2 = stoi(fecha2.substr(6, 4));

    if (anio1 != anio2) {
        return anio1 < anio2;
    } else if (mes1 != mes2) {
        return mes1 < mes2;
    } else {
        return dia1 < dia2;
    }
}

// Función de partición para QuickSort
int Particion(vector<Data> &VectorAOrdenar, int low, int high, int &ContCond) {
    string pivot = VectorAOrdenar[high].fecha; // Elegir la última fecha como pivote
    int i = low - 1;

    for (int j = low; j < high; j++) {
        ContCond++;
        if (CompararFechas(VectorAOrdenar[j].fecha, pivot, ContCond)) {
            i++;
            swap(VectorAOrdenar[i], VectorAOrdenar[j]);
        }
        ContCond++;
    }
    swap(VectorAOrdenar[i + 1], VectorAOrdenar[high]);
    return i + 1;
}

// Implementación de QuickSort
void QuickSort(vector<Data> &VectorAOrdenar, int low, int high, int &ContCond) {
    ContCond++;
    if (low < high) {
        int pi = Particion(VectorAOrdenar, low, high, ContCond);

        // Ordenar recursivamente los elementos antes y después de la partición
        QuickSort(VectorAOrdenar, low, pi - 1, ContCond);
        QuickSort(VectorAOrdenar, pi + 1, high, ContCond);
    }
}

// Función principal que ordena el vector usando QuickSort
void OrdenadoPorFechas(vector<Data> &VectorAOrdenar, int &ContCond) {
    if (!VectorAOrdenar.empty()) {
        QuickSort(VectorAOrdenar, 0, VectorAOrdenar.size() - 1, ContCond);
    }
}







































void VerResultadosDelEquipo(HashMapList<int, Data> &DataBase, string equipo, string competicion, vector<string> &Equipos)
{
    system("cls");
    int ConditionalCounter = 0;
    vector<Data> VectorAuxiliar = ArmadoDelVector(DataBase, equipo, competicion, Equipos);
    OrdenadoPorFechas(VectorAuxiliar, ConditionalCounter);
    for (int i = 0; i < VectorAuxiliar.size(); i++)
    {
        ConditionalCounter++;
        cout << equipo << " " << VectorAuxiliar[i].fecha << " ";
        if (equipo == VectorAuxiliar[i].local || stoi(VectorAuxiliar[i].golesLocal) > stoi(VectorAuxiliar[i].golesVisitante))
        {
            cout << VectorAuxiliar[i].golesLocal << " " << VectorAuxiliar[i].golesVisitante << " Gano a " << VectorAuxiliar[i].visitante;
        }else
        {
            cout << VectorAuxiliar[i].golesLocal << " " << VectorAuxiliar[i].golesVisitante << "Perdio contra " << VectorAuxiliar[i].visitante;
        }
        ConditionalCounter++;
        cout << endl;
    }

    cout << endl << " Resultados mostrados " << endl;
    cout << "Cantidad de condicionales" << ConditionalCounter << endl;
    system("pause");

}

void ResultadoEntre2Fechas(HashMapList<int, Data> &DataBase, string equipo, vector<string> &Equipos)
{
    system("cls");
    string fechaDesde, fechaHasta;
    string competicion;
    bool entro = false;
    int ConditionalCounter = 0;


    cout << "Ingrese desde que fecha desea ver los datos: ";
    getline(cin, fechaDesde);
    cout << "Ingrese hasta que fecha desea ver los datos: ";
    getline(cin, fechaHasta);

    vector<Data> VectorAuxiliar, VectorMuestra;

    // Definir las competiciones y concatenar resultados de cada una en VectorMuestra
    vector<string> competiciones = {"Champions League", "LALIGA", "Premier League", "Bundesliga"};
    
    for (const string& comp : competiciones) {
        VectorAuxiliar = ArmadoDelVector(DataBase, equipo, comp, Equipos);
        VectorMuestra.insert(VectorMuestra.end(), VectorAuxiliar.begin(), VectorAuxiliar.end());
    }

    OrdenadoPorFechas(VectorMuestra, ConditionalCounter);

    for (int i = 0; i < VectorMuestra.size(); i++)
    {
        ConditionalCounter++;
        if (fechaDesde == VectorMuestra[i].fecha)
        {
            do
            {
            cout << equipo << " " << VectorMuestra[i].fecha << " ";
            if (equipo == VectorMuestra[i].local || stoi(VectorMuestra[i].golesLocal) > stoi(VectorMuestra[i].golesVisitante))
            {
                cout << VectorMuestra[i].golesLocal << " " << VectorMuestra[i].golesVisitante << " Gano a " << VectorMuestra[i].visitante << " en " << VectorMuestra[i].competicion;
            }else
            {
            cout << VectorMuestra[i].golesLocal << " " << VectorMuestra[i].golesVisitante << "Perdio contra " << VectorMuestra[i].visitante << " en " << VectorMuestra[i].competicion;
            }
            ConditionalCounter++;
            cout << endl;
            if (VectorMuestra[i+1].fecha == fechaHasta)
            {
                entro == false;
            }
            } while (entro == true);
            
        }
        

    }

    cout << "Datos mostrados " << endl;
    cout << "Condicionales usados " << ConditionalCounter << endl;
    system("pause");
}


void ComparacionDeRendimiento(HashMapList<int, Data> &DataBase, vector<string> &Equipos)
{
    int ConditionalCounter = 0;

    string equipo1, equipo2;
    vector<Data> VectorAuxiliarE1;
    vector<Data> VectorAuxiliarE2;

    cout << "Ingrese el primer equipo del que quiere saber los resultados " << endl;
    cin.ignore();
    getline(cin, equipo1);
    cout << "Ingrese el segundo equipo" << endl;
    getline(cin, equipo2);

    vector<string> competiciones = {"Champions League", "LALIGA", "Premier League", "Bundesliga"};
    int golesAFavor = 0;
    int golesEnContra = 0;

    for (string comp : competiciones) {
        ConditionalCounter++;
        
        // Procesar goles del primer equipo
        VectorAuxiliarE1 = ArmadoDelVector(DataBase, equipo1, comp, Equipos);
        for (const auto& partido : VectorAuxiliarE1)
        {
            ConditionalCounter++;
            if (equipo1 == partido.local)
            {
                golesAFavor += stoi(partido.golesLocal);
                golesEnContra += stoi(partido.golesVisitante);
            }
            else
            {
                golesAFavor += stoi(partido.golesVisitante);
                golesEnContra += stoi(partido.golesLocal);
            }
        }
        cout << equipo1 << " goles a favor: " << golesAFavor << " goles en contra: " << golesEnContra << " en " << comp << endl;
        
        golesAFavor = golesEnContra = 0; // Reiniciar contadores para el siguiente equipo

        // Procesar goles del segundo equipo
        VectorAuxiliarE2 = ArmadoDelVector(DataBase, equipo2, comp, Equipos);
        for (const auto& partido : VectorAuxiliarE2)
        {
            ConditionalCounter++;
            if (equipo2 == partido.local)
            {
                golesAFavor += stoi(partido.golesLocal);
                golesEnContra += stoi(partido.golesVisitante);
            }
            else
            {
                golesAFavor += stoi(partido.golesVisitante);
                golesEnContra += stoi(partido.golesLocal);
            }
        }
        cout << equipo2 << " goles a favor: " << golesAFavor << " goles en contra: " << golesEnContra << " en " << comp << endl;
        
        golesAFavor = golesEnContra = 0; // Reiniciar contadores para el siguiente equipo
    }

    cout << "\nDatos mostrados" << endl;
    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
}

void ComparacionSelectiva(HashMapList<int, Data> &DataBase)
{
    int ConditionalCounter = 0;
    string equipo1, equipo2;
    cout << "Ingrese el nombre del primer equipo " << endl;
    cin.ignore();
    getline(cin, equipo1);
    cout << "Ingrese le nomrbe del segundo equipo " << endl;
    getline(cin,equipo2);


    vector<string> competiciones = {"Champions League", "LALIGA", "Premier League", "Bundesliga"};
    vector<Data> VectorAuxiliar;
    int clave;
    int gano1 = 0;
    int gano2 = 0;
    int empate = 0;
    int Enfrentamientos = 0;
    for (string comp : competiciones)
    {
        ConditionalCounter++;
        clave = GenerarClave(comp, equipo1, equipo2);
        VectorAuxiliar = DataBase.getDatosPorClave(clave);
        for (int i = 0; i < VectorAuxiliar.size(); i++)
        {
            ConditionalCounter += 2;
            if (equipo1 == VectorAuxiliar[i].local and stoi(VectorAuxiliar[i].golesLocal) > stoi(VectorAuxiliar[i].golesVisitante))
            {
                gano1 += 1;
            }else if (stoi(VectorAuxiliar[i].golesLocal) == stoi(VectorAuxiliar[i].golesVisitante))
            {
                empate += 1;
            }
            else
            {
                gano2 += 1;
            }

            ConditionalCounter++;
            Enfrentamientos++;
        }
        
    }
    
    cout << "Calculos realizados" << endl;
    cout << equipo1 << "gano: " << gano1;
    cout << equipo2 << "gano: " << gano2;
    cout << "Empataron " << empate << " veces" << endl;
    cout << "Se enfrentaros: " << Enfrentamientos << " veces" << endl;

    cout << endl << "Cantidad de condicionales: " << ConditionalCounter;
    system("pause");

}




void FiltrarEquiposPorUmbral(const vector<Data>& ReferenceList, double umbral, bool esMayor) {
    map<string, map<string, pair<int, int>>> golesPorEquipoCompeticion; // {competicion: {equipo: {goles, partidos}}}
    int ConditionalCounter = 0;

    // Acumular goles y contar partidos por equipo y competición
    for (const auto& partido : ReferenceList) {
        ConditionalCounter++;
        string competicion = partido.competicion;

        // Equipo local
        golesPorEquipoCompeticion[competicion][partido.local].first += stoi(partido.golesLocal);
        golesPorEquipoCompeticion[competicion][partido.local].second++;

        // Equipo visitante
        golesPorEquipoCompeticion[competicion][partido.visitante].first += stoi(partido.golesVisitante);
        golesPorEquipoCompeticion[competicion][partido.visitante].second++;
    }

    // Filtrar y mostrar equipos según el umbral
    cout << "Equipos que cumplen con el umbral de goles por partido en promedio:\n";
    for (const auto& competicionEntry : golesPorEquipoCompeticion) {
        const string& competicion = competicionEntry.first;
        for (const auto& equipoEntry : competicionEntry.second) {
            ConditionalCounter++;
            const string& equipo = equipoEntry.first;
            int goles = equipoEntry.second.first;
            int partidos = equipoEntry.second.second;
            double promedio = static_cast<double>(goles) / partidos;

            if ((esMayor && promedio >= umbral) || (!esMayor && promedio <= umbral)) {
                cout << equipo << " " << promedio << " goles promedio por partido en " << competicion << endl;
            }
        }
    }

    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
}


