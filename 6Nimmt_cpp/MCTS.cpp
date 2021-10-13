//
//  MCTS.cpp
//  stage_MC
//
//  Created by Yanis Bakhtaoui on 23/06/2021.
//  Copyright © 2021 Yanis Bakhtaoui. All rights reserved.
//

#include "MCTS.h"
#include <math.h>
#include <random>

Node::Node(){
    this->son = {};
    this->father = NULL;
    this->nbr_simu = 0;
    this->nbr_win = 0;
    this->policy = 0.;
    this->polp = 0.;
    Card empty;
    this->Card_played = empty;
    this->player_actu = 1;
}

Node::Node(Node *p, Card Card, int player, float pol){
    this->son = {};
    this->father = p;
    this->nbr_simu = 0;
    this->nbr_win = 0;
    this->policy = pol;
    this->polp = 0.;
    this->Card_played = Card;
    p->son.push_back(this);
    this->player_actu = player;

}

bool Node::is_Leaf(){
    return this->son.empty();
}

vector <Node*> Node::get_son(){
    return this->son;
}

int Node::get_nbr_win(){
    return this->nbr_win;
}

int Node::get_nbr_simu(){
    return this->nbr_simu;
}

int Node::get_player_actu(){
    return this->player_actu;
}

float Node::get_policy(){
    return this->policy;
}

float Node::get_polp(){
    return this->polp;
}

void Node::incr_win(){
    this->nbr_win++;
}

void Node::incr_simu(){
    this->nbr_simu++;
}

void Node::update_polp(){
    this->polp = this->policy;
}

void Node::update_policy(){
    this->policy = this->polp;
}

void Node::add_polp(float alpha){
    this->polp = this->polp + alpha;
}

void Node::update_polp(float alpha, float z){
    this->polp = this->polp - alpha * (float(exp(this->policy)/z));
}

void Node::update_policy_MAST(){
    this->policy = float(this->get_nbr_win())/this->get_nbr_simu();
}

Card Node::get_Card_played(){
    return this->Card_played;
}

Node & Node :: operator=(const Node &node){
    this->father = node.father;
    this->son = node.son;
    this->nbr_win = node.nbr_win;
    this->nbr_simu = node.nbr_simu;
    this->player_actu = node.player_actu;
    return *this;
}

Node* Node::get_father(){
    return this->father;
}

Tree::Tree(){
    Playout playout;
    this->playout_actu = playout;
    this->road.push_back(new Node);
    this->road_playouts.push_back(new Node);
}

Tree::Tree(Playout playout){
    this->playout_actu = playout;
    this->road.push_back(new Node);
    this->road_playouts.push_back(new Node);
}

Tree::~Tree(){
    for(int i = 0 ; i < road.size() ; i++){
        delete road[i];
    }
    for(int i = 0 ; i < road_playouts.size() ; i++){
        delete road_playouts[i];
    }
}

Tree & Tree :: operator=(const Tree &tree){
    this->road = tree.road;
    this->playout_actu = tree.playout_actu;
    return *this;
}

