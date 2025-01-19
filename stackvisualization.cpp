#include "StackVisualization.h"
#include <QLabel>

StackVisualization::StackVisualization(QWidget* parent)
    : QWidget(parent),
    currentTraversalIndex(-1),
    elementToDelete(-1),
    isTransferToTemporary(true),
    traversalTimer(new QTimer(this)),
    scale(1.0),
    defaultColor(Qt::blue),
    traversingColor(Qt::red) {

    // Set the window background color to black
    this->setStyleSheet("background-color: black;");

    // Create and configure the title label
    QLabel* titleLabel = new QLabel("Stack Visualization", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);  // Set the font size to a larger value
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white;"); // Title text color

    // Main layout setup
    QVBoxLayout* allLayout = new QVBoxLayout(this);
    QHBoxLayout* mainLayout = new QHBoxLayout();  // Main layout
    QVBoxLayout* buttonLayout = new QVBoxLayout(); // Layout for buttons and inputs

    // Add title label to the main layout
    allLayout->addWidget(titleLabel);

    // Set up input fields
    dataInput = new QLineEdit(this);
    dataInput->setFixedSize(120, 30);
    dataInput->setPlaceholderText("Enter value");
    dataInput->setStyleSheet("background-color: white; color: black;");

    deleteInput = new QLineEdit(this);
    deleteInput->setFixedSize(120, 30);
    deleteInput->setPlaceholderText("Enter value to delete");
    deleteInput->setStyleSheet("background-color: white; color: black;");

    // Create buttons
    pushButton = new QPushButton("Push", this);
    popButton = new QPushButton("Pop", this);
    removeButton = new QPushButton("Remove Specific", this);
    zoomInButton = new QPushButton("Zoom In", this);
    zoomOutButton = new QPushButton("Zoom Out", this);

    // Apply styles to buttons
    QString buttonStyle = R"(
        QPushButton {
            background-color: red;
            color: white;
            font-size: 14px;
            border-radius: 5px;
            padding: 5px;
        }
        QPushButton:hover {
            background-color: darkred;
        }
    )";

    pushButton->setStyleSheet(buttonStyle);
    popButton->setStyleSheet(buttonStyle);
    removeButton->setStyleSheet(buttonStyle);
    zoomInButton->setStyleSheet(buttonStyle);
    zoomOutButton->setStyleSheet(buttonStyle);

    // Set fixed sizes for buttons
    pushButton->setFixedSize(120, 40);
    popButton->setFixedSize(120, 40);
    removeButton->setFixedSize(120, 40);
    zoomInButton->setFixedSize(120, 40);
    zoomOutButton->setFixedSize(120, 40);

    // Add input fields and buttons to the button layout
    buttonLayout->addWidget(dataInput);
    buttonLayout->addWidget(pushButton);
    buttonLayout->addWidget(popButton);
    buttonLayout->addWidget(deleteInput);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);
    buttonLayout->addStretch(); // Add stretch to align buttons to the top

    // Add main visualization area and buttons to the main layout
    mainLayout->addStretch();        // Push visualization to the left
    mainLayout->addLayout(buttonLayout); // Place buttons on the right

    allLayout->addLayout(mainLayout); // Add main layout to the overall layout
    setLayout(allLayout);             // Set the overall layout for the widget

    // Connect buttons to their respective slots
    connect(pushButton, &QPushButton::clicked, this, &StackVisualization::pushElement);
    connect(popButton, &QPushButton::clicked, this, &StackVisualization::popElement);
    connect(removeButton, &QPushButton::clicked, this, &StackVisualization::removeSpecificElement);
    connect(zoomInButton, &QPushButton::clicked, this, &StackVisualization::zoomIn);
    connect(zoomOutButton, &QPushButton::clicked, this, &StackVisualization::zoomOut);
    connect(traversalTimer, &QTimer::timeout, this, &StackVisualization::updateTraversal);
}


void StackVisualization::pushElement() {
    bool ok;
    int value = dataInput->text().toInt(&ok);
    if (ok) {
        stackData.insert(0, value); // Add element to the top
        update();
    }
}

void StackVisualization::popElement() {
    if (!stackData.isEmpty()) {
        // Directly remove the top element for a simple pop
        stackData.removeFirst();
        update(); // Redraw the stack
    } else {
        QMessageBox::warning(this, "Error", "Stack is empty.");
    }
}

void StackVisualization::zoomIn() {
    scale += 0.1;
    update();
}

void StackVisualization::zoomOut() {
    if (scale > 0.1) scale -= 0.1;
    update();
}
void StackVisualization::removeSpecificElement() {
    bool ok;
    int value = deleteInput->text().toInt(&ok); // Input from the user
    if (ok && !stackData.isEmpty()) {
        // Find the index of the element to delete
        elementToDelete = stackData.indexOf(value);
        if (elementToDelete != -1) {
            qDebug() << "Target element index:" << elementToDelete;
            // Initialize traversal
            currentTraversalIndex = 0;
            isTransferToTemporary = true;
            traversalTimer->start(500); // Animation interval
        } else {
            QMessageBox::warning(this, "Error", "Element not found in the stack.");
        }
    } else {
        QMessageBox::warning(this, "Error", "Invalid input or stack is empty.");
    }
}

