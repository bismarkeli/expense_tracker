# C++ Expense Tracker

A lightweight, interactive console application written in C++ for tracking personal expenses, categorizing spending, generating cost summaries, and persisting data via CSV export and import.

---

## Features

- **Automated Date Tracking**: Automatically captures current system date (`DD/MM/YYYY`) using standard library `<chrono>` utilities.
- **Batch Entry Mode**: Add multiple expenses sequentially in a single session.
- **Categorization**: Assign entries across predefined categories:
  - Food & Drinks
  - Transportation
  - Personal & Lifestyle
  - Bills & Utilities
  - Other
- **Expense Analysis**:
  - View full itemized list of expenses.
  - Calculate grand total spending (formatted in `GHS`).
  - View total expenditures broken down by category.
- **Data Persistence (CSV)**: Automatically loads past records from `Expenses.csv` on application startup and exports updated data with CSV-safe double-quote escaping.
- **Input Validation**: Prevents invalid values, negative amounts, or malformed data inputs.

---

## File Structure

- `main.cpp` — Complete source code containing data structures, helper utilities, menu logic, and file IO methods.
- `Expenses.csv` — CSV file generated upon export to store expense records.

---

## Requirements & Prerequisites

- **Compiler**: C++11 or newer standard compiler (`g++`, `clang++`, or MSVC).
- **Standard Libraries Used**: `<iostream>`, `<vector>`, `<string>`, `<iomanip>`, `<chrono>`, `<ctime>`, `<fstream>`, `<sstream>`.

---

## Building and Running

### 1. Compilation

Using **GCC (`g++`)**:
```bash
g++ -std=c++11 main.cpp -o ExpenseTracker
```

Using **Clang (`clang++`)**:
```bash
clang++ -std=c++11 main.cpp -o ExpenseTracker
```

### 2. Execution

**Linux / macOS:**
```bash
./ExpenseTracker
```

**Windows Command Prompt:**
```cmd
ExpenseTracker.exe
```

---

## How to Use

Upon launching the application, it automatically checks for and imports existing entries from `Expenses.csv`. You will be presented with an interactive menu:

```text
========== EXPENSE TRACKER ==========
1. Add Expense
2. View Expenses
3. Show Total Expenses
4. Category Summary
5. Delete Expense
6. Export Expenses to CSV
0. Exit
```

1. **Add Expense**: Pick a category (1–5), type a description, enter the positive numeric amount, and confirm if you want to enter another entry.
2. **View Expenses**: Displays indexed expenses alongside session dates, categories, descriptions, and amounts.
3. **Show Total Expenses**: Calculates cumulative expenditures.
4. **Category Summary**: Aggregates total expenditure for each category.
5. **Delete Expense**: View indexed entries and select one to remove from memory.
6. **Export Expenses to CSV**: Appends recorded expenses to `Expenses.csv`.

---

## File Data Format (`Expenses.csv`)

The export mechanism generates plain-text CSV records structured as follows:

```csv
Date, Description, Category, Amount
27/08/2026, Groceries, Food & Drinks,150.50
27/08/2026, Taxi fare, Transportation,45.00
