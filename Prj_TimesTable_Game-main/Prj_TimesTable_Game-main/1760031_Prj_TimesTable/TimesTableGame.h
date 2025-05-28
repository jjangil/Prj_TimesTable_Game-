#pragma once

#include <iostream>
#include <string>			//C++�� ǥ�� ���̺귯��: C++�� ǥ�� ���ڿ�(string)�� string; string�� namespace std�� ���ǵ�
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>		
#include "LibConsole.hpp"	//�ܼ� ��� ���� ����
#include "LibGameTool.hpp"	//���� ó�� ���

#define DEF_TIMES_MAX	(9)			//������ ����� ����Ʈ ��� �ܼ�
#define MAX_STREAM_SIZE	(10000)		//��Ʈ�� ������� �� �� ó���ϴ� �ִ� ���� ��
#define DEF_X_COORD (46)			//����Ʈ X��ǥ ��
#define DEF_Y_COORD (13)			//����Ʈ Y��ǥ ��
#define LOADING_SCREEN_DELAY (500)	//����ȭ�� �����ð� msec����
#define DIFF_EASY (5)
#define DIFF_NOMAL (10)
#define DIFF_HARD (15)

/*
	- "enum" OpType
	- C ���		: ������ ��� ����
	- C++ ���	: ������ Ŭ���� ����(���ο� ��� ����� ����); ���ο� ������ ����� �ٸ� �ڵ� ��ϰ� �� ��ġ�� ����

	- OT_MUL == 1, OT_DIV == 2
*/
enum class OpType
{
	OT_NULL = 0, OT_MUL, OT_DIV
};

enum class WASDKeyOrSpace
{
	Up = 0, Down, Left, Right, SpaceBar
};

/*
	- ��Ģ: ���ϸ��� Ŭ�������� ����(�ǹ��� �ƴϰ� �ǰ�)
	- �ڵ� ����� ĸ��ȭ
*/
class TimesTableGame
{
public: //public group(�ܺο��� ���� ����: C ����� ����ü(struct)�� ����)

	//������(constructor): Ŭ������� ���� �̸��� ���� ��� �Լ�
	TimesTableGame(void) 
	{
		using namespace mglib;
		randseed(); //���� �ʱ�ȭ
	}

	/*���͸� ����Ϸ��� �Ͽ����� ���׸� �������� ����
	TimesTableGame(const std::string strName, int nDifficulty = 0, int nPlayTime = 0, double dbCorrectRatio = 0.0)
	{
		mName = strName;
		mDifficulty = nDifficulty;
		mPlayTime = nPlayTime;
		mCorrectRatio = dbCorrectRatio;
	}*/

	//�Ҹ���, �ı���(destructor): Ŭ������ �տ� ~(not �ǹ�)�� ���� ��� �Լ�
	~TimesTableGame() {}


	//setter
	void setXpos(int nXPos);
	void setYpos(int nYpos);
	
	//�޼ҵ� (��Ȱ��ȭ �� �޼ҵ�� "Menu" ���� �޼ҵ�� ����� ���)
	//void start(void);
	//void printLogo(void);
	//void printMenu(void);
	//int inputMenu(void);						//���: ������� �޴� ���� ��ȣ
	int inputInt(const std::string& sInput);	//���� �Է�: sInput�� �Է½� ����� ����
	int inputTimesNum(void);					//���: ���ϴ� �ܼ�
	int inputMaxTimesNum(void);					//���: ����� �ִ� �ܼ�
	int inputGameTimesNum(void);				//���: ���ϴ� �ܼ�
	void InputUserName(void);					//����� �̸��� �Է¹޴� �޼ҵ�
	void Menu(void);							//Ÿ��Ʋ ȭ�� �� �޴� ���� �޼ҵ�
	void printTimesTable(int i, int jMax);		//���ϴ� �ܼ� ��� �޼ҵ�
	void printAllTimesTable(int nTimesMax);		//��� ������ ��� �޼ҵ�
	void startGame(int nTimes);					//������ ���� �޼ҵ�
	void exeEasyGame(int nTimes);
	void exeNomalGame(int nTimes);
	void exeHardGame(int nTimes);
	//void exeMenu(int nMenu);

