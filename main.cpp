

#include <iostream>
#include <fstream>
#include <cmath>


using namespace std;

#define INPUT_FILE "./sample_inputs/example1-10x5.txt"
#define OUTPUT_FILE "result_addition.txt"

class ArrayPoly
{
    int* polynomial, numOfCoff;
    static int currentG; // CURRENT LOCATION OF GETTER POINTER

public:
    ArrayPoly()
    {

        ifstream data;
        data.open(INPUT_FILE);
        data.seekg(2, ios::beg);
        data >> numOfCoff;

        polynomial = new int[numOfCoff];

        if (currentG != -1)
        {
            data.seekg(currentG, ios::beg);
            for (int i = 0; i < numOfCoff; i++)
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

    int* getPoly()
    {
        return polynomial;
    }

    ArrayPoly addPoly(ArrayPoly p2)
    {
        ArrayPoly tempPoly;

        for (int i = 0; i < numOfCoff; i++)
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

    for (int i = 2; i < numOfPolys; i++)
        polys[numOfPolys] = polys[i].addPoly(polys[numOfPolys]);

    data.open(OUTPUT_FILE, ios::out);

    data << "New Polynomial = ";
    for (int i = 0; i < numOfCoff; i++)
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

void usinglinkedlist()
{
    int polynomials = 0, coef = 0, num;

    ifstream data;
    data.open("example.txt");
    data >> polynomials;
    data >> coef;
    linkedlist list, total;
    int x = 0;
    for (int i = 0; i < polynomials; i++)
    {
        for (int j = 0; j < coef;j++)
        {

            data >> num;
            list.addnode(num, j);
            if (x < coef)
            {
                total.addnode(num, j);
                x++;

            }
            else
                total.sum(num, j);

        }
    }
    total.displayscreen(coef);
    total.displayfile(polynomials, coef);
    data.close();

    cout << endl;





}

class linkedlist
{
private:
    struct node
    {

        int num;
        int coefficient;
        node* next;
    };
    node* listheadptr;
   
    

public:
    linkedlist()
    {
        listheadptr = NULL;
    }
    void addnode(int x, int y)
    {
        node* ptrnew = new node;
        node* ptrtemp = listheadptr;
        ptrnew->num = x;
        ptrnew->coefficient = y;
        ptrnew->next = NULL;

        if (listheadptr == NULL)
        {
            listheadptr = ptrnew;
            return;
        }
        while (ptrtemp->next != NULL)
            ptrtemp = ptrtemp->next;

        
            ptrtemp->next = ptrnew;
        
    }
        void displayscreen(int c)
        {
            node* ptrtemp = listheadptr;
            cout << endl;
           
            cout << "Addition of polynomials is:  ";
                
                while (ptrtemp != NULL)
                { 
                    if(ptrtemp->next==NULL)
                    cout << ptrtemp->num << "x" << ptrtemp->coefficient ;
                    else
                    cout << ptrtemp->num << "x" << ptrtemp->coefficient << " + ";
                    ptrtemp = ptrtemp->next;
                }
        
                
           }


        void displayfile(int p, int c)
        {
            node* ptrtemp = listheadptr;
            cout << endl;

            ofstream added;
            added.open("resut_addition.txt");

            added << "Polynomial after addition: ";
            while (ptrtemp != NULL)
            {
                if (ptrtemp->next == NULL)
                added << ptrtemp->num << "x" << ptrtemp->coefficient ;
                else
                    added << ptrtemp->num << "x" << ptrtemp->coefficient << " + ";
                ptrtemp = ptrtemp->next;
            }
            added << endl << endl;
            added << " In the format of txt files given addition is:" <<endl<< p << endl << c << endl;
            node* ptrtemp2 = listheadptr;
            while (ptrtemp2 != NULL)
            {   
                
                added << ptrtemp2->num<<"\t";
                ptrtemp2 = ptrtemp2->next;
            }

            added.close();
        }
        void sum( int n, int c)
        {
           
            node* tempptr = listheadptr;
            while (tempptr != NULL)
            {
                if (tempptr->coefficient == c)
                {
                    tempptr->num = tempptr->num + n;
                    return;
                }
                else
                    tempptr = tempptr->next;

            }

        }
        ~linkedlist()
        {
            node* ptrprevious;
            while (listheadptr != NULL)
            {
                ptrprevious = listheadptr;
                listheadptr = listheadptr->next;
                delete ptrprevious;
            }
     }


};


void usinglinkedlist()
{
    int polynomials=0, coef=0,num;
    
    ifstream data;
    data.open("./sample_inputs/example1-10x5.txt");
    data >> polynomials;
    data >> coef;
    linkedlist list,total;
    int x = 0;
        for (int i=0 ; i < polynomials; i++)
        {
            for (int j = 0; j<coef;j++)
            { 

                data >> num;
                list.addnode(num, j);
                if(x<coef)
                {
                    total.addnode(num, j);
                    x++;

                }
                else
                total.sum(num,j);

            }
        }
        total.displayscreen(coef);
        total.displayfile(polynomials,coef);
        data.close();
    
    cout << endl;
    
   



}

int main()
{
    usinglinkedlist();


    return 0;
    
   
}

