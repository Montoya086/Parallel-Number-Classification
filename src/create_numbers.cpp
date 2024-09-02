/**
 * Program to load N random numbers into a csv file
 * Authors: Andrés Montoya - 21552, Francisco Castillo - 21562
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

int main(int argc, char * argv[]) {
    //Variable to store the number of random numbers to generate
    int N;

    //Variable to store the maximum value of the random numbers
    int max;

    //Variable to store the name of the file
    string filename;

    //Load the variables from argv
    if (argc == 3) {
        N = atoi(argv[1]);
        max = atoi(argv[1]);
        filename = argv[2];
    } else {
        cout << "Usage: " << argv[0] << " N filename.csv" << endl;
        return 1;
    }

    // if the file already exists, delete it
    remove(filename.c_str());

    //Create the file
    ofstream file(filename.c_str());

    //Seed the random number generator
    srand(time(0));

    //Generate N random numbers and write them to the file
    for (int i = 0; i < N; i++) {
        file << rand() % max << ",";
    }

    //Close the file

    file.close();

}
