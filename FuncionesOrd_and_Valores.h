#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

#include"GestorDeDatos.h"
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
