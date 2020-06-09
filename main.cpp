/*
    Name: Muhammad Saaim Qureshi
    Reg: 2019444

    Name: Muwahid Asim
    Reg: 2019352
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define INPUT_FILE "./sample_inputs/example3-20x10.txt"
#define OUTPUT_FILE "result_addition.txt"

class ArrayPoly
{
    int* polynomial, numOfCoff;

public:
    static int currentG; // CURRENT LOCATION OF GETTER POINTER

    ArrayPoly(){};
    ArrayPoly(int numOfCoff)
    {

        ifstream data;
        data.open(INPUT_FILE);
        this -> numOfCoff = numOfCoff;

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

    int* getPoly()
    {
        return polynomial;
    }

    ArrayPoly addPoly(ArrayPoly p2)
    {
        ArrayPoly tempPoly(numOfCoff);
        for (int i = 0; i < numOfCoff; i++)
            tempPoly.polynomial[i] = polynomial[i] + p2.polynomial[i];

        return tempPoly;
    }





};

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
        void displayscreen(int p,int c)
        {
            node* ptrtemp = listheadptr;
            cout << endl;
           
            cout << "Polynomial after addition: ";
                
                while (ptrtemp != NULL)
                { 
                    if(ptrtemp->next==NULL)
                    cout << ptrtemp->num << "x" << ptrtemp->coefficient ;
                    else
                    cout << ptrtemp->num << "x" << ptrtemp->coefficient << " + ";
                    ptrtemp = ptrtemp->next;
                }
        
                node* ptrtemp2 = listheadptr;
                cout << endl <<endl;

                cout << "In the format of txt files given addition is: "<<endl<<p<<endl<<c<<endl;

                while (ptrtemp2 != NULL)
                {
                    
                        cout << ptrtemp2->num << " " ;
                    ptrtemp2 = ptrtemp2->next;
                }

                
           }


        void displayfile(int p, int c)
        {
            node* ptrtemp = listheadptr;
            cout << endl;

            ofstream added;
            added.open(OUTPUT_FILE);

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
            added << "In the format of txt files given addition is:" <<endl<< p << endl << c << endl;
            node* ptrtemp2 = listheadptr;
            while (ptrtemp2 != NULL)
            {   
                
                added << ptrtemp2->num<<" ";
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
    data.open(INPUT_FILE);
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
        total.displayscreen(polynomials,coef);
        total.displayfile(polynomials,coef);
        data.close();
    
    cout << endl;
    
}

int ArrayPoly::currentG = 0;

void array_init(ArrayPoly *polys, int numOfPolys, int numOfCoff)
{
    for(int i = 0; i < numOfPolys; i++)
        polys[i] = ArrayPoly(numOfCoff);
}

void sumOfArrayPoly()
{
    int numOfPolys, numOfCoff;

    fstream data;
    data.open(INPUT_FILE, ios::in);
    data >> numOfPolys >> numOfCoff;
    ArrayPoly::currentG = data.tellg();
    data.close();

    ArrayPoly *polys = new ArrayPoly[numOfPolys + 1];
    array_init(polys, numOfPolys + 1, numOfCoff);

    polys[numOfPolys] = polys[0].addPoly(polys[1]);

    for (int i = 2; i < numOfPolys; i++)
        polys[numOfPolys] = polys[i].addPoly(polys[numOfPolys]);

    data.open(OUTPUT_FILE, ios::out);

    data << "Polynomial after addition: ";
    for (int i = 0; i < numOfCoff; i++)
    {
        if(i == numOfCoff - 1)
            data << polys[numOfPolys].getPoly()[i] << "x" << i;
        else
           data << polys[numOfPolys].getPoly()[i] << "x" << i << " + "; 
    }

    data << "\n\nIn the format of txt files given after addition is:\n";
    data << numOfPolys << endl << numOfCoff << endl;
    for(int i = 0; i < numOfCoff; i++)
    {
        data << polys[numOfPolys].getPoly()[i] << " ";
    }


    data.close();

    data.open(OUTPUT_FILE, ios::in);

    string newPolyOutput;
    

    while(!data.eof())
    {
        getline(data, newPolyOutput);
        cout << newPolyOutput << endl;
    }   

    data.close();
}

int main()
{
    int choice;
  
    cout << "Please enter the number correnspoding to your choice: ";
    cin >> choice, cout << endl;

    switch (choice)
    {
    case 1:
        sumOfArrayPoly();
        break;
    
    case 2:
        usinglinkedlist();
        break;

    default:
        cout << "Invalid choice!\n";
        break;
    }
    

    


    return 0;
    
   
}

