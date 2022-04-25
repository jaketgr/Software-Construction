/* FILE NAME: project4_Knight_jdk0058.cpp 
 * AUTHOR: Jacob Knight
 * Auburn ID: jdk0058
 * Resources: I used the project4 hints file slightly to help with this assignment and I also used 
 * https://stackoverflow.com/questions/14544539/linked-lists-in-c to remind me about linked lists, then
 * https://www.cplusplus.com/reference/string/string/getline/, and
 * https://www.cplusplus.com/reference/string/stoi/, to help with the addQuestion.
 * Compile: g++ project4_Knight_jdk0058.cpp 
 * Run: ./a.out project4_Knight_jdk0058.cpp
 */
#include <iostream>
#include <string>
#include <stdlib.h>
#include <assert.h>
using namespace std;

struct Trivia {
    // Node Structure
    struct TriviaNode {
        string question;
        string answer;
        int value;
        TriviaNode *next;

        TriviaNode(string questionIn, string answerIn, int valueIn) {
            question = questionIn;
            answer = answerIn;
            value = valueIn;
            next = nullptr;
        }
    };

    // Iterator
    struct TriviaIterator {
        TriviaNode *current;

        TriviaIterator(TriviaNode *nodeIn) {
            current = new TriviaNode("", "", 0);
            current->next = nodeIn;
        }

        bool hasNext() {
            return current->next != nullptr;
        }

        TriviaNode next() {
            current = current->next;
            return (*current);
        }
    };

    // List Variables
    TriviaNode *first;
    TriviaNode *last;
    int size;
    int score;

    Trivia() {
        first = nullptr;
        last = nullptr;
        size = 0;
        score = 0;
    }

    bool add(string questionIn, string answerIn, int valueIn) {
        TriviaNode* newNode = new TriviaNode(questionIn, answerIn, valueIn);
        if (size == 0) {
            first = newNode;
        }
        else {
            last->next = newNode;
        }
        last = newNode;
        size++;
        return true;
    }

    TriviaIterator iterator() {
        return TriviaIterator(first);
    }

    // Prompt user to add a question
    void addQuestion() {
        string newQuestion;
        string newAnswer;
        string valueResponse;
        int newValue;
        cout << "Enter a question: ";
        getline(cin, newQuestion);
        cout << "Enter an answer: ";
        getline(cin, newAnswer);
        cout << "Enter award points: ";
        getline(cin, valueResponse);
        newValue = stoi(valueResponse);
        add(newQuestion, newAnswer, newValue);
    }

    // Ask the specified number of questions
    bool askQuestion(int numAsk) {
        if (numAsk < 1) {
            cout << "Warning - the number of trivia to be asked must equal to or be larger than 1." << endl;
            return false;
        }
        else if (size < numAsk) {
            cout << "Warning - there (is/are) only " << size << " trivia question(s) in the list." << endl;
            return false;
        }
        else {
            score = 0;
            TriviaIterator itr = iterator();
            int count = 0;
            while (itr.hasNext() && count < numAsk) {
                TriviaNode current = itr.next();
                string userAnswer;
                cout << "\nQuestion: " << current.question;
                cout << "\nAnswer: ";
                getline(cin, userAnswer);
                if (userAnswer.compare(current.answer) == 0) {
                    cout << "Your answer is correct! You receive " << current.value << " points." << endl;
                    score += current.value;
                }
                else {
                    cout << "Your answer is wrong. The correct answer is: " << current.answer << endl;
                }
                cout << "Your total points: " << score << endl;
                count++;
            }
            return true;
        }
    }

    // Initialize a list with some example questions. Currently accepted versions are 1 and 2
    void initialQuestions(int version) {
        size = 0;
        score = 0;
        if (version > -1) {  // Version 1 selects this list only
            add("How long was the shortest war on record? (Hint: how many minutes)", "38", 100);
        }
        if (version > 0) {  // Version 2 adds this block and the previous
            add("What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)?", "Bank of Germany", 50);
            add("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?", "Wii Sports", 20);
        }
    }
};

// Conditional Compilation
#define triviaQuiz
//#define UNIT_TESTING

int main() {
    Trivia game = Trivia();

    #ifdef triviaQuiz
        cout << "*** Welcome to Jacob's trivia quiz game ***" << endl;

        bool addMore = false;
        do {
            game.addQuestion();
            string userResponse = "";
            while (userResponse == "") {
                cout << "Continue? (Y/N): ";
                getline(cin, userResponse);
                if (userResponse.at(0) == 'y' || userResponse.at(0) == 'Y') {
                    addMore = true;
                }
                else if (userResponse.at(0) == 'n' || userResponse.at(0) == 'N') {
                    addMore = false;
                }
                else {
                    cout << "Invalid Response" << endl;
                    userResponse = "";
                }
            }
        } while (addMore);

        cout << "\n\n*** Welcome to Jacob's trivia quiz game ***"<< endl;
        game.askQuestion(game.size);

        cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***";
    #endif

    #ifdef UNIT_TESTING
        cout << "*** This is a debugging version ***" << endl;
        cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
        bool warning = game.askQuestion(0);
        assert(!warning);
        cout << "\nCase 1 Passed" << endl << endl;

        game.initialQuestions(1);
        cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
        game.askQuestion(1);
        assert(game.score == 0);
        cout << "\nCase 2.1 passed" << endl << endl;

        cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
        game.askQuestion(1);
        assert(game.score == 100);
        cout << "\nCase 2.2 passed" << endl << endl;

        cout << "Unit Test Case 3: Ask all the questions in the linked list." << endl;
        bool played = game.askQuestion(3);
        assert(played);
        cout << "\nCase 3 passed" << endl << endl;

        cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
        warning = game.askQuestion(5);
        assert(!warning);
        cout << "\nCase 4 passed" << endl << endl;

        cout << "*** End of debugging version ***";
    #endif

    return 0;
}