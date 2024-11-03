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