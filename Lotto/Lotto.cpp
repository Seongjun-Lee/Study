#include <iostream>
#include <time.h>

using namespace std;

void main()
{
	for (int i = 2; i <= 9; ++i)
	{
		for (int j = 2; j <= 0; ++j)
		{
			cout << i << " * " << j << " = " << i * j << endl;
		}
	}

	int iArray2[10][10] = { {1,2,3},{4,5,6} };

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			cout << iArray2[i][j] << "\t";
		}

		cout << endl;
	}
	
	srand((unsigned int)time(0));

	system("cls");

	int iLotto[45] = {};

	for (int i = 0; i < 45; ++i)
	{
		iLotto[i] = i + 1;
	}

	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		iTemp = iLotto[idx1];
		iLotto[idx1] = iLotto[idx2];
		iLotto[idx2] = iTemp;
	}

	for (int i = 0; i < 6; ++i)
	{
		cout << iLotto[i] << "\t";
	}

	cout << "보너스 번호 : " << iLotto[6] << endl;

	getchar();
	getchar();

}