void Tree::exploration(float c){
    Node* point;
    this->road = {this->road[0]};
    point = this->road[0];
    this->already_played1 = {};
    this->already_played2 = {};
    while(!point->is_Leaf()){
        vector <double> value;
        vector <Node*> son_node = point->get_son();
        for(int i = 0 ; i < son_node.size() ; i++){
            int test = son_node[i]->get_nbr_simu();
            if(test==0){
                test = 1;
            }
            cout << float(son_node[i]->get_nbr_win())/test
            + c*sqrt(log(son_node[i]->get_father()->get_nbr_simu())/test) << endl;
            value.push_back(
                        float(son_node[i]->get_nbr_win())/test
                        + c*sqrt(log(son_node[i]->get_father()->get_nbr_simu())/test)
                        );
        }
        int pos = max_element(value.begin(),value.end()) - value.begin();
        if(son_node[pos]->get_player_actu()==1){
            this->already_played1.push_back(this->playout_actu.get_player1().get_pos_card(son_node[pos]->get_Card_played()));
        }
        else{
            this->already_played2.push_back(this->playout_actu.get_player2().get_pos_card(son_node[pos]->get_Card_played()));
        }
        this->road.push_back(son_node[pos]);
        point = this->road.back();
    }
    vector <int> not_played1;
    vector <int> not_played2;
    for(int j = 0 ; j < this->playout_actu.get_player1().Number_Cards() ; j++){            if(!(find(this->already_played1.begin(), this->already_played1.end(), j) != this->already_played1.end())){
            not_played1.push_back(j);
        }
        if(!(find(this->already_played2.begin(), this->already_played2.end(), j) != this->already_played2.end())){
            not_played2.push_back(j);
        }
    }
    for(int k = 0 ; k < not_played1.size() ; k++){
        new Node(point,this->playout_actu.get_player1().give_Card(not_played1[k]),1);
        for(int l = 0 ; l < not_played2.size() ; l++){
            new Node(point->get_son()[k],this->playout_actu.get_player2().give_Card(not_played2[l]),2);
        }
    }
    point->get_Card_played().Display();
}

void Tree::exploration_policy(float k, float pol){
    Node* point;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    this->road = {this->road[0]};
    point = this->road[0];
    this->already_played1 = {};
    this->already_played2 = {};
    float z = 0.;
    vector <float> weights;
    random_device generator;
    mt19937 gen(generator());
    while(!point->is_Leaf()){
        z = 0.;
        weights = {};
        vector <Node*> son_node = point->get_son();
        cout.rdbuf(orig_buf);
        for(int i = 0 ; i < son_node.size() ; i++){
            z = z + float(exp(k*son_node[i]->get_policy()));
        }
        int pos_test = -1;

        for(int j = 0 ; j < son_node.size() ; j++){
            weights.push_back(float(exp(k*son_node[j]->get_policy()))/z);
            if(float(weights.back())>0.9999){
                pos_test = j;
            }
        }
        int pos;
        if(pos_test >-1){
            pos = pos_test;
        }
        else{
            discrete_distribution<> d(weights.begin(),weights.end());
            pos = d(generator);
        }
        cout.rdbuf(NULL);
        if(son_node[pos]->get_player_actu()==1){
            already_played1.push_back(this->playout_actu.get_player1().get_pos_card(son_node[pos]->get_Card_played()));
        }
        else{
            already_played2.push_back(this->playout_actu.get_player2().get_pos_card(son_node[pos]->get_Card_played()));
        }
        this->road.push_back(son_node[pos]);
        point = this->road.back();
    }
    vector <int> not_played1;
    vector <int> not_played2;
    for(int j = 0 ; j < this->playout_actu.get_player1().Number_Cards() ; j++){            if(!(find(already_played1.begin(), already_played1.end(), j) != already_played1.end())){
            not_played1.push_back(j);
        }
        if(!(find(already_played2.begin(), already_played2.end(), j) != already_played2.end())){
            not_played2.push_back(j);
        }
    }
    for(int m = 0 ; m < not_played1.size() ; m++){
        new Node(point,this->playout_actu.get_player1().give_Card(not_played1[m]),1, pol);
        for(int l = 0 ; l < not_played2.size() ; l++){
            new Node(point->get_son()[m],this->playout_actu.get_player2().give_Card(not_played2[l]),2, pol);
        }
    }

}


int Tree::simulation(){
    int verif;
    Playout recopie = this->playout_actu;
    cout << this->road.size() << endl;
    cout << (this->road.size()-1)/2 + 1 << endl;
    for(int i = 0 ; i < (this->road.size()-1)/2 + 1 ; i++){
        if(i>0){
            cout << recopie.get_player1().get_pos_card(this->road[i]->get_Card_played())<<endl;
            recopie.Round_two_cards(recopie.get_player1().get_pos_card(this->road[2*(i-1)+1]->get_Card_played()),recopie.get_player2().get_pos_card(this->road[2*(i-1)+2]->get_Card_played()));
        }
    }
    verif = recopie.Game_No_text();
    return verif;
}

