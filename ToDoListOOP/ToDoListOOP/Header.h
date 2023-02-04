#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <vector>
#include <algorithm>



#define ESC 27
#define ENTER 13
#define SPACE 32

#define UP 72
#define DOWN 80 
#define LEFT 75
#define RIGHT 77


#define green SetConsoleTextAttribute(hStdOut, !FOREGROUND_BLUE | !FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_GREEN); 
#define violet SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
#define red SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_BLUE);
#define white SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

// тут будут прописан класс; 

/*

string searchMenu[6] = { "Name", "Priority" , "Description", "Date", "DeadLine", "Exit to main menu"};
	int actSearch = 0;
	string* searchMenuptr;
	searchMenuptr = searchMenu;
	char searchch;


Типы данных

1) Название
2) Приоритет
3) Описание
4) Дата
5) Время исполнения

*/

void XY(short x, short y);
void ConsoleCursorVisible(bool show, short size);
void SetColor(int activeMenu, string* menu, int x, int y);
void SetDelMenuColor(int activeMenu, string* menu, int sizeMenu, int x, int y);
void EnterMenu(string menu[], int activeMenu, int x, int y);

_declspec(selectany) HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

class ToDoList
{
public:
	
	class Date
	{
	private:
		int day;
		int month;
		int year;
	public:
		Date()
		{
			time_t now = time(0);
			tm* ltm = localtime(&now);

			this->day = ltm->tm_mday;
			this->month = 1 + ltm->tm_mon;
			this->year = 1900 + ltm->tm_year;
		}
		Date(int day, int month, int year) : Date()
		{
			this->day = day;
			this->month = month;
			this->year = year;
		}
		friend ostream& operator <<(ostream& out, const Date& d)
		{
			if (d.day == 0)
			{
				out << "__.__ .____" << endl;
			}
			else
			{
				out << d.day << "." << d.month << "." << d.year << endl;
				return out;
			}
		}
		friend istream& operator >>(istream& in, Date& d)
		{
			violet;
			cout << "\nEnter Deadline:" << endl;
			cout << "Enter day: ";
			green;
			in >> d.day;
			violet
			cout << "Enter month: ";
			green;
			in >> d.month;
			violet;
			cout << "Enter year: ";
			green;
			in >> d.year;
			violet;
			return in;
		}
		friend bool operator==(const Date& a, const Date& b)
		{
			if (a.day == b.day and a.month == b.month and a.year == b.year) 
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		friend bool operator < (const Date& a, const Date& b) 
		{
			if (a.day < b.day or a.month < b.month or a.year < b.year)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		static int AmountDays(Date& start, Date& end)
		{
			int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 30 };
			int stDays{ 0 }, endDays{ 0 };

			for (int i = 1; i < start.month; i++)
			{
				stDays += daysInMonth[i];
			}
			stDays += start.day + (start.year - 2000) * 365;
			for (int i = 1; i < end.month; i++)
			{
				endDays += daysInMonth[i];
			}
			endDays += end.day + (end.year - 2000) * 365;

			return  stDays - endDays;
		}
		int const getDay()
		{
			return day;
		}

		~Date() {}
	};
	
	explicit ToDoList()
	{
		this->name = "NON";
		this->priority = 0;
		this->_date;
		this->DeadLine;
		this->description = "NON";
	}
	void setName();
	void setPriority();
	void setDescription();
	void setDeadLine();
	void setDaysBeforeDeadline();

	void setCase();
	void const get();
	string const getNameForSearch();
	int const getPriority();
	string const getDescription();
	void const getNameCase(int i);
	int const getDeadLine();

	friend bool operator==(const ToDoList& a, string b) // поиск по имени кейса
	{
		return a.name == b;
	}
	friend bool operator==(const ToDoList& a, int b) // поиск по приотритету
	{
		return a.priority == b;
	}
	friend bool operator==(const ToDoList& a, const Date& b) // тут применил 
	{
		if (a._date == b) return true;
		else return false;
	}
	/*friend bool operator<(const ToDoList& a, const ToDoList& b)
	{
		return a.priority < b.priority;
	}
	*/
	friend bool operator<(const ToDoList& a, const ToDoList& b) 
	{
		return a._date < b._date;
	}
	/*
	friend bool operator<(const ToDoList& a, const ToDoList& b)
	{
		return a.DaysBeforeDeadline < b.DaysBeforeDeadline;
	}*/

private:
	static int amount;
	int id;
	string name;
	int priority;
	Date _date;
	Date DeadLine;
	int DaysBeforeDeadline;
	string description;

};

// два других поиска перегружены оператором сравнения.

void Search(vector <ToDoList>& a, string value); // поиск по описанию 
void Search(vector<ToDoList>& a, ToDoList::Date value); // поиск по дате
void Search(vector<ToDoList>& a, int value);

void Sort(vector<ToDoList>& old);
void Sort(vector<ToDoList>& old, int count);