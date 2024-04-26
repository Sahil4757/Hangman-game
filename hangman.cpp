#include<iostream>
#include<vector>                           
#include<fstream>                          
#include<string>
#include<time.h>
using namespace std;

void printmessage (string message, bool printTop = true, bool printBotomm = true) {

    
    if (printTop) {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    } else {
        cout << "|";
    }

   
    bool front = true;
    for (int i = message.length(); i < 33; i++) {
        if (front) {
            message = " " + message;
        }
        else{
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();

    if (printBotomm) {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl; 
    }
    else {
        cout << "|" << endl;
    }
}

void drawHangman (int guessCount = 0) {

    if (guessCount >= 1) 
        printmessage("|", false, false);
    else 
        printmessage("", false, false);

    if (guessCount >= 2)
        printmessage("|", false, false);
    else 
        printmessage("", false, false);
    
    if (guessCount >= 3)
        printmessage("O", false, false);
    else 
        printmessage("", false, false);

    if (guessCount == 4) 
        printmessage("/  ", false, false);
    if (guessCount == 5)
        printmessage("/| ", false, false);
    if (guessCount >= 6)
        printmessage("/|\\", false, false);
    else
        printmessage("", false, false);

    if (guessCount >= 7)
        printmessage("|", false, false);
    else
        printmessage("", false, false);

    if (guessCount == 8)
        printmessage("/", false, false);
    if (guessCount >= 9)
        printmessage("/ \\", false, false);
    else
        printmessage("", false, false);    
}

void printLetters (string input, char from, char to) {

    string s;
    for (char i = from; i <= to; i++) {
        if (input.find(i) == string::npos) {   
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    printmessage(s, false, false);
}

void printAvailiableLeters (string taken) {

    printmessage("Availiable Letters");    
    printLetters(taken, 'A', 'M');
    printLetters(taken, 'N', 'Z');
}

bool printWordAndCheckWin (string word, string guessed) {

    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++) {
        if (guessed.find(word[i]) == string::npos) {
            won = false;
            s += "_ ";
        }
        else {
            s += word[i];
            s += " ";
        }
    }
    printmessage(s, false);
    return won;
}

string loadRandomWord (string path)  {

    srand(time(0));
    int lineCount = 0;                      
    string word;
    vector<string> v;                       
    ifstream reader(path);                      
    if (reader.is_open())                      
    {                 
        while(std::getline(reader, word))       
            v.push_back(word);

        int randomLine = rand() % v.size();     

        word = v.at(randomLine);               
        reader.close();
    }
    return word;

}

int triesLeft (string word, string guessed) {

    int error = 0;
    for (int i = 0; i < guessed.length(); i++) {
        if (word.find(guessed[i]) == string::npos)
            error++;
    }
    return error;
}

int main()
{
    srand(time(0));
    string guesses;
    string wordToGuess;
    wordToGuess = loadRandomWord("hangman.txt");                //load from this file
    int tries;
    bool win = false;
    do {
        system("cls");
        printmessage("Hang Man");                               
        drawHangman(tries);
        printAvailiableLeters(guesses);
        printmessage("Guess the word");
        printWordAndCheckWin(wordToGuess, guesses);

        if (win)
            break;
            
        char x;
        cout << ">"; cin >> x;
        if (guesses.find(x) == string::npos) 
                guesses += x;

        tries = triesLeft(wordToGuess, guesses);

    } while(tries < 10);

    if (win)
        printmessage("YOU WON!");
    else
        printmessage("GAME OVER");

    cout << "The word was: " << wordToGuess << endl;
    system("pause");
    getchar();
    return 0;
}


/*

Should look like this

+---------------------------------------+
|               HANG MAN                |
+---------------------------------------+
|                  |                    |
|                  |                    |
|                  O                    |
|                 /|\                   |
|                  |                    |
|                 / \                   |
|            --------------             |
|            |            |             |
+---------------------------------------+
|           Availiable letters          |
+---------------------------------------+
|       A B C D E F G H I J K L M       |
|       N O P Q R S T U V W X Y Z       |
+---------------------------------------+ 
|           Guess the word              |
+---------------------------------------+
|    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _      |
+---------------------------------------+
*/
