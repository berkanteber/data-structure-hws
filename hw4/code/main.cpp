/*

	BERKAN TEBER 19080

*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "mpq.cpp"

// for array of x coordinates
class coordinate
{
public:
	int id, side, xcoord;

	bool operator<(coordinate rhs) {return (xcoord<rhs.xcoord)||(xcoord==rhs.xcoord && side < rhs.side) || (xcoord==rhs.xcoord && side == rhs.side && side == 1 && height > rhs.height) || (xcoord == rhs.xcoord && side == rhs.side && side == 2 && height < rhs.height);}
	
	coordinate operator=(coordinate rhs)
	{
		xcoord = rhs.xcoord;
		side = rhs.side;
		id = rhs.id;
		return *this;
	}
};

// for heap sort
void percDown(vector<coordinate> & a, int i, int n)
{
	int child;
	coordinate tmp;

	for (tmp = a[i]; 2*i+1 < n; i = child)
	{
		// left child
		child = 2*i+1;

		// compare left and right
		if (child != n-1 && a[child] < a[child+1])
			child++;

		// if necessary, percolate
		if (tmp < a[child])
			a[i] = a[child];
		else
			break;
	}

	a[i] = tmp;
}

// sort an array
void heapsort(vector<coordinate> & a)
{
	// empty array
	if(!a.size())
		return;

	// build heap
	for (int i = a.size()/2; i >= 0; i--)
		percDown(a, i, a.size());

	// sort
	for (int j = a.size() - 1; j > 0; j--)
	{
		// swap the max element with jth
		coordinate tmp = a[0];
		a[0] = a[j];
		a[j] = tmp;

		// percolate down 0th element
		percDown(a, 0, j);
	}
}

int main ()
{
	ifstream input;
	input.open("input.txt");

	int num, left, right, ctr;
	input >> num;

	// no building
	if (num == 0)
	{
		input.close();

		cout << 0 << " " << 0 << endl;

		return 0;
	}

	vector<int> heights(num+1);		// heights of the building - 1 to num
	vector<coordinate> coord(2*num);	// x-coordinates, side, id

	// for each building
	for (int i = 1; i <= num; i++)
	{
		input >> left >> heights[i] >> right;

		// left x-coord
		coord[ctr].id = i;
		coord[ctr].side = 1;
		coord[ctr].xcoord = left;
		ctr++;

		// right x-coord
		coord[ctr].id = i;
		coord[ctr].side = 2;
		coord[ctr].xcoord = right;
		ctr++;
	}

	// sort the coordinate array
	heapsort(coord);

	// heap
	MPQ myheap(num);

	int currentMax = -1;

	// in case of there is no building at 0
	if (coord[0].xcoord != 0)
		cout << 0 << " " << 0 << endl;

	// for each coordinate
	for (int i = 0; i < 2*num; i++)
	{
		// coordinate is a left coordinate - insert to heap
		if (coord[i].side == 1)
			myheap.insert(heights[coord[i].id], coord[i].id);

		// coordinate is  right coordinate - remove from heap
		else
			myheap.remove(coord[i].id);

		// if there is any change, print it
		if (myheap.getMax() != currentMax)
		{
			currentMax = myheap.getMax();
			cout << coord[i].xcoord << " " << currentMax << endl;
		}
	}

	// for the end (actually there is no such case in practice, but i put it to be safe)
	if (currentMax != 0)
		cout << coord[2*num-1].xcoord << " " << 0 << endl;

	input.close();

	return 0;
}
