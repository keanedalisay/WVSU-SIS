// Program Title: WVSU-SIS (Student Information System)
// Submitted by: Keane Dalisay

// Program Description: WVSU-SIS is a C++ based program designed
// to store, retrieve, and print student as well as teacher info.

#include <iostream>
#include <fstream>
#include "json.hpp"

void welcomeMsg();
void loginOrSignup();

void doSignup();
void doLogin();
void doExitProgram();

void getFileName(std::string &fileName);
void getWhatName(std::string whatName, std::string &name);
void getUniID(std::string &uniID);
void getPassword(std::string &password);

void getOccup(std::string &occup);

void getYearLevel(std::string &yrLvl, std::string &course);
void getCourse(std::string &course);

void getSubjects(std::string var[]);

bool isNotEmptyFile(std::ifstream &file);
bool isYes(char choice);

void pressEnterToContinue();

void createThematicBreak();

int main()
{
    welcomeMsg();
    loginOrSignup();
    return 0;
}

namespace SIS
{
    using std::string;

    struct stdntTemp
    {
        string fName;
        string mName;
        string lName;
        string uniID;
        string yrLvl;
        string course;
        string password;
    };

    struct teachrTemp
    {
        string fName;
        string mName;
        string lName;
        string uniID;
        string subjects[5];
        string password;
    };
}

void welcomeMsg()
{
    using std::cout;
    char choice;

    createThematicBreak();
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
        cout << "\n- It uses json (Javascript Object Notation) to store that information...";
        cout << "\n- Hence, this program requires a file of that type to write and store data...";
        cout << "\n- End of story, hope you liked it.";
        pressEnterToContinue();
    }
}

void loginOrSignup()
{
    using std::cout;
    int choice;

    cout << "\nWhich option would you like to choose?";
    cout << "\n\n> Log-in (1)";
    cout << "\n> Sign-up (2)";
    cout << "\n> Exit (3)";

    cout << "\n\n: ";
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        doLogin();
        break;
    case 2:
        doSignup();
        break;
    case 3:
        doExitProgram();
        break;
    default:
        doExitProgram();
    }
}

void doSignup()
{
    using std::cin;
    using std::cout;
    using std::string;
    using json = nlohmann::ordered_json;

    string fName, mName, lName, fileName;
    string occup, uniID, password;
    string yrLvl, course;
    string subjects[5];
    char choice;

    json data;

    getFileName(fileName);

    std::ifstream jsonInpFile(fileName);
    if (isNotEmptyFile(jsonInpFile))
    {
        jsonInpFile >> data;
    }
    jsonInpFile.close();

    getWhatName("first", fName);

    cout << "\nDo you have a middle name? (y/n): ";
    cin >> choice;
    cin.ignore(1000, '\n');
    if (isYes(choice))
    {
        getWhatName("middle", mName);
    }

    getWhatName("last", lName);

    getUniID(uniID);
    getPassword(password);
    getOccup(occup);

    int arrIndx = 0;
    for (auto &item : data[occup].items())
    {
        arrIndx++;
    }

    if (occup == "students")
    {
        getYearLevel(yrLvl, course);
        SIS::stdntTemp user = {fName, mName, lName, uniID, yrLvl, course, password};
        data[occup][arrIndx] = {
            {"fName", user.fName},
            {"mName", user.mName},
            {"lName", user.lName},
            {"uniID", user.uniID},
            {"yrLvl", user.yrLvl},
            {"course", user.course},
            {"password", user.password}};
    }
    else if (occup == "teachers")
    {
        getSubjects(subjects);
        SIS::teachrTemp user = {
            fName,
            mName,
            lName,
            uniID,
            {subjects[0], subjects[1], subjects[2], subjects[3], subjects[4]},
            password};

        data[occup][arrIndx] = {
            {"fName", user.fName},
            {"mName", user.mName},
            {"lName", user.lName},
            {"uniID", user.uniID},
            {"subjects", user.subjects},
            {"password", user.password}};
    }

    std::ofstream jsonOutFile(fileName);
    jsonOutFile << data.dump(2, ' ');
    jsonOutFile.close();

    doExitProgram();
}

void doLogin()
{
}

void doExitProgram()
{
    createThematicBreak();
    std::cout << "\nSuccessfully exited program.\n\n";
}

// helper functions below this comment

void getFileName(std::string &fileName)
{
    std::cout << "\nEnter your file name.";
    std::cout << "\n(must end with .json): ";
    std::cin >> fileName;
    std::cin.ignore(1000, '\n');
}

