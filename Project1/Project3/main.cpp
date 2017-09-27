#include<iostream>

using namespace std;

/*************************************线性表链表描述**********************************/
template<typename K, typename E>
class sortedChain {
public:
	sortedChain() :dSize(0),fristNode(NULL) {}
	~sortedChain() {}
	int size()const { return dSize; }
	bool isEmpty()const { return dSize == 0; }
	void print()const;
	pair<const K, E>* find(const K& theKey);
	void insert(const pair<const K, E>& thePair);
	void erease(const K& theKey);
	
private:
	struct pairNode
	{
		pairNode() {}
		pairNode(const pair<K, E> &thePair, pairNode *next = NULL) :Pair(thePair),next(next) {}
		pairNode *next;
		pair<const K, E> Pair;
	};
	pairNode element;
	pairNode *fristNode;
	int dSize;
};
/*将链表打印出来*/
template<typename K, typename E>
void sortedChain<K, E>::print() const
{
	pairNode* cur = fristNode;
	while (cur) {
		cout << cur->Pair.first << ' ' << cur->Pair.second << endl;
		cur = cur->next;
	}
}
/*返回匹配的数对的指针,如果不存在，则返回NULL*/
template<typename K, typename E>
pair<const K, E>* sortedChain<K, E>::find(const K & theKey)
{
	pairNode* currentNode = fristNode;
	while (currentNode != NULL&&currentNode->Pair.first != theKey)
		currentNode = currentNode->next;
	if (currentNode != NULL&&currentNode->Pair.first == theKey)
		return &currentNode->Pair;
	return NULL;
}
/*往字典中插入thePair，如果已经存在则覆盖已经存在的匹配数对*/
template<typename K, typename E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{
	pairNode *current = fristNode, *pre = NULL;
	/*移动指针current*/
	while (current != NULL&&current->Pair.first < thePair.first) {
		pre = current;
		current = current->next;
	}
	if (current != NULL&&current->Pair.first == thePair.first) {
		current->Pair.second = thePair.second;
		return;
	}
	/*将thePair插在pre和current之间*/
	pairNode* tempNode = new pairNode(thePair, current);
	if (pre == NULL)fristNode = tempNode;
	else pre->next = tempNode;
	dSize++;
	return;
}
/*删除关键字为theKey的数对*/
template<typename K, typename E>
void sortedChain<K, E>::erease(const K & theKey)
{
	pairNode *current = fristNode, *pre = NULL;
	while (current != NULL&&current->Pair.first < theKey) {
		pre = current;
		current = current->next;
	}
	if (current != NULL&&current->Pair.first == theKey) {
		if (pre == NULL)fristNode = current->next;
		else pre->next = current->next;
		delete current;
		current = NULL;
		dSize--;
	}
}

/**********************线性表数组描述，使用一对平行数组，一个存储键，一个存储值基于有序数组的二分查找********************/

template<typename K, typename E>
class BinarySearchST {
public:
	BinarySearchST() :maxSize(2),size(0){
		key = new K[maxSize];
		val = new E[maxSize];
	}
	BinarySearchST(int num) :maxSize(num),size(0) {
		key = new K[maxSize];
		val = new E[maxSize];
	}
	~BinarySearchST() {
		delete[]key;
		delete[]val;
		key = NULL;
		val = NULL;
	}
	void insert(const K& key, const E& val);
	E* Find(const K& key)const;
	void erease(const K& theKey);
	bool contains(const K& key)const;
	bool isEmpty()const { return size == 0; }
	int getSize()const { return size; }
	K& min()const { return key[0]; }
	K& max()const { return key[size - 1]; }
	K* floor(const K& key)const;
	K* ceiling(const K& key)const;
	int Rank(const K& key)const;
	K& select(int k)const { return key[k]; }
	void deleteMin() { erease(select(0)); }
	void deleteMax() { erease(select(size - 1)); }
	int getSize(const K low, const K hight)const;
	void print()const;
	/*在const成员函数中调用的成员函数也必须是const*/
	E& operator[](const K& Key)const { return *Find(Key); }
private:
	void resize(int newSize);
	K* key;
	E* val;
	int size;
	int maxSize;
};

template<typename K, typename E>
void BinarySearchST<K, E>::insert(const K& Key, const E& Val)
{
	if (size == maxSize)resize(2 * maxSize);
	int j = Rank(Key);
	if (j < size&&Key == key[j]) {
		val[j] = Val;
		return;
	}
	for (int i = size; i > j; i--) {
		key[i] = key[i - 1];
		val[i] = val[i - 1];
	}
	key[j] = Key;
	val[j] = Val;
	size++;
}
/*返回键key对应的值(若键key不存在则返回NULL)*/
template<typename K, typename E>
E* BinarySearchST<K, E>::Find(const K & Key)const
{
	int j = Rank(Key);
	if (j < size&&Key == key[j])
		return val + j;
	else
		return NULL;
}

