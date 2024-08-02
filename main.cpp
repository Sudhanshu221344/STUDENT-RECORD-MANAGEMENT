#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip> // For setw and left

using namespace std;

struct Student {
    string roll_no;
    string name;
    string Class;
    string course;
    string mobile_no;
    string admission_year;
};

vector<Student> students;

void enter() {
    int ch = 0;
    cout << "How many students do you want to enter?" << endl;
    cin >> ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    for(int i = 0; i < ch; i++) {
        Student s;
        cout << "\nEnter the Data of student " << i + 1 << endl << endl;
        cout << "Enter Roll NO: ";
        getline(cin, s.roll_no);
        cout << "Enter Name: ";
        getline(cin, s.name);
        cout << "Enter Class: ";
        getline(cin, s.Class);
        cout << "Enter Course: ";
        getline(cin, s.course);
        cout << "Enter Mobile NO: ";
        getline(cin, s.mobile_no);
        cout << "Enter Admission Year: ";
        getline(cin, s.admission_year);
        students.push_back(s);
    }
}

void show() {
    if (students.empty()) {
        cout << "No Data is Entered" << endl;
    } else {
        cout << "--------------------------------------------------------------------------" << endl;
        cout << "| Roll NO | Name           | Class | Course | Mobile NO | Admission Year |" << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        for (const auto& student : students) {
            cout << "| " << student.roll_no << " | "
                 << setw(15) << left << student.name << " | "
                 << setw(6) << left << student.Class << " | "
                 << setw(7) << left << student.course << " | "
                 << setw(10) << left << student.mobile_no << " | "
                 << setw(14) << left << student.admission_year << " |" << endl;
        }
        cout << "--------------------------------------------------------------------------" << endl;
    }
}

void search() {
    if (students.empty()) {
        cout << "No data is entered" << endl;
    } else {
        string rollno;
        cout << "Enter the roll no of student" << endl;
        cin >> rollno;
        bool found = false;
        for (const auto& student : students) {
            if (rollno == student.roll_no) {
                cout << "Roll NO: " << student.roll_no << endl;
                cout << "Name: " << student.name << endl;
                cout << "Class: " << student.Class << endl;
                cout << "Course: " << student.course << endl;
                cout << "Mobile NO: " << student.mobile_no << endl;
                cout << "Admission Year: " << student.admission_year << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "No student found with Roll NO: " << rollno << endl;
        }
    }
}

void update() {
    if (students.empty()) {
        cout << "No data is entered" << endl;
    } else {
        string rollno;
        cout << "Enter the roll no of student which you want to update" << endl;
        cin >> rollno;
        bool found = false;
        for (auto& student : students) {
            if (rollno == student.roll_no) {
                cout << "\nPrevious data" << endl << endl;
                cout << "Data of Student" << endl;
                cout << "Roll NO: " << student.roll_no << endl;
                cout << "Name: " << student.name << endl;
                cout << "Class: " << student.Class << endl;
                cout << "Course: " << student.course << endl;
                cout << "Mobile NO: " << student.mobile_no << endl;
                cout << "Admission Year: " << student.admission_year << endl;
                cout << "\nEnter new data" << endl << endl;
                cout << "Enter Roll NO: ";
                cin >> student.roll_no;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cout << "Enter Name: ";
                getline(cin, student.name);
                cout << "Enter Class: ";
                getline(cin, student.Class);
                cout << "Enter Course: ";
                getline(cin, student.course);
                cout << "Enter Mobile NO: ";
                getline(cin, student.mobile_no);
                cout << "Enter Admission Year: ";
                getline(cin, student.admission_year);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "No student found with Roll NO: " << rollno << endl;
        }
    }
}

void Delete() {
    if (students.empty()) {
        cout << "No data is entered yet" << endl;
    } else {
        int a;
        cout << "Are you Sure to Delete Data?" << endl;
        cout << "Press 1 to delete all records" << endl;
        cin >> a;
        if (a == 1) {
            students.clear();
            cout << "All records are deleted..!!" << endl;
        } else {
            cout << "Please Press 1 to Delete All Records" << endl;
        }
    }
}

void saveToFile() {
    ofstream outFile("students.txt");
    for (const auto& student : students) {
        outFile << student.roll_no << ","
                << student.name << ","
                << student.Class << ","
                << student.course << ","
                << student.mobile_no << ","
                << student.admission_year << endl;
    }
    outFile.close();
    cout << "Data saved to file successfully." << endl;
}

void loadFromFile() {
    ifstream inFile("students.txt");
    Student s;
    string line;
    while (getline(inFile, line)) {
        size_t pos = 0;
        vector<string> data;
        while ((pos = line.find(',')) != string::npos) {
            data.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        data.push_back(line); // Last element
        if (data.size() == 6) { // Ensure all fields are present
            s.roll_no = data[0];
            s.name = data[1];
            s.Class = data[2];
            s.course = data[3];
            s.mobile_no = data[4];
            s.admission_year = data[5];
            students.push_back(s);
        }
    }
    inFile.close();
    cout << "Data loaded from file successfully." << endl;
}

void sortStudents() {
    if (students.empty()) {
        cout << "No data to sort." << endl;
        return;
    }
    int choice;
    cout << "Sort by:\n1. Roll No\n2. Name\n3. Admission Year\nChoose an option: ";
    cin >> choice;
    switch (choice) {
        case 1:
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.roll_no < b.roll_no;
            });
            break;
        case 2:
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.name < b.name;
            });
            break;
        case 3:
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.admission_year < b.admission_year;
            });
            break;
        default:
            cout << "Invalid choice." << endl;
            return;
    }
    cout << "Students sorted successfully." << endl;
}

void showStatistics() {
    cout << "Total number of students: " << students.size() << endl;
    // Additional statistics can be added here
}

int main() {
    loadFromFile();
    int value;
    while (true) {
        cout << "\nPress 1 to Enter data" << endl;
        cout << "Press 2 to Show data" << endl;
        cout << "Press 3 to Search data" << endl;
        cout << "Press 4 to Update data" << endl;
        cout << "Press 5 to Delete data" << endl;
        cout << "Press 6 to Save data to file" << endl;
        cout << "Press 7 to Sort students" << endl;
        cout << "Press 8 to Show Statistics" << endl;
        cout << "Press 9 to Quit" << endl;
        cin >> value;
        switch (value) {
            case 1:
                enter();
                break;
            case 2:
                show();
                break;
            case 3:
                search();
                break;
            case 4:
                update();
                break;
            case 5:
                Delete();
                break;
            case 6:
                saveToFile();
                break;
            case 7:
                sortStudents();
                break;
            case 8:
                showStatistics();
                break;
            case 9:
                saveToFile();
                exit(0);
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }
}
