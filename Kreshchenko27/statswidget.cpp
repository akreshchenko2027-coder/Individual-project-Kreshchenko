#include "statswidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>

StatsWidget::StatsWidget(QWidget *parent) : QWidget(parent) {
    QFont defaultFont("Segoe UI", 11);
    this->setFont(defaultFont);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(40, 40, 40, 40);

    QLabel *title = new QLabel("Статистика", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont("Segoe UI", 22, QFont::Bold);
    title->setFont(titleFont);

    m_statsLabel = new QLabel("Загалом зіграно ігор: 0", this);
    m_statsLabel->setAlignment(Qt::AlignCenter);
    m_statsLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #FFFFFF;");

    m_btnClear = new QPushButton("Очистити статистику", this);
    QPushButton *btnMenu = new QPushButton("Назад до меню", this);

    m_btnClear->setMinimumHeight(42);
    btnMenu->setMinimumHeight(42);

    layout->addWidget(title);
    layout->addWidget(m_statsLabel);
    layout->addSpacing(20);
    layout->addWidget(m_btnClear);
    layout->addWidget(btnMenu);
    layout->addStretch();

    connect(m_btnClear, &QPushButton::clicked, this, &StatsWidget::clearRequested);
    connect(btnMenu, &QPushButton::clicked, this, &StatsWidget::menuRequested);
}

void StatsWidget::updateStats(int gamesCount) {

    if (m_statsLabel) {
        m_statsLabel->setText(QString("Загалом зіграно ігор: %1").arg(gamesCount));
    }
}
