#include "gamelogic.h"
#include <algorithm>
#include <random>
#include <chrono>

GameLogic::GameLogic() : remainingPairs(0) {
    icons = {"A", "B", "C", "D", "E", "F", "G", "H"};
}

void GameLogic::startNewGame(int pairsCount) {
    remainingPairs = pairsCount;
    cards.clear();

    for (int i = 0; i < pairsCount; ++i) {
        cards.push_back(i);
        cards.push_back(i);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

QString GameLogic::getCardIcon(int index) const {
    if (index >= 0 && index < static_cast<int>(cards.size())) {
        int iconIdx = cards[index];
        return icons[iconIdx];
    }
    return "?";
}

bool GameLogic::checkMatch(int firstIdx, int secondIdx) {
    if (firstIdx < 0 || firstIdx >= static_cast<int>(cards.size()) ||
        secondIdx < 0 || secondIdx >= static_cast<int>(cards.size())) {
        return false;
    }

    if (cards[firstIdx] == cards[secondIdx]) {
        remainingPairs--;
        return true;
    }

    return false;
}

bool GameLogic::isGameOver() const {
    return remainingPairs == 0;
}
