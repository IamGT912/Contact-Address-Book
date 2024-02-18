#include <bits/stdc++.h>
using namespace std;

string FILENAME = "contacts.csv";

class contacts
{
public:
    string name;
    string number;
    string emailaddress;
    contacts() {}
    void makeContact()
    {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter phone number: ";
        cin >> number;
        cout << "Enter email address: ";
        cin >> emailaddress;
    }
};
void addContacts(const contacts C)
{
    ofstream file;
    file.open("contacts.csv", ios::app);
    if (file.is_open())
    {
        file << C.name << "," << C.number << "," << C.emailaddress << "\n";
        file.close();
        cout << "Contact Added Successfully\n\n";
    }
    else
    {
        cerr << "Erorr Opening file\n";
    }
}
void display(string s)
{
    size_t pos = s.find(',');
    cout << "\nName: " << s.substr(0, pos) << "\n";
    cout << "Phone number: " << s.substr(pos + 1, s.find(',', pos + 1) - pos - 1) << "\n";
    cout << "Email: " << s.substr(s.find(',', pos + 1) + 1) << "\n\n";
}
void displayPhonebook()
{
    ifstream file;
    file.open("contacts.csv");
    if (file.is_open())
    {
        string line; int i = 1;
        while (getline(file, line))
        {
            cout << "Contact No. " << i << " :"; 
            display(line);
            i++;
        }
        file.close();
    }
    else
    {
        cerr << "Error opening file\n";
    }
}
string getField(int field, const string line)
{
    size_t pos = line.find(',');
    switch (field)
    {
    case 1:
        return line.substr(0, pos); // Name
    case 2:
        return line.substr(pos + 1, line.find(',', pos + 1) - pos - 1); // Number
    case 3:
        return line.substr(line.find(',', pos + 1) + 1); // Email

    default:
        return "";
    }
}
void deleteContact(int field, string term) {
    ifstream file;
    file.open("contacts.csv");
    if (!file.is_open()) {
        cerr << "Error Opening file\n";
    }

    string line;

    ofstream tempFile;
    tempFile.open("temp.csv");
    if (!tempFile.is_open()) {
        cerr << "Error making a temporary file\n";
    }
    bool contactFound = false;
    while(getline(file,line)) {
        if (getField(field, line) == term) {
            cout << "Is this the contact you want to delete?\n";
            display(line);

            cout << "1. Yes\n2. No\nYour choice: ";
            int choice; cin >> choice;
            switch(choice) {
                case 1:
                    contactFound = true;
                    cout << "Contact found and deleted!\n\n";
                    break;
                case 2:
                    tempFile << line << "\n";
                    break;
                default:
                    cout << "Invalid Choice\n";
                    break;
            }
        } 
        else 
        {
            tempFile << line << "\n";
        }
    }
    tempFile.close();
    file.close();
    if (contactFound) {
        if (remove(FILENAME.c_str()) != 0) {
            cerr << "Error deleting the original file!\n";
        }

        // Rename the temporary file to the original FILENAME
        if (rename("temp.csv", FILENAME.c_str()) != 0) {
            cerr << "Error renaming the temporary file!\n";
        }
    } else {
        cout << "Contact not found!\n\n";
        // Remove the temporary file since no deletion was performed
        remove("temp.csv");
    }
}
void searchContact(int field, string term)
{
    ifstream file;
    file.open("contacts.csv");
    bool contactFound = false;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (getField(field, line) == term)
            {
                contactFound = true;
                display(line);
            }
        }
        if (!contactFound) cout << "Contact not found :(\n\n";
        file.close();
    }
    else
    {
        cerr << "Error Opening File\n";
    }
}
void getchoice()
{
    cout << "Enter search term: ";
    string term;
    cin >> term;
    cout << "1. Name\n2. Phone Number\n3. Email\n";
    cout << "Choose the Field: ";
    int field;
    cin >> field;
    searchContact(field, term);
}

int main()
{
    cout << "--------------------------------------x--------------------------------------\n";
    cout << "Please Choose the appropriate option: \n";
    while (true)
    {
        cout << "1. Add a Contact\n";
        cout << "2. Search a Contact\n";
        cout << "3. Delete a Contact\n";
        cout << "4. Display all Contacts\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Enter the number of contacts you want to add: ";
            int n;
            cin >> n;
            while (n--)
            {
                contacts buff;
                buff.makeContact();
                addContacts(buff);
            }
            break;
        }

        case 2:
        {
            getchoice();
            break;
        }

        case 3:
        {
            // yet to write
            cout << "Enter search term: ";
            string term;
            cin >> term;
            cout << "1. Name\n2. Phone Number\n3. Email\n";
            cout << "Choose the Field: ";
            int field;
            cin >> field;
            deleteContact(field, term);
            break;
        }

        case 4:
        {
            displayPhonebook();
            break;
        }

        case 5:
        {
            return 0;
        }

        default:
            break;
        }
    }
    cout << "--------------------------------------x--------------------------------------\n";
    return 0;
}