#include "calculatorwindow.hpp"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QDebug>

CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QWidget(parent)
    , m_leftOperand(0.0)
    , m_operator("")
    , m_waitingForOperand(true)
{
    m_display = new QLineEdit("0");
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    m_display->setMaxLength(30);

    QPushButton *button0 = new QPushButton("0");
    QPushButton *button1 = new QPushButton("1");
    QPushButton *button2 = new QPushButton("2");
    QPushButton *button3 = new QPushButton("3");
    QPushButton *button4 = new QPushButton("4");
    QPushButton *button5 = new QPushButton("5");
    QPushButton *button6 = new QPushButton("6");
    QPushButton *button7 = new QPushButton("7");
    QPushButton *button8 = new QPushButton("8");
    QPushButton *button9 = new QPushButton("9");
    QPushButton *buttonPlus = new QPushButton("+");
    QPushButton *buttonMinus = new QPushButton("-");
    QPushButton *buttonMul = new QPushButton("*");
    QPushButton *buttonDiv = new QPushButton("/");
    QPushButton *buttonEquals = new QPushButton("=");
    QPushButton *buttonClear = new QPushButton("C");

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(m_display, 0, 0, 1, 4);

    layout->addWidget(button7, 1, 0);
    layout->addWidget(button8, 1, 1);
    layout->addWidget(button9, 1, 2);
    layout->addWidget(buttonDiv, 1, 3);

    layout->addWidget(button4, 2, 0);
    layout->addWidget(button5, 2, 1);
    layout->addWidget(button6, 2, 2);
    layout->addWidget(buttonMul, 2, 3);

    layout->addWidget(button1, 3, 0);
    layout->addWidget(button2, 3, 1);
    layout->addWidget(button3, 3, 2);
    layout->addWidget(buttonMinus, 3, 3);

    layout->addWidget(button0, 4, 0, 1, 2);
    layout->addWidget(buttonClear, 4, 2);
    layout->addWidget(buttonPlus, 4, 3);

    layout->addWidget(buttonEquals, 5, 0, 1, 4);

    connect(button0, &QPushButton::clicked, this, &CalculatorWindow::digitPressed);
    connect(button1, &QPushButton::clicked, this, &CalculatorWindow::digitPressed);
    connect(button2, &QPushButton::clicked, this, &CalculatorWindow::digitPressed);
    connect(button3, &QPushButton::clicked, this, &CalculatorWindow::digitPressed);
    connect(button4, &QPushButton::clicked, this, &CalculatorWindow::digitPressed);
    connect(button5, &QPushButton::clicked, this, &CalculatorWindow::digitPressed);
    connect(button6, &QPushButton::clicked, this, &CalculatorWindow::digitPressed);
    connect(button7, &QPushButton::clicked, this, &CalculatorWindow::digitPressed);
    connect(button8, &QPushButton::clicked, this, &CalculatorWindow::digitPressed);
    connect(button9, &QPushButton::clicked, this, &CalculatorWindow::digitPressed);

    connect(buttonPlus, &QPushButton::clicked, this, &CalculatorWindow::operationPressed);
    connect(buttonMinus, &QPushButton::clicked, this, &CalculatorWindow::operationPressed);
    connect(buttonMul, &QPushButton::clicked, this, &CalculatorWindow::operationPressed);
    connect(buttonDiv, &QPushButton::clicked, this, &CalculatorWindow::operationPressed);

    connect(buttonEquals, &QPushButton::clicked, this, &CalculatorWindow::equalsPressed);
    connect(buttonClear, &QPushButton::clicked, this, &CalculatorWindow::clearPressed);

    setWindowTitle("Калькулятор");
    resize(350, 300);
}

CalculatorWindow::~CalculatorWindow()
{
}

void CalculatorWindow::digitPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString digit = button->text();
    QString currentText = m_display->text();

    if (m_waitingForOperand) {
        //если ждём новый операнд (после оператора)
        if (currentText.endsWith('+') || currentText.endsWith('-') ||
            currentText.endsWith('*') || currentText.endsWith('/')) {
            //добавляем цифру после оператора
            m_display->setText(currentText + digit);
        } else {
            //начинаем новое число
            m_display->setText(digit);
        }
        m_waitingForOperand = false;
    } else {
        //добавляем цифру к текущему числу
        if (currentText == "0" && digit != "0") {
            m_display->setText(digit);
        } else {
            m_display->setText(currentText + digit);
        }
    }
}

void CalculatorWindow::operationPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString newOperator = button->text();
    QString currentText = m_display->text();

    //сохраняем левый операнд
    bool ok;
    double currentValue = currentText.toDouble(&ok);
    if (ok) {
        m_leftOperand = currentValue;
    }

    //если последний символ уже оператор, заменяем его
    if (currentText.endsWith('+') || currentText.endsWith('-') ||
        currentText.endsWith('*') || currentText.endsWith('/')) {
        currentText.chop(1);
        m_display->setText(currentText + newOperator);
    } else {
        //добавляем новый оператор
        m_display->setText(currentText + newOperator);
    }

    m_operator = newOperator;
    m_waitingForOperand = true; //ждём второй операнд
}

void CalculatorWindow::equalsPressed()
{
    if (m_operator.isEmpty()) return;

    QString currentText = m_display->text();

    //извлекаем правый операнд из текста
    QStringList parts;
    if (currentText.contains('+')) parts = currentText.split('+');
    else if (currentText.contains('-')) parts = currentText.split('-');
    else if (currentText.contains('*')) parts = currentText.split('*');
    else if (currentText.contains('/')) parts = currentText.split('/');

    if (parts.size() == 2) {
        double rightOperand = parts[1].toDouble();

        //cохраняем выражение перед вычислением
        QString expression = currentText;

        //вычисляем результат
        calculate(rightOperand);

        //показываем выражение и результат
        m_display->setText(expression + "=" + QString::number(m_leftOperand));
    }

    m_operator.clear();
    m_waitingForOperand = true;
}

void CalculatorWindow::clearPressed()
{
    m_display->setText("0");
    m_leftOperand = 0.0;
    m_operator.clear();
    m_waitingForOperand = true;
}

void CalculatorWindow::calculate(double rightOperand)
{
    double result = 0.0;

    if (m_operator == "+") {
        result = m_leftOperand + rightOperand;
    } else if (m_operator == "-") {
        result = m_leftOperand - rightOperand;
    } else if (m_operator == "*") {
        result = m_leftOperand * rightOperand;
    } else if (m_operator == "/") {
        if (rightOperand != 0.0) {
            result = m_leftOperand / rightOperand;
        } else {
            m_display->setText("Ошибка");
            m_waitingForOperand = true;
            m_operator.clear();
            return;
        }
    }

    m_leftOperand = result;
}
