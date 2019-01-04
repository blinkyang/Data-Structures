/* Test cases - 1) Random array mixed positive and negative numbers 2) Sorted array 3) Reverse sorted array 4) Custom input */
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <algorithm>

using namespace std;

const int NUM_ELEM = 15;
const int MAX_VAL = 100;

int countInv(vector<int> &in_vec, vector<int> &out_vec, int begin, int end);

int main(int argc, char **argv)
{
    vector<int> my_vec;
    vector<int>::iterator it;
    srand(time(0)); // Seed for random number generator
    assert(argc == 2);
    switch(atoi(argv[1])) {
        case 1:
                // Input vector of positive and negative random ints
                for (int i = 0; i < NUM_ELEM; i++)
                    my_vec.push_back(rand() % MAX_VAL - (MAX_VAL/2));
                break;
        case 2:
                // Input vector of sorted ints
                for (int i = 0; i < NUM_ELEM; ++i)
                    my_vec.push_back(i);
                break;
        case 3:
                // Input vector of reverse sorted ints
                for (int i = 0; i < NUM_ELEM; ++i)
                    my_vec.push_back(NUM_ELEM-i);
                break;
        case 4:
                // Custom input
                my_vec.push_back(4);
                my_vec.push_back(5);
                my_vec.push_back(6);
                my_vec.push_back(1);
                my_vec.push_back(2);
                my_vec.push_back(3);
                break;
        default:
                cout << "Invalid input" << endl;
                return -1;

    }

    // Print vector
    for (it = my_vec.begin(); it !=  my_vec.end(); ++it)
        cout << *it << " ";
    cout << endl << endl;

    vector<int> sort_vec(my_vec);
    cout << "Number of inversions " << countInv(my_vec, sort_vec, 0, my_vec.size()) << endl;

    // Sorted array
    for (it = sort_vec.begin(); it != sort_vec.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int countInv(vector<int> &in_vec, vector<int> &out_vec, int begin, int end)
{
    vector<int> b; //Initializing variables
    vector<int> c;
    int i = 0;
    int j = 0;
    int inverse = 0;

    int i1 = 0,i2 = 0, m = 0;



if(end==1 || end ==0) return 0; //pushing input vector into 2
else{
    for (int i = begin; i<end; i++)
    {
        if(i < end/2)
        {
            b.push_back(in_vec[i]);
        }
        else
        {
            c.push_back(in_vec[i]);
        }
    }

    vector<int> b2(b);
    vector<int> c2(c);

    i1 = countInv(b,b2, 0,b.size());  //recursively counting inversions for both
    i2 = countInv(c,c2, 0,c.size());

    for (int k = begin; k< end; k++) //combining the two vectors, I don't know why there is bounding issues on some occasions though
    {
        if (i >= b2.size() && (j < c2.size()))
        {
            out_vec[k] = c2[j];
            j++;
        }
        else if ((j >= c2.size()) && (i < c2.size()))
        {
            out_vec[k] = b2[i];
            i++;
        }

        else if ((b2[i] < c2[j]) && (i < b2.size()))
        {
            out_vec[k] = b2[i];
            i++;
        }
        else if ((c2[j] < b2[i]) && (j < c2.size()))
        {
            out_vec[k] = c2[j];
            inverse = inverse + b2.size()-1; //Counting inversion for split
            j++;
        }
        else
        {
            //cout << "b[" << k << "]: " << b[k] << " c[" << k << "]: " << c[k] << endl;
        }
    }

    return i1+i2+inverse; //returning total inversions

}
}

