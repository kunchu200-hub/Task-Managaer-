#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime> 

using namespace std;

struct Date {

	tm tm;  // Structure to hold date components

	// Default constructor added to allow default construction of TASK
	Date() {
		tm = {};
		tm.tm_year = 1970 - 1900;
		tm.tm_mon = 0;
		tm.tm_mday = 1;
		tm.tm_hour = 0; tm.tm_min = 0; tm.tm_sec = 0;
		tm.tm_isdst = -1;
		mktime(&tm);
	}

	Date(int m, int d, int y) {
		tm.tm_year = y - 1900;
		tm.tm_mon = m - 1;      
		tm.tm_mday = d;         
		tm.tm_hour = 0; tm.tm_min = 0; tm.tm_sec = 0;
		tm.tm_isdst = -1;      

		mktime(&tm);  
	}

	bool valid() const {
		return tm.tm_mday != -1;  
	}

	string toString() const {
		if (!valid()) return "INVALID";
		char buf[11];
		strftime(buf, sizeof(buf), "%m/%d/%Y", &tm);
		return buf;
	}
};

struct TASK
{
	int id = 0;
	string description;
	bool status = false;
	Date dueDate;
};

vector <TASK> tasks;
int ID = 1;

void loadTasks();
Date inputDate();
void save_Task_toFile();
void addTask();
void viewTasks();
void mark_TaskCompleted();
void deleteTask();
void displayMenu();

int main()
{
	loadTasks();

	cout << "|_______Task Manager_______|" << endl
		<< endl
		<< endl;
	while (true)
	{
		displayMenu();
		int choice;
		cin >> choice;
		cin.ignore();

		switch (choice) {

		case 1:
			addTask();
			break;
		case 2:
			viewTasks();
			break;
		case 3:
			mark_TaskCompleted();
			break;
		case 4:
			deleteTask();
			break;
		case 5:
			return 0;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}

	}
}

void loadTasks()
{
	ifstream file("Task.txt");
	if (!file)
		return;

	TASK task;

	int m, d, y;
	while (file >> task.id)
	{
		file.ignore();
		getline(file, task.description);
		file >> task.status;
		file >> m >> d >> y;
		task.dueDate = Date(m, d, y);
		tasks.push_back(task);
		if (task.dueDate.valid() && task.id >= ID)
			ID = task.id + 1;
	}
	file.close();
}

Date inputDate() {
	int m, d, y;
	cout << "Enter due date (MM DD YYYY): ";
	cin >> m >> d >> y;
	Date date(m, d, y);
	if (!date.valid()) {
		cout << "Invalid date! Using default 12/31/2026." << endl;
		return Date(12, 31, 2026);
	}
	return date;
}

void save_Task_toFile()
{
	ofstream file("Task.txt");
	for (const auto& task : tasks)
	{
		file << task.id << endl;
		file << task.description << endl;
		file << task.status << endl;
		file << task.dueDate.tm.tm_mon + 1 << " " << task.dueDate.tm.tm_mday << " " << task.dueDate.tm.tm_year + 1900 << endl;	
	}
	file.close();
}

void addTask()
{
	TASK new_task;
	new_task.id = ID++;
	cout << "Enter your the task: ";
	getline(cin, new_task.description);
	new_task.dueDate = inputDate();
	tasks.push_back(new_task);
	save_Task_toFile();
	cout << "List has been updated." << endl;
}

void viewTasks()
{
	if (tasks.empty())
	{
		cout << "You ae FREE!, there are no task for completion" << endl;
		return;
	}
	cout << " ID | Task     | Status | Due" << endl;
	cout << "--------------------------------" << endl;
	for (const auto& task : tasks)
	{
		cout << task.id << " " << "|" << left << setw(29) << task.description
			<< " | " << (task.status ? "Done" : "Pending")
			<< " | " << task.dueDate.toString() << endl;
	}

}

void mark_TaskCompleted()
{
	viewTasks();
	int id; // Temporary varibale to store entry from the user. Used to compare with task IDs.

	cout << "Enter the ID of the task to mark as completed: ";
	cin >> id;

	for (auto& task : tasks) // allows users to modify the task status directly in the vector.
	{
		if (task.id == id)
		{
			task.status = true;

			save_Task_toFile();

			cout << "Task no " << id << " marked as completed." << endl;
			return;
		}
	}
	cout << "No task found with ID " << id << "." << endl;
}

void deleteTask()
{
	viewTasks();
	int id;

	cout << "Enter the ID of the task to delete: ";
	cin >> id;

	for (auto it = tasks.begin(); it != tasks.end(); ++it)
	{
		if (it->id == id)
		{
			tasks.erase(it);
			save_Task_toFile();
			cout << " Done" << endl;
			return;
		}
	}
	cout << "No task found with ID " << id << "." << endl;
}

void displayMenu()
{
	cout << endl
		<< "----------------------------" << endl
		<< "1. Add Task" << endl
		<< "----------------------------" << endl
		<< "2. View Tasks" << endl
		<< "----------------------------" << endl
		<< "3. Update status" << endl
		<< "----------------------------" << endl
		<< "4. Delete Task" << endl
		<< "----------------------------" << endl
		<< "5. Exit" << endl
		<< "----------------------------" << endl
		<< endl
		<< "Enter your choice: ";
}