/*
ListNode class
LinkedList class
wordElement class
*/


template <class Object>
class List;

template <class Object>
class ListNode; 

// list node class for a classic linked list
template <class Object>
class ListNode
{
public:
	ListNode(const Object & theElement = Object(), ListNode * n = NULL)
	 :element(theElement), next(n) {}

	Object element;
	ListNode* next;

private:
        bool operator!= (const ListNode & rhs)
        {       return element != rhs.element;	}

        bool operator== (const ListNode & rhs)
        {       return element == rhs.element;	}

        bool operator<=  (const ListNode & rhs)
        {       return element <= rhs.element;	}


	friend class List<Object>;
};

// linked list class with dummy header
template <class Object>
class List
{
public:
	List();
	~List();
	
	ListNode<Object>* zeroth() const;	// returns header
	ListNode<Object>* first() const;	// returns first element
	
	bool isEmpty() const;			// returns if the list is empty
        void makeEmpty();			// makes the list empty

	ListNode<Object>* findPE(const Object & x) const;	// returns a ptr to prev of searched
	ListNode<Object>* findE(const Object & x) const;	// returns a ptr to loc of searched
	ListNode<Object>* findLTE(const Object & x) const;	// finds with less than or equal
	ListNode<Object>* findAndInsert(const Object & x);	// searches and inserts if not exists


	void remove(const Object & x);		// finds and remove the object

	void intersect(const List & rhs);	// intersects the list with rhs

	int size() const;			// returns the number of elements
	
	const List & operator=(const List & rhs);	// assignment operator

private:
	ListNode<Object>* header;
};

template <class Object>
List<Object>::List()
{
	header = new ListNode<Object>;
}

template <class Object>
List<Object>::~List()
{
        makeEmpty();

        delete header;
}

template <class Object>
ListNode<Object>* List<Object>::zeroth() const
{
        return header;
}

template <class Object>
ListNode<Object>* List<Object>::first() const
{
        return header->next;
}

template <class Object>
bool List<Object>::isEmpty() const
{
	return header->next == NULL;
}

template <class Object>
void List<Object>::makeEmpty()
{
 	// remove first element until the list is empty
      	while(!isEmpty())
                remove(first()->element);
}

template <class Object>
ListNode<Object>* List<Object>::findPE(const Object & element) const
{
	// returns the prev loc for the search of an object
	// used with regular find to prevent from any bad cases

	ListNode<Object>* itr = header;

	while (itr->next != NULL && itr->next->element != element)
		itr = itr->next;
	
	return itr;
}

template <class Object>
ListNode<Object>* List<Object>::findE(const Object & element) const
{
	// returns the loc for the search of an object
	// returns NULL if unsuccessful

	ListNode<Object>* itr = header->next;

	while (itr != NULL && itr->element != element)
		itr = itr->next;

	return itr;
}

template <class Object>
ListNode<Object>* List<Object>::findLTE(const Object & element) const
{       
 	// returns the loc for the search of an object with lessthanorequal comparison	
	// returns the exact location if there exists such an object
	// returns the location to insert after if there is no exact object

	ListNode<Object>* itr = header->next;
	ListNode<Object>* prv = header;
        
        while (itr != NULL && itr->element <= element)
        {
		prv = itr;
		itr = itr->next;
        }	
	
        return prv;
}

template <class Object>
ListNode<Object>* List<Object>::findAndInsert(const Object & element)
{
	// searches the list
	// if there is a match, returns the location
	// otherwise inserts and returns the location

	ListNode<Object>* itr = findLTE(element);

	// exact match
	if (itr != NULL && itr->element == element)
		return itr;
	else	// no match
	{
		ListNode<Object>* next = itr->next;
		itr->next = new ListNode<Object> (element, itr->next);
	
		return itr->next;			
	}
}

template <class Object>
void List<Object>::remove(const Object & element)
{
	// finds and removes the element
	// doesn't remove anything if not found

	if (findE(element) == NULL)
		return;

	ListNode<Object>* p = findPE(element);

	if(p != NULL)
	{
		ListNode<Object>* oldNode = p->next;
		p->next = p->next->next;
		delete oldNode;
	}
}

template <class Object>
void List<Object>::intersect(const List<Object> & rhs)
{
	// intersects the list with rhs
	// goes trough all the elements in the list and checks if it exists in rhs, remove if not 

	ListNode<Object>* itr = first();
	for (;itr != NULL; itr=itr->next)
	{
		if (rhs.findE(itr->element) == NULL)
			remove(itr->element);
	}
}

template <class Object>
int List<Object>::size() const
{
	// returns the number of elements

	ListNode<Object>* itr = first();
	int cntr = 0;

	while (itr != NULL)
	{
		cntr++;
		itr = itr->next;
	}
	
	return cntr;
}

template <class Object>
const List<Object> & List<Object>::operator=(const List<Object> & rhs)
{
	// assignment operator

	if (rhs.isEmpty())
	{
		makeEmpty();
		return *this;
	}

	if(this != &rhs)
	{
		makeEmpty();
	
		ListNode<Object>* ritr = rhs.first();

		for (; ritr != NULL;ritr = ritr->next)
			findAndInsert(ritr->element);
	}
	
	return *this;
}

// used to construct a list with element type of wordElement
// a wordElement consists a word and a list of int
class wordElement
{
public: 
        wordElement() : word(), list(new List<int>) {}
        wordElement(const string & s) : word(s), list(new List<int>) {}
        
        string word;
        List<int>* list;

private:        
        bool operator!= (const wordElement & rhs)
        {       return word != rhs.word;        }
        
        bool operator== (const wordElement & rhs)
        {       return word == rhs.word;        }
        
        bool operator<=  (const wordElement & rhs)
        {       return word <= rhs.word;         }

        
        friend class List<wordElement>;
        friend class ListNode<wordElement>;
};
