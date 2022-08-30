//
// Created by Larry on 2022/8/30.
//

#ifndef QT_WASM_INPUT_METHOD_TEXTBALLOON_H
#define QT_WASM_INPUT_METHOD_TEXTBALLOON_H

#include <QObject>
#include <qqmlregistration.h>
#include <QQuickPaintedItem>

class TextBalloon : public QQuickPaintedItem {
Q_OBJECT
    Q_PROPERTY(bool rightAligned WRITE setRightAligned)
    QML_ELEMENT

public:
    TextBalloon(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

    void setRightAligned(bool rightAligned);

private:
    bool rightAligned;
};

#endif //QT_WASM_INPUT_METHOD_TEXTBALLOON_H
