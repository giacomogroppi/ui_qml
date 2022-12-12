#pragma once

#include <QObject>

class ControllerToolBar: public QObject {
    Q_OBJECT

    enum ToolType {
        Pen,
        Rubber,
        Highlighter,
        Hand,
        Cut
    } _type;

public:
    explicit ControllerToolBar(QObject *parent = nullptr);
    ~ControllerToolBar();

    Q_INVOKABLE void clickSelectPen();
    Q_INVOKABLE void clickRubber();
    Q_INVOKABLE void clickHand();
    Q_INVOKABLE void clickHighlighter();
    Q_INVOKABLE void clickCut();

    Q_PROPERTY(bool isPenSelected READ isPen NOTIFY toolHasChanged);
    bool isPen() const;

    Q_PROPERTY(bool isRubberSelected READ isRubber NOTIFY toolHasChanged);
    bool isRubber() const;

    Q_PROPERTY(bool isHandSelected READ isHand NOTIFY toolHasChanged);
    bool isHand() const;

    Q_PROPERTY(bool isHighlighterSelected READ isHighlighter NOTIFY toolHasChanged);
    bool isHighlighter() const;

    Q_PROPERTY(bool isCutSelected READ isCut NOTIFY toolHasChanged);
    bool isCut() const;

signals:
    void toolHasChanged();
};
