struct element		// element of the heap
{
	int value;
	int label;
};

class MPQ		// modified priority queue
{
public:
	// constructor - takes an integer as size and constructs the arrays for the heap and the loc
	MPQ(int size = 0) : array(size+1), locations(size+1) { currentSize = 0;	} 
	
	// deconstructor
	~MPQ() {}

	void insert (int value, int label);	// insert the element to the heap
	int remove (int label);			// remove the labeled element and returns the value

	int getMax() const;			// gets the maximum value

	bool isEmpty() const;			// checks if the heap is empty

	void print() const;			// prints both arrays

private:
	int currentSize;			// keeps track of current size

	vector<element> array;			// heap array
	vector<int> locations;			// locations array

	void percolateDown (int hole);		// to percolate down
};

void MPQ::insert (int value, int label)
{
	// create a hole and poercolate it up
	int hole = ++currentSize;
	for (; hole > 1 && value > array[hole/2].value; hole /= 2)
	{
		array[hole].value = array[hole/2].value;
		array[hole].label = array[hole/2].label;

		// update location in each time
		locations[array[hole].label] = hole;
	}
	
	// set the values for the hole
	array[hole].value = value;
	array[hole].label = label;

	// update location
	locations[array[hole].label] = hole;
}

int MPQ::remove (int label)
{
	// return 0 if the heap is empty or there doesn't exist the labeled item
	if (isEmpty() || !locations[label])
		return 0;

	// swap the labeled item with the last item in the heap

	int value = array[locations[label]].value;

	array[locations[label]].value = array[currentSize].value;
	array[locations[label]].label = array[currentSize].label;
	currentSize--;

	// percolate down the item for correct position
	percolateDown(locations[label]);

	// update the location as 0
	locations[label] = 0;

	return value;	
}

int MPQ::getMax() const
{
	// if empty, return 0
	if (isEmpty())	
		return 0;
	
	// return the max value
	return array[1].value;
}

bool MPQ::isEmpty() const
{
	// return the emptiness status

	if (currentSize)	return false;
	else			return true;
}

void MPQ::percolateDown(int hole)
{
	int child;
	
	int value = array[hole].value;
	int label = array[hole].label;


	// percolate the hole
	for(; hole * 2 <= currentSize; hole = child)
	{
		child = hole*2;

		// compare left and right child
		if (child != currentSize && array[child + 1].value > array[child].value)
			child++;

		// if necessary percolate 
		if (array[child].value > value)
		{
			array[hole].value = array[child].value;
			array[hole].label = array[child].label;

			locations[array[hole].label] = hole;
		}
		else	
			break;
	}

	// set the values for the hole
	array[hole].value = value;
	array[hole].label = label;

	locations[array[hole].label] = hole;
}

void MPQ::print() const
{
	// for heap
	cout << endl << "array:" << endl;
	for (int i = 1; i <=currentSize; i++)	
		cout << i << ":" << array[i].value << " ";
/*
	// for locations
	cout << endl << "locations:" << endl;
	for (int i = 1; i < locations.size(); i++)
		cout << i << ":" << locations[i] << " ";
*/

	cout << endl;	
}
