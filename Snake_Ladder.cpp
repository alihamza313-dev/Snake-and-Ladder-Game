#include <iostream>
#include <ctime>
#include <algorithm>
#include<fstream>
#include <string>
#include<conio.h>
#include<thread>
#include<chrono>

using namespace std;

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define BLUE "\033[1;34m"

class player
{
public:
    string name;
    int curPos;
    bool status;
    int die1, die2;
    bool active;

    player(bool a, string n)
    {
        die1 = -1;
        die2 = -2;
        curPos = 0;
        active = a;
        name = n;
        status = false;
    }

    void toss_die()
    {
        this->die1 = (rand() % 6) + 1;
        this->die2 = (rand() % 6) + 1;
    }

    bool is_dieSame()
    {
        return (die1 == die2);
    }

    string get_name() const
    {
        return name;
    }

    void show_dice()
    {
        cout << "[" << die1 << " , " << die2 << "]" << endl;
    }
};

class board
{
public:
    int win_pos;
    int* snake_top, * snake_botm;
    int* ladder_top, * ladder_botm;

    board()
    {
        snake_top = nullptr;
        snake_botm = nullptr;
        ladder_top = nullptr;
        ladder_botm = nullptr;
        cout << MAGENTA << "Enter winning Position (>=50) : " << RESET;
        cin >> win_pos;
        cin.ignore();
        while (win_pos < 50)
        {
            cout << MAGENTA << "Enter winning Position (>=50) : " << RESET;
            cin >> win_pos;
        }
        snakes_Ladder();
    }

    void snakes_Ladder()
    {
        int n = win_pos / 15;
        snake_botm = new int[n];
        snake_top = new int[n];
        ladder_botm = new int[n];
        ladder_top = new int[n];

        for (int i = 0, j = 1; i < n; i++, j += 2)
        {
            ladder_botm[i] = (rand() % (win_pos - 20)) + 5;
            ladder_top[i] = std::min((win_pos - 5), (ladder_botm[i] + ((rand() % 10) + 10)));
            snake_top[i] = (rand() % (win_pos - 30)) + 20;
            snake_botm[i] = std::max(5, snake_top[i] - ((rand() % 15) + 10));
        }
    }

    ~board()
    {
        delete[] snake_botm;
        delete[] snake_top;
        delete[] ladder_botm;
        delete[] ladder_top;
    }
};

class Game
{
    bool flag;
    board* gameboard;
    player* p1;
    player* p2;
    bool is_snake;
    bool is_ladder;
    bool is_singlePlayer;

public:
    Game(int c)
    {
        flag = false;
        is_snake = false;
        is_ladder = false;
        gameboard = new board();

        if (c == 1)
        {
            is_singlePlayer = true;
            single_player();
        }
        else
        {
            is_singlePlayer = false;
            double_player();
        }
    }

    void single_player()
    {
        string n;
        cout << RED << "Enter player name: " << RESET;
        getline(cin, n);
        p1 = new player(true, n);
        p2 = new player(false, "Computer");
    }

    void double_player()
    {
        string n;
        cout << RED << "Enter first player name: " << RESET;
        getline(cin, n);
        string m;
        cout << YELLOW << "Enter second player name: " << RESET;
        getline(cin, m);

        p1 = new player(true, n);
        p2 = new player(false, m);
    }

    void starting_details()
    {
        cout << YELLOW << "=============================================" << RESET << endl;
        cout<<YELLOW << "->" <<RESET << GREEN << " Both players are at square [0] " << RESET << endl;
        cout << YELLOW << "->" << RESET << GREEN << "Player will have another turn if both dice are the same" << RESET << endl;
        cout << YELLOW << "->" << RESET << GREEN << "First player turn dice by pressing ENTER" << RESET << endl;
        cout << YELLOW << "->" << RESET << GREEN << "Second player turn dice by pressing SPACE BAR" << RESET << endl;
        cout << YELLOW << "=============" << RESET
            << GREEN << " Lets Enjoy Your Game " << RESET
            << YELLOW << "=============" << RESET << endl;

        cout << "---------------------------------------------" << endl;
    }
    void start_game()
    {
        while (!flag)
        {
            if (p1->active)
            {
                player_turns(p1, RED);
            }
            else
            {
                player_turns(p2, YELLOW);
            }

            if (flag)
            {
                show_result();
                break;
            }

            change_player();
        }
    }

