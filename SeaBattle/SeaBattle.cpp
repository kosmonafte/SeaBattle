// SeaBattle.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
using namespace std;
char** createField(int size);
void printBattleField(char** enemy, char** my, int size);
void createShip(char** array, char* str);
int checkShip(char* decks, int size);
int checkField(char** field, char* decks);
int fillField(char** efield, char** mfield, int size, bool* shipsFullPtr);
int mainMenu(bool* shipsFullPtr);
int automaticFillField(char** efield, char** mfield, int size, bool* shipsFullPtr);
int automaticFF(char** field, bool* shipsFullPtr, int size);

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    int size = 11;
    char** enemyField = createField(size);
    char** myField = createField(size);
    bool menu = true; // Окно стартового меню
    bool arrangeShips = false; // Окно расстановки кораблей
    bool autoArrangeShips = false; // Окно автоматической расстановки кораблей
    bool battle = false; // Окно сражения
    bool shipsFull = false; bool* shipsFullPtr = &shipsFull; // Расставлены корабли или нет
    bool enemyShipsFull = false; bool* enemySshipsFullPtr = &shipsFull;
    while (true) {
        if (menu) { //  Окно меню
            int checkMenu = 0;
            checkMenu = mainMenu(shipsFullPtr);
            if (checkMenu == 1) {
                if (shipsFull) {
                    menu = false;
                    arrangeShips = false;
                    autoArrangeShips = false;
                    battle = true;
                    continue;
                }
                else {
                    continue;
                } 
            }
            else if (checkMenu == 2) {
                automaticFF(myField, shipsFullPtr, size);
                continue;
            }
            else if (checkMenu == 3) {
                menu = false;
                arrangeShips = true;
                autoArrangeShips = false;
                battle = false;
                continue;
            }
            else {
                continue;
            }
        }
        if (arrangeShips) { // Окно расстановки кораблей
            int check = fillField(enemyField, myField, size, shipsFullPtr);
            if (check == 1) {
                arrangeShips = false;
                battle = true;
            }
            else if (check == 2) {
                delete[]myField;
                myField = createField(size);
                shipsFull = false;
                continue;
            }
            else if (check == 3) {
                if (!shipsFull) {
                    delete[]myField;
                    myField = createField(size);
                }
                menu = true;
                arrangeShips = false;
                continue;
            }
        }
        //if (autoArrangeShips) { // Окно автоматической расстановки кораблей
        //    int check = automaticFillField(enemyField, myField, size, shipsFullPtr);
        //    if (check == 1) {
        //        autoArrangeShips = false;
        //        battle = true;
        //    }
        //    else if (check == 2) {
        //        delete[]myField;
        //        myField = createField(size);
        //        shipsFull = false;
        //        continue;
        //    }
        //    else if (check == 3) {
        //        if (!shipsFull) {
        //            delete[]myField;
        //            myField = createField(size);
        //        }
        //        menu = true;
        //        arrangeShips = false;
        //        continue;
        //    }
        //}
        if (battle) { // Окно сражения  
            automaticFF(enemyField, enemySshipsFullPtr, size);
            char* str = new char[3];
            char** tempField = createField(size);
            while (true) {
                system("cls");
                printBattleField(tempField, myField, size);
                cout << "Выстрел: ";
                cin >> str;
                if (enemyField[str[1] - 47][str[0] - 64] == '#') {
                    tempField[str[1] - 47][str[0] - 64] = 'X';
                }
                else {
                    tempField[str[1] - 47][str[0] - 64] = ' ';
                }
            }
        }
    }
}

