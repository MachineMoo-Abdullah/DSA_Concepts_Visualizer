#include "linkedlistvisualization.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QMouseEvent>

LinkedListVisualization::LinkedListVisualization(QWidget* parent)
    : QWidget(parent), linkedList(new LinkedList<int>()), scale(1.0), traversedNode(nullptr) {

    // Set window size larger, similar to BinaryTreeMainWindow
    setFixedSize(1200, 600);

    // Set background color to black and text color to white for the window
    setStyleSheet("background-color: black; color: white;");

    // Set up layout and widgets
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Create the title label
    QLabel* titleLabel = new QLabel("Singly Linked List Visualization", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);  // Set the font size to a larger value
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    // Add title label to the top of the layout
    mainLayout->addWidget(titleLabel);

    // Create the input field
    dataInput = new QLineEdit(this);
    dataInput->setPlaceholderText("Enter a value to add/remove");
    dataInput->setFixedHeight(30);

    // Create the "Add Node" button
    addButton = new QPushButton("Add Node at head", this);
    addButton->setFixedHeight(30);

    addtailButton = new QPushButton("Add Node at Last", this);
    addtailButton->setFixedHeight(30);
    removeButton = new QPushButton("Remove Node", this);
    removeButton->setFixedHeight(30);

    // Create Zoom In button
    zoomInButton = new QPushButton("Zoom In", this);
    zoomInButton->setFixedHeight(30);

    // Create Zoom Out button
    zoomOutButton = new QPushButton("Zoom Out", this);
    zoomOutButton->setFixedHeight(30);

    // Ensure the input field and buttons have the same width
    addButton->setFixedWidth(150);
    removeButton->setFixedWidth(150);
    zoomInButton->setFixedWidth(150);
    zoomOutButton->setFixedWidth(150);
    dataInput->setFixedWidth(150);
    addtailButton->setFixedWidth(150);

    // Set button colors (red background, white text)
    addButton->setStyleSheet("background-color: red; color: white;");
    removeButton->setStyleSheet("background-color: red; color: white;");
    zoomInButton->setStyleSheet("background-color: red; color: white;");
    zoomOutButton->setStyleSheet("background-color: red; color: white;");
    addtailButton->setStyleSheet("background-color: red; color: white;");

    // Layout for the input field and buttons at the bottom
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(dataInput);
    bottomLayout->addWidget(addButton);
    bottomLayout->addWidget(removeButton);
    bottomLayout->addWidget(zoomInButton);
    bottomLayout->addWidget(zoomOutButton);
    bottomLayout->addWidget(addtailButton);

    // Spacer to push the visualization to the top
    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(spacer);

    // Connect buttons' click events
    connect(addButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        int value = dataInput->text().toInt(&ok);
        if (ok) {
            insert(value);
            updateVisualization();
        }
        dataInput->clear();  // Clear input after adding node
    });

    connect(removeButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        int value = dataInput->text().toInt(&ok);
        if (ok) {
            linkedList->remove(value);
            updateVisualization();
        }
        dataInput->clear();  // Clear input after removing node
    });

    connect(addtailButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        int value = dataInput->text().toInt(&ok);
        if (ok) {
            linkedList->insertAtLast(value);
            updateVisualization();
        }
    });

    connect(zoomInButton, &QPushButton::clicked, this, &LinkedListVisualization::zoomIn);
    connect(zoomOutButton, &QPushButton::clicked, this, &LinkedListVisualization::zoomOut);

    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);
}

void LinkedListVisualization::setLinkedList(LinkedList<int>* list) {
    linkedList = list;
    update();  // Trigger a repaint of the widget to visualize the linked list
}

void LinkedListVisualization::setTraversedNode(Node<int>* node) {
    traversedNode = node;
    update();  // Repaint to show traversal highlight
}

void LinkedListVisualization::updateVisualization() {
    update();  // Repaint when the list changes
}

void LinkedListVisualization::zoomIn() {
    if (scale < 2.0) {
        scale += 0.1;
        updateVisualization();
    }
}

void LinkedListVisualization::zoomOut() {
    if (scale > 0.2) {
        scale -= 0.1;
        updateVisualization();
    }
}

void LinkedListVisualization::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::white));  // Default color for the outline

    if (linkedList != nullptr) {
        Node<int>* current = linkedList->getHead();
        int xPos = 100;
        int yPos = 150;
        const int nodeHeight = 50;
        const int nodeSpacing = 130;
        const int dataWidth = 50;
        const int linkWidth2 = 25;

        QFont font = painter.font();
        font.setPointSize(12 * scale);
        painter.setFont(font);

        bool isHead = true;

        while (current != nullptr) {
            painter.setPen(QPen(Qt::white));
            if (isHead) {
                painter.setPen(QPen(Qt::white));
                painter.drawText(xPos, yPos - 10, "Head");
                isHead = false;
            }

            // Draw the node rectangle
            painter.drawRect(xPos, yPos, dataWidth * scale, nodeHeight * scale);
            painter.setBrush(QBrush(Qt::black));  // Normal color


            // Draw the text (node data)
            QRect textRect(xPos, yPos, dataWidth * scale, nodeHeight * scale);
            painter.drawText(textRect, Qt::AlignCenter, QString::number(current->data));

            // Draw the link rectangle (arrow part)
            painter.setPen(QPen(Qt::white, 1));
            painter.drawLine(xPos + dataWidth * scale, yPos, xPos + dataWidth * scale, yPos + nodeHeight * scale);

            painter.setPen(QPen(Qt::white, 1));
            painter.drawRect(xPos + dataWidth * scale , yPos, linkWidth2 * scale, nodeHeight * scale);

            if (current->next != nullptr) {
                int lineStartX = xPos + dataWidth * scale + linkWidth2 * scale - 5;
                int lineEndX = xPos + nodeSpacing * scale;
                int lineY = yPos + nodeHeight * scale / 2;

                // Draw the line and arrow between nodes
                painter.drawLine(lineStartX, lineY, lineEndX, lineY);

                int arrowSize = 10;
                QPolygon arrowHead;
                arrowHead << QPoint(lineEndX, lineY);
                arrowHead << QPoint(lineEndX - arrowSize, lineY - arrowSize / 2);
                arrowHead << QPoint(lineEndX - arrowSize, lineY + arrowSize / 2);
                painter.setPen(QPen(Qt::white));
                painter.drawPolygon(arrowHead);
            } else {
                int crossX = xPos + dataWidth * scale + linkWidth2 * scale / 2;
                int crossY = yPos + nodeHeight * scale / 2;

                painter.setPen(QPen(Qt::red, 1.5));
                painter.drawLine(crossX - 3, crossY - 3, crossX + 3, crossY + 3);
                painter.drawLine(crossX - 3, crossY + 3, crossX + 3, crossY - 3);
            }

            xPos += nodeSpacing * scale;
            current = current->next;
        }
    }
}
void LinkedListVisualization::insert(int value) {
    linkedList->insert(value);
    setTraversedNode(linkedList->getHead());  // Set head as the traversed node (or any other node)
}
void LinkedListVisualization::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        zoomIn();
    } else if (event->button() == Qt::RightButton) {
        zoomOut();
    }
}
