//
//  Tests.cpp
//  stage_MC
//
//  Created by Yanis Bakhtaoui on 13/07/2021.
//  Copyright © 2021 Yanis Bakhtaoui. All rights reserved.
//

#include "Tests.h"
#include <chrono>
#include <random>


void test_MC_Flat(){
    Playout testgame;
    Playout copy100;
    Playout copy200;
    Playout copy500;
    Playout copy1000;
    copy100 = testgame;
    copy200 = testgame;
    copy500 = testgame;
    copy1000 = testgame;
    streambuf* orig_buf = cout.rdbuf();
    int nb_win100 = 0;
    int nb_win200 = 0;
    int nb_win500 = 0;
    int nb_win1000 = 0;
    int verif100;
    int verif200;
    int verif500;
    int verif1000;
    cout.rdbuf(NULL);
    auto start100 = std::chrono::high_resolution_clock::now();
    verif100 = copy100.Full_Game_MC(100);
    auto stop100 = std::chrono::high_resolution_clock::now();
    auto duration100 = std::chrono::duration_cast<std::chrono::microseconds>(stop100 - start100);
    cout.rdbuf(orig_buf);
    cout << "Duration MC flat with 100 simulations : " << duration100.count() << endl;
    cout.rdbuf(NULL);
    auto start200 = std::chrono::high_resolution_clock::now();
    verif200 = copy200.Full_Game_MC(200);
    auto stop200 = std::chrono::high_resolution_clock::now();
    auto duration200 = std::chrono::duration_cast<std::chrono::microseconds>(stop200 - start200);
    cout.rdbuf(orig_buf);
    cout << "Duration MC flat with 200 simulations : " << duration200.count() << endl;
    cout.rdbuf(NULL);
    auto start500 = std::chrono::high_resolution_clock::now();
    verif500 = copy500.Full_Game_MC(500);
    auto stop500 = std::chrono::high_resolution_clock::now();
    auto duration500 = std::chrono::duration_cast<std::chrono::microseconds>(stop500 - start500);
    cout.rdbuf(orig_buf);
    cout << "Duration MC flat with 500 simulations : " << duration500.count() << endl;
    cout.rdbuf(NULL);
    auto start1000 = std::chrono::high_resolution_clock::now();
    verif1000 = copy1000.Full_Game_MC(1000);
    auto stop1000 = std::chrono::high_resolution_clock::now();
    auto duration1000 = std::chrono::duration_cast<std::chrono::microseconds>(stop1000 - start1000);
    cout.rdbuf(orig_buf);
    cout << "Duration MC flat with 1000 simulations : " << duration1000.count() << endl;
    for(int i = 0 ; i < 500 ; i++){
            cout.rdbuf(NULL);
            testgame = Playout();
            copy100 = testgame;
            copy200 = testgame;
            copy500 = testgame;
            copy1000 = testgame;
            verif100 = copy100.Full_Game_MC(100);
            verif200 = copy200.Full_Game_MC(200);
            verif500 = copy500.Full_Game_MC(500);
            verif1000 = copy1000.Full_Game_MC(1000);
            while(verif100 == 0.5 & verif200 == 0.5 & verif500 == 0.5 & verif1000 == 0.5){
                testgame = Playout();
                copy100 = testgame;
                copy200 = testgame;
                copy500 = testgame;
                copy1000 = testgame;
                verif100 = copy100.Full_Game_MC(100);
                verif200 = copy200.Full_Game_MC(200);
                verif500 = copy500.Full_Game_MC(500);
                verif1000 = copy1000.Full_Game_MC(1000);
            }
            cout.rdbuf(orig_buf);
            cout << i << endl;
            nb_win100+=verif100;
            nb_win200+=verif200;
            nb_win500+=verif500;
            nb_win1000+=verif1000;
        }
    cout << "nb_win MCTS 100 simulations : " << nb_win100 << endl;
    cout << "nb_win MCTS 200 simulations : " << nb_win200 << endl;
    cout << "nb_win MCTS 500 simulations : " << nb_win500 << endl;
    cout << "nb_win MCTS 1000 simulations : " << nb_win1000 << endl;
}

