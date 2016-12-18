//
//  Flightplan.hpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/19/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#ifndef Flightplan_hpp
#define Flightplan_hpp

#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Waypoint.hpp"
using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class Flightplan
{
public:
	string aircraft, origination, destination;
	ptime take_off;
	ptime land;
	string aircraft_type;
	int fly_level;
	int relationdegree;
	double norm_speed, min_speed, max_speed;
	vector<Waypoint> flightrouting;
	double length;


	void set_length();
	void flp_print_to_file(ofstream& f_out);
	void set_copy_from_routing(vector<Waypoint> a);
	void set_copy_from_flightplan(Flightplan flp);
	//Flightplan& operator = (const Flightplan a);
	void set_speed(map<string, map<int, string>> aircraft_speed);
	void set_point_time();
	void flp_print_to_cout();
	string get_routing();


};
#endif /* Flightplan_hpp */
