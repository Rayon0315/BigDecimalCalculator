#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    void calcInsert(const QString &text);
    void calcBackspace();
    void calcClear();
    void calcMoveCursorLeft();
    void calcMoveCursorRight();
    void onEqualClicked();

    void setupCalculatorConnections();
};
#endif // MAINWINDOW_H
