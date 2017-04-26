/******************************
	BERKAN TEBER 19080
******************************/

#define NDEBUG

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "19080-berkanteber-list.cpp"

// prints the list
void printList(const List<wordElement> & theList)
{
	ListNode<wordElement>* itr = theList.first();
	while(itr != NULL) // for each word
        {       
		cout << itr->element.word << ": ";

	       	ListNode<int>* itrtr = itr->element.list->first();
               	while(itrtr != NULL) // for each document
               	{
                       cout << itrtr->element << " ";
	               itrtr = itrtr->next;
		}

                cout << endl;
        	itr = itr->next;
        }

	cout << endl;
}

int main()
{
	// complete list
	List<wordElement> theList;

	ifstream input;
	input.open("docdb.txt");	
	
	int docno;
	string word;

	while(input >> word) // until EOF
	{
		// find the word in the list or insert it if it doesn't exist
		ListNode<wordElement>* ptr = theList.findAndInsert(wordElement(word));
	
		input >> docno;	

		// search the doc no in the list of the word and insert if it doesn't exist
		ptr->element.list->findAndInsert(docno);		
	}

	input.close();

#ifdef DEBUG
	printList(theList);	// to see the complete list
#endif

	// keeps track of the intersected list
	List<int> result;

	int wordcount;
	while (cin>>wordcount && wordcount)	// until wordcount is 0
	{
		string qword;
		for (int i = 0; i < wordcount; i++)
		{
			cin >> qword;
			
			// find the word
			ListNode<wordElement>* p = theList.findE(wordElement(qword));

			if (p == NULL) 	// word doesn't exist
			{
				result.makeEmpty();	// result is empty
			}
			else		// word is found 
			{
				if (i == 0)	// for first word in query
				{
					// assign the doc list of the word to result
					result = (*(p->element.list));
				}
				else		// for other words
				{	
					// intersect the doc list with result 
					result.intersect(*(p->element.list));
				}
			}
			
			cout << qword << " ";
		}
		
		cout << result.size() << " ";	
	
		// print result
		if (!result.isEmpty())
		{
			ListNode<int>* itr = result.first();		
			for (;itr != NULL; itr = itr->next, cout << " ")
				cout << itr->element;	
		}
		
		cout << endl;
	}
	
	// empty the doc lists for each word
	while(!theList.isEmpty())
	{
		ListNode<wordElement>* itr = theList.first();
		delete itr->element.list;
		theList.remove(itr->element);
	}

	return 0;
}
