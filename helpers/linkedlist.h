#ifndef linkedlist_H
#define linkedlist_H
#include <string>

#include "./print.h"
#include "./structures.h"
class linkedlist {
   private:
    struct Node {
        Node* next;
        tableData data;
    };
    Node* head;
    Node* tail;
    void allocateNode(tableData& data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

   public:
    linkedlist() {
        head = NULL;
        tail = NULL;
    }
    void getDataPaginated(int offset = 0, int limit = 20) {
        // Get data from the database
    }
    void insert(tableData& data) {
        allocateNode(data);
    }
    void display() {
        Node* temp = head;
        while (temp != NULL) {
            // print all in one line
            printLn(temp->data.id);
            printLn(", ");
            printLn(temp->data.username);
            printLn(", ");
            printLn(temp->data.password);
            printLn(", ");
            printLn(temp->data.email);
            printLn(", ");
            print(temp->data.origin);
            temp = temp->next;
        }
    }
    void deleteNode(tableData& data, int id = 0) {
        Node* temp = head;
        Node* prev = NULL;
        while (temp != NULL) {
            if (temp->data.id == data.id) {
                if (prev == NULL) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }
    void updateNode(tableData& oldData, tableData& newData) {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->data.id == oldData.id) {
                temp->data = newData;
                return;
            }
            temp = temp->next;
        }
    }
    void search(tableData& data, int field = 0, std::string query = "") {
        Node* temp = head;
        while (temp != NULL) {
            switch (field) {
                case 0:
                    if (temp->data.id == data.id) {
                        print(temp->data.id);
                        print(temp->data.username);
                        print(temp->data.password);
                        print(temp->data.email);
                        print(temp->data.origin);
                        return;
                    }
                    break;
                case 1:
                    if (temp->data.username == data.username) {
                        // std::cout << temp->data.id << " " << temp->data.username << " " << temp->data.password << " " << temp->data.email << " " << temp->data.origin << std::endl;
                        return;
                    }
                    break;
                case 2:
                    if (temp->data.password == data.password) {
                        // std::cout << temp->data.id << " " << temp->data.username << " " << temp->data.password << " " << temp->data.email << " " << temp->data.origin << std::endl;
                        return;
                    }
                    break;
                case 3:
                    if (temp->data.email == data.email) {
                        // std::cout << temp->data.id << " " << temp->data.username << " " << temp->data.password << " " << temp->data.email << " " << temp->data.origin << std::endl;
                        return;
                    }
                    break;
                case 4:
                    if (temp->data.origin == data.origin) {
                        // std::cout << temp->data.id << " " << temp->data.username << " " << temp->data.password << " " << temp->data.email << " " << temp->data.origin << std::endl;
                        return;
                    }
                    break;
                default:
                    // std::cout << "Invalid field" << std::endl;
                    return;
            }
            temp = temp->next;
        }
        // std::cout << "Data not found" << std::endl;
    }
    linkedlist(tableData& data, std::string salt = "salt") {
        head = NULL;
        tail = NULL;
    }
    ~linkedlist() {
        Node* temp = head;
        while (temp != NULL) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};
#endif
