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
	int min;//第i位后最小数的下标
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
	for (int i = 1; i < num; i++) {//将a[i]插入到a[i-1],a[i-2],a[i-3]...之中
		for (int j = i; j > 0; j--)
			if (a[j] < a[j - 1])//如果a[j]<a[j-1]，那么这两个数交换位置，如此0到i之间的元素都是有序的。若a[j]>a[j-1]，则之后的就不需要再比较
				exechange(a, j, j - 1);//这样对于一个很大且其中的元素已经有序(或接近有序)的数组进行排序将会比随机数组或是逆序数组进行排序快得多。
			else
				break;
	}
}

void shell_sort(double * a, const int num)
{
	int h = 1;
	while (h < num / 3)h = 3 * h + 1;
	while (h >= 1) {//将数组变为h有序，即0,h,2h...和1,1+h,1+2h...等序列有序
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


