#ifndef CIRCULARSINGLYLINKEDLIST_H
#define CIRCULARSINGLYLINKEDLIST_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "singlynode.h"
#include <QPainter>


// Define the CircularSinglyLinkedList template class
template <typename T>
class CircularSinglyLinkedList {
private:
    Node<T>* head;

public:
    CircularSinglyLinkedList() : head(nullptr) {}

    void insert(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
            head->next = head;
        } else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    void remove(T value) {
        if (!head) return;

        Node<T>* current = head;
        Node<T>* prev = nullptr;

        do {
            if (current->data == value) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    // Removing the head node
                    Node<T>* temp = head;
                    while (temp->next != head) {
                        temp = temp->next;
                    }
                    temp->next = head->next;
                    head = head->next;
                }

                delete current;
                return;
            }

            prev = current;
            current = current->next;
        } while (current != head);
    }

    void insertAtHead(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
            head->next = head;
        } else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
            head = newNode;
        }
    }

    Node<T>* getHead() {
        return head;
    }
};

// Visualization class definition
class CircularSinglyLinkedListVisualization : public QWidget {
    Q_OBJECT

private:
    CircularSinglyLinkedList<int>* circularSinglyLinkedList;
    QLineEdit* dataInput;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* zoomInButton;
    QPushButton* zoomOutButton;
    QPushButton* addHeadButton;
    double scale;

public:
    explicit CircularSinglyLinkedListVisualization(QWidget* parent = nullptr);
    void setCircularSinglyLinkedList(CircularSinglyLinkedList<int>* list);
    void updateVisualization();

protected:
    void paintEvent(QPaintEvent* event) override;
    void drawCross(QPainter& painter, const QRect& rect);
    void drawArrow(QPainter& painter, int x, int y, int direction);

private:
    void zoomIn();
    void zoomOut();
};

#endif // CIRCULARSINGLYLINKEDLIST_H
