// SeaBattle.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
char** createField(int size);
void printBattleField(char** enemy, char** my, int size);
void createShip(char** array, char* str);
int checkShip(char* decks, int size);
int main()
{
    setlocale(LC_ALL, "RUS");
    int size = 11, i = 0;
    char* decks = new char[6];
    char** enemyField = createField(size);
    char** myField = createField(size);
    while (true) {
        system("cls");
        cout << " Морской бой!" << endl;
        cout << " -------------------------------------------" << endl;
        printBattleField(enemyField, myField, size);
        cout << endl;
        cout << "Противник уже расставил корабли, дело за тобой!" << endl;
        cout << "Используй координатную сетку для указания места установки корабля." << endl;
        cout << "Чтобы поставить четырех палубный корабль укажи первую и последнюю клетку через знак '-'." << endl;
        cout << "Например A1-D1, корабли можно ставить только горизонтально или вертикально!" << endl;
        if (i == 0) {
            cout << "Установи четырехпалубник: ";
            cin >> decks;
            if (!checkShip(decks, 4)) {
                createShip(myField, decks);
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
            if (!checkShip(decks, 3)) {
                createShip(myField, decks);
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
            if (!checkShip(decks, 2)) {
                createShip(myField, decks);
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
            if (!checkShip(decks, 1)) {
                createShip(myField, decks);
                i++;
                continue;
            }
            else {
                continue;
            }
        }
    }
}
int checkShip(char* decks, int size) {
    if (decks[0] == decks[3] || decks[1] == decks[4]) {
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
void createShip(char** field, char* decks) {
    if (decks[1] == decks[4]) {
        for (int j = decks[0] - 64; j <= decks[3] - 64; j++) {
            field[decks[1] - 47][j] = '#';
        }
    }
    else if (decks[0] == decks[3]) {
        for (int i = decks[1] - 47; i <= decks[4] - 47; i++) {
            field[i][decks[0] - 64] = '#';
        }
    }
}
void printBattleField(char** enemy, char** my, int size) {
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

char** createField(int size) {
    char** field = new char* [size];
    for (int i = 0; i < size; i++) {
        field[i] = new char[size];
    }
    field[0][0] = ' ';
    for (int j = 1; j < size; j++) {
        field[0][j] = 64 + j;
    }
    for (int j = 1; j < size; j++) {
        field[j][0] = 47 + j;
    }
    for (int i = 1; i < size; i++) {
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
