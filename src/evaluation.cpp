//
//  evaluation.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/20/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include "evaluation.hpp"


void Chromosome::chro_penalty()
{
	this->set_conflict();
	//    if ((this->conflict_num)/8530 > 1)
	//    {
	//        this -> evaluation =this -> evaluation + this->conflict_num;
	//    }
	this->evaluation = this->evaluation + 2 * this->conflict_num;
}

void Chromosome::chro_evaluation()
{
	this->evaluation = 0;
	double total_dalay_m = 0;
	for (auto it = this->flightplan_list.begin(); it != this->flightplan_list.end(); it++)
	{

		/*
		计算染色体中每个航班的里程数，除以航空器速度，加上起飞时间，所得值超出计划到达时间的部分，视作延误
		*/
		seconds norm_time(3600 * (*it).length / (*it).norm_speed);
		seconds min_time(3600 * (*it).length / (*it).max_speed);
		seconds max_time(3600 * (*it).length / (*it).min_speed);
		//cout << norm_time << "\t" << min_time << "\t" << max_time << endl;
 		ptime min_real_land = (*it).take_off + min_time;
		//cout << min_real_land << endl;
		if (min_real_land>(*it).land)
		{
			time_duration delay = min_real_land - (*it).land;
			total_dalay_m += delay.total_seconds() / 60;
			//cout << delay << "\t"  << delay.total_seconds() << "\t" << total_dalay_m << endl;
		}
				
	}
	this->evaluation = (total_dalay_m);
	this->chro_penalty();
}

void Chromosome::chro_print_to_file_and_evaluation(ofstream& f_out)
{
	this->evaluation = 0;
	double total_dalay_m = 0;
	f_out << "# 第" << code_chro << "条染色体" << " : " << endl;
	for (auto it = flightplan_list.begin(); it != flightplan_list.end(); it++)
	{
		seconds norm_time(3600 * (*it).length / (*it).norm_speed);
		seconds min_time(3600 * (*it).length / (*it).max_speed);
		seconds max_time(3600 * (*it).length / (*it).min_speed);

		ptime min_real_land = (*it).take_off + min_time;
		if (min_real_land>(*it).land)
		{
			time_duration delay = min_real_land - (*it).land;
			total_dalay_m += delay.total_seconds() / 60;
		}
		(*it).flp_print_to_file(f_out);
		f_out << endl;
	}
	this->evaluation = (total_dalay_m);
	f_out << "evaluation is " << evaluation << endl;
	this->chro_penalty();
	f_out << "conflict_num is " << conflict_num << endl;
	f_out << "new_evaluation:\t" << this->evaluation << endl;
}