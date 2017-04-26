/********************

Berkan Teber 19080

********************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "bst.cpp"

int main()
{
	ifstream input;
	input.open("compin");

	ofstream output;
	output.open("compout");

	// not found returns -1
	BST dict(-1);

	int code = 256;

	int outcode;
	string oldp, p;
	char ch;
	int dummy;

	int ctr = 0;

	bool notEmpty = false;

	// for every char
	while (input.get(ch))
	{
		if (ch == 13)
			continue;

		notEmpty = true;

		// add ch to p
		p.push_back(ch);

		dummy = dict.find(p);

		// p is not in dict
		if(p.length() > 1 && dummy == -1)
		{
			// add p into dict
			dict.insert(p, code++);

			// determine the code of oldp (p - ch)
			if (oldp.length() == 1) outcode = oldp.at(0);
			else			outcode = dict.find(oldp);

			// write it
			output << outcode << " ";

			// p becomes only ch
			p = ch;
		}

		// oldp becomes p
		oldp = p;
	}

	if (notEmpty)
	{
		// for last output
		if (oldp.length() == 1) outcode = oldp.at(0);
		else			outcode = dict.find(oldp);

		output << outcode;
	}

	dict.makeEmpty();

	input.close();
	output.close();

	return 0;
}
