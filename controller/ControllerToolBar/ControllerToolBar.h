#pragma once

#include <QObject>

class ControllerToolBar: public QObject {
    Q_OBJECT
public:
    explicit ControllerToolBar(QObject *parent = nullptr);
    ~ControllerToolBar();

    Q_INVOKABLE void clickSelectPen();

    Q_PROPERTY(bool isPenSelected READ isPenSelected NOTIFY toolHasChanged);
    bool isPenSelected() const;

    Q_PROPERTY(bool isRubberSelected READ isRubberSelected NOTIFY toolHasChanged);
    bool isRubber() const;

    Q_PROPERTY(bool isHandSelected READ isHandSelected NOTIFY toolHasChanged);
    bool isHand() const;

    Q_PROPERTY(bool isHighlighterSelected READ isHighlighterSelected NOTIFY toolHasChanged);
    bool isHighlighter() const;

signals:
    void toolHasChanged();
};
