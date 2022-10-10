class COVIDPriorityQueue {
     public:
     std::string name;
     int age;
     int precondition;
     COVIDPriorityQueue(std::string name, int age, int precondition);
}; 

COVIDPriorityQueue::COVIDPriorityQueue(std::string name, int age, int precondition) {
     this->name = name;
     this->age = age;
     this->precondition = precondition;
}


