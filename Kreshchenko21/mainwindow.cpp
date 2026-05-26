#include "mainwindow.h"
#include "mainmenuwidget.h"
#include "gamewidget.h"
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    menuWidget = new MainMenuWidget(this);
    gameWidget = new GameWidget(this);

    stackedWidget->addWidget(menuWidget);
    stackedWidget->addWidget(gameWidget);

    connect(menuWidget, &MainMenuWidget::startGameRequested, this, [=]() {
        gameWidget->setupNewGame();
        stackedWidget->setCurrentWidget(gameWidget);
    });

    connect(gameWidget, &GameWidget::menuRequested, this, [=]() {
        stackedWidget->setCurrentWidget(menuWidget);
    });

    setWindowTitle("Memory Training App");
    resize(380, 480);
}

MainWindow::~MainWindow() {
}
