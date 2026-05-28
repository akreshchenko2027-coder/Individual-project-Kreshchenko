#include "mainwindow.h"
#include "mainmenuwidget.h"
#include "gamewidget.h"
#include "statswidget.h"
#include <QStackedWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // ШАР ДАНИХ: Ініціалізуємо сховище та читаємо попередній результат
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

    // НАВІГАЦІЯ ТА ЛОГІКА ІНТЕРФЕЙСУ
    connect(m_menuWidget, &MainMenuWidget::startRequested, [=]() {
        m_gameWidget->setupNewGame();
        m_stackedWidget->setCurrentIndex(1); // Перехід на екран гри
    });

    connect(m_menuWidget, &MainMenuWidget::statsRequested, [=]() {
        // Оновлюємо лейбл значенням із репозиторію перед показом сторінки
        m_statsWidget->updateStats(m_repository->getTotalGamesPlayed());
        m_stackedWidget->setCurrentIndex(2); // Перехід на екран статистики
    });

    connect(m_statsWidget, &StatsWidget::menuRequested, [=]() {
        m_stackedWidget->setCurrentIndex(0); // Назад до меню
    });

    // ШАР ДАНИХ: Очищення статистики у файлі
    connect(m_statsWidget, &StatsWidget::clearRequested, [=]() {
        m_repository->setTotalGamesPlayed(0);
        m_repository->saveToFile(); // Скидаємо в JSON
        m_statsWidget->updateStats(0);
        QMessageBox::information(this, "Статистика", "Статистику успішно скинуто!");
    });

    connect(m_gameWidget, &GameWidget::menuRequested, [=]() {
        m_stackedWidget->setCurrentIndex(0); // Назад до меню з гри
    });

    // ЗВ'ЯЗОК UI ТА ДАНИХ: Обробка виграшу
    connect(m_gameWidget, &GameWidget::gameFinished, [=]() {
        int currentCount = m_repository->getTotalGamesPlayed();
        m_repository->setTotalGamesPlayed(currentCount + 1);
        m_repository->saveToFile(); // Записуємо нове значення в JSON

        // Відразу оновлюємо екран статистики актуальним значенням
        m_statsWidget->updateStats(m_repository->getTotalGamesPlayed());

        QMessageBox::information(this, "Перемога!", "Вітаємо! Результат збережено в статистику.");
        m_stackedWidget->setCurrentIndex(0); // Повертаємо користувача в меню
    });

    resize(400, 500);
}

MainWindow::~MainWindow() {
    delete m_repository;
}
