//
//  evaluation.hpp
//  4DT-GA-LYX
//
//  Created by thinking on 4/20/16.
//  Copyright © 2016 Arthur Lee. All rights reserved.
//

#ifndef evaluation_hpp
#include <stdio.h>
#include "Chromosome.hpp"
#define evaluation_hpp


void chro_evaluation();
void chro_penalty();
void chro_print_to_file_and_evaluation(ofstream& f_out);

#endif /* evaluation_hpp */
