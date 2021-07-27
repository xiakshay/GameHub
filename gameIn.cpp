/* <-------------------------- Header Files --------------------------> */
#include <iostream>
#include <vector>  // use vector method
#include <fstream> // play with filles
#include <conio.h>
#include <windows.h> // to use system
#include <chrono>    // time and date

using namespace std;
int main();
/* <-------------------------- End Header Files --------------------------> */
/*<--------------------------- Timer for Game ---------------------------->*/
/* don't touch class */
class Timer
{
    LARGE_INTEGER startTime;
    double fFreq;

public:
    Timer()
    {
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        fFreq = (double)freq.QuadPart;
        reset();
    }

    void reset() { QueryPerformanceCounter(&startTime); }

    double getTime() const
    {
        LARGE_INTEGER endTime;
        QueryPerformanceCounter(&endTime);
        return (endTime.QuadPart - startTime.QuadPart) / fFreq; // as double
    }
};

/*<--------------------------- End Timer for Game ---------------------------->*/
/* <------------------------- Screen Modification ------------------------> */
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
/* <------------------------- End Screen Modification --------------------> */
/*<-------------------------- Design of load ----------------------------->*/

void loadingDesign()
{
    system("cls");
    system("Color 4D");
    cout << "\033[3;33m";
    cout << "\n\n\n\n                                                                                                               " << endl;
    cout << "                                                                                                               " << endl;
    cout << "          |              .------.      .------------.    .---------.    |   |\\        |     _________         " << endl;
    cout << "          |            .'        '.    |            |   |           |   |   | \\       |    |         |        " << endl;
    cout << "          |           |            |   |            |   |           |   |   |  \\      |    |         |        " << endl;
    cout << "          |           |            |   |            |   |           |   |   |   \\     |    |                  " << endl;
    cout << "          |           |            |   |            |   |           |   |   |    \\    |    |                  " << endl;
    cout << "          |           |            |   |------------|   |           |   |   |     \\   |    |    ---.          " << endl;
    cout << "          |           |            |   |            |   |           |   |   |      \\  |    |        |         " << endl;
    cout << "          |            '.        .'    |            |   |           |   |   |       \\ |    |        |         " << endl;
    cout << "          |_________     '------'      |            |   '-----------'   |   |        \\|    |________|  _ _ _  " << endl;
    cout << "                                                                                                               " << endl;

    cout << "   ";
    cout << "\033[3;34m";
    for (int i = 0; i < 102; i++)
    {
        cout << ":";
        Sleep(15);
    }
    cout << "\n\n"
         << endl;
    system("cls");
}
/*<-------------------------- End Design of load ----------------------------->*/
/*<------------------------- Game Score Update -------------------------------> */
// game history
int runCar = 0;
int runTicTac = 0;
int runCasino = 0;
int runWord = 0;
int runHangman = 0;
// player history
int maxCarScore = 0;
int maxWordScore = 0;
int maxHnagmanScore = 0;
int maxCasinoWin = 0;
int maxTictac = 0;
string wordHunter = "";
string hangmanHunter = "";
string casinoHunter = "";
string tictacHunter = "";

void uploadData(int carscore, string tictacname, int tictacScore, string csinoname, int casinomoney, string wordplayername, int wordscore, string hangmanplayer, int hangmanscore, int h1, int h2, int h3, int h4, int h5)
{
    ofstream myfile;
    myfile.open("scoredata.txt");
    myfile << carscore << "\n";
    myfile << tictacname << "\n";
    myfile << tictacScore << "\n";
    myfile << csinoname << "\n";
    myfile << casinomoney << "\n";
    myfile << wordplayername << "\n";
    myfile << wordscore << "\n";
    myfile << hangmanplayer << "\n";
    myfile << hangmanscore << "\n";
    myfile << h1 << "\n";
    myfile << h2 << "\n";
    myfile << h3 << "\n";
    myfile << h4 << "\n";
    myfile << h5 << "\n";
    myfile.close();
}

string LoadRandomWord(string path, int p)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);

        int randomLine = p;
        word = v.at(randomLine);
        reader.close();
    }
    return word;
}

void dataUpdation()
{
    string wordToGuess;
    wordToGuess = LoadRandomWord("scoredata.txt", 0);
    int carscore = stoi(wordToGuess);
    wordToGuess = LoadRandomWord("scoredata.txt", 1);
    string tictacname = wordToGuess;
    wordToGuess = LoadRandomWord("scoredata.txt", 2);
    int tictacScore = stoi(wordToGuess);
    wordToGuess = LoadRandomWord("scoredata.txt", 3);
    string csinoname = wordToGuess;
    wordToGuess = LoadRandomWord("scoredata.txt", 4);
    int casinomoney = stoi(wordToGuess);
    wordToGuess = LoadRandomWord("scoredata.txt", 5);
    string wordplayername = wordToGuess;
    wordToGuess = LoadRandomWord("scoredata.txt", 6);
    int wordscore = stoi(wordToGuess);
    wordToGuess = LoadRandomWord("scoredata.txt", 7);
    string hangmanplayer = wordToGuess;
    wordToGuess = LoadRandomWord("scoredata.txt", 8);
    int hangmanscore = stoi(wordToGuess);

    // played history
    wordToGuess = LoadRandomWord("scoredata.txt", 9);
    int recordRunCar = stoi(wordToGuess);
    wordToGuess = LoadRandomWord("scoredata.txt", 10);
    int recordRunTicTac = stoi(wordToGuess);
    wordToGuess = LoadRandomWord("scoredata.txt", 11);
    int recordRunCasino = stoi(wordToGuess);
    wordToGuess = LoadRandomWord("scoredata.txt", 12);
    int recordRunWord = stoi(wordToGuess);
    wordToGuess = LoadRandomWord("scoredata.txt", 13);
    int recordRunHangman = stoi(wordToGuess);

    // conditions for update every player name and score
    if (maxCarScore > carscore || maxWordScore > wordscore || maxHnagmanScore > hangmanscore || maxCasinoWin > casinomoney || maxTictac > tictacScore)
    {
        carscore = maxCarScore;
        wordscore = maxWordScore;
        wordplayername = wordHunter;
        hangmanscore = maxHnagmanScore;
        hangmanplayer = hangmanHunter;
        casinomoney = maxCasinoWin;
        csinoname = casinoHunter;
        tictacScore = maxTictac;
        tictacname = tictacHunter;
    }
    else
    {
        maxCarScore = carscore;
        maxWordScore = wordscore;
        wordHunter = wordplayername;
        maxHnagmanScore = hangmanscore;
        hangmanHunter = hangmanplayer;
        maxCasinoWin = casinomoney;
        casinoHunter = csinoname;
        maxTictac = tictacScore;
        tictacHunter = tictacname;
    }

    if (runCar > recordRunCar || runTicTac > recordRunTicTac || runCasino > recordRunCasino || runWord > recordRunWord || runHangman > recordRunHangman)
    {
        recordRunCar = runCar;
        recordRunTicTac = runTicTac;
        recordRunCasino = runCasino;
        recordRunWord = runWord;
        recordRunHangman = runHangman;
    }
    else
    {
        runCar = recordRunCar;
        runTicTac = recordRunTicTac;
        runCasino = recordRunCasino;
        runWord = recordRunWord;
        runHangman = recordRunHangman;
    }

    uploadData(carscore, tictacname, tictacScore, csinoname, casinomoney, wordplayername, wordscore, hangmanplayer, hangmanscore, runCar, runTicTac, runCasino, runWord, runHangman);
}
/*<------------------------- End Game Score Update -------------------------------> */
/* <-------------------------- Tic Tac Toi -------------------------------> */