template<typename K, typename E>
void BinarySearchST<K, E>::erease(const K & theKey)
{
	int j = Rank(theKey);
	if (j < size&&theKey == key[j]) {
		for (int i = j + 1; i < size; i++) {
			key[i - 1] = key[i];
			val[i - 1] = val[i];
		}
		size--;
		if (size < maxSize / 4)resize(maxSize / 2);
		return;
	}
	else return;
}

template<typename K, typename E>
bool BinarySearchST<K, E>::contains(const K & key) const
{
	return Find(key);
}
//小于等于key的最大键
template<typename K, typename E>
K* BinarySearchST<K, E>::floor(const K & Key) const
{
	int j = Rank(Key);
	if (j < size&&Key == key[j])return key + j;
	else if (j > 0&&j <= size)return key + j - 1;
	else return NULL;
}
//大于等于key的最小键
template<typename K, typename E>
K* BinarySearchST<K, E>::ceiling(const K & Key) const
{
	int j = Rank(Key);
	if (j < size)return key + j;
	else return NULL;
}
/*二分法查找，返回键小于等于Key的个数*/
template<typename K, typename E>
int BinarySearchST<K, E>::Rank(const K & Key) const
{
	int low = 0, high = size;
	while (low < high) {
		int mid = low + (high - low) / 2;
		if (Key < key[mid])high = mid;
		else if (Key > key[mid])low = mid + 1;
		else return mid;
	}
	return low;
}

template<typename K, typename E>
int BinarySearchST<K, E>::getSize(const K low, const K hight) const
{
	if (low > hight)return -1;
	else return Rank(hight) - Rank(low);
}

template<typename K, typename E>
void BinarySearchST<K, E>::print() const
{
	for (int i = 0; i < size; i++)
		cout << key[i] << ' ' << val[i] << endl;
}

template<typename K, typename E>
void BinarySearchST<K, E>::resize(int newSize)
{
	K* newK = new K[newSize];
	E* newE = new E[newSize];
	int i = newSize < size ? newSize : size;
	for (int j = 0; j < i; j++) {
		newK[j] = key[j];
		newE[j] = val[j];
	}
	delete[]key; delete[]val;
	key = newK; val = newE;
	maxSize = newSize;
}

/****************************************二叉查找树******************************************/
template<typename K, typename V>
class BST {
public:
	BST() :root(NULL) {}
	int size()const { return size(root); }
	V* Find(const K Key)const { return Find(root, Key); }
	void insert(const K& Key, const V& Val) { root = insert(root, Key, Val); }
private:
	struct Node {
	public:
		Node() {}
		Node(const K &key,const V &val, int N = 1) :key(key), val(val), N(N), left(NULL), right(NULL) {}
	private:
		K key;                 //键
		V val;                 //值
		Node *left, *right;    //指向子树的指针
		int N;                 //以该节点为根节点的子树中节点总数
	};
	Node *root;                //二叉树的根节点
	int size(Node* x)const{
		if (Node == NULL)return 0;
		else		  return x->N;
	}
	V* Find(const Node* root,const K& Key)const;
	Node* insert(const Node* root, const K& Key, const V& Val);
};
/*以root为根节点的子树中查找并返回key所对应值的指针，找不到则返回NULL*/
template<typename K, typename V>
V * BST<K, V>::Find(const Node * root, const K & Key) const
{
	if (NULL == root)return NULL;
	if (Key > root->key)Find(root->right, Key);
	else if (Key < root->key)Find(root->left, Key);
	else return &(root->val);
}
/*类中的返回结构体指针的函数在类外实现,Node* BST<K, V>::insert(...)这么写会报错,不知道为什么。。。
  */
template<typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::insert(const Node * root, const K & Key, const V & Val)
{
	if (NULL == root)return new Node(Key, Val);
	if (Key > root->key)root = insert(root->left, Key, Val);
	else if (Key < root->key)root = insert(root->right, Key, Val);
	else root->val = Val;
	root->N = size(root->left) + size(root->right) + 1;
	return root;
}

int main() {
	BinarySearchST<char, int> ST;
	ST.insert('C', 1);
	ST.insert('E', 2);
	ST.insert('C', 3);
	ST.insert('D', 4);
	ST.insert('B', 8);
	ST.insert('G', 4);
	ST.erease('E');
	cout << ST['G'] << endl;
	ST.print();
	return 0;
}