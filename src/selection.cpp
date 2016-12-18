//
//  selection.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/7/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include "selection.hpp"

bool comp_a(const Chromosome& a, const Chromosome& b)
{
	return a.evaluation <= b.evaluation;
}

vector<Chromosome> selection(vector<Chromosome>& chro_population)
{
	/*
	按评估标准排序
	1、轮盘赌
	2、改为排序选择
	*/
	sort(chro_population.begin(), chro_population.end(), less<Chromosome>());
	
	if (chro_population.size()>POPU_SIZE) {


		chro_population.erase(chro_population.begin() + POPU_SIZE, chro_population.end());
	}
	//sort(chro_population.begin(), chro_population.end(),less<Chromosome>());//保持有序

	//    vector<double> add_probable;//累加选择概率
	//    vector<double> probable;
	//    for (auto it = chro_population.begin(); it != chro_population.end(); it++)
	//    {
	//        probable.push_back(1/(it->evaluation+1));
	//    }
	//    for (auto it = probable.begin(); it != probable.end(); it++)
	//    {
	//        //计算累加概率
	//        if(it == probable.begin())
	//        {
	//            add_probable.push_back(*it);
	//        }
	//        else
	//        {
	//            add_probable.push_back(*it + (*(add_probable.end()-1)));
	//        }
	//    }
	//    
	//    int select_times = (int)chro_population.size()/2;//设置选择次数
	//    vector<vector<Chromosome>::iterator> select_set;//选择集
	//    while (select_times > 0)
	//    {
	//        select_times -= 1;
	//    int rd = get_randnum();//生成随机数
	//
	//    double dice = fmod(rd,*(add_probable.end()-1));//取余
	//    auto ic = chro_population.begin();
	//    for(auto it = add_probable.begin(); it != add_probable.end(); it++,ic++)
	//    {
	//        //得出选择集
	//        if (dice <= *it)
	//        {
	//            select_set.push_back(ic);
	//            break;
	//        }
	//        
	//    }
	//    }
	vector<Chromosome> Chro_new_population;//新种群
											//long select_size = chro_population.size()/2;
	for (auto it = chro_population.begin(); it != chro_population.end() - 10; it++) {
		Chro_new_population.push_back(*it);
	}

	//    for (auto it = select_set.begin(); it!= select_set.end(); it++) {
	//        Chro_new_population.push_back(**it);
	//    }
	return Chro_new_population;
}