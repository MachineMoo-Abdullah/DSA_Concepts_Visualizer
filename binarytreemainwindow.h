
#ifndef BINARYTREEMAINWINDOW_H
#define BINARYTREEMAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMenu>
#include "bst_properties_window.h"
#include <QAction>
#include <QLabel>
#include <QColorDialog>
#include <QColor>
#include <QLineEdit>
#include "renderarea.h"
#include "binarysearchtree.h"

class BinaryTreeMainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;

public:
    explicit BinaryTreeMainWindow(QWidget *parent = 0);
    ~BinaryTreeMainWindow();

private:
    RenderArea *renderArea;
    QPushButton *propertyButton;
    QPushButton *deleteButton;
    QPushButton *insertButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *clearTreeButton;
    QLineEdit *insertValueLineEdit;
    QLineEdit *deleteValueLineEdit;

    BST_Properties_Window *prop;
    QScrollArea *treeScrollArea;
    QVBoxLayout *mainLayout;
    QLabel *statusLabel;
    BinarySearchTree<int> *bst;
    BinarySearchTree<int> *getBST();


protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual void resizeEvent(QResizeEvent* event);

private slots:
    void propertyClicked() const;
    void insertClicked() const;
    void deleteClicked();
    void clearTreeClicked();
    void zoomInClicked() const;
    void zoomOutClicked() const;

};

#endif // BINARYTREEMAINWINDOW_H
