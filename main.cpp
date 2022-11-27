// Program Title: West Visayas State University Student Information System
// Submitted by: Keane Dalisay

// Program Description: WVSU-SIS is a C++ based program designed
// to store, retrieve, and print student as well as teacher info.

#include <iostream>
#include <fstream>
#include "json.hpp"

void displayWelcomeDshbrd();
void loginOrSignup();

void doSignup();
void doLogin();
void doLogout(std::string fullname, std::string uniID, char occup);

void displayStudentDshbrd(std::string fullName, std::string uniID);
void displayTeacherDshbrd(std::string fullName, std::string uniID);

void exitProgram();

namespace feat
{
    void pressEnterToContinue()
    {
        std::cin.clear();
        std::cout << "\n\nPress enter to continue... ";
        std::cin.ignore(1000, '\n');
        return;
    }

    void newThematicBreak(char symbol)
    {
        using std::cout;
        cout << "\n";
        char dash = symbol;
        int dashCount = 0;
        while (dashCount <= 50)
        {
            cout << dash;
            dashCount += 1;
        }
        cout << "\n";
        return;
    }
}

namespace help
{
    void getFileName(std::string &fileName)
    {
        std::cout << "\nEnter your file name.";
        std::cout << "\n(must end with .json): ";
        std::cin >> fileName;
        std::cin.ignore(1000, '\n');
        return;
    }

    void getWhatName(std::string whatName, std::string &name)
    {
        std::cout << "\nEnter your " + whatName + " name: ";
        std::getline(std::cin, name);
        return;
    }

    void getOccupation(std::string &occup)
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
            exitProgram();

        return;
    }

    void getCourse(std::string &course)
    {
        std::cout << "\nWhat senior high or college course are you currently taking?";
        std::cout << "\n(STEM/Bachelor of...): ";
        std::getline(std::cin, course);
        return;
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
            feat::pressEnterToContinue();

            help::getSubjects(subjects);
            return;
        }
        else if (numOfSubj <= 0)
        {
            cout << "\nYou entered a number below or equal to 0!";
            cout << "\nRe-routing you to re-enter your subjects...";
            feat::pressEnterToContinue();

            help::getSubjects(subjects);
            return;
        }

        while (arrIndx < numOfSubj)
        {
            cout << "\nType in the subject (add one at a time): ";
            cin >> subjects[arrIndx];
            cin.ignore(1000, '\n');
            arrIndx += 1;
        }

        return;
    }

    void getYearLevel(std::string &yearLevel, std::string &course)
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
            std::getline(cin, yearLevel);
            break;
        }
        case 'j':
        {
            cout << "\nWhat year level are you currently?";
            cout << "\n(specify Grade 7 if so): ";
            std::getline(cin, yearLevel);
            break;
        }
        case 's':
        {
            cout << "\nWhat year level are you currently?";
            cout << "\n(specify Grade 11 if so): ";
            std::getline(cin, yearLevel);
            getCourse(course);
            break;
        }
        case 'c':
        {
            cout << "\nWhat college level are you currently?";
            cout << "\n(specify Freshman if so): ";
            std::getline(cin, yearLevel);
            getCourse(course);
            break;
        }
        }

        return;
    }

    void getUniID(std::string &uniID)
    {
        std::cout << "\nType in your university identification number: ";
        std::cin >> uniID;
        std::cin.ignore(1000, '\n');
        return;
    }

    void getPassword(std::string &password, bool isLoggingIn)
    {
        using std::cin;
        using std::cout;
        using std::string;

        string firstPassword, finalPassword;

        if (isLoggingIn)
        {
            string itemPassword = password;

            cout << "\nEnter your password: ";
            cin >> finalPassword;
            cin.ignore(1000, '\n');

            if (finalPassword == itemPassword)
            {
                cout << "\nLogged in successfully...";
                feat::pressEnterToContinue();

                feat::newThematicBreak('*');
                return;
            }
            cout << "\nPassword entered does not match!";
            cout << "\nRe-routing you to re-enter password...";
            feat::pressEnterToContinue();

            help::getPassword(itemPassword, true);
            return;
        }

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
            feat::pressEnterToContinue();
        }
        else
        {
            cout << "\nPassword entered does not match!\n";
            cout << "\nRe-routing you to re-enter password...";
            feat::pressEnterToContinue();
            help::getPassword(password, false);
        }

        return;
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
        string yearLevel;
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

namespace jsonManip
{
    using json = nlohmann::ordered_json;

    void getData(json &data, std::string fileName)
    {
        std::ifstream jsonInpFile(fileName);

        if (help::isNotEmptyFile(jsonInpFile))
        {
            jsonInpFile >> data;
        }

        jsonInpFile.close();
        return;
    }

    void dumpData(json &data, std::string fileName)
    {
        std::ofstream jsonOutFile(fileName);
        jsonOutFile << data.dump(2, ' ');

        jsonOutFile.close();
        return;
    }

