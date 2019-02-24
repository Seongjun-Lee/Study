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
	cout << endl << "---�������ͽ�---" << endl;
	cout << "�̸� : " << user.name << endl;
	cout << "���� : " << user.job << endl;
	cout << "���� : " << user.Lev << endl;
	cout << "���ݷ� : " << user.Att_Max << " ~ " << user.Att_Min << endl;
	cout << "���� : " << user.Arm_Max << " ~ " << user.Arm_Min << endl;
	cout << "ü�� : " << user.Hp_Max << " / " << user.Hp << endl;
	cout << "���� : " << user.Mp_Max << " / " << user.Mp << endl;
	cout << "���� ����ġ : " << user.Exp << endl;
	cout << "������ : " << user.Inventory.Gold << endl;
}

void display_monster(Monster mob)
{
	cout << "---�� ����---" << endl;
	cout << "�̸� : " << mob.name << endl;
	cout << "���� : " << mob.Lev << endl;
	cout << "���ݷ� : " << mob.Att_Max << " ~ " << mob.Att_Min << endl;
	cout << "���� : " << mob.Arm_Max << " ~ " << mob.Arm_Min << endl;
	cout << "ü�� : " << mob.Hp_Max << " / " << mob.Hp << endl;
	cout << "���� : " << mob.Mp_Max << " / " << mob.Mp << endl;
	cout << "����ġ : " << mob.Exp << endl;
	cout << "������ : " << mob.Gold_Max << " ~ " << mob.Gold_Min << endl;
}

void main()
{
	srand((unsigned int)time(0));

	Player user = {};

	cout << "�̸� : ";
	cin.getline(user.name, NAME_SIZE - 1);

	int job = JOB_NONE;
	
	while (job == JOB_NONE)
	{
		system("cls");
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. �̹��" << endl;
		cout << "������ �����Ͻÿ� : ";
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
		strcpy_s(user.job, "���");
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
		strcpy_s(user.job, "�ü�");
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
		strcpy_s(user.job, "������");
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

	strcpy_s(monster[0].name, "���");
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

	strcpy_s(monster[1].name, "Ʈ��");
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

	strcpy_s(monster[2].name, "�巡��");
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
		cout << "1. ��" << endl;
		cout << "2. ����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ����" << endl;
		cout << "�޴��� �����Ͻÿ� : ";
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
				cout << "---�ʼ���---" << endl;
				cout << "1. ����" << endl;
				cout << "2. ����" << endl;
				cout << "3. �����" << endl;
				cout << "4. �ڷΰ���" << endl;
				cout << "���� �����Ͻÿ� : ";
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
						cout << "--����--" << endl;
						break;
					case MT_NORMAL:
						cout << "--����--" << endl;
						break;
					case MT_HARD:
						cout << "--�����--" << endl;
					}

					cout << "1. ����" << endl;
					cout << "2. ����" << endl;
					cout << "�ൿ�� �����Ͻÿ� : " << endl;
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

						cout << "�� ���� ü�� : " << monsterM.Hp << endl;

						if (monsterM.Hp <= 0)
						{
							cout << "���� �¸�" << endl;
							user.Exp += monsterM.Exp;
							int get_money = rand() % (monsterM.Gold_Max - monsterM.Gold_Min) + monsterM.Gold_Min;

							user.Inventory.Gold += get_money;

							cout << monsterM.Exp << " ����ġ ȹ��" << endl << "���� ����ġ�� : " << user.Exp << endl;
							cout << get_money << "�� ȹ�� " << endl << "���� ������ : " << user.Inventory.Gold << endl;
							system("pause");
							break;
						}

						att = rand() % (monsterM.Att_Max - monsterM.Att_Min + 1) + monsterM.Att_Min;
						arm = rand() % (user.Arm_Max - user.Arm_Min + 1) + user.Arm_Min;
						damage = 1;

						if (att > arm)
							damage = att - arm;

						user.Hp -= damage;

						cout << "�÷��̾� ���� ü�� : " << user.Hp << endl;

						if (user.Hp <= 0)
						{
							cout << "�÷��̾ ����Ͽ����ϴ�." << endl;
							cout << "����ġ�� " << user.Exp * 0.1f << "�Ҿ���Ƚ��ϴ�." << endl;
							cout << "�������� " << user.Inventory.Gold *0.1f << "�Ҿ���Ƚ��ϴ�." << endl;
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
			cout << "�߸��� �����Դϴ�." << endl;
			break;
		}
	}
}