typedef struct
{
    int *row;
} WinList;

class Player
{
private:
    string name;
    int score = 0;

public:
    Player() : Player{""} {}
    Player(string n) : score{0}, name{n} {}

    void won()
    {
        //increment the score
        score++;
    }
    int getScore() { return this->score; }

    string getName() { return this->name; }
};

class Game
{
private:
    char board[9];
    int emptyIndex[9];
    int gameOn, againstComputer;
    int emptyCount;
    WinList winlist[8];

    void displayBoard()
    {
        cout << endl;
        cout << "\t\t---------------------------" << endl;
        cout << "\t\t|                         |" << endl;
        cout << "\t\t|\t   |   |   "
             << "       |" << endl;
        cout << "\t\t|\t " << board[0] << " | " << board[1] << " | " << board[2] << "        |" << endl;
        cout << "\t\t|\t   |   |   "
             << "       |" << endl;
        cout << "\t\t|\t-----------"
             << "       |" << endl;
        cout << "\t\t|\t   |   |   "
             << "       |" << endl;
        cout << "\t\t|\t " << board[3] << " | " << board[4] << " | " << board[5] << "        |" << endl;
        cout << "\t\t|\t   |   |   "
             << "       |" << endl;
        cout << "\t\t|\t-----------"
             << "       |" << endl;
        cout << "\t\t|\t   |   |   "
             << "       |" << endl;
        cout << "\t\t|\t " << board[6] << " | " << board[7] << " | " << board[8] << "        |" << endl;
        cout << "\t\t|\t   |   |   "
             << "       |" << endl;
        cout << "\t\t|                         |" << endl;
        cout << "\t\t---------------------------" << endl;
        cout << endl;
    }

    void computerInput()
    {
        int pos;
        pos = rand() % 10;
        if (emptyIndex[pos] == 1)
        {
            if (emptyCount < 0)
                return;
            computerInput();
        }
        else
        {
            system("cls");
            cout << "\t\tComputer choose: " << pos + 1 << endl;
            Sleep(400);
            emptyIndex[pos] = 1;
            emptyCount -= 1;
            board[pos] = 'O';
        }
    }

    void playerInput(Player &player, Player &player1)
    {

        int pos;
        Sleep(500);
        cout << endl;
        // cout << "\t" << player.getName() << " Turn ";
        cout << "\t" << player.getName() << "'s Turn ";
        char inpt;
        cout << "\t Enter the position : ";
        inpt = getche();
        pos = (int)(inpt)-48;

        pos -= 1;
        if (emptyIndex[pos] == 1)
        {
            cout << "\n\t-----Position Invalid-------\n"
                 << endl;
            playerInput(player, player1);
        }
        else
        {
            emptyIndex[pos] = 1;
            emptyCount -= 1;
            player.getName().compare(player1.getName()) == 0 ? board[pos] = 'X' : board[pos] = 'O';
        }

        system("cls");
    }

    void
    checkWin(Player &p1, Player &p2)
    {
        int i, j, k;
        bool flag = false;
        char first_symbol;
        for (i = 0; i < 8; i++)
        {
            first_symbol = board[winlist[i].row[0]];

            if ((first_symbol != 'X') && (first_symbol != 'O'))
            {
                flag = false;
                continue;
            }
            flag = true;
            for (j = 0; j < 3; j++)
            {
                if (first_symbol != board[winlist[i].row[j]])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                gameOn = 0;
                if (first_symbol == 'X')
                {
                    cout << "\t\t--------------------------" << endl;
                    cout << "\t\t     " << p2.getName() << " WON          " << endl;
                    cout << "\t\t--------------------------" << endl;
                    p1.won();
                }
                else
                {
                    p2.won();
                    if (againstComputer)
                    {
                        cout << "\t\t------------------------" << endl;
                        cout << "\t\t|      Computer WON     |" << endl;
                        cout << "\t\t------------------------" << endl;
                    }
                    else
                    {
                        cout << "\t\t---------------------------" << endl;
                        cout << "\t\t    " << p1.getName() << " WON      " << endl;
                        cout << "\t\t---------------------------" << endl;
                    }
                }
                displayScore(p1, p2);
                break;
            }
        }
    }

