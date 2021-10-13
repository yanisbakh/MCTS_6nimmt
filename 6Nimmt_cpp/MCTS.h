//
//  MCTS.hpp
//  stage_MC
//
//  Created by Yanis Bakhtaoui on 23/06/2021.
//  Copyright © 2021 Yanis Bakhtaoui. All rights reserved.
//

#ifndef MCTS_hpp
#define MCTS_hpp

#include <stdio.h>
#include "game.h"

#include <iostream>
#include <vector>
using namespace std;

class Node{
    private:
    Node *father;
    vector <Node*> son;
    int nbr_simu;
    int nbr_win;
    float policy;
    float polp;
    Card Card_played;
    int player_actu;
    public:
    Node();
    Node(Node*, Card, int, float pol = 0.);
    bool is_Leaf();
    vector <Node*> get_son();
    int get_nbr_simu();
    int get_nbr_win();
    int get_player_actu();
    float get_policy();
    float get_polp();
    void incr_simu();
    void incr_win();
    void update_polp();
    void update_policy();
    void add_polp(float);
    void update_polp(float, float);
    void update_policy_MAST();
    Card get_Card_played();
    Node &operator = (const Node &);
    Node* get_father();

};

class Tree{
    private:
    vector <Node*> road;
    vector <Node*> road_playouts;
    vector <int> already_played1;
    vector <int> already_played2;
    Playout playout_actu;
    public:
    Tree();
    Tree(Playout);
    ~Tree();
    Tree &operator = (const Tree &);
    void exploration(float c = 0.4);
    void exploration_policy(float, float pol = 0.);
    int simulation();
    int simulation_playout(float k, float pol = 0.);
    void adapt_MAST(int result);
    void adapt_MAST_no_depth(int result);
    void adapt_PPA_no_depth(int result, float alpha);
    void adapt_PPA(int result, float alpha);
    void backprop();
    void backprop_PPA(float alpha);
    void backprop_PPA_no_depth(float alpha);
    void backprop_MAST(float k = 3.5);
    void backprop_MAST_no_depth(float k = 3.5);
    vector <Node*> get_road();
    vector <Node*> get_road_playout();
    Playout get_playout();
};

#endif /* MCTS_hpp */
