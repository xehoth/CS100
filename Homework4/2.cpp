/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @author Hongtu Xu
 * @date 2019-10-17
 */
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <time.h>
#include <functional>
#include <cassert>
#include <cstring>

using namespace std;

#define MAX_ROWS 3
#define MAX_COLS 10
#define MAX_STUDENTS 30

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define NOTHING 0
#define APPLEPIE 1
#define BEEF 2
#define CURRY 3

typedef int MEALTYPE;

class Fmart;  // this line is used to identify Fmart as a type name, since class Player and class
              // Student have pointers to Fmart.

// ------------------------------Helper functions--------------------------------------//
int randInt(int min, int max) {
    if (max < min) swap(max, min);
    return rand() % (max - min + 1) + min;
}
// -----------------------------Class Declarations-------------------------------------//
class Player {
   public:
    // constructor
    Player(Fmart *fp);

    // destructor
    ~Player();

    // accessors
    int row() const;
    int col() const;
    int lives() const;
    int score() const;
    MEALTYPE mealInHand() const;

    // mutators
    void pickup(MEALTYPE meal);
    void move(int dir);

    void deliver();
    void decLife();

   private:
    int m_row;
    int m_col;
    int m_lives;
    int m_score;
    MEALTYPE m_mealInHand;
    Fmart *m_fp;
};

class Student {
   public:
    // constructor
    Student(Fmart *fp, int row, int col);

    // destructor
    ~Student();

    // accessors
    int row() const;
    int col() const;
    MEALTYPE typeWanted() const;

    // mutators
    void moveForward();

   private:
    Fmart *m_fp;
    int m_row, m_col;
    MEALTYPE m_typeWanted;
};

class Fmart {
   public:
    // constructor
    Fmart();

    // destructor
    ~Fmart();

    // accessors
    Player *getPlayer() const;
    int numberOfStudents() const;
    bool studentAt(int row, int col) const;

    // mutators
    bool addStudent();
    bool deleteStudent(int row, int col);
    void display();
    void play();

    Student *getLeftMostStudent(int row) {
        Student *p = nullptr;
        int minCol = 11;
        for (int i = 0; i < m_numStudents; i++) {
            if (m_students[i]->row() == row && m_students[i]->col() < minCol) {
                p = m_students[i];
                minCol = m_students[i]->col();
            }
        }
        return p;
    }

   private:
    Player *m_player;
    Student *m_students[MAX_STUDENTS];
    int m_numStudents;
};

//---------------------------Implementions of Fmart-------------------------------------//

Fmart::Fmart() {
    m_player = new Player(this);
    memset(m_students, 0, sizeof(m_students));
    m_numStudents = 0;
}

Fmart::~Fmart() {
    delete m_player;
    m_player = nullptr;
    for (int i = 0; i < m_numStudents; i++) {
        delete m_students[i];
        m_students[i] = nullptr;
    }
    m_numStudents = 0;
}

Player *Fmart::getPlayer() const { return m_player; }

int Fmart::numberOfStudents() const { return m_numStudents; }

bool Fmart::studentAt(int row, int col) const {
    for (int i = 0; i < m_numStudents; i++) {
        if (m_students[i]->row() == row && m_students[i]->col() == col) return true;
    }
    return false;
}

bool Fmart::addStudent() {
    if (m_numStudents >= MAX_STUDENTS) return false;
    m_students[m_numStudents++] = new Student(this, randInt(1, 3), 10);
    return true;
}

bool Fmart::deleteStudent(int row, int col) {
    int idx = -1;
    for (int i = 0; i < m_numStudents; i++) {
        if (m_students[i]->row() == row && m_students[i]->col() == col) {
            idx = i;
            break;
        }
    }
    if (idx == -1) return false;
    delete m_students[idx];
    memmove(m_students + idx, m_students + idx + 1, sizeof(Student) * (m_numStudents - idx - 1));
    m_numStudents--;
    return true;
}

/** Display the game grid
 * It will display grids, players and students.
 * There are a few blanks for you to fill in.
 */