void test_MCTS(){
    Playout testgame;
    Playout copy100;
    Playout copy200;
    Playout copy500;
    Playout copy1000;
    Playout copy1500;
    copy100 = testgame;
    copy200 = testgame;
    copy500 = testgame;
    copy1000 = testgame;
    copy1500 = testgame;
    streambuf* orig_buf = cout.rdbuf();
    int nb_win100 = 0;
    int nb_win200 = 0;
    int nb_win500 = 0;
    int nb_win1000 = 0;
    int nb_win1500 = 0;
    int verif100;
    int verif200;
    int verif500;
    int verif1000;
    int verif1500;
    cout.rdbuf(NULL);
    auto start100 = std::chrono::high_resolution_clock::now();
    verif100 = copy100.Full_Game_MCTS(100);
    auto stop100 = std::chrono::high_resolution_clock::now();
    auto duration100 = std::chrono::duration_cast<std::chrono::microseconds>(stop100 - start100);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with 100 simulations : " << duration100.count() << endl;
    cout.rdbuf(NULL);
    auto start200 = std::chrono::high_resolution_clock::now();
    verif200 = copy200.Full_Game_MCTS(200);
    auto stop200 = std::chrono::high_resolution_clock::now();
    auto duration200 = std::chrono::duration_cast<std::chrono::microseconds>(stop200 - start200);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with 200 simulations : " << duration200.count() << endl;
    cout.rdbuf(NULL);
    auto start500 = std::chrono::high_resolution_clock::now();
    verif500 = copy500.Full_Game_MCTS(500);
    auto stop500 = std::chrono::high_resolution_clock::now();
    auto duration500 = std::chrono::duration_cast<std::chrono::microseconds>(stop500 - start500);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with 500 simulations : " << duration500.count() << endl;
    cout.rdbuf(NULL);
    auto start1000 = std::chrono::high_resolution_clock::now();
    verif1000 = copy1000.Full_Game_MCTS(1000);
    auto stop1000 = std::chrono::high_resolution_clock::now();
    auto duration1000 = std::chrono::duration_cast<std::chrono::microseconds>(stop1000 - start1000);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with 1000 simulations : " << duration1000.count() << endl;
    cout.rdbuf(NULL);
    auto start1500 = std::chrono::high_resolution_clock::now();
    verif1500 = copy1500.Full_Game_MCTS(1500);
    auto stop1500 = std::chrono::high_resolution_clock::now();
    auto duration1500 = std::chrono::duration_cast<std::chrono::microseconds>(stop1500 - start1500);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with 1500 simulations : " << duration1500.count() << endl;
    for(int i = 0 ; i < 500 ; i++){
            cout.rdbuf(NULL);
            testgame = Playout();
            copy100 = testgame;
            copy200 = testgame;
            copy500 = testgame;
            copy1000 = testgame;
            copy1500 = testgame;
            verif100 = copy100.Full_Game_MCTS(100);
            verif200 = copy200.Full_Game_MCTS(200);
            verif500 = copy500.Full_Game_MCTS(500);
            verif1000 = copy1000.Full_Game_MCTS(1000);
            verif1500 = copy1500.Full_Game_MCTS(1500);
            while(verif100 == 0.5 & verif200 == 0.5 & verif500 == 0.5 & verif1000 == 0.5 & verif1500 == 0.5){
                testgame = Playout();
                copy100 = testgame;
                copy200 = testgame;
                copy500 = testgame;
                copy1000 = testgame;
                copy1500 = testgame;
                verif100 = copy100.Full_Game_MCTS(100);
                verif200 = copy200.Full_Game_MCTS(200);
                verif500 = copy500.Full_Game_MCTS(500);
                verif1000 = copy1000.Full_Game_MCTS(1000);
                verif1500 = copy1500.Full_Game_MCTS(1500);
            }
            cout.rdbuf(orig_buf);
            cout << i << endl;
            nb_win100+=verif100;
            nb_win200+=verif200;
            nb_win500+=verif500;
            nb_win1000+=verif1000;
            nb_win1500+=verif1500;
        }
    cout << "nb_win MCTS 100 simulations : " << nb_win100 << endl;
    cout << "nb_win MCTS 200 simulations : " << nb_win200 << endl;
    cout << "nb_win MCTS 500 simulations : " << nb_win500 << endl;
    cout << "nb_win MCTS 1000 simulations : " << nb_win1000 << endl;
    cout << "nb_win MCTS 1500 simulations : " << nb_win1500 << endl;
}

