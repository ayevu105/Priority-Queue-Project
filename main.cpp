/* @file main.cpp
 * @brief The following code fufills the requirments of the Priority Queue 
 * Project where the main driver reads a patients.txt file in and asks the user 
 * to input an integer that indicates the amount of vaccines avaiable. The 
 * program then will print out a list of names according to the amount of 
 * vaccines available in an order where precondition illnesses and higher ages 
 * are prioritized. 
 * @author Anthony Vu
 * @date 10/9/2022
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include "COVIDPriorityQueue.h"

/* printPriorityQueue prints out a list of names in prioritizing order
 * @param pq is a priority queue
 * @param input is the users input that was asked in the drivers code
 */
void printPriorityQueue (std::priority_queue<std::pair<int, std::pair<int, std::string> > > Pq, int Input) {                                                                          
  for (int i = 0; i < Input; i++) {   
        if(!Pq.empty()) {
            std::cout << Pq.top().second.second << std::endl;
            Pq.pop();
        }   
    }
}

/* isInputValid checks if the users input is a valid integer
 * @param input is the users input that was asked in the drivers code
 */
int isInputValid (int Input) {
    //If the users input is an invalid integer (less/equal to 0) throw and exception
    if (Input <= 0) {
        throw ("User Input must be an integer larger than 0.");
    }
    return Input;
}


/* Reads the given patients.txt file and pushes them into a queue
 * @param input is the users input that was asked in the drivers code
 */
void running (int Input) {
    //declare of names, age, and precondition as strings since they are in a .txt file
    std::string Name;                                                                        
    std::string Line;                                                                           
    std::string Age;
    std::string Precondition;

    //declare convert_precondition and set it equal to 0;
    int ConvertPrecondition = 0; 
    
    std::ifstream In("patients.txt");  
    std::priority_queue<std::pair<int, std::pair<int, std::string> > > Pq;  
    //goes through the patients.txt file line by line
    while (getline(In, Line)) {
        //for each line store a name, age, and precondition into strings in this order
        In >> Name >> Age >> Precondition;  
        
        //remove the trailing commas from the name and age string                                              
        Name.pop_back();                                                                        
        Age.pop_back();

        //convert the variable age into an integer for comparison
        int ConvertAge = stoi(Age);                                                           

        //converts the string "Yes" and "No" into an integer value for comparison, "No" is equal to 0 and "Yes" is equal to 1
        if (Precondition == "Yes") {
            ConvertPrecondition = 1;
        }

        if (Precondition == "No") {
            ConvertPrecondition = 0;
        }

        //saves the values as members
        COVIDPriorityQueue Patient = COVIDPriorityQueue(Name, ConvertAge, ConvertPrecondition);

        //only if the age of the patients that are above 5 are pushed into the priority queue
        if (ConvertAge > 5) 
        {
            Pq.push(std::make_pair(Patient.precondition, std::make_pair(Patient.age, Patient.name)));                                                              
        }
    }
    printPriorityQueue(Pq, Input);
}

int main() {   
    //declaring integer variable for user input
    int UserInput = 0;

    std::cout << "How many vaccines are available? ";
    std::cin >> UserInput;

    // exception handling to see if the users input is a valid integer, if it isnt a message is printed
    try {
        isInputValid(UserInput);
    }

    catch (const char* Error) {
        std::cerr << Error << std::endl;
        return 0;
    }
    running(UserInput);
}