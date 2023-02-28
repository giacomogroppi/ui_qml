#pragma once

#include <QDate>
#include <QString>
#include <QByteArray>

class Files
{
private:
    QDate _lastMod;
    QByteArray _name;
public:
    Files(const QByteArray &path, const QDate &_lastMod);
    ~Files() = default;

    const QByteArray &getName() const;
    const QDate &getLastMod() const;

};

inline const QByteArray& Files::getName() const
{
    return this->_name;
}

inline const QDate &Files::getLastMod() const
{
    return this->_lastMod;
}
