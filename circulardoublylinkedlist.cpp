#include "CircularDoublyLinkedList.h"
#include <QPainter>
#include <QPen>
#include <QPolygon>
#include <QPainterPath>
#include <QPointF>
#include "QLabel"

// Constructor
CircularDoublyLinkedListVisualization::CircularDoublyLinkedListVisualization(QWidget* parent)
    : QWidget(parent), doublyLinkedList(nullptr), scale(1.0) {

    dataInput = new QLineEdit(this);
    addButton = new QPushButton("Add Node at Last", this);
    addHeadButton = new QPushButton("Add Node at Head", this);
    removeButton = new QPushButton("Remove Node", this);
    zoomInButton = new QPushButton("Zoom In", this);
    zoomOutButton = new QPushButton("Zoom Out", this);

    // Set button colors to red with transparency
    QString buttonStyle = "QPushButton {"
                          "background-color: rgba(255, 0, 0, 150);"  // Semi-transparent red
                          "color: white;"
                          "border: none;"
                          "padding: 5px 10px;"
                          "border-radius: 5px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: rgba(139, 0, 0, 150);"  // Darker semi-transparent red
                          "}";
    addButton->setStyleSheet(buttonStyle);
    addHeadButton->setStyleSheet(buttonStyle);
    removeButton->setStyleSheet(buttonStyle);
    zoomInButton->setStyleSheet(buttonStyle);
    zoomOutButton->setStyleSheet(buttonStyle);

    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Label at the top center
    QLabel* titleLabel = new QLabel("Circular Doubly Linked List Visualization", this);
    titleLabel->setAlignment(Qt::AlignCenter); // Center align the text
    titleLabel->setStyleSheet("font-size: 38px; color: white;"); // Styling
    mainLayout->addWidget(titleLabel);

    // Visualization area (background of the widget)
    QWidget* visualizationArea = new QWidget(this);
    visualizationArea->setStyleSheet("background-color: transparent;"); // Transparent background
    visualizationArea->setAttribute(Qt::WA_TranslucentBackground, true); // Ensure true transparency
    mainLayout->addWidget(visualizationArea, 1);

    // Button layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(dataInput);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(addHeadButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);

    // Transparent widget to hold buttons
    QWidget* buttonContainer = new QWidget(this);
    buttonContainer->setLayout(buttonLayout);
    buttonContainer->setStyleSheet("background-color: transparent;"); // Transparent container
    buttonContainer->setAttribute(Qt::WA_TranslucentBackground, true); // True transparency
    mainLayout->addWidget(buttonContainer);

    connect(addButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        int value = dataInput->text().toInt(&ok);
        if (ok) {
            doublyLinkedList->insert(value);
            updateVisualization();
        }
    });

    connect(addHeadButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        int value = dataInput->text().toInt(&ok);
        if (ok) {
            doublyLinkedList->insertAtHead(value);
            updateVisualization();
        }
    });

    connect(removeButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        int value = dataInput->text().toInt(&ok);
        if (ok) {
            doublyLinkedList->remove(value);
            updateVisualization();
        }
    });

    connect(zoomInButton, &QPushButton::clicked, this, &CircularDoublyLinkedListVisualization::zoomIn);
    connect(zoomOutButton, &QPushButton::clicked, this, &CircularDoublyLinkedListVisualization::zoomOut);
}



// Set the list to visualize
void CircularDoublyLinkedListVisualization::setDoublyLinkedList(CircularDoublyLinkedList<int>* list) {
    doublyLinkedList = list;
    updateVisualization();
}

// Update the visualization
void CircularDoublyLinkedListVisualization::updateVisualization() {
    update();
}

