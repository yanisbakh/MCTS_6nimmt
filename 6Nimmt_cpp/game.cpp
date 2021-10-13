//
//  game.cpp
//  stage_MC
//
//  Created by Yanis Bakhtaoui on 08/06/2021.
//  Copyright © 2021 Yanis Bakhtaoui. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime> 
#include "game.h"
#include "MCTS.h"

Card::Card(){
    this->num = 0;
    this->nbr_heads=0;
    this->policy=0.;
    this->polp = 0.;
    this->nbr_win=0;
    this->nbr_simu=0;
}

Card::Card(int num, float policy){
    this->num = num;
    this->policy=policy;
    this->polp = 0.;
    this->nbr_win=0;
    this->nbr_simu=0;
    int mod;
    mod = num % 10;
    switch(mod){
        case 0:
            this->nbr_heads = 3;
            break;
        case 5 :
            this->nbr_heads = 2;
            if(num == 55){
                this->nbr_heads = 7;
            }
            break;
        default:
            if(num % 11 == 0){
                this->nbr_heads = 5;
            }
            else{
                this->nbr_heads = 1;
            }
            break;
    }
}

void Card::Display(){
    cout << "--------------------------"<<endl;
    cout << "Number of the card : " << this->num << endl;
    cout << "Number of bull heads : " << this->nbr_heads << endl;
}

int Card::Give_num(){
    return this->num;
}

int Card::Give_nbr_heads(){
    return this->nbr_heads;
}

void Card::incr_win(){
    this->nbr_win++;
}

void Card::incr_simu(){
    this->nbr_simu++;
}

void Card::add_polp(float alpha){
    this->polp = this->polp + alpha;
}

void Card::update_polp(float alpha, float z){
    this->polp = this->polp - alpha * (float(exp(this->policy)/z));
}

float Card::get_policy(){
    return this->policy;
}

void Card::update_policy(){
    this->policy = this->polp;
}

void Card::update_policy_mast(){
    this->policy = float(this->nbr_win)/this->nbr_simu;
}

Card & Card :: operator=(const Card &card){
    this->nbr_heads = card.nbr_heads;
    this->num = card.num;
    return *this;
}

bool Card :: operator==(const Card &card){
    if(this->num == card.num){
        return true;
    }
    else{
        return false;
    }
}

int boolcard::Sum(){
    int sum = 0;
    for(int i = 0 ; i < 5 ; i++){
        sum += this->card[i].Give_nbr_heads();
    }
    return sum;
}

Column::Column(){
}

Column::Column(int i){
    this->num_col = i;
}

int Column::Sum(){
    int sum = 0;
    for(int i = 0 ; i < 5 ; i++){
        sum += this->tab[i].Give_nbr_heads();
    }
    return sum;
}

int Column::Give_max(){
    int maxim = 0;
    for(int i = 0 ; i < 5 ; i++){
        maxim = max(maxim,tab[i].Give_num());
    }
    return maxim;
}


void Column::Display(){
    cout << "The column n° " << this->num_col << " includes the cards : "<< endl;
    for(int i = 0 ; i < 5 ; i++){
        if(this->tab[i].Give_num() != 0){
            tab[i].Display();
        }
    }
}

boolcard Column::Reset(Card &card){
    Card empty;
    boolcard ver;
    ver.verif = false;
    ver.card[0] = this->tab[0];
    this->tab[0] = card;
    for(int i = 1; i < 5 ; i++){
        ver.card[i] = this->tab[i];
        this->tab[i] = empty;
    }
    cout << "The column has been reseted"<<endl;
    this->Display();
    return ver;
}


boolcard Column::Add(Card &card){
    Card empty;
    boolcard ver;
    ver.card[0] = empty;
    ver.card[1] = empty;
    ver.card[2] = empty;
    ver.card[3] = empty;
    ver.card[4] = empty;
    if(this->tab[4].Give_num()!=0){
        ver.card[0] = tab[0];
        ver.card[1] = tab[1];
        ver.card[2] = tab[2];
        ver.card[3] = tab[3];
        ver.card[4] = tab[4];
        this->Reset(card);
        ver.verif = false;
        return ver;
    }
    else{
        int pos = 0;
        while(this->tab[pos].Give_num()!=0){
            pos++;
        }
        tab[pos] = card;
        ver.verif = true;
        return ver;
    }
}