    int getNxtArrIndx(std::string occup, std::string fileName)
    {
        json data;

        getData(data, fileName);

        int arrIndx = 0;
        for (auto &item : data[occup].items())
        {
            arrIndx++;
        }

        return arrIndx;
    }

    void storeStdnt(SIS::stdntTemp stdnt, std::string fileName)
    {
        json data;

        getData(data, fileName);

        data["students"][getNxtArrIndx("students", fileName)] = {
            {"fName", stdnt.fName},
            {"mName", stdnt.mName},
            {"lName", stdnt.lName},
            {"uniID", stdnt.uniID},
            {"yearLevel", stdnt.yearLevel},
            {"course", stdnt.course},
            {"password", stdnt.password}};

        dumpData(data, fileName);

        return;
    }

    void storeTeachr(SIS::teachrTemp teachr, std::string fileName)
    {
        json data;

        getData(data, fileName);

        data["teachers"][getNxtArrIndx("teachers", fileName)] = {
            {"fName", teachr.fName},
            {"mName", teachr.mName},
            {"lName", teachr.lName},
            {"uniID", teachr.uniID},
            {"subjects", teachr.subjects},
            {"password", teachr.password}};

        dumpData(data, fileName);

        return;
    }

    bool confirmLogIn(std::string occup, std::string uniID, std::string fileName)
    {
        using std::string;
        json data;

        getData(data, fileName);

        int arrIndx = 0;
        for (auto &item : data[occup].items())
        {
            string itemUniID = data[occup][arrIndx]["uniID"];
            string itemPassword = data[occup][arrIndx]["password"];

            if (itemUniID == uniID)
            {
                help::getPassword(itemPassword, true);
                return true;
            }

            arrIndx += 1;
            continue;
        }

        return false;
    }

    std::string getUserFullName(std::string occup, std::string uniID, std::string fileName)
    {
        using std::string;
        string fullName = " ";

        json data;

        getData(data, fileName);

        int arrIndx = 0;
        for (auto &item : data[occup].items())
        {
            string itemUniID = data[occup][arrIndx]["uniID"];

            if (itemUniID == uniID)
            {
                string fName = data[occup][arrIndx]["fName"];
                string mName = data[occup][arrIndx]["mName"];
                string lName = data[occup][arrIndx]["lName"];

                fullName = fName + " " + mName + " " + lName;
                break;
            }

            arrIndx += 1;
            continue;
        }

        return fullName;
    }
}

int main()
{
    displayWelcomeDshbrd();
    return 0;
}

void displayWelcomeDshbrd()
{
    using feat::pressEnterToContinue;
    using std::cout;

    char choice;

    feat::newThematicBreak('-');

    cout << "\nWelcome to WVSU-SIS.";
    pressEnterToContinue();

    cout << "\nWould you like to know the history of this program? (y/n): ";
    std::cin >> choice;
    std::cin.ignore(1000, '\n');

    if (help::isYes(choice))
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

    loginOrSignup();
    return;
}

void loginOrSignup()
{
    using std::cin;
    using std::cout;
    int choice;

    cout << "\nWhich option would you like to choose?";
    cout << "\n\n> Log-in (1)";
    cout << "\n> Sign-up (2)";
    cout << "\n> Exit (3)";

    cout << "\n\n: ";
    cin >> choice;
    cin.ignore(1000, '\n');

    switch (choice)
    {
    case 1:
        doLogin();
        break;
    case 2:
        doSignup();
        break;
    case 3:
        exitProgram();
        break;
    default:
        exitProgram();
        break;
    }

    return;
}

void doSignup()
{
    using help::getWhatName;
    using std::cin;
    using std::cout;
    using std::string;

    feat::newThematicBreak('*');

    string fName, mName, lName, fileName;
    string occup, uniID, password;
    string yearLevel, course;
    string subjects[5];
    char choice;

    help::getFileName(fileName);

    getWhatName("first", fName);

    cout << "\nDo you have a middle name?";
    cout << "\n(y/n): ";
    cin >> choice;
    cin.ignore(1000, '\n');

    if (help::isYes(choice))
    {
        getWhatName("middle", mName);
    }

    getWhatName("last", lName);

    string fullName = fName + " " + mName + " " + lName;

    help::getUniID(uniID);
    help::getPassword(password, false);
    help::getOccupation(occup);

    if (occup == "students")
    {
        help::getYearLevel(yearLevel, course);
        SIS::stdntTemp stdnt = {fName, mName, lName, uniID, yearLevel, course, password};

        jsonManip::storeStdnt(stdnt, fileName);

        feat::newThematicBreak('*');
        displayStudentDshbrd(fullName, uniID);
        return;
    }

    help::getSubjects(subjects);
    SIS::teachrTemp teachr = {
        fName,
        mName,
        lName,
        uniID,
        {subjects[0], subjects[1], subjects[2], subjects[3], subjects[4]},
        password};

    jsonManip::storeTeachr(teachr, fileName);

    feat::newThematicBreak('*');
    displayTeacherDshbrd(fullName, uniID);
    return;
}

