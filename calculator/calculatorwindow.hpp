#ifndef CALCULATORWINDOW_HPP
#define CALCULATORWINDOW_HPP

#include <QWidget>

class QLineEdit;
class QPushButton;

class CalculatorWindow : public QWidget
{
    Q_OBJECT

public:
    CalculatorWindow(QWidget *parent = nullptr);
    ~CalculatorWindow();

private slots:
    void digitPressed();
    void operationPressed();
    void equalsPressed();
    void clearPressed();

private:
    QLineEdit *m_display;
    double m_leftOperand;
    QString m_operator;
    bool m_waitingForOperand;

    void calculate();
};

#endif
