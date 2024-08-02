#include <iostream>
#include <cstring>
#include "Boss.h"
using namespace std;

Monster::Monster(string n, int a)
{
    name = n;
    lv = a;
}

void Monster::battle(Monster m, int exp)
{
    if (exp >= 0)
    {
        cout << "Lv." << m.lv << " " << m.name << "를 처치하였습니다." << endl;
        printf("%.2d 의 경험치를 획득했습니다.\n", exp);
    }
    else
    {
        cout << "Lv." << m.lv << " " << m.name << "를 처치하지 못하였습니다." << endl;
        printf("%.2d 의 경험치가 차감되었습니다.\n", exp);
    }
}