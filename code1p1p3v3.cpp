// SPMD Pattern example

#include <iostream>
#include <chrono>
#include <omp.h>
#include <climits>
#include <random>
using namespace std; 

#define N 20000000  //seg fault 

int main() {
    cout << INT_MAX << endl; 
    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end; 

    const int SIZE = 200; // cant make it 20 million without seg fault
    const int FLIPS = 1000000;
    random_device engine; 
    uniform_int_distribution diceValues(0, 1); 
    //int myArray[SIZE];  //stack memory?
    int* myArray = new int[N];  // this is ok? Heap memory?

    start = chrono::system_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        int id = omp_get_thread_num();
        //printf("%d %d\n", i, id);  
        myArray[i] = 0;
        for (int f = 0; f < FLIPS; f++) {
            if (diceValues(engine) == 0) {
                myArray[i]++; 
            }
        }
        
    }

    end = chrono::system_clock::now();
    chrono::duration<float> elapsed = end-start;

    cout << "Done populating array" << endl; 
    cout << elapsed.count() << endl; 

    return 0;
}