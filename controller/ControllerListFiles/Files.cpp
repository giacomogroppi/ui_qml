#include "Files.h"

File::File(const QByteArray &name, const QDate &lastMod)
    : _name(name)
    , _lastMod(lastMod)
{
}

bool File::operator==(const File &other) const
{
    return this->_name == other._name;
}
