#include "gamewidget.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QFont>
#include <QPropertyAnimation> // АНІМАЦІЯ: Інклуд для анімацій

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , firstClickedIdx(-1)
    , secondClickedIdx(-1)
    , isProcessing(false)
    , gamesPlayedInSession(0)
{
    // Шрифт для екрану гри
    QFont defaultFont("Segoe UI", 11);
    this->setFont(defaultFont);

    // Загальний лейаут
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // Сітка для карт
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(10);

    buttons.resize(16);
    for (int i = 0; i < 16; ++i) {
        buttons[i] = new QPushButton("?", this);
        buttons[i]->setMinimumSize(70, 80);

        // ДИЗАЙН: Застосовуємо початковий красивий стиль (темно-синій)
        applyButtonStyle(buttons[i]);

        gridLayout->addWidget(buttons[i], i / 4, i % 4);

        // Зв'язуємо клік по карті
        connect(buttons[i], &QPushButton::clicked, this, &GameWidget::onCardClicked);
    }

    mainLayout->addLayout(gridLayout);

    // Локальна кнопка повернення в меню
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

    // Скидаємо стан кнопок до початкового
    for (int i = 0; i < 16; ++i) {
        buttons[i]->setText("?");
        buttons[i]->setEnabled(true);
        // ДИЗАЙН: Скидаємо стиль до стандартного темно-синього
        applyButtonStyle(buttons[i], false);
    }
}

// ДИЗАЙН+КОНТРАСТ: Новий метод для налаштування вигляду кнопок
void GameWidget::applyButtonStyle(QPushButton *btn, bool isMatched) {
    if (isMatched) {
        // Стиль для ЗНАЙДЕНОЇ ПАРИ: Зелений фон, жовті букви, без бордера
        btn->setStyleSheet(
            "QPushButton {"
            "   background-color: #2ECC71;" // Яскравий зелений
            "   color: #F1C40F;"            // Яскравий жовтий
            "   font-size: 22px;"
            "   font-weight: bold;"
            "   border: none;"
            "   border-radius: 8px;"
            "}"
            );
    } else {
        // Стиль для ЗАКРИТОЇ/АКТИВНОЇ КАРТИ: Темно-синій фон, білі букви, бордер
        btn->setStyleSheet(
            "QPushButton {"
            "   background-color: #2C3E50;" // Глибокий темно-синій
            "   color: #FFFFFF;"            // Білий
            "   font-size: 20px;"
            "   font-weight: bold;"
            "   border: 2px solid #34495E;"
            "   border-radius: 8px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #34495E;" // Світліший при наведенні
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

    // АНІМАЦІЯ: Ефект перегортання (зміна масштабу)
    QPropertyAnimation *flipAnimation = new QPropertyAnimation(buttons[idx], "geometry");
    flipAnimation->setDuration(250); // Тривалість 0.25 сек
    QRect orgRect = buttons[idx]->geometry();
    // Звужуємо кнопку до центру (ефект ребра)
    flipAnimation->setKeyValueAt(0.5, QRect(orgRect.x() + orgRect.width()/2, orgRect.y(), 1, orgRect.height()));
    // Повертаємо початковий розмір
    flipAnimation->setEndValue(orgRect);
    flipAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    // Показуємо букву/іконку карти з логіки
    buttons[idx]->setText(logic.getCardIcon(idx));
    // ДИЗАЙН: Змінюємо колір тексту на жовтий при відкритті
    buttons[idx]->setStyleSheet(buttons[idx]->styleSheet() + " QPushButton { color: #F1C40F; }");

    if (firstClickedIdx == -1) {
        firstClickedIdx = idx;
    } else {
        secondClickedIdx = idx;
        isProcessing = true;

        if (logic.checkMatch(firstClickedIdx, secondClickedIdx)) {
            // ДИЗАЙН+КОНТРАСТ: Пара збіглася! Фарбуємо в зелений.
            applyButtonStyle(buttons[firstClickedIdx], true);
            applyButtonStyle(buttons[secondClickedIdx], true);

            // Блокуємо, але не робимо сірими
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
            // Карти не збіглися
            QTimer::singleShot(800, this, &GameWidget::hideSelectedCards);
        }
    }
}

void GameWidget::hideSelectedCards() {
    if (firstClickedIdx != -1 && secondClickedIdx != -1) {
        // ДИЗАЙН: Ховаємо і повертаємо стандартний темно-синій стиль
        buttons[firstClickedIdx]->setText("?");
        applyButtonStyle(buttons[firstClickedIdx], false);

        buttons[secondClickedIdx]->setText("?");
        applyButtonStyle(buttons[secondClickedIdx], false);
    }
    firstClickedIdx = -1;
    secondClickedIdx = -1;
    isProcessing = false;
}