void doLogin()
{
    using jsonManip::confirmLogIn;
    using std::cin;
    using std::cout;
    using std::string;

    feat::newThematicBreak('*');

    string fileName;
    string occup, uniID, password;
    char choice;
    int arrIndx = 0;

    help::getFileName(fileName);
    help::getUniID(uniID);
    help::getOccupation(occup);

    if (confirmLogIn(occup, uniID, fileName))
    {
        string fullName = jsonManip::getUserFullName(occup, uniID, fileName);

        if (occup == "students")
            displayStudentDshbrd(fullName, uniID);
        else
            displayTeacherDshbrd(fullName, uniID);

        return;
    }

    cout << "\nThe university identification number you entered...";
    cout << "\nDoes not match any of our pre-existing users...";
    feat::pressEnterToContinue();

    cout << "\nWould you like to try and log-in again?";
    cout << "\n(y/n): ";
    cin >> choice;
    cin.ignore(1000, '\n');

    if (help::isYes(choice))
    {
        doLogin();
        return;
    }

    exitProgram();
    return;
}

void displayStudentDshbrd(std::string fullName, std::string uniID)
{
    using feat::pressEnterToContinue;
    using std::cin;
    using std::cout;
    using std::string;

    string teacherUniID = uniID;
    string teacherFullName = fullName;
    int choice;

    cout << "\n----- Welcome " << fullName << " -----";
    pressEnterToContinue();

    cout << "\nPlease choose an option you would like to do below...";
    cout << "\n\n> Print your info (1)";
    cout << "\n> Print your grades (2)";
    cout << "\n> Study (3)";
    cout << "\n> Log Out (4)";

    cout << "\n\n: ";
    cin >> choice;
    cin.ignore(1000, '\n');

    switch (choice)
    {
    case 1:
    case 2:
        cout << "\n- Sorry, this feature was intentionally not implemented...";
        pressEnterToContinue();
        cout << "\n- I (Keane) would have liked to...";
        cout << "\n- But C++ development is not my focus as of writing (11/26/2022)...";
        pressEnterToContinue();
        cout << "\n- Hope you understand... re-routing you to student dashboard...";
        pressEnterToContinue();

        displayStudentDshbrd(teacherFullName, teacherUniID);
        break;
    case 3:
        cout << "\n Temp";
        break;
    case 4:
        doLogout(teacherFullName, teacherUniID, 's');
        break;
    }

    return;
}

void displayTeacherDshbrd(std::string fullName, std::string uniID)
{
    using feat::pressEnterToContinue;
    using std::cin;
    using std::cout;
    using std::string;

    string teacherUniID = uniID;
    string teacherFullName = fullName;
    int choice;

    cout << "\n----- Welcome " << fullName << " -----";
    pressEnterToContinue();

    cout << "\nPlease choose an option you would like to do below...";
    cout << "\n\n> Print your info (1)";
    cout << "\n> Assign student grades (2)";
    cout << "\n> Drink coffee (3)";
    cout << "\n> Log Out (4)";

    cout << "\n\n: ";
    cin >> choice;
    cin.ignore(1000, '\n');

    switch (choice)
    {
    case 1:
    case 2:
        cout << "\n- Sorry, this feature was intentionally not implemented...";
        pressEnterToContinue();
        cout << "\n- I (Keane) would have liked to...";
        cout << "\n- But C++ development is not my focus as of writing (11/26/2022)...";
        pressEnterToContinue();
        cout << "\n- Hope you understand... re-routing you to teacher dashboard...";
        pressEnterToContinue();

        displayTeacherDshbrd(teacherFullName, teacherUniID);
        break;
    case 3:
        cout << "\n Temp";
        break;
    case 4:
        doLogout(teacherFullName, teacherUniID, 't');
        break;
    }

    return;
}

void doLogout(std::string fullName, std::string uniID, char occup)
{
    using feat::pressEnterToContinue;
    using std::cin;
    using std::cout;

    char choice;
    cout << "\nAre you sure you want to log-out?";
    cout << "\n(y/n): ";
    cin >> choice;
    cin.ignore(1000, '\n');

    if (help::isYes(choice))
    {
        cout << "\nRe-routing you to welcome dashboard...";
        pressEnterToContinue();

        cout << "\n----- Logging out as " + fullName + " -----";
        pressEnterToContinue();

        displayWelcomeDshbrd();
        return;
    }

    switch (occup)
    {
    case 's':
        displayStudentDshbrd(fullName, uniID);
        break;
    case 't':
        displayTeacherDshbrd(fullName, uniID);
        break;
    }

    return;
}

void exitProgram()
{
    feat::newThematicBreak('-');
    std::cout << "\nSuccessfully exited program.\n\n";
    return;
}