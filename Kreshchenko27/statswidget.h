#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;

class StatsWidget : public QWidget {
    Q_OBJECT
public:
    explicit StatsWidget(QWidget *parent = nullptr);
    void updateStats(int gamesCount);

signals:
    void menuRequested();
    void clearRequested();

private:
    QLabel *m_statsLabel;
    QPushButton *m_btnClear;
};

#endif