int Tree::simulation_playout(float k, float pol){
    this->road_playouts = {this->road.back()};
    Node* point;
    point = this->road_playouts[0];
    Playout recopie = this->playout_actu;
    for(int i = 0 ; i < (this->road.size()-1)/2 + 1 ; i++){
        if(i>0){
            recopie.Round_two_cards(recopie.get_player1().get_pos_card(this->road[2*(i-1)+1]->get_Card_played()),recopie.get_player2().get_pos_card(this->road[2*(i-1)+2]->get_Card_played()));
        }
    }
    vector <float> weights1;
    vector <float> weights2;
    vector <int> not_played1;
    vector <int> not_played2;
    float z1;
    float z2;
    int pos1;
    int pos2;
    random_device generator;
    mt19937 gen(generator());
    int count = 0;
    while(already_played1.size() < recopie.get_player1().Number_Cards()){
        count++;
        z1 = 0.;
        z2 = 0.;
        weights1 = {};
        weights2 = {};
        not_played1={};
        not_played2={};
        vector <Node*> son_node = point->get_son();
        for(int i = 0 ; i < son_node.size() ; i++){
            z1 = z1 + float(exp(k*son_node[i]->get_policy()));
        }
        int pos_test = -1;
        for(int j = 0 ; j < son_node.size() ; j++){
            weights1.push_back(float(exp(k*son_node[j]->get_policy()))/z1);
            if(float(weights1.back())>0.9999){
                pos_test = j;
            }
        }
        if(pos_test >-1){
            pos1 = pos_test;
        }
        else{
            discrete_distribution<> d1(weights1.begin(),weights1.end());
            pos1 = d1(generator);
        }
        already_played1.push_back(recopie.get_player1().get_pos_card(son_node[pos1]->get_Card_played()));
        this->road_playouts.push_back(son_node[pos1]);
        point = this->road_playouts.back();
        son_node = point->get_son();
        for(int i = 0 ; i < son_node.size() ; i++){
            z2 = z2 + float(exp(k*son_node[i]->get_policy()));
        }
        pos_test = -1;
        for(int j = 0 ; j < son_node.size() ; j++){
            weights2.push_back(float(exp(k*son_node[j]->get_policy()))/z2);
            if(float(weights2.back())>0.9999){
                pos_test = j;
            }
        }
        if(pos_test >-1){
            pos2 = pos_test;
        }
        else{
            discrete_distribution<> d2(weights2.begin(),weights2.end());
            pos2 = d2(generator);
        }
        already_played2.push_back(recopie.get_player2().get_pos_card(son_node[pos2]->get_Card_played()));
        for(int j = 0 ; j < recopie.get_player1().Number_Cards() ; j++){            if(!(find(already_played1.begin(), already_played1.end(), j) != already_played1.end())){
                    not_played1.push_back(j);
            }
        }
        for(int j = 0 ; j < recopie.get_player2().Number_Cards() ; j++){            if(!(find(already_played2.begin(), already_played2.end(), j) != already_played2.end())){
                    not_played2.push_back(j);
            }
        }
        this->road_playouts.push_back(son_node[pos2]);
        point = this->road_playouts.back();
        for(int m = 0 ; m < not_played1.size() ; m++){
            new Node(point,recopie.get_player1().give_Card(not_played1[m]),1, pol);
            for(int l = 0 ; l < not_played2.size() ; l++){
                new Node(point->get_son()[m],recopie.get_player2().give_Card(not_played2[l]),2, pol);
            }
        }
    }
    streambuf* orig_buf = cout.rdbuf();
    for(int i = 0 ; i < (this->road_playouts.size()-1)/2 + 1 ; i++){
        cout.rdbuf(NULL);
        if(i>0){
            recopie.Round_two_cards(recopie.get_player1().get_pos_card(this->road_playouts[2*(i-1)+1]->get_Card_played()),recopie.get_player2().get_pos_card(this->road_playouts[2*(i-1)+2]->get_Card_played()));
        }
        cout.rdbuf(orig_buf);
    }
    cout.rdbuf(orig_buf);
    if(recopie.get_player1().Get_Points() < recopie.get_player2().Get_Points()){
        return 1;
    }
    else if (recopie.get_player1().Get_Points() > recopie.get_player2().Get_Points()){
        return 0;
    }
    else{
        return 0.5;
    }
}

