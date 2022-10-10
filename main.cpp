/* @file main.cpp
 * @brief The following code fufills the requirments of the Priority Queue Project 
 * where the main driver reads a patients.txt file in and asks the user to input
 * an integer that indicates the amount of vaccines avaiable. The program then 
 * will print out a list of names according to the amount of vaccines available
 * in an order where precondition illnesses and higher ages are prioritized. 
 * @author Anthony Vu
 * @date 10/9/2022
 */

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include "COVIDPriorityQueue.cpp"

/* testPQ1 writes to the patients.txt file to test new lists of patients
 */
void testPQ1 () {
    std::ofstream write ("patients.txt");
    write << "Name, Age, Precondition Illnesses\n";
    write << "Jessica, 13, No\n";
    write << "Robert, 25, Yes\n";
    write << "James, 90, No\n";
    write << "Maggie, 80, Yes";
    write.close();
}

/* printPriorityQueue prints out a list of names in prioritizing order
 * @param pq is a priority queue that is a tuple which allows it to take in three elements
 * @param input is the users input that was asked in the drivers code
 */
void printPriorityQueue (std::priority_queue<std::pair<int, std::pair<int, std::string> > > pq, int input)
{                                                                          
  for (int i = 0; i < input; i++)
        {   
            if(!pq.empty()) 
            {
                std::cout << pq.top().second.second << std::endl;
                pq.pop();
            }   
        }
}

/* isInputValid checks if the users input is a valid integer
 * @param input is the users input that was asked in the drivers code
 */
int isInputValid (int input)                                                                     
{
    //If the users input is an invalid integer (less/equal to 0) throw and exception
    if (input <= 0)                                                                            
    {
        throw ("User Input must be an integer larger than 0.");
    }
    return input;
}


/* Reads the given patients.txt file and pushes them into a queue
 * @param input is the users input that was asked in the drivers code
 */
void running (int input)
{
    //declare of names, age, and precondition as strings since they are in a .txt file
    std::string name;                                                                        
    std::string line;                                                                           
    std::string age;
    std::string precondition;

    //declare convert_precondition and set it equal to 0;
    int convert_precondition = 0;

    //declare a priority queue with a tuple so that we can compare with three elements
    // std::priority_queue<std::tuple<int, int, std::string> > pq;     
    
    std::ifstream in("patients.txt");  
    std::priority_queue<std::pair<int, std::pair<int, std::string> > > pq;  
    //goes through the patients.txt file line by line
    while (getline(in, line))                                                               
    {
        //for each line store a name, age, and precondition into strings in this order
        in >> name >> age >> precondition;  
        
        //remove the trailing commas from the name and age string                                              
        name.pop_back();                                                                        
        age.pop_back();

        //convert the variable age into an integer for comparison
        int convert_age = stoi(age);                                                           

        //converts the string "Yes" into an integer value for comparison, "No" is equal to 0 and "Yes" is equal to 1
        if (precondition == "Yes")                                                          
        {
            convert_precondition = 1;
        }

        if (precondition == "No")                                                          
        {
            convert_precondition = 0;
        }

        COVIDPriorityQueue patient = COVIDPriorityQueue(name, convert_age, convert_precondition);

        if (convert_age > 5) 
        {
            pq.push(std::make_pair(patient.precondition, std::make_pair(patient.age, patient.name)));                                                              
        }
    }
    printPriorityQueue(pq, input);
}

int main()
{   
    //declaring integer variable for user input
    int user_input;
    std::cout << "How many vaccines are available? ";
    std::cin >> user_input;

    // exception handling to see if the users input is a valid integer, if it isnt a message is printed
    try 
    {
        isInputValid(user_input);
    }

    catch (const char* error)
    {
        std::cerr << error << std::endl;
        return 0;
    }

    testPQ1();
    running(user_input);
}