#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

vector<vector<int>> M;

void ImprimeVector(vector<int> v){
    cout << endl;
    for(int i = 0; i <  v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

void ImprimeMatriz(vector<vector<int>> Matrix){
    cout << "\n\nLa matriz es: ";
    for(int i = 0; i < Matrix.size(); i++){
        cout << endl;
        for(int j = 0; j < Matrix[i].size(); j++)
            cout << Matrix[i][j] << " ";
    }
    cout << endl;
}

int main(int argc, char** argv) {
   string line;
   
   //Lee el archivo pasado por parámetro
   ifstream f(argv[1]);
   
   getline(f, line); //Cogemos la primera linea y la imprimimos
   //cout << line;
   
   while (std::getline(f, line)) //Lee la matriz
   {
        std::istringstream iss(line);
        M.emplace_back(std::istream_iterator<int>(iss),
                                 std::istream_iterator<int>());
   }
   
   ImprimeMatriz(M);
}