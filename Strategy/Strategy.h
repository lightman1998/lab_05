//
// Created by gerdon on 27.11.2019.
//

#ifndef UNTITLED_STRATEGY_H
#define UNTITLED_STRATEGY_H


#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Strategy {

    vector<vector<double>> Matrix;
    vector<vector<double >> MatrixB;
public:
    const vector<vector<double>> &getMatrixForB() const;

private:
    int size_x,size_y;
    vector<double> vector_x, vector_y;
    double min_x, max_y;
    bool saddle_point = false;


public:
    Strategy (vector<vector<double>> M){
        Matrix = M;
        size_y = M.size();
        size_x = M.at(0).size();
        minimax_x();
        maximin_y();
        isSaddlePoint();
        createMatrixForB();
    }



    bool isSaddlePoint() {
        if(max_y == min_x){
            saddle_point = true;
            return saddle_point;
        }
        else {
            saddle_point = false;
        }
        return saddle_point;
    }

    // СТРАТЕГИЯ ИГРОКА А
    void maximin_y(){

        for (int i = 0; i < size_y; ++i) {
            vector<double> v = Matrix.at(i);
            auto result = min_element(v.begin(), v.end());
            double a = v.at(std::distance(v.begin(), result));
            vector_y.emplace_back(a);
        }

        auto max_result = max_element(vector_y.begin(), vector_y.end());
        double a = vector_y.at(std::distance(vector_y.begin(), max_result));
        max_y = a;
    }


    //СТРАТЕГИЯ ИГРОКА B
    void minimax_x(){

        for (int j = 0; j < size_x; ++j) {
            vector<double> v;
            for (int i = 0; i < size_y; ++i) {
                v.emplace_back(Matrix.at(i).at(j));
            }
            auto result = max_element(v.begin(), v.end());
            double a = v.at(std::distance(v.begin(), result));
            vector_x.emplace_back(a);
        }

        vector<double> v = vector_x;

        auto min_result = std::min_element(v.begin(), v.end());
        double a = v.at(std::distance(v.begin(), min_result));
        min_x = a;
    }


    void print();

    const vector<vector<double>> &getMatrixForA() const;
    vector<vector<double>> &createMatrixForB();


};






#endif //UNTITLED_STRATEGY_H
