
#include "binarytreemainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QMenuBar>
#include <QSpacerItem>
#include <qglobal.h>
#include <QTime>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QFileInfo>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>
#include <QStringList>
#include <QTableWidget>

BinaryTreeMainWindow::BinaryTreeMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QLabel* titleLabel = new QLabel("Binary Tree Visualization", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);  // Set the font size to a larger value
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    this->bst = this->getBST();

    // Build buttons and layout for buttons on the bottom of the window
    prop = new BST_Properties_Window(this);
    propertyButton = new QPushButton("&Properties", this);
    deleteButton = new QPushButton("&Delete", this);
    insertButton = new QPushButton("Insert", this);
    zoomInButton = new QPushButton("Zoom &In", this);
    zoomOutButton = new QPushButton("Zoom &Out", this);
    clearTreeButton = new QPushButton("Clear Tree", this);
    insertValueLineEdit = new QLineEdit;
    deleteValueLineEdit = new QLineEdit;
    statusLabel = new QLabel;

    // Set properties of buttons
    propertyButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    deleteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    insertButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    zoomInButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    zoomOutButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    clearTreeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Set grey background color for buttons
    propertyButton->setStyleSheet("background-color: red; color: white;");
    deleteButton->setStyleSheet("background-color: red; color: white;");
    insertButton->setStyleSheet("background-color: red; color: white;");
    zoomInButton->setStyleSheet("background-color: red; color: white;");
    zoomOutButton->setStyleSheet("background-color: red; color: white;");
    clearTreeButton->setStyleSheet("background-color: red; color: white;");

    insertValueLineEdit->setFixedWidth(200);
    insertValueLineEdit->setToolTip("Enter single value or multiple values separated by space");

    deleteValueLineEdit->setFixedWidth(100);
    deleteValueLineEdit->setToolTip("Enter value to delete");


    connect(clearTreeButton, SIGNAL(clicked()), this, SLOT(clearTreeClicked()));
    connect(propertyButton, SIGNAL(clicked()), this, SLOT(propertyClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomInClicked()));
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOutClicked()));
    connect(insertValueLineEdit, SIGNAL(returnPressed()), this, SLOT(insertClicked()));
    connect(deleteValueLineEdit, SIGNAL(returnPressed()), this, SLOT(deleteClicked()));

    // Create button layout and add buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(propertyButton);
    buttonLayout->addWidget(clearTreeButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(deleteValueLineEdit);
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(insertValueLineEdit);
    buttonLayout->addSpacing(25);
    buttonLayout->addWidget(statusLabel);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);

    // Create the render area (canvas for drawing the BST)
    renderArea = new RenderArea(this->bst);

    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderArea);

    // Pass any events that happen on the scroll area to the
    // render area (specifically clicking, so that renderArea
    // can zoom in/out when clicks happen
    treeScrollArea->installEventFilter(renderArea);

    // Create the main layout and add all the widgets to it
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(treeScrollArea);
    mainLayout->addLayout(buttonLayout);

    // Build the main window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setMinimumHeight(400);
    this->setWindowTitle("Binary Search Tree Visualization");
    //this->showMaximized();

    // Must show window before loading settings
    this->show();
}

void BinaryTreeMainWindow::clearTreeClicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm", "Are you sure you want to clear the whole tree?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        delete this->bst;
        this->bst = new BinarySearchTree<int>();
        this->renderArea->repaint();
        this->statusLabel->setText("Tree cleared.");
    }
}
void BinaryTreeMainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    this->renderArea->callRepaint();
}

BinaryTreeMainWindow::~BinaryTreeMainWindow()
{
    delete renderArea;
    delete propertyButton;
    delete deleteButton;
    delete insertButton;
    delete zoomInButton;
    delete zoomOutButton;
    delete treeScrollArea;
    delete bst;
    delete prop;
    delete centralWidget;
}


void BinaryTreeMainWindow::closeEvent(QCloseEvent *event)
{
    // Save BST before closing
    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer/last_bst.txt";

    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream writer(&file);

        // Save the BST in preorder traversal
        QString text = bst->getPreOrderTraversal();
        writer << text;
        file.close();

        qDebug() << "BST saved successfully to" << fileName;
        event->accept();  // Allow the application to close
    } else {
        qDebug() << "Failed to save BST to" << fileName;
        event->ignore();  // Prevent the application from closing if saving fails
    }
    prop->closePropertyWindow();
}

void BinaryTreeMainWindow::propertyClicked() const{
    if (!prop) {
        qDebug() << "Property window is not initialized!";
        return;
    }

    prop->update(this->bst); // Update the property window with the latest BST data
    prop->show();           // Show the property window
    prop->raise();          // Bring the property window to the foreground
    prop->activateWindow(); // Ensure the property window is active
}


// Slot for delete button
void BinaryTreeMainWindow::deleteClicked() {
    QString value = deleteValueLineEdit->text();

    if (!this->bst->deleteItem(value.toInt())) {
        // Show a message box if the value is not found
        QMessageBox::warning(this, "Delete Error", "The value '" + value + "' was not found in the tree.");
    } else {
        this->statusLabel->setText("Value deleted.");
    }

    this->renderArea->repaint(); // Repaint to show changes to the tree
    this->deleteValueLineEdit->setText(""); // Clear the text box
    return;
}


// Slot for insert button
void BinaryTreeMainWindow::insertClicked() const
{
    // Get entire line of text and iterate through the list of
    // values separated by whitespace - inserting all the values
    QString values = insertValueLineEdit->text();
    QStringList valueList = values.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    QStringListIterator iterator(valueList);

    while (iterator.hasNext())
    {
        if(!this->bst->insert(iterator.next().toInt())) // inserts 0 if text isn't an int
            this->statusLabel->setText("Duplicate valaue...");
        else
            this->statusLabel->setText("Value inserted...");
    }
    this->renderArea->repaint(); // repaint to show changes to tree
    insertValueLineEdit->setText(""); // clear text box
    return;
}

// Slot for zoom in button
void BinaryTreeMainWindow::zoomInClicked() const {
    this->statusLabel->setText("");
    renderArea->zoomIn();
    return;
}

// Slot for zoom out button
void BinaryTreeMainWindow::zoomOutClicked() const {
    this->statusLabel->setText("");
    renderArea->zoomOut();
    return;
}





BinarySearchTree<int>* BinaryTreeMainWindow::getBST()
{

    BinarySearchTree<int> *bst = new BinarySearchTree<int>;

    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer/last_bst.txt";

    QString text;
    QFile file(fileName);

    // If the file doesn't exist or if it can't open, return an empty bst
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return bst;
    }

    QTextStream reader(&file);

    while (!reader.atEnd())
    {
        reader >> text;
        if (text != " " && text != "")
            bst->insert(text.toInt());
    }

    file.close();
    return bst;
}

