#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>

class QPushButton;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openCalculator();

private:
    QPushButton *m_button;
};

#endif
