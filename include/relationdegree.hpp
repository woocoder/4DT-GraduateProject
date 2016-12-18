#ifndef relationdegree_hpp
#define relationdegree_hpp

#include <stdio.h>
#include "Chromosome.hpp"

vector<Chromosome> relationdegree(vector<Chromosome>& chro_population, map<string, vector<vector<Waypoint>>>&  flightrouting, map<string, map<int, string>>& aircraft_speed, bool thisActive);

#endif /* mutation_hpp */