Column & Column :: operator=(const Column &col){
    this->num_col = col.num_col;
    for(int i = 0 ; i < 5 ; i++){
        this->tab[i] = col.tab[i];
    }
    return *this;
}

Board::Board(){
    for(int i = 0 ; i < 4 ; i++){
        this->cols[i] = Column(i+1);
    }
}

Board::Board(Card init[4]){
    for(int i = 0 ; i < 4 ; i++){
        this->cols[i] = Column(i+1);
        this->cols[i].Add(init[i]);
    }
}

void Board::Display(){
    cout << "\nThe board is : " << endl;
    for(int i = 0 ; i < 4 ; i++){
        cout << "\n**********************************" << endl;
        this->cols[i].Display();
    }
}

void Board::sort_Cols(){
    vector <Column> new_col;
    vector <int> max_elements;
    int pos;
    for(int i = 0 ; i < 4 ; i++){
        max_elements.push_back(this->cols[i].Give_max());
    }
    for(int j = 0 ; j < 4 ; j++){
        pos = min_element(max_elements.begin(),max_elements.end()) - max_elements.begin();
        new_col.push_back(this->cols[pos]);
        max_elements.erase(max_elements.begin()+pos);
    }
    for(int k = 0 ; k < 4 ; k++){
        this->cols[k] = new_col[k];
    }
    
}

boolcard Board::Add(Card & card){
    int num = card.Give_num();
    boolcard ver;
    ver.verif = false;
    Card empty;
    ver.card[0] = empty;
    ver.card[1] = empty;
    ver.card[2] = empty;
    ver.card[3] = empty;
    ver.card[4] = empty;
    if(num < this->cols[0].Give_max()){
        vector<int> vec;
        vec.push_back(this->cols[0].Sum());
        vec.push_back(this->cols[1].Sum());
        vec.push_back(this->cols[2].Sum());
        vec.push_back(this->cols[3].Sum());
        int pos = min_element(vec.begin(),vec.end()) - vec.begin();
        this->cols[pos].Display();
        ver = this->cols[pos].Reset(card);
        this->sort_Cols();
        return ver;
    }
    else if(num > this->cols[0].Give_max() & num < this->cols[1].Give_max()){
        ver = this->cols[0].Add(card);
        return ver;
    }
    else if(num > this->cols[1].Give_max() & num < this->cols[2].Give_max()){
        ver = this->cols[1].Add(card);
        return ver;
    }
    else if(num > this->cols[2].Give_max() & num < this->cols[3].Give_max()){
        ver = this->cols[2].Add(card);
        return ver;
    }
    else{
        ver = this->cols[3].Add(card);
        return ver;
    }
}


Board & Board :: operator=(const Board &board){
    for(int i = 0 ; i < 4 ; i++){
        this->cols[i] = board.cols[i];
    }
    return *this;
}

Player::Player(){
    this->nom = "";
    this->score = 0;
    this->nbr_Cards = 10;
    Card empty;
    for(int i = 0 ; i < 10 ; i++){
        this->hand.push_back(empty);
    }
}

Player::Player(string nom, vector <Card> init){
    this->nom = nom;
    this->score = 0;
    this->nbr_Cards = 10;
    this->hand = init;
}

Card Player::Play(int pos){
    Card played;
    Card empty;
    played = this->hand[pos];
    this->hand.erase(this->hand.begin() + pos);
    this->nbr_Cards--;
    return played;
}

Card Player::give_Card(int pos){
    Card played;
    played = this->hand[pos];
    return played;
}

void Player::Add_Points(boolcard ver){
    int sum;
    if(ver.verif==false){
        sum = ver.Sum();
        cout << "The player " << this->nom << " takes " << sum << " points." << endl;
        this->score += sum;
        cout << "He now has " << this->score << " points." << endl;
    }
}

int Player::Get_Points(){
    return this->score;
}

void Player::Display_Hand(){
    cout << "\n**********************************" << endl;
    cout << "Player " << this->nom << "'s hand is : "<<endl;
    for(int i = 0 ; i < this->nbr_Cards ; i++){
        this->hand[i].Display();
    }
}

int Player::Number_Cards(){
    return this->nbr_Cards;
}

