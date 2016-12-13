//
//  Flightplan.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/19/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include "Flightplan.hpp"

string Flightplan::get_routing()
{
	string temp_routing = "";
	for (auto it = this->flightrouting.begin(); it != this->flightrouting.end(); it++)
	{
		if (it == this->flightrouting.begin())
		{
			temp_routing = temp_routing + it->name;
		}
		else
			temp_routing = temp_routing + " " + it->name;
	}
	return temp_routing;
}
void Flightplan::set_point_time()
{
	for (auto it = this->flightrouting.begin(); it != this->flightrouting.end(); it++)
	{
		if (it == this->flightrouting.begin())
		{
			it->norm_time = this->take_off;
			minutes m(5);
			it->min_time = it->norm_time - m;
			it->max_time = it->norm_time + m;
			//            cout<<it->norm_time<<endl;

		}
		else
		{

			seconds norm_time_dur((it->between_pre_point * 3600) / ((this->norm_speed)));
			seconds min_time_dur((it->between_pre_point * 3600) / ((this->max_speed)));
			seconds max_time_dur((it->between_pre_point * 3600) / ((this->min_speed)));

			//            cout<<it->between_pre_point<<endl;
			//            cout<< this->norm_speed<<endl;
			//            cout << norm_time_dur <<endl;
			//            cout <<(it->between_pre_point*3600)/((this->norm_speed)) <<endl;
			it->norm_time = ((it - 1)->norm_time) + norm_time_dur;
			it->min_time = ((it - 1)->min_time) + min_time_dur;
			it->max_time = ((it - 1)->max_time) + max_time_dur;

			//            cout << "norm_time_dur" << norm_time_dur <<endl;
			//            cout << it->name << ": norm_time: " << it->norm_time <<endl;
		}

	}
}

void Flightplan::set_length()
{
	this->length = 0;
	for (auto it = this->flightrouting.begin(); it != this->flightrouting.end(); it++)
	{
		this->length += (*it).between_pre_point;
	}
}
void Flightplan::set_speed(map<string, map<int, string>> aircraft_speed)
{
	if (this->aircraft_type == "")
	{
		cout << "aircraft_type is null" << endl;
		return;
	}
	vector<string> temps;
	int a = this->fly_level;
	stringstream tempsti1, tempsti2, tempsti3;
	if (a == 60)
	{

		boost::split(temps, aircraft_speed[this->aircraft_type][60], boost::is_any_of("&"));
		//cout << aircraft_type <<endl;
		tempsti1 << temps[0];
		tempsti1 >> this->min_speed;
		tempsti2 << temps[1];
		tempsti2 >> this->norm_speed;
		tempsti3 << temps[2];
		tempsti3 >> this->max_speed;

	}
	else if (a == 157)
	{
		boost::split(temps, aircraft_speed[this->aircraft_type][140], boost::is_any_of("&"));
		tempsti1 << temps[0];
		tempsti1 >> this->min_speed;
		tempsti2 << temps[1];
		tempsti2 >> this->norm_speed;
		tempsti3 << temps[2];
		tempsti3 >> this->max_speed;
	}
	else if (a == 217)
	{
		boost::split(temps, aircraft_speed[this->aircraft_type][200], boost::is_any_of("&"));
		tempsti1 << temps[0];
		tempsti1 >> this->min_speed;
		tempsti2 << temps[1];
		tempsti2 >> this->norm_speed;
		tempsti3 << temps[2];
		tempsti3 >> this->max_speed;
	}
	else if (a == 276)
	{
		boost::split(temps, aircraft_speed[this->aircraft_type][260], boost::is_any_of("&"));
		tempsti1 << temps[0];
		tempsti1 >> this->min_speed;
		tempsti2 << temps[1];
		tempsti2 >> this->norm_speed;
		tempsti3 << temps[2];
		tempsti3 >> this->max_speed;
	}
	else if (a == 291)
	{
		boost::split(temps, aircraft_speed[this->aircraft_type][290], boost::is_any_of("&"));
		tempsti1 << temps[0];
		tempsti1 >> this->min_speed;
		tempsti2 << temps[1];
		tempsti2 >> this->norm_speed;
		tempsti3 << temps[2];
		tempsti3 >> this->max_speed;
	}
	else if (a == 331)
	{
		boost::split(temps, aircraft_speed[this->aircraft_type][330], boost::is_any_of("&"));
		tempsti1 << temps[0];
		tempsti1 >> this->min_speed;
		tempsti2 << temps[1];
		tempsti2 >> this->norm_speed;
		tempsti3 << temps[2];
		tempsti3 >> this->max_speed;
	}
	this->min_speed = this->min_speed * 1.852 *1.37;
	this->norm_speed = this->norm_speed * 1.852 *1.37;
	this->max_speed = this->max_speed * 1.852 *1.37;

}
void Flightplan::set_copy_from_routing(vector<Waypoint> initial_waypoint)
{
	this->flightrouting.clear();
	this->length = 0;
	for (auto it = initial_waypoint.begin(); it != initial_waypoint.end(); it++)
	{
		Waypoint* a = new Waypoint();
		a->copy_waypoint(*it);
		this->flightrouting.push_back(*a);
		delete a;
		this->length += it->between_pre_point;
	}

}

