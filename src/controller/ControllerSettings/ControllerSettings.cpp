#include "ControllerSettings.h"
#include <QStandardPaths>

#include "utils/slash/slash.h"
#include "Scheduler/Scheduler.h"

ControllerSettings::ControllerSettings(QObject *parent, Fn<WString()> getPath)
    : QObject(parent)
    , _options(new WOptionSettings())
    , _getPath(std::move(getPath))
    , _pathSaving()
{
    _options->begin();

    Scheduler::addTaskMainThread(new WTaskFunction(nullptr, [this] { _pathSaving = _getPath(); }, true));
}

ControllerSettings::~ControllerSettings()
{
    _options->save();
}

auto ControllerSettings::onPositionChanged() -> void
{
    const auto newPath = _getPath();
    if (newPath != _pathSaving) {
        _pathSaving = newPath;
        emit onPositionFileChange();
    }
}

auto ControllerSettings::getPositionFile() const -> QString
{
    return this->_pathSaving;
}

auto ControllerSettings::setPositionFile(const QString& path) -> void
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