int Player::get_pos_card(Card card){
    int pos=-1;
    for(int i = 0 ; i < this->nbr_Cards ; i++){
        if(card == this->hand[i]){
            pos = i;
        }
    }
    return pos;
}

string Player::Display_Name(){
    return this->nom;
}

int Player::Game_alea(){
    int pos_played_card;
    pos_played_card = rand() % this->nbr_Cards ;
    return pos_played_card;
}

Player & Player :: operator=(const Player &player){
    this->nom = player.nom;
    this->score = player.score;
    this->nbr_Cards = player.nbr_Cards;
    this->hand = player.hand;
    return *this;
}


Playout::Playout(){
    int deck[24];
    for(int i = 0 ; i < 24 ; i++){
        deck[i] = i+1;
    }
    vector<int> tab(deck, deck + sizeof(deck) / sizeof(int) );
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine e(seed);
    shuffle(tab.begin(), tab.end(),e);
    vector <Card> hand1;
    vector <Card> hand2;
    vector<int> pile;
    for(int i = 0 ; i < 10 ; i++){
        hand1.push_back(Card(tab[i]));
        hand2.push_back(Card(tab[10+i]));
    }
    pile.push_back(tab[20]);
    pile.push_back(tab[21]);
    pile.push_back(tab[22]);
    pile.push_back(tab[23]);
    sort(pile.begin(),pile.end());
    Card pilecol[4];
    for(int i = 0 ; i < 4 ; i++){
        pilecol[i] = Card(pile[i]);
    }
    Board newboard(pilecol);
    this->board = newboard;
    Player j1("Player 1", hand1);
    Player j2("Player 2", hand2);
    this->player1 = j1;
    this->player2 = j2;
}


Playout Playout::get_current(){
    Playout copy;
    copy.player1 = this->player1;
    copy.player2 = this->player2;
    copy.board = this->board;
    copy.already_played1 = this->already_played1;
    copy.already_played2 = this->already_played2;
    return copy;
}

void Playout::Round(){
    cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\nWe are at the round n° " << 11 - this->player1.Number_Cards() << endl;
    cout << "The player " << this->player1.Display_Name() << " has " << this->player1.Get_Points() << " points." << endl;
    cout << "The player " << this->player2.Display_Name() << " has " << this->player2.Get_Points() << " points." << endl;
    this->player1.Display_Hand();
    this->player2.Display_Hand();
    this->board.Display();
    int pos_played_card1;
    int pos_played_card2;
    pos_played_card1 = this->player1.Game_alea();
    pos_played_card2 = this->player2.Game_alea();
    cout << "\nplayer 1 plays : " << pos_played_card1 << " and player2 plays " << pos_played_card2 << endl;
    Card Card_played1;
    Card Card_played2;
    Card_played1 = this->player1.Play(pos_played_card1);
    Card_played2 = this->player2.Play(pos_played_card2);
    Card_played1.Display();
    Card_played2.Display();
    boolcard verif;
    if(Card_played1.Give_num()>Card_played2.Give_num()){
        verif = this->board.Add(Card_played2);
        this->player2.Add_Points(verif);
        verif = this->board.Add(Card_played1);
        this->player1.Add_Points(verif);
    }
    else{
        verif = this->board.Add(Card_played1);
        this->player1.Add_Points(verif);
        verif = this->board.Add(Card_played2);
        this->player2.Add_Points(verif);
    }
}

int Playout::Game(){
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        this->Round();
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}

int Playout::Game_No_text(){
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        this->Round();
    }
    if(this->player1.Get_Points() < player2.Get_Points()){
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        return 0;
    }
    else{
        return 0.5;
    }
}


Playout & Playout :: operator=(const Playout &playout){
    this->player1 = playout.player1;
    this->player2 = playout.player2;
    this->board = playout.board;
    this->already_played1 = playout.already_played1;
    this->already_played2 = playout.already_played2;
    return *this;
}

Playout Playout::change_player(int player){
    Playout modif;
    if(player==2){
        modif.player1 = this->player2;
        modif.player2 = this->player1;
        modif.board = this->board;
        modif.already_played1 = this->already_played2;
        modif.already_played2 = this->already_played1;
    }
    else{
        modif = get_current();
    }
    return modif;
}