    void playtic(Player &p1, Player &p2)
    {
        system("Color AD");
        char rematch = '\0';
        int hand = 0;
        gameOn = 1;
        displayBoard();
        while ((emptyCount > 0) && (gameOn != 0))
        {

            if (againstComputer)
                hand == 1 ? computerInput() : playerInput(p2, p2);
            else
                hand == 1 ? playerInput(p1, p2) : playerInput(p2, p2);
            hand = !hand;
            displayBoard();
            checkWin(p1, p2);
        }
        if (emptyCount <= 0)
        {
            cout << "\t\t-----------------------" << endl;
            cout << "\t\t|     No WINNER        |" << endl;
            cout << "\t\t-----------------------" << endl;
        }
        cout << endl;
        //score calculate high
        if (p1.getScore() > maxTictac)
        {
            maxTictac = p1.getScore();
            tictacHunter = p2.getName();
            cout << "\n\t\tCongo! " << tictacHunter << ", You just created a highest record of " << maxTictac << endl;
        }

        if (p2.getScore() > maxTictac)
        {
            maxTictac = p2.getScore();
            tictacHunter = p1.getName();
            cout << "\n\t\tCongo! " << tictacHunter << ", You just created a highest record of " << maxTictac << endl;
        }

        cout << "\n\n\t<------------------------------------------>" << endl;
        cout << "\t\t\tRematch Y/N: ";
        rematch = getche();
        if ((rematch == 'Y') || (rematch == 'y'))
        {
            init();
            playtic(p1, p2);
        }
    }
    void displayScore(Player &p1, Player &p2)
    {
        cout << endl;
        cout << "\t--------------------------------------------------------------------------------" << endl;
        cout << "\t|                                                                               |" << endl;
        cout << "\t\t" << p2.getName() << " SCORE : " << (p1.getScore() - p2.getScore());
        if (againstComputer)
            cout << "\t\t" << p2.getName() << " : " << p1.getScore() << " \t\tComputer: " << p2.getScore() << "      " << endl;
        else
            cout << "\t " << p2.getName() << " : " << p1.getScore() << " \t " << p1.getName() << " : " << p2.getScore() << endl;
        cout << "\t|                                                                               |" << endl;
        cout << "\t--------------------------------------------------------------------------------" << endl;
    }

public:
    Game() : emptyCount{0}, gameOn{1}, againstComputer{0}
    {
        init();
        winlist[0].row = new int[3]{0, 1, 2};
        winlist[1].row = new int[3]{3, 4, 5};
        winlist[2].row = new int[3]{6, 7, 8};
        winlist[3].row = new int[3]{0, 3, 6};
        winlist[4].row = new int[3]{1, 4, 7};
        winlist[5].row = new int[3]{2, 5, 8};
        winlist[6].row = new int[3]{0, 4, 8};
        winlist[7].row = new int[3]{2, 4, 6};
    }

    void init()
    {
        gameOn = 1;

        emptyCount = 0;
        srand(time(0));
        for (size_t i = 0; i < 10; i++)
        {
            emptyIndex[i] = 0;
            board[i] = (i + 1) + '0';
            emptyCount++;
        }
        emptyCount--;
    }

    void onePlayerGame()
    {
        //Creating Player
        string yname;
        cout << "\n\n\n\t\t-----------------------Name Creation---------------------" << endl;
        cout << "\t\t<>Enter your name : ";
        cin >> yname;
        Player p(yname);
        system("cls");
        Player c("Computer");
        cout << "\n\t\t-----------------------------------" << endl;
        cout << "\t\t   " << yname << ": X \t Computer: O" << endl;
        cout << "\t\t-------------------------------------" << endl;
        cout << endl;
        againstComputer = 1;
        playtic(c, p);
    }

    void twoPlayerGame()
    {
        //Creating Player
        string yname, oname;
        cout << "\n\n\n\t\t-----------------------Name Creation---------------------" << endl;
        cout << "\t\t<>Enter your name : ";
        cin >> yname;
        Sleep(500);
        Player p(yname);
        cout << "\t\t<>Enter another player name : ";
        cin >> oname;
        Player c(oname);
        Sleep(700);
        system("cls");
        cout << "\n\t\t-----------------------------------" << endl;
        cout << "\t\t " << yname << ": X \t " << oname << ": O" << endl;
        cout << "\n\t\t-----------------------------------" << endl;
        cout << endl;
        againstComputer = 0;
        playtic(c, p);
    }
};
void tictoctoi()
{
    int ch;

    system("cls");
    system("Color AD");
    cout << "\n\n\n\t\t -------------MENU-----------" << endl;
    cout << "\t\t|                            |" << endl;
    cout << "\t\t|    1. 1 Player game        |" << endl;
    cout << "\t\t|    2. 2 Player game        |" << endl;
    cout << "\t\t|    3. To exit              |" << endl;
    cout << "\t\t|                            |" << endl;
    cout << "\t\t ----------------------------" << endl;
    cout << endl;
    cout << "\n\t\t<> Select an option : ";
    char op = getche();
    ch = (int)(op)-48;
    cout << "\n\n\t<> Highest win in Tic Toc by " << tictacHunter << " won " << maxTictac << " times" << endl;
    Sleep(1500);
    loadingDesign();
    system("cls");
    system("Color AD");
    switch (ch)
    {
    case 1:
    {
        Game *game = new Game;
        game->init();
        game->onePlayerGame();
    }
    break;
    case 2:
    {
        Game *game = new Game;
        game->init();
        game->twoPlayerGame();
    }
    break;
    case 3:
        break;
    default:
        cout << "\n\t\t<-----OOPs Invalid Option! TRY AGAIN------>\n"
             << endl;
        tictoctoi();
    }
}
void tictacInstructions()
{
    system("cls");
    system("Color AD");
    cout << "\n\n\n"
         << endl;
    cout << "\t\t                + Tic Tac Toe + " << endl;
    cout << "\t\t - - - - - - - - - - - - - - -  - - -- - - - - - - - - - - - -" << endl;
    cout << "\t\t     . There are two options " << endl;
    cout << "\t\t               > one for play with computer" << endl;
    cout << "\t\t               > another for play with nearby player" << endl;
    cout << "\t\t     . in both the cases player have to enter name" << endl;
    cout << "\t\t     . Both can see there score and chances with name" << endl;
    cout << "\t\t     . Highest score is calculating in backend" << endl;
    cout << "\t\t - - - - - - - - - - - - - - -  - - -- - - - - - - - - - - - -" << endl;
    Sleep(1000);
}
// int main()
// {
//     tictoctoi();
//     return 0;
// }

/* <-------------------------- End Tic Tac Toi -------------------------------> */
/* <-------------------------- HnagMan Game -------------------------------> */
void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
    if (printTop)
    {
        cout << "\t\t+---------------------------------+" << endl;
        cout << "\t\t|";
    }
    else
    {
        cout << "\t\t|";
    }
    bool front = true;
    for (int i = message.length(); i < 33; i++)
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();

    if (printBottom)
    {
        cout << "|" << endl;
        cout << "\t\t+---------------------------------+" << endl;
    }
    else
    {
        cout << "|" << endl;
    }
}
void DrawHangman(int guessCount = 0)
{
    if (guessCount >= 1)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 2)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 3)
        PrintMessage("O", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 4)
        PrintMessage("/  ", false, false);

    if (guessCount == 5)
        PrintMessage("/| ", false, false);

    if (guessCount >= 6)
        PrintMessage("/|\\", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 7)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 8)
        PrintMessage("/", false, false);

    if (guessCount >= 9)
        PrintMessage("/ \\", false, false);
    else
        PrintMessage("", false, false);
}
void PrintLetters(string input, char from, char to)
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    PrintMessage(s, false, false);
}
void PrintAvailableLetters(string taken)
{
    PrintMessage("Available letters");
    PrintLetters(taken, 'A', 'M');
    PrintLetters(taken, 'N', 'Z');
}
bool PrintWordAndCheckWin(string word, string guessed)
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }
    PrintMessage(s, false);
    return won;
}
int hangmancountword;

