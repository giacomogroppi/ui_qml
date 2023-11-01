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

    /**
     * \brief Getter for the current position path show in the UI
     * \return The current position for saving file
     */
    nd auto getPositionFile() const -> QString;

    /**
     * \brief Setter for path position
     * \param newPosition A new position entered by the client
     */
    auto setPositionFile(const QString& newPosition) -> void;

public slots:
    /**
     * \brief Call this method to update the path show in the UI with the
     * model.
     */
    void positionFileChanged();

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
