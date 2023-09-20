#include "ControllerSettings.h"
#include <QStandardPaths>

#include "utils/slash/slash.h"

ControllerSettings::ControllerSettings(QObject *parent)
    : QObject(parent)
    , _options(new WOptionSettings())
{
    _options->begin();


    _pathSaving = _options->value(namePositionSettings, getDefaultSavePath()).toString();
}

ControllerSettings::~ControllerSettings()
{
    _options->save();
}

auto ControllerSettings::getPositionFile() const -> QString
{
    return this->_pathSaving;
}

auto ControllerSettings::setPositionFile(QString path) -> void
{
    if (_pathSaving != path) {
        _pathSaving = path;
        emit onPositionFileChange();
    }
}

auto ControllerSettings::getDefaultSavePath() -> QString
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + slash::__slash() + "Writernote";
    return path;
}