string loadHangedWord(string path)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);

        int randomLine = rand() % v.size();
        // int randomLine = 0;
        hangmancountword = randomLine;
        word = v.at(randomLine);
        reader.close();
    }
    return word;
}
int TriesLeft(string word, string guessed)
{
    int error = 0;
    for (int i = 0; i < guessed.length(); i++)
    {
        if (word.find(guessed[i]) == string::npos)
            error++;
    }
    return error;
}
void HangManGame()
{
    system("cls");
    system("Color 1F");
    string hangmanplayer = "";
    cout << "\n\n\n"
         << endl;
    cout << "\t\t <> ---------------------------------------------- <>" << endl;
    cout << "\t\t |                                                  |" << endl;
    cout << "\t\t |      H A N G M A N                               |" << endl;
    cout << "\t\t |                     W O R D                      |" << endl;
    cout << "\t\t |                              K I L L E R         |" << endl;
    cout << "\t\t |                                                  |" << endl;
    cout << "\t\t <> ---------------------------------------------- <>" << endl;
    cout << "\n\n"
         << endl;
    cout << "\t\t<> Enter your name : ";
    cin >> hangmanplayer;
    cout << "\n\n\t<> Highest score made by " << hangmanHunter << " is : " << maxHnagmanScore << endl;
    Sleep(1500);

    char choice;
    int score = 0;
    Timer tHnag;
    do
    {
        srand(time(0));
        string guesses;
        string wordToGuess;
        wordToGuess = loadHangedWord("hangWords.txt");
        int tries = 0;
        int scoreChecker = 0;
        bool win = false;
        tHnag.reset(); // Timer starts
        do
        {
            system("cls");
            cout << "\n\n\n";
            cout << "\t -------------------------------------------------\n"
                 << endl;
            cout << "\t\t <> " << hangmanplayer << "! your game is running " << endl;
            cout << "\t\t <> your score is : " << score << "" << endl;
            cout << "\n\t -------------------------------------------------\n\n"
                 << endl;

            PrintMessage("HANGMAN");
            DrawHangman(tries);
            PrintAvailableLetters(guesses);
            PrintMessage("Guess the word");
            win = PrintWordAndCheckWin(wordToGuess, guesses);
            PrintMessage("Hint Below");

            if (win)
            {
                score += 10;
                break;
            }
            if (hangmancountword < 12)
            {
                PrintMessage("Month Name");
            }
            else if (hangmancountword < 19)
            {
                PrintMessage("Days Name");
            }
            else
            {
                PrintMessage("Social Media");
            }

            char x;
            cout << "\n\t\t>> ";
            x = getche();
            // cin >> x;

            if (guesses.find(x) == string::npos)
            {
                guesses += x;
                if (scoreChecker < 5)
                {
                    score += 1;
                }
                scoreChecker++;
            }
            else
            {
                score -= 2;
            }
            tries = TriesLeft(wordToGuess, guesses);

        } while (tries < 10);

        if (win)
        {
            cout << "\n"
                 << endl;
            cout << "\n\t\t" << hangmanplayer << ", Your current score is : " << score << endl;
            PrintMessage("YOU WON!");
            cout << "\n\t\tHurry!! You found word in " << tHnag.getTime() << "s Only" << endl;
        }
        else
        {
            cout << "\n"
                 << endl;
            cout << "\n\t\tyour  current score is : " << score << endl;
            PrintMessage("GAME OVER");
            score -= 5;
            cout << "\n\t\tOops! You Hanged in " << tHnag.getTime() << "s !!" << endl;
        }
        //highest score calculation
        if (maxHnagmanScore < score)
        {
            maxHnagmanScore = score;
            hangmanHunter = hangmanplayer;
            cout << "\n\n"
                 << endl;
            cout << "\t\tCongo ^.^ " << hangmanHunter << ", Your achieved Highest Hang score " << endl;
        }
        cout << "\n\t\tdo you want to replay y/n : ";
        choice = getche();
        if (choice == 'Y' || choice == 'y')
        {
            score += 5;
        }
        else
        {
            cout << "\n\n\t\t <> ";
            cout << hangmanplayer << ", you choose to quit this game" << endl;
            cout << "\t\t <> your total score is : " << score << endl;
        }
    } while (choice == 'Y' || choice == 'y');
}
void hangmaninstruction()
{
    system("cls");
    system("Color A0");
    cout << "\n\n\n\n"
         << endl;
    cout << "\t\t             . . . . . . . . . . . . . . " << endl;
    cout << "\t\t            |      HangMan  Rules       |" << endl;
    cout << "\t\t<------------------------------------------------------------------>" << endl;
    cout << "\t\t   . There are 10 trias only for the player" << endl;
    cout << "\t\t   . for one new try player get 1 score only for 5 times " << endl;
    cout << "\t\t   . After 5 trials for new key input player loose 2 scores " << endl;
    cout << "\t\t   . after find total word player get 10 scores" << endl;
    cout << "\t\t   . to continue with new game player get bonus score 5" << endl;
    cout << "\t\t   . after fail to find word in the game player loose 5 score " << endl;
    cout << "\t\t<------------------------------------------------------------------>" << endl;
    Sleep(1000);
}
/*
+---------------------------------+
|             HANG MAN            |
+---------------------------------+
|               |                 |
|               |                 |
|               O                 |
|              /|\                |
|               |                 |
|              / \                |
|         +----------+            |
|         |          |            |
+---------------------------------+
|        Available letters        |
+---------------------------------+
|     A B C D E F G H I J K L M   |
|     N O P Q R S T U V W X Y Z   |
+---------------------------------+
|         Guess the word          |
+---------------------------------+
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |
+---------------------------------+
>
*/

/* <-------------------------- End HangMan Game -------------------------------> */
/* <------------------------- Casino number gussing game -------------------> */