	//��� ���� ��� �޼ҵ� (���� ���� ���з� ��Ȱ��ȭ)
	/*
	void PrintStats(void);						//��� ��� �޼ҵ�
	void UpdateStats(TimesTableGame UserStats);	//��� ������Ʈ �޼ҵ�
	void SaveStats(std::string& filename);		//��� ���� �޼ҵ�
	void LoadStats(std::string& filename);		//��� �ҷ����� �޼ҵ�
	*/

private: //private group(�ܺο��� ���� �Ұ���)

	//private property(��� ����)
	int nXPosition = 0;			//nXPosition : X��ǥ
	int	nYPosition = 0;			//nYPosition : Y��ǥ
	int nSelectDiff = 0;		//���̵� ����
	int m_nNumCalc = 0;
	int m_nCorrectCalc = 0;
	double m_totalCalcTime = 0.0;

	double correctRatio = 0.0;	//������� 
	double avgCalcTime = 0.0;	//�ɸ��ð�


	std::string strUserName;	//����� �̸�
	std::string strStartLogo;
	std::string strEndLogo;
	std::string strTitle;

	/*
	int mDifficulty = 0;			//����
	int mPlayTime = 0;				//�÷��� �ð�
	double mCorrectRatio = 0.0;		//���� ����
	std::string SavedStats = "SavedStats.txt";		//��� ���� ��Ī
	std::vector<TimesTableGame>Stats;				//��� ����� ���� ����
	std::string mName;								//����� �̸�
	*/

	//private method(��� �Լ�)

	int getIntSafe(void);
	bool playTimesTable(int nTimes); // true: ��� ����; false: ������ ����
	void updateScore(bool bCorrect, int nCorrectAns, double calcTime);

	//�޴� ��� ������ ���� �޼ҵ�
	void SaveStats(std::ofstream& file);		//��� ���� �޼ҵ�
	void LoadStats(std::ifstream& file);		//��� �ҷ����� �޼ҵ�
	void DisplayStats(void);					//��� ��� �޼ҵ�
	void TitlePrint(std::ifstream& file);		//���α׷� ���� ��� �޼ҵ�
	void GotoXY(int nXPos, int nYPos);			//�ܼ� Ŀ�� ��ǥ���� �޼ҵ�
	void InitXY(void);							//X, Y��ǥ �ʱ�ȭ �޼ҵ�
	void MenuPrint(void);						//�޴� ��� �޼ҵ�
	int SetGameLevel(void);						//���̵� ���� �޼ҵ�
	int InputKey(void);							//WASDŰ �Է� �޼ҵ�
	int MoveORSelect(void);						//�޴� �̵� �� ���� �޼ҵ�
	void PrintDot(int nDot);					//�ε�, ����� ���� ����ϴ� �޼ҵ�
	void StartLogoPrint(std::ifstream& file);	//Start �޽��� ��� �޼ҵ�
	void EndLogoPrint(std::ifstream& file);		//End �޽��� ��� �޼ҵ�
};

inline void TimesTableGame::setXpos(int nXPos)
{
	nXPosition = nXPos;
}

inline void TimesTableGame::setYpos(int nYpos)
{
	nYPosition = nYpos;
}

/*inline void TimesTableGame::start(void)
{
	int nMenu = 0;

	while (1)
	{
		//�޴� ���
		printMenu();

		// ����� �Է�
		nMenu = inputMenu();

		//cout << "�Է��� ��ȣ: " << nMenu;
		exeMenu(nMenu);
	}
}*/

/*inline void TimesTableGame::printLogo(void)
{
	using namespace mglib;
	using namespace std;
	settextcol(YELLOW);

	cout << "\t\t\t" << "����������������������������������������������������������������" << endl;
	cout << "\t\t\t" << " _____  _                         _____         _      _       " << endl;
	cout << "\t\t\t" << "|_   _|(_)                       |_   _|       | |    | |      " << endl;
	cout << "\t\t\t" << "  | |   _  _ __ ___    ___  ___    | |    __ _ | |__  | |  ___ " << endl;
	cout << "\t\t\t" << "  | |  | || '_ ` _ \\  / _ \\/ __|   | |   / _` || '_ \\ | | / _ \\" << endl;
	cout << "\t\t\t" << "  | |  | || | | | | ||  __/\\__ \\   | |  | (_| || |_) || ||  __/" << endl;
	cout << "\t\t\t" << "  \\_/  |_||_| |_| |_| \\___||___/   \\_/   \\__,_||_.__/ |_| \\___|" << endl;
	cout << "\t\t\t" << "����������������������������������������������������������������" << endl << endl;
}*/

