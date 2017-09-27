#ifndef PRACTICE_H
#define PRACTICE_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<iterator>
#include <random>

typedef std::default_random_engine random_engin;

class FixedCapacityStackOfStrings
{
public:
	FixedCapacityStackOfStrings(int cap);
	~FixedCapacityStackOfStrings();
	std::string pop();
	void push(std::string item);
	bool isEmpty();
	int size();
private:
	std::string *a;
	int n;
};

/*定义一个模板类，stack*/
template <typename T> class FixedCapacityStack
{
public:
	FixedCapacityStack() {}
	FixedCapacityStack(size_t cap);
	~FixedCapacityStack();
	bool isEmpty() { return n == 0; }
	T pop();
	void push(const T& item);
	size_t size() { return n; }
	/*下压堆栈链表实现*/
	void push_node(const T &item);
	T pop_node();
	/*链表实现队列*/
	void queue_push(const T &item);
	T queue_pop();
	/*删除并返回最早插入的第k个元素*/
	T del(size_t k);
private:
	T *a;
	size_t n;
	size_t maxLength;
	void resize(size_t size);
	/*链表*/
	struct Node {
		Node():item(NULL){}
		Node(const T & i) :item(i), next(NULL){}
		T item;
		Node *next;
	};
	//头结点，指向最早添加节点的链接
	Node *frist;
	Node *last;//指向最近添加节点的链接
};

template <typename T>
FixedCapacityStack<T>::FixedCapacityStack(size_t cap)
{
	a = new T[cap];
	maxLength = cap;
	n = 0;
}

template <typename T>
FixedCapacityStack<T>::~FixedCapacityStack()
{
	delete[] a;
	a = NULL;
}

template<typename T>
inline T FixedCapacityStack<T>::pop()
{
	T item = a[--n];
	if (n > 0 && n < maxLength / 4)
		resize(maxLength / 2);
	return item;
}

template<typename T>
inline void FixedCapacityStack<T>::push(const T & item)
{
	if (n == maxLength)
		resize(2 * maxLength);
	a[n++] = item;
}

template<typename T>
inline void FixedCapacityStack<T>::push_node(const T & item)
{
	Node *oldfrist = frist;
	frist = new Node(item);
	frist->next = oldfrist;
	n++;
}

template<typename T>
inline T FixedCapacityStack<T>::pop_node()
{
	T item = frist->item;
	Node *newfrist = frist->next;
	delete frist;
	frist = NULL;
	frist = newfrist;
	n--;
	return item;
}

template<typename T>
inline void FixedCapacityStack<T>::queue_push(const T & item)
{
	Node *oldlast = last;
	last = new Node(item);
	if (isEmpty())
		frist = last;
	else
		oldlast->next = last;
	n++;
}

template<typename T>
inline T FixedCapacityStack<T>::queue_pop()
{
	T item;
	if (!isEmpty())
	{
		Node *newfrist = frist->next;
		item = frist->item;
		delete frist;
		frist = NULL;
		frist = newfrist;
		n--;
	}
	else
		last = NULL;
	return item;
}

template<typename T>
inline T FixedCapacityStack<T>::del(size_t k)
{
	Node *pre, *cur = frist;
	T item;
	int i = 1;
	if (1 == k && cur) {
		n--; 
		item = cur->item;
		frist = cur->next;
		delete frist;
		frist = NULL;
	}
	while (i < k) {
		pre = cur;
		cur = cur->next;
		i++;
		if (i == k)
		{
			n--;
			item = cur->item;
			pre->next = cur->next;
			delete cur;
			cur = NULL;
			break;
		}
	}
	return item;
}

template<typename T>
inline void FixedCapacityStack<T>::resize(size_t size)
{	//在堆中new[]出一个新的数组，再从旧数组把数据搬移到新的数组，最后在删除旧的数组......
	T *pTemp = new T[size];
	size_t min= (size < n) ? size:n;
	for (size_t i = 0; i < min; i++)
		pTemp[i] = a[i];
	delete []a;
	a = NULL;
	a = pTemp;
	maxLength = size;
}