void kasinorules();
void kasinogame()
{
    system("Color 5F");
    system("cls");
    string playerName = "";
    int amount; // hold player's balance amount
    int bettingAmount;
    int guess;
    int dice; // hold computer generated number
    char choice;
    int usedMoney; // for calculate won money using this

    srand(time(0)); // "Seed" the random generator

    cout << "\t:..................................:" << endl;
    cout << "\t-----------------------------------" << endl;
    cout << "\t|                                  |" << endl;
    cout << "\t|                CASINO            |" << endl;
    cout << "\t|                 GAME             |" << endl;
    cout << "\t|                                  |" << endl;
    cout << "\t------------------------------------" << endl;
    cout << "\t:..................................:" << endl;
    Sleep(500);
    cout << "\n\n\tEnter Your Name : ";
    cin >> playerName;
    do
    {
        cout << "\n\n\tEnter Deposit amount to play game : Rs.";
        cin >> amount;
        usedMoney = amount;
        if (amount < 10)
        {
            cout << "\n\tYou have too low money! Enter again to play" << endl;
        }
    } while (amount < 10);
    cout << "\n\n\t<> Exclusive winner " << casinoHunter << " won : " << maxCasinoWin << "Rs." << endl;
    int moneyLeft = amount; //for calculate total lose or gain
    Sleep(1500);
    system("cls");
    cout << "\n\n\n";
    kasinorules();
    /*time to watch */
    Sleep(3000);
    /*end time to watch */

    int fwin = 0;
    do
    {
        system("Color 4E");
        system("cls");
        cout << "\n\n\n\tYour current balance is Rs. " << amount << "\n";
        Sleep(700);
        // Get player's betting amount
        do
        {
            cout << "\n\n\n\t" << playerName << ", enter money to bet : Rs.";
            cin >> bettingAmount;
            if (bettingAmount > amount)
                cout << "\n\tYour betting amount is more than your current balance\n"
                     << "\n\tRe-enter data\n ";
        } while (bettingAmount > amount);
        /* -----------start offer boxes---------- */

        int newLuck1 = rand() % 9 + 1;
        int newLuck2 = rand() % 9 + 1;
        gotoxy(WIN_WIDTH + 5, 5);
        cout << ".___________________________________.";
        gotoxy(WIN_WIDTH + 5, 6);
        cout << "|     Extra offer pack"
             << "              |";
        gotoxy(WIN_WIDTH + 5, 7);
        cout << "|     1. lucky draw " << newLuck1 << "               |";
        gotoxy(WIN_WIDTH + 5, 8);
        cout << "|     2. lucky draw " << newLuck2 << "               |";
        gotoxy(WIN_WIDTH + 5, 9);
        cout << "|  .:Press for extra wining price :.|";
        gotoxy(WIN_WIDTH + 5, 10);
        cout << "|___________________________________|";

        /*------------End offer box-------------*/
        // Get player's numbers
        do
        {
            cout << "\n\tGuess your number to bet between 1 to 9 :";
            if (fwin < -3)
            {
                cout << "\n\n\t<---------------------------------------->" << endl;
                cout << "\t|        Guess number between 1 and 2     |" << endl;
                cout << "\t|         There is an offer for you       |" << endl;
                cout << "\t<---------------------------------------->" << endl;
                cout << "\n\n\tInput lucky number : ";
            }
            char op = getche();
            // cin >> guess;
            guess = (int)(op)-48;
            if (guess <= 0 || guess > 10)
                cout << "\n\tPlease check the number!! should be between 1 to 9\n"
                     << "\n\tRe-enter data\n ";
        } while (guess <= 0 || guess > 10);

        gotoxy(WIN_WIDTH + 6, 16);
        cout << "\tyour credit score : " << amount - moneyLeft;

        cout << "\n\n\t ------------------------------" << endl;
        cout << "\t|          Checking...         |" << endl;
        cout << "\t ------------------------------\n"
             << endl;
        Sleep(1000);
        if (fwin < -3)
        {
            dice = rand() % 2 + 1;
        }
        else
        {
            dice = rand() % 9 + 1; // Will hold the randomly generated integer between 1 and 10
        }
        system("Color 5F");
        if (dice == guess)
        {
            cout << "\n\n\tHurry!! You won Rs." << bettingAmount * 8;
            amount = amount + bettingAmount * 8;
            if (dice == newLuck1)
            {
                cout << "\n\t\tcongo! you won extra 3x money : " << bettingAmount * 3 << endl;
                amount = amount + bettingAmount * 3;
            }
            else if (dice == newLuck2)
            {
                cout << "\n\t\tcongo! you won extra 5x money : " << bettingAmount * 5 << endl;
                amount = amount + bettingAmount * 5;
            }
            fwin = 0; //win in worst case
        }
        else
        {
            cout << "\tBetter luck next time !! You lost Rs. " << bettingAmount << "\n";
            amount = amount - bettingAmount;
            fwin--; //win in worst case
        }

        cout << "\n\tThe winning number was : " << dice << "\n";
        cout << "\n\t"
             << playerName << ", You have Rs. " << amount << "\n";

        // calculete wining money and max won
        int wonmoneycasino = amount - usedMoney;
        if (wonmoneycasino > maxCasinoWin)
        {
            maxCasinoWin = wonmoneycasino;
            casinoHunter = playerName;
            cout << "\n\tAmazing " << casinoHunter << ", You are doing great." << endl;
            cout << "\t    ^.^ you have won " << maxCasinoWin << " money. :))" << endl;
        }
        Sleep(700);
        if (amount == 0)
        {
            cout << "\tYou have no money to play ";
            Sleep(1600);
            break;
        }
        cout << "\n\n\t--> Do you want to play again (y/n)? ";
        choice = getche();
        // cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    system("cls");
    Sleep(700);
    cout << "\n\n\n";
    cout << "\t\t ===============================================================" << endl;
    cout << "\t\t||                                                             ||" << endl;
    cout << "\t\t                    :: " << playerName << " :: " << endl;
    cout << "\t\t     Thanks for playing game. Your Total amount is Rs. " << amount << endl;
    cout << "\t\t||                                                             ||" << endl;
    cout << "\t\t ===============================================================" << endl;
    Sleep(1500);
    cout << "\n\t:..............................................................................:" << endl;
    cout << "\t\t\t   ... Back to Home ..." << endl;
    Sleep(1000);
}

void kasinorules()
{
    system("cls");
    cout << "\n\n";
    cout << "\t-----------------------------------------------------------------------" << endl;
    cout << "\t|                                                                      |" << endl;
    cout << "\t|                           Rules of Casino                            |" << endl;
    cout << "\t|                                                                      |" << endl;
    cout << "\t-----------------------------------------------------------------------" << endl;
    cout << "\t|   1. Choose any number between 1 to 9                                |" << endl;
    cout << "\t|   2. If you win you will get 8 times of money you bet                |" << endl;
    cout << "\t|   3. If you will loose 4 times then you will get a special offer     |" << endl;
    cout << "\t|   4. There is section for extra win draw your luck with primium      |" << endl;
    cout << "\t|   5. If you bet on wrong number you will lose your betting amount    |" << endl;
    cout << "\t-----------------------------------------------------------------------" << endl;
    Sleep(2000);
}

/* <------------------------- End Casino number gussing game -------------------> */

/* <------------------------- Find word game ---------------------------------> */

void wordgameInstruction()
{
    system("cls");
    system("Color 60");
    cout << "\n\n\n\t\t.{}------------{instructions For Word Searching}----------------{}." << endl;
    cout << "\t\t|                                                                 |" << endl;
    cout << "\t\t|     1. Guess word using mind with pacience                      |" << endl;
    cout << "\t\t|     2. ALways try to be winner                                  |" << endl;
    cout << "\t\t|     3. For one correct answer you will get 5 points             |" << endl;
    cout << "\t\t|     4. For one wrong answer you will loose 2 points             |" << endl;
    cout << "\t\t|     5. To quit this game type *q* or *quite*  anytime           |" << endl;

    cout << "\t\t<>..............................................................<>\n"
         << endl;
    Sleep(2000);
}
string FindWordFile(string path)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);

        int randomLine = rand() % v.size();
        word = v.at(randomLine);
        reader.close();
    }
    return word;
}
void wordguessingMain()
{
    system("cls");
    system("Color A0");
    int wordScore = 0;
    string wordplayer;
    Timer tword; //timer init

    cout << "\n\n\n\t\t._________________________________________________________________." << endl;
    cout << "\t\t|                                                                 |" << endl;
    cout << "\t\t|            W O R D                                              |" << endl;
    cout << "\t\t|                 G U E S S I N G                                 |" << endl;
    cout << "\t\t|                          C H A M P I A N S                      |" << endl;
    cout << "\t\t|                                        2 0 2 1                  |" << endl;
    cout << "\t\t|_________________________________________________________________|\n"
         << endl;
    cout << "\t\t<>..............................................................<>\n"
         << endl;
    // cout << "\n\t\tYou can quit anytime by entering : quit \n\n";
    cout << "\n\n";
    cout << "\t\t <> Enter your name > ";
    cin >> wordplayer;
    cout << "\n\n\t <> Thank you! you game is starting... " << endl;
    cout << "\n\n\t <> Highest score of made by " << wordHunter << " is : " << maxWordScore << endl;

    Sleep(1500);
    wordgameInstruction();
    Sleep(500);
    // for random number generator
    srand(time(NULL));
    int count = 0;
    string guess;
    // loop
    do
    {
        system("Color 5E");
        system("cls");
        cout << "\n\n\n"
             << endl;
        cout << "\t\t! - () --------------------------------------------------------- () - !" << endl;
        cout << "\t\t! - ()                                                           () - !" << endl;
        cout << "\t\t! - ()       G U E S S                   HI                      () - !" << endl;
        cout << "\t\t! - ()             A N D                   GH                    () - !" << endl;
        cout << "\t\t! - ()                S C O R E              EST                 () - !" << endl;
        cout << "\t\t! - ()                                                           () - !" << endl;
        cout << "\t\t! - () --------------------------------------------------------- () - !" << endl;

        //score plate
        cout << "\n\n\t\tYour current score is : " << wordScore << endl;

        // word find through a file
        string str = FindWordFile("wordGuess.txt");
        string originalStr = str;

        int strlent = str.length();
        if (strlent > 5)
        {
            if (strlent < 8)
            {
                int ch1 = rand() % 7;
                int ch2 = rand() % 7;
                int ch3 = rand() % 7;
                // checking for same
                while (ch1 == ch2 || ch2 == ch3 || ch1 == ch3)
                {
                    ch2 = rand() % 7;
                    ch3 = rand() % 7;
                }
                // replacing with *
                str[ch1] = '*';
                str[ch2] = '*';
                str[ch3] = '*';
            }
            else
            {
                int ch1 = rand() % 8;
                int ch2 = rand() % 8;
                int ch3 = rand() % 8;
                int ch4 = rand() % 8;
                // checking for same
                while (ch1 == ch2 || ch1 == ch3 || ch1 == ch4 || ch2 == ch3 || ch2 == ch4 || ch3 == ch4)
                {
                    if (ch1 == ch2 || ch1 == ch3 || ch1 == ch4)
                    {
                        ch1 = rand() % 8;
                    }
                    if (ch2 == ch3 || ch2 == ch4)
                    {
                        ch2 = rand() % 8;
                    }
                    if (ch3 == ch4)
                    {
                        ch3 = rand() % 8;
                    }
                }
                // replacing with *
                str[ch1] = '*';
                str[ch2] = '*';
                str[ch3] = '*';
                str[ch4] = '*';
            }
        }
        else
        {
            int ch1 = rand() % 5;
            int ch2 = rand() % 5;

            // chekcing for same
            while (ch2 == ch1)
                ch2 = rand() % 5;

            // replacing with *
            str[ch1] = '*';
            str[ch2] = '*';
        }

        // timer starts here
        tword.reset();

        // showing
        cout << "\n\t\tword :  " << str;
        cout << "\n\n\t\tEnter your word guess : ";
        cin >> guess;

        // checking for quit
        if (guess.compare("q") == 0 || guess.compare("quit") == 0)
        {
            cout << "\n\n\n";
            cout << "\t\t     <> " << wordplayer << ", you choose to quit game <>" << endl;
            cout << "\t\t --------- <> calculating scores <> ---------\n\n"
                 << endl;
            Sleep(1500);
            cout << "\t\t{} : . : . : . : . : . {Final Score} : . : . : . : . : . : '  {}" << endl;
            cout << "\t\t|                                                              |" << endl;
            cout << "\t\t            Your Total Game Guess is : " << count << "                      " << endl;
            cout << "\t\t|                                                              |" << endl;
            cout << "\t\t                 <>Total Score : " << wordScore << "                            " << endl;
            cout << "\t\t<>...........................................................<>\n"
                 << endl;
            goto end;
        }
        // winning condition
        cout << "\n\n\t\t    ------------------------------" << endl;
        cout << "\t\t   |          Checking...         |" << endl;
        cout << "\t\t    ------------------------------\n"
             << endl;

        Sleep(1000);
        if (guess.compare(originalStr) == 0)
        {
            Beep(1397, 200);
            system("Color A0");
            cout << "\n\t\t\t: Your Guess is correct. :\n";
            wordScore += 5;
            count++;

            // timer end for word here
            cout << "\n\t\tYou got the word just in : " << (tword.getTime() - 1) << "s" << endl;

            Sleep(1000);
        }
        else
        {
            system("Color 4F");
            cout << "\n\n\t\t\t: Your Guess is Incorrect. :\n";
            Beep(240, 1500);
            cout << "\n\t\tRemember this word " << wordplayer << endl;
            cout << "\t\tCorrect word : " << originalStr << endl;
            // timer end for word here
            cout << "\n\t\tYou loosed time : " << (tword.getTime() - 2.5) << "s to find word" << endl;
            wordScore -= 2;
            Sleep(1000);
        }
        cout << "\n\t   <- - - - To Quit Game press 'q' or 'quit' while guessing - - - - ->\n"
             << endl;
        Sleep(1000);
    } while (1);
end:
    Beep(240, 900);
    //highest score calculation
    if (maxWordScore < wordScore)
    {
        maxWordScore = wordScore;
        wordHunter = wordplayer;
        cout << "\n\n"
             << endl;
        cout << "\t\tHurry! yo man ^.^ " << wordHunter << " hunted Highest word score :)" << endl;
    }
}

