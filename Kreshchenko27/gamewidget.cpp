#include "gamewidget.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QFont>
#include <QPropertyAnimation>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , firstClickedIdx(-1)
    , secondClickedIdx(-1)
    , isProcessing(false)
    , gamesPlayedInSession(0)
{

    QFont defaultFont("Segoe UI", 11);
    this->setFont(defaultFont);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(10);

    buttons.resize(16);
    for (int i = 0; i < 16; ++i) {
        buttons[i] = new QPushButton("?", this);
        buttons[i]->setMinimumSize(70, 80);

        applyButtonStyle(buttons[i]);

        gridLayout->addWidget(buttons[i], i / 4, i % 4);

        connect(buttons[i], &QPushButton::clicked, this, &GameWidget::onCardClicked);
    }

    mainLayout->addLayout(gridLayout);

    QPushButton *btnMenu = new QPushButton("Назад до меню", this);
    btnMenu->setMinimumHeight(42);
    mainLayout->addWidget(btnMenu);

    connect(btnMenu, &QPushButton::clicked, this, &GameWidget::menuRequested);

    setupNewGame();
}

void GameWidget::setupNewGame() {
    logic.startNewGame(8);
    firstClickedIdx = -1;
    secondClickedIdx = -1;
    isProcessing = false;

    for (int i = 0; i < 16; ++i) {
        buttons[i]->setText("?");
        buttons[i]->setEnabled(true);

        applyButtonStyle(buttons[i], false);
    }
}

void GameWidget::applyButtonStyle(QPushButton *btn, bool isMatched) {
    if (isMatched) {

        btn->setStyleSheet(
            "QPushButton {"
            "   background-color: #2ECC71;"
            "   color: #F1C40F;"
            "   font-size: 22px;"
            "   font-weight: bold;"
            "   border: none;"
            "   border-radius: 8px;"
            "}"
            );
    } else {
        btn->setStyleSheet(
            "QPushButton {"
            "   background-color: #2C3E50;"
            "   color: #FFFFFF;"
            "   font-size: 20px;"
            "   font-weight: bold;"
            "   border: 2px solid #34495E;"
            "   border-radius: 8px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #34495E;"
            "}"
            );
    }
}

void GameWidget::onCardClicked() {
    if (isProcessing) return;

    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    int idx = -1;
    for (int i = 0; i < 16; ++i) {
        if (buttons[i] == clickedButton) {
            idx = i;
            break;
        }
    }

    if (idx == -1 || !buttons[idx]->isEnabled() || idx == firstClickedIdx) return;

    QPropertyAnimation *flipAnimation = new QPropertyAnimation(buttons[idx], "geometry");
    flipAnimation->setDuration(250);
    QRect orgRect = buttons[idx]->geometry();

    flipAnimation->setKeyValueAt(0.5, QRect(orgRect.x() + orgRect.width()/2, orgRect.y(), 1, orgRect.height()));

    flipAnimation->setEndValue(orgRect);
    flipAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    buttons[idx]->setText(logic.getCardIcon(idx));

    buttons[idx]->setStyleSheet(buttons[idx]->styleSheet() + " QPushButton { color: #F1C40F; }");

    if (firstClickedIdx == -1) {
        firstClickedIdx = idx;
    } else {
        secondClickedIdx = idx;
        isProcessing = true;

        if (logic.checkMatch(firstClickedIdx, secondClickedIdx)) {

            applyButtonStyle(buttons[firstClickedIdx], true);
            applyButtonStyle(buttons[secondClickedIdx], true);

            buttons[firstClickedIdx]->setEnabled(false);
            buttons[secondClickedIdx]->setEnabled(false);

            firstClickedIdx = -1;
            secondClickedIdx = -1;
            isProcessing = false;

            if (logic.isGameOver()) {
                gamesPlayedInSession++;
                emit gameFinished();
                setupNewGame();
            }
        } else {

            QTimer::singleShot(800, this, &GameWidget::hideSelectedCards);
        }
    }
}

void GameWidget::hideSelectedCards() {
    if (firstClickedIdx != -1 && secondClickedIdx != -1) {

        buttons[firstClickedIdx]->setText("?");
        applyButtonStyle(buttons[firstClickedIdx], false);

        buttons[secondClickedIdx]->setText("?");
        applyButtonStyle(buttons[secondClickedIdx], false);
    }
    firstClickedIdx = -1;
    secondClickedIdx = -1;
    isProcessing = false;
}
