#ifndef LINKEDLISTVISUALIZATION_H
#define LINKEDLISTVISUALIZATION_H

#include <QWidget>
#include "singlynode.h"
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>



// Template class definition for LinkedList
template<typename T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList(); // Destructor

    void insert(T value);
    void remove(T value);
    void insertAtLast(T value);
    Node<T>* getHead() const;

private:
    Node<T>* head;
};

// LinkedList constructor
template<typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

// LinkedList destructor
template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// Insert node at the head of the list
template <typename T>
void LinkedList<T>::insert(T value) {
    Node<T>* newNode = new Node<T>(value);

    if (!head) {
        head = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

// Insert node at the end of the list
template <typename T>
void LinkedList<T>::insertAtLast(T value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
    } else {
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Remove node by value
template<typename T>
void LinkedList<T>::remove(T value) {
    Node<T>* current = head;
    Node<T>* prev = nullptr;

    if (head == nullptr) return;

    // Find the node to remove
    while (current != nullptr && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return;

    if (prev == nullptr) { // Removing the head
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
}

// Get the head of the list
template<typename T>
Node<T>* LinkedList<T>::getHead() const {
    return head;
}

// LinkedListVisualization class
class LinkedListVisualization : public QWidget {
    Q_OBJECT

public:
    explicit LinkedListVisualization(QWidget* parent = nullptr);

    void setLinkedList(LinkedList<int>* list);  // Set the linked list for visualization
    void setTraversedNode(Node<int>* node);     // Set the traversed node

protected:
    void paintEvent(QPaintEvent* event) override;   // To handle the drawing of the linked list
    void mouseReleaseEvent(QMouseEvent* event) override; // To handle mouse events (zoom in/out)

private:
    void updateVisualization();  // Update the visual display
    void zoomIn();              // Zoom in the visualization
    void zoomOut();             // Zoom out the visualization
    void insert(int value);     // Insert method to visualize node insertion

    LinkedList<int>* linkedList; // Pointer to the linked list being visualized
    Node<int>* traversedNode;    // Pointer to the node currently being traversed
    double scale;                // Scale for zooming

    QLineEdit* dataInput;       // Input field for data
    QPushButton* addButton;     // Button to add nodes
    QPushButton* removeButton;  // Button to remove nodes
    QPushButton* zoomInButton;  // Button to zoom in
    QPushButton* zoomOutButton; // Button to zoom out
    QPushButton* addtailButton; // Button to add node at last

    const int nodeHeight = 30;   // Height for the node rectangle
    const int nodeSpacing = 100; // Horizontal spacing between nodes
    const int dataWidth = 30;    // Width for the data part of the node
    const int linkWidth2 = 15;   // Width for the link part (arrow part)
};

#endif // LINKEDLISTVISUALIZATION_H