    void player_turns(player* p, const string& color)
    {
        cout << color << p->name << RESET << YELLOW << "->" << RESET << color << " It's your turn: " << RESET << endl;

        if (p->name == "Computer" && is_singlePlayer)
        {

            cout << BLUE << "Computer rolled the dice!..." << RESET << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        else
        {
        char ch = _getch();
        if (p->name == p1->name)
        {
            while (true)
            {
                if (ch != 13)
                {
                    cout << color << p->get_name() << RESET << YELLOW << "->" << RESET << color << ": Press Enter to roll dices" << RESET;
                    ch = _getch();
                }
                else
                    break;
            }
        }
        else
        {
                while (true)
                {
                    if (ch != 32)
                    {
                        cout << color << p->get_name() << RESET << YELLOW << "->" << RESET << color << ": Press Space bar to roll dices" << RESET;
                        ch = _getch();
                    }
                    else
                        break;
                }
        }
                
            }

        p->toss_die();
        p->show_dice();
        p->curPos += p->die1 + p->die2;

        if (p->curPos == gameboard->win_pos)
        {
            flag = true;
            p->status = true;
        }
        else if (p->curPos > gameboard->win_pos)
        {
            p->curPos = gameboard->win_pos - (p->curPos % gameboard->win_pos);
        }

        cout << color << "You are at square [" << p->curPos << "]" << RESET << endl;
        change_cursor(p);

        if (is_snake)
        {
            cout << BLUE << "HAHA! Snake got you! You fell to square [" << p->curPos << "]" << RESET << endl;
            is_snake = false;
        }
        if (is_ladder)
        {
            cout << BLUE << "O MY YES! Ladder boost! You climbed to square [" << p->curPos << "]" << RESET << endl;
            is_ladder = false;
        }

        cout << "--------------------" << endl;

        if (p->is_dieSame())
        {
            cout <<YELLOW<< "Hurrah! Again turn" << RESET<<endl;
            change_player(); // Extra turn for same dice
        }
    }

    void change_player()
    {
        if (p1->active)
        {
            p1->active = false;
            p2->active = true;
        }
        else
        {
            p2->active = false;
            p1->active = true;
        }
    }

    void change_cursor(player* p)
    {
        int n = gameboard->win_pos / 15;
        for (int i = 0; i < n; i++)
        {
            if (p->curPos == gameboard->snake_top[i])
            {
                p->curPos = gameboard->snake_botm[i];
                is_snake = true;
            }

            if (p->curPos == gameboard->ladder_botm[i])
            {
                p->curPos = gameboard->ladder_top[i];
                is_ladder = true;
            }
        }
    }

    void show_result() const
    {
        cout << YELLOW<<"====================================================================="<<RESET << endl;
        if (p1->status)
        {
            cout << GREEN << "CONGRATULATIONS! " << p1->get_name() << " YOU ARE THE WINNER!" << RESET << endl;
        }
        else
        {
            cout << GREEN << "CONGRATULATIONS! " << p2->get_name() << " YOU ARE THE WINNER!" << RESET << endl;
        }
        cout << YELLOW<<"=====================================================================" <<RESET<< endl;
    }

    void save_result()
    {
        ofstream out("Game_history.txt",ios::app);

        if (!out)
        {
            cout << RED << "Error saving game!" << RESET << endl;
            return;
        }
        out << "Winning position : " << gameboard->win_pos<<endl;
        out << "    Player 1      |      player 2" << endl;
        out <<"    "<< p1->name << "       |       " << p2->name << endl;
        if (p1->status)
        {
            out <<"     Winner       |           Looser" << endl;
        }
        else
        {
            out << "    Looser       |           Winner" << endl;
        }
        out << "Snake Top | Snake bottom" << endl;
        for (int i = 0; i < (gameboard->win_pos / 15); i++)
        {
            out << gameboard->snake_top[i] << "    |     " << gameboard->snake_botm[i] << endl;
        }
        out << "Ladder Top | Ladder bottom" << endl;
        for (int i = 0; i < (gameboard->win_pos / 15); i++)
        {
            out << gameboard->ladder_top[i] << "    |     " << gameboard->ladder_botm[i] << endl;
        }
        out << "----------------------------------------------------------------" << endl;
        out.close();
    }

    ~Game()
    {
        delete p1;
        delete p2;
        delete gameboard;
    }

};

int main()
{
    srand(time(0));
    cout << CYAN << "======================= WELCOME TO SNAKE LADDER GAME =======================" << RESET << endl;
    cout << YELLOW << "----------------------------------------------------------------------------" << RESET << endl;
    cout<<GREEN << "Do you want to play game(Y/N)" <<RESET<< endl;
    char c = _getch();
    while (true)
    {
        if (c == 'Y' || c == 'y')
        {
            cout << CYAN<< "1. Single player" << RESET<<endl;
            cout <<CYAN<< "2. Double player" <<RESET<< endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
            return 0;
        }

        cout<<GREEN << "Enter your choice(1|2) : "<<RESET;
        int choice;
        cin >> choice;
        cin.ignore();
        while (true)
        {
            if (choice < 1 || choice>2)
            {
                cout <<RED<< "Enter valid choice(1|2) : "<<RESET;
                cin >> choice;
            }
            else
                break;
        }


        Game g1(choice);
        g1.starting_details();
        g1.start_game();
        g1.save_result();


        cout <<GREEN<< "Do you want to play again(y/n) : "<<RESET;
        c = getchar();
        if (c == 'y' || c == 'Y')
        {
            cout << CYAN << "======================= WELCOME Back TO SNAKE LADDER GAME =======================" << RESET << endl;
            system("cls");
        }
        else
            return 0;
    }


}