/* <------------------------- End Find word game ---------------------------------> */

/* <------------------------- car game ------------------------------------------> */
int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = {' ', '+', '+', ' ',
                  '+', '+', '+', '+',
                  ' ', '+', '+', ' ',
                  '+', '+', '+', '+'};

int carPos = WIN_WIDTH / 2;
int score = 0;

void setcursor(bool visible, DWORD size)
{
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}
void drawBorder()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            gotoxy(0 + j, i);
            cout << "±";
            gotoxy(WIN_WIDTH - j, i);
            cout << "±";
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(SCREEN_WIDTH, i);
        cout << "±";
    }
}
void genEnemy(int ind)
{
    enemyX[ind] = 17 + rand() % (33);
}
void drawEnemy(int ind)
{
    if (enemyFlag[ind] == true)
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "++++";
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << " ++ ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "++++";
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << " ++ ";
    }
}
void eraseEnemy(int ind)
{
    if (enemyFlag[ind] == true)
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << "    ";
    }
}
void resetEnemy(int ind)
{
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            cout << car[i][j];
        }
    }
}
void eraseCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            cout << " ";
        }
    }
}

int collision()
{
    if (enemyY[0] + 4 >= 23)
    {
        if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
        {
            return 1;
        }
    }
    return 0;
}
void gameover()
{
    system("cls");
    cout << "\n\n\n"
         << endl;
    cout << "\t\t _________________________\n"
         << endl;
    cout << "\t\t:    <> Car Crashed <>    :" << endl;
    cout << "\t\t:    <> score : " << score << " <>     :" << endl;
    cout << "\t\t _________________________" << endl
         << endl;
    if (maxCarScore <= score)
    {
        cout << "\n\t\t:   Boom" << endl;
        cout << "\t\t     Your are excellent" << endl;
        cout << "\t\t    created a new score (^.^)" << endl;
        cout << "\t\t _________________________" << endl;
    }

    Sleep(800);
}

