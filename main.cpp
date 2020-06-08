#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define FILE "./sample_inputs/example1-10x5.txt"

class ArrayPoly
{
    int *polynomial, numOfCoff;
    static int currentG; // CURRENT LOCATION OF GETTER POINTER

    public:
        ArrayPoly()
        {

            ifstream data;
            data.open(FILE);
            data.seekg(2, ios::beg);
            data >> numOfCoff;
           
           polynomial = new int[numOfCoff];

            data.seekg(currentG, ios::beg);
            for(int i = 0; i < numOfCoff; i++)
                data >> polynomial[i];

            currentG = data.tellg(); // UPDATING CURRENT GETTER POINTER LOCATION FOR NEXT POLY

            data.close();
           
        }

        int calculateSum(int X)
        {
            int sum = 0;
            for(int n = 0; n < numOfCoff; n++)
            {
                sum += polynomial[n] * pow(X, n); 
            }

            return sum;

        }

        

};

int calculateSumOfArrayPoly(ArrayPoly polys[], int numOfPoly, int var)
{
    int sum = 0;
    for(int i = 0; i < numOfPoly; i++)
        sum += polys[i].calculateSum(var);
    return sum;
}

int ArrayPoly::currentG = 5;

int main()
{
    int X = 2;
    ArrayPoly polys[10];
    for(int i = 0; i < 10; i++)
        cout << polys[i].calculateSum(X) << " + ";
    
    cout << endl << "= " << calculateSumOfArrayPoly(polys, 10, X);
    



    return 0;
}