/**
 * Program to load numbers from a csv file to an array and sort them
 * Authors: Andrés Montoya - 21552, Francisco Castillo - 21562
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

//Quick sort function
void quickSort(vector<int> &numbers, int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = numbers[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (numbers[i] < pivot)
            i++;
        while (numbers[j] > pivot)
            j--;
        if (i <= j) {
            tmp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quickSort(numbers, left, j);
    if (i < right)
        quickSort(numbers, i, right);
}

int main(int argc, char * argv[]) {
    //Variable to store the name of the file
    string filename;

    //Load the variables from argv
    if (argc == 2) {
        filename = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " filename.csv" << endl;
        return 1;
    }

    //Open the file
    ifstream file(filename.c_str());

    //Variable to store the numbers
    vector<int> numbers;

    //Variable to store the number read from the file
    int number;

    //Read the numbers from the file
    while (file >> number) {
        numbers.push_back(number);
        //Ignore the comma
        file.ignore();
    }

    //Close the file
    file.close();

    //Sort the numbers
    auto start = chrono::high_resolution_clock::now();
    quickSort(numbers, 0, numbers.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Time to sort: " << elapsed.count() << " s" << endl;

    //Save the sorted numbers to a csv file
    ofstream sorted_file("sorted_" + filename);
    for (int i = 0; i < numbers.size(); i++) {
        sorted_file << numbers[i] << ",";
    }
    sorted_file.close();
    
    cout << endl;

    return 0;
}