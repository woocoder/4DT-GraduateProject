//
//  env_set.hpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/9/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#ifndef env_set_hpp
#define env_set_hpp

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>
#include "Waypoint.hpp"
#include "util.hpp"
#include "Flightplan.hpp"
void env_set(map<string, vector<vector<Waypoint>>>* flightrouting, vector<Flightplan>* flightplan, map<string, map<int, string>>& aircraft_speed);

#endif /* env_set_hpp */

