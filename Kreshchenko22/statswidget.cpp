#include "statswidget.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

StatsWidget::StatsWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_statsLabel = new QLabel(this);
    m_statsLabel->setAlignment(Qt::AlignCenter);
    m_statsLabel->setStyleSheet("font-size: 18px; margin-bottom: 20px;");

    m_btnClear = new QPushButton("Очистити статистику", this);
    m_btnClear->setStyleSheet("font-size: 14px; padding: 8px;");

    QPushButton *btnMenu = new QPushButton("↩ Меню", this);
    btnMenu->setStyleSheet("font-size: 14px; padding: 8px;");

    layout->addWidget(m_statsLabel);
    layout->addWidget(m_btnClear);
    layout->addWidget(btnMenu);

    connect(m_btnClear, &QPushButton::clicked, this, &StatsWidget::clearRequested);
    connect(btnMenu, &QPushButton::clicked, this, &StatsWidget::menuRequested);

    updateStats(0);
}

void StatsWidget::updateStats(int gamesCount) {
    m_statsLabel->setText("Зіграно ігор: " + QString::number(gamesCount));
}
