#include "mainwindow.hpp"
#include "calculatorwindow.hpp"
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    m_button = new QPushButton("Открыть калькулятор", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_button);

    connect(m_button, &QPushButton::clicked, this, &MainWindow::openCalculator);

    setWindowTitle("Главное окно");
    resize(250, 100);
}

MainWindow::~MainWindow()
{
}

void MainWindow::openCalculator()
{
    CalculatorWindow *calcWindow = new CalculatorWindow();
    calcWindow->setAttribute(Qt::WA_DeleteOnClose);
    calcWindow->show();
}
