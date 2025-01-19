#ifndef STACKVISUALIZATION_H
#define STACKVISUALIZATION_H

#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QPainter>
#include <QVector>

class StackVisualization : public QWidget {
    Q_OBJECT

private:
    QVector<int> stackData;         // Primary stack
    QVector<int> temporaryStack;   // Temporary stack for transfer
    int currentTraversalIndex;      // Index during traversal
    int elementToDelete;            // Element to delete
    bool isTransferToTemporary;     // State of transfer to secondary stack
    QTimer* traversalTimer;         // Timer for animation
    QLineEdit* dataInput;           // Input field for push
    QLineEdit* deleteInput;         // Input field for specific delete
    QPushButton* pushButton;        // Push button
    QPushButton* popButton;         // Pop button
    QPushButton* removeButton;      // Remove specific button
    QPushButton* zoomInButton;      // Zoom in button
    QPushButton* zoomOutButton;     // Zoom out button
    double scale;                   // Scaling factor for zoom
    QColor defaultColor;            // Default node color
    QColor traversingColor;         // Color during traversal

public:
    explicit StackVisualization(QWidget* parent = nullptr);

private slots:
    void pushElement();
    void popElement();
    void removeSpecificElement();
    void zoomIn();
    void zoomOut();
    void updateTraversal();

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // STACKVISUALIZATION_H
