#pragma once

#include <QObject>
#include "core/WOptionSetting/WOptionSettings.h"
#include "core/pointer/UniquePtr.h"
#include <QString>
#include "utils/WCommonScript.h"
#include "core/Path/WPath.h"

class ControllerSettings: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString positionFile READ getPositionFile WRITE setPositionFile NOTIFY onPositionFileChange);

private:
    UniquePtr<WOptionSettings> _options;

public:
    explicit ControllerSettings(QObject *parent, Fn<WPath()> getPath);
    ~ControllerSettings() override;

    auto getPositionFile() const -> QString;
    auto setPositionFile(const QString& newPosition) -> void;

public slots:
    void onPositionChanged();

signals:
    void onPositionFileChange();

public:
    static auto getDefaultSavePath() -> WPath;
private:

    /**
     * This is the path in which the application
     * should save the documents
    */
    Fn<WPath()> _getPath;
    WPath _pathSaving;
};