/*inline void TimesTableGame::printMenu(void)
{
	using namespace mglib;
	using namespace std;
	settextcol(RED);

	cout << "\t\t\t" << "1. ��� ������ ���" << endl;
	cout << "\t\t\t" << "2. ���ϴ� �ܸ� ���" << endl;
	cout << "\t\t\t" << "3. ������ ����" << endl;
	cout << "\t\t\t" << "4. ���α׷� ����" << endl;
}*/

/*inline int TimesTableGame::inputMenu(void)
{
	using namespace mglib;
	using namespace std;
	settextcol(WHITE);

	int nMenu = 0;


	cout << "\t\t\t" << "���ϴ� ��ȣ�� �����ϼ���. ��ȣ��? ";
	cin >> nMenu; // cin: console input(���� Ű����)

	return nMenu;
}*/

inline int TimesTableGame::inputInt(const std::string& sInput)
{
	using namespace mglib;
	using namespace std;

	settextcol(WHITE);

	int nInput = 0;

	cout << sInput;
	cin >> nInput; // cin: console input(���� Ű����)

	return nInput;
}

inline int TimesTableGame::inputTimesNum(void)
{
	return inputInt("����ϱ� ���ϴ� �ܼ��� �Է��ϼ���. �ܼ���? : ");
}

inline int TimesTableGame::inputMaxTimesNum(void)
{
	return inputInt("����� �ִ� �ܼ��� �Է��ϼ���. �ܼ���? : ");
}

inline int TimesTableGame::inputGameTimesNum(void)
{
	return inputInt("�������� ������ �ܼ��� �Է��ϼ���. �ܼ���? : ");
}

inline void TimesTableGame::InputUserName(void)
{
	using namespace std;

	GotoXY(nXPosition - 3, nYPosition);
	cout << "����� �̸��� �Է����ּ��� : ";
	GotoXY(nXPosition + 10, nYPosition + 2);
	cin >> strUserName;
}

inline void TimesTableGame::Menu(void)
{
	using namespace std;
	TimesTableGame userStats;

	ifstream StartLogoFile("StartLogo.txt");	
	ifstream EndLogoFile("EndLogo.txt");
	ifstream OpenFile("SavedStats.txt");
	ofstream SaveFile("SavedStats.txt");

	StartLogoPrint(StartLogoFile); //���� �ΰ� ���
	system("cls");

	InputUserName(); //����� �̸� �Է�
	system("cls");

	while (1)
	{
		ifstream TitleFile("Title.txt");
		
		InitXY();				//X,Y��ǥ �ʱ�ȭ
		TitlePrint(TitleFile);	//Ÿ��Ʋȭ�� ���
		MenuPrint();			//�޴� ��� ���

		switch (MoveORSelect())
		{
		case 0:
			system("cls");
			GotoXY(nXPosition, nYPosition); //InitXY() �޼ҵ带 ���� �ʱ�ȭ�� x:46, y:13��ǥ�� Ŀ�� �̵�
			cout << "��� ������ ���";

			GotoXY(nXPosition - 12, nYPosition + 2); // x:46, y:13 ��ǥ���� ���� -12, +2 ���갪 ��ŭ Ŀ�� �̵�
			printAllTimesTable(inputMaxTimesNum());

			system("PAUSE"); //��� ������ ����� Ű �Է½� ���� ���
			break;

		case 1:
			system("cls");
			InitXY();
			GotoXY(nXPosition, nYPosition);
			cout << "���ϴ� �ܸ� ���";

			GotoXY(nXPosition - 12, nYPosition + 2);
			printTimesTable(inputTimesNum(), DEF_TIMES_MAX);

			system("PAUSE");
			break;

		case 2:
			system("cls");
			InitXY();
			GotoXY(nXPosition + 2, nYPosition);
			cout << "������ ����";

			GotoXY(nXPosition - 12, nYPosition + 2);
			startGame(inputGameTimesNum());
			SaveStats(SaveFile); //���� ����� ��� ����
			break;

		case 3:
			system("cls");
			InitXY();
			GotoXY(nXPosition, nYPosition - 5);
			cout << "���� ���" << endl;
			LoadStats(OpenFile); //����� ��� �ҷ�����
			DisplayStats();		 //�ҷ��� ��� ���
			break;

		case 4:
			system("cls");
			InitXY();
			EndLogoPrint(EndLogoFile); //���� �ΰ� ���
			exit(0);
		}
		system("cls");
	}
}

