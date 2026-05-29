#ifndef GAMEREPOSITORY_H
#define GAMEREPOSITORY_H

#include <QString>

class GameRepository {
public:
    explicit GameRepository(const QString &filePath);

    bool loadFromFile();
    bool saveToFile();

    int getTotalGamesPlayed() const;
    void setTotalGamesPlayed(int count);

private:
    QString m_filePath;
    int m_totalGamesPlayed;
};

#endif