void Playout::Round_MC(int card, int player){
    cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\nWe are at the round n° " << 11 - this->player1.Number_Cards() << endl;
    cout << "The player " << this->player1.Display_Name() << " has " << this->player1.Get_Points() << " points." << endl;
    cout << "The player " << this->player2.Display_Name() << " has " << this->player2.Get_Points() << " points." << endl;
    this->player1.Display_Hand();
    this->player2.Display_Hand();
    this->board.Display();
    int pos_played_card2;
    if(player==1){
        pos_played_card2 = this->player2.Game_alea();
    }
    else{
        pos_played_card2 = this->player1.Game_alea();
    }
    cout << "\nThe player2 plays " << pos_played_card2 << endl;
    Card Card_played1;
    Card Card_played2;
    if(player==1){
        Card_played1 = this->player1.Play(card);
        Card_played2 = this->player2.Play(pos_played_card2);
    }
    else{
        Card_played2 = this->player2.Play(card);
        Card_played1 = this->player1.Play(pos_played_card2);
    }
    Card_played1.Display();
    Card_played2.Display();
    boolcard verif;
    if(Card_played1.Give_num()>Card_played2.Give_num()){
        verif = this->board.Add(Card_played2);
        this->player2.Add_Points(verif);
        verif = this->board.Add(Card_played1);
        this->player1.Add_Points(verif);
    }
    else{
        verif = this->board.Add(Card_played1);
        this->player1.Add_Points(verif);
        verif = this->board.Add(Card_played2);
        this->player2.Add_Points(verif);
    }
}





int Playout::Game_MC(int n, int player){ // if player = 1, we play with the player 1
    streambuf* orig_buf = cout.rdbuf();
    int pos_played_card;
    int nbr = this->player1.Number_Cards();
    Playout recopie;
    recopie = this->get_current().change_player(player);
    vector <float> odds;
    int sum;
    bool repet[n];
    for(int i = 0 ; i < nbr ; i++){
        cout.rdbuf(NULL);
        sum = 0;
        for(int p = 0 ; p < n ; p++){
            recopie = this->get_current().change_player(player);
            recopie.Round_MC(i);
            repet[p] = recopie.Game_No_text();
            cout << repet[p];
            if(repet[p] == true){
                sum++;
            }
        }
        cout << "Playing the card " << i <<", we have " << sum << endl;
        odds.push_back(float(sum) / n * 100);
        cout << "Playing the card " << i <<", we have " << odds[i] << "% odds"<<endl;
    }
    cout.rdbuf(orig_buf);
    for(int i = 0 ; i < odds.size() ; i++){
        cout << "prob : " << odds[i] << "%" << endl;
    }
    pos_played_card = max_element(odds.begin(),odds.end()) - odds.begin();
    cout << "we play " << pos_played_card << endl;
    return pos_played_card;
}

int Playout::Full_Game_MC(int n, int player){
    int pos;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos = this->Game_MC(n,player);
        this->Round_MC(pos);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}

void Playout::Round_one_card(int card){
    int pos_played_card2;
    pos_played_card2 = this->player2.Game_alea();
    Card Card_played1;
    Card Card_played2;
    Card_played1 = this->player1.Play(card);
    Card_played2 = this->player2.Play(pos_played_card2);
    boolcard verif;
    if(Card_played1.Give_num()>Card_played2.Give_num()){
        verif = this->board.Add(Card_played2);
        this->player2.Add_Points(verif);
        verif = this->board.Add(Card_played1);
        this->player1.Add_Points(verif);
    }
    else{
        verif = this->board.Add(Card_played1);
        this->player1.Add_Points(verif);
        verif = this->board.Add(Card_played2);
        this->player2.Add_Points(verif);
    }
}