void getWhatName(std::string whatName, std::string &name)
{
    std::cout << "\nEnter your " + whatName + " name: ";
    std::getline(std::cin, name);
}

void getOccup(std::string &occup)
{
    char occupChoice;
    std::cout << "\nAre you a student or teacher?";
    std::cout << "\n(s/t): ";
    std::cin >> occupChoice;
    std::cin.ignore(1000, '\n');

    if (tolower(occupChoice) == 's')
        occup = "students";
    else if (tolower(occupChoice) == 't')
        occup = "teachers";
    else
        doExitProgram();
}

void getYearLevel(std::string &yrLvl, std::string &course)
{
    using std::cin;
    using std::cout;
    char crntEdu;

    cout << "\nAre you an elementary, junior high, senior high, or college student?";
    cout << "\n(e/j/s/c): ";
    cin >> crntEdu;
    cin.ignore(1000, '\n');

    switch (tolower(crntEdu))
    {
    case 'e':
    {
        cout << "\nWhat year level are you currently?";
        cout << "\n(specify Grade 6 if so): ";
        std::getline(cin, yrLvl);
        break;
    }
    case 'j':
    {
        cout << "\nWhat year level are you currently?";
        cout << "\n(specify Grade 7 if so): ";
        std::getline(cin, yrLvl);
        break;
    }
    case 's':
    {
        cout << "\nWhat year level are you currently?";
        cout << "\n(specify Grade 11 if so): ";
        std::getline(cin, yrLvl);
        getCourse(course);
        break;
    }
    case 'c':
    {
        cout << "\nWhat college level are you currently?";
        cout << "\n(specify Freshman if so): ";
        std::getline(cin, yrLvl);
        getCourse(course);
        break;
    }
    }
}

void getCourse(std::string &course)
{
    std::cout << "\nWhat senior high or college course are you currently taking?";
    std::cout << "\n(STEM/Bachelor of...): ";
    std::getline(std::cin, course);
}

void getSubjects(std::string subjects[])
{
    using std::cin;
    using std::cout;

    int numOfSubj, arrIndx = 0;
    cout << "\nSpecify the number of subjects you are teaching currently.";
    cout << "\n(max is 5): ";
    cin >> numOfSubj;
    cin.ignore(1000, '\n');

    if (numOfSubj > 5)
    {
        cout << "\nYou entered more than 5 subjects!";
        cout << "\nRe-routing you to re-enter your subjects...";
        pressEnterToContinue();

        getSubjects(subjects);
        return;
    }
    else if (numOfSubj <= 0)
    {
        cout << "\nYou entered a number below or equal to 0!";
        cout << "\nRe-routing you to re-enter your subjects...";
        pressEnterToContinue();

        getSubjects(subjects);
        return;
    }

    numOfSubj -= 1;
    while (arrIndx <= numOfSubj)
    {
        cout << "\nType in the subject (add one at a time): ";
        cin >> subjects[arrIndx];
        cin.ignore(1000, '\n');
        arrIndx += 1;
    }
}

void getUniID(std::string &uniID)
{
    std::cout << "\nType in your university identification number: ";
    std::cin >> uniID;
    std::cin.ignore(1000, '\n');
}

void getPassword(std::string &password)
{
    using std::cin;
    using std::cout;
    using std::string;

    string firstPassword, finalPassword;
    cout << "\nEnter your new password: ";
    cin >> firstPassword;
    cin.ignore(1000, '\n');

    cout << "\nEnter your password again: ";
    cin >> finalPassword;
    cin.ignore(1000, '\n');

    if (firstPassword == finalPassword)
    {
        password = finalPassword;
        cout << "\nPassword entered matches...";
        pressEnterToContinue();
    }
    else
    {
        cout << "\nPassword entered does not match!\n";
        cout << "\nRe-routing you to re-enter password...";
        pressEnterToContinue();
        getPassword(password);
    }
}

bool isNotEmptyFile(std::ifstream &file)
{
    return file.peek() != std::ifstream::traits_type::eof();
}

bool isYes(char choice)
{
    char finalChoice = tolower(choice);
    if (finalChoice == 'y')
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

void createThematicBreak()
{
    using std::cout;
    cout << "\n";
    char dash = '-';
    int dashCount = 0;
    while (dashCount <= 50)
    {
        cout << dash;
        dashCount += 1;
    }
    cout << "\n";
}