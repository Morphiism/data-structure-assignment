//// 方法 1
//#include<iostream>
//
//using namespace std;
//
//int main()
//{
//	int n, k;
//	cin >> n >> k;
//	
//	int* arr = new int[n];
//	int* arr2 = new int[n];
//	for (int i = 0; i < n; i++)
//		cin >> arr[i];
//
//	k = k % n;
//
//	for (int i = 0; i < n; i++)
//	{
//		if (i < k)
//			arr2[i] = arr[n + i - k];
//		else
//			arr2[i] = arr[i - k];
//	}
//
//	for (int i = 0; i < n; i++)
//		cout << arr2[i] << " ";
//
//	return 0;
//}

//// 方法 2
//#include<iostream>
//
//using namespace std;
//
//int main()
//{
//	int n, k;
//	cin >> n >> k;
//	
//	int* arr = new int[n];
//	
//	for (int i = 0; i < n; i++)
//		cin >> arr[i];
//	
//	k = k % n;
//	int* temp = new int[k];
//
//	for (int i = 0; i < k; i++)
//		temp[i] = arr[n - k + i];
//
//	for (int i = n - 1; i >= k; i--)
//		arr[i] = arr[i - k];
//
//	for (int i = 0; i < k; i++)
//		arr[i] = temp[i];
//
//	for (int i = 0; i < n; i++)
//		cout << arr[i] << " ";
//	
//	return 0;
//}

// 方法 3
#include<iostream>

using namespace std;

void revert(int* arr, int start, int end)
{
	while (start < end)
	{
		int temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
}

int main()
{
	int n, k;
	cin >> n >> k;

	int* arr = new int[n];

	for (int i = 0; i < n; i++)
		cin >> arr[i];

	k = k % n;

	revert(arr, 0, n - 1);
	revert(arr, 0, k - 1);
	revert(arr, k, n - 1);

	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";

	return 0;
}