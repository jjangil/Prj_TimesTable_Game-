#pragma once

#include <iostream>
#include <string>			//C++의 표준 라이브러리: C++의 표준 문자열(string)은 string; string은 namespace std에 정의됨
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>		
#include "LibConsole.hpp"	//콘솔 출력 색깔 선택
#include "LibGameTool.hpp"	//난수 처리 기능

#define DEF_TIMES_MAX	(9)			//구구단 출력의 디폴트 출력 단수
#define MAX_STREAM_SIZE	(10000)		//스트림 입출력을 할 때 처리하는 최대 문자 수
#define DEF_X_COORD (46)			//디폴트 X좌표 값
#define DEF_Y_COORD (13)			//디폴트 Y좌표 값
#define LOADING_SCREEN_DELAY (500)	//시작화면 지연시간 msec단위
#define DIFF_EASY (5)
#define DIFF_NOMAL (10)
#define DIFF_HARD (15)

/*
	- "enum" OpType
	- C 언어		: 열거형 상수 정의
	- C++ 언어	: 열거형 클래스 정의(내부에 멤버 상수가 있음); 내부에 정의한 상수가 다른 코드 블록과 잘 겹치지 않음

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
	- 원칙: 파일명은 클래스명은 같이(의무는 아니고 권고)
	- 코드 블록의 캡슐화
*/
class TimesTableGame
{
public: //public group(외부에서 접근 가능: C 언어의 구조체(struct)와 동일)

	//생성자(constructor): 클래스명과 같은 이름을 가진 멤버 함수
	TimesTableGame(void) 
	{
		using namespace mglib;
		randseed(); //난수 초기화
	}

	/*벡터를 사용하려고 하였으나 버그를 수정하지 못함
	TimesTableGame(const std::string strName, int nDifficulty = 0, int nPlayTime = 0, double dbCorrectRatio = 0.0)
	{
		mName = strName;
		mDifficulty = nDifficulty;
		mPlayTime = nPlayTime;
		mCorrectRatio = dbCorrectRatio;
	}*/

	//소멸자, 파괴자(destructor): 클래스명 앞에 ~(not 의미)를 붙인 멤버 함수
	~TimesTableGame() {}


	//setter
	void setXpos(int nXPos);
	void setYpos(int nYpos);
	
	//메소드 (비활성화 된 메소드는 "Menu" 통합 메소드로 기능이 흡수)
	//void start(void);
	//void printLogo(void);
	//void printMenu(void);
	//int inputMenu(void);						//출력: 사용자의 메뉴 선택 번호
	int inputInt(const std::string& sInput);	//정수 입력: sInput은 입력시 출력할 문장
	int inputTimesNum(void);					//출력: 원하는 단수
	int inputMaxTimesNum(void);					//출력: 출력할 최대 단수
	int inputGameTimesNum(void);				//출력: 원하는 단수
	void InputUserName(void);					//사용자 이름을 입력받는 메소드
	void Menu(void);							//타이틀 화면 및 메뉴 통합 메소드
	void printTimesTable(int i, int jMax);		//원하는 단수 출력 메소드
	void printAllTimesTable(int nTimesMax);		//모든 구구단 출력 메소드
	void startGame(int nTimes);					//구구단 게임 메소드
	void exeEasyGame(int nTimes);
	void exeNomalGame(int nTimes);
	void exeHardGame(int nTimes);
	//void exeMenu(int nMenu);

	//통계 저장 기능 메소드 (버그 수정 실패로 비활성화)
	/*
	void PrintStats(void);						//통계 출력 메소드
	void UpdateStats(TimesTableGame UserStats);	//통계 업데이트 메소드
	void SaveStats(std::string& filename);		//통계 저장 메소드
	void LoadStats(std::string& filename);		//통계 불러오기 메소드
	*/

private: //private group(외부에서 접근 불가능)

	//private property(멤버 변수)
	int nXPosition = 0;			//nXPosition : X좌표
	int	nYPosition = 0;			//nYPosition : Y좌표
	int nSelectDiff = 0;		//난이도 선택
	int m_nNumCalc = 0;
	int m_nCorrectCalc = 0;
	double m_totalCalcTime = 0.0;

