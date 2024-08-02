#ifndef Boss_H_
#define Boss_H_

#include <string>
using namespace std;
class Monster
{
private:
    string name;
    int lv;
public:
    Monster(string n, int a);
    void battle(Monster, int);
};


#endif