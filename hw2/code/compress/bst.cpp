// nodes of BST
class  BSTNode 
{
	string element;
	int id;

	BSTNode* left;
	BSTNode* right;

	BSTNode(const string & s, const int & x, BSTNode* lt, BSTNode* rt)
	:element(s), id(x), left(lt), right(rt) {}

	friend class BST;
};

class BST
{
public:
	explicit BST(const int & notFound);	// constructor
	~BST();					// destructor

	const int & find (const string & s) const;	// find a string in BST, returns id
	
	void makeEmpty();				// makes BST empty

	void insert(const string & s, const int & x);	// insert string and id wrt string
	void remove(const string & s);			// find and remove string

private:
	BSTNode* root;		
	const int ITEM_NOT_FOUND;

	const int & elementAt(BSTNode* t) const;	// returns id

	void insert(const string & s, const int & x, BSTNode* & t) const;	// private insert
	void remove(const string & s, BSTNode* & t) const;			// private remove

	BSTNode* find(const string & s, BSTNode* t) const;			// private find
	BSTNode* findMin(BSTNode* t) const;					// private findMin
	
	void makeEmpty(BSTNode* & t) const;					// private makeEmpty
};

BST::BST(const int & notFound): ITEM_NOT_FOUND(notFound), root(NULL) {}

const int & BST::elementAt (BSTNode* t) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->id;
}

const int & BST::find(const string & s) const
{
	return elementAt(find(s, root));
}

BSTNode* BST::find(const string & s, BSTNode* t) const
{
	if (t == NULL)				// not found
		return NULL;
	else if (s < t->element)		// continue with left
		return find(s, t->left);
	else if (s > t->element)		// continue with right
		return find(s, t->right);
	else					// found
		return t;
}

BSTNode* BST::findMin(BSTNode* t) const
{
	if (t == NULL)		// not found
		return NULL;
	if (t->left == NULL)	// no left subtree
		return t;
	return findMin(t->left);	// continue with left
}

void BST::insert(const string & s, const int & x)
{
	insert(s, x, root);
}

void BST::insert(const string & s, const int & x, BSTNode* & t) const
{
	if (t == NULL)					// insert
		t = new BSTNode(s, x, NULL, NULL);	
	else if (s < t->element)			// continue with left
		insert(s, x, t->left);
	else if (s > t->element)			// continue with right
		insert(s, x, t->right);
	else ;						// duplicate
}

void BST::remove(const string & s)
{
	remove(s, root);
}

void BST::remove(const string & s, BSTNode* & t) const
{
	if (t == NULL)
		return;
	
	if (s < t->element)			// continue with left
		remove(s, t->left);
	
	else if (s > t->element)		// continue with right
		remove(s, t->right);
	
	else if (t->left != NULL && t->right != NULL)		// two child
	{
		t->element = findMin(t->right)->element;
		t->id = findMin(t->right)->id;
		remove(t->element, t->right);
	}
	
	else							// one child
	{
		BSTNode* oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}
}

void BST::makeEmpty()
{
	makeEmpty(root);
}

void BST::makeEmpty(BSTNode * & t) const
{
	if (t != NULL)
	{
		makeEmpty(t->left);		// makes left subtree empty
		makeEmpty(t->right);		// makes right subtree empty
		delete t;			// delete root
	}
	
	t = NULL;
}

BST::~BST()
{
	makeEmpty();
}