inline void TimesTableGame::printTimesTable(int i, int jMax)
{
	using namespace mglib;
	using namespace std;

	//int nColor = i % WHITE; // 0~14
	int nColor = i % WHITE + 1; // 1~15

	settextcol(nColor); // ����ϴ� ���ڻ��� RED�� ����

	//printf("[%d�� ���]\n", i);
	cout << '[' << i << "�� ���]" << endl;

	for (int j = 1; j <= jMax; j++)
	{
		//printf("%d x %d = %d\n", i, j, i * j);
		cout << i << " x " << j << " = " << i * j << endl;
	}
	cout << endl;
}

inline void TimesTableGame::printAllTimesTable(int nTimesMax)
{
	using namespace std;

	for (int i = 1; i <= nTimesMax; i++)
	{
		printTimesTable(i, __max(nTimesMax, DEF_TIMES_MAX));
		cout << endl;
	}
}

inline void TimesTableGame::startGame(int nTimes)
{
	using namespace std;

	nSelectDiff = SetGameLevel(); //���̵� ���� �޼ҵ�

	switch (nSelectDiff)
	{
	case 1:
		exeEasyGame(nTimes); //���� ���̵�
		break;

	case 2:
		exeNomalGame(nTimes); //���� ���̵�
		break;	

	case 3:
		exeHardGame(nTimes); //����� ���̵�
		break;

	default:
		break;
	}
}

inline void TimesTableGame::exeEasyGame(int nTimes)
{
	using namespace std;

	for (int i = 0; i < DIFF_EASY; i++)
	{
		bool bResult = playTimesTable(nTimes);
		if (!bResult)
		{
			cout << endl << "\t\t\t" << "������ �����մϴ�." << endl << endl;
			break; // �ݺ��� ���� Ű����
		}
	}
}

inline void TimesTableGame::exeNomalGame(int nTimes)
{
	using namespace std;

	for (int i = 0; i < DIFF_NOMAL; i++)
	{
		bool bResult = playTimesTable(nTimes);
		if (!bResult)
		{
			cout << endl << "\t\t\t" << "������ �����մϴ�." << endl << endl;
			break; // �ݺ��� ���� Ű����
		}
	}
}

inline void TimesTableGame::exeHardGame(int nTimes)
{
	using namespace std;

	for (int i = 0; i < DIFF_HARD; i++)
	{
		bool bResult = playTimesTable(nTimes);
		if (!bResult)
		{
			cout << endl << "\t\t\t" << "������ �����մϴ�." << endl << endl;
			break; // �ݺ��� ���� Ű����
		}
	}
}

inline int TimesTableGame::getIntSafe(void)
{
	using namespace std;
	int nInput;

	cin >> nInput;
	//�Է��� ���� �� ������ �ƴϸ� ���� �߻�; ������ ����� cin�� �������� ����
	//bool bResult = (cin.rdstate() == ios::goodbit); // ������ ���� ó�� ���
	//if (!bResult) cout << endl << "�Է� ���� �߻�" << endl;

	cin.clear(); //������ ���� ���¸� ����
	cin.ignore(MAX_STREAM_SIZE, '\n');	//�� �� ���ڸ� ����; ������ ������ ���� ����
	//������ ����� nInput = 0�� �����
	return nInput;
}

