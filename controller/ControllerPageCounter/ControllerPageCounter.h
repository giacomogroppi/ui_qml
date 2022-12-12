#pragma once

#include <QObject>

class ControllerPageCounter: public QObject {
    Q_OBJECT
private:
    int _page;
public:
    explicit ControllerPageCounter(QObject *parent);
    ~ControllerPageCounter() = default;

    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged);
    int page() const;
    void setPage(int index);
    Q_SIGNAL void pageChanged();

    Q_PROPERTY(int numberOfPage READ numberOfPage NOTIFY numberOfPageChanged);
    int numberOfPage() const;
    Q_SIGNAL void numberOfPageChanged();
};
