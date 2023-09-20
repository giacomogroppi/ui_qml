#pragma once

#include <QObject>
#include "core/WOptionSetting/WOptionSettings.h"
#include "core/pointer/UniquePtr.h"
#include <QString>

class ControllerSettings: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString positionFile READ getPositionFile WRITE setPositionFile NOTIFY onPositionFileChange);

private:
    UniquePtr<WOptionSettings> _options;

public:
    explicit ControllerSettings(QObject *parent = nullptr);
    ~ControllerSettings() override;

    auto getPositionFile() const -> QString;
    auto setPositionFile(QString newPosition) -> void;

signals:
    void onPositionFileChange();

private:
    static auto getDefaultSavePath() -> QString;


    /**
     * This is the path in which the application
     * should save the documents
    */
    QString _pathSaving;

    /**
     * This is the name used for WOptionSettings for identify the
     * position in which the application should save.
    */
    static constexpr auto namePositionSettings = "position_path";
};