/*动态连通性，union-find算法实现*/
class UF {
public:
	UF(int N) {
		count = N;
		maxSize = N;
		id = new int[N];
		size = new int[N];
		for (int i = 0; i < N; i++) {
			id[i] = i;
			size[i] = 1;
		}
	}
	~UF() {
		delete []id;
		delete[]size;
		id = NULL;
		size = NULL;
	}
	size_t getCount(){
		return count;
	}
	bool connected(int p, int q) {
		return id[p] == id[q];
	}
	/*quick-find算法*/
	int find(int p) {
		//找出分量名称
		return id[p];
	}
	/*将p,q归并到相同的分量中，每次find()调用只需要访问数组一次，归并两个分量访问数组次数在(N+3)到(2N+1)之间
	假设使用该算法解决动态连通性问题并且到最后只得到一个连通分量，那么这至少需要用N-1次union()方法。即至少要
	(N+3)(N-1)约为N^2次数组访问，该算法是平方级别的。

	*/
	void Union(int p, int q) {
		int pId = find(p);
		int qId = find(q);
		if (pId == qId)
			return;
		else
			for (int i = 0; i < maxSize; i++)//将p分量归并到q分量中
				if (id[i] == pId)
					id[i] = qId;
		count--;
	}
	/*带权值的quick-union算法,最优化算法*/
	int qu_find(int p) {
		while (p != id[p]) {
			id[p] = id[id[p]];//路径压缩，将p节点的父节点设置为它的爷爷节点
			p = id[p];
		}
		return p;
	}
	void qu_union(int p, int q) {
		int pRoot = qu_find(p);
		int qRoot = qu_find(q);
		if (pRoot == qRoot)return;
		else if(size[pRoot] > size[qRoot]){
			id[qRoot] = pRoot;
			size[pRoot] += size[qRoot];
		}
		else {
			id[pRoot] = qRoot;
			size[qRoot] += size[pRoot];
		}
		count--;
	}
private:
	int *id;
	int *size;
	size_t count;
	int maxSize;
};

/*排序*/
void selection_sort(double *a, const int num);	//选择排序
void insert_sort(double *a, const int num);		//插入排序
void shell_sort(double *a, const int num);		//希尔排序

/*递归实现选择排序，但递归深度不宜太深，四千次就Stack overflow，报错*/
template<typename type>
void select(type *a, int low, int high) {
	if (low >= high)return;
	double t = a[low];
	for (int i = low + 1; i <= high; i++)
		t = t < a[i] ? t : a[i];
	a[low] = t;
	select(a, ++low, high);
}

template<typename type>
bool isSorted(type *a, const int num) {
	for (int i = 1; i < num; i++)
		if (a[i] < a[i - 1])
			return false;
	return true;
}

/*该方法基于原地归并的抽象实现了另一种递归归并，这也是分治思想的典型例子
  如果能将两个子数组排序，它就能通过归并两个子数组来将整个数组排序*/
  //自顶向下归并排序
template<typename type>
void merge_ub_sort(type *a, const int num) {
	type *aux = new type[num];					//归并需要辅助数组,将a复制到aux中
	memcpy(aux, a, sizeof(type)*num);
	/*for (int i = 0; i < num; i++)
		cout << aux[i] << " ";*/
	Sort(a, aux, 0, num - 1);
	delete[]aux;
	aux = NULL;
}

//自底向上归并排序
template<typename type>
void merge_bu_sort(type *a, const int num) {
	type *aux = new type[num];
	memcpy(aux, a, sizeof(type)*num);
	Sort_BU(a,aux,num);
	delete[]aux;
	aux = NULL;
}
/*自底向上归并排序，对十万个以上的数随机数排序，这个好像比自顶向下快一点*/
template<typename type>
void Sort_BU(type *a,type *aux,int num) {
	for (int sz = 1; sz < num; sz += sz) {		//sz子数组大小，num数组长度,aux为归并辅助数组,原数组a的副本
		for (int l = 0; l < num; l += 2 * sz)	//l:子数组索引
			Merge(a, aux, l, l + sz - 1, (l + 2 * sz - 1) < (num - 1) ? (l + 2 * sz - 1) : (num - 1));
	}
}
/*自顶向下归并排序*/
template<typename type>
void Sort(type *a,type *aux, int low, int high) {
	if (high <= low)return;
	int mid = low + (high - low) / 2;
	Sort(a, aux, low, mid);			//将左半边排序
	Sort(a, aux, mid + 1, high);	//将右半边排序
	Merge(a, aux, low, mid, high);	//归并数组
}

/*原地归并的抽象方法,将a[low...mid]和a[mid+1...high]归并
  其中a位原始数组，aux为归并辅助数组，将a中的值全部复制到aux中*/
