﻿//
//  main.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/7/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include <iostream>
#include "initialize.hpp"
#include <string>
#include "env_set.hpp"
#include "selection.hpp"
#include "crossover.hpp"
#include "mutation.hpp"
#include "relationdegree.hpp"
#include <random>
#define GENERATION 50

using namespace std;

int main()
{

	map<string, vector<vector<Waypoint>>> flightrouting;
	vector <Flightplan> flightplan;
	map<string, map<int, string>> aircraft_speed;

	env_set(&flightrouting, &flightplan, aircraft_speed);
	cout << flightplan[1].take_off << "\t" << flightplan[2].land << endl;
	cout << "初始化开始****************************" << endl;
	
		double c_p = 0.3, m_p = 0.05;
		bool thisActive = true;
		int k=40;
		int test = 0;
		cout << "\nk值为" << k <<endl;
		/*交叉变异概率计算代码
		switch(ij)
		{
			case 0:
				c_p = 0.6;
				m_p = 0.01;
				break;
			case 1:
				c_p = 0.6;
				m_p = 0.03;
				break;
			case 2:
				c_p = 0.6;
				m_p = 0.06;
				break;
			case 3:
				c_p = 0.7;
				m_p = 0.01;
				break;
			case 4:
				c_p = 0.7;
				m_p = 0.03;
				break;
			case 5:
				c_p = 0.7;
				m_p = 0.06;
				break;
			case 6:
				c_p = 0.8;
				m_p = 0.01;
				break;
			case 7:
				c_p = 0.8;
				m_p = 0.03;
				break;
			case 8:
				c_p = 0.8;
				m_p = 0.06;
				break;
			default:
				break;
		}*/

		for (int ii = 0; ii != 10; ii++)
		{
			vector<Chromosome> chro_population = initialize(flightplan, flightrouting, aircraft_speed);
			//为优化速度，评估功能在写入之前进行
			cout << "初始化结束****************************" << endl;
			cout << "初始染色体写入开始****************************" << endl;
			//ofstream f_chro("/Users/thinking/Developer/4dttest/4dttest/output/chro_initial_out.txt");
			double initial_goal = 0;
			cout << "评估开始****************************" << endl;
			for (auto it = chro_population.begin(); it != chro_population.end(); it++)
			{
				if (it == chro_population.begin())
				{
					initial_goal = it->evaluation;
					continue;
				}
				//cout << "第"<<it->code_chro << "条评估开始" << endl;
				(*it).chro_evaluation();
				initial_goal += it->evaluation;
				//(*it).chro_print_to_file(f_chro);

			}
			cout << "评估结束****************************" << endl;
			cout << "初始染色体写入结束****************************" << endl;

			/*
			GA
			*/

			vector<Chromosome> chro_crossovered_population;
			vector<Chromosome> chro_mutated_population;
			vector<Chromosome> chro_related_population;
			string temp_1;
			stringstream s_temp1,s_temp2, s_temp3, s_temp4;
			string ks,iis,actives,cps,mps;
			s_temp1 << k;
			s_temp1 >> ks;
			s_temp3 << ii;
			s_temp3 >> iis;
			s_temp2 << c_p;
			s_temp2 >> cps;
			s_temp4 << m_p;
			s_temp4 >> mps;

			if (thisActive == true)
				actives = "true";
			else
				actives = "false";
			temp_1 = "output/A_"+ actives+"_c"+cps+"_m"+mps +"_k" + ks +"_"+iis;
			ofstream f_chro_result(temp_1 + "_out.txt");
			Chromosome* it_f = new Chromosome();
			for (int i = 0; i != GENERATION; i++)
			{
				if (i != 0)
				{
					chro_population.clear();
					//vector<Chromosome>(chro_population).swap(chro_population);

					//for (auto it = chro_mutated_population.begin(); it != chro_mutated_population.end(); it++)
					//{
						//chro_population.push_back(*it);
					//}
					chro_population = chro_related_population;
					chro_related_population.clear();
					chro_crossovered_population.clear();
					//vector<Chromosome>(chro_mutated_population).swap(chro_mutated_population);
					//vector<Chromosome>(chro_crossovered_population).swap(chro_crossovered_population);

				}

				cout << "第" << i + 1 << "代计算<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
				cout << "\n初始种群大小\n" << chro_population.size() << "初始种群得分" << initial_goal / chro_population.size() << endl;
				cout << "选择开始****************************" << endl;
				vector<Chromosome> Chro_new_population = selection(chro_population);
				chro_population.clear();
				//vector<Chromosome>(chro_population).swap(chro_population);
				//释放初始种群

				//        chro_population.clear();
				//        vector<Chromosome>(chro_population).swap(chro_population);
				cout << Chro_new_population.size() << endl;
				cout << "选择结束****************************" << endl;
				stringstream s_temp;
				string s;
				s_temp << i;
				s_temp >> s;
				//        ofstream f_chro_s("/Users/thinking/Developer/4dttest/4dttest/output/chro_seleted_"+s+"_out.txt");
				//        for (auto it = Chro_new_population.begin(); it != Chro_new_population.end(); it++)
				//        {
				//            (*it).chro_evaluation();
				//        }
				cout << "交叉开始****************************" << endl;

				vector<Chromosome> temp_chro_cro = crossover(k,c_p,Chro_new_population);
				Chro_new_population.clear();
				//vector<Chromosome>(Chro_new_population).swap(Chro_new_population);
				for (auto it = temp_chro_cro.begin(); it != temp_chro_cro.end(); it++)
				{
					chro_crossovered_population.push_back(*it);
				}
				temp_chro_cro.clear();
				//vector<Chromosome>(temp_chro_cro).swap(temp_chro_cro);
				if (chro_crossovered_population.size() == 0)
				{
					exit(1);
				}
				cout << chro_crossovered_population.size() << endl;
				cout << "交叉结束****************************" << endl;
				//        ofstream f_chro_c("/Users/thinking/Developer/4dttest/4dttest/output/chro_crossovered"+s+"_out.txt");
				//        for (auto it = chro_crossovered_population.begin(); it != chro_crossovered_population.end(); it++)
				//        {
				//            //cout << "第"<<it->code_chro << "条评估开始" << endl;
				//            (*it).chro_evaluation();
				//            cout << it->evaluation<<endl;
				//        }
				//        sort(chro_mutated_population.begin(), chro_mutated_population.end(),less<Chromosome>());
				cout << "变异开始****************************" << endl;
				chro_mutated_population = mutation(m_p,chro_crossovered_population, flightrouting, aircraft_speed);
				chro_crossovered_population.clear();
				//vector<Chromosome>(chro_crossovered_population).swap(chro_crossovered_population);
				cout << chro_mutated_population.size() << endl;
				cout << "变异结束****************************" << endl;
				cout << "终极染色体写入开始****************************" << endl;
				//        ofstream f_chro_m("/Users/thinking/Developer/4dttest/4dttest/output/chro_result"+s+"_out.txt");
				cout << chro_mutated_population.size() << endl;
				double final_goal = 0;
				for (auto it = chro_mutated_population.begin(); it != chro_mutated_population.end(); it++)
				{
					//cout << "第"<<it->code_chro << "条评估开始" << endl;
					(*it).chro_evaluation();
					final_goal += it->evaluation;
				}
				cout << "\n终极种群大小\n" << chro_mutated_population.size() << "交叉种群得分" << final_goal / chro_mutated_population.size() << endl;
				initial_goal = final_goal;

				chro_related_population = relationdegree(chro_mutated_population, flightrouting, aircraft_speed,thisActive);

				chro_mutated_population.clear();
				final_goal = 0;
				for (auto it = chro_related_population.begin(); it != chro_related_population.end(); it++)
				{
					(*it).chro_evaluation();
					final_goal += it->evaluation;
				}
				cout << "\n航班相关性种群大小\n" << chro_related_population.size() << "相关种群得分" 
					<< final_goal / chro_related_population.size() << endl;

				//        f_chro_result.close();

				sort(chro_related_population.begin(), chro_related_population.end(), less<Chromosome>());
				auto ic = chro_related_population.begin();
				/*
				for (auto it = chro_related_population.begin(); it != chro_related_population.end(); it++) {
					cout << it->evaluation << endl;
				}*/

				//f_chro_result<<"#第"<<s<<"代染色体适应度函数值\n"<<
				f_chro_result << ic->evaluation << endl;
				cout << "最后染色体" << ic->evaluation << endl;
				it_f = &(*ic);
			}
			f_chro_result.close();
			ofstream f_chro_airtop_routing(temp_1 +"_airtop_routing.txt");
			ofstream f_chro_airtop_flp(temp_1+"_airtop_flp.txt");
			ofstream f_chro_airtop_tc(temp_1+"_airtop_tc.txt");


			cout << "airtop输入文件写入开始" << endl;

			for (auto it = it_f->flightplan_list.begin(); it != it_f->flightplan_list.end(); it++)
			{
				stringstream s;
				s << it->fly_level;

				string routing = "", flp = "", fl;
				s >> fl;
				routing = it->get_routing();
				flp = "true;" + it->aircraft + ";SHORT;AC#" + it->aircraft.substr(3, it->aircraft.length() - 1) + ";AirCarrier;;Departure;;1 " + to_simple_string(it->take_off.time_of_day()) + ";FixedVariation;;;;" + it->origination + ";" + it->destination + ";;;;;;" + it->aircraft.substr(3, it->aircraft.length() - 1) + ";" + "FL" + fl + ";;;";
				f_chro_airtop_flp << flp << endl;
				f_chro_airtop_routing << it->aircraft.substr(3, it->aircraft.length() - 1) << ";" << routing << ";" << endl;

				f_chro_airtop_tc << "true;TC#" + it->aircraft.substr(3, it->aircraft.length() - 1) + ";true;;01:00:00;;true;#FP" + it->aircraft.substr(3, it->aircraft.length() - 1) + ";#FP" + it->aircraft.substr(3, it->aircraft.length() - 1) + ";;;Airport " + it->origination + ";;1 " + to_simple_string(it->land.time_of_day()) + ";00:02:00;00:03:00;;false;;0.0;;;;;;0.0;true\t" + "TRUE\ttrue;TTO;Manual;;Creation;false;;Distance;30NM;;None;5NM;5NM;false;;;;;0;;;;;Arrival;;;" << endl;
			}

			f_chro_airtop_routing.close();
			f_chro_airtop_flp.close();
			f_chro_airtop_tc.close();

			cout << "airtop输入文件写入结束" << endl;
		}




	return 0;
}
