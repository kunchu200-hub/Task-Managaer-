C++ Task Manager - Professional Console Application

______________________________________________________________________________________________________________
Core Features:

Add tasks with description and due date (MM/DD/YYYY format)

View all tasks with ID, status (Pending/Done), and formatted due dates

Modifications: toggel tasks complete/incomplete and delete by ID
_______________________________________________________________________________________________________________
Technical Implementation:

Data Structure: std::vector<Task> stores dynamic list of tasks

Task Struct: Contains int id, std::string description, bool completed, Date dueDate

Date Handling: Custom Date struct wrapping std::tm (C++ standard time library)

Date Validation: std::mktime() automatically validates dates, handles leap years

File I/O: std::ifstream/ofstream reads/writes tasks (4 lines per task: ID, desc, status, date)
________________________________________________________________________________________________________________
Standards Compliance:

C++11 features (auto, range-for, to_string())

Cross-platform (Windows/Linux/Mac)

No external dependencies—pure standard library
_________________________________________________________________________________________________________________


<img width="700" height="540" alt="Screenshot 2026-04-20 000625" src="https://github.com/user-attachments/assets/93483be9-a365-428e-a6d5-db4e871e4bd6" />

This was made on Visual studio
