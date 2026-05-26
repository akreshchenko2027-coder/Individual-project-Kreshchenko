#include "mainmenuwidget.h"
#include <QApplication>

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(40, 40, 40, 40);

    QLabel *title = new QLabel("Memory Training", this);
    QFont titleFont = title->font();
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);

    QLabel *factLabel = new QLabel("Науковий факт: регулярні тренування покращують зорову пам'ять на 15%.", this);
    factLabel->setWordWrap(true);
    factLabel->setAlignment(Qt::AlignCenter);

    QPushButton *btnStart = new QPushButton("Почати гру", this);
    QPushButton *btnStats = new QPushButton("Статистика", this);
    QPushButton *btnExit = new QPushButton("Вихід", this);

    btnStart->setFixedHeight(40);
    btnStats->setFixedHeight(40);
    btnExit->setFixedHeight(40);

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