int Playout::Game_UCB(int n, float c){
    streambuf* orig_buf = cout.rdbuf();
    int pos_played_card;
    int nbr = this->player2.Number_Cards();
    Playout recopie;
    vector <int> nbr_simu;
    vector <int> nbr_win;
    for(int t = 0 ; t < nbr ; t++){
        nbr_simu.push_back(1);
        nbr_win.push_back(1);
    }
    bool verif;
    vector <float> value;
    int pos;
    cout.rdbuf(NULL);
    for(int k = 0 ; k < nbr ; k++){
        recopie = this->get_current();
        recopie.Round_one_card(k);
        verif = recopie.Game_No_text();
        nbr_simu[k]++;
        if(verif == false){
            nbr_win[k]++;
        }
    }
    for(int i = nbr ; i < n ; i++){
        value = {};
        for(int j = 0 ; j < nbr ; j++){
            value.push_back(float(nbr_win[j])/nbr_simu[j] + c*sqrt(log(i)/nbr_simu[j]));
        }
        pos =  max_element(value.begin(),value.end()) - value.begin();
        recopie = this->get_current();
        recopie.Round_one_card(pos);
        verif = recopie.Game_No_text();
        nbr_simu[pos]++;
        if(verif == false){
            nbr_win[pos]++;
        }
    }
    cout.rdbuf(orig_buf);
    for(int k = 0 ; k < nbr ; k++){
        cout << " The position " << k << " has been explored " << nbr_simu[k] << "and won " << nbr_win[k] << " times." << endl;
    }
    pos_played_card =  max_element(nbr_simu.begin(),nbr_simu.end()) - nbr_simu.begin();
    cout << "We play the card " << pos_played_card << endl;
    return pos_played_card;
}

void Playout::Round_two_cards(int card1, int card2){
    Card Card_played1;
    Card Card_played2;
    Card_played1 = this->player1.Play(card1);
    Card_played2 = this->player2.Play(card2);
    boolcard verif;
    if(Card_played1.Give_num()>Card_played2.Give_num()){
        verif = this->board.Add(Card_played2);
        this->player2.Add_Points(verif);
        verif = this->board.Add(Card_played1);
        this->player1.Add_Points(verif);
    }
    else{
        verif = this->board.Add(Card_played1);
        this->player1.Add_Points(verif);
        verif = this->board.Add(Card_played2);
        this->player2.Add_Points(verif);
    }
}

int Playout::Full_Game_MC_UCB(){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_MC();
        pos2 = this->Game_UCB();
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}

Player Playout::get_player1(){
    return player1;
}

Player Playout::get_player2(){
    return player2;
}

Board Playout::get_board(){
    return board;
}

void Playout::Display(){
    this->board.Display();
}



int Playout::Game_MCTS(int n, float c, int player){
    Tree tree(this->get_current().change_player(player));
    int pos_played = 0;
    int pos_hand;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    for(int k = 0 ; k < n ; k++){
        tree.exploration(c);
        tree.backprop();
    }
    cout.rdbuf(orig_buf);
    vector <double> values = {};
    vector <Node*> son_node = tree.get_road()[0]->get_son();
    if(son_node.size()==0){
        pos_hand = 0;
    }
    else{
        for(int i = 0; i < son_node.size() ; i++){
            values.push_back(son_node[i]->get_nbr_simu());
            cout << "pos " << i << " value : "  << son_node[i]->get_nbr_simu() << endl;
        }
        pos_played = max_element(values.begin(),values.end()) - values.begin();
        pos_hand = tree.get_playout().get_player1().get_pos_card(son_node[pos_played]->get_Card_played());
        
    }
    cout << "With MCTS we play " << pos_hand << endl;
    return pos_hand;
}



int Playout::Full_Game_MCTS(int n, float c){
    int pos;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos = this->Game_MCTS(n,c);
        this->Round_one_card(pos);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}


int Playout::Full_Game_MCTS_MC(int simu1, int simu2){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_MCTS(simu1);
        pos2 = this->Game_MC(simu2,2);
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}

int Playout::Game_PPA(int n, float c, float alpha, float pol, int player){
    Tree tree(this->get_current().change_player(player));
    int pos_played = 0;
    int pos_hand;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    for(int k = 0 ; k < n ; k++){
        cout << k << endl;
        tree.exploration(c);
        tree.backprop_PPA(alpha);
    }
    cout.rdbuf(orig_buf);
    vector <double> values = {};
    vector <Node*> son_node = tree.get_road()[0]->get_son();
    vector <float> weights;
    random_device generator;
    mt19937 gen(generator());
    if(son_node.size()==0){
        pos_hand = 0;
    }
    else{
        vector <double> values = {};
        vector <Node*> son_node = tree.get_road()[0]->get_son();
        if(son_node.size()==0){
            pos_hand = 0;
        }
        else{
            for(int i = 0; i < son_node.size() ; i++){
                values.push_back(son_node[i]->get_nbr_simu());
                cout << "pos " << i << " value : "  << son_node[i]->get_nbr_simu() << endl;
            }
            pos_played = max_element(values.begin(),values.end()) - values.begin();
            pos_hand = tree.get_playout().get_player1().get_pos_card(son_node[pos_played]->get_Card_played());
            
        }
    }
    cout << "With PPA we play " << pos_hand << endl;
    return pos_hand;
}


