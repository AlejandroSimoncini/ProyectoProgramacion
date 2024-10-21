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
    string getLocal();
    string getFecha();
    string getCompeticion();
    friend ostream& operator<<(ostream& cot, const Data& baseDatos);
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


string Data::getLocal()
{
    return local;
}

string Data::getFecha()
{
    return fecha;
}

string Data::getCompeticion()
{
    return competicion;
}



ostream &operator<<(ostream &cot, const Data &baseDatos)
{
    cot << baseDatos.local << " ";
    return cot;
}