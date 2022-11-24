// Program Title: WVSU-SIS (Student Information System)
// Submitted by: Keane Dalisay

// Program Description: WVSU-SIS is a C++ based program designed
// to store, retrieve, and print student as well as teacher info.

#include <iostream>
#include <fstream>
#include <limits>
#include "json.hpp"

void welcomeMsg();
void pressEnterToContinue();
bool isYes(char);

int main()
{
    welcomeMsg();
    return 0;
}

void welcomeMsg()
{
    using std::cout;
    char choice;

    cout << "\nWelcome to WVSU-SIS.";
    pressEnterToContinue();
    cout << "\nWould you like to know the history of this program? (y/n): ";

    std::cin >> choice;
    std::cin.ignore(1000, '\n');
    if (isYes(choice))
    {
        cout << "\n- WVSU-SIS stands for West Visayas State University Student Information System (not official)...";
        cout << "\n- This program was spearheaded by Keane Dalisay along with Nel Alanan...";
        pressEnterToContinue();
        cout << "\n- Both took Bachelor of Science in Computer Science as their desired college course...";
        pressEnterToContinue();
        cout << "\n- This program was built as a requirement for the subject CC 202 (Computer Programming 1)...";
        pressEnterToContinue();
        cout << "\n- Its purpose? An information system where students and teachers can look up their university profiles...";
        pressEnterToContinue();
        cout << "\n- It uses JSON (Javascript Object Notation) to store that information...";
        cout << "\n- Hence, this program requires a file of that type to write and store data...";
        cout << "\n- End of story, hope you liked it.";
        pressEnterToContinue();
    }
}

// helper functions below this comment

bool isYes(char choice)
{
    if (tolower(choice) == 'y')
    {
        return true;
    }
    return false;
}

void pressEnterToContinue()
{
    std::cin.clear();
    std::cout << "\nPress enter to continue... ";
    std::cin.ignore(1000, '\n');
}