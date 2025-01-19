#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QColorDialog>
#include <QColor>
#include "renderarea.h"
#include "binarysearchtree.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QInputDialog>
#include <QMessageBox>

class BinaryTree : public QMainWindow
{
    Q_OBJECT

public:
    explicit BinaryTree(QWidget *parent = nullptr);
    ~BinaryTree();

private slots:
    void on_actionInsert_triggered();
    void on_actionRemove_triggered();
    void on_actionClear_triggered();
    void on_actionExit_triggered();

private:
    QGraphicsScene *scene;
    void insertValue(int value);
    void removeValue(int value);
    void clearTree();
    void updateTreeVisualization();
    // Add your tree data structure here
};

#endif // BINARYTREE_H
