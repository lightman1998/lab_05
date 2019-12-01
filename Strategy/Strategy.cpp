//
// Created by gerdon on 27.11.2019.
//

#include "Strategy.h"


void Strategy::print() {

        for (int i = 0; i < size_y; ++i) {
            cout << "+";
            for (int j = 0; j < size_x + 1; ++j) {
                cout << "-------+";
            }
            cout << endl;
            for (int j = 0; j < size_x; ++j) {
                std::cout << "|  " << Matrix.at(i).at(j) << "\t";
            }
            cout << "|  " << vector_y.at(i) << "\t|\n";
        }
        cout << "+";
        for (int j = 0; j < size_x + 1; ++j) {

            cout << "-------+";
        }
        cout << endl;
        for (int k = 0; k < size_x; ++k) {
            std::cout << "|  " << vector_x.at(k) << "\t";
        }
        cout << "|\n";

        cout << "+";
        for (int j = 0; j < size_x ; ++j) {

            cout << "-------+";
        }
        cout << endl;

        cout << "min of column is: " << min_x << endl;
        cout << "max of row is:     " << max_y << endl;

        cout << "saddle point is ";
        if(isSaddlePoint()){
            cout << "exist.\n";
        }
        else{
            cout << "not exist.\n";
        }

        cout << "================================\n";
}

const vector<vector<double>> &Strategy::getMatrixForA() const {
    return Matrix;
}

// pivot operation
vector<vector<double>>& Strategy::createMatrixForB() {

    vector<vector<double>> result(Matrix.at(0).size(),vector<double>(Matrix.size()));
    for (size_t i = 0; i < Matrix.size(); ++i)
        for (size_t j = 0; j < Matrix.at(0).size(); ++j)
            result[j][i] = Matrix[i][j];

    MatrixB = result;
}

const vector<vector<double>> &Strategy::getMatrixForB() const {
    return MatrixB;
}