	double correctRatio = 0.0;	//정답비율 
	double avgCalcTime = 0.0;	//걸린시간


	std::string strUserName;	//사용자 이름
	std::string strStartLogo;
	std::string strEndLogo;
	std::string strTitle;

	/*
	int mDifficulty = 0;			//점수
	int mPlayTime = 0;				//플레이 시간
	double mCorrectRatio = 0.0;		//정답 비율
	std::string SavedStats = "SavedStats.txt";		//통계 파일 명칭
	std::vector<TimesTableGame>Stats;				//통계 기능을 위한 벡터
	std::string mName;								//사용자 이름
	*/

	//private method(멤버 함수)

	int getIntSafe(void);
	bool playTimesTable(int nTimes); // true: 계속 실행; false: 게임을 종료
	void updateScore(bool bCorrect, int nCorrectAns, double calcTime);

	//메뉴 기능 통합을 위한 메소드
	void SaveStats(std::ofstream& file);		//통계 저장 메소드
	void LoadStats(std::ifstream& file);		//통계 불러오기 메소드
	void DisplayStats(void);					//통계 출력 메소드
	void TitlePrint(std::ifstream& file);		//프로그램 제목 출력 메소드
	void GotoXY(int nXPos, int nYPos);			//콘솔 커서 좌표변경 메소드
	void InitXY(void);							//X, Y좌표 초기화 메소드
	void MenuPrint(void);						//메뉴 출력 메소드
	int SetGameLevel(void);						//난이도 설정 메소드
	int InputKey(void);							//WASD키 입력 메소드
	int MoveORSelect(void);						//메뉴 이동 및 선택 메소드
	void PrintDot(int nDot);					//로딩, 종료시 점을 출력하는 메소드
	void StartLogoPrint(std::ifstream& file);	//Start 메시지 출력 메소드
	void EndLogoPrint(std::ifstream& file);		//End 메시지 출력 메소드
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
		//메뉴 출력
		printMenu();

		// 사용자 입력
		nMenu = inputMenu();

		//cout << "입력한 번호: " << nMenu;
		exeMenu(nMenu);
	}
}*/

/*inline void TimesTableGame::printLogo(void)
{
	using namespace mglib;
	using namespace std;
	settextcol(YELLOW);

	cout << "\t\t\t" << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "\t\t\t" << " _____  _                         _____         _      _       " << endl;
	cout << "\t\t\t" << "|_   _|(_)                       |_   _|       | |    | |      " << endl;
	cout << "\t\t\t" << "  | |   _  _ __ ___    ___  ___    | |    __ _ | |__  | |  ___ " << endl;
	cout << "\t\t\t" << "  | |  | || '_ ` _ \\  / _ \\/ __|   | |   / _` || '_ \\ | | / _ \\" << endl;
	cout << "\t\t\t" << "  | |  | || | | | | ||  __/\\__ \\   | |  | (_| || |_) || ||  __/" << endl;
	cout << "\t\t\t" << "  \\_/  |_||_| |_| |_| \\___||___/   \\_/   \\__,_||_.__/ |_| \\___|" << endl;
	cout << "\t\t\t" << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl << endl;
}*/

/*inline void TimesTableGame::printMenu(void)
{
	using namespace mglib;
	using namespace std;
	settextcol(RED);

	cout << "\t\t\t" << "1. 모든 구구단 출력" << endl;
	cout << "\t\t\t" << "2. 원하는 단만 출력" << endl;
	cout << "\t\t\t" << "3. 구구단 게임" << endl;
	cout << "\t\t\t" << "4. 프로그램 종료" << endl;
}*/

/*inline int TimesTableGame::inputMenu(void)
{
	using namespace mglib;
	using namespace std;
	settextcol(WHITE);

	int nMenu = 0;


	cout << "\t\t\t" << "원하는 번호를 선택하세요. 번호는? ";
	cin >> nMenu; // cin: console input(보통 키보드)

	return nMenu;
}*/

