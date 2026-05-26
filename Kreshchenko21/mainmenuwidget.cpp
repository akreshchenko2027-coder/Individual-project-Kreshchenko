#include "mainmenuwidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(15);

    QLabel *title = new QLabel("Brain Train App", this);
    title->setStyleSheet("font-size: 26px; font-weight: bold; color: #2C3E50;");
    layout->addWidget(title, 0, Qt::AlignCenter);

    QLabel *subtitle = new QLabel(
        "Науковий факт: Когнітивні тренування стимулюють нейропластичність "
        "і збільшують об'єм сірого речовини в гіппокампі.", this);
    subtitle->setWordWrap(true);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("font-size: 12px; color: #7F8C8D; font-style: italic; max-width: 300px; margin-bottom: 20px;");
    layout->addWidget(subtitle, 0, Qt::AlignCenter);

    QPushButton *btnStart = new QPushButton("Почати тестування (4х4)", this);
    btnStart->setStyleSheet("font-size: 16px; padding: 10px 20px; background-color: #2ECC71; color: white; border-radius: 5px;");

    QPushButton *btnExit = new QPushButton("Вихід", this);
    btnExit->setStyleSheet("font-size: 14px; padding: 8px 15px; background-color: #E74C3C; color: white; border-radius: 5px;");

    layout->addWidget(btnStart);
    layout->addWidget(btnExit);

    connect(btnStart, &QPushButton::clicked, this, &MainMenuWidget::startGameRequested);
    connect(btnExit, &QPushButton::clicked, qApp, &QApplication::quit);
}
