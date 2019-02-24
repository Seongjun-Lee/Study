#include<iostream>
#include<time.h>

using namespace std;

enum AI_MODE
{
	AM_EASY=1,AM_HARD
};

enum LINE_NUMBER
{
	LN_H1, LN_H2, LN_H3, LN_H4, LN_H5, LN_V1, LN_V2, LN_V3, LN_V4, LN_V5, LN_LT, LN_RT
};
void main()
{
	srand((unsigned int)time(0));

	int number[25] = {};
	int AInumber[25] = {};

	for (int i = 0; i < 25; ++i)
	{
		number[i] = i + 1;
		AInumber[i] = i + 1;
	}

	int Temp, dx1, dx2;

	for (int i = 0; i < 100; ++i)
	{
		dx1 = rand() % 25;
		dx2 = rand() % 25;

		Temp = number[dx1];
		number[dx1] = number[dx2];
		number[dx2] = Temp;

		dx1 = rand() % 25;
		dx2 = rand() % 25;

		Temp = AInumber[dx1];
		AInumber[dx1] = AInumber[dx2];
		AInumber[dx2] = Temp;
	}

	int bingo = 0, AIbingo = 0;
	int AImode;

	while (true)
	{
		system("cls");
		cout << "1.EASY" << endl;
		cout << "2.HARD" << endl;
		cout << "AI 모드를 선택하시오 : ";
		cin >> AImode;

		if (AImode >= AM_EASY && AImode <= AM_HARD)
			break;
	}

	int nonSelect[25] = {};
	int nonCount = 0;

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

		cout << endl << endl << "Bingo Line : " << bingo << endl;

		cout << "=============== AI ===============" << endl;

		switch (AImode)
		{
		case AM_EASY:
			cout << "AI : EASY" << endl;
			break;
		case AM_HARD:
			cout << "AI : HARD" << endl;
			break;
		}
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (AInumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << AInumber[i * 5 + j] << "\t";
			}

			cout << endl;
		}

		cout << "AIBingo Line : " << AIbingo << endl;

		if (bingo >= 5)
		{
			cout << "플레이어 승리" << endl;
			break;
		}
		else if (AIbingo >= 5)
		{
			cout << "AI 승리" << endl;
			break;
		}
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

		for (int i = 0; i < 25; ++i)
		{
			if (AInumber[i] == input)
			{
				AInumber[i] = INT_MAX;
				--nonCount;
				break;
			}
		}

		switch (AImode)
		{
		case AM_EASY:
			nonCount = 0;
			for (int i = 0; i < 25; ++i)
			{
				if (AInumber[i] != INT_MAX)
				{
					nonSelect[nonCount] = AInumber[i];
					++nonCount;
				}
			}

			input = nonSelect[rand() % nonCount];
			break;
		case AM_HARD:
			int line = 0;
			int checkcount = 0;;
			int savecount = 0;

			for (int i = 0; i < 5; ++i)
			{
				for (int j = 0; j < 5; ++j)
				{
					if (AInumber[i * 5 + j] == INT_MAX)
						++checkcount;
				}

				if (checkcount < 5 && savecount << checkcount)
				{
					line = i;
					savecount = checkcount;
				}
			}

			for (int i = 0; i < 5; ++i)
			{
				checkcount = 0;
				for (int j = 0; j < 5; ++j)
				{
					if (AInumber[j * 5 + i] == INT_MAX)
						++checkcount;
				}

				if (checkcount < 5 && savecount < checkcount)
				{
					line = i + 5;
					savecount = checkcount;
				}
			}

			checkcount = 0;

			for (int i = 0; i < 25; i += 6)
			{
				if (AInumber[i] == INT_MAX)
					++checkcount;
			}

			if (checkcount < 5 && savecount < checkcount)
			{
				line = LN_LT;
				savecount = checkcount;
			}

			checkcount = 0;

			for (int i = 4; i < 20; i += 4)
			{
				if (AInumber[i] == INT_MAX)
					++checkcount;
			}

			if (checkcount < 5 && savecount < checkcount)
			{
				line = LN_RT;
				savecount = checkcount;
			}

			if (line <= LN_H5)
			{
				for (int i = 0; i < 5; ++i)
				{
					if (AInumber[line * 5 + i] != INT_MAX)
					{
						input = AInumber[line * 5 + i];
						break;
					}
				}
			}
			else if (line <= LN_V5)
			{
				for (int i = 0; i < 5; ++i)
				{
					if (AInumber[i * 5 + (line - 5)] != INT_MAX)
					{
						input = AInumber[i * 5 + (line - 5)];
						break;
					}
				}
			}
			else if (line == LN_LT)
			{
				for (int i = 0; i < 25; i += 6)
				{
					if (AInumber[i] != INT_MAX)
					{
						input = AInumber[i];
						break;
					}
				}
			}
			else if (line == LN_RT)
			{
				for (int i = 4; i <= 20; i += 4)
				{
					if (AInumber[i] != INT_MAX)
					{
						input = AInumber[i];
						break;
					}
				}
			}
			break;
		}

		for (int i = 0; i < 25; ++i)
		{
			if (number[i] == input)
			{
				number[i] = INT_MAX;
				break;
			}
		}

		for (int i = 0; i < 25; ++i)
		{
			if (AInumber[i] == input)
			{
				AInumber[i] = INT_MAX;
				break;
			}
		}

		bingo = 0;
		AIbingo = 0;

		int check1 = 0, check2 = 0;
		int AIcheck1 = 0, AIcheck2 = 0;

		for (int i = 0; i < 5; ++i)
		{
			check1 = check2 = 0;
			AIcheck1 = AIcheck2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (number[i * 5 + j] == INT_MAX)
					++check1;

				if (number[j * 5 + i] == INT_MAX)
					++check2;

				if (AInumber[i * 5 + j] == INT_MAX)
					++AIcheck1;

				if (AInumber[j * 5 + i] == INT_MAX)
					++AIcheck2;
			}

			if (check1 == 5)
				++bingo;

			if (check2 == 5)
				++bingo;

			if (AIcheck1 == 5)
				++AIbingo;

			if (AIcheck2 == 5)
				++AIbingo;
		}

		check1 = 0;
		AIcheck1 = 0;

		for (int i = 0; i < 25; i += 6)
		{
			if (number[i] == INT_MAX)
				++check1;
			if (AInumber[i] == INT_MAX)
				++AIcheck1;
		}

		if (check1 == 5)
			++bingo;
		if (AIcheck1 == 5)
			++AIbingo;

		check1 = 0;
		AIcheck1 = 0;

		for (int i = 4; i <= 20; i += 4)
		{
			if (number[i] == INT_MAX)
				++check1;
			if (AInumber[i] == INT_MAX)
				++AIcheck1;
		}

		if (check1 == 5)
			++bingo;
		if (AIcheck1 == 5)
			++AIbingo;
	}
	getchar();
	getchar();
}