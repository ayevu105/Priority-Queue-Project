#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

class COVIDPriorityQueue {
     public:
     std::string name;
     int age;
     int precondition;
     COVIDPriorityQueue();
     COVIDPriorityQueue(std::string name, int age, int precondition);
     std::string printName();
}; 

COVIDPriorityQueue::COVIDPriorityQueue(){}

COVIDPriorityQueue::COVIDPriorityQueue(std::string name, int age, int precondition) {
     this->name = name;
     this->age = age;
     this->precondition = precondition;
}