int automaticFF(char** field, bool* shipsFullPtr, int size) {
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
                createShip(field, decks);
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
                createShip(field, decks);
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
                createShip(field, decks);
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
                createShip(field, decks);
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

int automaticFillField(char** efield, char** mfield, int size, bool* shipsFullPtr) {
    int i = 0; int timer = 25;
    char* decks = new char[6];
    bool fullShips = false;
    if (!*shipsFullPtr) {
        while (!fullShips) {
            system("cls");
            cout << " Морской бой!" << endl;
            cout << " -------------------------------------------" << endl;
            printBattleField(efield, mfield, size);
            cout << endl;
            /*cout << "Противник уже расставил корабли, дело за тобой!" << endl;
            cout << "Используй координатную сетку для указания места установки корабля." << endl;
            cout << "Чтобы поставить четырех палубный корабль укажи первую и последнюю клетку через знак '-'." << endl;
            cout << "Например A1-A4, корабли можно ставить только горизонтально или вертикально!" << endl;
            cout << "Для сброса введи: reset. Для выхода в меню: exit." << endl;*/
            if (i == 0) {
                //cout << "Установи четырехпалубник: ";
                
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
                Sleep(timer);
                //cout << endl << decks << endl;
                //system("pause");
                // Здесь будем рандомить

                /*if (!strcmp(decks, "reset")) {
                    return 2;
                }
                else if (!strcmp(decks, "exit")) {
                    return 3;
                }*/
                if (!checkShip(decks, 4) && !checkField(mfield, decks)) {
                    createShip(mfield, decks);
                    i++;
                    continue;
                }
                else {
                    continue;
                }
            }
            else if (i == 1 || i == 2) {
                //cout << "Установи трехпалубник: ";
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
                Sleep(timer);
                /*if (!strcmp(decks, "reset")) {
                    return 2;
                }
                else if (!strcmp(decks, "exit")) {
                    return 3;
                }*/
                if (!checkShip(decks, 3) && !checkField(mfield, decks)) {
                    createShip(mfield, decks);
                    i++;
                    continue;
                }
                else {
                    continue;
                }
            }
            else if (i > 2 && i < 6) {
                //cout << "Установи двупалубник: ";
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
                Sleep(timer);
                /*if (!strcmp(decks, "reset")) {
                    return 2;
                }
                else if (!strcmp(decks, "exit")) {
                    return 3;
                }*/
                if (!checkShip(decks, 2) && !checkField(mfield, decks)) {
                    createShip(mfield, decks);
                    i++;
                    continue;
                }
                else {
                    continue;
                }
            }
            else if (i > 5 && i < 10) {
                //cout << "Установи однопалубник: ";

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
                Sleep(timer);
                /*if (!strcmp(decks, "reset")) {
                    return 2;
                }
                else if (!strcmp(decks, "exit")) {
                    return 3;
                }*/
                if (!checkShip(decks, 1) && !checkField(mfield, decks)) {
                    createShip(mfield, decks);
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
        else {
            return 0;
        }
    }
    else {
        system("cls");
        cout << " Морской бой!" << endl;
        cout << " -------------------------------------------" << endl;
        printBattleField(efield, mfield, size);
        cout << endl;
        /*cout << "Противник уже расставил корабли, дело за тобой!" << endl;
        cout << "Используй координатную сетку для указания места установки корабля." << endl;
        cout << "Чтобы поставить четырех палубный корабль укажи первую и последнюю клетку через знак '-'." << endl;
        cout << "Например A1-A4, корабли можно ставить только горизонтально или вертикально!" << endl;
        cout << "Для сброса введи: reset. Для выхода в меню: exit." << endl;*/
        int check = 0;
        cout << endl << "Корабли расставлены!" << endl;
        cout << "1 - Начать сражение" << endl;
        cout << "2 - Переставить корабли" << endl;
        cout << "3 - Выйти в меню" << endl;
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
        else {
            return 0;
        }
    }
}

int mainMenu(bool* shipsFullPtr) {
    system("cls");
    int start = 0;
    cout << "Морской бой!" << endl;
    cout << "===============================================================================" << endl;
    cout << " ####   #####   ####      #####    ####   ######  ######  ##      #####     ###" << endl;
    cout << "##      ##     ##  ##     ##  ##  ##  ##    ##      ##    ##      ##        ###" << endl;
    cout << " ####   ####   ######     #####   ######    ##      ##    ##      ####      ###" << endl;
    cout << "    ##  ##     ##  ##     ##  ##  ##  ##    ##      ##    ##      ##           " << endl;
    cout << " ####   #####  ##  ##     #####   ##  ##    ##      ##    ######  #####     ###" << endl;
    cout << "===============================================================================" << endl;
    cout << endl;
    cout << endl;
    cout << "1 - Начать сражение";
    (*shipsFullPtr) ? cout << " (Корабли расставлены!)" << endl : cout << " (Необходимо расставить корабли!)" << endl;
    cout << "2 - Автоматическая расстановка кораблей" << endl;
    cout << "3 - Расставить корабли в ручную" << endl;
    cout << endl;
    cin >> start;
    if (start == 1) {
        return 1;
    }
    else if (start == 2) {
        return 2;
    }
    else if (start == 3) {
        return 3;
    }
    else {
        return 0;
    }
}

int fillField(char** efield, char** mfield, int size, bool* shipsFullPtr) {  // Функиця расстановки кораблей
    int i = 0;
    char* decks = new char[6];
    bool fullShips = false;
    if (!*shipsFullPtr) {
        while (!fullShips) {
            system("cls");
            cout << " Морской бой!" << endl;
            cout << " -------------------------------------------" << endl;
            printBattleField(efield, mfield, size);
            cout << endl;
            cout << "Противник уже расставил корабли, дело за тобой!" << endl;
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
                    createShip(mfield, decks);
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
                    createShip(mfield, decks);
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
                    createShip(mfield, decks);
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
                    createShip(mfield, decks);
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
        else {
            return 0;
        }
    }
    else {
        system("cls");
        cout << " Морской бой!" << endl;
        cout << " -------------------------------------------" << endl;
        printBattleField(efield, mfield, size);
        cout << endl;
        /*cout << "Противник уже расставил корабли, дело за тобой!" << endl;
        cout << "Используй координатную сетку для указания места установки корабля." << endl;
        cout << "Чтобы поставить четырех палубный корабль укажи первую и последнюю клетку через знак '-'." << endl;
        cout << "Например A1-A4, корабли можно ставить только горизонтально или вертикально!" << endl;
        cout << "Для сброса введи: reset. Для выхода в меню: exit." << endl;*/
        int check = 0;
        cout << endl << "Корабли расставлены!" << endl;
        cout << "1 - Начать сражение" << endl;
        cout << "2 - Переставить корабли" << endl;
        cout << "3 - Выйти в меню" << endl;
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
            if (field[decks[1] - 47][j] == ' ' || field[decks[1] - 47][j] == '#') {
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
            if (field[i][decks[0] - 64] == ' ' || field[i][decks[0] - 64] == '#') {
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

void createShip(char** field, char* decks) {                            // Функция усиановки корабля на поле
    if (decks[1] == decks[4]) {
        for (int j = decks[0] - 64 - 1; j <= decks[3] - 64 + 1; j++) {
            if (j == decks[0] - 64 - 1 || j == decks[3] - 64 + 1) {
                if (j != 0 && j != 11) {
                    field[decks[1] - 47][j] = ' ';
                }
            }
            else {
                field[decks[1] - 47][j] = '#';
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
                field[i][decks[0] - 64] = '#';
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

void printBattleField(char** enemy, char** my, int size) {          //  Функиця выводит на экран два игровых поля в горизонтальной виде
    cout << " Поле противника" << "\t" << " Ваше поле" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << " " << enemy[i][j];
        }
        cout << "\t";
        for (int j = 0; j < size; j++) {
            cout << " " << my[i][j];
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

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
