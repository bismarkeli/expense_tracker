#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

const int CATEGORY_COUNT = 5;

struct Expense {
    string date;
    string description;
    double amount;
    int categoryIndex;
};
// Declaring of function prototypes
int getInt(string message, int minValue, int maxValue);
float getFloat(string message);
string getCurrentDate();
void showCategories(string categories[]);
void addExpenseBatch(vector<Expense>& expenses, string categories[]);
void addExpense(vector<Expense>& expenses, string categories[],const string& sessionDate);
void viewExpenses(const vector<Expense>& expenses, string categories[]);
void showTotal(const vector<Expense>& expenses);
void categorySummary(const vector<Expense>& expenses, string categories[]);
void deleteExpense(vector<Expense>& expenses, string categories[]);
void exportCSV(const vector<Expense>& expenses, string categories[]);
void loadCSV(vector<Expense>& expenses, string categories[]);
int main() {
    string categories[CATEGORY_COUNT] = { "Food & Drinks","Transportation","Personal & Lifestyle","Bills & Utilities","Other"};

    vector<Expense> expenses;
    loadCSV(expenses, categories);

    int choice;

    do {// Main menu for the expense tracker
        cout << "\n========== EXPENSE TRACKER ==========\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Show Total Expenses\n";
        cout << "4. Category Summary\n";
        cout << "5. Delete Expense\n";
        cout << "6. Export Expenses to CSV\n";
        cout << "0. Exit\n";

        choice = getInt("Choose an option: ", 0, 6);

        switch (choice) {
            case 1:
                addExpenseBatch(expenses, categories);
                break;

            case 2:
                viewExpenses(expenses, categories);
                break;

            case 3:
                showTotal(expenses);
                break;

            case 4:
                categorySummary(expenses, categories);
                break;

            case 5:
                deleteExpense(expenses, categories);
                break;
            case 6:
                exportCSV(expenses, categories);
                break;
            case 0:
                cout << "\nThank you for using the Expense Tracker.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}
//This function accepts and validates integer inputs from the user
int getInt(string message, int minValue, int maxValue) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value && value >= minValue && value <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
//This function accepts and validates floating inputs from the user
float getFloat(string message) {
    double value;

    while (true) {
        cout << message;

        if (cin >> value && cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Please enter a valid amount.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
string getCurrentDate(){
    auto now =chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    tm*localTime =localtime(&currentTime);
    //format the date as DD/MM/YYYY
    char buffer[11];
    strftime(buffer,sizeof(buffer),"%d/%m/%Y",localTime);
    //returns the date
    return string(buffer);

}
//This displays the categories for the expenses
void showCategories(string categories[]) {
    cout << "\nTo which category does your expense belong?\n";
    for (size_t i = 0; i < CATEGORY_COUNT; i++) {
        cout << i + 1 << ". " << categories[i] << endl;
    }
}
// This function helps the user add expense by asking 
void addExpense(vector<Expense>& expenses, string categories[],const string& sessionDate) {
    Expense newExpense;
    newExpense.date = sessionDate;
    showCategories(categories);
    int choice = getInt("Choose category by the corresponding number: ", 1, CATEGORY_COUNT);
    newExpense.categoryIndex = choice -1;

    cout << "Enter description: "; 
    getline(cin, newExpense.description);

    newExpense.amount = getFloat("Enter amount: ");
    expenses.push_back(newExpense);
    cout << "\nExpense added successfully!\n";

}
// This function allows the user to add or stop adding expenses when they want
void addExpenseBatch(vector<Expense>& expenses, string categories[]){
     string sessionDate =getCurrentDate();
    cout << "\n[ Session Date: " << sessionDate << " ]\n";
    char answer;
    do{
        addExpense(expenses,categories, sessionDate);
        cout << "Would you like to add another expense(Y/N):" ;
        cin >>  answer;
        cin.ignore();
    }while(answer == 'Y' || answer =='y');
}
//This function helps to display the expenses the user has entered in a tabular form
void viewExpenses(const vector<Expense>& expenses, string categories[]) {
    if (expenses.empty()) {
        cout << "\nNo expenses recorded yet.\n";
        return;
    }

    cout << "\n================ EXPENSE LIST ================\n";
        for (size_t i = 0; i < expenses.size(); i++) {
            cout << i+ 1 << ". Date "<< expenses[i].date << " | Category: " << categories[ expenses[i].categoryIndex]
            << " | Description: " << expenses[i].description << " | Amount: GHS " << fixed << setprecision(2) << expenses[i].amount << endl;
        } 

    cout << "------------------------------------------------------------\n";

    
}
// This function calculates and displays the total expenses recorded by the user
void showTotal(const vector<Expense>& expenses) {
    float total = 0.0;

    for (size_t i = 0; i < expenses.size(); i++) {
        total += expenses[i].amount;
    }

    cout << "\nTotal expenses: GHS "
         << fixed << setprecision(2) << total << endl;
}
// This function calculates and displays the total expenses recorded by the user under each category
void categorySummary(const vector<Expense>& expenses, string categories[]) {
     float totals[CATEGORY_COUNT] = {0};

    for (size_t i = 0; i < expenses.size(); i++) {
        totals[expenses[i].categoryIndex] += expenses[i].amount;
    }

    cout << "\n=========== CATEGORY SUMMARY ===========\n";

    for (size_t i = 0; i < CATEGORY_COUNT; i++) {
        cout << categories[i] << ": GHS "
             << fixed << setprecision(2) << totals[i] << endl;
    }
}
//  This function allows the user to delete an expense by selecting its number from the list
void deleteExpense(vector<Expense>& expenses, string categories[]) {
    if (expenses.empty()) {
        cout << "\nNo expenses to delete.\n";
        return;
    }

    viewExpenses(expenses, categories);

    int number = getInt("\nEnter expense number to delete: ", 1, expenses.size());

    expenses.erase(expenses.begin() + number - 1);

    cout << "\nExpense deleted successfully!\n";
}
// This function exports the recorded expenses to a CSV file
void exportCSV(const vector<Expense>& expenses, string categories[]) {

    ofstream file("Expenses.csv", ios::app);

    if (!file) {
        cout << "Unable to create file.\n";
        return;
    }

    file << "Date,Description,Category,Amount\n";

    for (const Expense& expense : expenses) {
        string escapedDescription = expense.description;
        size_t pos = 0;
        while ((pos = escapedDescription.find('"', pos)) != string::npos) {
            escapedDescription.insert(pos, "\"");
            pos += 2; 
        }
        file << expense.date << ","
             << expense.description << ","
             << categories[expense.categoryIndex] << ","
             << fixed << setprecision(2)
             << expense.amount << "\n";
    }

    file.close();

    cout << "\nExpenses exported successfully to Expenses.csv\n";
}
// This function loads the recorded expenses from a CSV file
void loadCSV(vector<Expense>& expenses, string categories[]){
    ifstream file("Expenses.csv");
    if (!file) {
        cout << "No existing expense records found. Starting fresh.\n";
        return;
    }
    string line;
    getline(file,line); // Skip header line
    while(getline(file,line)){
        if(line.empty())continue; // Skip empty lines
        vector<string>fields;
        string field;
        bool inQuotes = false;
        for(size_t i =0; i<line.length(); i++){
            char c = line[i];
            if(c=='"'){
                 if(inQuotes && i+1<line.length() && line[i+1]=='"'){
                    field +='"';
                    i++;
                }else {
                    inQuotes = !inQuotes;
                }
            }else if(c==',' && !inQuotes){
                fields.push_back(field);
                field.clear();
            }else{
                field += c;
            }
        }
        fields.push_back(field);
        if(fields.size() == 4){
            Expense expense;
            expense.date = fields[0];
            expense.description = fields[1];
            
            expense.categoryIndex= CATEGORY_COUNT -1;
            for(int i = 0; i < CATEGORY_COUNT; i++){
                if(categories[i] == fields[2]){
                    expense.categoryIndex = i;
                    break;
                }
            }
            expense.amount = stod(fields[3]);
            expenses.push_back(expense);
        }

        file.close();
        
    }
    if(!expenses.empty()){
            cout << "Loaded " << expenses.size() << " expense records from Expenses.csv\n";
     }
}