inline bool TimesTableGame::playTimesTable(int iTimes)
{
	using namespace std;
	using namespace mglib;

	int nMaxTimes = 0,		//������ ���� ���� Ƚ��
		jTimes = 0,			//����
		nResult = 0,		//��갪
		nAns = 0,			//�÷��̾� �Է�
		nCorrectAns = 0;	//���� ���

	double calcTime = 0.0;	//��� �ð�(���)
	bool bCorrect;			//bool �ڷ���: true, false�� ����

	nMaxTimes = __max(iTimes, DEF_TIMES_MAX); // 9�� ������ ���� ������ 9���� �������� �߻�
	jTimes = randrange(1, nMaxTimes + 1); // 1, 2, ..., nTimes���� ���� ���� �߻�

	/*
		- int nOp = randrange(1, 2 + 1); // 1(����), 2(������)���� ���� �߻�
		- �� ����(type casting): int(), OpType()
	*/
	OpType nOp = OpType(randrange(int(OpType::OT_MUL), int(OpType::OT_DIV) + 1));

	nResult = iTimes * jTimes; //nResult = �Էµ� ��(iTimes) * ������ ����(jTimes) 
	settextcol(GREEN);


	if (nOp == OpType::OT_MUL) //Multiplication : ������ ��� 
	{
		cout << "\t\t\t" << iTimes << " x " << jTimes << " = ?" << endl;
	}
	else
	{
		cout << "\t\t\t" << iTimes << " x ? = " << nResult << endl;
	}

	settextcol(WHITE);

	cout << "\t\t\t" << "���� ?\t:";

	//�÷��̾ ����ϴ� �κ�

	clock_t nBeginTime = clock(); //msec ������ ���� �ð� ���(�ð� ������ ������� ���α׷��� ����� ��); _t ���� ����: typedef���� ������ �ڷ����� ����
	nAns = getIntSafe(); //int nAns; cin >> nAns;
	clock_t nEndTime = clock();
	calcTime = (nEndTime - nBeginTime) / double(CLOCKS_PER_SEC);


	// ������ �߻��ϸ� ����
	if (nAns == 0)
	{
		return false;
	}

	/*
		- ���ǹ��� ���� ������
		- �����̶�� nResult, �ƴ϶�� jTimes
	*/
	nCorrectAns = (nOp == OpType::OT_MUL) ? nResult : jTimes;
	bCorrect = (nAns == nCorrectAns);

	updateScore(bCorrect, nCorrectAns, calcTime);

	return true;
}

inline void TimesTableGame::updateScore(bool bCorrect, int nCorrectAns, double calcTime)
{
	using namespace std;
	using namespace mglib;

	m_nNumCalc++;

	if (bCorrect) //���� ���
	{
		m_nCorrectCalc++;
		m_totalCalcTime += calcTime;

		settextcol(RED);

		cout << endl << "�����Դϴ�." << endl;
		cout << "��� �ð��� " << calcTime << "���Դϴ�." << endl << endl;
	}
	else //Ʋ�� ���
	{
		settextcol(BLUE);

		cout << endl << "Ʋ�Ƚ��ϴ�." << endl;
		cout << "������ " << nCorrectAns << "�Դϴ�." << endl << endl;
	}

	correctRatio = m_nCorrectCalc / double(m_nNumCalc) * 100.0;
	avgCalcTime = m_totalCalcTime / double(m_nCorrectCalc);

	cout << "���� ����: " << correctRatio << "%" << endl;
	cout << "��� ��� �ð�: " << avgCalcTime << "��" << endl << endl;
}

inline void TimesTableGame::SaveStats(std::ofstream& file)
{
	using namespace std;

	file << strUserName << endl;
	file << nSelectDiff << endl;
	file << correctRatio << endl;
	file << avgCalcTime << endl;
}

inline void TimesTableGame::LoadStats(std::ifstream& file)
{
	using namespace std;

	file >> strUserName;
	file >> nSelectDiff;
	file >> correctRatio;
	file >> avgCalcTime;
}

inline void TimesTableGame::DisplayStats(void)
{
	using namespace std;
	using namespace mglib;

	settextcol(GREEN);

	cout << endl << "\t\t\t\t\t����� �̸�\t:" << strUserName << endl;
	cout << "\t\t\t\t\t�÷��� ���̵�\t:" << nSelectDiff << "Lv." << endl;
	cout << "\t\t\t\t\t���� ����\t:" << correctRatio << '%' << endl;
	cout << "\t\t\t\t\t��� Ǯ�� �ӵ�\t:" << avgCalcTime << " ��" << endl;

	settextcol(RED);
	GotoXY(nXPosition - 13, nYPosition + 7);

	system("PAUSE");
}

