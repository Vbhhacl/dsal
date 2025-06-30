#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;

class EMP_CLASS
{
    typedef struct EMPLOYEE
    {
        char name[10];
        int emp_id;
        int salary;
    } Rec;

    typedef struct INDEX
    {
        int emp_id;
        int position;
    } Ind_Rec;

    Rec Records;
    Ind_Rec Ind_Records;

public:
    EMP_CLASS();
    void Create();
    void Display();
    void Update();
    void Delete();
    void Append();
    void Search();
};

EMP_CLASS::EMP_CLASS()
{
    strcpy(Records.name, "");
}

void EMP_CLASS::Create()
{
    int i = 0;
    char ch = 'y';
    fstream seqfile;
    fstream indexfile;
    indexfile.open("IND.DAT", ios::out);
    seqfile.open("EMP.DAT", ios::out);

    do
    {
        cout << "Enter Name: ";
        cin >> Records.name;
        cout << "Enter Emp_ID: ";
        cin >> Records.emp_id;
        cout << "Enter Salary: ";
        cin >> Records.salary;
        seqfile.write((char*)&Records, sizeof(Records));
        Ind_Records.emp_id = Records.emp_id;
        Ind_Records.position = i;
        indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));
        i++;
        cout << "Add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y');

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Display()
{
    fstream seqfile;
    fstream indexfile;
    seqfile.open("EMP.DAT", ios::in | ios::binary);
    indexfile.open("IND.DAT", ios::in | ios::binary);
    indexfile.seekg(0, ios::beg);
    seqfile.seekg(0, ios::beg);
    cout << "\nEmployee Records:\n";
    cout << left << setw(10) << "Name" << setw(8) << "Emp_ID" << setw(8) << "Salary" << endl;
    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
    {
        int i = Ind_Records.position * sizeof(Rec);
        seqfile.seekg(i, ios::beg);
        seqfile.read((char*)&Records, sizeof(Records));

        if (Records.emp_id != -1)
        {
            cout << left << setw(10) << Records.name 
                 << setw(8) << Records.emp_id 
                 << setw(8) << Records.salary << endl;
        }
    }
    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Update()
{
    int pos, id;
    char New_name[10];
    int New_salary;
    cout << "\nEnter Emp_ID to update: ";
    cin >> id;
    fstream seqfile;
    fstream indexfile;
    seqfile.open("EMP.DAT", ios::in | ios::out | ios::binary);
    indexfile.open("IND.DAT", ios::in | ios::out | ios::binary);
    indexfile.seekg(0, ios::beg);

    pos = -1;
    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
    {
        if (id == Ind_Records.emp_id)
        {
            pos = Ind_Records.position;
            break;
        }
    }
    if (pos == -1)
    {
        cout << "Record not found";
        return;
    }
    else
    {
        cout << "Enter new Name: ";
        cin >> New_name;
        cout << "Enter new Salary: ";
        cin >> New_salary;
        int offset = pos * sizeof(Rec);
        seqfile.seekp(offset);
        strcpy(Records.name, New_name);
        Records.emp_id = id;
        Records.salary = New_salary;
        seqfile.write((char*)&Records, sizeof(Records));
        cout << "Record updated";
    }
    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Delete()
{
    int id, pos;
    cout << "\nEnter Emp_ID to delete: ";
    cin >> id;
    fstream seqfile;
    fstream indexfile;
    seqfile.open("EMP.DAT", ios::in | ios::out | ios::binary);
    indexfile.open("IND.DAT", ios::in | ios::out | ios::binary);
    pos = -1;
    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
    {
        if (id == Ind_Records.emp_id)
        {
            pos = Ind_Records.position;
            Ind_Records.emp_id = -1;
            break;
        }
    }
    if (pos == -1)
    {
        cout << "Record not found";
        return;
    }
    int offset = pos * sizeof(Rec);
    seqfile.seekp(offset);
    strcpy(Records.name, "");
    Records.emp_id = -1;
    Records.salary = -1;
    seqfile.write((char*)&Records, sizeof(Records));
    offset = pos * sizeof(Ind_Rec);
    indexfile.seekp(offset);
    Ind_Records.emp_id = -1;
    Ind_Records.position = pos;
    indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));
    seqfile.close();
    indexfile.close();
    cout << "Record deleted";
}

void EMP_CLASS::Append()
{
    fstream seqfile;
    fstream indexfile;
    int pos;
    indexfile.open("IND.DAT", ios::in | ios::binary);
    indexfile.seekg(0, ios::end);
    pos = indexfile.tellg() / sizeof(Ind_Records);
    indexfile.close();

    indexfile.open("IND.DAT", ios::app | ios::binary);
    seqfile.open("EMP.DAT", ios::app | ios::binary);

    cout << "Enter Name: ";
    cin >> Records.name;
    cout << "Enter Emp_ID: ";
    cin >> Records.emp_id;
    cout << "Enter Salary: ";
    cin >> Records.salary;
    seqfile.write((char*)&Records, sizeof(Records));
    Ind_Records.emp_id = Records.emp_id;
    Ind_Records.position = pos;
    indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));
    seqfile.close();
    indexfile.close();
    cout << "Record appended";
}

void EMP_CLASS::Search()
{
    fstream seqfile;
    fstream indexfile;
    int id, pos;
    cout << "Enter Emp_ID to search: ";
    cin >> id;
    indexfile.open("IND.DAT", ios::in | ios::binary);
    pos = -1;
    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
    {
        if (id == Ind_Records.emp_id)
        {
            pos = Ind_Records.position;
            break;
        }
    }
    if (pos == -1)
    {
        cout << "Record not found";
        return;
    }
    int offset = pos * sizeof(Records);
    seqfile.open("EMP.DAT", ios::in | ios::binary);
    seqfile.seekg(offset, ios::beg);
    seqfile.read((char*)&Records, sizeof(Records));
    if (Records.emp_id == -1)
    {
        cout << "Record not found";
    }
    else
    {
        cout << "\nRecord found:";
        cout << "\nName: " << Records.name;
        cout << "\nEmp_ID: " << Records.emp_id;
        cout << "\nSalary: " << Records.salary;
    }
    seqfile.close();
    indexfile.close();
}

int main()
{
    EMP_CLASS List;
    int choice;
    while(true)
    {
        cout << "\nMain Menu";
        cout << "\n1. Create";
        cout << "\n2. Display";
        cout << "\n3. Update";
        cout << "\n4. Delete";
        cout << "\n5. Append";
        cout << "\n6. Search";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice)
        {
        case 1: List.Create(); break;
        case 2: List.Display(); break;
        case 3: List.Update(); break;
        case 4: List.Delete(); break;
        case 5: List.Append(); break;
        case 6: List.Search(); break;
        case 7: return 0;
        default: cout << "Invalid choice";
        }
    }
    return 0;
}