//
//  initialize.hpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/7/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#ifndef initialize_hpp
#define initialize_hpp

#include <stdio.h>
#include <map>
#include "Chromosome.hpp"

vector<Chromosome> initialize(vector<Flightplan> &flp_initial, map<string, vector<vector<Waypoint>>> &flightrouting, map<string, map<int, string>>& aircraft_speed);
#endif /* initialize_hpp */


