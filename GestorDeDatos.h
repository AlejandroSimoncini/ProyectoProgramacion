#include<fstream>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;


class Data
{
public:
    string jornada;
    string fecha;
    string local;
    string golesLocal;
    string golesVisitante;
    string visitante;
    string competicion;

    Data();
    void Carga(string jornadaParam, string fechaParam, string localParam, string golesLocalParam, string golesVisitanteParam, string visitanteParam, string competicionParam);
    

};

Data::Data()
{
    jornada = " ";
    fecha = " ";
    local = " ";
    golesLocal = " ";
    golesVisitante = " ";
    visitante = " ";
    competicion = " ";
}


void Data::Carga(string jornadaParam, string fechaParam, string localParam, string golesLocalParam, string golesVisitanteParam, string visitanteParam, string competicionParam)
{
    jornada = jornadaParam;
    fecha = fechaParam;
    local = localParam;
    golesLocal = golesLocalParam;
    golesVisitante = golesVisitanteParam;
    visitante = visitanteParam;
    competicion = competicionParam;
}



