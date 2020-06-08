#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define INPUT_FILE "./sample_inputs/example1-10x5.txt"
#define OUTPUT_FILE "result_addition.txt"

class ArrayPoly
{
    int *polynomial, numOfCoff;
    static int currentG; // CURRENT LOCATION OF GETTER POINTER

    public:
        ArrayPoly()
        {

            ifstream data;
            data.open(INPUT_FILE);
            data.seekg(2, ios::beg);
            data >> numOfCoff;
        
            polynomial = new int[numOfCoff];

            if(currentG != -1)
            {
                data.seekg(currentG, ios::beg);
                for(int i = 0; i < numOfCoff; i++)
                    data >> polynomial[i];

                currentG = data.tellg(); // UPDATING CURRENT GETTER POINTER LOCATION FOR NEXT POLY
            }

            data.close();
        }

        ~ArrayPoly()
        {
            polynomial = NULL;
            delete[] polynomial;
        }
/*
        int calculateSum(int X)
        {
            int sum = 0;
            for(int n = 0; n < numOfCoff; n++)
            {
                sum += polynomial[n] * pow(X, n); 
            }

            return sum;

        } */

        int *getPoly()
        {
          return polynomial;
        }

        ArrayPoly addPoly(ArrayPoly p2)
        {
            ArrayPoly tempPoly;
            
            for(int i = 0; i < numOfCoff; i++)
                tempPoly.polynomial[i] = polynomial[i] + p2.polynomial[i];

            return tempPoly;
        }



        

};

void sumOfArrayPoly();


int ArrayPoly::currentG = 5;

int main()
{
    int X = 2;
    
    sumOfArrayPoly();


    return 0;
}

void sumOfArrayPoly()
{
    int numOfPolys, numOfCoff;

    fstream data;
    data.open(INPUT_FILE, ios::in);
    data >> numOfPolys >> numOfCoff;
    data.close();

    ArrayPoly polys[numOfPolys + 1];
    
    polys[numOfPolys] = polys[0].addPoly(polys[1]);

    for(int i = 2; i < numOfPolys; i++)
        polys[numOfPolys] = polys[i].addPoly(polys[numOfPolys]);

    data.open(OUTPUT_FILE, ios::out);

    data << "New Polynomial = ";
    for(int i = 0; i < numOfCoff; i++)
    {
        data << polys[numOfPolys].getPoly()[i] << " ";
    }

    data.close();

    data.open(OUTPUT_FILE, ios::in);

    string newPoly;
    getline(data, newPoly);

    cout << newPoly << endl;

    data.close();
}