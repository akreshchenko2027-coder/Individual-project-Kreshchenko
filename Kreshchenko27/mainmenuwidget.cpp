#include "mainmenuwidget.h"
#include <QFont>
#include <QApplication>

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent) {
    // Налаштування красивого шрифту для всього екрану меню
    QFont defaultFont("Segoe UI", 11);
    this->setFont(defaultFont);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(40, 40, 40, 40);

    QLabel *title = new QLabel("Memory Training", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont("Segoe UI", 24, QFont::Bold);
    title->setFont(titleFont);

    QLabel *factLabel = new QLabel("Науковий факт: регулярні тренування покращують зорову пам'ять на 15%.", this);
    factLabel->setWordWrap(true);
    factLabel->setAlignment(Qt::AlignCenter);
    factLabel->setStyleSheet("color: #666666; font-style: italic;");

    QPushButton *btnStart = new QPushButton("Почати гру", this);
    QPushButton *btnStats = new QPushButton("Статистика", this);
    QPushButton *btnExit = new QPushButton("Вихід", this);

    btnStart->setMinimumHeight(42);
    btnStats->setMinimumHeight(42);
    btnExit->setMinimumHeight(42);

    layout->addWidget(title);
    layout->addWidget(factLabel);
    layout->addSpacing(20);
    layout->addWidget(btnStart);
    layout->addWidget(btnStats);
    layout->addWidget(btnExit);
    layout->addStretch();

    connect(btnStart, &QPushButton::clicked, this, &MainMenuWidget::startRequested);
    connect(btnStats, &QPushButton::clicked, this, &MainMenuWidget::statsRequested);
    connect(btnExit, &QPushButton::clicked, qApp, &QApplication::quit);
}
