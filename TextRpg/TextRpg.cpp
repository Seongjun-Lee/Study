#include<iostream>
#include<time.h>

using namespace std;

enum MAIN_MENU
{
	NONE, MAP, STORE, INVENTORY, EXIT
};

enum MAP_TYPE
{
	MT_NONE, MT_EASY, MT_NORMAL, MT_HARD, MT_BACK
};

enum JOB
{
	JOB_NONE, JOB_KNIGHT, JOB_ARCHER, JOB_WIZARD, JOB_END
};

enum BATTLE
{
	BATTLE_NONE, BATTLE_ATTACK, BATTLE_BACK
};

#define NAME_SIZE 32

typedef struct INVENTORY
{
	int Gold;
}INV;

struct Player
{
	char name[NAME_SIZE];
	char job[NAME_SIZE];
	JOB ejob;
	int Att_Min;
	int Att_Max;
	int Arm_Min;
	int Arm_Max;
	int Hp_Max;
	int Hp;
	int Mp_Max;
	int Mp;
	int Lev;
	int Exp;
	INV Inventory;
};

struct Monster
{
	char name[NAME_SIZE];
	int Att_Min;
	int Att_Max;
	int Arm_Min;
	int Arm_Max;
	int Hp_Max;
	int Hp;
	int Mp_Max;
	int Mp;
	int Lev;
	int Exp;
	int Gold_Min;
	int Gold_Max;
};

void display_user(Player user)
{
	cout << endl << "---스테이터스---" << endl;
	cout << "이름 : " << user.name << endl;
	cout << "직업 : " << user.job << endl;
	cout << "레벨 : " << user.Lev << endl;
	cout << "공격력 : " << user.Att_Max << " ~ " << user.Att_Min << endl;
	cout << "방어력 : " << user.Arm_Max << " ~ " << user.Arm_Min << endl;
	cout << "체력 : " << user.Hp_Max << " / " << user.Hp << endl;
	cout << "마력 : " << user.Mp_Max << " / " << user.Mp << endl;
	cout << "현재 경험치 : " << user.Exp << endl;
	cout << "소지금 : " << user.Inventory.Gold << endl;
}

void display_monster(Monster mob)
{
	cout << "---적 정보---" << endl;
	cout << "이름 : " << mob.name << endl;
	cout << "레벨 : " << mob.Lev << endl;
	cout << "공격력 : " << mob.Att_Max << " ~ " << mob.Att_Min << endl;
	cout << "방어력 : " << mob.Arm_Max << " ~ " << mob.Arm_Min << endl;
	cout << "체력 : " << mob.Hp_Max << " / " << mob.Hp << endl;
	cout << "마력 : " << mob.Mp_Max << " / " << mob.Mp << endl;
	cout << "경험치 : " << mob.Exp << endl;
	cout << "소지금 : " << mob.Gold_Max << " ~ " << mob.Gold_Min << endl;
}

