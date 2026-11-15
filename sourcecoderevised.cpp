#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>
using namespace std;

struct item {
    int itemID;
    string itemName;
    string category;
    double size;
    int level;
};

// Function declarations

void addItem(item items[], int &count);
void displayItems(item items[], int count);
double calculateTotal(item items[], int count);
double calculateAverage(item items[], int count);
void findLargest(item items[], int count);
void findSmallest(item items[], int count);
void classifySize(item items[], int count);
void storageByCategory(item items[], int count);
void sortBySize(item items[], int count);
void sortByImportance(item items[], int count);
void searchMenu(item items[], int count);
void searchByID(item items[], int count);
void searchByName(item items[], int count);
void searchByCategory(item items[], int count);
double recursiveTotal(item items[], int count);
void cleanupCandidates(item items[], int &count);

// Function to convert string to lowercase

string toLowerCase(string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = tolower(static_cast<unsigned char>(text[i]));
    }
    return text;
}

int main() {
    const int MAX_ITEMS = 100;
    item items[MAX_ITEMS];
    int count = 0;
    int choice;

    while (true) {

        cout << "\n===== STUDENT DEVICE & STORAGE MANAGER =====\n";
        cout << "1. Add New Item\n";
        cout << "2. Display All Items\n";
        cout << "3. Storage Statistics\n";
        cout << "4. Storage By Category\n";
        cout << "5. Sort By Size\n";
        cout << "6. Sort By Importance\n";
        cout << "7. Search Items\n";
        cout << "8. Calculate Storage Using Recursion\n";
        cout << "9. Cleanup Candidates\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";

        // Input validation
        if (!(cin >> choice)) {

            cout << "Invalid input! Please enter a number.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        // Clear remaining input in the current line
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Exit condition
        if (choice == 0) {
            cout << "Exiting the program." << endl;
            break;
        }

        switch (choice) {

            case 1:
                addItem(items, count);
                break;

            case 2:
                displayItems(items, count);
                break;

            case 3:
                cout << "Total Storage: "
                     << calculateTotal(items, count) << " MB" << endl;

                cout << "Average Storage: "
                     << calculateAverage(items, count) << " MB" << endl;

                findLargest(items, count);
                findSmallest(items, count);
                classifySize(items, count);
                break;

            case 4:
                storageByCategory(items, count);
                break;

            case 5:
                sortBySize(items, count);
                break;

            case 6:
                sortByImportance(items, count);
                break;

            case 7:
                searchMenu(items, count);
                break;

            case 8:
                cout << "Total Storage (using recursion): "
                     << recursiveTotal(items, count) << " MB" << endl;
                break;

            case 9:
                cleanupCandidates(items, count);
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}


// 1. Add Item
void addItem(item items[], int &count) {

    if (count >= 100) {
        cout << "Storage is full. Cannot add more items." << endl;
        return;
    }

    // Input validation for item ID
    cout << "Enter Item ID: ";

while (!(cin >> items[count].itemID) ||
       items[count].itemID <= 0) {

    cout << "Invalid ID! Enter a positive number: ";

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

    // Check duplicate ID
    for (int i = 0; i < count; i++) {
        if (items[i].itemID == items[count].itemID) {
            cout << "ID already exists!" << endl;
            return;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Input validation for item name
    cout << "Enter Item Name: ";
    getline(cin, items[count].itemName);

    while (items[count].itemName.find_first_not_of(" \t\n\r") == string::npos) {
    cout << "Item name cannot be empty. Enter again: ";
    getline(cin, items[count].itemName);
}

    // Input validation for category
    cout << "Enter Category (Development, Document, Dataset, Media, Other): ";
    getline(cin, items[count].category);


while (toLowerCase(items[count].category) != "development" &&
       toLowerCase(items[count].category) != "document" &&
       toLowerCase(items[count].category) != "dataset" &&
       toLowerCase(items[count].category) != "media" &&
       toLowerCase(items[count].category) != "other") {

    cout << "Invalid category! Enter again: ";
    getline(cin, items[count].category);
}

items[count].category = toLowerCase(items[count].category);

items[count].category[0] =
    toupper(static_cast<unsigned char>(items[count].category[0]));
    cout << "Enter Size (in MB): ";

    while (!(cin >> items[count].size) || items[count].size < 0) {
        cout << "Invalid size! Enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Input validation for importance level
    cout << "Enter Importance Level (1-5): ";

    while (!(cin >> items[count].level) ||
           items[count].level < 1 ||
           items[count].level > 5) {

        cout << "Invalid importance! Enter a number from 1 to 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    count++;

    cout << "\nItem added successfully!" << endl;
}


//2. Display items
void displayItems(item items[], int count) {
    if (count == 0) {
        cout << "\nNo items to display.\n";
        return;
    }
    
    cout << "\n========== Item List ==========\n";
    for (int i = 0; i < count; i++) {
        cout << "Item ID: " << items[i].itemID << endl;
        cout << "Item Name: " << items[i].itemName << endl;
        cout << "Category: " << items[i].category << endl;
        cout << "Size: " << fixed << setprecision(2) << items[i].size << " MB" << endl;
        cout << "Importance Level: " << items[i].level << endl;
        cout << "------------------------\n";
    }
}

//3. Calculate total storage
double calculateTotal(item items[], int count) {
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        total += items[i].size;
    }
    return total;
}

//4. Calculate average storage
double calculateAverage(item items[], int count) {
    if (count == 0) return 0.0;
    return calculateTotal(items, count) / count;
}

//5. Find largest item
void findLargest(item items[], int count) {
    if (count == 0) {
        cout << "No items to evaluate." << endl;
        return;
    }

    item largest = items[0];
    for (int i = 1; i < count; i++) {
        if (items[i].size > largest.size) {
            largest = items[i];
        }
    }

    cout << "Largest Item:\n";
    cout << "Item ID: " << largest.itemID << endl;
    cout << "Item Name: " << largest.itemName << endl;
    cout << "Category: " << largest.category << endl;
    cout << "Size: " << fixed << setprecision(2) << largest.size << " MB" << endl;
    cout << "Importance Level: " << largest.level << endl;
}

//6. Find smallest item
void findSmallest(item items[], int count) {
    if (count == 0) {
        cout << "No items to evaluate." << endl;
        return;
    }

    item smallest = items[0];
    for (int i = 1; i < count; i++) {
        if (items[i].size < smallest.size) {
            smallest = items[i];
        }
    }

    cout << "Smallest Item:\n";
    cout << "Item ID: " << smallest.itemID << endl;
    cout << "Item Name: " << smallest.itemName << endl;
    cout << "Category: " << smallest.category << endl;
    cout << "Size: " << fixed << setprecision(2) << smallest.size << " MB" << endl;
    cout << "Importance Level: " << smallest.level << endl;
}

//7. Classify Size
void classifySize(item items[], int count) {
    if (count == 0) {
    cout << "\nNo items to classify.\n";
    return;
}
    cout << "\n========== Size Classification ==========\n";
    for (int i = 0; i < count; i++){
        cout << "Item ID: " << items[i].itemID << " - ";
        if (items[i].size < 100) {
            cout << "Small (< 100 MB)" << endl;
        }
        else if (items[i].size <= 1000) {
            cout << "Medium (100-1000 MB)" << endl;
        }
        else {
            cout << "Large (> 1000 MB)" << endl;
        }
    }
}

//8. Storage by category
void storageByCategory(item items[], int count) {  

    string categories[] = {
        "Development", "Document", "Dataset", "Media", "Other"
    };

    cout << "\n========== STORAGE BY CATEGORY ==========\n";

    for (int i = 0; i < 5; i++) {

        double total = 0;

        for (int j = 0; j < count; j++) {

            if (toLowerCase(items[j].category) == toLowerCase(categories[i])) {
                total += items[j].size;
            }
        }

        cout << categories[i] << ": "
             << fixed << setprecision(2) << total << " MB\n";
    }
}

//9. Sort by size
void sortBySize(item items[], int count) {

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            if (items[j].size > items[j + 1].size) {
                item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    cout << "\nItems sorted by size (smallest to largest):\n";
    displayItems(items, count);
}

//10. Sort by importance
void sortByImportance(item items[], int count) {

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            if (items[j].level < items[j + 1].level) {
                item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    cout << "\nItems sorted by importance (highest to lowest):\n";
    displayItems(items, count);
}

// Search Items
void searchMenu(item items[], int count) {
    int choice;

    while (true) {
        cout << "\n========== SEARCH ITEMS ==========\n";
        cout << "1. Search by ID\n";
        cout << "2. Search by Name\n";
        cout << "3. Search by Category\n";
        cout << "0. Back to Main Menu\n";

        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                searchByID(items, count);
                break;

            case 2:
                searchByName(items, count);
                break;

            case 3:
                searchByCategory(items, count);
                break;

            case 0:
                return;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

//11. Search by ID
void searchByID(item items[], int count){
    int id;

cout << "Enter Item ID to search: ";

while (!(cin >> id)) {
    cout << "Invalid ID! Please enter a number: ";

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (items[i].itemID == id) {
            cout << "Item found:\n";
            cout << "Item ID: " << items[i].itemID << endl;
            cout << "Item Name: " << items[i].itemName << endl;
            cout << "Category: " << items[i].category << endl;
            cout << "Size: " << fixed << setprecision(2) << items[i].size << " MB" << endl;
            cout << "Importance Level: " << items[i].level << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Item not found.\n";
    }
}

//12. Search by Name
void searchByName(item items[], int count){
    string name;
    cout << "Enter Item Name to search: ";
    getline(cin, name);
    name = toLowerCase(name);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (toLowerCase(items[i].itemName) == name) {
            cout << "Item found:\n";
            cout << "Item ID: " << items[i].itemID << endl;
            cout << "Item Name: " << items[i].itemName << endl;
            cout << "Category: " << items[i].category << endl;
            cout << "Size: " << fixed << setprecision(2) << items[i].size << " MB" << endl;
            cout << "Importance Level: " << items[i].level << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Item not found.\n";
    }
}

//13. Search by Category
void searchByCategory(item items[], int count){
    string category;
    cout << "Enter Category to search: ";
    getline(cin, category);
    category = toLowerCase(category);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (toLowerCase(items[i].category) == category) {
            cout << "Item found:\n";
            cout << "Item ID: " << items[i].itemID << endl;
            cout << "Item Name: " << items[i].itemName << endl;
            cout << "Category: " << items[i].category << endl;
            cout << "Size: " << fixed << setprecision(2) << items[i].size << " MB" << endl;
            cout << "Importance Level: " << items[i].level << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No items found in this category.\n";
    }
}

//14. Calculate total storage using recursion
double recursiveTotal(item items[], int count) {
    if (count == 0) {
        return 0.0;
    } else {
        return items[count - 1].size + recursiveTotal(items, count - 1);
    }
}

//15. Cleanup candidates
void cleanupCandidates(item items[], int &count) {

    double sizeLimit;
    int importanceLimit;

   cout << "\nEnter minimum size limit (MB): ";

while (!(cin >> sizeLimit) || sizeLimit < 0) {
    cout << "Invalid size! Enter a valid number: ";

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

cout << "Enter maximum importance level (1-5): ";

while (!(cin >> importanceLimit) ||
       importanceLimit < 1 ||
       importanceLimit > 5) {

    cout << "Invalid importance! Enter a number from 1 to 5: ";

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

    bool found = false;

    cout << "\n========== CLEANUP CANDIDATES ==========\n";

    for (int i = 0; i < count; i++) {

        if (items[i].size >= sizeLimit &&
            items[i].level <= importanceLimit) {

            cout << "Item Name: " << items[i].itemName << endl;
            cout << "Size: " << items[i].size << " MB" << endl;
            cout << "Importance: " << items[i].level << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "No cleanup candidates found.\n";
        return;
    }

    char confirm;

cout << "\nDo you want to delete these items? (Y/N): ";
cin >> confirm;

while (confirm != 'Y' && confirm != 'y' &&
       confirm != 'N' && confirm != 'n') {

    cout << "Invalid input! Please enter Y or N: ";
    cin >> confirm;
}
cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm == 'Y' || confirm == 'y') {

        for (int i = 0; i < count; ) {

            if (items[i].size >= sizeLimit &&
                items[i].level <= importanceLimit) {

                for (int j = i; j < count - 1; j++) {
                    items[j] = items[j + 1];
                }

                count--;
            }
            else {
                i++;
            }
        }

        cout << "Cleanup completed successfully!\n";
    }
    else {
        cout << "No items were deleted.\n";
    }
}
