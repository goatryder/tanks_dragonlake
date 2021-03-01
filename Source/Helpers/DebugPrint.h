#pragma once

#include <iostream>
#include <stdio.h>

#include <windows.h>

using namespace std;

// Successfully stolen from https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout hehe)
inline std::ostream& blue(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
        | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& red(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& green(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& yellow(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& white(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return s;
}
//

typedef std::ostream& (*OSteamChangeColorSig)(std::ostream& s);

enum class PrintColor
{
    Blue,
    Red,
    Green,
    Yellow,
    White
};

inline OSteamChangeColorSig ChangeOutStreamColor(PrintColor Color)
{
    if (Color == PrintColor::Blue) return &blue;
    else if (Color == PrintColor::Red) return &red;
    else if (Color == PrintColor::Green) return &green;
    else if (Color == PrintColor::Yellow) return &yellow;
    else return &white;
}

#define PRINT(PRINT_COLOR, STR) \
 ( \
  (cout << ChangeOutStreamColor(PRINT_COLOR) << (STR) << endl << white), \
  (void)0 \
 )

#define PRINTF(PRINT_COLOR, STR, ...) \
 ( \
  (cout << ChangeOutStreamColor(PRINT_COLOR)), \
  (printf (STR, __VA_ARGS__)), \
  (cout << endl << white), \
  (void)0 \
 )
