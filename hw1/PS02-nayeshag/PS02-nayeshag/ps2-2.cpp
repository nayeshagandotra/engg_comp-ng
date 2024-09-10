#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// void printVector(const std::vector<int>& vec) {
//     // for debug
//     for (const int& element : vec) {
//         std::cout << element << " ";
//     }
//     std::cout << std::endl;
// }

void random_index_generator(int n, std::vector<int>& indices){
    // shuffle indices such that you get n random numbers, here n = num_flashcards (internally capped)

    // seed random
    srand(time(NULL));
    // define variables
    int random_no; // for random number
    int bag; //placeholder for swapping
    int size = indices.size();

    for (int i = size-1; i >= size-n; --i) {  //start from last element, and swap till n from end of list

        // generate random number between 0 and remaining part of list
        random_no=rand()%(i+1); 
        
        // swap elements
        bag = indices[i];
        indices[i] = indices[random_no];
        indices[random_no] = bag;

        // // debug
        // std::cout << "i is " << i << std::endl;
        // std::cout << "random no is" << random_no << std::endl;

    }
}

int show_flashcard(int index, int range_max){
    // show flashcard containing the multiplier at index
    // range_max is the max number of numbers, in case we want to multiply beyond 12x12
    int num1;
    int num2;
    // construct flashcard
    for (int i = 0; i < 5; i++){
        if (i == 0 || i == 4){
            // Print the top  and bottom row
            std::cout << "+";
            for (int i = 0; i < 5; i++) {
                std::cout << "-";
            }
            std::cout << "+" << std::endl;
        }
        if (i == 1 || i == 3){
            // Print the middle (non number) row
            std::cout << "|";
            for (int i = 0; i < 5; i++) {
                std::cout << " ";
            }
            std::cout << "|" << std::endl;
        }
        if (i == 2){
            // calculate what multiplier
            num1 = (index / range_max) + 1; 
            num2 = (index % range_max) + 1;

            // convert to string
            std::string str = std::to_string(num1) + "x" + std::to_string(num2);

            // make the middle number row
            std::string empty_string(7, ' ');  // A single string of 7 spaces


            empty_string[0] = '|';
            empty_string[6] = '|';

            // You can now fill the string with characters
            for (int i = 1; i < 6; i++) {
                empty_string[i] = ' ';
            }

            // replace with multipler
            empty_string.replace(6-str.size(), str.size(), str);

            // print the middle number row
            std::cout << empty_string <<std::endl;

        }
    }

    

    return num1 * num2;
}

int main() {

    // initialize variables
    int num_flashcards;
    int iter_num = 0;
    int num_correct = 0;
    time_t start = time(nullptr);

    // first ask the user for how many flashcards 
    std::cout << "Enter number of desired flashcards to practice : " << std::endl;
    

    while (true) {
        std::cin >> num_flashcards; // Accepts input with spaces
        // Check if the input is not an integer
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(1000, '\n'); //ignore characters in list
            std::cout << "Input is not an integer." << std::endl;
            }
        // check if integer is valid (between 1 and 144)
        else if (num_flashcards < 1 || num_flashcards > 144){
            std::cout << "The number of cards must be between 1 and 144. Please enter another number:" << std::endl;
        }
        else {
            break;
        }
    }

    // initialize array from 1 to 144 (for indexing flashcards)
    int r[144];   //here this number can be changed if we want to create a variable number of flashcards
	for(int i=0; i<144; ++i)
	{
		r[i]=i;
	}
    // convert array to vector
    std::vector<int> index_array(r, r + 144);

    // DEBUG
    // printVector(index_array);

    // shuffle input_array to get n random indices (worst case time complexity of O(n))
    random_index_generator(num_flashcards, index_array); // should shuffle index_array without outputting anything
    // printVector(index_array);

    // show the user flashcards as desired
    while (iter_num < num_flashcards){
        int user_ans;
        int act_result;

        // calculate flashcard answer

        // show flashcard

        act_result = show_flashcard(index_array[index_array.size()-iter_num - 1], 12);
        // Start measuring time
        time_t start = time(nullptr);

        // ask for answer
        std::cout << "Enter your answer" << std::endl;
        std::cin >> user_ans; 

        // check if answer is right
        if (user_ans == act_result) {
            std::cout << "CORRECT! YAY!" << std::endl;
            num_correct += 1;
        }
        else {
            std::cout << "Wrong. The correct answer was " << act_result << std::endl;
        }
        iter_num++;
    }
    // End measuring time
    time_t end = time(nullptr);
    double duration = difftime(end, start);
    int accuracy = (num_correct * 100) / num_flashcards;

    printf("You answered %d problems in %f seconds.\n", num_flashcards, duration);
    printf("You answered %d problems correctly (%d%%).\n", num_correct, accuracy);
    
    return 0;
}