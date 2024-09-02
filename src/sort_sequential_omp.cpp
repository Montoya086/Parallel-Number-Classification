#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <omp.h>

using namespace std;

// Function to find the median of three values
int median(int a, int b, int c) {
    if ((a > b) != (a > c)) return a;
    else if ((b > a) != (b > c)) return b;
    else return c;
}

void quickSort(vector<int> &numbers, int left, int right, int depth = 0) {
    int i = left, j = right;
    int pivot = median(numbers[left], numbers[(left + right) / 2], numbers[right]);

    while (i <= j) {
        while (numbers[i] < pivot)
            i++;
        while (numbers[j] > pivot)
            j--;
        if (i <= j) {
            swap(numbers[i], numbers[j]);
            i++;
            j--;
        }
    };

    int threshold = 10000; // Threshold for task creation
    if (left < j) {
        if (right - left > threshold) {
            #pragma omp task
            quickSort(numbers, left, j, depth + 1);
        } else {
            quickSort(numbers, left, j, depth + 1);
        }
    }
    if (i < right) {
        if (right - left > threshold) {
            #pragma omp task
            quickSort(numbers, i, right, depth + 1);
        } else {
            quickSort(numbers, i, right, depth + 1);
        }
    }

    #pragma omp taskwait
}

// Function to read numbers from a CSV file
vector<int> readNumbers(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: File not found" << endl;
        exit(1);
    }

    vector<int> numbers;
    string line;
    while (getline(file, line, ',')) {
        numbers.push_back(stoi(line));
    }

    file.close();
    return numbers;
}

int main(int argc, char * argv[]) {
    string filename;

    if (argc == 2) {
        filename = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " filename.csv" << endl;
        return 1;
    }

    vector<int> numbers = readNumbers(filename);

    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single
        quickSort(numbers, 0, numbers.size() - 1);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    ofstream sorted_file("sorted_" + filename);
    for (int i = 0; i < numbers.size(); i++) {
        sorted_file << numbers[i] << ",";
    }
    sorted_file.close();

    cout << endl;
    cout << "Time to sort: " << elapsed.count() << " s" << endl;
    cout << "Sorted numbers saved to sorted_" << filename << endl;
    cout << endl;

    return 0;
}