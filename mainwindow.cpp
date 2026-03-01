#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <string>
#include <QVector>
#include "CalculatorEngine.h"
#include "ExpressionEvaluator.h"
#include "ExpressionValidator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // -----------计算器----------
    ui->editArea->setReadOnly(false);
    ui->editArea->setAlignment(Qt::AlignRight);

    ui->editArea->setFocusPolicy(Qt::StrongFocus);
    ui->editArea->setFocus();

    QRegularExpression re("[0-9+\\-*/().]*");
    ui->editArea->setValidator(new QRegularExpressionValidator(re, this));
    ui->editA->setValidator(new QRegularExpressionValidator(re, this));
    ui->editB->setValidator(new QRegularExpressionValidator(re, this));

    setupCalculatorConnections();
    // ---------------------------

    // ---------基本运算-----------
    connect(ui->btnEqual, &QPushButton::clicked, this, [this]() {
        QString s = ui->editA->text();
        QString t = ui->editB->text();
        QString op = ui->opBox->currentText();

        if (s.isEmpty() || t.isEmpty()) return;

        std::string result = CalculatorEngine::calc(
            s.toStdString(),
            t.toStdString(),
            op[0].toLatin1());

        ui->editResult->setText(QString::fromStdString(result));
    });
    // ---------------------------

    // ----------页面显示----------
    ui->labelStart->setStyleSheet("color: blue;");

    connect(ui->btnReturnFromBasic, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageInit);
    });

    connect(ui->btnReturnFromHW, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageInit);
    });

    connect(ui->btnBasic, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageBasic);
    });

    connect(ui->btnCalc, &QPushButton::clicked, this, [this]() {
        calcClear();
        ui->stackedWidget->setCurrentWidget(ui->pageCalc);
    });

    connect(ui->btnHandwrite, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageHW);
    });

    ui->stackedWidget->setCurrentWidget(ui->pageInit);
    // ---------------------------
}

void MainWindow::calcBackspace() {
    ui->editArea->setFocus();
    ui->editArea->backspace();
}

void MainWindow::calcClear() {
    ui->editStatus->clear();
    ui->editArea->clear();
    ui->editArea->setCursorPosition(0);
}

void MainWindow::calcMoveCursorLeft() {
    ui->editArea->setFocus();

    int pos = ui->editArea->cursorPosition();
    if (pos > 0) {
        ui->editArea->setCursorPosition(pos - 1);
    }
}

void MainWindow::calcMoveCursorRight() {
    ui->editArea->setFocus();

    int pos = ui->editArea->cursorPosition();
    if (pos < ui->editArea->text().length()) {
        ui->editArea->setCursorPosition(pos + 1);
    }
}

void MainWindow::calcInsert(const QString &text) {
    ui->editArea->setFocus();
    ui->editArea->insert(text);
}

void MainWindow::onEqualClicked() {
    ExpressionValidator validator;
    ValidationResult val = validator.validate(ui->editArea->text().toStdString());
    if (!val.ok) {
        ui->editStatus->setText(QString::fromStdString("表达式非法：" + val.message));
        return;
    }


    ExpressionEvaluator evaluator;
    BigDecimal result = evaluator.evaluate(ui->editArea->text().toStdString());

    QString output = QString::fromStdString(result.convertToString());
    output.remove(',');

    ui->editArea->setText(output);
    ui->editArea->setCursorPosition(output.length());
    ui->editStatus->setText(QString::fromStdString("计算成功！"));
}

void MainWindow::setupCalculatorConnections() {
    QVector<QPushButton*> digitButtons = {
        ui->btn0, ui->btn1, ui->btn2, ui->btn3, ui->btn4, ui->btn5, ui->btn6, ui->btn7, ui->btn8, ui->btn9
    };

    for (auto btn : digitButtons) {
        connect(btn, &QPushButton::clicked, this, [this, btn]() {
            calcInsert(btn->text());
        });
    }

    QVector<QPushButton*> opButtons = {
        ui->btnAdd, ui->btnSub, ui->btnMul, ui->btnDiv, ui->btnDot, ui->btnLBrac, ui->btnRbrac
    };

    for (auto btn : opButtons) {
        connect(btn, &QPushButton::clicked, this, [this, btn]() {
            calcInsert(btn->text());
        });
    }

    connect(ui->btnBack, &QPushButton::clicked, this, &MainWindow::calcBackspace);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::calcClear);
    connect(ui->btnLeft, &QPushButton::clicked, this, &MainWindow::calcMoveCursorLeft);
    connect(ui->btnRight, &QPushButton::clicked, this, &MainWindow::calcMoveCursorRight);

    connect(ui->btnReturnFromCalc, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageInit);
    });

    connect(ui->btnEqualCalc, &QPushButton::clicked, this, &MainWindow::onEqualClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}
