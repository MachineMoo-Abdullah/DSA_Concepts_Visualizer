#include "CircularSinglyLinkedList.h"
#include <QPainter>
#include <QPen>
#include <QLAbel>
#include <QPolygon>
#include <QRect>
#include <QPainterPath>

template class CircularSinglyLinkedList<int>;


CircularSinglyLinkedListVisualization::CircularSinglyLinkedListVisualization(QWidget* parent)
    : QWidget(parent), circularSinglyLinkedList(nullptr), scale(1.0) {

    setFixedSize(1200, 600);

    // Title label for the visualization
    QLabel* titleLabel = new QLabel("Circular Singly Linked List Visualization", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);  // Set the font size to a larger value
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white;"); // White text color for the title

    // Input and buttons
    dataInput = new QLineEdit(this);
    addButton = new QPushButton("Add Node at Last", this);
    addHeadButton = new QPushButton("Add Node at Head", this);
    removeButton = new QPushButton("Remove Node", this);
    zoomInButton = new QPushButton("Zoom In", this);
    zoomOutButton = new QPushButton("Zoom Out", this);

    // Button styles
    addButton->setStyleSheet("background-color: red; color: white;");
    addHeadButton->setStyleSheet("background-color: red; color: white;");
    removeButton->setStyleSheet("background-color: red; color: white;");
    zoomInButton->setStyleSheet("background-color: red; color: white;");
    zoomOutButton->setStyleSheet("background-color: red; color: white;");

    // Layout for buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(dataInput);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(addHeadButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);

    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);           // Add the title label at the top
    mainLayout->addStretch();                    // Add a spacer to fill vertical space
    mainLayout->addLayout(buttonLayout);         // Add the button layout at the bottom

    // Set the main layout for this widget
    setLayout(mainLayout);

    // Connect button signals to their respective slots
    connect(addButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        int value = dataInput->text().toInt(&ok);
        if (ok) {
            circularSinglyLinkedList->insert(value);
            updateVisualization();
        }
    });

    connect(addHeadButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        int value = dataInput->text().toInt(&ok);
        if (ok) {
            circularSinglyLinkedList->insertAtHead(value);
            updateVisualization();
        }
    });

    connect(removeButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        int value = dataInput->text().toInt(&ok);
        if (ok) {
            circularSinglyLinkedList->remove(value);
            updateVisualization();
        }
    });

    connect(zoomInButton, &QPushButton::clicked, this, &CircularSinglyLinkedListVisualization::zoomIn);
    connect(zoomOutButton, &QPushButton::clicked, this, &CircularSinglyLinkedListVisualization::zoomOut);
}


void CircularSinglyLinkedListVisualization::setCircularSinglyLinkedList(CircularSinglyLinkedList<int>* list) {
    circularSinglyLinkedList = list;
    updateVisualization();
}

void CircularSinglyLinkedListVisualization::updateVisualization() {
    update();
}

