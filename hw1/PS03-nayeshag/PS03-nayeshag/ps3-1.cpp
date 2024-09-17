#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    // make variables 
    int u_alt;
    int u_temp;
    int alt_row;
    int temp_col;

    // make table 
    int table[6][6] = {
        {0, 79, 830, 770, 705, 640},
        {2000, 77, 720, 655, 595, 535},
        {4000, 76, 645, 585, 525, 465},
        {6000, 74, 530, 475, 415, 360},
        {8000, 72, 420, 365, 310, 250},
        {10000, 71, 310, 255, 200, 145},
    };

    while (true) {
        // ask for user input 
        std::cout << "Enter Altitude and Temperature:" << std::endl;
        std::cin >> u_alt >> u_temp;
        // check if inputs are valid 
        if (u_alt <0 || u_alt >10000 || u_temp<-20 || u_temp > 40) {
            std::cout << "Invalid altitude or temperature, please enter values in altitude range {0, 10,000} and temp range {-20, 40}" << std::endl;
        }
        else {
            break;
        }
    }

    // row for altitude and temp (lower lim)
    alt_row = u_alt / 2000;
    temp_col = ((u_temp + 20) / 20) + 2;

    // interpolate
    double m1 = (double)(table[alt_row + 1][temp_col] - table[alt_row][temp_col]) / (table[alt_row + 1][0] - table[alt_row][0]);
    double m2 = (double)(table[alt_row + 1][temp_col + 1] - table[alt_row][temp_col + 1]) / (table[alt_row + 1][0] - table[alt_row][0]);

    double pred_fpm1 = m1*(u_alt - table[alt_row][0]) + table[alt_row][temp_col];
    double pred_fpm2 = m2*(u_alt - table[alt_row][0]) + table[alt_row][temp_col + 1];

    double m3 = (double)(pred_fpm1 - pred_fpm2) / ((((temp_col-2)*20) - 20) - (((temp_col+1-2)*20) - 20));

    double pred_fpm = m3*(u_temp - (((temp_col-2)*20) - 20)) + pred_fpm1;



    // debugs
    std::cout << u_alt << std::endl;
    std::cout << u_temp << std::endl;
    std::cout << alt_row << std::endl;
    std::cout << temp_col << std::endl;
    std::cout << m1 << std::endl;
    std::cout << table[alt_row + 1][temp_col] << table[alt_row][temp_col] << table[alt_row + 1][0] - table[alt_row][0] <<std::endl;

    std::cout << "Expected Climb Rate= " << pred_fpm << std::endl;


    
    
    return 0;
    
}