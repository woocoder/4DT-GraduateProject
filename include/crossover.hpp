//
//  crossover.hpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/7/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#ifndef crossover_hpp
#define crossover_hpp

#include <stdio.h>
#include "Chromosome.hpp"
#include <math.h>

vector<Chromosome> crossover( int k,double c_p, vector<Chromosome>& chro_population);

#endif /* crossover_hpp */
