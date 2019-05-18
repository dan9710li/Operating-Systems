#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

using namespace std;
/*
 Given Utlities from main.cpp
 */
#include "../Utilities/Utils.h"
#include "../Utilities/Scanner.h"
#include "../Utilities/ScanLine.h"

//Create 3 3x3 matrices
#define NUM_THREADS 9
int matrixA[3][3];
int matrixB[3][3];
int matrixC[3][3];

//function to multpily matrices
void *matrix_mult(void *t) {
    long tid;
    tid = (long)t;
    long output_row,output_column,sum=0;
    output_row = tid/3;
    output_column = tid%3;
    
    for(int i = 0; i < 3; i++)
        sum+= matrixA[output_row][i] * matrixB[i][output_column];
    
    // create product of two matrices into matrix c
    matrixC[output_row][output_column] = sum;
}

//function to receive input for matrices
void getInput(string File1, string File2){
    Scanner scanner;
    string element = "";
    scanner.openFile(File1);
    //Receive input for first matrix
    cout<<" Reading input matrix 1....";
    int i = 0,k = 0;
    while (scanner.hasNext())
    {
        element = scanner.next();
        if(i < 3)
        {
            matrixA[k][i] = stoi(element);
            i++;
        }
        else
        {
            i = 0;
            k++;
            matrixA[k][i] = stoi(element);
            i++;
        }
    }
    cout<<"done"<<endl;
    i = 0,k = 0;
    scanner.close();
    scanner.openFile(File2);
    //receive input for second matrix
    cout<<"Reading input matrix 2....";
    while (scanner.hasNext())
    {
        element = scanner.next();
        if(i < 3)
        {
            matrixB[k][i] = stoi(element);
            i++;
        }
        else{
            i = 0;
            k++;
            matrixB[k][i] = stoi(element);
            i++;
        }
        
    }
    cout<<"done"<<endl; // input finished
    scanner.close();
}

//function to print outputfile
void print(string outputFile){
    ofstream outStream;
    outStream.open(outputFile);
    for(int i = 0; i < 3; i++)
    {
        for(int k = 0; k < 3; k++)
            outStream << matrixC[i][k]<< " ";
        outStream << endl;
    }
    outStream.close();
}

//Intialize threads
//Main thread waits until all threads are done to print results
//Given creation of threads from Multithreads example
int main (int argc, char *argv[])
{
    void *status;
    int rc, i = 0, k = 0;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    string File1 = "" ,File2 = "", outputFile = "";
    
    
    Utils::CheckArgs(3, argc, argv, "infilename (first matrix) infilename (second matrix) outfilename (output file)"); //Given from main.cpp
    File1 = static_cast<string>(argv[1]);
    File2 = static_cast<string>(argv[2]);
    outputFile = (static_cast<string>(argv[3]));
    
    getInput(File1,File2); //receive input from File1 and File 2
    
    for(i = 0; i < NUM_THREADS; i++)
    {
        cout<<" Creating thread, " <<i<<endl;
        rc = pthread_create(&threads[i],NULL,matrix_mult,(void *)i);
        if(rc){ //create error
            cout<<"unable to create thread " <<rc<<endl;
            exit(-1);
        }
    }
    pthread_attr_destroy(&attr);
    for(i = 0; i < NUM_THREADS; i++)
    {
        rc = pthread_join(threads[i],&status);
        if(rc){ //create error
            cout<<"error: unable to join thread id: "<<i;
            cout<<"        Exiting with error status : "<<status<<endl;
            exit(-1);
        }
    }
    //print output file and finish
    cout<<"printing output matrix to output file...";
    print(outputFile);
    cout<<"Done"<<endl;
    
    return 0;
}