void Fmart::display() {
    char **disp = new char *[3];
    for (int i = 0; i < 3; i++) {
        disp[i] = new char[10];
        for (int j = 0; j < 10; j++) disp[i][j] = '.';
    }

    for (int i = 0, r, c; i < m_numStudents; i++) {
        r = m_students[i]->row() - 1;
        c = m_students[i]->col() - 1;
        disp[r][c] = 'S';
        if (m_students[i]->typeWanted() == m_player->mealInHand()) disp[r][c] = '@';
    }
    auto getPlayerMealType = [&](MEALTYPE type) {
        switch (type) {
            case NOTHING:
                return 'P';
            case APPLEPIE:
                return 'A';
            case BEEF:
                return 'B';
            case CURRY:
                return 'C';
#ifdef _DEBUG
            default:
                assert(false);
#endif
        }
        return 'P';
    };
    disp[m_player->row() - 1][m_player->col() - 1] = getPlayerMealType(m_player->mealInHand());

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) cout << disp[i][j];
        cout << endl;
    }

    for (int i = 0; i < 3; i++) delete[] disp[i];
    delete[] disp;
}

void Fmart::play() {
    addStudent();  // Adds the first student.
    while (m_player->lives() > 0) {
        display();
        cout << "You have " << m_player->lives() << " lives, and your score is "
             << m_player->score() << "." << endl;
        cout << "make a move (a, b, c, u, d, g): " << endl;
        string input;
        getline(cin, input);
        cout << endl << endl << endl;

        char option = input[0];  // Here, option is 'a', 'b', 'c', 'u', 'd', or 'g'.

        switch (option) {
            case 'a': {
                m_player->pickup(APPLEPIE);
                break;
            }
            case 'b': {
                m_player->pickup(BEEF);
                break;
            }
            case 'c': {
                m_player->pickup(CURRY);
                break;
            }
            case 'u': {
                m_player->move(UP);
                break;
            }
            case 'd': {
                m_player->move(DOWN);
                break;
            }
            case 'g': {
                m_player->deliver();
                break;
            }
            default: {
                continue;
                break;
            }
        }
        // Moves all students forward
        for (int i = 0; i < m_numStudents; i++) {
            int detector =
                m_numStudents;  // Detect whether a student has reached col 1 and is deleted.
            m_students[i]->moveForward();
            if (m_numStudents != detector) i--;  // If so, move back 1 iteration.
        }
        // A 30% chance for adding a new student
        if (randInt(1, 10) <= 3) addStudent();
    }
    cout << "You lose. Your score is " << m_player->score() << ". Press any key to quit." << endl;
    getchar();
}

//---------------------------Implementions of Student -------------------------------------//
Student::Student(Fmart *fp, int row, int col) {
    m_fp = fp;
    m_row = row;
    m_col = col;
    m_typeWanted = randInt(1, 3);
}

Student::~Student() {
    m_fp = nullptr;
    m_row = m_col = 0;
    m_typeWanted = 0;
}

int Student::row() const { return m_row; }

int Student::col() const { return m_col; }

MEALTYPE Student::typeWanted() const { return m_typeWanted; }

void Student::moveForward() {
    if (--m_col == 1) {
        m_fp->getPlayer()->decLife();
        m_fp->deleteStudent(m_row, m_col);
    }
}

//---------------------------Implementions of Player -------------------------------------//

Player::Player(Fmart *fp) {
    m_row = 2;
    m_col = 1;
    m_lives = 3;
    m_score = 0;
    m_mealInHand = NOTHING;
    m_fp = fp;
}

Player::~Player() {
    m_row = m_col = m_lives = m_score = 0;
    m_mealInHand = 0;
    m_fp = nullptr;
}

int Player::row() const { return m_row; }
int Player::col() const { return m_col; }

int Player::lives() const { return m_lives; }

int Player::score() const { return m_score; }

MEALTYPE Player::mealInHand() const { return m_mealInHand; }

void Player::pickup(MEALTYPE meal) { m_mealInHand = meal; }

void Player::move(int dir) {
    switch (dir) {
        case UP: {
            if (m_row > 1) m_row--;
            break;
        }
        case DOWN: {
            if (m_row < 3) m_row++;
            break;
        }
#ifdef _DEBUG
        default: {
            assert(false);
            break;
        }
#endif
    }
}

void Player::deliver() {
    Student *p = m_fp->getLeftMostStudent(m_row);
    if (!p) return;
    if (m_mealInHand == NOTHING || p->typeWanted() != m_mealInHand) return;
    m_fp->deleteStudent(p->row(), p->col());
    m_score += 10;
    m_mealInHand = NOTHING;
}

void Player::decLife() { m_lives--; }

// ------------------------------Main function--------------------------------------//
int main() {
    srand(time(NULL));
    Fmart f;
    f.play();
}