//
//  Waypoint.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/15/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include "Waypoint.hpp"

void Waypoint::copy_waypoint(Waypoint& initial_waypoint)
{
    this->name = initial_waypoint.name;
    this->between_pre_point = initial_waypoint.between_pre_point;
    this->norm_time = initial_waypoint.norm_time;
    this->min_time = initial_waypoint.max_time;
    this->max_time = initial_waypoint.min_time;
    
}

void Waypoint::print()
{
    cout << this->name << " : " << this->between_pre_point<<" "<<"->"<<this->min_time<<' '<<this->norm_time<< " " << this->max_time<<endl ;
    
}
void Waypoint::set_waypoint(string r_name,double r_dist)
{
    this->name = r_name;
    this->between_pre_point = r_dist;
}

void Waypoint::wap_print_to_file(ofstream& f_out)
{
    f_out << this->name << " : " << this->between_pre_point<<"\t";
}

