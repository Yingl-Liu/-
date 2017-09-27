#include "Practice2.h"
#include <time.h>
#include <fstream>
using namespace std;
//#define DEBUG
class Counter
{
	friend ostream& operator<<(ostream& out, Counter& obj)
	{
		out << obj.name + ":" << obj.count;
		return out;
	}
	friend istream& operator >> (istream& in, Counter& obj)
	{
		in >> obj.name;
		/*if (!in)
		{
			obj = Counter();
		}*/
		return in;
	}
public:
	Counter();
	Counter(string id);
	~Counter();
	void increment();
	int tally();
private:
	string name;
	int count;
};

Counter::Counter():name("null"),count(0){}

Counter::Counter(string id):name(id),count(0){}

Counter::~Counter()
{
}

void Counter::increment()
{
	count++;
}

int Counter::tally()
{
	return count;
}

double Evaluate()
{
	stack<double> vals;
	stack<string> ops;
	string c;
	while (cin >> c)
	{
		if (c == "(");
		else if (c == "+" || c == "-" || c == "*" || c == "/" || c == "sqrt")ops.push(c);
		else if (c == ")")
		{
			string op = ops.top(); ops.pop();
			double val = vals.top(); vals.pop();
			if (op == "+") {val = vals.top() + val; vals.pop();}
			else if (op == "-") { val = vals.top() - val; vals.pop(); }
			else if (op == "*"){val = vals.top() * val; vals.pop();}
			else if (op == "/"){val = vals.top() / val; vals.pop();}
			else if (op == "sqrt"){ val = sqrt(val);}
			vals.push(val);
		}
		else
			vals.push(stod(c));
	}
	return vals.top();
}




int main()
{
	/*vector<Counter> counters;
	Counter count1;
	while(cin >> count1)
	{
		counters.push_back(count1);
	}
	for (Counter c : counters)
	{
		cout << "count1的name:" << c << endl;
	}
	double res = Evaluate();
	cout << res << endl;*/
	/*FixedCapacityStack<string> s;
	std::string str;
	while (cin >> str)
	{
		if (str != "-")
			s.push_node(str);
		else if (!s.isEmpty()&&str=="-")
			std::cout << s.pop_node() << std::endl;
	}
	cout << s.del(3) << endl;
	std::cout << s.size() << " left on stack" << std::endl;*/
	/*int N, p, q;
	cout << "输入初始化触点数量：";
	cin >> N;
	UF uf(N);
	while (cin >> p >> q) {
		if (uf.connected(p, q))
			continue;
		uf.qu_union(p, q);
		for (int i = 0; i < N; i++)
			cout << uf.qu_find(i) << " ";
		cout << '\n' <<uf.getCount() << " components" << endl;
	}	*/
#ifdef DEBUG
	int N = 10000000;
	vector<double> v(N);
	default_random_engine generator((unsigned)time(0));//随机数生成器
	uniform_real_distribution<double> dis(0, N);//能够把generator产生的均匀分布值映射到其他常见分布，如均匀分布uniform，正态分布normal，二项分布binomial，泊松分布poisson
	double dur1,dur2;
	clock_t start, end;
	double *a = new double[N];
	for (int i = 0; i < N; i++)
		a[i] = dis(generator);//分布器利用运算符()产生随机数，要传入一个generator对象作为参数

	/*double *b = new double[N];
	memcpy(b, a, sizeof(double)*N);*/

	start = clock();
	merge_bu_sort(a, N);
	//quick_sort(a, N);
	//insert_sort(a, N);
	//shell_sort(a, N);
	end = clock();
	/*for (int i = 0; i < N; i++)
		cout << a[i] << endl;*/
	if (isSorted(a, N))
		cout << N << "个数排序成功！" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	else
		cout << "未能正确排序！" << endl;

	delete[]a; a = NULL;
	//delete[]b; b = NULL;
#endif // DEBUG
	/*ifstream f;
	f.open("hello.txt", ifstream::out);
	if (!f.is_open())return -1;
	vector<string> file;
	string line;
	while (!f.eof()) {
		getline(f, line);
		file.push_back(line);
	}
	for (string c : file)
		cout << c << endl;*/
	//char a[10] = { 'A','X','R','W','O','V','G','Z','J','Y' };
	int N = 4000;
	default_random_engine generator((unsigned)time(0));//随机数生成器
	uniform_real_distribution<double> dis(0, N);//能够把generator产生的均匀分布值映射到其他常见分布，如均匀分布uniform，正态分布normal，二项分布binomial，泊松分布poisson
	double dur1, dur2;
	clock_t start, end;
	double *a = new double[N];
	for (int i = 0; i < N; i++)
		a[i] = dis(generator);
	start = clock();
	
	/*char in;
	while (cin >> in) {
		if ('*' == in)
			cout << pq.delMax() << endl;
		else {
			pq.insert(in);
			for(size_t i = 1;i<= pq.size();i++)
				cout << pq[i] << " ";
		}
	}*/
	//MaxPQ<double> pq(a, N);
	//pq.sort();
	//quick_sort(a, N);
	select(a, 0, N - 1);
	end = clock();
	/*for (size_t i = 2; i <= N + 1; i++)
		cout << pq[i] << endl;*/
	if (isSorted(a, N))
		cout << "排序成功！" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	delete[]a;
	a = NULL;
	return 0;
}