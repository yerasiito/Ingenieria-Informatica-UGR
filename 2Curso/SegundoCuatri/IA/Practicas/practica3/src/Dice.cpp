# include "Dice.h"

#include <iostream>
#include <algorithm>


Dice::Dice(){
    //Asigna por defecto los 6 valores del dado a cada jugador.
    this->dice =  map <color, vector <vector<int> >> {
        {color::red,    {{1,2,3,4,5,6}}},
        {color::blue,   {{1,2,3,4,5,6}}},
        {color::yellow, {{1,2,3,4,5,6}}},
        {color::green,  {{1,2,3,4,5,6}}}
    };
};

Dice::Dice (const map <color, vector<vector <int> >> & d){
    this->dice =  map <color, vector<vector <int> >>(d);
};

const vector<int> & Dice::getDice (color player) const{
    return dice.at(player).at(dice.at(player).size()-1);
}

const vector<vector<int>> & Dice::getAllDiceLayers(color player) const{
    return dice.at(player);
}

const int Dice::getLayersSize(color player) const{
    return dice.at(player).size();
}

void Dice::removeNumber (color player, int n){
    //Se elimnina n del vector de valores asociado al dado de player.
    dice[player][dice[player].size() - 1].erase(remove(dice[player][dice[player].size() - 1].begin(), dice[player][dice[player].size() - 1].end(), n), dice[player][dice[player].size() - 1].end());
    //Si se han gastado todos los números, se regenera de nuevo el dado.
    if (dice[player][dice[player].size() - 1].empty())
    {
        if(dice[player].size() == 1)
            resetDice(player);
        else
            dice[player].pop_back();
        
    }
}

void Dice::resetDice (color player , const vector<int> & new_dice){
    dice[player][dice[player].size() - 1] = new_dice;
}

bool Dice::isAvailable(color player, int n) const{
    vector<int> player_dice = dice.at(player).at(dice.at(player).size()-1);
    return (find(player_dice.begin(), player_dice.end(), n) != player_dice.end());
}

void Dice::addNumber(color player, int n){
    dice[player][dice[player].size() - 1].push_back(n);
}

void Dice::forceNumber(color player, int n){
    dice[player].push_back({n});
}

