//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    char tipo_cota_inf, coma_sep, tipo_cota_sup;
    double cota_inf,cota_sup;
    double valor;
    bool intervalo;

    //entrada de datos...
    cout <<"Introduce un intervalo: ";
    cin >> tipo_cota_inf >> cota_inf >> coma_sep >> cota_sup >> tipo_cota_sup;
    cout <<"Introduce un valor: ";
    cin >> valor;

    //proceso de datos...

    if(valor==cota_inf && tipo_cota_inf=='[')
        intervalo=true;
    else if(valor==cota_sup && tipo_cota_sup==']')
        intervalo=true;
    else if(valor>cota_inf && valor<cota_sup)
        intervalo=true;
    else
        intervalo=false;

    //Salida de datos...

    if(intervalo)
        cout << "El valor " << valor << " esta dentro del intervalo " << tipo_cota_inf << cota_inf << coma_sep << cota_sup << tipo_cota_sup << endl;
    else
        cout << "El valor " << valor << " NO esta dentro del intervalo " << tipo_cota_inf << cota_inf << coma_sep << cota_sup << tipo_cota_sup << endl;

}