void test_MCTS_vs_MC(int simu1, int simu2){
    Playout testgame;
    int verif;
    int nb_win = 0;
    streambuf* orig_buf = cout.rdbuf();
    for(int i = 0 ; i < 500 ; i++){
        cout.rdbuf(NULL);
        testgame = Playout();
        verif = testgame.Full_Game_MCTS_MC(simu1,simu2);
        cout.rdbuf(orig_buf);
        cout << i << endl;
        if(verif%1==0){
            nb_win+=verif;
        }
        else{
            cout << "Equality"<<endl;
            i--;
        }
    }
    cout << "nb_win MCTS : " << nb_win << endl;
}


void test_time_MCTS_MC(){
    Playout testgame;
    streambuf* orig_buf = cout.rdbuf();
    int nb_win = 0;
    int nb_win2 = 0;
    int verif;
    int verif2;
    cout.rdbuf(NULL);
    auto start = std::chrono::high_resolution_clock::now();
    verif = testgame.Full_Game_MCTS(1000);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    Playout testgame2;
    auto start2 = std::chrono::high_resolution_clock::now();
    verif2 = testgame2.Full_Game_MC(200);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    cout.rdbuf(orig_buf);
    cout << "MCTS : " << duration.count() << endl;
    cout << "MC flat : " << duration2.count() << endl;
    for(int i = 0 ; i < 500 ; i++){
        cout.rdbuf(NULL);
        testgame = Playout();
        testgame2 = testgame;
        verif = testgame.Full_Game_MCTS(1000);
        verif2 = testgame2.Full_Game_MC(200);
        while(verif==0.5 & verif2==0.5){
            testgame = Playout();
            verif = testgame.Full_Game_MCTS(1000);
            testgame2 = Playout();
            verif2 = testgame.Full_Game_MC(200);
        }
        cout.rdbuf(orig_buf);
        cout << i << endl;
        nb_win+=verif;
        nb_win2+=verif2;
    }
    cout << "nb_win MCTS : " << nb_win << endl;
    cout << "nb_win MC flat : " << nb_win2 << endl;
}

void test_PPA(){
    Playout test;
    int nb_win = 0;
    int verif;
    streambuf* orig_buf = cout.rdbuf();
    //cout.rdbuf(NULL);
    int verif1000;
    auto start1000 = std::chrono::high_resolution_clock::now();
    verif1000 = test.Full_Game_PPA();
    auto stop1000 = std::chrono::high_resolution_clock::now();
    auto duration1000 = std::chrono::duration_cast<std::chrono::microseconds>(stop1000 - start1000);
    cout.rdbuf(orig_buf);
    cout << "Duration PPA with 1000 simulations : " << duration1000.count() << endl;
    for(int i = 0 ; i < 500 ; i++){
        cout << i << endl;
        cout.rdbuf(NULL);
        test = Playout();
        verif = test.Full_Game_PPA();
        nb_win += verif;
        cout.rdbuf(orig_buf);
    }
    cout << "nb win : " << nb_win << endl;
}

void test_PPA_no_depth(){
    Playout test;
    int nb_win = 0;
    int verif;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);
    int verif1000;
    auto start1000 = std::chrono::high_resolution_clock::now();
    verif1000 = test.Full_Game_PPA_no_depth();
    auto stop1000 = std::chrono::high_resolution_clock::now();
    auto duration1000 = std::chrono::duration_cast<std::chrono::microseconds>(stop1000 - start1000);
    cout.rdbuf(orig_buf);
    cout << "Duration PPA with 1000 simulations : " << duration1000.count() << endl;
    for(int i = 0 ; i < 500 ; i++){
        cout << i << endl;
        cout.rdbuf(NULL);
        test = Playout();
        verif = test.Full_Game_PPA_no_depth();
        nb_win += verif;
        cout.rdbuf(orig_buf);
    }
    cout << "nb win : " << nb_win << endl;
}



