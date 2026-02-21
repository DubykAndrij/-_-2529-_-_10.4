#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

void CreateTXT(char* fname);
void PrintTXT(char* fname);
string FindShortestWordInLine(string line);
int ProcessAndCopy(char* fname, char* gname);
void AppendCountToFile(char* gname, int count);

void CreateTXT(char* fname) {
    ofstream fout(fname);
    if (!fout) {
        cerr << "Помилка відкриття файлу для запису!" << endl;
        return;
    }

    string s;
    char ch;
    do {
        cout << "Введіть рядок (слова через пробіл): ";
        cin.get();
        cin.sync();
        getline(cin, s);
        fout << s << endl;
        cout << "Продовжити введення? (y/n): "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fout.close();
}

void PrintTXT(char* fname) {
    ifstream fin(fname);
    if (!fin) {
        cerr << "Файл не знайдено!" << endl;
        return;
    }
    string s;
    cout << "\n--- Вміст файлу " << fname << " ---" << endl;
    while (getline(fin, s)) {
        cout << s << endl;
    }
    cout << "--------------------------" << endl;
    fin.close();
}

string FindShortestWordInLine(string line) {
    stringstream ss(line);
    string word, shortest;

    if (!(ss >> shortest)) return "";

    while (ss >> word) {
        if (word.length() < shortest.length()) {
            shortest = word;
        }
    }
    return shortest;
}

int ProcessAndCopy(char* fname, char* gname) {
    ifstream fin(fname);
    ofstream fout(gname);

    string line, word;
    int totalWords = 0;

    while (getline(fin, line)) {
        stringstream ss(line);
        while (ss >> word) {
            totalWords++;
        }

        string shortest = FindShortestWordInLine(line);
        if (!shortest.empty()) {
            fout << shortest << endl;
        }
    }

    fin.close();
    fout.close();
    return totalWords;
}

void AppendCountToFile(char* gname, int count) {
    ofstream fout(gname, ios::app);
    fout << count;
    fout.close();
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Ukrainian");

    char fname[100], gname[100];
    int choice;

    cout << "Введіть ім'я вхідного файлу: "; cin >> fname;
    cout << "Введіть ім'я вихідного файлу: "; cin >> gname;

    do {
        cout << "\n--- МЕНЮ ---" << endl;
        cout << "1. Створити/перезаписати вхідний файл" << endl;
        cout << "2. Обробити дані (знайти найкоротші слова)" << endl;
        cout << "3. Переглянути вхідний файл" << endl;
        cout << "4. Переглянути вихідний файл" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";

        if (!(cin >> choice)) {
            cout << "Помилка! Введіть число." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            CreateTXT(fname);
            break;
        case 2: {
            int count = ProcessAndCopy(fname, gname);
            AppendCountToFile(gname, count);
            cout << "Обробка завершена. Кількість слів: " << count << endl;
            break;
        }
        case 3:
            PrintTXT(fname);
            break;
        case 4:
            PrintTXT(gname);
            break;
        case 0:
            cout << "Завершення роботи." << endl;
            break;
        default:
            cout << "Невірний пункт меню!" << endl;
        }
    } while (choice != 0);

    return 0;
}