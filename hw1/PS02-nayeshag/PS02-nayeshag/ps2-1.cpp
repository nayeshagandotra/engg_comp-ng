#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fy_shuffle(std::vector<std::string>& strList) {

    // seed random
    srand(time(NULL));
    // define variables
    int n; // for random number
    int size = strList.size(); //to store size of list
    std::string bag = "hello"; //placeholder for swapping

    for (int i = size-1; i >= 0; --i) {  //start from last element, and swap till end of list

        // generate random number between 0 and remaining part of list
        n=rand()%(i+1); 
        
        // swap elements
        bag = strList[i];
        strList[i] = strList[n];
        strList[n] = bag;

    }
}



int main() {
    // Create two lists (vectors) of strings
    std::vector<std::string> days = {"Sun", "Mon", "Tue", "Wed", "Thurs", "Fri", "Sat"};
    std::vector<std::string> food_opts = {"Pizza from Mineo's", 
                                        "Tofu Tikka Masala from Prince of India", 
                                        "Crispy Salmon Roll from Sushi Fuku", 
                                        "Sub from Uncle Sam's", 
                                        "Fried rice from How Lee", 
                                        "Sandwiches from La Prima", 
                                        "Find free food on campus"};

    // shuffle list 2 (food options)
    fy_shuffle(food_opts);

    // print necessary
    for (int i = 0; i < days.size(); ++i) {
        std::cout << days[i] << " " << food_opts[i] << std::endl;
    }

    return 0;
}
