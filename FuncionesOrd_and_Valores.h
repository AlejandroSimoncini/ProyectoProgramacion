#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


#include"Hash/HashMapList.h"
using namespace std;

int GenerateKey(string equipo, string competicion)
{
    int ConditionalCounter = 0;
    int key;
    for (char c : equipo)
    {
        key += c;
        ConditionalCounter++;
    }
    
    for (char c : competicion)
    {
        key += c;
        ConditionalCounter++;
    }

    cout << "Cantidad de condicionales: " << ConditionalCounter << endl;
    system("pause");
    system("cls");
    return key;
}

void ControlDeBase(int &ConditionalCounter, HashMapList<int, Data> &DataBase, string juegaDe, string fecha, string competicion, Data PartidoModificado)
{
    int key = GenerateKey(juegaDe, competicion);
    vector<Data> ListaDelEquipo = DataBase.getDatosPorClave(GenerateKey(juegaDe, competicion));

    for (int i = 0; i < ListaDelEquipo.size() ; i++)
    {
        ConditionalCounter++;
        if (ListaDelEquipo[i].fecha == fecha)
        {
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
    
    
    int LocalKey;
    int VisitorKey;

    for (char c : PartidoModificado.competicion)
    {
        LocalKey += c;
        VisitorKey += c;
    }
    for (char c : PartidoModificado.local)
    {
        LocalKey += c;
    }
    for (char c : PartidoModificado.visitante)
    {
        VisitorKey +=c;
    }
    
    DataBase.put(LocalKey, PartidoModificado);
    DataBase.put(VisitorKey, PartidoModificado);
}



void EliminarContrario(HashMapList<int, Data> &DataBase, string juegaDe, string competicion, string fecha, int &ConditonalCounter)
{
    int key = GenerateKey(juegaDe, competicion);
    vector<Data> ListaDeLEquipo = DataBase.getDatosPorClave(key);

    for (int i = 0; i < ListaDeLEquipo.size(); i++)
    {
        ConditonalCounter++;
        if (ListaDeLEquipo[i].fecha == fecha)
        {
            ListaDeLEquipo.erase(ListaDeLEquipo.begin() + i);
        }
        ConditonalCounter++;
    }
    
    DataBase.remove(key);
    for (int i = 0; i < ListaDeLEquipo.size(); i++)
    {
        DataBase.put(key, ListaDeLEquipo[i]);
    }
    
}











void ComparacionRendimientoEquiposParticular(HashMapList<int, Data>& DataBase)
{
    system("cls");
    int ConditionalCounter = 0;
    string equipo1, equipo2;
    string competicion1, competicion2;
    cout << endl << "Ingrese el nombre del primer equipo: ";
    getline(cin, equipo1);
    cout << endl <<"Ingrese la competicion en la que jugo: ";
    getline(cin, competicion1);
    cout << endl <<"Ingrese el nombre del segundo equipo: ";
    getline(cin, equipo2);

    int key1 = GenerateKey(equipo1, competicion1);
    int key2 = GenerateKey(equipo2, competicion2);
    vector<Data> ListaEnfrentamiento = DataBase.getDatosPorClave(key1);
 

    int golesAfavorEquipo1;
    int golesAfavorEquipo2;

    for (int i = 0; i < ListaEnfrentamiento.size(); i++)
    {
        ConditionalCounter++;
        if (ListaEnfrentamiento[i].visitante == equipo2 || ListaEnfrentamiento[i].local == equipo2)
        {
            if (ListaEnfrentamiento[i].local == equipo1)
            {
                for (char c : ListaEnfrentamiento[i].golesLocal)
                {
                    ConditionalCounter++;
                    if (c != '(' || c != ')')
                    {
                        golesAfavorEquipo1 += c - '0';
                    }
                }
                for (char c : ListaEnfrentamiento[i].golesVisitante)
                {
                    ConditionalCounter++;
                    if (c != '(' || c != ')')
                    {
                        golesAfavorEquipo2 += c - '0';
                    }
                }
            }else{
                for (char c : ListaEnfrentamiento[i].golesVisitante)
                {
                    ConditionalCounter++;
                    if (c != '(' || c != ')')
                    {
                        golesAfavorEquipo1 += c - '0';
                    }
                }
                for (char c : ListaEnfrentamiento[i].golesLocal)
                {
                    ConditionalCounter++;
                    if (c != '(' || c != ')')
                    {
                        golesAfavorEquipo2 += c - '0';
                    }
                    
                }
            }
            
        }



        ConditionalCounter++;
    }
    
    cout << endl << "Goles a favor de " << equipo1 << ": " << golesAfavorEquipo1 << endl;
    cout << "Goles a favor de " << equipo2 << ": " << golesAfavorEquipo2 << endl;
    cout << endl << "Condicionales usados: " << ConditionalCounter << endl; 
}