#include "mainwindow.h"
#include "mainmenuwidget.h"
#include "gamewidget.h"
#include "statswidget.h"
#include <QStackedWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_repository = new GameRepository("stats.json");
    m_repository->loadFromFile();

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
        m_statsWidget->updateStats(m_repository->getTotalGamesPlayed());
        m_stackedWidget->setCurrentIndex(2);
    });

    connect(m_statsWidget, &StatsWidget::menuRequested, [=]() {
        m_stackedWidget->setCurrentIndex(0);
    });

    connect(m_statsWidget, &StatsWidget::clearRequested, [=]() {
        m_repository->setTotalGamesPlayed(0);
        m_repository->saveToFile();
        m_statsWidget->updateStats(0);
        QMessageBox::information(this, "Статистика", "Статистику успішно скинуто!");
    });

    connect(m_gameWidget, &GameWidget::menuRequested, [=]() {
        m_stackedWidget->setCurrentIndex(0);
    });

    connect(m_gameWidget, &GameWidget::gameFinished, [=]() {
        int currentCount = m_repository->getTotalGamesPlayed();
        m_repository->setTotalGamesPlayed(currentCount + 1);
        m_repository->saveToFile();

        m_statsWidget->updateStats(m_repository->getTotalGamesPlayed());

        QMessageBox::information(this, "Перемога!", "Вітаємо! Результат збережено в статистику.");
        m_stackedWidget->setCurrentIndex(0);
    });

    resize(400, 500);
}

MainWindow::~MainWindow() {
    delete m_repository;
}
