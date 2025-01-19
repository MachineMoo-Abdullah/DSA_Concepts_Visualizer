#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "circulardoublylinkedlist.h"
#include "circularsinglylinkedlist.h"
#include "doublylinkedlistvisualization.h"
#include "singlynode.h"
#include "doublynode.h"
#include "linkedlistvisualization.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_BinaryTree_clicked();
    void createVisualizationWindow(QWidget *visualizationWidget, const QString &title);
    void on_stack_visualization_clicked();

    void on_Singly_linkedList_clicked();

    void on_DoublyLinkedList_clicked();

    void on_circularsinglylinkedlist_clicked();

    void on_circulardoublylinkedlist_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
