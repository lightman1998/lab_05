//
// Created by gerdon on 27.11.2019.
//

#ifndef UNTITLED_SIMPLEX_H
#define UNTITLED_SIMPLEX_H

#include <vector>
#include <iostream>

using namespace std;

class Simplex {

    vector<vector<double>> A;
    vector<double> B;
    vector<double> C;
    int size_x, size_y;
    double g;
    char gambler;


    vector<string> VARIABLES_Y;
    vector<string> VARIABLES_X;

    vector<vector<double>> full_matrix;


public:
    void print();
    void printFullMatrix(int y_size, int x_size);
    void Solve();
    void first_step_solve();
    bool second_step_solve();
    void printMatrix();
    void printMatrixWithVariables();
    void printFullMatrixWithVariables(int y_size, int x_size);
    int find_max_or_min_index();
    int get_MIN_INDEX_BY_DIVIDING_AT_B(int column);
    void change_variables_index(int column, int row);
    void divide_row_by_main_element(int ,int );
    void minus_main_row_from_all_other_rows(int main_row, int main_column);
    void third_step_solve();

    Simplex(vector<vector<double>> M, bool is_min, double min_win, double max_lose) {


        // FOR A = search min, FOR B = search max
        if (is_min) {
            gambler = 'A';
        } else {
            gambler = 'B';
        }

        A = M;
        size_y = M.size();
        size_x = M.at(0).size();

        for (int m = 0; m < size_y; ++m) {
            VARIABLES_Y.emplace_back("X" + to_string(m+1+size_x));
        }

        for (int l = 0; l < size_y+size_x; ++l) {
            VARIABLES_X.emplace_back("X" + to_string(l+1));
        }

        int c = 0;

        if (gambler == 'A') {
            c = -1;
        } else if (gambler == 'B') {
            c = 1;
        }


        // <= или  >= система

        for (int i = 0; i < size_y; ++i) {
            B.emplace_back(c);
        }


        for (int j = 0; j < size_x; ++j) {
            C.emplace_back(-1);
        }

        if (gambler == 'A') {
            g = (1 / min_win);
        } else {
            g = (1 / max_lose);
        }

        if (gambler == 'A') {
            vector<vector<double>> v(size_y + 1, vector<double>(size_x + size_y + 1, 0));
            full_matrix = v;
        } else
        if (gambler == 'B') {
            vector<vector<double>> v(size_y + 1, vector<double>(size_x + size_y+1, 0));
            full_matrix = v;
        }



        {
            for (int k = 0; k < size_y; ++k) {
                for (int i = 0; i < size_x; ++i) {
                    full_matrix.at(k).at(i) = M.at(k).at(i);
                }
            }


            for (int j = 0; j < size_y; ++j) {
                full_matrix.at(j).at(j+size_x) = B.at(j);
                if(gambler == 'A') {
                    full_matrix.at(j).at(size_x + size_y) = -1;
                }
            }

            for (int l = 0; l < size_x; ++l) {
                full_matrix.at(size_y).at(l) = C.at(l);
            }

            for(int i = 0; i < size_y; ++i) {
                if(gambler == 'A') {
                    full_matrix.at(i).at(size_x + size_y) = -B.at(i);
                } else if (gambler == 'B') {
                    full_matrix.at(i).at(size_x + size_y) = B.at(i);
                }
            }
        }




    }



};


#endif //UNTITLED_SIMPLEX_H