// Paint event
void CircularDoublyLinkedListVisualization::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 2));

    if (!doublyLinkedList || !doublyLinkedList->getHead()) {
        return; // No nodes to paint
    }

    const int nodeWidth = 60 * scale;
    const int nodeHeight = 35 * scale;
    const int horizontalSpacing = 40 * scale;

    DoublyNode<int>* current = doublyLinkedList->getHead();
    int x =150; // Starting X
    int y = 200;               // Starting Y

    QRect headNodeRect, lastNodeRect;

    do {
        QRect nodeRect(x, y, nodeWidth, nodeHeight);
        painter.drawRect(nodeRect);
        painter.drawText(nodeRect, Qt::AlignCenter, QString::number(current->data));

        if (current == doublyLinkedList->getHead()) {
            headNodeRect = nodeRect;
        }
        lastNodeRect = nodeRect;

        // Forward Arrow (Next Node)
        if (current->next != doublyLinkedList->getHead()) {
            int arrowX = x + nodeWidth;
            int arrowY = y + nodeHeight / 3;
            painter.drawLine(arrowX, arrowY, arrowX + horizontalSpacing - 5*scale, arrowY);
            QPointF start(arrowX + horizontalSpacing, arrowY );
            QPointF end(arrowX + horizontalSpacing - 5*scale, arrowY); // Adjust the end point as needed

            drawArrow(painter, end, start, 5); // Example arrow size
        }

        // Backward Arrow (Prev Node)
        if (current != doublyLinkedList->getHead()) {
            // Position of the previous node (to the left of the current node)
            int prevX = x - horizontalSpacing;  // Position to the left of the current node
            int prevY = y + nodeHeight * 0.7;  // Vertical center of the current node

            // Adjust to start at the half part of the link width of the previous node
            painter.drawLine(prevX, prevY, x, prevY);  // Line from the previous node to the current one

            // Draw the reverse arrowhead (pointing left)
            QPointF start(prevX, prevY );
            QPointF end(prevX + horizontalSpacing , prevY); // Adjust the end point as needed

            drawArrow(painter, end, start, 5);

        }


        x += nodeWidth + horizontalSpacing;
        current = current->next;
    } while (current != doublyLinkedList->getHead());

    drawReturnArrow(painter, lastNodeRect, headNodeRect,-1);
    drawReturnArrow(painter, lastNodeRect, headNodeRect,1);
}

// Draw an arrow
// In CircularDoublyLinkedListVisualization definition (circulardoublylinkedlist.cpp)
void CircularDoublyLinkedListVisualization::drawArrow(QPainter& painter, QPointF start, QPointF end, int arrowSize) {
    QPolygon arrowHead;

    // Scale the arrow size based on the current zoom scale
    int scaledArrowSize = static_cast<int>(arrowSize * scale);

    // Convert QPointF to QPoint for QPolygon
    if (end.x() > start.x()) { // Rightward arrow
        arrowHead << QPoint(end.x(), end.y())
                  << QPoint(end.x() - scaledArrowSize, end.y() - scaledArrowSize)
                  << QPoint(end.x() - scaledArrowSize, end.y() + scaledArrowSize);
    } else { // Leftward arrow
        arrowHead << QPoint(end.x(), end.y())
                  << QPoint(end.x() + scaledArrowSize, end.y() - scaledArrowSize)
                  << QPoint(end.x() + scaledArrowSize, end.y() + scaledArrowSize);
    }

    painter.drawPolygon(arrowHead);
}


void CircularDoublyLinkedListVisualization::drawReturnArrow(QPainter& painter, const QRect& lastNodeRect, const QRect& headNodeRect, const int direction) {
    int startX ;
    int startY,endY;
    int endX;
    if (direction != -1)
    {
        startX = lastNodeRect.right() + 8* scale;
        startY = lastNodeRect.center().y() - 5 *scale;
        endY = headNodeRect.center().y() - 5 *scale;
        endX = headNodeRect.left();
    }
    else
    {
        startX = lastNodeRect.right();
        startY = lastNodeRect.center().y() + 5 *scale;
        endY = headNodeRect.center().y() + 5 *scale;
        endX = headNodeRect.left() - 5 * scale;
    }

    // Convert to QPointF (floating-point coordinates)
    QPointF start(startX, startY);
    QPointF end(endX, endY);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 2));

    // Draw cubic Bezier curve for the return arrow
    QPainterPath path;
    if (direction != -1) {
        // Path for upward cubic Bezier curve when direction is forward
        path.moveTo(start);
        path.cubicTo(start.x() + 45 * scale, start.y() - 100 * scale,
                     end.x() - 45 * scale, end.y() - 100 * scale,
                     end.x() - 3*scale, end.y());
    } else {

        // Path for downward cubic Bezier curve when direction is reversed
        path.moveTo(start);
        path.cubicTo(start.x() + 45 * scale, start.y() + 100 * scale,
                     end.x() - 45 * scale, end.y() + 100 * scale,
                     end.x()+2*scale, end.y());
    }
    painter.drawPath(path);

    // Draw the arrows
    if (direction != -1) {

        drawArrow(painter, end, start, 5);
    } else {

        drawArrow(painter, start, end, 5);
    }
}



// Zoom in
void CircularDoublyLinkedListVisualization::zoomIn() {
    scale += 0.1;
    update();
}

// Zoom out
void CircularDoublyLinkedListVisualization::zoomOut() {
    scale = std::max(0.1, scale - 0.1);
    update();
}
