#include "mainwindow.h"
#include "ui_mainwindow.h"

// Include necessary visualization headers
#include "binarytreemainwindow.h"
#include "binarytree.h"
#include "StackVisualization.h"
#include "LinkedListVisualization.h"
#include "DoublyLinkedListVisualization.h"
#include "CircularSinglyLinkedList.h"
#include "CircularDoublyLinkedList.h"

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Helper function to create and display visualization windows
void MainWindow::createVisualizationWindow(QWidget *visualizationWidget, const QString &title)
{
    QMainWindow *window = new QMainWindow(this); // Parent ensures proper deletion
    QWidget *centralWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    layout->addWidget(visualizationWidget);
    window->setCentralWidget(centralWidget);
    window->setWindowTitle(title);
    window->resize(1200, 600);
    window->setStyleSheet("background-color: black; color: white;");
    window->show();
}

void MainWindow::on_BinaryTree_clicked()
{
    BinaryTreeMainWindow* visualization = new BinaryTreeMainWindow();
    createVisualizationWindow(visualization,"Binary Tree Visualization");
}

void MainWindow::on_stack_visualization_clicked()
{
    StackVisualization *visualization = new StackVisualization();
    createVisualizationWindow(visualization, "Stack Visualization");
}

// Button click for Singly Linked List visualization
void MainWindow::on_Singly_linkedList_clicked()
{
    LinkedListVisualization *visualization = new LinkedListVisualization();
    createVisualizationWindow(visualization, "Singly Linked List Visualization");
}

// Button click for Doubly Linked List visualization
void MainWindow::on_DoublyLinkedList_clicked()
{
    DoublyLinkedList<int>* list = new DoublyLinkedList<int>();

    DoublyLinkedListVisualization* visualization = new DoublyLinkedListVisualization();
    visualization->setDoublyLinkedList(list);

    visualization->resize(800, 600);
    visualization->setWindowTitle("Doubly Linked List Visualization");
    visualization->setStyleSheet("background-color: black; color: white;");
    visualization->show();
}

// Button click for Circular Singly Linked List visualization
void MainWindow::on_circularsinglylinkedlist_clicked()
{
    CircularSinglyLinkedList<int>* list = new CircularSinglyLinkedList<int>();

    CircularSinglyLinkedListVisualization* visualization = new CircularSinglyLinkedListVisualization();
    visualization->setCircularSinglyLinkedList(list);

    visualization->resize(800, 600);
    visualization->setWindowTitle("Circular Singly Linked List Visualization");
    visualization->setStyleSheet("background-color: black; color: white;");
    visualization->show();
}

// Button click for Circular Doubly Linked List visualization
void MainWindow::on_circulardoublylinkedlist_clicked()
{
    CircularDoublyLinkedList<int>* list = new CircularDoublyLinkedList<int>();
    CircularDoublyLinkedListVisualization* visualization = new CircularDoublyLinkedListVisualization();
    visualization->setDoublyLinkedList(list);

    visualization->resize(800, 600);
    visualization->setWindowTitle("Circular Doubly Linked List Visualization");
    visualization->setStyleSheet("background-color: black; color: white;");
    visualization->show();
}
