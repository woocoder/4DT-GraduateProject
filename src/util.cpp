//
//  util.cpp
//  4DT-GA-LYX
//
//  Created by thinking on 5/10/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#include "util.hpp"

using namespace std;
int get_randnum()
{
	random_device rd;
	default_random_engine e(rd());
	uniform_int_distribution<> u(0, 30000);
	return u(e);
}