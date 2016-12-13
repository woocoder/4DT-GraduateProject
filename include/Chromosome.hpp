//
//  Chromosome.hpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/19/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#ifndef Chromosome_hpp
#define Chromosome_hpp

#include <stdio.h>
#include "Flightplan.hpp"
#include "evaluation.hpp"
#include "util.hpp"
#define POPU_SIZE 50

class Chromosome
{
public:
	int code_chro, conflict_num;
	vector<Flightplan> flightplan_list;
	double evaluation;

	void set_conflict();
	void set_flightplan_list(int code, vector <Flightplan>& flp_in);
	void set_copy_from_chro(int code, Chromosome chro_initial);

	void chro_print_to_file(ofstream& f_out);
	static vector<Chromosome> set_random_population(Chromosome chro_initial, map<string, vector<vector<Waypoint>>>* flightrouting, map<string, map<int, string>>& aircraft_speed);
	void chro_evaluation();
	void chro_penalty();
	void chro_print_to_file_and_evaluation(ofstream& f_out);
	bool operator > (const Chromosome& a) const;
	bool operator < (const Chromosome& a) const;


};


#endif /* Chromosome_hpp */

