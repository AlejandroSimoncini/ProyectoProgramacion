#include<iostream>
#include<vector>
#include<fstream>
#include<set>


#include"Funciones/Funciones.h"
#include"Hash/HashMapList.h"


using namespace std;







int main()
{
    HashMapList<int, Data> DataBase(9001); // HashMapList de la base de datos
    vector<Data> ReferenceList; // vector con el que se carga la lista 
    vector<string> Equipos;
    CargaVector(ReferenceList);
    CargaBaseHash(DataBase, ReferenceList);
    Equipos = ObtenerEquiposUnicos(ReferenceList);
    int ConditionalCounterTop5 = 0;
    Top5GoleadasQuickSort(ReferenceList, 0, ReferenceList.size() - 1, ConditionalCounterTop5);

    //Variables del menu
    
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
    {
        cout << "Cantidad de condicionales usados en los calculos: " << ConditionalCounterTop5;
        MostrarTop5Goleadas(ReferenceList);
        break;
    }

    case 2:
    {
        bool seguir = true;
        string team, competition;
        vector<Data> Partidos;
        int YesOrNO;
        int ConditionalCounter = 0;

        do
        {
            system("cls");
            ConditionalCounter++;
            cout << "Ingrese el equipo del que quiere ver los goles: ";
            cin.ignore();  // Ignorar el salto de línea en el buffer
            getline(cin, team);

            cout << "Ingrese de qué competicion quiere ver esos goles: ";
            getline(cin, competition);

            Partidos = ArmadoDelVector(DataBase, team, competition, Equipos);
            GolesTotales(Partidos, team, competition);

            cout << "¿Desea saber los datos de otro equipo?" << endl;
            cout << "1. Sí" << endl;

            cin >> YesOrNO;
            ConditionalCounter++;
            if (YesOrNO != 1)
            {
                seguir = false;
            }
        } while (seguir);
        
        cout << "Cantidad de condicionales usados: " << ConditionalCounter << endl;
        system("pause");
        break;
    }

    case 3:
    {
        bool seguir = true;
        string team, competition;
        vector<Data> Partidos;
        int YesOrNO;
        int ConditionalCounter = 0;

        do
        {
            system("cls");
            ConditionalCounter++;
            cout << "Ingrese el equipo del que quiere ver el promedio de goles: ";
            cin.ignore();  // Ignorar el salto de línea en el buffer
            getline(cin, team);

            cout << "Ingrese la competición: ";
            getline(cin, competition);

            Partidos = ArmadoDelVector(DataBase, team, competition, Equipos);
            PromedioGoles(Partidos, team, competition);

            cout << "¿Desea saber los datos de otro equipo?" << endl;
            cout << "1. Sí" << endl;

            cin >> YesOrNO;
            ConditionalCounter++;
            if (YesOrNO != 1)
            {
                seguir = false;
            }
        } while (seguir);

        cout << "Cantidad de condicionales usados: " << ConditionalCounter << endl;
        system("pause");
        break;
    }

    case 4:
    {
        bool seguir = true;
        string team, competition;
        vector<Data> Partidos;
        int YesOrNO;
        int ConditionalCounter = 0;

        do
        {
            system("cls");
            ConditionalCounter++;
            cout << "Ingrese el equipo del que quiere ver la cantidad de derrotas: ";
            cin.ignore();  // Ignorar el salto de línea en el buffer
            getline(cin, team);

            cout << "Ingrese de qué competición quiere ver las derrotas: ";
            getline(cin, competition);

            Partidos = ArmadoDelVector(DataBase, team, competition, Equipos);
            CantidadDeDerrotas(Partidos, team, competition);

            cout << "¿Desea saber los datos de otro equipo?" << endl;
            cout << "1. Sí" << endl;

            cin >> YesOrNO;
            ConditionalCounter++;
            if (YesOrNO != 1)
            {
                seguir = false;
            }
        } while (seguir);
        
        cout << "Cantidad de condicionales usados: " << ConditionalCounter << endl;
        system("pause");
        break;
    }

    case 5:
    {
        bool seguir = true;
        string team, competition;
        vector<Data> Partidos;
        int YesOrNO;
        int ConditionalCounter = 0;

        do 
        {
            system("cls");
            ConditionalCounter++;
            cout << "Ingrese el equipo del que quiere ver sus fechas con más y menos goles: ";
            cin.ignore();  // Ignorar el salto de línea en el buffer
            getline(cin, team); 

            cout << "Ingrese la competición: ";
            getline(cin, competition);

            Partidos = ArmadoDelVector(DataBase, team, competition, Equipos);
            FechaMaxMinGoles(Partidos, team, competition);

            cout << "¿Desea saber los datos de otro equipo?" << endl;
            cout << "1. Sí" << endl;

            cin >> YesOrNO;
            ConditionalCounter++;
            if (YesOrNO != 1)
            {
                seguir = false;
            }
        } while (seguir);

        cout << "Cantidad de condicionales usados: " << ConditionalCounter << endl;
        system("pause");
        break;
    }

    case 6:
    {
        system("cls");
        CompeticionConMasYMenosGoles(ReferenceList);
        break;
    }

    case 7:
    {
        system("cls");
        EquipoConMasYMenosGoles(ReferenceList);
        break;
    }
    case 8:
    {
        system("cls");
        int op;

        CambioDatos();
        cout << endl;
        cin >> op;
        switch (op)
        {
        case 1:
            AgregarPartido(DataBase, ReferenceList);
            break;
        case 2:
            EliminarPartido(DataBase);
            break;
        case 3:
            ModificarPartido(DataBase);
            break;
        default:
            break;
        }
    }
    break;
    case 9:
    {
        system("cls");
        int op;

        ConsultasDinamicas();
        cout << endl;
        cin >> op;
        switch (op)
        {
        case 1:
        {
            string equipo;
            string competicion;
            cin.ignore();
            cout << "Ingrese el equipo del que quiere ver los resultados " << endl;
            getline(cin, equipo);
            cout << "Ingrese la competicion en la que quiere ver los resultados " << endl;
            getline(cin, competicion);
        VerResultadosDelEquipo(DataBase, equipo, competicion, Equipos);
        }
            break;
        case 2:
            {
                string equipo;
                cin.ignore();
                cout << "Ingrese el equipo del que quiere ver los resultados " << endl;
                getline(cin, equipo);
                ResultadoEntre2Fechas(DataBase, equipo, Equipos);
            }
            break;
        case 3:
            system("cls");
            ComparacionDeRendimiento(DataBase, Equipos);
            break;
        case 4:
            system("cls");
            ComparacionSelectiva(DataBase);
            break;
        case 5:
            {
                system("cls");
                int umbral;
                bool SiNO;
                cout << "Ingrese el umbral " << endl;
                cin >> umbral;
                cout << "Quiere los equipos que estan por encima del umbral ?" << endl;
                cout << "1. Si" << endl;
                cout << "0. NO" << endl;
                cin >> SiNO;
                FiltrarEquiposPorUmbral(ReferenceList, umbral, SiNO);
            }
            break;
        default:
            break;
        }
    }
    break;
    default:
        cout << "Opción no válida. Intente nuevamente." << endl;
        break;
}
    } while (op != 0);
    

 

}