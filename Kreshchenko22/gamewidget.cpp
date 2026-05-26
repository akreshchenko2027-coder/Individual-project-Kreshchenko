#include "gamewidget.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <algorithm>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), firstClickedIdx(-1), secondClickedIdx(-1), isProcessing(false), gamesPlayedInSession(0)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(10);

    for (int i = 0; i < 16; ++i) {
        QPushButton *btn = new QPushButton("?", this);
        btn->setFixedSize(75, 75);
        btn->setStyleSheet("font-size: 24px; font-weight: bold; background-color: #ECF0F1; color: #2C3E50; border: 2px solid #BDC3C7; border-radius: 8px;");
        gridLayout->addWidget(btn, i / 4, i % 4);
        buttons.push_back(btn);

        connect(btn, &QPushButton::clicked, this, &GameWidget::onCardClicked);
    }

    QPushButton *btnMenu = new QPushButton("↩ Меню", this);
    btnMenu->setStyleSheet("font-size: 14px; padding: 5px; margin-top: 15px;");
    connect(btnMenu, &QPushButton::clicked, this, &GameWidget::menuRequested);

    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(btnMenu);
}

void GameWidget::setupNewGame() {
    logic.startNewGame(8);
    firstClickedIdx = -1;
    secondClickedIdx = -1;
    isProcessing = false;

    for (auto *btn : buttons) {
        btn->setText("?");
        btn->setEnabled(true);
        btn->setStyleSheet("font-size: 24px; font-weight: bold; background-color: #ECF0F1; color: #2C3E50; border: 2px solid #BDC3C7; border-radius: 8px;");
    }
}

void GameWidget::onCardClicked() {
    if (isProcessing) return;

    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    auto it = std::find(buttons.begin(), buttons.end(), clickedButton);
    int idx = std::distance(buttons.begin(), it);

    if (clickedButton->text() != "?") return;

    clickedButton->setText(logic.getCardIcon(idx));
    clickedButton->setStyleSheet("font-size: 24px; font-weight: bold; background-color: #FFFFFF; color: #2C3E50; border: 2px solid #3498DB; border-radius: 8px;");

    if (firstClickedIdx == -1) {
        firstClickedIdx = idx;
    } else {
        secondClickedIdx = idx;
        isProcessing = true;

        if (logic.checkMatch(firstClickedIdx, secondClickedIdx)) {
            buttons[firstClickedIdx]->setStyleSheet("font-size: 24px; font-weight: bold; background-color: #D5F5E3; color: #27AE60; border: 2px solid #2ECC71; border-radius: 8px;");
            buttons[secondClickedIdx]->setStyleSheet("font-size: 24px; font-weight: bold; background-color: #D5F5E3; color: #27AE60; border: 2px solid #2ECC71; border-radius: 8px;");
            buttons[firstClickedIdx]->setEnabled(false);
            buttons[secondClickedIdx]->setEnabled(false);

            firstClickedIdx = -1;
            secondClickedIdx = -1;
            isProcessing = false;

            if (logic.isGameOver()) {
                gamesPlayedInSession++;
                emit gameFinished();

                QString scientificFact = "<h3>Перемога! </h3>"
                                         "<p>Ви успішно пройшли активне тестування пам'яті.</p>"
                                         "<hr>"
                                         "<p><b>Когнітивна довідка:</b><br>"
                                         "Зараз ваш мозок задіяв зорову пам'ять. Багаторазова "
                                         "практика вилучення інформації (Testing Effect) створює "
                                         "стійкі структури в довготривалій пам'яті.</p>";

                if (gamesPlayedInSession >= 3) {
                    scientificFact += "<p style='color: #E67E22;'><b>Увага (Ефект відстані):</b> "
                                      "Ви зіграли декілька сесій поспіль. Згідно з дослідженнями, "
                                      "заплановані перерви між тренуваннями значно ефективніші, "
                                      "ніж одна довга безперервна сесія! Зробіть паузу.</p>";
                }

                QMessageBox::information(this, "Когнітивний результат", scientificFact);
                emit menuRequested();
            }
        } else {
            QTimer::singleShot(800, this, &GameWidget::hideSelectedCards);
        }
    }
}

void GameWidget::hideSelectedCards() {
    buttons[firstClickedIdx]->setText("?");
    buttons[secondClickedIdx]->setText("?");
    buttons[firstClickedIdx]->setStyleSheet("font-size: 24px; font-weight: bold; background-color: #ECF0F1; color: #2C3E50; border: 2px solid #BDC3C7; border-radius: 8px;");
    buttons[secondClickedIdx]->setStyleSheet("font-size: 24px; font-weight: bold; background-color: #ECF0F1; color: #2C3E50; border: 2px solid #BDC3C7; border-radius: 8px;");

    firstClickedIdx = -1;
    secondClickedIdx = -1;
    isProcessing = false;
}
