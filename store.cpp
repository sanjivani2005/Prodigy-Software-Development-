#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Define a structure for a contact
struct Contact {
    string name;
    string phone;
    string email;
};

// Function prototypes
void addContact(vector<Contact>& contacts);
void viewContacts(const vector<Contact>& contacts);
void editContact(vector<Contact>& contacts);
void deleteContact(vector<Contact>& contacts);
void saveContactsToFile(const vector<Contact>& contacts, const string& filename);
void loadContactsFromFile(vector<Contact>& contacts, const string& filename);

int main() {
    vector<Contact> contacts;
    string filename = "contacts.txt";

    // Load contacts from file
    loadContactsFromFile(contacts, filename);

    int choice;
    do {
        cout << "\nContact Management System" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. View Contacts" << endl;
        cout << "3. Edit Contact" << endl;
        cout << "4. Delete Contact" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                editContact(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                saveContactsToFile(contacts, filename);
                cout << "Contacts saved. Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter name: ";
    getline(cin, newContact.name);
    cout << "Enter phone number: ";
    getline(cin, newContact.phone);
    cout << "Enter email address: ";
    getline(cin, newContact.email);

    contacts.push_back(newContact);
    cout << "Contact added successfully!" << endl;
}

void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to display." << endl;
        return;
    }

    cout << "\nContact List:" << endl;
    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << i + 1 << ". Name: " << contacts[i].name
             << ", Phone: " << contacts[i].phone
             << ", Email: " << contacts[i].email << endl;
    }
}

void editContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to edit." << endl;
        return;
    }

    int index;
    cout << "Enter the number of the contact to edit: ";
    cin >> index;
    cin.ignore();

    if (index < 1 || index > static_cast<int>(contacts.size())) {
        cout << "Invalid contact number." << endl;
        return;
    }

    Contact& contact = contacts[index - 1];
    cout << "Editing contact: " << contact.name << endl;
    cout << "Enter new name (or press Enter to keep the current name): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) contact.name = newName;

    cout << "Enter new phone number (or press Enter to keep the current phone): ";
    string newPhone;
    getline(cin, newPhone);
    if (!newPhone.empty()) contact.phone = newPhone;

    cout << "Enter new email address (or press Enter to keep the current email): ";
    string newEmail;
    getline(cin, newEmail);
    if (!newEmail.empty()) contact.email = newEmail;

    cout << "Contact updated successfully!" << endl;
}

void deleteContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to delete." << endl;
        return;
    }

    int index;
    cout << "Enter the number of the contact to delete: ";
    cin >> index;
    cin.ignore();

    if (index < 1 || index > static_cast<int>(contacts.size())) {
        cout << "Invalid contact number." << endl;
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    cout << "Contact deleted successfully!" << endl;
}

void saveContactsToFile(const vector<Contact>& contacts, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Unable to open file for saving." << endl;
        return;
    }

    for (const auto& contact : contacts) {
        outFile << contact.name << '\n' << contact.phone << '\n' << contact.email << '\n';
    }
}

void loadContactsFromFile(vector<Contact>& contacts, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        // File does not exist or cannot be opened, skip loading
        return;
    }

    Contact contact;
    while (getline(inFile, contact.name) &&
           getline(inFile, contact.phone) &&
           getline(inFile, contact.email)) {
        contacts.push_back(contact);
    }
}
