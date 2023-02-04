#include "Header.h"

#define _CRT_SECURE_NO_WARNINGS


void XY(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, { x, y });
}
void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);


    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;

    SetConsoleCursorInfo(hStdOut, &structCursorInfo);

}
void SetColor(int activeMenu, string* menu, int x, int y)
{
    for (int i = 0; i < 7; i++)
    {
        if (i == activeMenu) 	SetConsoleTextAttribute(hStdOut, !FOREGROUND_BLUE | !FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        else 	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);

        XY(x, y++);
        cout << menu[i] << endl;
    }
}
void SetDelMenuColor(int activeMenu, string* menu, int sizeMenu, int x, int y) {
    for (int i = 0; i < sizeMenu; i++)
    {
        if (i == activeMenu) 	SetConsoleTextAttribute(hStdOut, !FOREGROUND_BLUE | !FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        else 	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);

        XY(x, y++);
        cout << menu[i] << endl;
    }
}
void EnterMenu(string menu[], int activeMenu, int x, int y)
{
    system("CLS");
    XY(x, y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    _getch();
    system("CLS");
}
//////////////////////////////////////////////////////////////////////

int ToDoList::amount{ 0 };
// тут будут прописаны поля методы классов. 
void ToDoList::setName()
{
    violet
    cin.ignore();
    cout << endl;
	cout << "Enter name of the case: ";
    green;
	getline(cin, name);
}
void ToDoList::setPriority()
{
    violet
	cout << "Enter the priority (0-10): ";
    green;
	cin >> priority;

}
void ToDoList::setDescription()
{
    violet
	cout << "Enter the description: ";
	cin.ignore();
    green;
	getline(cin, description);
}
void ToDoList::setDeadLine()
{
    green;
	cin >> DeadLine;
    violet
}
void ToDoList::setDaysBeforeDeadline() 
{
    green;
	this->DaysBeforeDeadline = Date::AmountDays(DeadLine, _date);
    violet
}

void ToDoList::setCase()
{
	amount++;
	this->id = amount;
	white;
	cout << "========================================" << endl;
	setName();
	setPriority();
	setDescription();
	if (_date.getDay() < 10)
	{
		violet;
		cout << "Added:";
		green;
		cout << " 0" << _date;
		violet;
	}
	else
	{
		violet;
		cout << "Added: ";
		green;
		cout << _date;
		violet;
	}
	while (true)
	{
		setDeadLine();
		setDaysBeforeDeadline();
		try
		{
			if (getDeadLine() < 0) 
			{
				throw getDeadLine();
			}
			else 
			{
				break;
			}
		}
		catch (int deadline)
		{
			int x = 50, y = 13;
			system("CLS");
			red;
			XY(x, y);
			cout << "The new case can\'t be expired";
			_getch();
			system("CLS");
			green;
			cout << "Try again: " << endl;
		}
	}
	white;
	cout << "========================================" << endl;

}

void const ToDoList::get()
{
	white;
	cout << "===============================" << endl;
	violet;
	cout << "Name: ";
	green;
	cout << name << endl;
	violet;
	cout << "Priority: ";
	green;
	cout << priority << endl;
	violet;
	cout << "Description: ";
	green;
	cout << description << endl;
	if (_date.getDay() < 10)
	{
		violet;
		cout << "Added:";
		green;
		cout << " 0" << _date;
		violet;
	}
	else
	{
		violet;
		cout << "Added: ";
		green;
		cout << _date;
		violet;
	}
	if (DeadLine.getDay() < 10)
	{
		violet;
		cout << "DeadLine:";
		green;
		cout << " 0" << DeadLine;
		violet;
	}
	else
	{
		violet;
		cout << "DeadLine: ";
		green;
		cout << DeadLine;
		violet;
	}
	violet;
	cout << "Days before deadline: ";
	green;
	cout << DaysBeforeDeadline << endl;
	white;
	cout << "===============================" << endl;
}
void const ToDoList::getNameCase(int i) 
{
	white;
	cout << "============== Case N" << i;
	cout << " =================" << endl;
	violet;
	cout << "Id: ";
	green;
	cout << &name;
	violet;
	cout << " Name: ";
	green;
	cout << name << endl;
	white;
	cout << "========================================" << endl;
}

string const  ToDoList::getNameForSearch()
{
	return name;
}
int const ToDoList::getPriority()
{
	return priority;
}
string const ToDoList::getDescription()
{
	return description;
}
int const ToDoList::getDeadLine() 
{
	return DaysBeforeDeadline;
}

/*
	4) поиск : 
	* Названию
	* Приориетету
	* Описанию
	* Дате
	* Времени исполнения
*/


void Search(vector <ToDoList>& a, string value)// поиск по описанию 
{
	int counter = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i].getDescription() == value)
		{
			a[i].get();
			counter++;
		}
	}
	if (counter == 0)
	{
		red;
		cout << "Nothing" << endl;
	}
}
void Search(vector<ToDoList>& a, ToDoList::Date value)
{
	int counter = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == value)
		{
			a[i].get();
			counter++;
		}
	}
	if (counter == 0)
	{
		red;
		cout << "Nothing" << endl;
	}
}
void Search(vector<ToDoList>& a, int value) // поиск по времени исполнения
{
	int counter = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i].getDeadLine() == value)
		{
			a[i].get();
			counter++;
		}
	}
	if (counter == 0)
	{
		red;
		cout << "Nothing" << endl;
	}
}

/*
	5) Отображение списка дел:
	* На день
	* На неделю
	* На месяц
	просто через условие прогоняем дней до дедлайна.
*/
// сортировка по дате через дружественную функцию реализлвана в классе.
void Sort(vector <ToDoList>& old)
{
	for (int i = 0; i < old.size(); i++) 
	{
		for (int j = 0; j < old.size(); j++) 
		{
			if (old[i].getPriority() < old[j].getPriority()) 
			{
				swap(old[i], old[j]);
			}
		}
	}
}
void Sort(vector <ToDoList>& old, int count)
{
	for (int i = 0; i < old.size(); i++)
	{
		for (int j = 0; j < old.size(); j++)
		{
			if (old[i].getDeadLine() < old[j].getDeadLine())
			{
				swap(old[i], old[j]);
			}
		}
	}
}
