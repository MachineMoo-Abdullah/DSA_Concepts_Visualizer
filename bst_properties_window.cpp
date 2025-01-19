
#include "bst_properties_window.h"
#include <iostream>
#include <QScrollArea>
#include <QTableWidget>
#include <QHBoxLayout>

BST_Properties_Window::BST_Properties_Window(QWidget *parent) : QMainWindow(parent)
{


    this->setWindowTitle("Properties");
    this->setFixedSize(QSize(400, 525));
    this->setStyleSheet("background-color: black; color: white;");

    // Example of adding a QLineEdit and QPushButton with specific styles
    QLineEdit *textBox = new QLineEdit(this);
    textBox->setPlaceholderText("Enter property...");
    textBox->setStyleSheet("background-color: white; color: black;");

    labelLayout = new QVBoxLayout;\
    heightLabel = new QLabel("Height:");
    nodeCountLabel = new QLabel("Node count:");
    leafNodesLabel = new QLabel("Leaf nodes:");
    internalNodesLabel = new QLabel("Internal nodes:");
    heightLabel->setStyleSheet("font-size: 14px;");
    nodeCountLabel->setStyleSheet("font-size: 14px;");
    leafNodesLabel->setStyleSheet("font-size: 14px;");
    internalNodesLabel->setStyleSheet("font-size: 14px;");

    labelLayout->addWidget(heightLabel);
    labelLayout->addWidget(nodeCountLabel);
    labelLayout->addWidget(leafNodesLabel);
    labelLayout->addWidget(internalNodesLabel);

    textAreaLayout = new QVBoxLayout;
    heightValue = new QLineEdit("");
    nodeCountValue = new QLineEdit("");
    leafNodesValue = new QLineEdit("");
    internalNodesValue = new QLineEdit("");
    heightValue->setReadOnly(true);
    nodeCountValue->setReadOnly(true);
    leafNodesValue->setReadOnly(true);
    internalNodesValue->setReadOnly(true);

    heightValue->setStyleSheet("color: white; width: 100px;"
                               "padding-left: 10px; font-size: 12px;");
    nodeCountValue->setStyleSheet("color: white; width: 100px;"
                                  "padding-left: 10px; font-size: 12px;");
    leafNodesValue->setStyleSheet("color: white; width: 100px;"
                                  "padding-left: 10px; font-size: 12px;");
    internalNodesValue->setStyleSheet("color: white; width: 100px;"
                                      "padding-left: 10px; font-size: 12px;");

    textAreaLayout->addWidget(heightValue);
    textAreaLayout->addWidget(nodeCountValue);
    textAreaLayout->addWidget(leafNodesValue);
    textAreaLayout->addWidget(internalNodesValue);

    containerLayout = new QHBoxLayout;
    containerLayout->addLayout(labelLayout);
    containerLayout->addLayout(textAreaLayout);


    preOrderTraversal = new QTextEdit;
    inOrderTraversal = new QTextEdit;
    postOrderTraversal = new QTextEdit;
    breadthFirstTraversal = new QTextEdit;
    preOrderTraversal->setReadOnly(true);
    inOrderTraversal->setReadOnly(true);
    postOrderTraversal->setReadOnly(true);
    breadthFirstTraversal->setReadOnly(true);

    exitButton = new QPushButton("E&xit", this);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitSlot()));
    exitButton->setStyleSheet("background-color: red; color: white;");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(exitButton);

    // Create the main layout and add all the widgets to it
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(containerLayout);
    mainLayout->addWidget(new QLabel("Preorder Traversal:"));
    mainLayout->addWidget(preOrderTraversal);
    mainLayout->addWidget(new QLabel("Inorder Traversal:"));
    mainLayout->addWidget(inOrderTraversal);
    mainLayout->addWidget(new QLabel("Postorder Traversal:"));
    mainLayout->addWidget(postOrderTraversal);
    mainLayout->addWidget(new QLabel("Breadthfirst Traversal"));
    mainLayout->addWidget(breadthFirstTraversal);
    mainLayout->addLayout(buttonLayout); // layout for ok/close button

    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);

    this->setCentralWidget(centralWidget);
}

BST_Properties_Window::~BST_Properties_Window(){
    delete heightLabel;
    delete heightValue;
    delete nodeCountLabel;
    delete nodeCountValue;
    delete leafNodesLabel;
    delete leafNodesValue;
    delete internalNodesLabel;
    delete internalNodesValue;
    delete labelLayout;
    delete textAreaLayout;
    delete containerLayout;
    delete preOrderTraversal;
    delete inOrderTraversal;
    delete postOrderTraversal;
    delete breadthFirstTraversal;
    delete exitButton;
    delete mainLayout;
    delete centralWidget;
}

void BST_Properties_Window::closePropertyWindow()
{
    this->close();
    return;
}

void BST_Properties_Window::update(BinarySearchTree<int> *bst)
{
    this->heightValue->setText(QString::number(bst->getTreeHeight()));
    this->nodeCountValue->setText(QString::number(bst->getNodeCount()));
    this->leafNodesValue->setText(QString::number(bst->getLeafNodeCount()));
    this->internalNodesValue->setText(QString::number(bst->getNodeCount() - bst->getLeafNodeCount()));
    this->preOrderTraversal->setText(bst->getPreOrderTraversal());
    this->inOrderTraversal->setText(bst->getInOrderTraversal());
    this->postOrderTraversal->setText(bst->getPostOrderTraversal());
    this->breadthFirstTraversal->setText(bst->getBreadthFirstSearch());
    return;
}


void BST_Properties_Window::show()
{
    qDebug() << "Property button clicked, showing window";
    this->setVisible(true);
    this->activateWindow();
    return;
}

void BST_Properties_Window::exitSlot()
{
    this->close();
    return;
}