inline int TimesTableGame::inputInt(const std::string& sInput)
{
	using namespace mglib;
	using namespace std;

	settextcol(WHITE);

	int nInput = 0;

	cout << sInput;
	cin >> nInput; // cin: console input(보통 키보드)

	return nInput;
}

inline int TimesTableGame::inputTimesNum(void)
{
	return inputInt("출력하기 원하는 단수를 입력하세요. 단수는? : ");
}

inline int TimesTableGame::inputMaxTimesNum(void)
{
	return inputInt("출력할 최대 단수를 입력하세요. 단수는? : ");
}

inline int TimesTableGame::inputGameTimesNum(void)
{
	return inputInt("구구단을 연습할 단수를 입력하세요. 단수는? : ");
}

inline void TimesTableGame::InputUserName(void)
{
	using namespace std;

	GotoXY(nXPosition - 3, nYPosition);
	cout << "사용자 이름을 입력해주세요 : ";
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

	StartLogoPrint(StartLogoFile); //시작 로고 출력
	system("cls");

	InputUserName(); //사용자 이름 입력
	system("cls");

	while (1)
	{
		ifstream TitleFile("Title.txt");
		
		InitXY();				//X,Y좌표 초기화
		TitlePrint(TitleFile);	//타이틀화면 출력
		MenuPrint();			//메뉴 목록 출력

		switch (MoveORSelect())
		{
		case 0:
			system("cls");
			GotoXY(nXPosition, nYPosition); //InitXY() 메소드를 통해 초기화된 x:46, y:13좌표로 커서 이동
			cout << "모든 구구단 출력";

			GotoXY(nXPosition - 12, nYPosition + 2); // x:46, y:13 좌표에서 각각 -12, +2 연산값 만큼 커서 이동
			printAllTimesTable(inputMaxTimesNum());

			system("PAUSE"); //모든 구구단 출력후 키 입력시 까지 대기
			break;

		case 1:
			system("cls");
			InitXY();
			GotoXY(nXPosition, nYPosition);
			cout << "원하는 단만 출력";

			GotoXY(nXPosition - 12, nYPosition + 2);
			printTimesTable(inputTimesNum(), DEF_TIMES_MAX);

			system("PAUSE");
			break;

		case 2:
			system("cls");
			InitXY();
			GotoXY(nXPosition + 2, nYPosition);
			cout << "구구단 게임";

			GotoXY(nXPosition - 12, nYPosition + 2);
			startGame(inputGameTimesNum());
			SaveStats(SaveFile); //게임 종료시 통계 저장
			break;

		case 3:
			system("cls");
			InitXY();
			GotoXY(nXPosition, nYPosition - 5);
			cout << "게임 통계" << endl;
			LoadStats(OpenFile); //저장된 통계 불러오기
			DisplayStats();		 //불러온 통계 출력
			break;

		case 4:
			system("cls");
			InitXY();
			EndLogoPrint(EndLogoFile); //엔딩 로고 출력
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

	settextcol(nColor); // 출력하는 글자색을 RED로 변경

	//printf("[%d단 출력]\n", i);
	cout << '[' << i << "단 출력]" << endl;

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

	nSelectDiff = SetGameLevel(); //난이도 선택 메소드

	switch (nSelectDiff)
	{
	case 1:
		exeEasyGame(nTimes); //쉬움 난이도
		break;

	case 2:
		exeNomalGame(nTimes); //보통 난이도
		break;	

	case 3:
		exeHardGame(nTimes); //어려움 난이도
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
			cout << endl << "\t\t\t" << "게임을 종료합니다." << endl << endl;
			break; // 반복문 종료 키워드
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
			cout << endl << "\t\t\t" << "게임을 종료합니다." << endl << endl;
			break; // 반복문 종료 키워드
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
			cout << endl << "\t\t\t" << "게임을 종료합니다." << endl << endl;
			break; // 반복문 종료 키워드
		}
	}
}

inline int TimesTableGame::getIntSafe(void)
{
	using namespace std;
	int nInput;

	cin >> nInput;
	//입력을 받을 때 정수가 아니면 에러 발생; 에러가 생기면 cin이 동작하지 않음
	//bool bResult = (cin.rdstate() == ios::goodbit); // 개선된 에러 처리 방법
	//if (!bResult) cout << endl << "입력 에러 발생" << endl;

	cin.clear(); //에러가 생긴 상태를 없앰
	cin.ignore(MAX_STREAM_SIZE, '\n');	//만 개 문자를 무시; 엔더를 만나면 무시 종료
	//에러가 생기면 nInput = 0이 실행됨
	return nInput;
}

inline bool TimesTableGame::playTimesTable(int iTimes)
{
	using namespace std;
	using namespace mglib;

	int nMaxTimes = 0,		//구구단 게임 진행 횟수
		jTimes = 0,			//난수
		nResult = 0,		//계산값
		nAns = 0,			//플레이어 입력
		nCorrectAns = 0;	//정답 계산

	double calcTime = 0.0;	//경과 시간(계산)
	bool bCorrect;			//bool 자료형: true, false만 가능

	nMaxTimes = __max(iTimes, DEF_TIMES_MAX); // 9단 이하일 때는 난수를 9까지 나오도록 발생
	jTimes = randrange(1, nMaxTimes + 1); // 1, 2, ..., nTimes까지 정수 난수 발생

	/*
		- int nOp = randrange(1, 2 + 1); // 1(곱셈), 2(나눗셈)에서 난수 발생
		- 형 선정(type casting): int(), OpType()
	*/
	OpType nOp = OpType(randrange(int(OpType::OT_MUL), int(OpType::OT_DIV) + 1));

	nResult = iTimes * jTimes; //nResult = 입력된 단(iTimes) * 무작위 난수(jTimes) 
	settextcol(GREEN);


	if (nOp == OpType::OT_MUL) //Multiplication : 곱셈의 경우 
	{
		cout << "\t\t\t" << iTimes << " x " << jTimes << " = ?" << endl;
	}
	else
	{
		cout << "\t\t\t" << iTimes << " x ? = " << nResult << endl;
	}

	settextcol(WHITE);

	cout << "\t\t\t" << "답은 ?\t:";

	//플레이어가 계산하는 부분

	clock_t nBeginTime = clock(); //msec 단위로 현재 시간 계산(시간 측정의 출발점은 프로그램이 실행될 때); _t 붙인 이유: typedef으로 정의한 자료형을 강조
	nAns = getIntSafe(); //int nAns; cin >> nAns;
	clock_t nEndTime = clock();
	calcTime = (nEndTime - nBeginTime) / double(CLOCKS_PER_SEC);


	// 에러가 발생하면 종료
	if (nAns == 0)
	{
		return false;
	}

	/*
		- 조건문용 삼항 연산자
		- 곱셈이라면 nResult, 아니라면 jTimes
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

	if (bCorrect) //맞은 경우
	{
		m_nCorrectCalc++;
		m_totalCalcTime += calcTime;

		settextcol(RED);

		cout << endl << "정답입니다." << endl;
		cout << "계산 시간은 " << calcTime << "초입니다." << endl << endl;
	}
	else //틀린 경우
	{
		settextcol(BLUE);

		cout << endl << "틀렸습니다." << endl;
		cout << "정답은 " << nCorrectAns << "입니다." << endl << endl;
	}

	correctRatio = m_nCorrectCalc / double(m_nNumCalc) * 100.0;
	avgCalcTime = m_totalCalcTime / double(m_nCorrectCalc);

	cout << "정답 비율: " << correctRatio << "%" << endl;
	cout << "평균 계산 시간: " << avgCalcTime << "초" << endl << endl;
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

	cout << endl << "\t\t\t\t\t사용자 이름\t:" << strUserName << endl;
	cout << "\t\t\t\t\t플레이 난이도\t:" << nSelectDiff << "Lv." << endl;
	cout << "\t\t\t\t\t정답 비율\t:" << correctRatio << '%' << endl;
	cout << "\t\t\t\t\t평균 풀이 속도\t:" << avgCalcTime << " 초" << endl;

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
		getline 함수는 입력 스트림에서 문자들을 읽어서, 인자로 받은 문자열에 저장
		입력 스트림에서 문자를 읽다가 delim 문자를 읽게되면, 해당 문자를 버리고, 읽어들이기를 종료 
		만약에 delim 문자를 설정하지 않았다면, 디폴트로 개행 문자('\n')로 설정됨.
	*/
	while (getline(file, strTitle))
	{
		settextcol(YELLOW);
		cout << "\t\t\t" << strTitle << endl;
	}
}

inline void TimesTableGame::GotoXY(int nXPos, int nYPos)
{
	COORD Position; //Short X,Y typedef임, X, Y좌표로 커서 위치를 옮기는 동작을 수행

	Position.X = nXPos;
	Position.Y = nYPos;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}

inline void TimesTableGame::InitXY(void)
{
	//기본 X, Y좌표 값으로 초기화
	setXpos(DEF_X_COORD);
	setYpos(DEF_Y_COORD);
}

inline void TimesTableGame::MenuPrint(void)
{
	using namespace mglib;
	using namespace std;

	GotoXY(nXPosition - 2, nYPosition);
	settextcol(YELLOW);
	cout << "▶";
	settextcol(RED);
	cout << " 모든 구구단 출력" << endl;

	GotoXY(nXPosition, nYPosition + 1);
	cout << "원하는 단만 출력" << endl;

	GotoXY(nXPosition, nYPosition + 2);
	cout << "구구단 게임" << endl;

	GotoXY(nXPosition, nYPosition + 3);
	cout << "통계" << endl;

	GotoXY(nXPosition, nYPosition + 4);
	cout << "프로그램 종료" << endl;

	GotoXY(nXPosition + 3, nYPosition + 8);
	settextcol(WHITE);
	cout << "■ 조작법 ■";

	GotoXY(nXPosition - 16, nYPosition + 10);
	cout << "[w] 위로 이동 [s] 아래로 이동 [spacebar] 메뉴 선택";
}

inline int TimesTableGame::SetGameLevel(void)
{
	int nInput = 0;

	using namespace mglib;
	using namespace std;

	system("cls");

	settextcol(WHITE);
	GotoXY(nXPosition - 10, nYPosition);
	cout << "난이도에 따라 제시되는 문항수가 변동됩니다" << endl;

	settextcol(GREEN);
	GotoXY(nXPosition - 8, nYPosition + 2);
	cout << "[Easy] : 1, [Nomal] : 2, [Hard] : 3" << endl;

	settextcol(WHITE);
	GotoXY(nXPosition - 2, nYPosition + 4);
	cout << "난이도를 선택하여 주세요 : ";
	cin >> nInput;

	system("cls");
	GotoXY(5, 4); //문제 풀이 좌표로 이동

	return nInput;
}

inline int TimesTableGame::InputKey(void) //방향키 없는 사용자를 위해 wasd키를 사용
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
				cout << "▶";
			}
			break;

		case (int)WASDKeyOrSpace::Down:

			if (nYPosition < DEF_Y_COORD + 4) //시작좌표 + 4 : 5가지 메뉴가 존재하며, 커서 범위를 제한
			{
				GotoXY(nXPosition - 2, nYPosition);
				cout << " ";

				GotoXY(nXPosition - 2, ++nYPosition);
				settextcol(YELLOW);
				cout << "▶";
			}
			break;

		case (int)WASDKeyOrSpace::SpaceBar:

			return nYPosition - DEF_Y_COORD; //(변수) - (기본 y좌표)를 통해 switch문에 사용될 정수 반환 

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
		cout << "이름 : " << user.mName << " 점수 : " << user.mDifficulty << " 플레이 시간 : " << user.mPlayTime << " 정답 비율 : " << user.mCorrectRatio * 100.0 << "%" << endl;
	}
}

inline void TimesTableGame::UpdateStats(TimesTableGame UserStats)
{
	using namespace std;

	Stats.push_back(UserStats);

	sort(Stats.begin(), Stats.end(), [](TimesTableGame& Stats_1, TimesTableGame& Stats_2) //sort() 메소드를 이용하여 점수가 높은 사용자가 높은 랭크에 위치하도록 함
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
		cout << "파일을 열 수 없습니다." << endl;
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
		cout << "파일을 열 수 없습니다." << endl;
	}
}*/