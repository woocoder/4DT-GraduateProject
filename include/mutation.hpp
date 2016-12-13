//
//  mutation.hpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/7/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#ifndef mutation_hpp
#define mutation_hpp

#include <stdio.h>
#include "Chromosome.hpp"

vector<Chromosome> mutation(double m_p, vector<Chromosome>& chro_population, map<string, vector<vector<Waypoint>>>&  flightrouting, map<string, map<int, string>>& aircraft_speed);

#endif /* mutation_hpp */
