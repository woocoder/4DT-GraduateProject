//
//  initialize.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/7/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include "initialize.hpp"
//extern map<string, vector<vector<Waypoint>>> flightrouting;

vector<Chromosome> initialize(vector<Flightplan> &flp_initial, map<string, vector<vector<Waypoint>>> &flightrouting, map<string, map<int, string>>& aircraft_speed)
{
	/*
	individual initialization
	*/
	Chromosome* chro_initial = new Chromosome();
	chro_initial->set_flightplan_list(0, flp_initial);
	//chro_initial->chro_evaluation();
	ofstream f_chro_initial("output/chro_root_out.txt");

	chro_initial->chro_print_to_file_and_evaluation(f_chro_initial);
	/*
	population initialization
	*/
	f_chro_initial.close();
	//为未评估种群
	vector<Chromosome> chro_population = Chromosome::set_random_population(*chro_initial, &flightrouting, aircraft_speed);
	delete chro_initial;
	return chro_population;
}

