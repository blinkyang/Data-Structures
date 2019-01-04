#include <iostream>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int MAX_VAL = 100;
const int NUM_ELEM = 15;

int find_median(priority_queue<int, vector<int>, greater<int>>& h_high, priority_queue<int>& h_low, int num);
template<typename T> void print_queue(T& q);

int main() {
    int current_median;
    priority_queue<int> lo; // Bottom half of numbers - max-heap (default)
    priority_queue<int, vector<int>, greater<int> > hi; // Top half of numbers - min-heap
    srand(time(0)); // Seed for random number generator
    for (int i = 0; i < NUM_ELEM; i++) {
        int n = rand() % MAX_VAL;
        current_median = find_median(hi, lo, n);
        cout <<  "Inserted " << n << " Median " << current_median << endl << endl;
    }

    return 0;
}

template<typename T> void print_queue(T& q) {
    T q_copy(q);
    while(!q_copy.empty()) {
        std::cout << q_copy.top() << " ";
        q_copy.pop();
    }
    std::cout << '\n';
}


int find_median(priority_queue<int, vector<int>, greater<int>>& h_high, priority_queue<int>& h_low, int num) {

         if (h_low.size() == 0 || num < h_low.top()) //Inputting low numbers into low heap
         {
            h_low.push(num);
            if (h_low.size() > ((h_high.size() + h_low.size()) / 2)) //If low heap is bigger than high heap, push top to high heap
            {
                h_high.push(h_low.top());
                h_low.pop();
            }
         }
         else //inputting high numbers into high heap
         {
             h_high.push(num);
             if (h_high.size() > ((h_high.size() + h_low.size()) / 2)) //If high heap is bigger than low heap, push top to low heap
            {
                h_low.push(h_high.top());
                h_high.pop();
            }
         }
    return h_low.top(); //Picking the top of low to be the middle with 15 number input
}
