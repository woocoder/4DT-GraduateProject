//
//  crossover.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/7/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include "crossover.hpp"



vector<Chromosome> crossover(int k,double c_p ,vector<Chromosome>& chro_population)
{
	/*
	交叉范围：每条染色体只与排名相差五位中随机一条染色体进行交叉
	交叉规则：染色体中，元素互换
	1、性能提高：只能与相邻个体交叉或者动态选择
	2、时间控制：通过整个航班交换实现，设置时间控制裕度
	3、交叉策略：
	-> 单点交叉
	-> 均匀交叉：掩码、不用保留父代（待定）
	*/
	int base_code = 10000;
	vector<Chromosome> chro_crossovered_population;
	/*
	决定交叉范围
	*/
	if (chro_population.size() <= 1)
	{
		cout << " 种群数为空" << endl;
		return chro_population;
	}
	int size = (int)chro_population.size();
	int total_evaluation = 0, average_evaluation = 0, max_evaluation = 0;
	for (auto it = chro_population.begin(); it != chro_population.end(); it++)
	{
		if (it->evaluation>max_evaluation)
		{
			max_evaluation = it->evaluation;
		}
		total_evaluation += it->evaluation;
	}
	average_evaluation = total_evaluation / size;
	//double control_index = 2; // 控制最大值与平均值的差值影响
	//double temp = 1 / (((double)max_evaluation - (double)average_evaluation)*control_index + 1);
	//    if (temp ==0)
	//    {
	//        cout << endl;
	//    }
	//int crossover_size = ceil(temp*size / 2) * 2;
	//crossover_size = 4;
	int crossover_size = k;

	if (crossover_size >= size)
	{
		crossover_size = size;
	}

	for (auto it = chro_population.begin(); it != chro_population.end(); it++)
	{
		if (chro_crossovered_population.size() == 0)
		{
			cout << endl;
		}
		int rd = get_randnum();//生成随机数
		double proc = rd % 10;
		auto ie = it;
		int rds = get_randnum();
		rds = rds % (crossover_size);
		//选择交叉位置
		int diff = (int)(chro_population.end() - it - 1);
		if (diff<rds)
		{
			ie = chro_population.begin() + rds - diff - 1;
		}
		else
		{
			if (rds == 0) {
				continue;
			}
			ie = it + rds;
		}
		//        if (ie->flightplan_list.size()==0)
		//        {
		//            cout <<endl;
		//        }

		if (proc < c_p * 10)
		{

			//        if ((rds == 0)||(rds == chro_population.size()))
			//        {
			//            chro_crossovered_population.push_back(*it);
			//            chro_crossovered_population.push_back(*it);
			//            continue;
			//        }
			chro_crossovered_population.push_back(*it);
			chro_crossovered_population.push_back(*ie);
			int a = it->code_chro;
			int b = ie->code_chro;
			auto iw = ie->flightplan_list.begin();

			for (auto ic = it->flightplan_list.begin(); ic != it->flightplan_list.end(); ic++)
			{
				//均匀交叉
				Flightplan id = *(iw);
				Flightplan iu = *(ic);
				int rd = get_randnum();//生成随机数
				int proc = rd % 2;
				if (proc == 0)
				{
					//开始交叉
					Flightplan temp_flightplan = id;
					id = iu;
					iu = temp_flightplan;
				}
				//it->chro_evaluation();
				//ie->chro_evaluation();
				//输出为未评估染色体
				iw++;
				//id.set_copy_from_flightplan(*iw);
			}
			it->code_chro += base_code;
			ie->code_chro += base_code;

			chro_crossovered_population.push_back(*it);
			chro_crossovered_population.push_back(*ie);
			it->code_chro = a;
			ie->code_chro = b;

		}
		else
		{
			//it->chro_evaluation();
			chro_crossovered_population.push_back(*it);
			chro_crossovered_population.push_back(*ie);
		}

	}
	if (chro_crossovered_population.size() == 0)
	{
		cout << endl;
	}
	//释放原种群
	chro_population.clear();
	vector<Chromosome>(chro_population).swap(chro_population);
	//控制种群大小
	//    for (auto it = chro_crossovered_population.begin(); it != chro_crossovered_population.end(); it++) {
	//        it->chro_evaluation();
	//    }


	return chro_crossovered_population;
}