void Tree::adapt_MAST(int result){
    for(int i = 0 ; i < this->road_playouts.size() ; i++){
        this->road_playouts[i]->incr_simu();
        if(((result == 1) & (i%2==0)) || ((result == 0) & (i%2==1))){
            this->road_playouts[i]->incr_win();
        }
        this->road_playouts[i]->update_policy_MAST();
    }
}

void Tree::adapt_MAST_no_depth(int result){
    for(int i = 0 ; i < this->road_playouts.size() ; i++){
        this->road_playouts[i]->get_Card_played().incr_simu();
        if(((result == 1) & (i%2==0)) || ((result == 0) & (i%2==1))){
            this->road_playouts[i]->get_Card_played().incr_win();
        }
        this->road_playouts[i]->get_Card_played().update_policy_mast();
    }
}


void Tree::adapt_PPA_no_depth(int result, float alpha){
    float z;
    for(int i = 0 ; i < this->road_playouts.size() ; i++){
        this->road_playouts[i]->get_Card_played().incr_simu();
        if(((result == 1) & (i%2==0)) || ((result == 0) & (i%2==1))){
            this->road_playouts[i]->get_Card_played().incr_win();
        }
        this->road_playouts[i]->get_Card_played().add_polp(alpha);
        z = 0.;
        vector <Card*> son_card;
        Card tempo;
        if(i<this->road_playouts.size()-1){
            for(int l = i+1 ; l < this->road_playouts.size() ; l++){
                tempo = this->road_playouts[l]->get_Card_played();
                son_card.push_back(&tempo);
            }
        }
        for(int k = 0 ; k < son_card.size() ; k++){
            z = z + float(exp(son_card[k]->get_policy()));
        }
        for(int j = 0 ; j < son_card.size() ; j++){
            son_card[j]->update_polp(alpha,z);
        }
    }
    for(int i = 0 ; i < this->road_playouts.size() ; i++){
        vector <Card*> son_card;
        Card tempo;
        if(i<this->road_playouts.size()-1){
            for(int l = i+1 ; l < this->road_playouts.size() ; l++){
                tempo = this->road_playouts[l]->get_Card_played();
                son_card.push_back(&tempo);
            }
        }
        this->road_playouts[i]->get_Card_played().update_policy();
        for(int j = 0 ; j < son_card.size() ; j++){
            son_card[j]->update_policy();
        }
    }
}

void Tree::adapt_PPA(int result, float alpha){
    float z;
    for(int i = 0 ; i < this->road_playouts.size() ; i++){
        this->road_playouts[i]->incr_simu();
        if(((result == 1) & (i%2==0)) || ((result == 0) & (i%2==1))){
            this->road_playouts[i]->incr_win();
        }
        this->road_playouts[i]->add_polp(alpha);
        z = 0.;
        vector <Node*> son_node = this->road_playouts[i]->get_son();
        cout << son_node.size()<<endl;
        for(int k = 0 ; k < son_node.size() ; k++){
            cout << k << endl;
            z = z + float(exp(son_node[k]->get_policy()));
        }
        for(int j = 0 ; j < son_node.size() ; j++){
            son_node[j]->update_polp(alpha,z);
        }
    }
    for(int i = 0 ; i < this->road_playouts.size() ; i++){
        for(int j = 0 ; j < road_playouts[i]->get_son().size() ; j++){
            road_playouts[i]->get_son()[j]->update_policy();
        }
    }
}