void updateHighestScore()
{
    gotoxy(WIN_WIDTH + 6, 7);
    cout << "Highest" << endl;
    gotoxy(WIN_WIDTH + 7, 8);
    cout << "score ";
    gotoxy(WIN_WIDTH + 9, 9);
    cout << maxCarScore << endl;
}

void updateScore()
{
    gotoxy(WIN_WIDTH + 7, 5);
    cout << "Score: " << score << endl;
    updateHighestScore();
    if (score > maxCarScore)
    {
        maxCarScore = score;
    }
}

void instructions()
{
    system("Color 5F");

    system("cls");
    cout << "\n\n\n"
         << endl;
    cout << "\t\t________________________________________________\n"
         << endl;
    cout << "\t\t\t Instructions for Car Game" << endl;
    cout << "\t\t\t<>-----------------------<>" << endl;
    cout << "\t\t\t Avoid Cars by moving left or right. " << endl;
    cout << "\t\t\t Press 'a' to move left" << endl;
    cout << "\t\t\t Press 'd' to move right" << endl;
    cout << "\t\t\t Press 'escape' to exit" << endl;
    cout << "\t\t________________________________________________\n"
         << endl;
    cout << "\n\t\tpress any key for casino rules ";
    getche();
    kasinorules();
    cout << "\n\t\tpress any key for word game rules ";
    getche();
    wordgameInstruction();
    cout << "\n\t\tpress any key for hangman rules ";
    getche();
    hangmaninstruction();
    cout << "\n\t\tpress any key for Tic Tac rules ";
    getche();
    tictacInstructions();
    cout << "\n\t\tMove ahade and play games ";
    getche();
}

void play()
{
    system("Color 5F");

    carPos = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH + 7, 2);
    cout << "Car Game";
    gotoxy(WIN_WIDTH + 6, 4);
    cout << "----------";
    gotoxy(WIN_WIDTH + 6, 6);
    cout << "----------";
    gotoxy(WIN_WIDTH + 7, 12);
    cout << "Control ";
    gotoxy(WIN_WIDTH + 7, 13);
    cout << "-------- ";
    gotoxy(WIN_WIDTH + 2, 14);
    cout << " A Key - Left";
    gotoxy(WIN_WIDTH + 2, 15);
    cout << " D Key - Right";

    gotoxy(18, 5);
    // cout << "Press any key to start";
    // getch();
    gotoxy(18, 5);
    cout << "                      ";

    int speedGame = 50;
    while (1)
    {
        if (kbhit())
        {
            char ch = getch();
            if (ch == 'a' || ch == 'A')
            {
                if (carPos > 18)
                    carPos -= 4;
            }
            if (ch == 'd' || ch == 'D')
            {
                if (carPos < 50)
                    carPos += 4;
            }
            if (ch == 27)
            {
                break;
            }
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);
        if (collision() == 1)
        {
            gameover();
            return;
        }

        speedGame = 50 - (score / 5);
        if (speedGame < 20)
        {
            score += 1; // bonus score
        }
        else if (speedGame < 10)
        {
            speedGame = 10;
            score += 2; // bonus score
        }
        if (score > 400)
        {
            speedGame = 6;
            score += 4;
        }
        Sleep(speedGame);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10)
            if (enemyFlag[1] == 0)
                enemyFlag[1] = 1;

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;

        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(1);
            score++;
            updateScore();
        }
    }
}

