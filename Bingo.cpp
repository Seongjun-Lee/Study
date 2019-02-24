/*#include <iostream>
#include <time.h>

using namespace std;

void main()
{
	srand((unsigned int)time(0));

	int number[25] = {};

	for (int i = 0; i < 25; ++i)
	{
		number[i] = i + 1;
	}

	int Temp, dx1, dx2;

	for (int i = 0; i < 100; ++i)
	{
		dx1 = rand() % 25;
		dx2 = rand() % 25;

		Temp = number[dx1];
		number[dx1] = number[dx2];
		number[dx2] = Temp;
	}

	int bingo = 0;

	while (true)
	{
		system("cls");

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (number[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << number[i * 5 + j] << "\t";
			}

			cout << endl;
		}

		cout << endl << "Bingo Line : " << bingo << endl;

		if (bingo >= 5)
			break;
		cout << "숫자를 입력하시오(0 : 종료) : ";

		int input;
		cin >> input;

		if (input == 0)
			break;
		else if (input < 1 || input > 25)
			continue;

		bool acc = true;

		for (int i = 0; i < 25; ++i)
		{
			if (input == number[i])
			{
				acc = false;
				number[i] = INT_MAX;
				break;
			}
		}

		if (acc)
			continue;

		bingo = 0;

		int check1 = 0, check2 = 0;
	
		for (int i = 0; i < 5; ++i)
		{
			check1 = check2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (number[i * 5 + j] == INT_MAX)
					++check1;

				if (number[j * 5 + i] == INT_MAX)
					++check2;
			}

			if (check1 == 5)
				++bingo;

			if (check2 == 5)
				++bingo;
		}

		check1 = 0;

		for (int i = 0; i < 25; i += 6)
		{
			if (number[i] == INT_MAX)
				++check1;
		}

		if (check1 == 5)
			++bingo;

		check1 = 0;

		for (int i = 4; i <= 20; i += 4)
		{
			if (number[i] == INT_MAX)
				++check1;
		}

		if (check1 == 5)
			++bingo;
	}

	getchar();
	getchar();
}*/