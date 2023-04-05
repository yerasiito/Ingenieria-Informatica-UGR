#include <iostream>
#include <vector>
// From https://github.com/effolkronium/random
#include "random.hpp"

using namespace std;

int fact(int n);

// get base random alias which is auto seeded and has static API and internal state
// it is not threads secure, you can also use ::random_thread_local
using Random = effolkronium::random_static;

int main(int argc, char **argv) {
  long int seed;

  if (argc <= 1) {
    cout <<"Not setting seed" <<endl;
  }
  else {
    seed = atoi(argv[1]);
    Random::seed(seed);
    cout <<"Using seed: " <<seed <<endl;
  }

  cout <<"Entero entre 1 y 10: " <<Random::get(1, 10) <<endl;
  cout <<"Entero unsigned entre 1 y 10: " <<Random::get<unsigned>(1, 10) <<endl;
  cout <<"Real entre 0 y 1: " <<Random::get(0.0, 1.0) <<endl;
  cout <<"Real entre 1.0 y 5.0: " <<Random::get(1.0, 5.0) <<endl;
  cout <<"Booleano1: " <<Random::get<bool>() <<endl;
  cout <<"Booleano2: " <<Random::get<bool>() <<endl;
  double p = 0.2;

  for (int i = 0; i < 10; i++) {
    cout <<"Booleano con probability " <<p <<" " <<Random::get<bool>(p) <<endl;
  }

  const auto print = [](auto &e){ cout <<" " <<e; };
  vector<int> values = {1, 3, 10, 5, 8};
  cout <<"values: [";
  for_each(values.begin(), values.end(), print);
  cout <<" ]" <<endl;
  Random::shuffle(values);
  cout <<"shuffle values: [";
  for_each(values.begin(), values.end(), print);
  cout <<" ]" <<endl;
  Random::shuffle(values);
  cout <<"shuffled again : [";
  for_each(values.begin(), values.end(), print);
  cout <<" ]" <<endl;

  // Using a normal distribution
  std::normal_distribution<double> distribution(0.0, sqrt(0.5));

  for (int i = 0; i < 10; i++) {
    cout <<"Normal distribution: " <<Random::get(distribution) <<endl;
  }

  // Escoge de una tirada n elementos (con repetición)
  vector<int> varios = Random::get<std::vector>(10, 30, 10);
  cout <<"Varios (con repetición): ";

  for (unsigned i = 0; i < varios.size(); i++) {
    cout <<varios[i] <<", ";
  }

  cout <<endl;
  return 0;
}
