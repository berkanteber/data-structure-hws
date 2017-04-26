/********************

Berkan Teber 19080

********************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


// each element of the array has the code as index, string and a flag which indicates if it exists
struct dictElement
{
	string s;
	int flag;
};

int main()
{
	ifstream input;
	input.open("compout");

	ofstream output;
	output.open("decompout");

	dictElement dict[4096];


	// add all the elements to the dict
	for (int i = 0; i < 256; i++)
	{
		dict[i].s = i;
		dict[i].flag = 1;
	}

	int nextcode = 256;
	int prevcode, code;

	// for first code
	input >> code;
	output << dict[code].s;

	// for every other code
	prevcode = code;
	while (input >> code)
	{
		if(dict[code].flag)	// the code is in dictionary
		{
			output << dict[code].s;

			dict[nextcode].flag = 1;
			dict[nextcode].s = dict[prevcode].s + dict[code].s.at(0);
			nextcode++;
		}

		else			// not in dictionary
		{
			dict[nextcode].flag = 1;
			dict[nextcode].s = dict[prevcode].s + dict[prevcode].s.at(0);
			nextcode++;
			output << dict[prevcode].s + dict[prevcode].s.at(0);
		}

		prevcode = code;
	}

	input.close();
	output.close();

	return 0;
}
