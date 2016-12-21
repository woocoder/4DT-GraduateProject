#include "relationdegree.hpp"


vector<Chromosome> relationdegree(vector<Chromosome>& chro_population, map<string, vector<vector<Waypoint>>>&  flightrouting, map<string, map<int, string>>& aircraft_speed, bool thisActive)
{
	if (thisActive == false)
	{
		return chro_population;
	}

	vector<Chromosome> chro_related_population;
	for (auto it = chro_population.begin(); it != chro_population.end(); it++)
	{
		Chromosome* chro_temp = new Chromosome();
		*chro_temp = *it;
		chro_related_population.push_back(*chro_temp);
		delete chro_temp;
		/*
		int rd1 = get_randnum()%5;
		if (rd1 != 0)
			continue;
			*/
		for (auto ic = it->flightplan_list.begin(); ic != it->flightplan_list.end(); ic++)
		{
			if (ic->relationdegree > 1)
			{
				if (flightrouting.find(((*ic).origination + "-" + (*ic).destination)) != flightrouting.end())
				{

					int rd = get_randnum() % flightrouting[(*ic).origination + "-" + (*ic).destination].size();
					//(*ic).set_copy_from_routing(flightrouting[(*ic).origination + "-" + (*ic).destination][rd]);
					ic->flightrouting = flightrouting[(*ic).origination + "-" + (*ic).destination][rd];
				}
				int rd = get_randnum() % 5;
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

				default:
					break;
				}
				ic->set_speed(aircraft_speed);
				ic->set_length();
				ic->set_point_time();
			}
		}
		chro_related_population.push_back(*it);
	}
	return chro_related_population;
}