void StackVisualization::updateTraversal() {

    qDebug() << "Starting traversal...";
    qDebug() << "Current stackData:" << stackData;
    qDebug() << "Temporary stack:" << temporaryStack;
    qDebug() << "CurrentTraversalIndex:" << currentTraversalIndex;
    qDebug() << "ElementToDelete:" << elementToDelete;

    if (isTransferToTemporary) {
        StackVisualization::removeSpecificElement();
        if (currentTraversalIndex < stackData.size()) {

            if (currentTraversalIndex == elementToDelete) {
                // Found the element to delete; remove it
                qDebug() << "Found target element, removing it...";
                popElement(); // Remove directly by index
                isTransferToTemporary = false; // Switch to restoration mode
            } else {
                // Move current element to the temporary stack
                qDebug() << "Transferring element to temporary stack:" << stackData[currentTraversalIndex];
                temporaryStack.prepend(stackData.takeAt(currentTraversalIndex));
                // Do not increment currentTraversalIndex here to avoid skipping the next element
            }
            currentTraversalIndex++; // Increment after moving element to the temporary stack or removing
        } else {
            // Traversal finished, but element not found
            qDebug() << "Traversal finished, element not found.";
            traversalTimer->stop();
            QMessageBox::warning(this, "Error", "Element not found in the stack.");
        }
    } else {
        // Restore elements from the temporary stack
        if (!temporaryStack.isEmpty()) {
            qDebug() << "Restoring element from temporary stack:" << temporaryStack.last();
            stackData.append(temporaryStack.takeLast());
        } else {
            // Restoration complete
            qDebug() << "Restoration complete.";
            traversalTimer->stop();
            currentTraversalIndex = -1;
            elementToDelete = -1;
        }
    }

    qDebug() << "End of updateTraversal iteration.";
    qDebug() << "Updated stackData:" << stackData;
    qDebug() << "Updated temporaryStack:" << temporaryStack;

    update(); // Redraw the visualization
}


void StackVisualization::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int x = width() / 2;
    int y = 150; // Start from top
    int nodeHeight = 40 * scale;
    int nodeWidth = 70 * scale;

    QFont labelFont = painter.font();
    labelFont.setPointSize(15 * scale);  // Set a larger font size
    painter.setFont(labelFont);

    // Draw label for Stack 1
    painter.setPen(Qt::white);
    painter.drawText(x - nodeWidth / 2, y + 10 * scale, "Stack 1");

    // Draw the box for Stack 1 (primary stack)
    if (!stackData.isEmpty())
    {
        QRect stackBox(x - nodeWidth / 2 - 10, y - 10, nodeWidth + 20, stackData.size() * (nodeHeight + 10) + 20);  // Adjust the size to fit nodes
        painter.setPen(Qt::white);
        painter.drawRect(stackBox);
    }
    labelFont.setPointSize(12);  // Set a smaller font size for stack nodes
    painter.setFont(labelFont);

    // Draw primary stack (Stack 1) elements
    y += 30;  // Move down to leave space for the label
    for (int i = 0; i < stackData.size(); ++i) {
        QRect rect(x - nodeWidth / 2, y, nodeWidth, nodeHeight);

        // Highlight only the current traversal index if transferring to temporary stack
        if (i == currentTraversalIndex && isTransferToTemporary) {
            painter.setBrush(traversingColor); // Highlight during traversal
        } else {
            painter.setBrush(defaultColor);
        }

        painter.drawRect(rect);
        painter.setPen(Qt::white);
        painter.drawText(rect, Qt::AlignCenter, QString::number(stackData[i]));

        y += nodeHeight + 10; // Move to the next position
    }

    painter.setPen(Qt::white);
    // Draw label for Stack 2 (Temporary stack)
    labelFont.setPointSize(15 * scale);  // Set a larger font size for Stack 2 label
    painter.setFont(labelFont);
    y = 150;  // Reset Y position for second stack
    painter.drawText(x - 150 - nodeWidth / 2, y + 10 * scale, "Stack 2");

    if (!temporaryStack.isEmpty()) {
        int tempStackHeight = temporaryStack.size() * (nodeHeight + 10); // Total height based on elements
        QRect tempStackBox(x - 150 - nodeWidth / 2 - 10, y - 10, nodeWidth + 20, tempStackHeight + 20);

        painter.setPen(Qt::white); // Ensure the pen color is set correctly
        painter.setBrush(Qt::NoBrush); // Avoid filling the bounding box
        painter.drawRect(tempStackBox);
    }



    labelFont.setPointSize(12);  // Set a smaller font size for stack nodes
    painter.setFont(labelFont);

    // Draw temporary stack (Stack 2) elements
    y += 30; // Reset and adjust Y position for second stack
    for (int i = 0; i < temporaryStack.size(); ++i) {
        QRect rect(x - 150 - nodeWidth / 2, y, nodeWidth, nodeHeight);

        // Highlight if restoring from the temporary stack
        if (i == temporaryStack.size() - 1 && !isTransferToTemporary) {
            painter.setBrush(traversingColor); // Highlight the top of the temporary stack
        } else {
            painter.setBrush(defaultColor);
        }

        painter.drawRect(rect);
        painter.setPen(Qt::white);
        painter.drawText(rect, Qt::AlignCenter, QString::number(temporaryStack[i]));

        y += nodeHeight + 10; // Move to the next position
    }

}

