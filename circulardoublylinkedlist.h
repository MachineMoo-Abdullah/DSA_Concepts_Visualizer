#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "doublynode.h"
#include <QPainter>
#include "doublynode.h"

template <typename T>
class CircularDoublyLinkedList {
private:
    DoublyNode<T>* head;

public:
    CircularDoublyLinkedList() : head(nullptr) {}

    void insert(T value) {
        DoublyNode<T>* newNode = new DoublyNode<T>(value);
        if (!head) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            DoublyNode<T>* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    void insertAtHead(T value) {
        insert(value);
        head = head->prev; // New node becomes the head
    }

    void remove(T value) {
        if (!head) return;

        DoublyNode<T>* current = head;
        do {
            if (current->data == value) {
                if (current->next == current) { // Single node case
                    delete current;
                    head = nullptr;
                    return;
                }

                DoublyNode<T>* prevNode = current->prev;
                DoublyNode<T>* nextNode = current->next;

                prevNode->next = nextNode;
                nextNode->prev = prevNode;

                if (current == head) {
                    head = nextNode; // Update head if necessary
                }

                delete current;
                return;
            }
            current = current->next;
        } while (current != head);
    }

    DoublyNode<T>* getHead() {
        return head;
    }
};

class CircularDoublyLinkedListVisualization : public QWidget {
    Q_OBJECT

public:
    explicit CircularDoublyLinkedListVisualization(QWidget* parent = nullptr);
    void setDoublyLinkedList(CircularDoublyLinkedList<int>* list);
    void updateVisualization();

protected:
    void paintEvent(QPaintEvent* event) override;
    void drawArrow(QPainter& painter, QPointF start, QPointF end, int arrowSize);

    void drawReturnArrow(QPainter& painter, const QRect& lastNodeRect, const QRect& headNodeRect, const int direction);

private:
    CircularDoublyLinkedList<int>* doublyLinkedList;
    QLineEdit* dataInput;
    QPushButton* addButton;
    QPushButton* addHeadButton;
    QPushButton* removeButton;
    QPushButton* zoomInButton;
    QPushButton* zoomOutButton;
    double scale;

    void zoomIn();
    void zoomOut();
};

#endif // DOUBLYLINKEDLIST_H