int Playout::Full_Game_PPA(int n, float c, float alpha, float pol){
    int pos;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos = this->Game_PPA(n, c, alpha, pol, 1);
        this->Round_one_card(pos);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}

int Playout::Game_PPA_no_depth(int n, float c, float alpha, float pol, int player){
    Tree tree(this->get_current().change_player(player));
    int pos_played = 0;
    int pos_hand;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    for(int k = 0 ; k < n ; k++){
        tree.exploration(c);
        tree.backprop_PPA_no_depth(alpha);
    }
    cout.rdbuf(orig_buf);
    vector <double> values = {};
    vector <Node*> son_node = tree.get_road()[0]->get_son();
    vector <float> weights;
    random_device generator;
    mt19937 gen(generator());
    if(son_node.size()==0){
        pos_hand = 0;
    }
    else{
        vector <double> values = {};
        vector <Node*> son_node = tree.get_road()[0]->get_son();
        if(son_node.size()==0){
            pos_hand = 0;
        }
        else{
            for(int i = 0; i < son_node.size() ; i++){
                values.push_back(son_node[i]->get_nbr_simu());
                cout << "pos " << i << " value : "  << son_node[i]->get_nbr_simu() << endl;
            }
            pos_played = max_element(values.begin(),values.end()) - values.begin();
            pos_hand = tree.get_playout().get_player1().get_pos_card(son_node[pos_played]->get_Card_played());
            
        }
    }
    cout << "With PPA we play " << pos_hand << endl;
    return pos_hand;
}


int Playout::Full_Game_PPA_no_depth(int n, float c, float alpha, float pol){
    int pos;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos = this->Game_PPA_no_depth(n, c, alpha, pol, 1);
        this->Round_one_card(pos);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}




int Playout::Game_MAST(int n, float c, float k, float pol, int player){
    Tree tree(this->get_current().change_player(player));
    int pos_played = 0;
    int pos_hand;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    for(int j = 0 ; j < n ; j++){
        cout << j << endl;
        tree.exploration(c);
        tree.backprop_MAST(k);
    }
    cout.rdbuf(orig_buf);
    vector <double> values = {};
    vector <Node*> son_node = tree.get_road()[0]->get_son();
    vector <float> weights;
    random_device generator;
    mt19937 gen(generator());
    if(son_node.size()==0){
        pos_hand = 0;
    }
    else{
        vector <double> values = {};
        vector <Node*> son_node = tree.get_road()[0]->get_son();
        if(son_node.size()==0){
            pos_hand = 0;
        }
        else{
            for(int i = 0; i < son_node.size() ; i++){
                cout << "Number : " << i <<  " Value : " << son_node[i]->get_nbr_simu() << endl;
                values.push_back(son_node[i]->get_nbr_simu());
            }
            pos_played = max_element(values.begin(),values.end()) - values.begin();
            pos_hand = tree.get_playout().get_player1().get_pos_card(son_node[pos_played]->get_Card_played());
            
        }
    }
    return pos_hand;
}


int Playout::Full_Game_MAST(int n, float c, float k, float pol){
    int pos;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos = this->Game_MAST(n,c,k,pol,1);
        cout << "on est a la fin, la carte est " << pos << endl;
        this->Round_one_card(pos);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}