void Tree::backprop(){
    int verif;
    Node empty;
    int rand_pos1 = 0;
    int rand_pos2 = 0;
    if(this->road.back()->get_son().size()>1){
        rand_pos1 = rand() % (this->road.back()->get_son().size()-1);
        rand_pos2 = rand() % (this->road.back()->get_son()[rand_pos1]->get_son().size()-1);
    }
    if(this->road.back()->get_son().size()>0){
        this->road.push_back(road.back()->get_son()[rand_pos1]);
        if(this->road.back()->get_son().size()>0){
            this->road.push_back(this->road.back()->get_son()[rand_pos2]);
        }
    }
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    verif = this->simulation();
    cout.rdbuf(orig_buf);
    Node* point;
    point = this->road.back();
    while(point->get_Card_played().Give_num()!=0){
        if((verif == 1 & point->get_player_actu()==1) | (verif == 0 & point->get_player_actu()==2) ){
            point->incr_win();
        }
        point->incr_simu();
        cout << point->get_nbr_simu() << endl;;
        cout << point->get_nbr_win() << endl;
        point = point->get_father();
    }
    point->incr_simu();
    cout << point->get_nbr_simu() << endl;;
    cout << point->get_nbr_win() << endl;
    point = point->get_father();//à supp ?
    this->road.pop_back();
    this->road.pop_back();
}


void Tree::backprop_MAST(float k){
    int verif;
    Node empty;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    verif = this->simulation_playout(k);
    this->adapt_MAST(verif);
    Node* point;
    point = this->road.back();
    while(point->get_Card_played().Give_num()!=0){
        if((verif == 1 & point->get_player_actu()==1) | (verif == 0 & point->get_player_actu()==2) ){
            point->incr_win();
        }
        point->incr_simu();
        point = point->get_father();
    }
    point->incr_simu();
    point = point->get_father();
    this->road_playouts={};
}

void Tree::backprop_MAST_no_depth(float k){
    int verif;
    Node empty;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    verif = this->simulation_playout(k);
    this->adapt_MAST_no_depth(verif);
    Node* point;
    point = this->road.back();
    while(point->get_Card_played().Give_num()!=0){
        if((verif == 1 & point->get_player_actu()==1) | (verif == 0 & point->get_player_actu()==2) ){
            point->incr_win();
        }
        point->incr_simu();
        cout << point->get_nbr_simu() << endl;;
        cout << point->get_nbr_win() << endl;
        point = point->get_father();
    }
    point->incr_simu();
    point = point->get_father();
    this->road_playouts={};}

void Tree::backprop_PPA(float alpha){
    int verif;
    Node empty;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    verif = this->simulation_playout(1.);
    this->adapt_PPA(verif,alpha);
    cout.rdbuf(orig_buf);
    Node* point;
    point = this->road.back();
    while(point->get_Card_played().Give_num()!=0){
        if((verif == 1 & point->get_player_actu()==1) | (verif == 0 & point->get_player_actu()==2) ){
            point->incr_win();
        }
        point->incr_simu();
        point = point->get_father();
    }
    point->incr_simu();
    point = point->get_father();
    this->road_playouts={};
}

void Tree::backprop_PPA_no_depth(float alpha){
    int verif;
    Node empty;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    verif = this->simulation_playout(1.);
    this->adapt_PPA_no_depth(verif,alpha);
    Node* point;
    point = this->road.back();
    while(point->get_Card_played().Give_num()!=0){
        if((verif == 1 & point->get_player_actu()==1) | (verif == 0 & point->get_player_actu()==2) ){
            point->incr_win();
        }
        point->incr_simu();
        cout << point->get_nbr_simu() << endl;;
        cout << point->get_nbr_win() << endl;
        point = point->get_father();
    }
    point->incr_simu();
    point = point->get_father();
    this->road_playouts={};
}


vector <Node*> Tree::get_road(){
    return road;
}

vector <Node*> Tree::get_road_playout(){
    return road_playouts;
}


Playout Tree::get_playout(){
    return playout_actu;
}
