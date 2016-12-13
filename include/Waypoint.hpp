//
//  Waypoint.hpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/19/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#ifndef Waypoint_hpp
#define Waypoint_hpp
#include <iostream>
#include <string>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>


using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;


class Waypoint
{
public:
    string name ;
    double between_pre_point ;
    ptime norm_time,min_time,max_time;
    void print();
    void wap_print_to_file(ofstream& f_out);
    void set_waypoint(string r_name,double r_dist);
    void copy_waypoint(Waypoint& a);
};


#endif /* Waypoint_h */