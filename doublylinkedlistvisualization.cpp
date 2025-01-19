#include "doublylinkedlistvisualization.h"
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QMouseEvent>
#include <QPen>
#include <QLabel>
/*int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the linked list instance
    DoublyLinkedList<int> doublyLinkedList;

    // Create the visualization widget
    DoublyLinkedListVisualization* visualization = new DoublyLinkedListVisualization();
    visualization->setDoublyLinkedList(&doublyLinkedList);

    // Set up the main window layout
    QWidget mainWindow;
    QVBoxLayout* layout = new QVBoxLayout(&mainWindow);
    layout->addWidget(visualization);

    mainWindow.setWindowTitle("Doubly Linked List Visualization");
    mainWindow.resize(500, 400);
    mainWindow.show();

    doublyLinkedList.insert(10);
    doublyLinkedList.insert(20);
    doublyLinkedList.insert(30);

    // Remove a node
    doublyLinkedList.remove(20);

    visualization->updateVisualization();

    return app.exec();
}
*/
// Constructor for DoublyLinkedListVisualization
DoublyLinkedListVisualization::DoublyLinkedListVisualization(QWidget* parent)
    : QWidget(parent),
    doublyLinkedList(nullptr),
    traversedNode(nullptr),
    scale(1.0) {


    // Set window size larger, similar to BinaryTreeMainWindow
    setFixedSize(1200, 600);
    QLabel* titleLabel = new QLabel("Doubly Linked List Visualization", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);  // Set the font size to a larger value
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    // Set up layout and widgets
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Create the title label


    // Add title label to the top of the layout
    mainLayout->addWidget(titleLabel);


    // Create the input field
    dataInput = new QLineEdit(this);
    dataInput->setPlaceholderText("Enter a value to add/remove");
    dataInput->setFixedHeight(30);

    // Create the "Add Node" button
    addHeadButton = new QPushButton("Add Node at head", this);
    addHeadButton->setFixedHeight(30);

    addButton = new QPushButton("Add Node at Last", this);
    addButton->setFixedHeight(30);
    removeButton = new QPushButton("Remove Node", this);
    removeButton->setFixedHeight(30);

    // Create Zoom In button
    zoomInButton = new QPushButton("Zoom In", this);
    zoomInButton->setFixedHeight(30);

    // Create Zoom Out button
    zoomOutButton = new QPushButton("Zoom Out", this);
    zoomOutButton->setFixedHeight(30);

    // Ensure the input field and buttons have the same width
    addHeadButton->setFixedWidth(150);
    removeButton->setFixedWidth(150);
    zoomInButton->setFixedWidth(150);
    zoomOutButton->setFixedWidth(150);
    dataInput->setFixedWidth(150);
    addButton->setFixedWidth(150);

    // Set button colors (red background, white text)
    addHeadButton->setStyleSheet("background-color: red; color: white;");
    removeButton->setStyleSheet("background-color: red; color: white;");
    zoomInButton->setStyleSheet("background-color: red; color: white;");
    zoomOutButton->setStyleSheet("background-color: red; color: white;");
    addButton->setStyleSheet("background-color: red; color: white;");

    // Layout for the input field and buttons at the bottom
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(dataInput);
    bottomLayout->addWidget(addHeadButton);
    bottomLayout->addWidget(removeButton);
    bottomLayout->addWidget(zoomInButton);
    bottomLayout->addWidget(zoomOutButton);
    bottomLayout->addWidget(addButton);

    // Spacer to push the visualization to the top
    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(spacer);

    // Connect buttons to their respective functions
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

    connect(zoomInButton, &QPushButton::clicked, this, &DoublyLinkedListVisualization::zoomIn);
    connect(zoomOutButton, &QPushButton::clicked, this, &DoublyLinkedListVisualization::zoomOut);


    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);

    }


void DoublyLinkedListVisualization::setDoublyLinkedList(DoublyLinkedList<int>* list) {
    doublyLinkedList = list;
    updateVisualization();
}

