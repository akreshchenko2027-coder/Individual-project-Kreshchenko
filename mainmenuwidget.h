#pragma once
#include <QWidget>

class MainMenuWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainMenuWidget(QWidget *parent = nullptr);

signals:
    void startGameRequested();
};
