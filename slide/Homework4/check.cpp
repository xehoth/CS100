#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <Windows.h>

void setWhite() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
                                                                 FOREGROUND_GREEN |
                                                                 FOREGROUND_BLUE);
}

void setRed() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
}

void setGreen() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_GREEN);
}

int main() {
    for (int i = 0; i < 1000; i++) {
        setWhite();
        std::cout << "Testing case " << i << ": ";
        system("gen.exe > tmp.in");
        auto now = time(NULL);
        for (auto tmp = time(NULL); now == tmp;) tmp = time(NULL);
        system("std.exe < tmp.in > std.out && ex2rad.exe < tmp.in > me.out");
        std::ifstream a("std.out"), b("me.out");
        std::stringstream sa, sb;
        sa << a.rdbuf();
        sb << b.rdbuf();
        if (sa.str() != sb.str()) {
            setRed();
            std::cout << "Wrong answer on test " << i << std::endl;
            setWhite();
            return 0;
        }
        setWhite();
        std::cout << "The output is: " << std::endl << sa.str() << std::endl;
        setGreen();
        std::cout << "Test " << i << " Accepted!!!" << std::endl << std::endl;
    }
    setWhite();
}