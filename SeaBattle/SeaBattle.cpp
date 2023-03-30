// SeaBattle.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
using namespace std;
//int automaticFillField(char** efield, char** mfield, int size, bool* shipsFullPtr);
char** createField(int size);
void printBattleField(char** enemy, char** my, int size, HANDLE console);
void printMyBattleField(char** enemy, char** my, int size);
void createShip(char** array, char* str, char rang);
void deathShip(char** field, char* decks);
int checkShip(char* decks, int size);
int checkField(char** field, char* decks);
int fillField(char** efield, char** mfield, int size, bool* shipsFullPtr, bool* enemyShipsFullPtr, HANDLE console, char** shipsEnemy, char** shipsMy);
int mainMenu(bool* shipsFullPtr, bool* pausePtr, bool* compVsCompPtr, HANDLE console, char** ships, bool* firstStartPtr);
int automaticFF(char** field, bool* shipsFullPtr, int size, char** ships);
int battle(char** enemyField, char** myField, char** tempField, int size, bool* playerWinPtr, bool* compVsComp, HANDLE console, char** ships, char** shipsEn);
char* attack(char** field);
int strValid(char* str);
void win(const char* str, HANDLE console, bool *firstStart);

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    int size = 11;
    const char* player = "Игрок победил!!! :)";
    const char* computer = "Компьютер победил!!! :(";
    char** enemyField = createField(size);
    char** myField = createField(size);
    char** tempField = createField(size);
    char** shipsEnemy = new char* [10];
    for (int i = 0; i < 10; i++) {
        shipsEnemy[i] = new char[6];
    }
    char** shipsMy = new char* [10];
    for (int i = 0; i < 10; i++) {
        shipsMy[i] = new char[6];
    }
    bool menu = true; // Окно стартового меню
    bool arrangeShips = false; // Окно расстановки кораблей
    bool autoArrangeShips = false; // Окно автоматической расстановки кораблей
    bool battleField = false; // Окно сражения
    bool shipsFullFlag = false; bool* shipsFullFlagPtr = &shipsFullFlag; // Расставлены корабли или нет
    bool pauseFlag = false; bool* pauseFlagPtr = &pauseFlag;
    bool enemyShipsFull = false; bool* enemyShipsFullPtr = &enemyShipsFull;
    bool playerWin = false; bool* playerWinPtr = &playerWin;
    bool compVsComp = false; bool* compVsCompPtr = &compVsComp;
    bool firstStart = true; bool* firstStartPtr = &firstStart;
    while (true) {
        if (menu) { //  Окно меню
            int checkMenu = mainMenu(shipsFullFlagPtr, pauseFlagPtr, compVsCompPtr, console, shipsEnemy, firstStartPtr);
            if (checkMenu == 1) {
                if (shipsFullFlag) {
                    if (pauseFlag) {
                        delete[]tempField;
                        tempField = createField(size);
                    }
                    menu = false;
                    arrangeShips = false;
                    autoArrangeShips = false;
                    battleField = true;
                    continue;
                }
                else {
                    continue;
                } 
            }
            else if (checkMenu == 2) {
                if (pauseFlag) {
                    continue;
                }
                delete[]tempField;
                tempField = createField(size);
                automaticFF(enemyField, enemyShipsFullPtr, size, shipsEnemy);
                automaticFF(myField, shipsFullFlagPtr, size, shipsMy);
                continue;
            }
            else if (checkMenu == 3) {
                if (pauseFlag) {
                    continue;
                }
                menu = false;
                arrangeShips = true;
                autoArrangeShips = false;
                battleField = false;
                continue;
            }
            else if (checkMenu == 4) {
                if (pauseFlag) {
                    menu = false;
                    arrangeShips = false;
                    autoArrangeShips = false;
                    battleField = true;
                    continue;
                }
                else {
                    continue;
                }
            }
            else if (checkMenu == 5) {
                if (compVsComp) {
                    compVsComp = false;
                }
                else {
                    compVsComp = true;
                }
                continue;
            }
            else {
                continue;
            }
        }
        if (arrangeShips) { // Окно расстановки кораблей
            int checkArrangeShips = fillField(enemyField, myField, size, shipsFullFlagPtr, enemyShipsFullPtr, console, shipsEnemy, shipsMy);
            if (checkArrangeShips == 1) {
                arrangeShips = false;
                battleField = true;
            }
            else if (checkArrangeShips == 2) {
                delete[]myField;
                myField = createField(size);
                shipsFullFlag = false;
                continue;
            }
            else if (checkArrangeShips == 3) {
                if (!shipsFullFlag) {
                    delete[]myField;
                    myField = createField(size);
                }
                menu = true;
                arrangeShips = false;
                continue;
            }
            else if (checkArrangeShips == 4) {
                automaticFF(myField, shipsFullFlagPtr, size, shipsMy);
                continue;
            }
        }
        if (battleField) { // Окно сражения  
            int checkBattle = battle(enemyField, myField, tempField, size, playerWinPtr, &compVsComp, console, shipsEnemy, shipsMy);
            if (checkBattle == 1) {
                battleField = false;
                menu = true;
                pauseFlag = true;
                continue;
            }
            else if (checkBattle == 2) {
                battleField = false;
                menu = true;
                pauseFlag = false;
                arrangeShips = false;
                shipsFullFlag = false;
                delete[]tempField;
                delete[]enemyField;
                tempField = createField(size);
                enemyField = createField(size);
                continue;
            }
            else if (checkBattle == 0) {
                (playerWin) ? win(player, console, &firstStart)/*cout << "PLAYER WIN!!!"*/ : win(computer, console, &firstStart)/*cout << "COMPUTER WIN!!!"*/;
                system("pause");
                battleField = false;
                pauseFlag = false;
                arrangeShips = false;
                shipsFullFlag = false;
                playerWin = false;
                enemyShipsFull = false;
                menu = true;
            }
        }
    }
}
void win(const char* str, HANDLE console, bool* firstStart) {
    int x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << endl << str << endl;
    Beep(659, 170);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(622, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(659, 170);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(622, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(659, 170);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(494, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(587, 170);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(523, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(440, 170);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(262, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(330, 170);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(440, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(494, 170);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(330, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(415, 170);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(494, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(523, 170);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(330, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(659, 170);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(622, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(659, 170);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(622, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(659, 170);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(494, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(587, 170);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(523, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(440, 170);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(262, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(330, 170);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(440, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(494, 170);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(330, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(523, 170);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(494, 170);
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    Beep(440, 170);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    x = rand() % 10;
    for (int i = 0; i < x; i++) {
        cout << "\t";
    }
    cout << str << endl;
    *firstStart = true;
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

int strValid(char* str) {
    if (str[0] > 64 && str[0] < 75 && str[1] > 47 && str[1] < 58) {
        return 0;
    }
    else {
        return 1;
    }
}

int battle(char** enemyField, char** myField, char** tempField, int size, bool* playerWinPtr, bool* compVsCompPtr, HANDLE console, char** shipsEnemy, char** shipsMy) {
    int speed = 100;
    char* str = new char[5];
    bool player = true;
    bool computer = false;
    int myShipsArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int EnemyShipsArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int countPlayer = 0;
    int countComputer = 0;
    while (true) {
        system("cls");
        SetConsoleTextAttribute(console, FOREGROUND_BLUE);
        printBattleField(tempField, myField, size, console);

        if (countPlayer == 20) {
            *playerWinPtr = true;
            return 0;
        }
        if (countComputer == 20) {
            return 0;
            *playerWinPtr = false;
        }
        cout << endl;
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "Попадания:" << endl;
        cout << "Игрок: ";
        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
        cout << countPlayer << endl;
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "Компьютер: ";
        SetConsoleTextAttribute(console, FOREGROUND_RED);
        cout << countComputer << endl;
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << endl;
        if (player) {
            cout << "Выстрел: ";
            if (*compVsCompPtr) {
                str = attack(tempField);
            }
            else {
                cin >> str;
                if (strValid(str)) {
                    if (!strcmp(str, "pause")) {
                        return 1;
                    }
                    if (!strcmp(str, "exit")) {
                        return 2;
                    }
                    continue;
                }
            }
            /*if (!strcmp(str, "pause")) {
                return 1;
            }
            else if (!strcmp(str, "exit")) {
                return 2;
            }*/
            if (enemyField[str[1] - 47][str[0] - 64] > 47 && enemyField[str[1] - 47][str[0] - 64] < 58) {
                Beep(100, speed);
                tempField[str[1] - 47][str[0] - 64] = 'X';
                EnemyShipsArray[enemyField[str[1] - 47][str[0] - 64] - 48]++;
                countPlayer++;
            }
            else {
                Beep(500, speed);
                tempField[str[1] - 47][str[0] - 64] = '*';
                player = false;
            }
            if (EnemyShipsArray[0] == 4) {
                deathShip(tempField, shipsEnemy[0]);
                EnemyShipsArray[0] = 9;
            }
            else if (EnemyShipsArray[1] == 3) {
                deathShip(tempField, shipsEnemy[1]);
                EnemyShipsArray[1] = 9;
            }
            else if (EnemyShipsArray[2] == 3) {
                deathShip(tempField, shipsEnemy[2]);
                EnemyShipsArray[2] = 9;
            }
            else if (EnemyShipsArray[3] == 2) {
                deathShip(tempField, shipsEnemy[3]);
                EnemyShipsArray[3] = 9;
            }
            else if (EnemyShipsArray[4] == 2) {
                deathShip(tempField, shipsEnemy[4]);
                EnemyShipsArray[4] = 9;
            }
            else if (EnemyShipsArray[5] == 2) {
                deathShip(tempField, shipsEnemy[5]);
                EnemyShipsArray[5] = 9;
            }
            else if (EnemyShipsArray[6] == 1) {
                deathShip(tempField, shipsEnemy[6]);
                EnemyShipsArray[6] = 9;
            }
            else if (EnemyShipsArray[7] == 1) {
                deathShip(tempField, shipsEnemy[7]);
                EnemyShipsArray[7] = 9;
            }
            else if (EnemyShipsArray[8] == 1) {
                deathShip(tempField, shipsEnemy[8]);
                EnemyShipsArray[8] = 9;
            }
            else if (EnemyShipsArray[9] == 1) {
                deathShip(tempField, shipsEnemy[9]);
                EnemyShipsArray[9] = 9;
            }
            //Sleep(1000);
        }
        else {
            cout << "Выстрел компьютера: ";
            str = attack(myField);
            if (myField[str[1] - 47][str[0] - 64] > 47 && myField[str[1] - 47][str[0] - 64] < 58) {
                myShipsArray[myField[str[1] - 47][str[0] - 64] - 48]++;
                myField[str[1] - 47][str[0] - 64] = 'X';
                countComputer++;
                Beep(100, speed);
            }
            else {
                myField[str[1] - 47][str[0] - 64] = '*';
                Beep(500, speed);
                player = true;
            }
            if (myShipsArray[0] == 4) {
                deathShip(myField, shipsMy[0]);
                myShipsArray[0] = 9;
            }
            else if (myShipsArray[1] == 3) {
                deathShip(myField, shipsMy[1]);
                myShipsArray[1] = 9;
            }
            else if (myShipsArray[2] == 3) {
                deathShip(myField, shipsMy[2]);
                myShipsArray[2] = 9;
            }
            else if (myShipsArray[3] == 2) {
                deathShip(myField, shipsMy[3]);
                myShipsArray[3] = 9;
            }
            else if (myShipsArray[4] == 2) {
                deathShip(myField, shipsMy[4]);
                myShipsArray[4] = 9;
            }
            else if (myShipsArray[5] == 2) {
                deathShip(myField, shipsMy[5]);
                myShipsArray[5] = 9;
            }
            else if (myShipsArray[6] == 1) {
                deathShip(myField, shipsMy[6]);
                myShipsArray[6] = 9;
            }
            else if (myShipsArray[7] == 1) {
                deathShip(myField, shipsMy[7]);
                myShipsArray[7] = 9;
            }
            else if (myShipsArray[8] == 1) {
                deathShip(myField, shipsMy[8]);
                myShipsArray[8] = 9;
            }
            else if (myShipsArray[9] == 1) {
                deathShip(myField, shipsMy[9]);
                myShipsArray[9] = 9;
            }
            //Sleep(1000);
        } 
    }
}

char* attack(char** field) {
    char* str = new char[3];
    str[2] = '\0';
    while (true) {
        str[0] = rand() % 10 + 65;
        str[1] = rand() % 10 + 48;
        if (field[str[1] - 47][str[0] - 64] == '*') {
            continue;
        }
        else if (field[str[1] - 47][str[0] - 64] == 'X') {
            continue;
        }
        else {
            return str;
        }
    }
}

int automaticFF(char** field, bool* shipsFullPtr, int size, char** ships) {  // Автоматическая расстановка кораблей
    for (int i = 1; i < size; i++) {
        for (int j = 1; j < size; j++) {
            field[i][j] = '.';
        }
    }
    int i = 0; int timer = 25;
    char* decks = new char[6];
    bool fullShips = false;
    while (!fullShips) {
        if (i == 0) {
            for (int j = 0; j < 6; j++) {
                if (j == 0 || j == 3) {
                    decks[j] = rand() % 10 + 65;
                }
                else if (j == 2) {
                    decks[j] = '-';
                }
                else if (j == 1 || j == 4) {
                    decks[j] = rand() % 10 + 48;
                }
                else if (j == 5) {
                    decks[j] = '\0';
                }
            }
            if (!checkShip(decks, 4) && !checkField(field, decks)) {
                createShip(field, decks, i + 48);
                for (int m = 0; m < 6; m++) {
                    ships[i][m] = decks[m];
                }
                i++;
                continue;
            }
            else {
                continue;
            }
        }
        else if (i == 1 || i == 2) {
            for (int j = 0; j < 6; j++) {
                if (j == 0 || j == 3) {
                    decks[j] = rand() % 10 + 65;
                }
                else if (j == 2) {
                    decks[j] = '-';
                }
                else if (j == 1 || j == 4) {
                    decks[j] = rand() % 10 + 48;
                }
                else if (j == 5) {
                    decks[j] = '\0';
                }
            }
            if (!checkShip(decks, 3) && !checkField(field, decks)) {
                createShip(field, decks, i + 48);
                for (int m = 0; m < 6; m++) {
                    ships[i][m] = decks[m];
                }
                i++;
                continue;
            }
            else {
                continue;
            }
        }
        else if (i > 2 && i < 6) {
            for (int j = 0; j < 6; j++) {
                if (j == 0 || j == 3) {
                    decks[j] = rand() % 10 + 65;
                }
                else if (j == 2) {
                    decks[j] = '-';
                }
                else if (j == 1 || j == 4) {
                    decks[j] = rand() % 10 + 48;
                }
                else if (j == 5) {
                    decks[j] = '\0';
                }
            }
            if (!checkShip(decks, 2) && !checkField(field, decks)) {
                createShip(field, decks, i + 48);
                for (int m = 0; m < 6; m++) {
                    ships[i][m] = decks[m];
                }
                i++;
                continue;
            }
            else {
                continue;
            }
        }
        else if (i > 5 && i < 10) {
            for (int j = 0; j < 6; j++) {
                if (j == 0) {
                    decks[j] = rand() % 10 + 65;
                    decks[3] = decks[j];
                }
                else if (j == 2) {
                    decks[j] = '-';
                }
                else if (j == 1) {
                    decks[j] = rand() % 10 + 48;
                    decks[4] = decks[j];
                }
                else if (j == 5) {
                    decks[j] = '\0';
                }
            }
            if (!checkShip(decks, 1) && !checkField(field, decks)) {
                createShip(field, decks, i + 48);
                for (int m = 0; m < 6; m++) {
                    ships[i][m] = decks[m];
                }
                i++;
                continue;
            }
            else {
                continue;
            }
        }
        if (i == 10) {
            fullShips = true;
        }
    }
    *shipsFullPtr = true;
    return 0;
}

int mainMenu(bool* shipsFullPtr, bool* pausePtr, bool* compVsCompPtr, HANDLE console, char** ships, bool* firstStartPtr) {
    system("cls");
    char start = ' ';
    cout << endl;
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "*******************************************************************************" << endl;
    cout << "..............................................................................." << endl;
    cout << " ####   #####   ####      #####    ####   ######  ######  ##      #####     ###" << endl;
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    cout << "##      ##     ##  ##     ##  ##  ##  ##    ##      ##    ##      ##        ###" << endl;
    cout << " ####   ####   ######     #####   ######    ##      ##    ##      ####      ###" << endl;
    cout << "    ##  ##     ##  ##     ##  ##  ##  ##    ##      ##    ##      ##           " << endl;
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    cout << " ####   #####  ##  ##     #####   ##  ##    ##      ##    ######  #####     ###" << endl;
    cout << "..............................................................................." << endl;
    cout << "*******************************************************************************" << endl;
    if (*firstStartPtr) {
        Beep(300, 250);
        Beep(300, 250);
        Beep(300, 250);
        Beep(250, 175);
        Beep(350, 100);
        Beep(300, 250);
        Beep(250, 175);
        Beep(350, 100);
        Beep(300, 250);
        Sleep(225);
        Beep(450, 250);
        Beep(450, 250);
        Beep(450, 250);
        Beep(300, 175);
        Beep(350, 100);
        Beep(300, 250);
        Beep(250, 175);
        Beep(350, 100);
        Beep(300, 250);
        *firstStartPtr = false;
    }
    cout << endl;
    cout << endl;
    if (*shipsFullPtr) {
        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
        cout << "1 - Начать сражение";
        (*shipsFullPtr) ? cout << " (Корабли расставлены!)" << endl : cout << " (Необходимо расставить корабли!)" << endl;
    }
    else {
        SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
        cout << "1 - Начать сражение";
        (*shipsFullPtr) ? cout << " (Корабли расставлены!)" << endl : cout << " (Необходимо расставить корабли!)" << endl;
    }
    if (*pausePtr) {
        SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
        cout << "2 - Автоматическая расстановка кораблей" << endl;
        cout << "3 - Расставить корабли в ручную" << endl;
    }
    else {
        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
        cout << "2 - Автоматическая расстановка кораблей" << endl;
        cout << "3 - Расставить корабли в ручную" << endl;
    }
    if (*pausePtr) {
        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
        cout << "4 - Продолжить сражение";
        (*pausePtr) ? cout << " (Игра начата)" << endl : cout << " (Игра еще не начата!)" << endl;
    }
    else {
        SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
        cout << "4 - Продолжить сражение";
        (*pausePtr) ? cout << " (Игра начата)" << endl : cout << " (Игра еще не начата!)" << endl;
    }
    if (*compVsCompPtr) {
        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
        cout << "5 - Режим игры (Компьютер против компьютера)" << endl;
    }
    else {
        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
        cout << "5 - Режим игры (Игрок против компьютера)" << endl;
    }
    cout << endl;
    //cin >> start;
    start = _getch();
    if (start == '1') {
        return 1;
    }
    else if (start == '2') {
        return 2;
    }
    else if (start == '3') {
        return 3;
    }
    else if (start == '4') {
        return 4;
    }
    else if (start == '5') {
        return 5;
    }
    else {
        return 0;
    }
}

int fillField(char** efield, char** mfield, int size, bool* shipsFullPtr, bool* enemyShipsFullPtr, HANDLE console, char** shipsEnemy, char** shipsMy) {  // Функиця расстановки кораблей в ручную
    int i = 0;
    char* decks = new char[6];
    bool fullShips = false;
    automaticFF(efield, enemyShipsFullPtr, size, shipsEnemy);
    if (!*shipsFullPtr) {
        while (!fullShips) {
            system("cls");
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            cout << " Морской бой!" << endl;
            cout << " -------------------------------------------" << endl;
            SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            printMyBattleField(efield, mfield, size);
            cout << endl;
            //cout << "Противник уже расставил корабли, дело за тобой!" << endl;
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            cout << "Используй координатную сетку для указания места установки корабля." << endl;
            cout << "Чтобы поставить четырех палубный корабль укажи первую и последнюю клетку через знак '-'." << endl;
            cout << "Например A1-A4, корабли можно ставить только горизонтально или вертикально!" << endl;
            cout << "Для сброса введи: reset. Для выхода в меню: exit." << endl;
            if (i == 0) {
                cout << "Установи четырехпалубник: ";
                cin >> decks;
                if (!strcmp(decks, "reset")) {
                    return 2;
                }
                else if (!strcmp(decks, "exit")) {
                    return 3;
                }
                if (!checkShip(decks, 4) && !checkField(mfield, decks)) {
                    createShip(mfield, decks, i + 48);
                    for (int m = 0; m < 6; m++) {
                        shipsMy[i][m] = decks[m];
                    }
                    i++;
                    continue;
                }
                else {
                    continue;
                }
            }
            else if (i == 1 || i == 2) {
                cout << "Установи трехпалубник: ";
                cin >> decks;
                if (!strcmp(decks, "reset")) {
                    return 2;
                }
                else if (!strcmp(decks, "exit")) {
                    return 3;
                }
                if (!checkShip(decks, 3) && !checkField(mfield, decks)) {
                    createShip(mfield, decks, i + 48);
                    for (int m = 0; m < 6; m++) {
                        shipsMy[i][m] = decks[m];
                    }
                    i++;
                    continue;
                }
                else {
                    continue;
                }
            }
            else if (i > 2 && i < 6) {
                cout << "Установи двупалубник: ";
                cin >> decks;
                if (!strcmp(decks, "reset")) {
                    return 2;
                }
                else if (!strcmp(decks, "exit")) {
                    return 3;
                }
                if (!checkShip(decks, 2) && !checkField(mfield, decks)) {
                    createShip(mfield, decks, i + 48);
                    for (int m = 0; m < 6; m++) {
                        shipsMy[i][m] = decks[m];
                    }
                    i++;
                    continue;
                }
                else {
                    continue;
                }
            }
            else if (i > 5 && i < 10) {
                cout << "Установи однопалубник: ";
                cin >> decks;
                if (!strcmp(decks, "reset")) {
                    return 2;
                }
                else if (!strcmp(decks, "exit")) {
                    return 3;
                }
                if (!checkShip(decks, 1) && !checkField(mfield, decks)) {
                    createShip(mfield, decks, i + 48);
                    for (int m = 0; m < 6; m++) {
                        shipsMy[i][m] = decks[m];
                    }
                    i++;
                    continue;
                }
                else {
                    continue;
                }
            }
            if (i == 10) {
                fullShips = true;
                *shipsFullPtr = true;
            }
        }
        int check = 0;
        cout << endl << "Корабли расставлены!" << endl;
        cout << "1 - Начать сражение" << endl;
        cout << "2 - Переставить корабли" << endl;
        cout << "3 - Выйти в меню" << endl;
        cout << "4 - Автоматическая расстановка" << endl;
        cin >> check;
        if (check == 1) {
            return 1;
        }
        else if (check == 2) {
            return 2;
        }
        else if (check == 3) {
            return 3;
        }
        else if (check == 4) {
            return 4;
        }
        else {
            return 0;
        }
    }
    else {
        system("cls");
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << " Морской бой!" << endl;
        cout << " -------------------------------------------" << endl;
        SetConsoleTextAttribute(console, FOREGROUND_BLUE);
        printMyBattleField(efield, mfield, size);
        cout << endl;
        /*cout << "Противник уже расставил корабли, дело за тобой!" << endl;
        cout << "Используй координатную сетку для указания места установки корабля." << endl;
        cout << "Чтобы поставить четырех палубный корабль укажи первую и последнюю клетку через знак '-'." << endl;
        cout << "Например A1-A4, корабли можно ставить только горизонтально или вертикально!" << endl;
        cout << "Для сброса введи: reset. Для выхода в меню: exit." << endl;*/
        char check = ' ';
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << endl << "Корабли расставлены!" << endl;
        cout << "1 - Начать сражение" << endl;
        cout << "2 - Переставить корабли" << endl;
        cout << "3 - Выйти в меню" << endl;
        cout << "4 - Автоматическая расстановка" << endl;
        check = _getch();
        if (check == '1') {
            return 1;
        }
        else if (check == '2') {
            return 2;
        }
        else if (check == '3') {
            return 3;
        }
        else if (check == '4') {
            return 4;
        }
        else {
            return 0;
        }
    }
}

int checkShip(char* decks, int size) {                      //  Функия проверки проавильности ввода кораблей, правильный вормат A0-A4,
    if (decks[0] == decks[3] || decks[1] == decks[4]) {     //  корабли ставятся по вертикали либо по горизонтали
        if (decks[0] == decks[3]) {
            if (decks[4] < decks[1]) {
                swap(decks[4], decks[1]);
            }
            if (decks[4] - decks[1] == size - 1) {
                return 0;
            }
            else {
                return 1;
            }
        }
        else {
            if (decks[3] < decks[0]) {
                swap(decks[3], decks[0]);
            }
            if (decks[3] - decks[0] == size - 1) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
    else {
        return 1;
    }
}

int checkField(char** field, char* decks) {  // Функция проверки игрового поля на возможность установки корабля
    if (decks[1] == decks[4]) {
        if (decks[0] > decks[3]) {
            swap(decks[0], decks[3]);
        }
        int test = 0;
        for (int j = decks[0] - 64; j <= decks[3] - 64; j++) {
            if (field[decks[1] - 47][j] == ' ' || field[decks[1] - 47][j] == '#' || field[decks[1] - 47][j] > 47 && field[decks[1] - 47][j] < 58) {
                test++;
            }
        }
        if (test == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else if (decks[0] == decks[3]) {
        if (decks[1] > decks[4]) {
            swap(decks[1], decks[4]);
        }
        int test = 0;
        for (int i = decks[1] - 47; i <= decks[4] - 47; i++) {
            if (field[i][decks[0] - 64] == ' ' || field[i][decks[0] - 64] == '#' || field[i][decks[0] - 64] > 47 && field[i][decks[0] - 64] < 58) {
                test++;
            }
        }
        if (test == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }
}

void createShip(char** field, char* decks, char rang) {                            // Функция установки корабля на поле
    if (decks[1] == decks[4]) {
        for (int j = decks[0] - 64 - 1; j <= decks[3] - 64 + 1; j++) {
            if (j == decks[0] - 64 - 1 || j == decks[3] - 64 + 1) {
                if (j != 0 && j != 11) {
                    field[decks[1] - 47][j] = ' ';
                }
            }
            else {
                field[decks[1] - 47][j] = rang;
            }
            if (decks[1] - 47 - 1 > 0) {
                if (j != 0 && j != 11) {
                    field[decks[1] - 47 - 1][j] = ' ';
                }
            }
            if (decks[1] - 47 + 1 < 11) {
                if (j != 0 && j != 11) {
                    field[decks[1] - 47 + 1][j] = ' ';
                } 
            }
        }
    }
    else if (decks[0] == decks[3]) {
        for (int i = decks[1] - 47 - 1; i <= decks[4] - 47 + 1; i++) {
            if (i == decks[1] - 47 - 1 || i == decks[4] - 47 + 1) {
                if (i != 0 && i != 11) {
                    field[i][decks[0] - 64] = ' ';
                } 
            }
            else {
                field[i][decks[0] - 64] = rang;
            }
            if (decks[0] - 64 - 1 > 0) {
                if (i != 0 && i != 11) {
                    field[i][decks[0] - 64 - 1] = ' ';
                }
            }
            if (decks[0] - 64 + 1 < 11) {
                if (i != 0 && i != 11) {
                    field[i][decks[0] - 64 + 1] = ' ';
                }
            }
        }
    }
}

void deathShip(char** field, char* decks) {
    if (decks[1] == decks[4]) {
        for (int j = decks[0] - 64 - 1; j <= decks[3] - 64 + 1; j++) {
            if (j == decks[0] - 64 - 1 || j == decks[3] - 64 + 1) {
                if (j != 0 && j != 11) {
                    field[decks[1] - 47][j] = '*';
                }
            }
            else {
                field[decks[1] - 47][j] = 'X';
            }
            if (decks[1] - 47 - 1 > 0) {
                if (j != 0 && j != 11) {
                    field[decks[1] - 47 - 1][j] = '*';
                }
            }
            if (decks[1] - 47 + 1 < 11) {
                if (j != 0 && j != 11) {
                    field[decks[1] - 47 + 1][j] = '*';
                }
            }
        }
    }
    else if (decks[0] == decks[3]) {
        for (int i = decks[1] - 47 - 1; i <= decks[4] - 47 + 1; i++) {
            if (i == decks[1] - 47 - 1 || i == decks[4] - 47 + 1) {
                if (i != 0 && i != 11) {
                    field[i][decks[0] - 64] = '*';
                }
            }
            else {
                field[i][decks[0] - 64] = 'X';
            }
            if (decks[0] - 64 - 1 > 0) {
                if (i != 0 && i != 11) {
                    field[i][decks[0] - 64 - 1] = '*';
                }
            }
            if (decks[0] - 64 + 1 < 11) {
                if (i != 0 && i != 11) {
                    field[i][decks[0] - 64 + 1] = '*';
                }
            }
        }
    }
}

void printBattleField(char** enemy, char** my, int size, HANDLE console) {          //  Функиця выводит на экран два игровых поля в горизонтальной виде
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    cout << " Поле компьютера";
    cout << "\t";
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    cout << " Поле игрока" << endl;
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (enemy[i][j] == 'X') {
                SetConsoleTextAttribute(console, FOREGROUND_RED);
                cout << " " << enemy[i][j];
                SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            }
            else if (enemy[i][j] == '#') {
                SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << " " << enemy[i][j];
                SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            }
            else if (enemy[i][j] == '*') {
                SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
                cout << " " << enemy[i][j];
                SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            }
            else if (j == 0 || i == 0) {
                SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << " " << enemy[i][j];
                SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            }
            else {
                cout << " " << enemy[i][j];
            }
        }
        cout << "\t";
        for (int j = 0; j < size; j++) {
            if (my[i][j] == 'X') {
                SetConsoleTextAttribute(console, FOREGROUND_RED);
                cout << " " << my[i][j];
                SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            }
            else if (/*my[i][j] == '#'*/ my[i][j] > 47 && my[i][j] < 58 && j != 0) {
                SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << " " << /*my[i][j]*/ '#';
                SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            }
            else if (my[i][j] == '*') {
                SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
                cout << " " << my[i][j];
                SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            }
            else if (j == 0 || i == 0) {
                SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << " " << enemy[i][j];
                SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            }
            else {
                cout << " " << my[i][j];
            }
        }
        cout << endl;
    }
}

void printMyBattleField(char** enemy, char** my, int size) {          //  Функиця выводит на экран два игровых поля в горизонтальной виде
    cout << " Ваше поле" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (my[i][j] > 47 && my[i][j] < 58 && j != 0) {
                cout << " " << '#';
            }
            else {
                cout << " " << my[i][j];
            }
        }
        cout << endl;
    }
}

char** createField(int size) {          // Функция создает одно пустое игровое поле размером size x size
    char** field = new char* [size];    // Создаем поле 
    for (int i = 0; i < size; i++) {
        field[i] = new char[size];
    }
    field[0][0] = ' ';
    for (int j = 1; j < size; j++) {    // Создаем строку с буквами
        field[0][j] = 64 + j;
    }
    for (int j = 1; j < size; j++) {    // Создаем строку с цифрами
        field[j][0] = 47 + j;
    }
    for (int i = 1; i < size; i++) {        // Заполняем остальные поля точками
        for (int j = 1; j < size; j++) {
            field[i][j] = '.';
        }
    }
    return field;
}

//int automaticFillField(char** efield, char** mfield, int size, bool* shipsFullPtr) {  //  Первый вариант автоматической расстановки кораблей, теперь не использую, использую automaticFF
//    int i = 0; int timer = 25;
//    char* decks = new char[6];
//    bool fullShips = false;
//    if (!*shipsFullPtr) {
//        while (!fullShips) {
//            system("cls");
//            cout << " Морской бой!" << endl;
//            cout << " -------------------------------------------" << endl;
//            printBattleField(efield, mfield, size);
//            cout << endl;
//            /*cout << "Противник уже расставил корабли, дело за тобой!" << endl;
//            cout << "Используй координатную сетку для указания места установки корабля." << endl;
//            cout << "Чтобы поставить четырех палубный корабль укажи первую и последнюю клетку через знак '-'." << endl;
//            cout << "Например A1-A4, корабли можно ставить только горизонтально или вертикально!" << endl;
//            cout << "Для сброса введи: reset. Для выхода в меню: exit." << endl;*/
//            if (i == 0) {
//                //cout << "Установи четырехпалубник: ";
//                
//                for (int j = 0; j < 6; j++) {
//                    if (j == 0 || j == 3) {
//                        decks[j] = rand() % 10 + 65;
//                    }
//                    else if (j == 2) {
//                        decks[j] = '-';
//                    }
//                    else if (j == 1 || j == 4) {
//                        decks[j] = rand() % 10 + 48;
//                    }
//                    else if (j == 5) {
//                        decks[j] = '\0';
//                    }
//                }
//                Sleep(timer);
//                //cout << endl << decks << endl;
//                //system("pause");
//                // Здесь будем рандомить
//
//                /*if (!strcmp(decks, "reset")) {
//                    return 2;
//                }
//                else if (!strcmp(decks, "exit")) {
//                    return 3;
//                }*/
//                if (!checkShip(decks, 4) && !checkField(mfield, decks)) {
//                    createShip(mfield, decks);
//                    i++;
//                    continue;
//                }
//                else {
//                    continue;
//                }
//            }
//            else if (i == 1 || i == 2) {
//                //cout << "Установи трехпалубник: ";
//                for (int j = 0; j < 6; j++) {
//                    if (j == 0 || j == 3) {
//                        decks[j] = rand() % 10 + 65;
//                    }
//                    else if (j == 2) {
//                        decks[j] = '-';
//                    }
//                    else if (j == 1 || j == 4) {
//                        decks[j] = rand() % 10 + 48;
//                    }
//                    else if (j == 5) {
//                        decks[j] = '\0';
//                    }
//                }
//                Sleep(timer);
//                /*if (!strcmp(decks, "reset")) {
//                    return 2;
//                }
//                else if (!strcmp(decks, "exit")) {
//                    return 3;
//                }*/
//                if (!checkShip(decks, 3) && !checkField(mfield, decks)) {
//                    createShip(mfield, decks);
//                    i++;
//                    continue;
//                }
//                else {
//                    continue;
//                }
//            }
//            else if (i > 2 && i < 6) {
//                //cout << "Установи двупалубник: ";
//                for (int j = 0; j < 6; j++) {
//                    if (j == 0 || j == 3) {
//                        decks[j] = rand() % 10 + 65;
//                    }
//                    else if (j == 2) {
//                        decks[j] = '-';
//                    }
//                    else if (j == 1 || j == 4) {
//                        decks[j] = rand() % 10 + 48;
//                    }
//                    else if (j == 5) {
//                        decks[j] = '\0';
//                    }
//                }
//                Sleep(timer);
//                /*if (!strcmp(decks, "reset")) {
//                    return 2;
//                }
//                else if (!strcmp(decks, "exit")) {
//                    return 3;
//                }*/
//                if (!checkShip(decks, 2) && !checkField(mfield, decks)) {
//                    createShip(mfield, decks);
//                    i++;
//                    continue;
//                }
//                else {
//                    continue;
//                }
//            }
//            else if (i > 5 && i < 10) {
//                //cout << "Установи однопалубник: ";
//
//                for (int j = 0; j < 6; j++) {
//                    if (j == 0) {
//                        decks[j] = rand() % 10 + 65;
//                        decks[3] = decks[j];
//                    }
//                    else if (j == 2) {
//                        decks[j] = '-';
//                    }
//                    else if (j == 1) {
//                        decks[j] = rand() % 10 + 48;
//                        decks[4] = decks[j];
//                    }
//                    else if (j == 5) {
//                        decks[j] = '\0';
//                    }
//                }
//                Sleep(timer);
//                /*if (!strcmp(decks, "reset")) {
//                    return 2;
//                }
//                else if (!strcmp(decks, "exit")) {
//                    return 3;
//                }*/
//                if (!checkShip(decks, 1) && !checkField(mfield, decks)) {
//                    createShip(mfield, decks);
//                    i++;
//                    continue;
//                }
//                else {
//                    continue;
//                }
//            }
//            if (i == 10) {
//                fullShips = true;
//                *shipsFullPtr = true;
//            }
//        }
//        int check = 0;
//        cout << endl << "Корабли расставлены!" << endl;
//        cout << "1 - Начать сражение" << endl;
//        cout << "2 - Переставить корабли" << endl;
//        cout << "3 - Выйти в меню" << endl;
//        cin >> check;
//        if (check == 1) {
//            return 1;
//        }
//        else if (check == 2) {
//            return 2;
//        }
//        else if (check == 3) {
//            return 3;
//        }
//        else {
//            return 0;
//        }
//    }
//    else {
//        system("cls");
//        cout << " Морской бой!" << endl;
//        cout << " -------------------------------------------" << endl;
//        printBattleField(efield, mfield, size);
//        cout << endl;
//        /*cout << "Противник уже расставил корабли, дело за тобой!" << endl;
//        cout << "Используй координатную сетку для указания места установки корабля." << endl;
//        cout << "Чтобы поставить четырех палубный корабль укажи первую и последнюю клетку через знак '-'." << endl;
//        cout << "Например A1-A4, корабли можно ставить только горизонтально или вертикально!" << endl;
//        cout << "Для сброса введи: reset. Для выхода в меню: exit." << endl;*/
//        int check = 0;
//        cout << endl << "Корабли расставлены!" << endl;
//        cout << "1 - Начать сражение" << endl;
//        cout << "2 - Переставить корабли" << endl;
//        cout << "3 - Выйти в меню" << endl;
//        cin >> check;
//        if (check == 1) {
//            return 1;
//        }
//        else if (check == 2) {
//            return 2;
//        }
//        else if (check == 3) {
//            return 3;
//        }
//        else {
//            return 0;
//        }
//    }
//}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
