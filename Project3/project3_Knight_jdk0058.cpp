/* FILE NAME: project1_Knight_jdk0058.cpp 
 * AUTHOR: Jacob Knight
 * Auburn ID: jdk0058
 * Resources: I used the project3 hints file slightly to help with this assignment and I also used 
 * https://www.tutorialspoint.com/cplusplus-program-to-implement-merge-sort to help with merge and merge sort methods.
 * Compile: g++ project3_Knight_jdk0058.cpp 
 * Run: ./a.out project3_Knight_jdk0058.cpp
 */ 
#include <fstream>
#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

int read_file(int inputArray[], ifstream& instream) {
    int index = 0;

    instream >> inputArray[index];
    while (!instream.eof()) {
        index++;
        instream >> inputArray[index];
    }
    return index;
}

void merge(int array[], int x, int y, int z) { 
    int i, j, k; 
    int n1 = y - x + 1; 
    int n2 = z - y; 
  
    int* X = new int[n1];
    int* Z = new int[n2];

  
    for (i = 0; i < n1; i++) {
        X[i] = array[x + i]; 
    }

    for (j = 0; j < n2; j++) {
        Z[j] = array[y + 1 + j];
    }
  
    i = 0;
    j = 0; 
    k = x;
    while (i < n1 && j < n2) { 
        if (X[i] <= Z[j]) { 
            array[k] = X[i]; 
            i++; 
        } 
        else { 
            array[k] = Z[j]; 
            j++; 
        } 
        k++; 
    }
  
    while (i < n1) { 
        array[k] = X[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) { 
        array[k] = Z[j]; 
        j++; 
        k++; 
    }

    delete[] X;
    delete[] Z;
} 
  
void mergeSort(int array[], int x, int z) 
{ 
    if (x < z) { 
        int y = x + (z - x) / 2; 
   
        mergeSort(array, x, y); 
        mergeSort(array, y + 1, z); 
  
        merge(array, x, y, z); 
    } 
}

int combine_and_sort(int array1[], int array1Size, int array2[], int array2Size, int outputArray[]) {
    int outputArraySize = array1Size + array2Size;

    for (int i = 0; i < array1Size; i++) {
        outputArray[i] = array1[i];
    }
    for (int i = 0; i < array2Size; i++) {
        outputArray[i+array1Size] = array2[i];
    }
    mergeSort(outputArray, 0, outputArraySize-1);

    return outputArraySize;
}

void writefile(int outputArray[], int outputArraySize) {
    ofstream outstream;
    string outputFilename;
    cout << "Enter the output file name: ";
    cin >> outputFilename;

    outstream.open((char*)outputFilename.c_str());
    for (int i = 0; i < outputArraySize; i++) {
        outstream << outputArray[i] << "\n";
    }
    outstream.close();

    cout << "*** Please check the new file - " << outputFilename << " ***\n";
}

int main() {
    int array1[MAX_SIZE];
    int array1Size;
    int array2[MAX_SIZE];
    int array2Size;

    cout << endl << "*** Welcome to Jacob's sorting program ***\n";

    ifstream instream;
    string filename1;
    bool checkFile1 = false;
    while (!checkFile1) {
        cout << "Enter the first input file name: ";
        cin >> filename1;
        instream.open((char*)filename1.c_str());
        checkFile1 = instream.good();
        if (!checkFile1) {
            cout << "Error: Invalid filename\n";
            cout << endl;
        }
    }
    
    array1Size = read_file(array1, instream);
    instream.close();

    cout << "The list of " << array1Size << " numbers in file " << filename1 << " is:\n";
    for (int i = 0; i < array1Size; i++) {
        cout << array1[i] << "\n";
    }
    cout << endl;

    string filename2;
    bool checkFile2 = false;
    while (!checkFile2) {
        cout << "Enter the second input file name: ";
        cin >> filename2;
        instream.open((char*)filename2.c_str());
        checkFile2 = instream.good();
        if (!checkFile2) {
            cout << "Error: Invalid filename\n";
            cout << endl;
        }
    }
    
    array2Size = read_file(array2, instream);
    instream.close();

    cout << "The list of " << array2Size << " numbers in file " << filename2 << " is:\n";
    for (int i = 0; i < array2Size; i++) {
        cout << array2[i] << "\n";
    }
    cout << endl;

    int outputArray[MAX_SIZE];
    int outputArraySize = combine_and_sort(array1, array1Size, array2, array2Size, outputArray);

    cout << "The sorted list of " << outputArraySize << " numbers is:";
    for (int i = 0; i < outputArraySize; i++) {
        cout << " " << outputArray[i];
    }
    cout << endl;

    writefile(outputArray, outputArraySize);

    cout << "*** Goodbye. ***" << endl;
    return 0;
}