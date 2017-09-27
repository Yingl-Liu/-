#include<iostream>

using namespace std;

/*************************************���Ա���������**********************************/
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
/*�������ӡ����*/
template<typename K, typename E>
void sortedChain<K, E>::print() const
{
	pairNode* cur = fristNode;
	while (cur) {
		cout << cur->Pair.first << ' ' << cur->Pair.second << endl;
		cur = cur->next;
	}
}
/*����ƥ������Ե�ָ��,��������ڣ��򷵻�NULL*/
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
/*���ֵ��в���thePair������Ѿ������򸲸��Ѿ����ڵ�ƥ������*/
template<typename K, typename E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{
	pairNode *current = fristNode, *pre = NULL;
	/*�ƶ�ָ��current*/
	while (current != NULL&&current->Pair.first < thePair.first) {
		pre = current;
		current = current->next;
	}
	if (current != NULL&&current->Pair.first == thePair.first) {
		current->Pair.second = thePair.second;
		return;
	}
	/*��thePair����pre��current֮��*/
	pairNode* tempNode = new pairNode(thePair, current);
	if (pre == NULL)fristNode = tempNode;
	else pre->next = tempNode;
	dSize++;
	return;
}
/*ɾ���ؼ���ΪtheKey������*/
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

/**********************���Ա�����������ʹ��һ��ƽ�����飬һ���洢����һ���洢ֵ������������Ķ��ֲ���********************/

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
	/*��const��Ա�����е��õĳ�Ա����Ҳ������const*/
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
/*���ؼ�key��Ӧ��ֵ(����key�������򷵻�NULL)*/
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
//С�ڵ���key������
template<typename K, typename E>
K* BinarySearchST<K, E>::floor(const K & Key) const
{
	int j = Rank(Key);
	if (j < size&&Key == key[j])return key + j;
	else if (j > 0&&j <= size)return key + j - 1;
	else return NULL;
}
//���ڵ���key����С��
template<typename K, typename E>
K* BinarySearchST<K, E>::ceiling(const K & Key) const
{
	int j = Rank(Key);
	if (j < size)return key + j;
	else return NULL;
}
/*���ַ����ң����ؼ�С�ڵ���Key�ĸ���*/
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

/****************************************���������******************************************/
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
		K key;                 //��
		V val;                 //ֵ
		Node *left, *right;    //ָ��������ָ��
		int N;                 //�Ըýڵ�Ϊ���ڵ�������нڵ�����
	};
	Node *root;                //�������ĸ��ڵ�
	int size(Node* x)const{
		if (Node == NULL)return 0;
		else		  return x->N;
	}
	V* Find(const Node* root,const K& Key)const;
	Node* insert(const Node* root, const K& Key, const V& Val);
};
/*��rootΪ���ڵ�������в��Ҳ�����key����Ӧֵ��ָ�룬�Ҳ����򷵻�NULL*/
template<typename K, typename V>
V * BST<K, V>::Find(const Node * root, const K & Key) const
{
	if (NULL == root)return NULL;
	if (Key > root->key)Find(root->right, Key);
	else if (Key < root->key)Find(root->left, Key);
	else return &(root->val);
}
/*���еķ��ؽṹ��ָ��ĺ���������ʵ��,Node* BST<K, V>::insert(...)��ôд�ᱨ��,��֪��Ϊʲô������
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