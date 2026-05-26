#pragma once
#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <vector>
#include "gamelogic.h"

class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    void setupNewGame();

signals:
    void menuRequested();
    void gameFinished();

private slots:
    void onCardClicked();
    void hideSelectedCards();

private:
    GameLogic logic;
    std::vector<QPushButton*> buttons;
    int firstClickedIdx;
    int secondClickedIdx;
    bool isProcessing;
    int gamesPlayedInSession;
};