int Playout::Game_MAST_no_depth(int n, float c, float k, float pol, int player){
    Tree tree(this->get_current().change_player(player));
    int pos_played = 0;
    int pos_hand;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    for(int j = 0 ; j < n ; j++){
        cout << j << endl;
        tree.exploration(c);
        tree.backprop_MAST_no_depth(k);
    }
    cout.rdbuf(orig_buf);
    vector <double> values = {};
    vector <Node*> son_node = tree.get_road()[0]->get_son();
    vector <float> weights;
    random_device generator;
    mt19937 gen(generator());
    if(son_node.size()==0){
        pos_hand = 0;
    }
    else{
        vector <double> values = {};
        vector <Node*> son_node = tree.get_road()[0]->get_son();
        if(son_node.size()==0){
            pos_hand = 0;
        }
        else{
            for(int i = 0; i < son_node.size() ; i++){
                cout << "Number : " << i <<  " Value : " << son_node[i]->get_nbr_simu() << endl;
                values.push_back(son_node[i]->get_nbr_simu());
            }
            pos_played = max_element(values.begin(),values.end()) - values.begin();
            pos_hand = tree.get_playout().get_player1().get_pos_card(son_node[pos_played]->get_Card_played());
            
        }
    }
    return pos_hand;
}


int Playout::Full_Game_MAST_no_depth(int n, float c, float k, float pol){
    int pos;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos = this->Game_MAST_no_depth(n,c,k,pol,1);
        this->Round_one_card(pos);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}


int Playout::Full_Game_PPA_vs_Flat(int simu1, int simu2, float pol){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_PPA();
        pos2 = this->Game_MC(simu2,2);
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}


int Playout::Full_Game_Flat_vs_MAST(int simu1, int simu2, float pol){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_MC(simu1,1);
        pos2 = this->Game_MAST(simu2,1.8, 3.5, pol,2);
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}


int Playout::Full_Game_MAST_vs_MAST(int simu1, int simu2, float pol){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_MAST(simu1, 1.8, 3.5, pol, 1);
        pos2 = this->Game_MAST(simu2, 1.8, 3.5, pol, 2);
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}


int Playout::Full_Game_PPA_vs_MAST(int simu1, int simu2, float pol_mast, float pol_ppa){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_PPA(simu1,1.8, 0.4, pol_ppa,1);
        pos2 = this->Game_MAST(simu2, 1.8, 3.5, pol_mast, 2);
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}

int Playout::Full_Game_MCTS_vs_MAST(int simu1, int simu2, float pol){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_MCTS(simu1, 1.8, 1);
        pos2 = this->Game_MAST(simu2, 1.8, 3.5, pol, 2);
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}

int Playout::Full_Game_Flat_vs_MCTS(int simu1, int simu2){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_MC(simu1, 1);
        pos2 = this->Game_MCTS(simu2, 1.8, 2);
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}


int Playout::Full_Game_MCTS_vs_MCTS(int simu1, int simu2){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_MCTS(simu1, 1.8);
        pos2 = this->Game_MCTS(simu2, 1.8, 2);
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}

int Playout::Full_Game_PPAn_vs_MAST(int simu1, int simu2, float pol_mast, float pol_ppa){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_PPA_no_depth(simu1,1.8, 0.4, pol_ppa,1);
        pos2 = this->Game_MAST(simu2, 1.8, 3.5, pol_mast, 2);
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}

int Playout::Full_Game_MASTn_vs_MAST(int simu1, int simu2, float pol){
    int pos1;
    int pos2;
    while(( this->player1.Number_Cards()>0 ) & ( this->player1.Get_Points() < 66 ) & ( this->player2.Get_Points() < 66) ){
        pos1 = this->Game_MAST_no_depth(simu1,1.8, 3.5, pol,1);
        pos2 = this->Game_MAST(simu2, 1.8, 3.5, pol, 2);
        this->Round_two_cards(pos1, pos2);
    }
    cout << "\n\n\nThe player " << this->player1.Display_Name() << " has " << player1.Get_Points() << " points"<< endl;
    cout << "\n\n\nThe player " << this->player2.Display_Name() << " has " << player2.Get_Points() << " points"<< endl;
    if(this->player1.Get_Points() < player2.Get_Points()){
        cout <<"\n**************************\nThe player " << this->player1.Display_Name() << " won" << endl;
        return 1;
    }
    else if (this->player1.Get_Points() > player2.Get_Points()){
        cout << "\n\n\n**************************\nThe player " << this->player2.Display_Name() << " won" << endl;
        return 0;
    }
    else{
        cout << "\n\n\n**************************\nEquality" << endl;
        return 0.5;
    }
}
