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
    Q_PROPERTY(QString text WRITE setText)
    QML_ELEMENT

public:
    static std::shared_ptr<TextBalloon> defaultBalloon;

    TextBalloon(QQuickItem *parent = nullptr);

    ~TextBalloon();

    void paint(QPainter *painter) override;

    void setText(QString text);

private:
    QString text;
};

#endif //QT_WASM_INPUT_METHOD_TEXTBALLOON_H
