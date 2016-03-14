#include <iostream>
#include <vector>

using namespace std;

int sum(initializer_list<int> lis)
{
	int sumix = 0;

	for(int i:lis)
		sumix += i;

	return sumix;

}

int main(void)
{
	cout << sum({1,2,3,4,5,6,7,8,9});
	return 0;
}