inline void TimesTableGame::TitlePrint(std::ifstream& file)
{
	using namespace mglib;
	using namespace std;

	cout << "\n\n\n\n\n";

	/*
		getline �Լ��� �Է� ��Ʈ������ ���ڵ��� �о, ���ڷ� ���� ���ڿ��� ����
		�Է� ��Ʈ������ ���ڸ� �дٰ� delim ���ڸ� �аԵǸ�, �ش� ���ڸ� ������, �о���̱⸦ ���� 
		���࿡ delim ���ڸ� �������� �ʾҴٸ�, ����Ʈ�� ���� ����('\n')�� ������.
	*/
	while (getline(file, strTitle))
	{
		settextcol(YELLOW);
		cout << "\t\t\t" << strTitle << endl;
	}
}

inline void TimesTableGame::GotoXY(int nXPos, int nYPos)
{
	COORD Position; //Short X,Y typedef��, X, Y��ǥ�� Ŀ�� ��ġ�� �ű�� ������ ����

	Position.X = nXPos;
	Position.Y = nYPos;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}

inline void TimesTableGame::InitXY(void)
{
	//�⺻ X, Y��ǥ ������ �ʱ�ȭ
	setXpos(DEF_X_COORD);
	setYpos(DEF_Y_COORD);
}

inline void TimesTableGame::MenuPrint(void)
{
	using namespace mglib;
	using namespace std;

	GotoXY(nXPosition - 2, nYPosition);
	settextcol(YELLOW);
	cout << "��";
	settextcol(RED);
	cout << " ��� ������ ���" << endl;

	GotoXY(nXPosition, nYPosition + 1);
	cout << "���ϴ� �ܸ� ���" << endl;

	GotoXY(nXPosition, nYPosition + 2);
	cout << "������ ����" << endl;

	GotoXY(nXPosition, nYPosition + 3);
	cout << "���" << endl;

	GotoXY(nXPosition, nYPosition + 4);
	cout << "���α׷� ����" << endl;

	GotoXY(nXPosition + 3, nYPosition + 8);
	settextcol(WHITE);
	cout << "�� ���۹� ��";

	GotoXY(nXPosition - 16, nYPosition + 10);
	cout << "[w] ���� �̵� [s] �Ʒ��� �̵� [spacebar] �޴� ����";
}

inline int TimesTableGame::SetGameLevel(void)
{
	int nInput = 0;

	using namespace mglib;
	using namespace std;

	system("cls");

	settextcol(WHITE);
	GotoXY(nXPosition - 10, nYPosition);
	cout << "���̵��� ���� ���õǴ� ���׼��� �����˴ϴ�" << endl;

	settextcol(GREEN);
	GotoXY(nXPosition - 8, nYPosition + 2);
	cout << "[Easy] : 1, [Nomal] : 2, [Hard] : 3" << endl;

	settextcol(WHITE);
	GotoXY(nXPosition - 2, nYPosition + 4);
	cout << "���̵��� �����Ͽ� �ּ��� : ";
	cin >> nInput;

	system("cls");
	GotoXY(5, 4); //���� Ǯ�� ��ǥ�� �̵�

	return nInput;
}

inline int TimesTableGame::InputKey(void) //����Ű ���� ����ڸ� ���� wasdŰ�� ���
{
	char chInput = _getch();

	if (chInput == 'w' || chInput == 'W')
	{
		return (int)WASDKeyOrSpace::Up;
	}
	else if (chInput == 'a' || chInput == 'A')
	{
		return (int)WASDKeyOrSpace::Left;
	}
	else if (chInput == 's' || chInput == 'S')
	{
		return (int)WASDKeyOrSpace::Down;
	}
	else if (chInput == 'd' || chInput == 'D')
	{
		return (int)WASDKeyOrSpace::Right;
	}
	else if (chInput == ' ')
	{
		return (int)WASDKeyOrSpace::SpaceBar;
	}
	else return 0;
}

