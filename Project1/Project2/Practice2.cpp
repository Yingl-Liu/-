#include "Practice2.h"

FixedCapacityStackOfStrings::FixedCapacityStackOfStrings(int cap)
{
	a = new std::string[cap];
	n = 0;
}

FixedCapacityStackOfStrings::~FixedCapacityStackOfStrings()
{
	delete[] a;
	a = NULL;
}

std::string FixedCapacityStackOfStrings::pop()
{
	return a[--n];
}

void FixedCapacityStackOfStrings::push(std::string item)
{
	a[n++] = item;
}

bool FixedCapacityStackOfStrings::isEmpty()
{
	return n == 0;
}

int FixedCapacityStackOfStrings::size()
{
	return n;
}

void selection_sort(double * a, const int num)
{
	int min;//��iλ����С�����±�
	for (int i = 0; i < num; i++) {
		min = i;
		for (int j = i + 1; j < num; j++) {
			min = a[min] < a[j] ? min : j;
		}
		exechange(a, i, min);
	}
}

void insert_sort(double * a, const int num)
{
	for (int i = 1; i < num; i++) {//��a[i]���뵽a[i-1],a[i-2],a[i-3]...֮��
		for (int j = i; j > 0; j--)
			if (a[j] < a[j - 1])//���a[j]<a[j-1]����ô������������λ�ã����0��i֮���Ԫ�ض�������ġ���a[j]>a[j-1]����֮��ľͲ���Ҫ�ٱȽ�
				exechange(a, j, j - 1);//��������һ���ܴ������е�Ԫ���Ѿ�����(��ӽ�����)������������򽫻����������������������������öࡣ
			else
				break;
	}
}

void shell_sort(double * a, const int num)
{
	int h = 1;
	while (h < num / 3)h = 3 * h + 1;
	while (h >= 1) {//�������Ϊh���򣬼�0,h,2h...��1,1+h,1+2h...����������
		for (int i = h; i < num; i++) {
			for (int j = i; j >= h&&a[j] < a[j - h]; j -= h)
				exechange(a, j, j - h);
		}
		h = h / 3;
	}
}

void quick_sort(double * a, const int num)
{
}


