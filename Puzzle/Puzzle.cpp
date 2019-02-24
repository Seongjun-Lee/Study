#include<iostream>
#include<time.h>
#include<conio.h>

using namespace std;

void main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = {};

	for (int i = 0; i < 24; ++i)
	{
		iNumber[i] = i + 1;
	}

	iNumber[24] = INT_MAX;

	int index = 24;

	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}

	while (true)
	{
		system("cls");
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNumber[i * 5 + j] << "\t";
			}

			cout << endl;
		}
		
		bool win = true;

		for (int i = 0; i < 24; ++i)
		{
			if (iNumber[i] != i + 1)
			{
				win = false;
				break;
			}
		}

		if (win == true)
		{
			cout << "���ڸ� ��� ������ϴ�" << endl;
			break;
		}

		cout << "w : �� s : �Ʒ� a : ���� d : ������ q : ���� : ";

		char cinput = _getch();

		if (cinput == 'q' || cinput == 'Q')
			break;

		switch (cinput)
		{
		case 'w':
		case 'W':
			if (index > 4)
			{
				iNumber[index] = iNumber[index - 5];
				iNumber[index - 5] = INT_MAX;
				index -= 5;
			}
			break;
		case 's':
		case 'S':
			if (index < 20)
			{
				iNumber[index] = iNumber[index + 5];
				iNumber[index + 5] = INT_MAX;
				index += 5;
			}
			break;
		case 'a':
		case 'A':
			if (index % 5 != 0)
			{
				iNumber[index] = iNumber[index - 1];
				iNumber[index - 1] = INT_MAX;
				--index;
			}
			break;
		case 'd':
		case 'D':
			if (index % 5 != 4)
			{
				iNumber[index] = iNumber[index + 1];
				iNumber[index + 1] = INT_MAX;
				++index;
			}
			break;

		}
	}

	cout << endl << "������ �����մϴ�." << endl;

	getchar();
	getchar();
}