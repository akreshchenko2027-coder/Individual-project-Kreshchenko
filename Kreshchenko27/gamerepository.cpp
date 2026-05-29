#include "gamerepository.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

GameRepository::GameRepository(const QString &filePath)
    : m_filePath(filePath), m_totalGamesPlayed(0) {}

bool GameRepository::loadFromFile() {
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        m_totalGamesPlayed = 0;
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    m_totalGamesPlayed = obj.value("totalGamesPlayed").toInt(0);
    file.close();
    return true;
}

bool GameRepository::saveToFile() {
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QJsonObject obj;
    obj["totalGamesPlayed"] = m_totalGamesPlayed;

    QJsonDocument doc(obj);
    file.write(doc.toJson());
    file.close();
    return true;
}

int GameRepository::getTotalGamesPlayed() const {
    return m_totalGamesPlayed;
}

void GameRepository::setTotalGamesPlayed(int count) {
    m_totalGamesPlayed = count;
}