void test_best_alpha(){
    vector <int> values;
    vector <float> alphas;
    streambuf* orig_buf = cout.rdbuf();
    int nb_win;
    Playout test;
    int verif;
    for(float alpha = 0. ; alpha < 1 ; alpha = alpha + 0.1){
        cout.rdbuf(orig_buf);
        cout << float(alpha) << endl;
        nb_win = 0;
        for(int i = 0 ; i < 500 ; i++){
            cout.rdbuf(orig_buf);
            cout << i << endl;
            cout.rdbuf(NULL);
            test = Playout();
            verif = test.Full_Game_PPA(1000, 1.8,alpha,0.6);
            while(verif == 0.5){
                test = Playout();
                verif = test.Full_Game_PPA(1000, 1.8, alpha,0.6);
            }
            nb_win += verif;
        }
        values.push_back(nb_win);
        alphas.push_back(alpha);
    }
    cout.rdbuf(orig_buf);
    for(int j = 0 ; j < values.size() ; j++){
        cout << "Alpha : " << float(alphas[j]) << " value : " << values[j] << " % : " << float(values[j])/5 << endl;
    }
    int pos = max_element(values.begin(),values.end()) - values.begin();
    cout << "The best alpha is : " << alphas[pos] << endl;
}

void test_MAST(){
    Playout test;
    Playout test2 = test;
    int nb_win = 0;
    int verif;
    int verif2;
    streambuf* orig_buf = cout.rdbuf();
    //cout.rdbuf(NULL);
    int verif1000;
    auto start1000 = std::chrono::high_resolution_clock::now();
    verif1000 = test.Full_Game_MAST(1000, 1.8, 3.5);
    verif2 = test2.Full_Game_MCTS();
    auto stop1000 = std::chrono::high_resolution_clock::now();
    auto duration1000 = std::chrono::duration_cast<std::chrono::microseconds>(stop1000 - start1000);
    cout.rdbuf(orig_buf);
    cout << "Duration MAST with 1000 simulations : " << duration1000.count() << endl;
    for(int i = 0 ; i < 500 ; i++){
        cout << i << endl;
        cout.rdbuf(NULL);
        test = Playout();
        verif = test.Full_Game_MAST(1000, 1.8, 3.5);
        nb_win += verif;
        cout.rdbuf(orig_buf);
    }
    cout << "nb win : " << nb_win << endl;
}


void test_best_k(){
    vector <int> values;
    vector <float> ks;
    streambuf* orig_buf = cout.rdbuf();
    int nb_win;
    Playout test;
    int verif;
    for(float k = 1. ; k < 5.1 ; k = k + 0.5){
        cout.rdbuf(orig_buf);
        cout << float(k) << endl;
        nb_win = 0;
        for(int i = 0 ; i < 500 ; i++){
            cout.rdbuf(orig_buf);
            cout << i << endl;
            cout.rdbuf(NULL);
            test = Playout();
            verif = test.Full_Game_MAST(1000, 1.8, k, 0.);
            while(verif == 0.5){
                test = Playout();
                verif = test.Full_Game_MAST(1000, 1.8, k, 0.);
            }
            nb_win += verif;
        }
        values.push_back(nb_win);
        ks.push_back(k);
    }
    cout.rdbuf(orig_buf);
    for(int j = 0 ; j < values.size() ; j++){
        cout << "k : " << float(ks[j]) << " value : " << values[j]  << " en % : " << float(values[j])/5<< "%" << endl;
    }
    int pos = max_element(values.begin(),values.end()) - values.begin();
    cout << "The best k is : " << ks[pos] << endl;
}

void test_MAST_vs_Flat(int simu1, int simu2){
    Playout testgame;
    int verif;
    int nb_win = 0;
    streambuf* orig_buf = cout.rdbuf();
    for(int i = 0 ; i < 500 ; i++){
        cout.rdbuf(NULL);
        testgame = Playout();
        verif = testgame.Full_Game_Flat_vs_MAST(simu1,simu2,0.);
        cout.rdbuf(orig_buf);
        cout << i << endl;
        if(verif!=0.5){
            nb_win+=verif;
        }
        else{
            cout << "Equality"<<endl;
            i--;
        }
    }
    cout << "nb_win MAST : " << nb_win << endl;
}