/* <------------------------- End car game ------------------------------------------> */

/* <-+++++--------------- MAIN OPERATION -------------+++++++++++++-----------+++++----->*/

int main()
{
    dataUpdation();
    system("Color 1F");
    setcursor(0, 0);
    srand((unsigned)time(NULL));

    //timer start for full game
    Timer tFull;
    auto fullStart = std::chrono::system_clock::now();

    do
    {
        system("cls");
        system("Color 1F");
        gotoxy(16, 4);
        cout << "  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ";
        gotoxy(16, 5);
        cout << " |                                                                     | ";
        gotoxy(16, 6);
        cout << "                        G   A   M   I   N   G                            ";
        gotoxy(16, 7);
        cout << " |                                                                     | ";
        gotoxy(16, 8);
        cout << "                              H   U   B                                  ";
        gotoxy(16, 9);
        cout << " |                                                                     | ";
        gotoxy(16, 10);
        cout << "  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ";

        gotoxy(39, 13);
        cout << " ------------------------ ";
        gotoxy(39, 14);
        cout << "|     Played History     |";
        gotoxy(39, 15);
        cout << " ------------------------ ";
        gotoxy(39, 16);
        cout << "|                        |";
        gotoxy(39, 17);
        cout << "|    Car Game    : " << runCar << "    |";
        gotoxy(39, 18);
        cout << "|    Tic Toc     : " << runTicTac << "    |";
        gotoxy(39, 19);
        cout << "|    Casino Game : " << runCasino << "    |";
        gotoxy(39, 20);
        cout << "|    Word Guess  : " << runWord << "    |";
        gotoxy(39, 21);
        cout << "|     HangMan    : " << runHangman << "    |";
        gotoxy(39, 22);
        cout << "|                        |";
        gotoxy(39, 23);
        cout << " ------------------------ ";

        gotoxy(68, 13);
        cout << " - - - - - - - - - - - - - - - - - - - - - ";
        gotoxy(68, 14);
        cout << ":                Hunter's                 :";
        gotoxy(68, 15);
        cout << ":            Highest   Score              :";
        gotoxy(68, 16);
        cout << " - - - - - - - - - - - - - - - - - - - - - ";
        gotoxy(68, 17);
        cout << " <> Car Game .";
        gotoxy(68, 18);
        cout << "          crossed  { " << maxCarScore << " }  ";
        gotoxy(68, 19);
        cout << " <> Tic Toc ";
        gotoxy(68, 20);
        cout << "          { " << tictacHunter << " } Hited { " << maxTictac << " } times.";
        gotoxy(68, 21);
        cout << " <> Casino Game ";
        gotoxy(68, 22);
        cout << "          { " << casinoHunter << " } comped { " << maxCasinoWin << " } Rs. ";
        gotoxy(68, 23);
        cout << " <> Word Guess  ";
        gotoxy(68, 24);
        cout << "          { " << wordHunter << " } Scored { " << maxWordScore << " } at once.";
        gotoxy(68, 25);
        cout << " <>  HangMan  ";
        gotoxy(68, 26);
        cout << "          { " << hangmanHunter << " } Hited { " << maxHnagmanScore << " } score";
        gotoxy(68, 27);
        cout << "                   . . .                        ";
        gotoxy(68, 28);
        cout << " - - - - - - - - - - - - - - - - - - - - - ";

        gotoxy(10, 13);
        cout << " ---------------------- ";
        gotoxy(10, 14);
        cout << "|   Abvilable Games    |";
        gotoxy(10, 15);
        cout << " ---------------------- ";
        gotoxy(10, 16);
        cout << "|   1. Car Game        |";
        gotoxy(10, 17);
        cout << "|   2. Tic Toc         |";
        gotoxy(10, 18);
        cout << "|   3. Casino Game     |";
        gotoxy(10, 19);
        cout << "|   4. Word Guessing   |";
        gotoxy(10, 20);
        cout << "|   5. HangeMan        |";
        gotoxy(10, 21);
        cout << "|   6. Instructions    |";
        gotoxy(10, 22);
        cout << "|   7. Quit            |";
        gotoxy(10, 23);
        cout << " ----------------------";

        gotoxy(80, 31);
        cout << "Created By: ";
        gotoxy(90, 32);
        cout << " Akshay Kumar Kushwaha";
        gotoxy(90, 33);
        cout << " Shubham Singh";

        gotoxy(10, 26);
        cout << "Select option: ";
        char op = getche();

        //adding time management system
        tFull.reset();

        if (op == '1')
        {
            runCar++;
            loadingDesign();
            play();
            cout << "\n\n\tYou played car game till : " << tFull.getTime() << "s" << endl;
            dataUpdation();
            Sleep(3000);
        }
        else if (op == '2')
        {
            runTicTac++;
            tictoctoi();
            cout << "\n\n\tYou played tic toc toe game till : " << tFull.getTime() << "s" << endl;
            dataUpdation();
            Sleep(3000);
        }
        else if (op == '3')
        {
            runCasino++;
            kasinogame();
            cout << "\n\n\tYou played Casino Number guessing till : " << tFull.getTime() << "s" << endl;
            dataUpdation();
            Sleep(3000);
        }
        else if (op == '4')
        {
            runWord++;
            wordguessingMain();
            cout << "\n\n\tYou played word Guessing game till : " << tFull.getTime() << "s" << endl;
            dataUpdation();
            Sleep(3000);
        }
        else if (op == '5')
        {
            runHangman++;
            loadingDesign();
            HangManGame();
            cout << "\n\n\tYou played Hangman till : " << tFull.getTime() << "s" << endl;
            dataUpdation();
            Sleep(3000);
        }
        else if (op == '6')
        {
            instructions();
        }
        else if (op == '7')
        {
            break;
        }

    } while (1);

    // end full timer
    auto fullEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_secondstotal = fullEnd - fullStart;
    std::time_t fullEnd_time = std::chrono::system_clock::to_time_t(fullEnd);
    cout << "\n\n\n"
         << endl;
    cout << "\t\t<>-------------------------<>------------------------------<>" << endl;
    std::cout << "\t\t  finished full game computation at " << std::ctime(&fullEnd_time)
              << "\n\t\t\t\telapsed time: " << elapsed_secondstotal.count() << "s\n";
    cout << "\n\t\t<>-------------------------<>------------------------------<>\n\n"
         << endl;

    Sleep(1000);
    return 0;
}