inline int TimesTableGame::MoveORSelect(void)
{
	using namespace mglib;
	using namespace std;

	while (1)
	{
		switch (InputKey())
		{
		case (int)WASDKeyOrSpace::Up:

			if (nYPosition > DEF_Y_COORD)
			{
				GotoXY(nXPosition - 2, nYPosition);
				cout << " ";

				GotoXY(nXPosition - 2, --nYPosition);
				settextcol(YELLOW);
				cout << "��";
			}
			break;

		case (int)WASDKeyOrSpace::Down:

			if (nYPosition < DEF_Y_COORD + 4) //������ǥ + 4 : 5���� �޴��� �����ϸ�, Ŀ�� ������ ����
			{
				GotoXY(nXPosition - 2, nYPosition);
				cout << " ";

				GotoXY(nXPosition - 2, ++nYPosition);
				settextcol(YELLOW);
				cout << "��";
			}
			break;

		case (int)WASDKeyOrSpace::SpaceBar:

			return nYPosition - DEF_Y_COORD; //(����) - (�⺻ y��ǥ)�� ���� switch���� ���� ���� ��ȯ 

		default:
			break;
		}
	}
}

inline void TimesTableGame::PrintDot(int nDot)
{
	using namespace mglib;

	for (int i = 0; i < nDot; i++)
	{
		Sleep(LOADING_SCREEN_DELAY);
		settextcol(WHITE);
		std::cout << ".";
	}
}

inline void TimesTableGame::StartLogoPrint(std::ifstream& file)
{
	using namespace mglib;
	using namespace std;

	cout << "\n\n\n\n\n\n";

	while (getline(file, strStartLogo))
	{
		settextcol(SKYBLUE);
		cout << "\t\t\t\t\t" << strStartLogo << endl;
	}

	InitXY();
	GotoXY(nXPosition + 5, nYPosition);

	cout << "Loading";
	PrintDot(4);
}

inline void TimesTableGame::EndLogoPrint(std::ifstream& file)
{
	using namespace std;

	cout << "\n\n\n\n\n\n";

	while (getline(file, strEndLogo))
	{
		cout << "\t\t\t\t" << strEndLogo << endl;
	}

	InitXY();
	GotoXY(nXPosition + 3, nYPosition);

	cout << "Program off";
	PrintDot(4);

	GotoXY(nXPosition + 3, nYPosition + 8);
}

/*
inline void TimesTableGame::PrintStats(void)
{
	using namespace std;

	for (auto& user : Stats)
	{
		cout << "�̸� : " << user.mName << " ���� : " << user.mDifficulty << " �÷��� �ð� : " << user.mPlayTime << " ���� ���� : " << user.mCorrectRatio * 100.0 << "%" << endl;
	}
}

inline void TimesTableGame::UpdateStats(TimesTableGame UserStats)
{
	using namespace std;

	Stats.push_back(UserStats);

	sort(Stats.begin(), Stats.end(), [](TimesTableGame& Stats_1, TimesTableGame& Stats_2) //sort() �޼ҵ带 �̿��Ͽ� ������ ���� ����ڰ� ���� ��ũ�� ��ġ�ϵ��� ��
		{
			return Stats_1.mDifficulty > Stats_2.mDifficulty;
		});

	if (Stats.size() > 5) {
		Stats.pop_back();
	}
}

inline void TimesTableGame::SaveStats(std::string& filename)
{
	using namespace std;

	ofstream SavedStats(filename);

	if (SavedStats.is_open())
	{
		for (auto& user : Stats)
		{
			SavedStats << user.mName << ' ' << user.mDifficulty << ' ' << user.mPlayTime << ' ' << user.mCorrectRatio << endl;
		}
		SavedStats.close();
	}
	else
	{
		cout << "������ �� �� �����ϴ�." << endl;
	}
}

inline void TimesTableGame::LoadStats(std::string& filename)
{
	using namespace std;

	ifstream SavedStats(filename);
	TimesTableGame user;

	if (SavedStats.is_open())
	{
		Stats.clear();

		while (SavedStats >> user.mName >> user.mDifficulty >> user.mPlayTime >> user.mCorrectRatio)
		{
			Stats.push_back(user);
		}
		SavedStats.close();
	}
	else
	{
		cout << "������ �� �� �����ϴ�." << endl;
	}
}*/