void best_c(){
    vector <int> values;
    vector <float> cs;
    streambuf* orig_buf = cout.rdbuf();
    int nb_win;
    Playout test;
    cout.rdbuf(NULL);
    Playout test2;
    Playout test3;
    Playout test4;
    Playout test5;
    Playout test6;
    Playout test7;
    Playout test8;
    Playout test9;
    int verif;
    auto start2 = std::chrono::high_resolution_clock::now();
    verif = test2.Full_Game_MCTS(1000,0.1);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with c = 0,2 : " << duration2.count() << endl;
    cout.rdbuf(NULL);
    auto start3 = std::chrono::high_resolution_clock::now();
    verif = test3.Full_Game_MCTS(1000,0.1);
    auto stop3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with c = 0,3 : " << duration3.count() << endl;
    cout.rdbuf(NULL);
    auto start4 = std::chrono::high_resolution_clock::now();
    verif = test4.Full_Game_MCTS(1000,0.1);
    auto stop4 = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(stop4 - start4);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with c = 0,4 : " << duration4.count() << endl;
    cout.rdbuf(NULL);
    auto start5 = std::chrono::high_resolution_clock::now();
    verif = test5.Full_Game_MCTS(1000,0.1);
    auto stop5 = std::chrono::high_resolution_clock::now();
    auto duration5 = std::chrono::duration_cast<std::chrono::microseconds>(stop5 - start5);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with c = 0,5 : " << duration5.count() << endl;
    cout.rdbuf(NULL);
    auto start6 = std::chrono::high_resolution_clock::now();
    verif = test6.Full_Game_MCTS(1000,0.1);
    auto stop6 = std::chrono::high_resolution_clock::now();
    auto duration6 = std::chrono::duration_cast<std::chrono::microseconds>(stop6 - start6);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with c = 0,6 : " << duration6.count() << endl;
    cout.rdbuf(NULL);
    auto start7 = std::chrono::high_resolution_clock::now();
    verif = test7.Full_Game_MCTS(1000,0.1);
    auto stop7 = std::chrono::high_resolution_clock::now();
    auto duration7 = std::chrono::duration_cast<std::chrono::microseconds>(stop7 - start7);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with c = 0,7 : " << duration7.count() << endl;
    cout.rdbuf(NULL);
    auto start8 = std::chrono::high_resolution_clock::now();
    verif = test8.Full_Game_MCTS(1000,0.1);
    auto stop8 = std::chrono::high_resolution_clock::now();
    auto duration8 = std::chrono::duration_cast<std::chrono::microseconds>(stop8 - start8);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with c = 0,8 : " << duration8.count() << endl;
    cout.rdbuf(NULL);
    auto start9 = std::chrono::high_resolution_clock::now();
    verif = test9.Full_Game_MCTS(1000,0.1);
    auto stop9 = std::chrono::high_resolution_clock::now();
    auto duration9 = std::chrono::duration_cast<std::chrono::microseconds>(stop9 - start9);
    cout.rdbuf(orig_buf);
    cout << "Duration MCTS with c = 0,9 : " << duration9.count() << endl;
    cout.rdbuf(NULL);
    for(float c = 0.1 ; c < 2 ; c = c + 0.1){
        cout.rdbuf(orig_buf);
        cout << float(c) << endl;
        nb_win = 0;
        for(int i = 0 ; i < 500 ; i++){
            cout.rdbuf(orig_buf);
            cout << i << endl;
            cout.rdbuf(NULL);
            test = Playout();
            verif = test.Full_Game_MCTS(1000, c);
            while(verif == 0.5){
                test = Playout();
                verif = test.Full_Game_MCTS(1000, c);
            }
            nb_win += verif;
        }
        values.push_back(nb_win);
        cs.push_back(c);
    }
    cout.rdbuf(orig_buf);
    for(int j = 0 ; j < values.size() ; j++){
        cout << "c : " << float(cs[j]) << " value : " << values[j]  << " en % : " << float(values[j])/5<< "%" << endl;
    }
    int pos = max_element(values.begin(),values.end()) - values.begin();
    cout << "The best c is : " << cs[pos] << endl;
}


void test_MAST_vs_Flat(){
    Playout testgame;
    Playout testgame2;
    int verif;
    int verif2;
    int nb_win_mast = 0;
    int nb_win_flat = 0;
    int nb_total = 0;
    int count = 0;
    streambuf* orig_buf = cout.rdbuf();
    while(nb_total < 500){
        cout.rdbuf(NULL);
        testgame = Playout();
        testgame2 = testgame ;
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif = testgame.Full_Game_Flat_vs_MAST(200,1000,0.);
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif2 = testgame2.Full_Game_MAST_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        if(verif > verif2){
            nb_win_flat ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "flat wins, total : " << nb_total << endl;
        }
        else if(verif2 > verif){
            nb_win_mast ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "mast wins, total : " << nb_total << endl;
        }
        cout.rdbuf(orig_buf);
        count ++;
        cout << "total games : " << count << endl;
    }
    cout << "nb_win MAST : " << nb_win_mast << endl;
    cout << "nb_win Flat : " << nb_win_flat << endl;
}

