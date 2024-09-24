#include <iostream>
#include <string>

using namespace std;

// Struct to represent a single task in the linked list
struct TaskNode {
    int taskID;                 // ID for the task
    string description;         // Description of the task
    int priority;               // Priority of the task
    TaskNode* next;             // Pointer to the next task node
    
    TaskNode(int id, string desc, int prio) 
        : taskID(id), description(desc), priority(prio), next(NULL) {}
};

class TaskManager {
private:
    TaskNode* head;
    
public:
    TaskManager() : head(NULL) {}
    
    // Function to add a new task
    void addTask(int id, string desc, int prio) {
        TaskNode* newTask = new TaskNode(id, desc, prio);
        
        if (!head || head->priority < prio) {
            newTask->next = head;
            head = newTask;
            return;
        }
        TaskNode* current = head;
        while (current->next && current->next->priority >= prio) {
            current = current->next;
        }
        newTask->next = current->next;
        current->next = newTask;
    }

    // Function to display all tasks
    void displayTasks() {
        if (!head) {
            cout << "No tasks found." << endl;
            return;
        }

        TaskNode* current = head;
        cout << "List of Tasks:" << endl;
        while (current) {
            cout << "ID: " << current->taskID << ", Description: " << current->description
                 << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }
    
    // Function to remove the highest priority task
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks available to remove." << endl;
            return;
        }
        
        TaskNode* temp = head;
        head = head->next;
        delete temp;
        cout << "Successfully removed the highest priority task." << endl;
    }

    // Function to remove a task using its ID
    void removeTaskByID(int id) {
        if (!head) {
            cout << "No tasks available to remove." << endl;
            return;
        }
        // task to remove the head
        if (head->taskID == id) {
            TaskNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Successfully removed task with ID: " << id << endl;
            return;
        }
        // Searching for the task with the ID
        TaskNode* current = head;
        while (current->next && current->next->taskID != id) {
            current = current->next;
        }
        // If the task was found
        if (current->next) {
            TaskNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Successfully removed task with ID: " << id << endl;
        } else {
            cout << "No task found with ID: " << id << "." << endl;
        }
    }

    //free allocated memory for tasks
    ~TaskManager() {
        while (head) {
            removeHighestPriorityTask();
        }
    }
};

void displayMenu() {
    TaskManager taskManager;
    int choice, id, priority;
    string description;

    do {
        cout << "\nManagement System" << endl;
        cout << "1. Add New Task " << endl;
        cout << "2. View All Tasks" << endl;
        cout << "3. Remove Highest Priority Task From list" << endl;
        cout << "4. Remove Task by ID" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "ID Enter : ";
                cin >> id;
                cout << "Task Description : ";
                cin.ignore();
                getline(cin, description);
                cout << "Priority Level of this task : ";
                cin >> priority;
                taskManager.addTask(id, description, priority);
                break;
            case 2:
                taskManager.displayTasks();
                break;
            case 3:
                taskManager.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Id to remove the task from list: ";
                cin >> id;
                taskManager.removeTaskByID(id);
                break;
            case 5:
                cout << "Exiting.. " << endl;
                break;
            default:
                cout << "Invalid .. Atry again." << endl;
        }
    } while (choice != 5);
}

int main() {
    displayMenu();
    return 0;
}

