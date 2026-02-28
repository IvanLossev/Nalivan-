#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include "Game.hpp"

class GameWindow : public QWidget {
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void onTimer();

private:
    Game game;
    QTimer timer;
    bool leftPressed;
    bool rightPressed;
    bool jumpPressed;
};

#endif