void test_PPA_vs_Flat(){
    Playout testgame;
    Playout testgame2;
    int verif;
    int verif2;
    int nb_win_ppa = 0;
    int nb_win_flat = 0;
    int nb_total = 0;
    int count = 0;
    streambuf* orig_buf = cout.rdbuf();
    while(nb_total < 500){
        cout.rdbuf(NULL);
        testgame = Playout();
        testgame2 = testgame ;
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif = testgame.Full_Game_Flat_vs_MAST(200,1000,0.);
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif2 = testgame2.Full_Game_PPA_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        if(verif > verif2){
            nb_win_flat ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "flat wins, total : " << nb_total << endl;
        }
        else if(verif2 > verif){
            nb_win_ppa ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "ppa wins, total : " << nb_total << endl;
        }
        cout.rdbuf(orig_buf);
        count ++;
        cout << "total games : " << count << endl;
    }
    cout << "nb_win PPA : " << nb_win_ppa << endl;
    cout << "nb_win Flat : " << nb_win_flat << endl;
}

void test_MCTS_vs_Flat(){
    Playout testgame;
    Playout testgame2;
    int verif;
    int verif2;
    int nb_win_mcts = 0;
    int nb_win_flat = 0;
    int nb_total = 0;
    int count = 0;
    streambuf* orig_buf = cout.rdbuf();
    while(nb_total < 500){
        cout.rdbuf(NULL);
        testgame = Playout();
        testgame2 = testgame ;
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif = testgame.Full_Game_Flat_vs_MAST(200,1000,0.);
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif2 = testgame2.Full_Game_MCTS_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        if(verif > verif2){
            nb_win_flat ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "flat wins, total : " << nb_total << endl;
        }
        else if(verif2 > verif){
            nb_win_mcts ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "mcts wins, total : " << nb_total << endl;
        }
        cout.rdbuf(orig_buf);
        count ++;
        cout << "total games : " << count << endl;
    }
    cout << "nb_win MCTS : " << nb_win_mcts << endl;
    cout << "nb_win Flat : " << nb_win_flat << endl;
}

void test_MCTS_vs_PPA(){
    Playout testgame;
    Playout testgame2;
    int verif;
    int verif2;
    int nb_win_mcts = 0;
    int nb_win_ppa = 0;
    int nb_total = 0;
    int count = 0;
    streambuf* orig_buf = cout.rdbuf();
    while(nb_total < 500){
        cout.rdbuf(NULL);
        testgame = Playout();
        testgame2 = testgame ;
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif = testgame.Full_Game_PPA_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif2 = testgame2.Full_Game_MCTS_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        if(verif > verif2){
            nb_win_ppa ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "ppa wins, total : " << nb_total << ", ppa : "<< nb_win_ppa << endl;
        }
        else if(verif2 > verif){
            nb_win_mcts ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "mcts wins, total : " << nb_total << ", mcts : "<< nb_win_mcts <<endl;
        }
        cout.rdbuf(orig_buf);
        count ++;
        cout << "total games : " << count << endl;
    }
    cout << "nb_win MCTS : " << nb_win_mcts << endl;
    cout << "nb_win PPA : " << nb_win_ppa << endl;
}

void test_MCTS_vs_MAST(){
    Playout testgame;
    Playout testgame2;
    int verif;
    int verif2;
    int nb_win_mcts = 0;
    int nb_win_mast = 0;
    int nb_total = 0;
    int count = 0;
    streambuf* orig_buf = cout.rdbuf();
    while(nb_total < 500){
        cout.rdbuf(NULL);
        testgame = Playout();
        testgame2 = testgame ;
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif = testgame.Full_Game_MAST_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif2 = testgame2.Full_Game_MCTS_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        if(verif > verif2){
            nb_win_mast ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "mast wins, total : " << nb_total << endl;
        }
        else if(verif2 > verif){
            nb_win_mcts ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "mcts wins, total : " << nb_total << endl;
        }
        cout.rdbuf(orig_buf);
        count ++;
        cout << "total games : " << count << endl;
    }
    cout << "nb_win MCTS : " << nb_win_mcts << endl;
    cout << "nb_win MAST : " << nb_win_mast << endl;
}

