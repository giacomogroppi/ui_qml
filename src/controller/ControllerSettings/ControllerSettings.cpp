#include "ControllerSettings.h"
#include <QStandardPaths>

#include "utils/slash/slash.h"
#include "Scheduler/Scheduler.h"

ControllerSettings::ControllerSettings(QObject *parent, Fn<WPath()> getPath)
    : QObject(parent)
    , _options(new WOptionSettings())
    , _getPath(std::move(getPath))
    , _pathSaving()
{
    _options->begin();

    auto updatePath = [this] { onPositionFileChange(); };

    Scheduler::addTaskMainThread(Scheduler::Ptr<WTask>(new WTaskFunction(nullptr, true, std::move(updatePath))));
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
    return this->_pathSaving.toString();
}

auto ControllerSettings::setPositionFile(const QString& path) -> void
{
    const auto newPath = WPath(path);
    if (_pathSaving != newPath) {
        _pathSaving = newPath;
        emit onPositionFileChange();
    }
}

auto ControllerSettings::getDefaultSavePath() -> WPath
{
    const auto path = WPath{QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)} / "Writernote";
    return path;
}
