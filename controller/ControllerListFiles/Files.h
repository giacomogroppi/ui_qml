#pragma once

#include <QDate>
#include <QString>
#include <QByteArray>

class File
{
private:
    QDate _lastMod;
    QByteArray _name;
public:
    File(const QByteArray &name, const QDate &lastMod);
    ~File() = default;

    const QByteArray &getName() const;
    const QDate &getLastMod() const;

    bool operator==(const File &other) const;
};

inline const QByteArray& File::getName() const
{
    return this->_name;
}

inline const QDate &File::getLastMod() const
{
    return this->_lastMod;
}
