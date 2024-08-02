#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Boss.h"
#include "Boss.cpp"
#define Exp_rand_box (((float)(rand() % 7) / 10) + 1.8)             // 2렙 이후 부터 레벨 당 경험치 수치 1.8배 ~ 2.5배 선택됨
#define Exp_rand_stage rand() % 7001 - 3500                         // 단계마다 경험치 -3500 ~ +3500 랜덤으로 선택됨
#define Exp_rand_event (((float)(rand() % 40) / 10) + 1)            // 이벤트 경험치 1.0배 ~ 5.0배 랜덤으로 선택됨
using namespace std;

void now(float, int, int, int);
void output(void);
void error(void);
void the_end(string, int);

int main()
{
    srand(time(NULL));              // 랜덤 변수 시간을 이용해 계속해서 초기화
    string name;                    // 유저 이름
    string m_name;                  // 몬스터 이름
    int level = 1;                  // 레벨
    int dungeon;                    // 던젼(1던젼~5던젼)
    int stage;                      // 단계(1단계~5단계)
    int turn = 0;                   // 턴 수
    int number;                     // 던젼 선택, 재시작 및 종료 입력 번호
    int m_number;                   // 몬스터 해당 번호
    float Exp_box = 0;              // 경험치 박스
    float Exp_stage = 0;            // 단계마다의 경험치
    float Exp = 0;                  // 총 경험치

    Monster c ("Iron Boy", 26);
    Monster j ("Juno Panther", 26);
    Monster d ("Captain Ddong", 31);
    Monster s ("Scarlet Onsi", 29);

    cout << "이름을 입력하시오: ";
    getline(cin, name);

    while(1)
    {
        cout << endl;
        if (level == 1)
        {
            Exp_box = 30000;                                // 1렙일 때의 3만 경험치 고정
        }
        for(dungeon=1; dungeon<=5; dungeon++)
        {
            for (stage=1; stage<=5; stage++)                    // 1 ~ 5단계
            {
                Exp_stage = Exp_rand_stage;                     // -3500 ~ +3500 까지 랜덤하게 경험치를 뽑는다
                Exp += Exp_stage;
                cout << stage << "단계" << endl;

                m_number = (rand() % 4) +1;
                if(m_number == 1)
                {
                    c.battle(c, Exp_rand_stage);
                }
                else if(m_number == 2)
                {
                    j.battle(j, Exp_rand_stage);
                }
                else if(m_number == 3)
                {
                    d.battle(d, Exp_rand_stage);
                }
                else
                {
                    s.battle(s, Exp_rand_stage);
                }

                if(stage == 5)                                  // 5단계 후 event
                {
                    Exp *= Exp_rand_event;
                    cout << "이벤트 경험치 " << Exp_rand_event << "배를 획득하였습니다." << endl;
                    cout << name << "님이 이번 턴에서 얻은 총 경험치: " << Exp << endl;
                    cout << endl;
                }
            }

            while(Exp > Exp_box)                // 레벨 업
            {
                level++;
                Exp = Exp - Exp_box;            // 초과 경험치 이월
                Exp_box *= Exp_rand_box;

                if(level < 99)                  // 렙 99 미만
                {
                    cout << name << "님 축하합니다! 레벨 업 되셨습니다!" << endl;
                    printf("Lv. %d의 경험치 MAX 값: %.2f\n", level, Exp_box);
                    cout << endl;
                }
                else                            // 렙 99 이상 -> 해피엔딩
                {
                    printf("Lv. %d, 게임 종료!", level);
                    break;
                }
            }

            while(Exp < 0)                      // 레벨 다운
            {
                level--;
                Exp = Exp_box - Exp;
                Exp_box = Exp_box / Exp_rand_box;
                printf("Lv. %d, 레벨 다운\n", level);
                cout << endl;
            }

            turn++;
            now(Exp, level, dungeon, turn);
            output();

            cin >> number;
            while(number == 0)
            {
                error();
                cin >> number;
            }
            if(dungeon == 5 && number == 1)
            {
                cout << endl;
                cout << "현재 최고 던젼인 5던젼입니다." << endl;
                output();
                cin >> number;
            }

            if(number == 1)
            {
                cout << "다음 던젼으로 이동합니다" << endl;
                if(dungeon == 5)
                {
                    cout << "1던젼으로 이동합니다." << endl;
                    dungeon = 0;
                }
                if(level >= 99)
                {
                    break;
                }
                else if(level < 1)
                {
                    break;
                }
            }
            else if(number == 2)
            {
                cout << "현재 던젼에 머무릅니다." << endl;
                --dungeon;
                if(level >= 99)
                {
                    break;
                }
                else if(level < 1)
                {
                    break;
                }
            }
            else
            {
                cout << "이전 던젼으로 이동합니다." << endl;
                --dungeon;
                --dungeon;
                if(dungeon <= -1)
                {
                    dungeon = 0;
                }
                if(level >= 99)
                {
                    break;
                }
                else if(level < 1)
                {
                    break;
                }
            }
            cout << endl;
        }
        the_end(name, level);
        cin >> number;
        while(number == 0)
        {
            error();
            cin >> number;
        }
        if(number == 7)
        {
            level = 1;
            turn = 0;
            Exp = 0;
            continue;
        }
        else
        {
            break;
        }

    }
    cout << "게임 종료" << endl;
    return 0;
}

void now(float exp, int lv, int dg, int tr)
{
    printf("현재 경험치: %.2f\n", exp);
    printf("현재 레벨: %d\n", lv);
    printf("진행 던젼: %d\n", dg);
    printf("진행 턴 수: %d\n", tr);
}

void output(void)
{
    cout << "다음 던젼으로 이동 원할 시 숫자 1을 입력하시오." << endl;
    cout << "현재 던젼에 머물길 원할 시 숫자 2를 입력하시오." << endl;
    cout << "이전 던젼으로 이동 원할 시 숫자 3 이상을 입력하시오." << endl;
    cout << ": ";
}

void error(void)
{
    cout << "잘못 입력하였습니다." << endl;
    cout << "다시 입력해주십시오.: ";
}

void the_end(string n, int l)
{
    if(l >= 99)
    {
        cout << "Lv.99 달성" << endl;
    }
    else if(l < 1)
    {
        cout << "Lv. 1 이하, " << n << "님 사망" << endl;
    }
    cout << endl;
    cout << "다시 시작을 원할 경우: 7" << endl;
    cout << "종료를 원할 경우: 7을 제외한 숫자" << endl;
    cout << ": ";
}