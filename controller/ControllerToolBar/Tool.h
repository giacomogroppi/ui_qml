#pragma once

class Tool
{
private:
    enum ToolType {
        Pen,
        Rubber,
        Highlighter,
        Hand
    } _type;
public:
    Tool();

    bool isPen() const;
    bool isRubber() const;
    bool isHighlighter() const;
    bool isHand() const;

    void setPen();
    void setRubber();
    void setHighlighter();
    void setHand();
};
