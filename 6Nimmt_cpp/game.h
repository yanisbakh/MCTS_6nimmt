//
//  game.h
//  stage_MC
//
//  Created by Yanis Bakhtaoui on 08/06/2021.
//  Copyright © 2021 Yanis Bakhtaoui. All rights reserved.
//

#ifndef game_h
#define game_h

#include <iostream>
#include <vector>
using namespace std;

class Tree;

class Card{
    private :
    int num;
    int nbr_heads;
    float policy;
    float polp;
    int nbr_win;
    int nbr_simu;
    public :
    Card();
    Card(int,float policy = 0.);
    void Display();
    int Give_num();
    int Give_nbr_heads();
    void incr_simu();
    void incr_win();
    void add_polp(float);
    void update_polp(float, float);
    float get_policy();
    void update_policy();
    void update_policy_mast();
    Card &operator = (const Card &);
    bool operator == (const Card &);
};

struct boolcard{
    bool verif;
    Card card[5];
    int Sum();
};

class Column{
    private:
    int num_col;
    Card tab[5];
    public:
    Column();
    Column(int);
    int Sum();
    int Give_max();
    void Display();
    boolcard Reset(Card &);
    boolcard Add(Card &);
    Column &operator = (const Column &);

};

class Board{
    private:
    Column cols[4];
    public:
    Board();
    Board(Card[4]);
    void Display();
    void sort_Cols();
    boolcard Add(Card &); //true if we added it, false otherwise
    Board &operator = (const Board &);
};

class Player{
    private:
    string nom;
    int score;
    vector <Card> hand;
    int nbr_Cards;
    public:
    Player();
    Player(string,vector<Card>);
    Card Play(int);
    Card give_Card(int);
    void Add_Points(boolcard);
    int Get_Points();
    void Display_Hand();
    int Number_Cards();
    int get_pos_card(Card);
    string Display_Name();
    int Game_alea();
    Player &operator = (const Player &);
};

class Playout{
    private:
    Player player1;
    Player player2;
    Board board;
    vector <int> already_played1;
    vector <int> already_played2;
    public:
    Playout();
    Playout get_current();
    void Round();
    int Game();
    int Game_No_text();
    Playout &operator = (const Playout &);
    Playout change_player(int player = 1);
    void Round_MC(int, int player = 1);
    void Round_MC_MC(int,int);
    int Game_MC(int n = 200, int player = 1);
    int Full_Game_MC(int n = 200, int player = 1);
    int Game_UCB(int n = 1000, float c = 0.4);
    void Round_one_card(int);
    void Round_two_cards(int,int);
    int Full_Game_MC_UCB();
    Player get_player1();
    Player get_player2();
    Board get_board();
    void Display();
    int Game_MCTS(int n = 1000, float c = 1.8, int player = 1);
    int Full_Game_MCTS(int n = 1000, float c = 1.8);
    int Full_Game_MCTS_MC(int,int);
    int Game_PPA(int n = 1000, float c = 1.8, float alpha = 0.4, float pol = 0.6, int player = 1);
    int Full_Game_PPA(int n = 1000, float c = 1.8, float alpha = 0.4, float pol = 0.6);
    int Game_PPA_no_depth(int n = 1000, float c = 1.8, float alpha = 0.4, float pol = 0.6, int player = 1);
    int Full_Game_PPA_no_depth(int n = 1000, float c = 1.8, float alpha = 0.4, float pol = 0.6);
    int Game_MAST(int n = 1000, float c = 1.8, float k = 3.5, float pol = 0., int player = 1);
    int Full_Game_MAST(int n = 1000, float c = 1.8, float k = 3.5, float pol = 0.);
    int Game_MAST_no_depth(int n = 1000, float c = 1.8, float k = 3.5, float pol = 0., int player = 1);
    int Full_Game_MAST_no_depth(int n = 1000, float c = 1.8, float k = 3.5, float pol = 0.);
    int Full_Game_PPA_vs_Flat(int simu1 = 1000, int simu2 = 200, float pol = 0.6);
    int Full_Game_Flat_vs_MAST(int simu1 = 200, int simu2 = 1000, float pol = 0.);
    int Full_Game_MAST_vs_MAST(int simu1 = 1000, int simu2 = 1000, float pol = 0.);
    int Full_Game_PPA_vs_MAST(int simu1 = 1000, int simu2 = 1000, float pol_mast = 0., float pol_ppa = 0.6);
    int Full_Game_MCTS_vs_MAST(int simu1 = 1000, int simu2 = 1000, float pol = 0.);
    int Full_Game_Flat_vs_MCTS(int simu1 = 200, int simu2 = 1000);
    int Full_Game_MCTS_vs_MCTS(int simu1 = 1000, int simu2 = 1000);
    int Full_Game_PPAn_vs_MAST(int simu1 = 1000, int simu2 = 1000, float pol_mast = 0., float pol_ppa = 0.6);
    int Full_Game_MASTn_vs_MAST(int simu1 = 1000, int simu2 = 1000, float pol = 0.);
};


#endif /* game_h */