void test_PPA_vs_MAST(){
    Playout testgame;
    Playout testgame2;
    int verif;
    int verif2;
    int nb_win_ppa = 0;
    int nb_win_mast = 0;
    int nb_total = 0;
    int count = 0;
    streambuf* orig_buf = cout.rdbuf();
    while(nb_total < 500){
        cout.rdbuf(NULL);
        testgame = Playout();
        testgame2 = testgame ;
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif = testgame.Full_Game_MAST_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif2 = testgame2.Full_Game_PPA_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        if(verif > verif2){
            nb_win_mast ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "mast wins, total : " << nb_total << endl;
        }
        else if(verif2 > verif){
            nb_win_ppa ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "ppa wins, total : " << nb_total << endl;
        }
        cout.rdbuf(orig_buf);
        count ++;
        cout << "total games : " << count << endl;
    }
    cout << "nb_win ppa : " << nb_win_ppa << endl;
    cout << "nb_win MAST : " << nb_win_mast << endl;
}

void test_PPA_vs_PPAn(){
    Playout testgame;
    Playout testgame2;
    int verif;
    int verif2;
    int nb_win_ppa = 0;
    int nb_win_ppan = 0;
    int nb_total = 0;
    int count = 0;
    streambuf* orig_buf = cout.rdbuf();
    while(nb_total < 500){
        cout.rdbuf(NULL);
        testgame = Playout();
        testgame2 = testgame ;
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif = testgame.Full_Game_PPAn_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif2 = testgame2.Full_Game_PPA_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        if(verif > verif2){
            nb_win_ppan ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "ppan wins, total : " << nb_total << ", ppan : " << nb_win_ppan << endl;
        }
        else if(verif2 > verif){
            nb_win_ppa ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "ppa wins, total : " << nb_total << ", ppa : " << nb_win_ppa <<endl;
        }
        cout.rdbuf(orig_buf);
        count ++;
        cout << "total games : " << count << endl;
    }
    cout << "nb_win ppa : " << nb_win_ppa << endl;
    cout << "nb_win ppan : " << nb_win_ppan << endl;
}

void test_MCTS_vs_Flat_D_MCTS(){
    Playout testgame;
    Playout testgame2;
    int verif;
    int verif2;
    int nb_win_mcts = 0;
    int nb_win_flat = 0;
    int nb_total = 0;
    int count = 0;
    streambuf* orig_buf = cout.rdbuf();
    while(nb_total < 500){
        cout.rdbuf(NULL);
        testgame = Playout();
        testgame2 = testgame ;
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif = testgame.Full_Game_Flat_vs_MCTS(500,1000);
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif2 = testgame2.Full_Game_MCTS_vs_MCTS(1500, 1000);
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        if(verif > verif2){
            nb_win_flat ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "flat wins, total : " << nb_total << endl;
        }
        else if(verif2 > verif){
            nb_win_mcts ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "mcts wins, total : " << nb_total << endl;
        }
        cout.rdbuf(orig_buf);
        count ++;
        cout << "total games : " << count << endl;
    }
    cout << "nb_win MCTS : " << nb_win_mcts << endl;
    cout << "nb_win Flat : " << nb_win_flat << endl;
}

void test_MASTn_vs_MAST(){
    Playout testgame;
    Playout testgame2;
    int verif;
    int verif2;
    int nb_win_mastn = 0;
    int nb_win_mast = 0;
    int nb_total = 0;
    int count = 0;
    streambuf* orig_buf = cout.rdbuf();
    while(nb_total < 500){
        cout.rdbuf(NULL);
        testgame = Playout();
        testgame2 = testgame ;
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif = testgame.Full_Game_MAST_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        verif2 = testgame2.Full_Game_MASTn_vs_MAST();
        cout.rdbuf(orig_buf);
        cout.rdbuf(NULL);
        if(verif > verif2){
            nb_win_mast ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "mast wins, total : " << nb_total << ", mast : " << nb_win_mast << endl;
        }
        else if(verif2 > verif){
            nb_win_mastn ++;
            nb_total ++;
            cout.rdbuf(orig_buf);
            cout << "mastn wins, total : " << nb_total << ", mastn : " << nb_win_mastn << endl;
        }
        cout.rdbuf(orig_buf);
        count ++;
        cout << "total games : " << count << endl;
    }
    cout << "nb_win mastn : " << nb_win_mastn << endl;
    cout << "nb_win MAST : " << nb_win_mast << endl;
}
