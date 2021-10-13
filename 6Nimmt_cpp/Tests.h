//
//  Tests.hpp
//  stage_MC
//
//  Created by Yanis Bakhtaoui on 13/07/2021.
//  Copyright © 2021 Yanis Bakhtaoui. All rights reserved.
//

#ifndef Tests_h
#define Tests_h

#include <stdio.h>
#include "MCTS.h"

void test_MC_Flat();
void test_MCTS();
void test_MCTS_vs_MC(int,int);
void test_time_MCTS_MC();
void test_PPA();
void test_PPA_no_depth();
void test_best_alpha();
void test_MAST();
void test_best_k();
void test_MAST_vs_Flat(int, int);
void best_c();
void test_MAST_vs_Flat();
void test_PPA_vs_Flat();
void test_MCTS_vs_Flat();
void test_MCTS_vs_PPA();
void test_MCTS_vs_MAST();
void test_PPA_vs_MAST();
void test_PPA_vs_PPAn();
void test_MASTn_vs_MAST();
void test_MCTS_vs_Flat_D_MCTS();
#endif /* Tests_h */
