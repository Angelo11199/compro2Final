#ifndef linkedlist_H
#define linkedlist_H
#include <string>

#include "./print.h"
#include "./structures.h"

/**
 * @brief linkedlist class to store the data in a linked list
 *
 */
class linkedlist {
   private:
    struct Node {
        Node* next;
        tableData data;
    };
    Node* head;
    Node* tail;
    /**
     * @brief Allocate a new node and store the data
     *
     * @private
     * @param tableData data to be stored
     */
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
    /**
     * @brief Construct a new linkedlist object
     *
     */
    linkedlist() {
        head = NULL;
        tail = NULL;
    }
    /**
     * @brief Insert the data into the linked list
     *
     * @param data tableData to be inserted
     */
    void insert(tableData& data) {
        allocateNode(data);
    }
    /**
     * @brief Display the data in the linked list
     *
     */
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
    /**
     * @brief Delete the node from the linked list
     *
     * @param data tableData to be deleted
     * @param id id of the data to be deleted
     */
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
    /**
     * @brief Delete all the nodes from the linked list
     *
     */
    void deleteAll() {
        Node* temp = head;
        while (temp != NULL) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        head = NULL;
    }
    /**
     * @brief Update the node in the linked list
     *
     * @param oldData old data to be updated
     * @param newData new data to be updated
     */
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
    /**
     * @brief create a linked list from the tableData
     *
     * @param data tableData to be inserted
     * @param salt salt to be used. Default is "salt"
     */
    linkedlist(tableData& data, std::string salt = "salt") {
        head = NULL;
        tail = NULL;
    }
    /**
     * @brief Destroy the linkedlist object
     *
     */
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
