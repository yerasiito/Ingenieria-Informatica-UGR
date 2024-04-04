/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   greedyTiempos.cpp
 * Author: yerasito
 *
 * Created on 28 de abril de 2022, 0:20
 */

#include <cstdlib>
#include <iostream>
#include "greedy.cpp"

using namespace std;

int n;
vector<vector<int>> c;
vector<int> a;
/*
 * 
 */
int main(int argc, char** argv) {
    cin >> n;
    a.resize(n);
    c.resize(n, vector<int>(n));
    
    greedy();
    
    return 0;
}

