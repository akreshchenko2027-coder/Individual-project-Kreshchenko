#pragma once
#include <vector>
#include <QString>

class GameLogic {
public:
    GameLogic();
    void startNewGame(int pairsCount);
    QString getCardIcon(int index) const;
    bool checkMatch(int firstIdx, int secondIdx);
    bool isGameOver() const;

private:
    std::vector<int> cards;
    std::vector<QString> icons;
    int remainingPairs;
};
