#include<iostream>
#include<vector>                            // Dynamic array
#include<fstream>                           // To load files
#include<string>
#include<time.h>
using namespace std;

void printmessage (string message, bool printTop = true, bool printBotomm = true) {

    //prints top"+--" 
    if (printTop) {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    } else {
        cout << "|";
    }

    //prints sentence 
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

    // prinits bottom "---+" after sentence
    if (printBotomm) {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl; 
    }
    else {
        cout << "|" << endl;
    }
}

void drawHangman (int guessCount = 0) {

    //this function draws hangman's body as per guess count
    //else means rhs space
    //printmessage("lhs", top, bottom)
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

    // here == bc 3 chars on line therefore print '/' only idk y. Also no else condition for these. 
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

    // This prints chars A to Z 
    // Empty if guessed char correctly
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

    // same like above fun ig
    printmessage("Availiable Letters");     //here fun(" ", true, true);
    printLetters(taken, 'A', 'M');
    printLetters(taken, 'N', 'Z');
}

bool printWordAndCheckWin (string word, string guessed) {

    //assume player already won
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
    //prints entered guess if correct on that _
    printmessage(s, false);
    return won;
}

string loadRandomWord (string path)  {

    // Most complex fuction yet
    // This will load any 1 of 100 words from hangman.txt file

    srand(time(0));
    int lineCount = 0;                      
    string word;
    vector<string> v;                       
    ifstream reader(path);                      // read file path ?
    if (reader.is_open())                       // if file is open
    {                 
        while(std::getline(reader, word))       
            v.push_back(word);

        int randomLine = rand() % v.size();     // random find  v.size = max, min = 0

        word = v.at(randomLine);                //word = random sentence selected
        reader.close();
    }
    return word;

}

int triesLeft (string word, string guessed) {

    // simple fun to find errors | if guessed char[i] != char at that pos, err++
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
        printmessage("Hang Man");                               // fun(" ", true, true);
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