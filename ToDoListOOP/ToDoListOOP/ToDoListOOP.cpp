#include "Header.h"
#define _CRT_SECURE_NO_WARNINGS



/*

Список функций:

1) Добавить дело                                +
2) Удалить дело                                 +
3) Редактировать уже существующее дело          +
4) Поиск дела по:                               +
	* Названию                                  +
	* Приориетету                               +
	* Описанию                                  +       
	* Дате                                      +
	* Времени исполнения                        +
5) Отображение списка дел:                      +
	* На день                                   +
	* На неделю                                 +
	* На месяц                                  +
6) Сортировка:
	* По приоритету
	* По дате
	* По времени исполнения

*/

void main()
{

    /////////////////////// Консольные настройки ///////////////////////////////////////////
    SetConsoleTitle(L"Nazarko Danil To Do List OOP");
    HWND hWindowConsole = GetConsoleWindow();
    RECT r;
    GetWindowRect(hWindowConsole, &r); 
    MoveWindow(hWindowConsole, r.left, r.top, 1100, 500, TRUE);
    /////////////////////////////////////////////////////////////////////////////////////////

    system("CLS");
    setlocale(0, "");
    ConsoleCursorVisible(false, 100);

    string menu[7] = { "Add case",
                       "Delete case",
                       "Change case",
                       "Searching case",
                       "Case printer",
                       "Sort cases",
                       "Exit" };
    int sizeSubMenu{ 0 }; /// размеры подменю меняются при входе в подменю
    int activeMenu = 0;
    string* menuptr;
    menuptr = menu;
    char ch;

    string DelMenu[3] = { "Delete all cases", "Delete one case", "Exit to main menu" };

    int activesubMenu = 0;
    string* subMenuptr;
    subMenuptr = DelMenu;
    char subch;
    int ex = 1; // сброс всех подменю. 


    string searchMenu[6] = { "Name", "Priority" , "Description", "Date", "DeadLine", "Exit to main menu"};
    int actSearch = 0;
    string* searchMenuptr;
    searchMenuptr = searchMenu;
    char searchch;


    string printMenu[5] = {"Print all", "Print for the day", "Print for the week", "Print for the month" , "Exit" };
    int actPrint = 0;
    string* printMenuptr;
    printMenuptr = printMenu;
    char printch;


    string sortMenu[4] = { "Sort by priority", "Sort by date", "Sort by deadline", "Exit" };
    int actSort = 0;
    string* sortMenuptr;
    sortMenuptr = sortMenu;
    char sortch;

    /////// search ////////////
    int searchint{0};
    string searchstr = "";
    int counter = 0;
    ////////////////////////////////////////////////////////////////////////////////////////
    vector <ToDoList> cases;
    auto iter = cases.begin();
    auto itere = cases.end();
    ToDoList cas;
    ToDoList::Date searchDate;


    while (true)
    {
        iter = cases.begin(); /// возвращение итератора в начало.
        int x = 50, y = 13;
        XY(x, y);
        SetColor(activeMenu, menuptr, x, y);
        ch = _getch();
        if (ch == -32) ch = _getch(); // Отлавливаем стрелочки
        switch (ch)
        {
        case ESC:
            exit(0);
        case UP:
            if (activeMenu > 0) { activeMenu--; }
            break;
        case DOWN:
            if (activeMenu < 6) { activeMenu++; }
            break;
        case ENTER:
            switch (activeMenu)
            {
                //////////// Add case /////////////////////////////////////////////////////////////////
            case 0:
                system("CLS");
                XY(x - 5, y - 12);
                violet;
                cout << "You enter the  \"" << menu[activeMenu] << "\"\n";
                cas.setCase();
                cases.push_back(cas);
                _getch();
                system("CLS");
                break;
                ////////// Delete case ////////////////////////////////////////////////////////////////
            case 1:
                system("CLS");
                activesubMenu = 0;
                sizeSubMenu = 3;
                ex = 1;
                while (ex)
                {

                    XY(x, y);
                    SetDelMenuColor(activesubMenu, subMenuptr, sizeSubMenu, x, y);
                    char choise;
                    choise = _getch();
                    if (choise == -32) choise = _getch(); 
                    switch (choise)
                    {
                    case ESC:
                        break;
                    case UP:
                        if (activesubMenu > 0) { activesubMenu--; }
                        break;
                    case DOWN:
                        if (activesubMenu < 2) { activesubMenu++; }
                        break;
                    case ENTER:
                        switch (activesubMenu)
                        {
                            /////////// Delete all cases /////////////////////////////////
                        case 0:
                            system("CLS");
                            XY(x - 5, y - 12);
                            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                            cout << "You enter the  \"" << DelMenu[activesubMenu] << "\"\n";
                            
                            if (cases.empty())
                            {
                                red;
                                XY(x - 5, y );
                                cout << "List of cases is empty";
                            }
                            else
                            {
                                cases.clear();
                                red;
                                XY(x - 5, y);
                                cout << "List of cases has been deleted";
                            }
                            _getch();
                            system("CLS");
                            break;
                            ////////////Delete one case/////////////////////////////////////
                        case 1:
                            system("CLS");
                            XY(x - 5, y - 12);
                            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                            cout << "You enter the  \"" << DelMenu[activesubMenu] << "\"\n";

                            if (cases.empty())
                            {
                                red;
                                XY(x, y);
                                cout << "List of cases is empty";
                            }
                            else 
                            {
                                XY(x - 5, y - 10);
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                                cout << "Enter the number of case to delete: " << endl;
                                for (int i = 0; i < cases.size(); i++)
                                {
                                    cases[i].getNameCase(i + 1);
                                }
                                int ch;
                                cout << ">>>>";
                                cin >> ch;
                                try 
                                {
                                    if (0 < ch < cases.size()) 
                                    {
                                        cases.erase(iter + ch - 1);
                                        system("CLS");
                                        red;
                                        XY(x, y);
                                        cout << "the case has been deleted";
                                    }
                                    else 
                                    {
                                        throw ch;
                                    }
                                }
                                catch(int ch)
                                {
                                    red;
                                    XY(x, y);
                                    cout << "The wrong number" << endl;
                                }
                            }

                            _getch();
                            system("CLS");
                            break;
                            /////////////////////////////Выход из подменю в основное меню //////////////////////////
                        case 2:
                            ex = 0;
                            system("CLS");
                            break;
                        }
                    }
                }
                break;
                _getch();
                system("CLS");
                break;

                //////// Change case ////////////////////////////////////////////////////////////////////
            case 2:
                system("CLS");
                XY(x - 5, y - 12);
                violet;
                cout << "You enter the  \"" << menu[activeMenu] << "\"\n";
                if (cases.empty())
                {
                    red;
                    XY(x - 5, y);
                    cout << "List of cases is empty";
                }
                else
                {
                   
                    for (int i = 0; i < cases.size(); i++)
                    {
                        cases[i].getNameCase(i + 1);
                    }
                    int ch;
                    violet;
                    cout << "\nEnter the number of case to change ";
                    white;
                    cout << ">>>>";
                    green;
                    cin >> ch;
                    ch -= 1;
                    try
                    {
                        if (0 < ch < cases.size())
                        {
                            cases[ch].setCase();
                            system("CLS");
                            green;
                            XY(x, y);
                            cout << "The case has been changed" << endl;
                        }
                        else
                        {
                            throw ch;
                        }
                    }
                    catch (int ch)
                    {
                        red;
                        XY(x, y);
                        cout << "The wrong number" << endl;
                    }
                }

                _getch();
                system("CLS");
                break;
                /////// Searching case ////////////////////////////////////////////////////
            case 3:
                system("CLS");
                if (cases.empty())
                {
                    red;
                    XY(x - 5, y);
                    cout << "List of cases is empty";
                }
                else
                {
                    system("CLS");
                    actSearch = 0;
                    sizeSubMenu = 6;
                    ex = 1;
                    while (ex)
                    {

                        XY(x, y);
                        SetDelMenuColor(actSearch, searchMenuptr, sizeSubMenu, x, y);
                        char choise;
                        choise = _getch();
                        if (choise == -32) choise = _getch(); 
                        switch (choise)
                        {
                        case ESC:
                            break;
                        case UP:
                            if (actSearch > 0) { actSearch--; }
                            break;
                        case DOWN:
                            if (actSearch < 5) { actSearch++; }
                            break;
                        case ENTER:
                            switch (actSearch)
                            {
                                /////////// Search by name /////////////////////////////////
                            case 0:

                                counter = 0;
                                system("CLS");
                                XY(x - 5, y - 12);
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                                cout << "You enter the  \"" << searchMenu[actSearch] << "\"\n";
                                cin.ignore();
                                white;
                                cout << "Enter name of case for search: ";
                                
                                green;
                                getline(cin, searchstr);

                                //Search(cases, searchstr, actSearch);
                                
                                for (int i = 0; i < cases.size(); i++)
                                {
                                    if (cases[i] == searchstr)
                                    {
                                        cases[i].get();
                                        counter++;
                                    }
                                }
                                if (counter == 0)
                                {
                                    red;
                                    cout << "Nothing" << endl;
                                }

                                _getch();
                                system("CLS");
                                break;
                                /////////// Search by priority /////////////////////////////////////
                            case 1:

                                counter = 0;
                                system("CLS");
                                XY(x - 5, y - 12);
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                                cout << "You enter the  \"" << searchMenu[actSearch] << "\"\n";

                                white;
                                cout << "Enter priority of case for search: ";
                                green;
                                cin >> searchint;

                                for (int i = 0; i < cases.size(); i++)
                                {
                                    if (cases[i] == searchint)
                                    {
                                        cases[i].get();
                                        counter++;
                                    }
                                }
                                if (counter == 0)
                                {
                                    red;
                                    cout << "Nothing" << endl;
                                }

                                _getch();
                                system("CLS");
                                break;
                                /////////// Search by description////////////////////////////////////
                            case 2:

                                counter = 0;
                                system("CLS");
                                XY(x - 5, y - 12);
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                                cout << "You enter the  \"" << searchMenu[actSearch] << "\"\n";
                                cin.ignore();
                                white;
                                cout << "Enter description of case for search: ";

                                green;
                                getline(cin, searchstr);
                                
                                Search(cases, searchstr);

                                _getch();
                                system("CLS");
                                break;
                                /////////// Search by date///////////////////////////////////////////
                            case 3:

                                counter = 0;
                                system("CLS");
                                XY(x - 5, y - 12);
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                                cout << "You enter the  \"" << searchMenu[actSearch] << "\"\n";

                                
                                cin >> searchDate;

                                Search(cases, searchDate);

                                _getch();
                                system("CLS");
                                break;
                                /////////// Search by deadline///////////////////////////////////////
                            case 4:

                                counter = 0;
                                system("CLS");
                                XY(x - 5, y - 12);
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                                cout << "You enter the  \"" << searchMenu[actSearch] << "\"\n";

                                white;
                                cout << "Enter days before deadline of case for search: ";

                                green;
                                cin >> searchint;

                                Search(cases, searchint);


                                _getch();
                                system("CLS");
                                break;
                           
                                /////////////////////////////Выход из подменю в основное меню //////////////////////////
                            case 5:
                                ex = 0;
                                system("CLS");
                                break;
                            }
                        }
                    }
                    break;
                    _getch();
                    system("CLS");
                    break;

                }

                _getch();
                system("CLS");
                break;
/////////////////////////////////////////////////////////////// Case printer//////////////////////////////////////////////////////////////////
            case 4:
                system("CLS");
                
                if (cases.empty())
                {
                    red;
                    XY(x - 5, y);
                    cout << "List of cases is empty";
                }
                else
                {
               
                    system("CLS");
                    actPrint = 0;
                    sizeSubMenu = 5;
                    ex = 1;
                    while (ex)
                    {

                        XY(x, y);
                        SetDelMenuColor(actPrint, printMenuptr, sizeSubMenu, x, y);
                        char choise;
                        choise = _getch();
                        if (choise == -32) choise = _getch();
                        switch (choise)
                        {
                        case ESC:
                            break;
                        case UP:
                            if (actPrint > 0) { actPrint--; }
                            break;
                        case DOWN:
                            if (actPrint < 4) { actPrint++; }
                            break;
                        case ENTER:
                            switch (actPrint)
                            {
                                /////////// printer  all /////////////////////////////////
                            case 0:

                                counter = 0;
                                system("CLS");
                                XY(x - 5, y - 12);
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                                cout << "You enter the  \"" << printMenu[actPrint] << "\"\n";
                                
                                for (int i = 0; i < cases.size(); i++)
                                {
                                    cases[i].get();
                                }
                                _getch();
                                system("CLS");
                                break;
                                ///////////// print for the day ////////////////////////////////
                            case 1:

                                counter = 0;
                                system("CLS");
                                XY(x - 5, y - 12);
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                                cout << "You enter the  \"" << printMenu[actPrint] << "\"\n";

                                for (int i = 0; i < cases.size(); i++)
                                {
                                    if (cases[i].getDeadLine() <= 1) 
                                    {
                                        cases[i].get();
                                    }
                                }

                                _getch();
                                system("CLS");
                                break;
                                ///////////// print for the week ////////////////////////////////
                            case 2:

                                counter = 0;
                                system("CLS");
                                XY(x - 5, y - 12);
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                                cout << "You enter the  \"" << printMenu[actPrint] << "\"\n";

                                for (int i = 0; i < cases.size(); i++)
                                {
                                    if ( 1 < cases[i].getDeadLine() and cases[i].getDeadLine() <= 7)
                                    {
                                        cases[i].get();
                                    }
                                }

                                _getch();
                                system("CLS");
                                break;

                                ///////////// print for the month ////////////////////////////////
                            case 3:

                                counter = 0;
                                system("CLS");
                                XY(x - 5, y - 12);
                                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_INTENSITY);
                                cout << "You enter the  \"" << printMenu[actPrint] << "\"\n";
                                for (int i = 0; i < cases.size(); i++)
                                {
                                    if (7 < cases[i].getDeadLine() and cases[i].getDeadLine() <= 31)
                                    {
                                        cases[i].get();
                                    }
                                }
                                _getch();
                                system("CLS");
                                break;
                                /////////////////////////////Выход из подменю в основное меню //////////////////////////
                            case 4:
                                ex = 0;
                                system("CLS");
                                break;
                            }
                        }
                    }
                    break;
                    _getch();
                    system("CLS");
                    break;
                }

                
                _getch();
                system("CLS");
                break;
///////////////////////////////////////////////////////////// Sort cases /////////////////////////////////////////////////////////////////
            case 5:
                system("CLS");
                
                if (cases.empty())
                {
                    system("cls");
                    red;
                    XY(x - 5, y);
                    cout << "List of cases is empty";
                    _getch();
                    system("cls");
                }
                else
                {
                    system("CLS");
                    actSort = 0;
                    sizeSubMenu = 4;
                    ex = 1;
                    while (ex)
                    {

                        XY(x, y);
                        SetDelMenuColor(actSort, sortMenuptr, sizeSubMenu, x, y);
                        char choise;
                        choise = _getch();
                        if (choise == -32) choise = _getch();
                        switch (choise)
                        {
                        case ESC:
                            break;
                        case UP:
                            if (actSort > 0) { actSort--; }
                            break;
                        case DOWN:
                            if (actSort < 3) { actSort++; }
                            break;
                        case ENTER:
                            switch (actSort)
                            {
                                /////////// Sort by priority /////////////////////////////////
                            case 0:
                                system("CLS");
                                
                                Sort(cases);

                                green;
                                XY(x, y);
                                cout << "The list of cases has been sorted" << endl;
                                _getch();
                                system("CLS");
                                break;
                                /////////// Sort by date  /////////////////////////////////////
                            case 1:
                                system("CLS");

                                sort(cases.begin(), cases.end());

                                green;
                                XY(x, y);
                                cout << "The list of cases has been sorted" << endl;

                                _getch();
                                system("CLS");
                                break;
                                /////////// Sort by deadline ////////////////////////////////////
                            case 2:
                                system("CLS");

                                Sort(cases, 4);

                                green;
                                XY(x, y);
                                cout << "The list of cases has been sorted" << endl;


                                _getch();
                                system("CLS");
                                break;
                                /////////////////////////////Выход из подменю в основное меню //////////////////////////
                            case 3:
                                ex = 0;
                                system("CLS");
                                break;
                            }
                        }
                    }

                }
                break;
                //////// EXIT ////////////// ВЫХОД //////////////////////////////////////////////////////////////////////////////////
            case 6:
                exit(0);
            }
            break;



        default:
            cout << endl;
        }
    }   
}