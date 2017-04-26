/*

	BERKAN TEBER 19080

*/


#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;

#include "hash.cpp"

// for array
struct entry
{
	double probe;
	int transaction;
};


// for ratio (6:1:1, 4:2:2, 2:1:5)
int determinetype(const int & typedummy, const int & choice);

// prints to the files
void print(double** a10, double** a11, double** a20, double** a21, double** a30, double** a31, int s);

int main()
{
	// hash table of size 10000+
	HashTable mytable;

	int size = mytable.gettotalsize();	

	// 6 3x(size+1) arrays

        double** myarrays10 = new double*[4];
        for(int i = 1; i <= 3; i++)
                myarrays10[i] = new double[size+1];
        double** myarrays11 = new double*[4];
        for(int i = 1; i <= 3; i++)
                myarrays11[i] = new double[size+1];
        double** myarrays20 = new double*[4];
        for(int i = 1; i <= 3; i++)
                myarrays20[i] = new double[size+1];
        double** myarrays21 = new double*[4];
        for(int i = 1; i <= 3; i++)
                myarrays21[i] = new double[size+1];
        double** myarrays30 = new double*[4];
        for(int i = 1; i <= 3; i++)
                myarrays30[i] = new double[size+1];
	double** myarrays31 = new double*[4];
	for(int i = 1; i <= 3; i++)
		myarrays31[i] = new double[size+1];
	
	
	// for all 3 choices
	for(int i = 1; i <= 3; i++)
	{
		mytable.makeEmpty();

		// 6 arrays for 6 options

		entry* ary10 = new entry[size+1];
		entry* ary11 = new entry[size+1];
		entry* ary20 = new entry[size+1];
		entry* ary21 = new entry[size+1];
		entry* ary30 = new entry[size+1];
		entry* ary31 = new entry[size+1];

		// to get the same numbers
		srand(1);

		int typedummy, type, number, dummy, currentsize;

		// until 1000000 transactions or the table gets full
		int transaction = 0;
		while (transaction++ < 1000000 && mytable.getcurrentsize() < size)
		{
			// random operation
			typedummy = rand() % 8;		
			type = determinetype(typedummy, i);

			// random number
			number = rand() % 100000;

			currentsize = mytable.getcurrentsize();

			// insert
			if	(type == 1)
			{
				dummy = mytable.insert(number);

				if	(dummy < 0) // failed
				{
					ary10[currentsize].probe -= dummy;
					ary10[currentsize].transaction++;
				}
				else if	(dummy > 0) // OK
				{
					ary11[currentsize].probe += dummy;
					ary11[currentsize].transaction++;
				}
				else cout << "ERROR 1" << endl;
			}
			// delete
			else if	(type == 2)
			{
				dummy = mytable.remove(number);
				
				if      (dummy < 0) // failed
                                {
                                        ary20[currentsize].probe -= dummy;
                                        ary20[currentsize].transaction++;
                                }
                                else if (dummy > 0) // OK
                                {
                                        ary21[currentsize].probe += dummy;
                                        ary21[currentsize].transaction++;
                                }
                                else cout << "ERROR 2" << endl;
			}
			// find
			else if	(type == 3)
			{
				dummy = mytable.contains(number);
			
				if      (dummy < 0) // failed
                                {
                                        ary30[currentsize].probe -= dummy;
                                        ary30[currentsize].transaction++;
                                }
                                else if (dummy > 0) // OK
                                {
                                        ary31[currentsize].probe += dummy;
                                        ary31[currentsize].transaction++;
                                }
                                else cout << "ERROR 3" << endl;
			}
			else cout << "ERROR" << endl;
		}

		// get averages for each load factor
		for(int j = 0; j < size+1; j++)
		{
			if(ary10[j].transaction != 0)
				myarrays10[i][j] = ary10[j].probe / ary10[j].transaction;
			if(ary11[j].transaction != 0)
				myarrays11[i][j] = ary11[j].probe / ary11[j].transaction;
                    	if(ary20[j].transaction != 0)
				myarrays20[i][j] = ary20[j].probe / ary20[j].transaction;
        	        if(ary21[j].transaction != 0)
				myarrays21[i][j] = ary21[j].probe / ary21[j].transaction;
                	if(ary30[j].transaction != 0) 
				myarrays30[i][j] = ary30[j].probe / ary30[j].transaction;
	               	if(ary31[j].transaction != 0) 
				myarrays31[i][j] = ary31[j].probe / ary31[j].transaction;
		}		
	}

	// print to the documents
	print(myarrays10, myarrays11, myarrays20, myarrays21, myarrays30, myarrays31, size);
	
	return 0;
}

int determinetype(const int & typedummy, const int & choice)
{       
        if      (choice == 1)
        {       
                if      (typedummy <= 5)        return 1;
                else if (typedummy <= 6)        return 2;
                else                            return 3;
        }
        else if (choice == 2)
        {       
                if      (typedummy <= 3)        return 1;
                else if (typedummy <= 5)        return 2;
                else                            return 3;
        }
        else if (choice == 3)
        {       
                if      (typedummy <= 1)        return 1;
                else if (typedummy <= 2)        return 2;
                else                            return 3;
        }
        else    
                return 0;
}

void print(double** a10, double** a11, double** a20, double** a21, double** a30, double** a31, int s)
{
        ofstream out10, out11, out20, out21, out30, out31;

        out10.open("insertion_fail.txt");
        out11.open("insertion_success.txt");
        out20.open("deletion_fail.txt");
        out21.open("deletion_success.txt");
        out30.open("find_fail.txt");
        out31.open("find_success.txt");

	out10 << fixed << setprecision(4);
	out11 << fixed << setprecision(4);
	out20 << fixed << setprecision(4);
	out21 << fixed << setprecision(4);
	out30 << fixed << setprecision(4);
	out31 << fixed << setprecision(4);

	double r;
	
	for(int i = 0; i <= s; i++)
	{
		r = (double) i/s;

		out10 << r << "\t" << a10[1][i] << "\t" << a10[2][i] << "\t" << a10[3][i] << endl;
		out11 << r << "\t" << a11[1][i] << "\t" << a11[2][i] << "\t" << a11[3][i] << endl;
		out20 << r << "\t" << a20[1][i] << "\t" << a20[2][i] << "\t" << a20[3][i] << endl;
		out21 << r << "\t" << a21[1][i] << "\t" << a21[2][i] << "\t" << a21[3][i] << endl;
		out30 << r << "\t" << a30[1][i] << "\t" << a30[2][i] << "\t" << a30[3][i] << endl;
		out31 << r << "\t" << a31[1][i] << "\t" << a31[2][i] << "\t" << a31[3][i] << endl;
	}

	out10.close();
	out11.close();
	out20.close();
	out21.close();
	out30.close();
	out31.close();
}
