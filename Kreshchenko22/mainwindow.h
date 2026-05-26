#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStackedWidget;
class MainMenuWidget;
class GameWidget;
class StatsWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *m_stackedWidget;
    MainMenuWidget *m_menuWidget;
    GameWidget *m_gameWidget;
    StatsWidget *m_statsWidget;
    int m_totalGamesPlayed;
};

#endif
