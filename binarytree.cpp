#include "binarytree.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QMenuBar>
#include <QSpacerItem>
#include <qglobal.h>
#include <QTime>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>

#include <QStringList>

BinaryTree::BinaryTree(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this))
{
    setWindowTitle("Binary Tree Visualization");

    // Set up the graphics view
    QGraphicsView *view = new QGraphicsView(this);
    view->setScene(scene);
    setCentralWidget(view);

    // Add menus and actions
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *insertAction = fileMenu->addAction("Insert");
    QAction *removeAction = fileMenu->addAction("Remove");
    QAction *clearAction = fileMenu->addAction("Clear");
    QAction *exitAction = fileMenu->addAction("Exit");

    connect(insertAction, &QAction::triggered, this, &BinaryTree::on_actionInsert_triggered);
    connect(removeAction, &QAction::triggered, this, &BinaryTree::on_actionRemove_triggered);
    connect(clearAction, &QAction::triggered, this, &BinaryTree::on_actionClear_triggered);
    connect(exitAction, &QAction::triggered, this, &BinaryTree::on_actionExit_triggered);

    // Initialize tree visualization (to be implemented)
}

BinaryTree::~BinaryTree()
{
    delete scene;
}

void BinaryTree::on_actionInsert_triggered()
{
    bool ok;
    int value = QInputDialog::getInt(this, "Insert Node", "Enter value:", 0, INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        insertValue(value);
    }
}

void BinaryTree::on_actionRemove_triggered()
{
    bool ok;
    int value = QInputDialog::getInt(this, "Remove Node", "Enter value:", 0, INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        removeValue(value);
    }
}

void BinaryTree::on_actionClear_triggered()
{
    if (QMessageBox::question(this, "Clear Tree", "Are you sure you want to clear the tree?") == QMessageBox::Yes) {
        clearTree();
    }
}


void BinaryTree::on_actionExit_triggered()
{
    close();
}

void BinaryTree::insertValue(int value)
{
    // Implement tree insertion logic
    updateTreeVisualization();
}

void BinaryTree::removeValue(int value)
{
    // Implement tree removal logic
    updateTreeVisualization();
}

void BinaryTree::clearTree()
{
    // Implement tree clearing logic
    updateTreeVisualization();
}


void BinaryTree::updateTreeVisualization()
{
    // Implement visualization update logic using QGraphicsScene
    scene->clear();
    // Example: Add nodes and edges here
}
