//
// Created by gerdon on 27.11.2019.
//

#include "Simplex.h"
#include <math.h>
#include <algorithm>
#include <sstream>


void Simplex::printFullMatrix(int y_size, int x_size) {

    cout << "FULL MATRIX IS:\n";

    for (int i = 0; i < y_size; ++i) {
        cout << "+";
        for (int j = 0; j < x_size; ++j) {
            cout << "-------+";
        }
        cout << endl;
        for (int j = 0; j < x_size; ++j) {
            std::cout << "|  " << roundf(full_matrix.at(i).at(j)*100)/100 << "\t";
        }
        cout << "|\n";
    }

    cout << "+";
    for (int j = 0; j < x_size; ++j) {
        cout << "-------+";
    }
    cout << endl;
}


void Simplex::Solve() {
    if(gambler == 'A') {
        first_step_solve();
    }

    for (int i = 0; i < size_y; ++i) {
        printMatrixWithVariables();
        second_step_solve();
    }

    third_step_solve();

}






void Simplex::first_step_solve() {

    for (int j = 0; j < size_y; ++j) {

        cout << "divide string at value in basics X" <<  j+5 << endl;

        double string_value_divider = full_matrix.at(j).at(j+size_x);
        for (int i = 0; i < full_matrix.at(0).size(); ++i) {
            if(full_matrix.at(j).at(i) != 0) {
                full_matrix.at(j).at(i) = full_matrix.at(j).at(i) / string_value_divider;
            }
        }
        printFullMatrix(size_y,size_x+size_y+1);
    }
}

bool Simplex::second_step_solve() {

    int column_index = find_max_or_min_index(); // find max or min from L(C) vector

    //get true string (divide B by a at index and then compare to choose min)
    int row_index = get_MIN_INDEX_BY_DIVIDING_AT_B(column_index);

    change_variables_index(column_index,row_index);


    divide_row_by_main_element(column_index,row_index);

    minus_main_row_from_all_other_rows(column_index,row_index);

    for (int i = 0; i < size_x; ++i) {
        C.at(i) = full_matrix.at(size_y).at(i);
    }
    cout << endl;

}


void Simplex::third_step_solve() {
    double sum = 0;
    for (int i = 0; i < VARIABLES_Y.size(); ++i) {
        int n = atoi(VARIABLES_Y.at(i).substr(1, 1).c_str());
        if(n < 5){
            sum += full_matrix.at(i).at(size_y+size_x);
            cout << "X" <<n <<": "<< full_matrix.at(i).at(size_y+size_x) << endl;
        }
    }
    if(gambler == 'A'){
        cout << "max win is " << sum;
    }
    else if (gambler == 'B') {
        cout << "min lose is " << sum;
    }
}































int Simplex::find_max_or_min_index() {

    if(gambler == 'A'){
        //find max from L(C) vector
        int maxElementIndex = max_element(C.begin(),C.end()) - C.begin();
        return maxElementIndex;

    } else if (gambler == 'B') {
        //find min from L(C) vector
        int minElementIndex = min_element(C.begin(),C.end()) - C.begin();
        return minElementIndex;
    }
}


int Simplex::get_MIN_INDEX_BY_DIVIDING_AT_B(int column) {
    vector<double> values;
    for (int i = 0; i < size_y; ++i) {
        values.emplace_back(abs(full_matrix.at(i).at(size_y+size_x)/full_matrix.at(i).at(column)));
    }

    cout << endl;

    int minElementIndex = std::min_element(values.begin(),values.end()) - values.begin();
    return minElementIndex;
}


void Simplex::change_variables_index(int column, int row) {
    VARIABLES_Y.at(row) = VARIABLES_X.at(column);
}


void Simplex::divide_row_by_main_element(int column, int row) {

    double element = full_matrix.at(row).at(column);
    for (int i = 0; i < size_x+size_y+1; ++i) {
        full_matrix.at(row).at(i) = full_matrix.at(row).at(i) / element;
    }
}


void Simplex::minus_main_row_from_all_other_rows(int main_column, int main_row) {

    for (int i = 0; i < size_y+1; ++i) {
        if( i == main_row){
            continue;
        } else {

            double x_times = full_matrix.at(i).at(main_column) / full_matrix.at(main_row).at(main_column);

            for (int j = 0; j < size_x + size_y + 1; ++j) {
                full_matrix.at(i).at(j) = full_matrix.at(i).at(j) - full_matrix.at(main_row).at(j) * x_times;
            }
        }
    }
}







void Simplex::printMatrix() {
    if(gambler == 'A') {
        printFullMatrix(size_y, size_x + size_y + 1);
    }
    else if (gambler == 'B') {
        printFullMatrix(size_y, size_x + size_y);
    }
}


void Simplex::printMatrixWithVariables() {
    if(gambler == 'A') {
        printFullMatrixWithVariables(size_y +1, size_x + size_y + 1);
    }
    else if (gambler == 'B') {
        printFullMatrixWithVariables(size_y+1, size_x + size_y+1);
    }
}


void Simplex::printFullMatrixWithVariables(int y_size, int x_size) {
    cout << "FULL MATRIX WITH VARIABLES IS:\n";

    cout << "+-------+";
    for (int j = 0; j < x_size ; ++j) {
        cout << "-----------+";
    }
    cout << endl;
    cout << "|       ";

    for (int d = 0; d < x_size-1; ++d){
        cout << "|  " <<  VARIABLES_X.at(d) << "\t\t";
    }
    cout << "|  " <<  "B" << "\t\t";
    cout << "|\n";

    for (int i = 0; i < y_size; ++i) {

        cout << "+-------+";
        for (int j = 0; j < x_size; ++j) {
            cout << "-----------+";
        }
        cout << endl;

        if(VARIABLES_Y.size() > i) {
            std::cout << "|  " << VARIABLES_Y.at(i) << 	"\t";
        } else {
            std::cout << "|  " << "L" << "\t";
        }


        for (int j = 0; j < x_size; ++j) {



            ostringstream strs;
            double a = roundf(full_matrix.at(i).at(j) * 100) / 100;
            strs << a;
            string str = strs.str();

            if (str.length() > 4) {
                std::cout << "|  " << str << "\t";
            } else {
                std::cout << "|  " << str << "\t\t";
            }





        }


        cout << "|\n";
    }

    cout << "+-------+";
    for (int j = 0; j < x_size; ++j) {
        cout << "-----------+";
    }
    cout << endl;
}




void Simplex::print() {

    for (int i = 0; i < size_y; ++i) {
        cout << "+";
        for (int j = 0; j < size_x + 1; ++j) {
            cout << "-------+";
        }
        cout << endl;
        for (int j = 0; j < size_x; ++j) {
            std::cout << "|  " << roundf(A.at(i).at(j)*100)/100 << "\t";
        }
        cout << "|  " << roundf(B.at(i)*100)/100 << "\t|\n";
    }
    cout << "+";
    for (int j = 0; j < size_x + 1; ++j) {

        cout << "-------+";
    }
    cout << endl;
    for (int k = 0; k < size_x; ++k) {
        std::cout << "|  " << roundf(C.at(k)*100)/100 << "\t";
    }
    cout << "|\n";

    cout << "+";
    for (int j = 0; j < size_x; ++j) {

        cout << "-------+";
    }
    cout << endl;
}



