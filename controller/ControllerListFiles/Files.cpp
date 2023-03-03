#include "Files.h"

Files::Files(const QByteArray &path, const QDate &lastMod)
    : _name(path)
    , _lastMod(lastMod)
{
}