void Flightplan::set_copy_from_flightplan(Flightplan flp)
{
	this->flightrouting.clear();

	this->aircraft = flp.aircraft;
	this->origination = flp.origination;
	this->destination = flp.destination;
	this->take_off = flp.take_off;
	this->land = flp.land;
	this->fly_level = flp.fly_level;
	this->aircraft_type = flp.aircraft_type;
	this->length = 0;
	this->norm_speed = flp.norm_speed;
	this->min_speed = flp.min_speed;
	this->max_speed = flp.max_speed;

	if (!flp.flightrouting.empty())
	{
		for (auto it = flp.flightrouting.begin(); it != flp.flightrouting.end(); it++)
		{
			Waypoint* a = new Waypoint();
			a->copy_waypoint(*it);
			this->flightrouting.push_back(*a);
			delete a;
			this->length += it->between_pre_point;

		}
	}
}

void Flightplan::flp_print_to_file(ofstream& f_out)
{
	f_out << this->aircraft << endl;
	f_out << "起飞机场：" << this->origination << '\t' << "目的机场：" << this->destination << '\t' << "起飞时间：" << this->take_off << '\t' << "降落时间：" << this->land << '\t' << "飞行高度：" << this->fly_level << '\t' << "机型：" << aircraft_type << endl;
	for (auto it = this->flightrouting.begin(); it != this->flightrouting.end(); it++)
	{
		(*it).wap_print_to_file(f_out);
	}
	f_out << endl;
}
void Flightplan::flp_print_to_cout()
{
	cout << this->aircraft << endl;
	cout << "起飞机场：" << this->origination << '\t' << "目的机场：" << this->destination << '\t' << "起飞时间：" << this->take_off << '\t' << "降落时间：" << this->land << '\t' << "飞行高度：" << this->fly_level << '\t' << "机型：" << aircraft_type << "飞行里程\t" << this->length << endl;
	cout << "速度\t" << this->norm_speed << '\t' << this->max_speed << '\t' << this->min_speed << endl;
	for (auto it = this->flightrouting.begin(); it != this->flightrouting.end(); it++)
	{
		(*it).print();
	}
	cout << endl;
}
/*
Flightplan& Flightplan::operator = (const Flightplan flp)
{
	this->aircraft = flp.aircraft;
	this->origination = flp.origination;
	this->destination = flp.destination;
	this->take_off = flp.take_off;
	this->land = flp.land;
	this->fly_level = flp.fly_level;
	this->aircraft_type = flp.aircraft_type;
	this->length = flp.length;
	this->norm_speed = flp.norm_speed;
	this->min_speed = flp.min_speed;
	this->max_speed = flp.max_speed;

	if (!flp.flightrouting.empty())
	{
		for (auto it = flp.flightrouting.begin(); it != flp.flightrouting.end(); it++)
		{
			this->flightrouting.push_back(*it);
		}
	}

	return *this;
}

*/