void CircularSinglyLinkedListVisualization::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!circularSinglyLinkedList) return;

    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);

    // Scale the font size based on zoom level
    QFont font = painter.font();
    font.setPointSizeF(12 * scale);
    painter.setFont(font);

    int x = 100;                     // Starting X position for the first node
    int y = 150;                    // Starting Y position for nodes
    const int nodeWidth = 50;       // Base node width (data part width)
    const int nodeHeight = 50;      // Base node height
    const int linkWidth = 25;       // Base link width
    const int spacing = 100;         // Spacing between nodes

    Node<int>* head = circularSinglyLinkedList->getHead();
    Node<int>* node = head;

    if (!node) return; // If list is empty, return immediately

    QVector<QRect> nodeRects; // Store rectangles of nodes for calculating connections
    QRect lastNodeRect;       // Rectangle for the last node

    // Declare the scaled link width before the loop
    int currentLinkWidth = linkWidth * scale;

    // Loop to draw the nodes and links
    do {
        // Adjust node dimensions based on scale
        int currentNodeWidth = nodeWidth * scale;
        int currentNodeHeight = nodeHeight * scale;

        // --- Draw the current node's data part ---
        QRect nodeRect(x, y, currentNodeWidth, currentNodeHeight);
        painter.drawRect(nodeRect);
        painter.drawText(nodeRect, Qt::AlignCenter, QString::number(node->data));
        nodeRects.append(nodeRect);

        // --- Label the head node ---
        if (node == head) {
            QRect labelRect(nodeRect.x(), nodeRect.y() - 20 * scale, currentNodeWidth, 20 * scale);
            painter.drawText(labelRect, Qt::AlignCenter, "Head");
        }

        QRect nextRect(x + currentNodeWidth, y, currentLinkWidth, currentNodeHeight);

        painter.drawRect(nextRect);


        // --- Draw the forward link (line) to the next node ---
        if (node->next != head) {
            int nextX = x + currentNodeWidth + currentLinkWidth/2;
            int nextY = y + currentNodeHeight * 0.4;

            int lineEndX = nextX + spacing+ currentLinkWidth/2;
            painter.drawLine(nextX, nextY, lineEndX, nextY);

            drawArrow(painter, lineEndX, nextY, -1);
        }



        // --- Store the last node's rectangle ---
        if (node->next == head) {
            lastNodeRect = QRect(x, y, currentNodeWidth, currentNodeHeight);
        }

        // Move to the next node
        x += currentNodeWidth + currentLinkWidth + spacing;
        node = node->next;

    } while (node && node != head);

    // --- Draw the circular connection arrow (last node to head) ---
    if (!nodeRects.isEmpty() && lastNodeRect.isValid()) {
        // Calculate the position of the last node's link center
        int startX = lastNodeRect.center().x() + currentLinkWidth * 2;
        int startY = lastNodeRect.bottom() + 20 * scale; // Below the last node

        int endX = nodeRects.first().x() - 6 * scale;
        int endY = nodeRects.first().bottom() - 10 * scale; // Above the first node

        // Draw the curved path
        QPainterPath path;
        int curveHeight = 50; // Increase this value to increase the curviness

        path.moveTo(startX, lastNodeRect.bottom()); // Start from the bottom of the last node
        path.cubicTo(startX, startY + curveHeight, endX, startY + curveHeight, endX, endY); // Smooth curve to the head
        painter.drawPath(path);

        // Draw arrowhead at the end of the curve
        drawArrow(painter, endX, endY, 1);
    }

}

// Helper function to draw a red "X" for null links
void CircularSinglyLinkedListVisualization::drawCross(QPainter& painter, const QRect& rect) {
    int centerX = rect.center().x();
    int centerY = rect.center().y();
    int crossSize = 8 * scale;

    int halfCrossSize = crossSize / 2;

    painter.drawLine(centerX - halfCrossSize, centerY - halfCrossSize, centerX + halfCrossSize, centerY + halfCrossSize);
    painter.drawLine(centerX - halfCrossSize, centerY + halfCrossSize, centerX + halfCrossSize, centerY - halfCrossSize);
}

// Helper function to draw arrows for links
void CircularSinglyLinkedListVisualization::drawArrow(QPainter& painter, int x, int y, int direction) {
    int arrowSize = 5 * scale;
    QPolygon arrowHead;
    if (direction > 0) { // Arrow pointing right
        arrowHead << QPoint(x, y) << QPoint(x + arrowSize, y - arrowSize) << QPoint(x + arrowSize, y + arrowSize);
    } else { // Arrow pointing left
        arrowHead << QPoint(x, y) << QPoint(x - arrowSize, y - arrowSize) << QPoint(x - arrowSize, y + arrowSize);
    }
    painter.drawPolygon(arrowHead);
}

void CircularSinglyLinkedListVisualization::zoomIn() {
    scale += 0.1;
    update();
}

void CircularSinglyLinkedListVisualization::zoomOut() {
    scale -= 0.1;
    if (scale < 0.1) scale = 0.1;
    update();
}


