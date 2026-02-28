#include "GameWindow.hpp"
#include <QPainter>
#include <QMessageBox>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent), leftPressed(false), rightPressed(false), jumpPressed(false) {
    setFixedSize(MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE);
    game.initializeLevel(1);
    timer.setInterval(15);
    connect(&timer, &QTimer::timeout, this, &GameWindow::onTimer);
    timer.start();
}

void GameWindow::onTimer() {
    game.handleInput(leftPressed, rightPressed, jumpPressed);
    game.update();
    if (game.isGameOver()) {
        timer.stop();
        QMessageBox::information(this, "Game over", "Вы прошли все уровни!");
        close();
    }
    update();
}

void GameWindow::paintEvent(QPaintEvent * /*event*/) {
    QPainter p(this);
    game.render(p);
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        leftPressed = true;
    } else if (event->key() == Qt::Key_D) {
        rightPressed = true;
    } else if (event->key() == Qt::Key_Space) {
        jumpPressed = true;
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        leftPressed = false;
    } else if (event->key() == Qt::Key_D) {
        rightPressed = false;
    } else if (event->key() == Qt::Key_Space) {
        jumpPressed = false;
    }
}
