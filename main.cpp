#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
using namespace std;

class Expense {
private:
    map<string, double> expenses;
    double total = 0.0;

public:
    void addExpense(const string& name, double amount) {
        expenses[name] = amount;
        total += amount;
    }

    double getTotal() const {
        return total;
    }

    void displayExpenses() const {
        for (auto& expense : expenses) {
            cout << expense.first << " - Rs " << expense.second << endl;
        }

        cout << "\nTotal Expenses for the Month : Rs " << total << endl;
    }

    void exportToCSV(const string& filename) const {
        ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            cout << "Error: Could not open file for writing." << endl;
            return;
        }

        outputFile << "Expense Name,Amount" << endl;

        for (const auto& expense : expenses) {
            outputFile << expense.first << "," << expense.second << endl;
        }

        outputFile << "Total Expenses," << total << endl;

        cout << "Expenses exported to " << filename << " successfully." << endl;

        outputFile.close();
    }
};

int main() {
    map<string, Expense> yearlyExpenses;
    string months[] = {"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};

    // Initialize Expense objects for all 12 months
    for (const auto& month : months) {
        yearlyExpenses[month] = Expense(); // Initialize each month with an Expense object
    }

    while (true) {
        string selectedMonth;
        cout << "Enter the month for which you want to enter expenses (or 'exit' to finish): ";
        getline(cin, selectedMonth);

        if (selectedMonth == "exit") {
            break;
        }

        auto it = yearlyExpenses.find(selectedMonth);
        if (it == yearlyExpenses.end()) {
            cout << "Invalid month entered. Please try again." << endl;
            continue;
        }

        Expense& expense = it->second;

        cout << "Enter Expenses for " << selectedMonth << ":" << endl;
        while (true) {
            string expenseName;
            double expenseAmount;

            cout << "Enter expense name (or 'exit' to finish): ";
            getline(cin, expenseName);

            if (expenseName == "exit") {
                break;
            }

            cout << "Enter expense amount: ";
            cin >> expenseAmount;
            cin.ignore(); // Ignore the newline character left in the buffer after entering the amount

            expense.addExpense(expenseName, expenseAmount);
        }
    }

    // Display and export expenses for all 12 months
    for (auto& [month, expense] : yearlyExpenses) {
        cout << "EXPENSE REPORT OF " << month << ":" << endl;
        expense.displayExpenses();

        string filename = "expense_report_" + month + ".csv";
        expense.exportToCSV(filename);
        cout << endl;
    }

    return 0;
}


