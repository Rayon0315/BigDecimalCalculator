#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
    namespace Ui { class CalculatorWidget; }
QT_END_NAMESPACE

class CalculatorWidget : public QWidget {
    Q_OBJECT

public:
    explicit CalculatorWidget(QWidget *parent = nullptr);
    ~CalculatorWidget();

private:
    Ui::CalculatorWidget *ui;

    void insertText(const QString &text);
    void backspace();
    void clearAll();
    void moveCursorLeft();
    void moveCursorRight();

    void setUpConnections();
};
