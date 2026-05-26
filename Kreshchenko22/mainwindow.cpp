#include "mainwindow.h"
#include "mainmenuwidget.h"
#include "gamewidget.h"
#include "statswidget.h"
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_totalGamesPlayed(0) {
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    m_menuWidget = new MainMenuWidget(this);
    m_gameWidget = new GameWidget(this);
    m_statsWidget = new StatsWidget(this);

    m_stackedWidget->addWidget(m_menuWidget);
    m_stackedWidget->addWidget(m_gameWidget);
    m_stackedWidget->addWidget(m_statsWidget);

    connect(m_menuWidget, &MainMenuWidget::startRequested, [=]() {
        m_gameWidget->setupNewGame();
        m_stackedWidget->setCurrentIndex(1);
    });

    connect(m_menuWidget, &MainMenuWidget::statsRequested, [=]() {
        m_statsWidget->updateStats(m_totalGamesPlayed);
        m_stackedWidget->setCurrentIndex(2);
    });

    connect(m_statsWidget, &StatsWidget::menuRequested, [=]() {
        m_stackedWidget->setCurrentIndex(0);
    });

    connect(m_statsWidget, &StatsWidget::clearRequested, [=]() {
        m_totalGamesPlayed = 0;
        m_statsWidget->updateStats(0);
    });

    connect(m_gameWidget, &GameWidget::menuRequested, [=]() {
        m_stackedWidget->setCurrentIndex(0);
    });

    connect(m_gameWidget, &GameWidget::gameFinished, [=]() {
        m_totalGamesPlayed++;
    });

    resize(400, 500);
}