template<typename type>
void Merge(type *a, type *aux, int low, int mid, int high) {
	int num = high - low + 1;
	int i = low;
	int j = mid + 1;
	memmove(aux + low, a + low, sizeof(type)*num);
	for (int k = low; k <= high; k++) {
		if (i > mid)				a[k] = aux[j++];
		else if (j > high)			a[k] = aux[i++];
		else if (aux[i] > aux[j])	a[k] = aux[j++];
		else						a[k] = aux[i++];
	}
	/*cout << endl;
	for (int i = 0; i <= high; i++)
		cout << a[i] << " ";*/
}
//交换数组a中p和q的位置
template<typename type>
void exechange(type *a, int p, int q) {
	type temp = a[p];
	a[p] = a[q];
	a[q] = temp;
}

/*快速排序，quick-sort*/
template<typename type>
void quick_sort(type *a, const int num) {
	random_engin gen((unsigned)time(0));//保持随机性的另一种方法就是在Partition()中随机选择一个切分元素
	//std::shuffle(a, a + num, gen);
	qSort(a, gen, 0, num - 1);			
}
/*分割数组*/
template<typename type>
int Partition(type *a, random_engin &gen, const int low, const int high) {
	int i = low, j = high + 1;//i，j分别为左右扫描指针
	if (high - low > 1) {
		uniform_int_distribution<int> dis(low, high);//产生low到high之间的随机数
		int r = dis(gen);
		if (r != low) 
			exechange(a, low, r);
	}
	while (true)
	{
		while (a[low] > a[++i]) if(i > j) break;
		while (a[low] < a[--j]) if(j < i) break;
		if (i >= j)break;
		exechange(a, i, j);
	}
	exechange(a, low, j);
	return j;    //最终达成a[low...j-1] <= a[j] <= a[j + 1...high]
}

template<typename type>
void qSort(type *a, random_engin &gen, int low, int high) {
	if (low >= high)return;
	int mid = Partition(a, gen, low, high);
	qSort(a, gen, low, mid - 1);
	qSort(a, gen,  mid + 1, high);
}

/*************************基于堆的优先队列**************************/
template<typename type>
class MaxPQ {
public:
	MaxPQ(type *a, int num) {
		pq = new type[num + 2];
		for (int i = 0; i < num; i++)
			pq[i + 1] = a[i];
		N = num;
		maxNum = num;
		sink();//将任意序列构造堆有序
	}

	MaxPQ(int max) {
		pq = new type[max + 2];
		N = 0;
		maxNum = max;
	}
	~MaxPQ() {
		delete[]pq;
		pq = NULL;
	}
	void insert(type v);
	type max() { return pq[1]; }
	type delMax();
	bool isEmpty() { return N == 0; }
	int size() { return N; }
	type& operator[](size_t n) {
		return pq[n];
	}
	void sort();//堆排序
	bool is_Sorted();
private:
	int N;
	type *pq;
	int maxNum;
	void swim(int k);
	void sink(int k);
	void sink();//将任意序列构造堆有序
	void exech(int i, int j){
		type t = pq[i];
		pq[i] = pq[j];
		pq[j] = t;
	}
};


#endif

template<typename type>
inline void MaxPQ<type>::insert(type v)
{
	pq[++N] = v;
	swim(N);
}

template<typename type>
inline type MaxPQ<type>::delMax()
{
	type t = pq[1];
	exech(1, N + 1);
	N--;
	sink(1);
	return t;
}
/*由下至上堆有序化（上浮）*/
template<typename type>
inline void MaxPQ<type>::swim(int k)
{
	while (k > 1 && pq[k] > pq[k / 2]) {
		exech(k, k / 2);
		k = k / 2;
	}
}
/*由上至下堆有序化(下沉)*/
template<typename type>
inline void MaxPQ<type>::sink(int k)
{
	while (2 * k <= N) {
		int j = 2 * k;
		if (pq[j] < pq[j + 1])j++;
		if (pq[j] < pq[k])break;
		exech(j, k);
		k = j;
	}
}

template<typename type>
inline void MaxPQ<type>::sink()
{
	int n = N / 2;
	while (n > 0) {
		if (pq[n] <= pq[N]) exech(n, N);	
		sink(n--);
	}
}
/*堆排序的主要工作，在这个阶段完成。先将堆有序中的最大元素删除，然后放入对缩小后数组空出的位置，与选择排序有点类似，但比它快得多*/
template<typename type>
inline void MaxPQ<type>::sort() {
	while ( N > 1)
		delMax();
}

template<typename type>
inline bool MaxPQ<type>::is_Sorted()
{
	for (int i = 3; i <= N + 1; i++)
		if (pq[i - 1] > pq[i])
			return false;
	return true;
}
