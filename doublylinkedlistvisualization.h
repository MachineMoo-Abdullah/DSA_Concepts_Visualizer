#ifndef DOUBLYLINKEDLISTVISUALIZATION_H
#define DOUBLYLINKEDLISTVISUALIZATION_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include "doublynode.h"
#include <QMouseEvent>


// Doubly Linked List class definition
template <typename T>
class DoublyLinkedList {
private:
    DoublyNode<T>* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    // Insert a new value into the list
    void insert(T value) {
        DoublyNode<T>* newNode = new DoublyNode<T>(value);
        if (!head) {
            head = newNode;
        } else {
            DoublyNode<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }
    void insertAtHead(T value) {
        DoublyNode<T>* newNode = new DoublyNode<T>(value);

        if (!head) {
            // If the list is empty
            head = newNode;
            head->next = nullptr;
            head->prev = nullptr;
        } else {
            // If the list is not empty
            newNode->next = head;
            newNode->prev = nullptr;

            head->prev = newNode;
            head = newNode;
        }
    }

    // Remove a value from the list
    void remove(T value) {
        DoublyNode<T>* current = head;
        while (current) {
            if (current->data == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                }
                delete current;
                return;
            }
            current = current->next;
        }
    }

    // Getter for the head of the list
    DoublyNode<T>* getHead() const {
        return head;
    }
};


// Visualization class for the doubly linked list
class DoublyLinkedListVisualization : public QWidget {
    Q_OBJECT  // Add this line

public:
    explicit DoublyLinkedListVisualization(QWidget* parent = nullptr);

    // Set the doubly linked list to visualize
    void setDoublyLinkedList(DoublyLinkedList<int>* list);

    // Update visualization (manual refresh of the widget)
    void updateVisualization();

protected:
    // Paint event to render the visualization
    void paintEvent(QPaintEvent* event) override;

    // Mouse event for interaction
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    DoublyLinkedList<int>* doublyLinkedList;  // The linked list instance
    DoublyNode<int>* traversedNode;  // Node currently being traversed
    double scale;  // Scale for zooming
    QLineEdit* dataInput;  // Input field for data
    QPushButton* addButton;  // Button to add a node
    QPushButton* removeButton;  // Button to remove a node
    QPushButton* zoomInButton;  // Button for zooming in
    QPushButton* zoomOutButton;  // Button for zooming out
    QPushButton* addHeadButton;

private slots:
    // Slots to handle zoom in and zoom out actions
    void zoomIn();
    void zoomOut();
};

#endif // DOUBLYLINKEDLISTVISUALIZATION_H
