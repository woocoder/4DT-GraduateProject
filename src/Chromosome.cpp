//
//  Chromosome.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/19/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include "Chromosome.hpp"



void Chromosome::set_conflict()
{
	/*
	冲突检测策略
	time_duration来做
	最大时间与最小时间有冲突
	目前使用norm速度来判断冲突
	*/
	map<string, vector<ptime>> waypoint_time;
	this->conflict_num = 0;
	seconds conflict_time_duration(30);
	//cout << "conflict_time_duration" <<conflict_time_duration<<endl;
	for (auto it = this->flightplan_list.begin(); it != this->flightplan_list.end(); it++)
	{
		for (auto ic = it->flightrouting.begin() + 1; ic != it->flightrouting.end() - 1; ic++)
		{   //首末两项是机场,使其中保持有序。
			//            cout << "ic->norm_time\n"<<ic->norm_time<<endl;
			if (ic->name == "") 
			{
				continue;
			}
			string temp_name = "";
			stringstream ss;
			ss << it->fly_level;
			ss >> temp_name;
			temp_name = temp_name + "-" + ic->name;
			if (waypoint_time.find(temp_name) == waypoint_time.end())
			{
				//如果map中没有航路点

				waypoint_time[temp_name].push_back(ic->norm_time);

			}
			else
			{
				//                cout << "ic->name\n"<<ic->name<<endl;
				//                cout << "ic->norm_time\n"<<ic->norm_time<<endl;
				//如果已有航路点
				//                cout << temp_name << endl;
				auto id = waypoint_time[temp_name].begin();
				//                cout << "id\n" <<*id<<endl;

				while ((id != waypoint_time[temp_name].end()) && (ic->norm_time >= (*id)))
				{
					//越过比norm_time小的点，使vector保持有序
					if (ic->norm_time - (*id) <= conflict_time_duration)
					{
						this->conflict_num++;
					}
					id++;
				}
				if (id != waypoint_time[temp_name].end())
				{
					auto ie = id;
					//                    cout << "\nie : \n" << *ie <<endl ;
					//                    cout << "\nic->normtime\n" << ic->norm_time <<endl;
					while ((ie != waypoint_time[temp_name].end()) && ((*ie) - (ic->norm_time) <= conflict_time_duration))
					{
						this->conflict_num++;
						ie++;
					}
				}
				waypoint_time[temp_name].insert(id, ic->norm_time);
			}
		}
	}
	//    //如输出则需设定断点，否则会多遍打印
	//    ofstream f_way_t_out("/Users/thinking/Developer/4dttest/4dttest/output/way_t_out");
	//    for (auto it = waypoint_time.cbegin(); it!= waypoint_time.cend(); it++)
	//    {
	//        f_way_t_out << "waypoint:\t" << it->first << endl;
	//        for (auto ic = it->second.begin(); ic != it->second.end(); ic++)
	//        {
	//            f_way_t_out << *ic << "\t";
	//        }
	//        f_way_t_out<<endl;
	//        
	//    }
	//cout << endl;
}

void Chromosome::set_flightplan_list(int code, vector<Flightplan>& flp_in)
{
	/*
	通过flightplan数组构造Chrommosome实例
	*/
	this->code_chro = code;
	for (auto it = flp_in.begin(); it != flp_in.end(); it++)
	{
		this->flightplan_list.push_back(*it);
	}
}

void Chromosome::set_copy_from_chro(int code, Chromosome chro_initial)
{
	this->evaluation = 0;
	this->flightplan_list.clear();
	this->code_chro = code;
	this->evaluation = chro_initial.evaluation;
	this->conflict_num = chro_initial.conflict_num;
	for (auto it = chro_initial.flightplan_list.begin(); it != chro_initial.flightplan_list.end(); it++)
	{
		Flightplan* a = new Flightplan();
		a->set_copy_from_flightplan(*it);
		this->flightplan_list.push_back(*a);
		delete a;
	}
}


vector<Chromosome> Chromosome::set_random_population(Chromosome chro_initial, map<string, vector<vector<Waypoint>>>* flightrouting, map<string, map<int, string>>& aircraft_speed)
{
	vector<Chromosome> chro_population;
	chro_population.push_back(chro_initial);
	int temp_delete_code = 0;
	for (auto ic = 1; ic <POPU_SIZE; ic++)
	{
		temp_delete_code += 1;
		//记得改写最大代数，用预编译处理
		vector<Flightplan> flp_list_temp;
		Chromosome* chro_individual = new Chromosome();
		for (auto it = chro_initial.flightplan_list.begin(); it != chro_initial.flightplan_list.end(); it++)
		{
			//            it->flp_print_to_cout();
			Flightplan* flp_temp = new Flightplan();
			flp_temp->set_copy_from_flightplan(*it);
			string key_airport = (*it).origination + "-" + (*it).destination;
			auto rd = get_randnum() % ((*flightrouting)[key_airport].size());
			/*
			提取相同机场对随机路径
			*/
			int rd_fl = get_randnum() % 5;
			switch (rd_fl) {
			case 0:
				it->fly_level = 157;
				break;
			case 1:
				it->fly_level = 217;
				break;
			case 2:
				it->fly_level = 276;
				break;
			case 3:
				it->fly_level = 291;
				break;
			case 4:
				it->fly_level = 331;
				break;
			default:
				break;
			}

			flp_temp->set_copy_from_routing((*flightrouting)[key_airport][rd]);
			//            flp_temp->flp_print_to_cout();
			flp_temp->set_speed(aircraft_speed);
			int rdt = (get_randnum() % 10) - 5;
			minutes m(rdt);
			flp_temp->take_off = flp_temp->take_off + m;
			flp_temp->set_point_time();
			//            flp_temp->flp_print_to_cout();
			flp_list_temp.push_back(*flp_temp);
			delete flp_temp;
		}

		chro_individual->code_chro = temp_delete_code;
		/*
		设置染色体航班计划
		*/
		chro_individual->set_flightplan_list(temp_delete_code, flp_list_temp);

		chro_population.push_back(*chro_individual);
		delete chro_individual;
	}

	return chro_population;
}
void Chromosome::chro_print_to_file(ofstream& f_out)
{
	f_out << "# " << code_chro << " : " << endl;
	f_out << "evaluation is " << evaluation << endl;
	for (auto it = flightplan_list.begin(); it != flightplan_list.end(); it++)
	{
		(*it).flp_print_to_file(f_out);
		f_out << endl;
	}
}

bool Chromosome::operator > (const Chromosome& a) const
{
	return this->evaluation > a.evaluation;
}
bool Chromosome::operator < (const Chromosome& a) const
{
	return this->evaluation < a.evaluation;
}