void main()
{
	srand((unsigned int)time(0));

	Player user = {};

	cout << "이름 : ";
	cin.getline(user.name, NAME_SIZE - 1);

	int job = JOB_NONE;
	
	while (job == JOB_NONE)
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 미밥시" << endl;
		cout << "직업을 선택하시오 : ";
		cin >> job;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (job <= JOB_NONE || job >= JOB_END)
			job = JOB_NONE;
	}

	user.Lev = 1;
	user.Exp = 0;
	user.Inventory.Gold = 1000;
	user.ejob = (JOB)job;

	switch (user.ejob)
	{
	case JOB_KNIGHT:
		strcpy_s(user.job, "기사");
		user.Att_Min = 5;
		user.Att_Max = 10;
		user.Arm_Min = 15;
		user.Arm_Max = 20;
		user.Hp_Max = 500;
		user.Hp = 500;
		user.Mp_Max = 100;
		user.Mp = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(user.job, "궁수");
		user.Att_Min = 10;
		user.Att_Max = 15;
		user.Arm_Min = 5;
		user.Arm_Max = 10;
		user.Hp_Max = 350;
		user.Hp = 350;
		user.Mp_Max = 150;
		user.Mp = 150;
		break;
	case JOB_WIZARD:
		strcpy_s(user.job, "마법사");
		user.Att_Min = 15;
		user.Att_Max = 20;
		user.Arm_Min = 5;
		user.Arm_Max = 10;
		user.Hp_Max = 250;
		user.Hp = 250;
		user.Mp_Max = 250;
		user.Mp = 250;
		break;
	}

	Monster monster[MT_BACK - 1] = {};

	strcpy_s(monster[0].name, "고블린");
	monster[0].Att_Max = 30;
	monster[0].Att_Min = 20;
	monster[0].Arm_Max = 5;
	monster[0].Arm_Min = 2;
	monster[0].Hp_Max = 100;
	monster[0].Hp = 100;
	monster[0].Mp_Max = 10;
	monster[0].Mp = 10;
	monster[0].Lev = 1;
	monster[0].Exp = 1000;
	monster[0].Gold_Max = 500;
	monster[0].Gold_Min = 100;

	strcpy_s(monster[1].name, "트롤");
	monster[1].Att_Max = 130;
	monster[1].Att_Min = 80;
	monster[1].Arm_Max = 90;
	monster[1].Arm_Min = 60;
	monster[1].Hp_Max = 2000;
	monster[1].Hp = 2000;
	monster[1].Mp_Max = 100;
	monster[1].Mp = 100;
	monster[1].Lev = 5;
	monster[1].Exp = 7000;
	monster[1].Gold_Max = 5000;
	monster[1].Gold_Min = 3000;

	strcpy_s(monster[2].name, "드래곤");
	monster[2].Att_Max = 300;
	monster[2].Att_Min = 250;
	monster[2].Arm_Max = 400;
	monster[2].Arm_Min = 200;
	monster[2].Hp_Max = 30000;
	monster[2].Hp = 30000;
	monster[2].Mp_Max = 20000;
	monster[2].Mp = 20000;
	monster[2].Lev = 10;
	monster[2].Exp = 30000;
	monster[2].Gold_Max = 50000;
	monster[2].Gold_Min = 25000;

	while (true)
	{
		system("cls");
		cout << "1. 맵" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하시오 : ";
		int menu;
		cin >> menu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (menu == EXIT)
			break;

		switch (menu)
		{
		case MAP:
			while (true)
			{
				system("cls");
				cout << "---맵선택---" << endl;
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로가기" << endl;
				cout << "맵을 선택하시오 : ";
				cin >> menu;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (menu == MT_BACK)
					break;

				Monster monsterM = monster[menu - 1];

				display_user(user);
				display_monster(monsterM);

				while (true)
				{
					switch (menu)
					{
					case MT_EASY:
						cout << "--쉬움--" << endl;
						break;
					case MT_NORMAL:
						cout << "--보통--" << endl;
						break;
					case MT_HARD:
						cout << "--어려움--" << endl;
					}

					cout << "1. 공격" << endl;
					cout << "2. 후퇴" << endl;
					cout << "행동을 선택하시오 : " << endl;
					cin >> menu;

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}
					else if (menu == BATTLE_BACK)
						break;

					switch (menu)
					{
					case BATTLE_ATTACK:
					{
						int att = rand() % (user.Att_Max - user.Att_Min + 1) + user.Att_Min;
						int arm = rand() % (monsterM.Arm_Max - monsterM.Arm_Min + 1) + monsterM.Arm_Min;
						int damage = 1;

						if (att > arm)
							damage = att - arm;

						monsterM.Hp -= damage;

						cout << "적 남은 체력 : " << monsterM.Hp << endl;

						if (monsterM.Hp <= 0)
						{
							cout << "전투 승리" << endl;
							user.Exp += monsterM.Exp;
							int get_money = rand() % (monsterM.Gold_Max - monsterM.Gold_Min) + monsterM.Gold_Min;

							user.Inventory.Gold += get_money;

							cout << monsterM.Exp << " 경험치 획득" << endl << "현재 경험치량 : " << user.Exp << endl;
							cout << get_money << "원 획득 " << endl << "현재 소지금 : " << user.Inventory.Gold << endl;
							system("pause");
							break;
						}

						att = rand() % (monsterM.Att_Max - monsterM.Att_Min + 1) + monsterM.Att_Min;
						arm = rand() % (user.Arm_Max - user.Arm_Min + 1) + user.Arm_Min;
						damage = 1;

						if (att > arm)
							damage = att - arm;

						user.Hp -= damage;

						cout << "플레이어 남은 체력 : " << user.Hp << endl;

						if (user.Hp <= 0)
						{
							cout << "플레이어가 사망하였습니다." << endl;
							cout << "경험치를 " << user.Exp * 0.1f << "잃어버렸습니다." << endl;
							cout << "소지금을 " << user.Inventory.Gold *0.1f << "잃어버렸습니다." << endl;
							user.Exp -= user.Exp * 0.1f;
							user.Inventory.Gold -= user.Inventory.Gold * 0.1f;

							user.Hp = user.Hp_Max;
							user.Mp = user.Mp_Max;
						}
					}
						break;
					}
				}
			}
			break;
		case STORE:
			break;
		case INVENTORY:
			break;
		default:
			cout << "잘못된 선택입니다." << endl;
			break;
		}
	}
}