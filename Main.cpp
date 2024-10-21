#include<iostream>
#include<fstream>
#include<sstream>
#include"GestorDeDatos.h"
#include"Hash/HashMapList.h"

// Cantidad de datos de la base = 7



using namespace std;

void Carga(HashMapList <int, Data> &DataBase)
{
    string jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion;
    ifstream Datos("Base_Datos_COMA.csv");
    string LineaDatos;
    Data datosPartidos;
    int clave;

    for (int i = 0; i < 500; i++)
    {
        clave = 0;
        stringstream ss(LineaDatos);
        string valor;
        getline(ss, valor, ',');
        jornada = valor;
        getline(ss, valor, ',');
        fecha = valor;
        getline(ss, valor, ',');
        local = valor;
        getline(ss, valor, ',');
        golesLocal = valor;
        getline(ss, valor, ',');
        golesVisitante = valor;
        getline(ss, valor, ',');
        visitante = valor;
        getline(ss, valor, ',');
        competicion = valor;
        
        datosPartidos.Carga(jornada, fecha, local, golesLocal, golesVisitante, visitante, competicion);
        
        /*
        tabla de valores ascii a tener en cuenta:
            0 = 48
            1 = 48 + 1
            2 = 48 + 2
            .
            9 = 48 + 9

            / = 47 
        */


       //funciones que pasan las palabras de la competicion y del equipo local 
        for (char c : datosPartidos.getCompeticion())
        {
            clave += static_cast<int>(c); 
        }

        for (char c : datosPartidos.getLocal())
        {
            clave += static_cast<int>(c);
        }
        
        DataBase.put(clave, datosPartidos);
        
    }
    
}



int main()
{
    Data Datos;
    HashMapList < int, Data> DataBase(9001);

    Carga(DataBase);

    DataBase.print();
    
}