void DoublyLinkedListVisualization::updateVisualization() {
    update();
}
void DoublyLinkedListVisualization::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!doublyLinkedList) return;

    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);

    // Scale the font size based on zoom level
    QFont font = painter.font();
    font.setPointSizeF(12 * scale);  // Scale font size dynamically with zoom level
    painter.setFont(font);

    int x = 50;  // Starting X position for the first node
    int y = 100; // Starting Y position for nodes
    const int nodeWidth = 50;       // Base node width (data part width)
    const int nodeHeight = 50;      // Base node height
    const int linkWidth = 15 * scale;  // Link width for previous and forward parts
    const int spacing = 100 * scale; // Dynamic spacing between nodes based on scale

    DoublyNode<int>* node = doublyLinkedList->getHead();
    while (node != nullptr) {
        // Adjust node size based on zoom scale
        int currentNodeWidth = nodeWidth * scale;
        int currentNodeHeight = nodeHeight * scale;
        int currentLinkWidth = linkWidth * scale;  // Dynamic link width

        // --- Draw the previous link part (left rectangle) ---
        if (node->prev != nullptr) {
            // Draw the left rectangle (previous link)
            painter.drawRect(x - currentLinkWidth, y, currentLinkWidth, currentNodeHeight); // Left rectangle for the previous link
        }
        else {
            painter.setPen(QPen(Qt::white));
            QRect prevRect(x - currentLinkWidth, y, currentLinkWidth, currentNodeHeight);

            painter.drawRect(prevRect);  // Draw the rectangle for the null link

            // Draw the red "X" inside the rectangle for null link (centered)
            int centerX = prevRect.center().x();
            int centerY = prevRect.center().y();
            int crossSize = 8 * scale;  // Size of the cross (adjustable based on scale)

            // Calculate half the cross size for symmetry
            int halfCrossSize = crossSize / 2;
            painter.setPen(QPen(Qt::red));
            // Draw the two diagonal lines for the cross, ensuring equal lengths
            painter.drawLine(centerX - halfCrossSize, centerY - halfCrossSize, centerX + halfCrossSize, centerY + halfCrossSize);  // Diagonal line from top-left to bottom-right
            painter.drawLine(centerX - halfCrossSize, centerY + halfCrossSize, centerX + halfCrossSize, centerY - halfCrossSize);  // Diagonal line from bottom-left to top-right

            painter.setPen(QPen(Qt::white));  // Reset pen color to black for other drawings
        }
        // --- Draw the current node's data part (center rectangle) ---
        painter.drawRect(x, y, currentNodeWidth, currentNodeHeight); // Node (center part)

        // Calculate the position of the text (centered inside the node)
        QRect textRect(x, y, currentNodeWidth, currentNodeHeight);
        painter.drawText(textRect, Qt::AlignCenter, QString::number(node->data)); // Draw the node's data

        // --- Draw the forward link part (right rectangle) ---
        if (node->next != nullptr) {
            // Draw the right rectangle (forward link)
            painter.drawRect(x + currentNodeWidth, y, currentLinkWidth, currentNodeHeight); // Right rectangle for the forward link
        }
        else {
            painter.setPen(QPen(Qt::white));
            QRect nextRect(x + currentNodeWidth, y, currentLinkWidth, currentNodeHeight);
            painter.drawRect(nextRect);  // Draw the rectangle for the null link

            // Draw the red "X" inside the rectangle for null link (centered)
            // Draw the red "X" inside the rectangle for null link (centered)
            int centerX = nextRect.center().x();
            int centerY = nextRect.center().y();
            int crossSize = 8  * scale;  // Size of the cross (adjustable based on scale)

            // Calculate half the cross size for symmetry
            int halfCrossSize = crossSize / 2;
            painter.setPen(QPen(Qt::red));
            // Draw the two diagonal lines for the cross, ensuring equal lengths
            painter.drawLine(centerX - halfCrossSize, centerY - halfCrossSize, centerX + halfCrossSize, centerY + halfCrossSize);  // Diagonal line from top-left to bottom-right
            painter.drawLine(centerX - halfCrossSize, centerY + halfCrossSize, centerX + halfCrossSize, centerY - halfCrossSize);  // Diagonal line from bottom-left to top-right

            painter.setPen(QPen(Qt::white));  // Reset pen color to black for other drawings
        }

        // --- Draw the forward link (line) to the next node ---
        if (node->next != nullptr) {
            int nextX = x + currentNodeWidth + currentLinkWidth / 2; // Position to the right of the current node
            int nextY = y + currentNodeHeight * 0.7;                // Vertical center of the node

            // Draw the line connecting the right edge of the current node to the left edge of the next node
            int lineEndX = nextX + spacing - currentLinkWidth/2;       // Adjust to end at the start of the link width of the next node
            painter.drawLine(nextX, nextY, lineEndX, nextY);

            // Dynamic arrow size based on scale
            int arrowSize = 5 * scale;

            // Draw the forward arrowhead
            QPolygon arrowHead;
            arrowHead << QPoint(lineEndX, nextY);                      // Start of the arrowhead
            arrowHead << QPoint(lineEndX - arrowSize, nextY - arrowSize); // Top of the arrowhead
            arrowHead << QPoint(lineEndX - arrowSize, nextY + arrowSize); // Bottom of the arrowhead
            painter.drawPolygon(arrowHead);
        }

        // --- Draw the reverse link (line) from the previous node ---
        if (node->prev != nullptr) {
            int prevX = x - currentLinkWidth / 2;                   // Position to the left of the current node
            int prevY = y + currentNodeHeight * 0.5;                // Vertical center of the node

            // Draw the line connecting the left edge of the current node to the right edge of the previous node
            int lineStartX = prevX - spacing + currentLinkWidth / 2;     // Adjust to start at the half part of the link width of the previous node
            painter.drawLine(prevX, prevY, lineStartX, prevY);

            // Dynamic arrow size based on scale
            int reverseArrowSize = 5 * scale;

            // Draw the reverse arrowhead
            QPolygon reverseArrow;
            reverseArrow << QPoint(lineStartX, prevY);                  // Start of the arrowhead
            reverseArrow << QPoint(lineStartX + reverseArrowSize, prevY - reverseArrowSize); // Top of the arrowhead
            reverseArrow << QPoint(lineStartX + reverseArrowSize, prevY + reverseArrowSize); // Bottom of the arrowhead
            painter.drawPolygon(reverseArrow);
        }

        if (node == doublyLinkedList->getHead()) {
            QFont headFont = painter.font();
            headFont.setPointSizeF(10 * scale);
            painter.setFont(headFont);

            // Draw the "Head" label above the head node
            QRect labelRect(x, y - 20 * scale, currentNodeWidth, 20 * scale); // Adjust position above the node
            painter.drawText(labelRect, Qt::AlignCenter, "Head");
        }
        // Move to the next node's position
        x += currentNodeWidth + currentLinkWidth + spacing; // Move to the next position for the next node
        node = node->next;
    }
}



void DoublyLinkedListVisualization::mouseReleaseEvent(QMouseEvent* event) {
    QWidget::mouseReleaseEvent(event);
}

// Zoom In action
void DoublyLinkedListVisualization::zoomIn() {
    scale += 0.1;
    update();
}

// Zoom Out action
void DoublyLinkedListVisualization::zoomOut() {
    scale -= 0.1;
    if (scale < 0.1) scale = 0.1;
    update();
}
