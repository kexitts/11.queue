#include <iostream>
#include <string>
#include <limits>
using namespace std;

template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        int priority;
        Node* next;

        Node(T value, int p)
        {
            data = value;
            priority = p;
            next = nullptr;
        }
    };

    Node* head;
    int count;

public:
    Queue()
    {
        head = nullptr;
        count = 0;
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    ~Queue()
    {
        Clear();
    }

    bool IsEmpty() const
    {
        return head == nullptr;
    }

    int Count() const
    {
        return count;
    }

    void Push(T value, int priority)
    {
        Node* temp = new Node(value, priority);

        if (IsEmpty() || priority > head->priority)
        {
            temp->next = head;
            head = temp;
        }
        else
        {
            Node* current = head;

            while (current->next != nullptr &&
                current->next->priority >= priority)
            {
                current = current->next;
            }

            temp->next = current->next;
            current->next = temp;
        }

        count++;
    }

    bool Pop(T& value)
    {
        if (IsEmpty())
            return false;

        Node* temp = head;
        value = head->data;

        head = head->next;
        delete temp;
        count--;

        return true;
    }

    void Show() const
    {
        if (IsEmpty())
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        Node* current = head;
        int number = 1;

        while (current != nullptr)
        {
            cout << number++ << ". "
                << current->data
                << " | Priority: "
                << current->priority << endl;

            current = current->next;
        }
    }

    void Clear()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        count = 0;
    }
};

struct Document
{
    string filename;
    string position;
};

ostream& operator<<(ostream& out, const Document& doc)
{
    out << "File: " << doc.filename
        << " | Position: " << doc.position;

    return out;
}

int main()
{
    Queue<Document> printer;

    int choice;

    do
    {
        cout << "\n===== PRINTER MENU =====" << endl;
        cout << "1. Add document" << endl;
        cout << "2. Print document" << endl;
        cout << "3. Show queue" << endl;
        cout << "4. Count documents" << endl;
        cout << "5. Clear queue" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!" << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            Document doc;
            int priority;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter filename: ";
            getline(cin, doc.filename);

            if (doc.filename.empty())
            {
                cout << "Filename cannot be empty!" << endl;
                break;
            }

            cout << "\nChoose position:" << endl;
            cout << "1. Guest" << endl;
            cout << "2. Administrator" << endl;
            cout << "3. Manager" << endl;
            cout << "4. Director" << endl;
            cout << "Your choice: ";

            if (!(cin >> priority))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input!" << endl;
                break;
            }

            switch (priority)
            {
            case 1:
                doc.position = "Guest";
                break;
            case 2:
                doc.position = "Administrator";
                break;
            case 3:
                doc.position = "Manager";
                break;
            case 4:
                doc.position = "Director";
                break;
            default:
                cout << "Invalid position!" << endl;
                break;
            }

            if (priority >= 1 && priority <= 4)
            {
                printer.Push(doc, priority);
                cout << "Document added successfully!" << endl;
            }

            break;
        }

        case 2:
        {
            Document doc;

            if (printer.Pop(doc))
            {
                cout << "\nPrinting document..." << endl;
                cout << doc << endl;
                cout << "Printing completed!" << endl;
            }
            else
            {
                cout << "Queue is empty!" << endl;
            }

            break;
        }

        case 3:
            cout << "\nDocuments in queue:" << endl;
            printer.Show();
            break;

        case 4:
            cout << "Documents count: "
                << printer.Count() << endl;
            break;

        case 5:
            printer.Clear();
            cout << "Queue cleared!" << endl;
            break;

        case 0:
            cout << "Program finished!" << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 0);

    return 0;
}
