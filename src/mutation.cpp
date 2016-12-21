//
//  mutation.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/7/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include "mutation.hpp"

vector<Chromosome> mutation(double m_p,vector<Chromosome>& chro_population, map<string, vector<vector<Waypoint>>>& flightrouting, map<string, map<int, string>>& aircraft_speed)
{
	/*
	变异规则，当满足条件从相同机场对的备选航线中选取一条作为变异后航线。
	1、一条染色体变异只变异一个元素。
	*/
	vector<Chromosome> new_chro_population;
	for (auto it = chro_population.begin(); it != chro_population.end(); it++)
	{
		//        int rc =get_randnum()%10;
		//        if ((rc!=9)|(rc!=8)|(rc!=7))
		//        {
		//            new_chro_population.push_back(*it);
		//            continue;
		//        }
		Chromosome* chro_temp = new Chromosome();
		//chro_temp->set_copy_from_chro(it->code_chro, *it);
		*chro_temp = *it;
		new_chro_population.push_back(*chro_temp);
		delete chro_temp;
		for (auto ic = (*it).flightplan_list.begin(); ic != (*it).flightplan_list.end(); ic++)
		{
			int rd = get_randnum();//生成随机数
			long prob = rd % 100;
			if (prob < m_p * 100)
			{
				/*
				for (auto aa = ic->flightrouting.begin(); aa != ic->flightrouting.end(); aa++)
				{
					aa->print();
				}
				cout <<"变异前里程："<< ic->length<<endl;
				*/
				//开始变异
				if (flightrouting.find(((*ic).origination + "-" + (*ic).destination)) != flightrouting.end())
				{
					int rd = get_randnum() % flightrouting[(*ic).origination + "-" + (*ic).destination].size();
					//(*ic).set_copy_from_routing(flightrouting[(*ic).origination + "-" + (*ic).destination][rd]);
					ic->flightrouting = flightrouting[(*ic).origination + "-" + (*ic).destination][rd];
				}
				int rd = get_randnum() % 6;
				switch (rd)
				{
				case 0:
					ic->fly_level = 157;
					break;
				case 1:
					ic->fly_level = 217;
					break;
				case 2:
					ic->fly_level = 276;
					break;
				case 3:
					ic->fly_level = 291;
					break;
				case 4:
					ic->fly_level = 331;
					break;
				case 5:
					ic->fly_level = 60;
					break;
				default:
					break;
				}
				ic->set_speed(aircraft_speed);
				ic->set_length();
				ic->set_point_time();
				/*
				cout << endl;
				for (auto aa = ic->flightrouting.begin(); aa != ic->flightrouting.end(); aa++)
				{
					aa->print();
				}
				cout << "变异后里程：" << ic->length << endl;

				cout << endl;
				*/
			}

		}

		//        it -> chro_evaluation();
		new_chro_population.push_back(*it);
	}

	return new_chro_population;
}