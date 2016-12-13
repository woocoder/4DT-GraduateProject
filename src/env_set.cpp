//
//  env_set.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/9/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include "env_set.hpp"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

void env_set(map<string, vector<vector<Waypoint>>>* flightrouting, vector<Flightplan>* flightplan, map<string, map<int, string>>& aircraft_speed)
{
	/*
	1. distance of Waypoints input  -- cancel
	2. real flightplan input
	3. preformance of aircrafts input
	4. optional routes              -- done
	*/

	/*
	备选路径读取
	*/

	ifstream f_dis("input/rout_dist_0513.txt");
	ifstream f_dic("input/dist_rout_0513.txt");
	ofstream f_disout("output/rout_test_out.txt");

	if ((!f_dis.good()) || (!f_dic.good()) || (!f_disout.good()))
	{
		cout << "Unable open distance file" << endl;
		exit(1);
	}
	else
	{
		cout << "路径信息读写开始********************************" << endl;
		//map<string, vector<vector<Waypoint>>> flightrouting;
		while (!f_dis.eof())            // 若未到文件结束一直循环
		{
			vector<string> temps;
			vector<double> tempd;
			vector<Waypoint> temp_w;
			string s_read, d_read;
			double dist;

			getline(f_dis, s_read, '\n');//读取一行，以换行符结束
			getline(f_dic, d_read, '\n');
			if ((s_read == "") || (d_read == ""))
				continue;
			//istringstream dist_line(d_read.erase(d_read.size()-1,1));
			istringstream dist_line(d_read);
			//cout << "#s_read : " << s_read <<endl;
			boost::split(temps, s_read, boost::is_any_of(" "));
			string s = *temps.begin() + "-" + *(temps.end() - 1);
			while (dist_line >> dist)
			{
				tempd.push_back(dist);
			}
			auto ic = temps.begin();
			for (auto it = tempd.begin(); it != tempd.end(); it++)
			{
				Waypoint *temp_wp = new Waypoint();
				temp_wp->set_waypoint(*ic, *it);
				temp_w.push_back(*temp_wp);
				delete temp_wp;
				ic++;
			}
			(*flightrouting)[s].push_back(temp_w);
		}
		int c = 0;
		for (auto it = (*flightrouting).cbegin(); it != (*flightrouting).cend(); it++)
		{
			//cout <<"第"<< c <<"行写入"<<endl;
			c++;
			f_disout << "#" << c << ":  ";
			f_disout << it->first << endl;
			for (auto ic = it->second.begin(); ic != it->second.end(); ic++)
			{
				for (auto id = (*ic).begin(); id != (*ic).end(); id++)
				{
					f_disout << id->name << ":" << id->between_pre_point << " ";
					//id->print();
				}
				f_disout << '\n';
			}
			f_disout << endl;
		}
		f_disout.close();
		f_dis.close();
		f_dic.close();
		cout << "路径信息读写结束********************************" << endl;


		/*
		读写机型速度
		*/
		//        map<string, map<int, string>> aircraft_speed;

		ifstream f_speed("input/机型速度");
		if (!f_speed.good())
		{
			cout << "Unable open speed file" << endl;
			exit(1);
		}
		while (!f_speed.eof())
		{
			string s_read;
			vector<string> temps;
			//cout << endl;
			getline(f_speed, s_read, '\n');
			if (s_read == "")
			{
				continue;
			}
			boost::split(temps, s_read, boost::is_any_of("\t"));
			aircraft_speed[temps[0]][60] = temps[1];
			aircraft_speed[temps[0]][140] = temps[2];
			aircraft_speed[temps[0]][200] = temps[3];
			aircraft_speed[temps[0]][260] = temps[4];
			aircraft_speed[temps[0]][290] = temps[5];
			aircraft_speed[temps[0]][330] = temps[6];
			//            for(auto it = aircraft_speed.cbegin(); it != aircraft_speed.cend(); it++)
			//            {
			//                cout << it->first << endl;
			//                for (auto ik = it->second.cbegin(); ik != it->second.cend(); ik ++)
			//                {
			//                    cout<< ik->first <<":" << ik->second<<"  " ;
			//                }
			//                cout <<endl;
			//            }
		}

		/*
		读写航班计划
		*/
		cout << "航班计划读写开始********************************" << endl;
		ifstream f_flp("input/flightplan_set.txt");
		ifstream f_land("input/plan_land_time.txt");
		//ofstream f_flpout("/Users/thinking/Developer/4dttest/4dttest/flptest_out.txt");

		//map<string,Flightplan> flightplan;
		if ((!f_flp.good()) || (!f_land.good()))
		{
			cout << "Unable open plan file" << endl;
			exit(1);
		}
		map<string, ptime> flp_land_time;
		while (!f_land.eof())
		{
			vector<string> temps;
			string s_read;
			getline(f_land, s_read, '\n');
			if (s_read == "")
				continue;

			//cout << s_read << endl;
			boost::split(temps, s_read, boost::is_any_of("\t"));
			ptime land_time_temp = time_from_string("2016-05-08 " + temps[1]);
			flp_land_time[temps[0]] = land_time_temp;
		}
		while (!f_flp.eof())           // 若未到文件结束一直循环
		{
			vector<string> temps;
			vector<string> tempw;
			vector<Waypoint> temp_w;
			string s_read, d_read, flp_s;

			getline(f_flp, s_read, '\n');//读取一行，以换行符结束

			if (s_read == "")
				continue;

			boost::split(temps, s_read, boost::is_any_of("\t"));

			Flightplan *temp_flp = new Flightplan();
			string date_temp = "2016-05-08 " + temps[1];

			temp_flp->take_off = time_from_string(date_temp);
			int hour = temp_flp->take_off.time_of_day().hours();
			if ((hour != 8)&& (hour!=9))//&&(hour!=10)&&(hour!=11))
			{
				continue;
			}
			temp_flp->aircraft = temps[0];
			temp_flp->aircraft_type = temps[2];
			temp_flp->origination = temps[3];
			temp_flp->destination = temps[4];
			int rd = get_randnum() % 9;
			switch (rd) {
			case 0:
				temp_flp->fly_level = 60;
				break;
			case 1:
				temp_flp->fly_level = 157;
				break;
			case 2:
				temp_flp->fly_level = 217;
				break;
			case 3:
				temp_flp->fly_level = 276;
				break;
			case 4:
				temp_flp->fly_level = 291;
				break;
			case 5:
				temp_flp->fly_level = 331;
				break;
			case 6:
				temp_flp->fly_level = 331;
				break;
			case 7:
				temp_flp->fly_level = 331;
				break;
			case 8:
				temp_flp->fly_level = 331;
				break;

			default:
				break;
			}

			/*
			设置速度
			*/
			temp_flp->set_speed(aircraft_speed);

			//cout << date_temp <<endl;
			//string s = to_simple_string(temp_flp->take_off);
			//cout << s<< endl;
			temp_flp->land = flp_land_time[temps[0]] - minutes(15);
			if (temp_flp->land<temp_flp->take_off)
			{
				temp_flp->land += days(1);
			}

			//boost::split(tempw,temps[6],boost::is_any_of(" "));
			flp_s = temp_flp->origination + "-" + temp_flp->destination;
			/*
			用flightrouting的第一个元素作为计划航线
			改为用初始航迹来计划路径

			***************************************
			flightrouting 中，第一条航迹即为初始航迹
			*/
			if (flightrouting->find(flp_s) != flightrouting->end())
			{
				auto c = (*flightrouting)[flp_s][0];
				temp_flp->set_copy_from_routing((*flightrouting)[flp_s][0]);
				temp_flp->set_point_time();
				flightplan->push_back(*temp_flp);
				delete temp_flp;
			}
			else
				break;

			//cout <<"第"<<count++<<endl;
		}
		cout << "flightplan size :" << flightplan->size() << endl;
		f_flp.close();
		ofstream f_flpout("output/flptest_out");
		if (!f_flpout.good())
		{
			cout << "Unable open plan file" << endl;
			exit(1);
		}
		for (auto it = (*flightplan).begin(); it != (*flightplan).end(); it++)
		{
			//cout <<"第"<< c++ <<"行写入"<<endl;

			f_flpout << it->aircraft << endl;
			f_flpout << it->origination << '\t' << it->destination << '\t' << it->take_off << '\t' << it->land << '\t' << it->length << '\t' << it->fly_level << endl;
			f_flpout << it->norm_speed << '\t' << it->min_speed << '\t' << it->max_speed << endl;
			for (auto ic = it->flightrouting.begin(); ic != it->flightrouting.end(); ic++)
			{
				f_flpout << ic->name << ":" << ic->between_pre_point << " ";
				//id->print();
			}
			f_flpout << endl;
		}
		f_flpout.close();
		cout << "航班计划读写结束********************************" << endl;


	}
	/*
	out:
	distace <map>
	flghtplan <map> {airport\time\waypoint}
	*/


}