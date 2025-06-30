#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

struct student {
    int rollNo;
    char name[50];
    char div[5];
    char address[100];
};

class studentDatabase {
    string fileName = "student_data.dat";

public:
    studentDatabase() {
        fstream fileObj(fileName);
        if (fileObj.fail()) {
            fileObj.open(fileName, ios::out);
            cout << "New file created." << endl;
        } else {
            cout << "File already exists." << endl;
        }
        fileObj.close();
    }

    void addStudent();
    void searchStudent();
    void deleteStudent();
    void displayAll();
};

void studentDatabase::searchStudent() {
    int roll;
    student s;
    bool found = false;

    cout << "Enter Roll Number to search:\t";
    cin >> roll;

    ifstream readFile(fileName, ios::in | ios::binary);
    if (!readFile) {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    while (readFile.read((char*)&s, sizeof(student))) {
        if (s.rollNo == roll) {
            found = true;
            cout << "--- RECORD FOUND ---" << endl;
            cout << "Roll number:\t" << s.rollNo << endl;
            cout << "Name:\t" << s.name << endl;
            cout << "Division:\t" << s.div << endl;
            cout << "Address:\t" << s.address << endl;
            cout << "--- END OF RECORD ---" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Record not found." << endl;
    }

    readFile.close();
}

void studentDatabase::deleteStudent() {
    int roll;
    student s;
    bool found = false;

    cout << "Enter Roll Number to delete:\t";
    cin >> roll;

    ifstream readFile(fileName, ios::in | ios::binary);
    if (!readFile) {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    string tempFile = "temp.dat";
    ofstream writeFile(tempFile, ios::out | ios::binary);

    while (readFile.read((char*)&s, sizeof(student))) {
        if (s.rollNo == roll) {
            found = true;
        } else {
            writeFile.write((char*)&s, sizeof(student));
        }
    }

    readFile.close();
    writeFile.close();

    if (found) {
        remove(fileName.c_str());
        rename(tempFile.c_str(), fileName.c_str());
        cout << "Record deleted successfully." << endl;
    } else {
        cout << "Record not found." << endl;
        remove(tempFile.c_str());  // Delete temp file if record was not found
    }
}

void studentDatabase::addStudent() {
    student s, temp;
    cout << "Enter Roll Number:\t";
    cin >> s.rollNo;
    cin.ignore();  // Ignore newline before reading strings

    cout << "Enter Name:\t";
    cin.getline(s.name, 50);

    cout << "Enter Division:\t";
    cin.getline(s.div, 5);

    cout << "Enter Address:\t";
    cin.getline(s.address, 100);

    // Open original file for reading
    ifstream inFile(fileName, ios::in | ios::binary);
    if (!inFile) {
        cout << "Error: Could not open file for reading!" << endl;
        return;
    }

    // Create temporary file for writing
    string tempFile = "temp.dat";
    ofstream outFile(tempFile, ios::out | ios::binary);
    if (!outFile) {
        cout << "Error: Could not create temporary file!" << endl;
        inFile.close();
        return;
    }

    bool inserted = false;

    // Read records and insert new record at correct position
    while (inFile.read((char*)&temp, sizeof(student))) {
        if (!inserted && temp.rollNo > s.rollNo) {
            // Found the position to insert new record
            outFile.write((char*)&s, sizeof(student));
            inserted = true;
        }
        outFile.write((char*)&temp, sizeof(student));
    }

    // If new record should be at the end
    if (!inserted) {
        outFile.write((char*)&s, sizeof(student));
    }

    inFile.close();
    outFile.close();

    // Replace original file with temporary file
    remove(fileName.c_str());
    rename(tempFile.c_str(), fileName.c_str());

    cout << "Student added successfully." << endl;
}

void studentDatabase::displayAll() {
    ifstream file(fileName, ios::in | ios::binary);
    if (!file) {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    student s;
    int count = 0;

    cout<<"Roll no. | Name  | Div   | Address "<<endl;

    while (file.read((char*)&s, sizeof(student))) {
        count++;
        cout << count << ") " << s.rollNo << "\t | " << s.name << "\t | " << s.div << "\t | " << s.address << endl;
    }

    if (count == 0) {
        cout << "No records found." << endl;
    }

    file.close();
}

int main() {
    int choice;
    studentDatabase db;

    do {
        cout << "\n--- MAIN MENU ---" << endl;
        cout << "1 -> Add record" << endl;
        cout << "2 -> Delete record" << endl;
        cout << "3 -> Search record" << endl;
        cout << "4 -> Display all records" << endl;
        cout << "0 -> Exit" << endl;
        cout << "Choose an option (0-4):\t";
        cin >> choice;

        switch (choice) {
            case 1:
                db.addStudent();
                break;
            case 2:
                db.deleteStudent();
                break;
            case 3:
                db.searchStudent();
                break;
            case 4:
                cout << "All records are:\t" << endl;
                db.displayAll();
                break;
            case 0:
                cout << "\n// END OF CODE\n" << endl;
                break;
            default:
                cout << "Invalid option! Please choose between 0-4." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
