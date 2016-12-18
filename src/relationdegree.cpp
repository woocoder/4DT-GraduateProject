#include "relationdegree.hpp"


vector<Chromosome> relationdegree(vector<Chromosome>& chro_population, map<string, vector<vector<Waypoint>>>&  flightrouting, map<string, map<int, string>>& aircraft_speed, bool thisActive)
{
	if (thisActive == false)
	{
		return chro_population;
	}

}