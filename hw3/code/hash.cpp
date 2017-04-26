int nextprime(const int & x);	// finds the next smallest prime
bool isprime(const int & x);	// checks if the number is prime

int nextprime(const int & x)
{
	int xx = x;	

	while(!isprime(xx))
		xx++;
	
	return xx;
}

bool isprime(const int & x)
{
	int i;

	for (i = 2; i < x; i++)
		if (!(x % i))
			return false;
	
	return true;
}

class HashTable
{
public:
	explicit HashTable(int size = 10000);	// constructor

	void makeEmpty();			// makes the table empty

	// find, insert and remove returns the number of probes (negative if fails, positive o/w)

	int contains(const int & x) const;	// find
	int insert(const int & x);		// insert
	int remove(const int & x);		// remove

	enum EntryType {ACTIVE, EMPTY, DELETED};

	int getcurrentsize() const;	// accessor
	int gettotalsize() const;	// accessor
	
private:
	struct HashEntry
	{
		int element;
		EntryType info;

		HashEntry(const int & e = int(), EntryType i = EMPTY)
		: element(e), info(i) {}
	};

	vector<HashEntry> array;
	int currentSize;
	int totalSize;

	bool isActive(int currentPos) const;
	int findPos(const int & x, int & i) const;	// finds the position for operations

	int myhash(const int & x) const;		// hash function
};

int HashTable::getcurrentsize() const
{
	return currentSize;
}

int HashTable::gettotalsize() const
{
	return totalSize;
}

int HashTable::myhash(const int & x) const
{
	return x % totalSize;
}

HashTable::HashTable (int size) : array(nextprime(size)), totalSize(nextprime(size))
{
	makeEmpty();
}

void HashTable::makeEmpty()
{
	currentSize = 0;
	for (auto & entry : array)
		entry.info = EMPTY;
}

int HashTable::findPos(const int & x, int & i) const
{
	int currentPos = myhash(x);

	while(array[currentPos].info == ACTIVE && array[currentPos].element != x)
	{
		currentPos++;
		i++;

		if (currentPos >= array.size())
			currentPos -= array.size();
	}

	return currentPos; 
}

bool HashTable::isActive (int currentPos) const
{
	return array[currentPos].info == ACTIVE;
}

int HashTable::contains (const int & x) const
{
        int probe = 1;

        int dummy = findPos(x, probe);

        if (isActive(dummy))
                return probe;
        else
                return -1*probe;
}

int HashTable::insert (const int & x)
{
	int probe = 1;
	int currentPos = findPos(x, probe);

	if(isActive(currentPos))
		return -1*probe;

	array[currentPos].element = x;
	array[currentPos].info = ACTIVE;
	currentSize++;

	return probe;
}

int HashTable::remove(const int & x)
{
	int probe = 1;
	int currentPos = findPos(x, probe);

	if(!isActive(currentPos))
		return -1*probe;

	array[currentPos].info = DELETED;
	currentSize--;

	return probe;
}
