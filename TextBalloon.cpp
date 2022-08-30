//
// Created by Larry on 2022/8/30.
//

#include "TextBalloon.h"
#include <QBrush>
#include <QPainter>
#include <iostream>

std::shared_ptr<TextBalloon> TextBalloon::defaultBalloon = std::make_shared<TextBalloon>(nullptr);

TextBalloon::TextBalloon(QQuickItem *parent)
        : QQuickPaintedItem(parent), text("") {
    std::cout << "TextBalloon" << std::endl;
    TextBalloon::defaultBalloon.reset(this);
}

TextBalloon::~TextBalloon() {
    std::cout << "~TextBalloon" << std::endl;
}


void TextBalloon::paint(QPainter *painter) {
    QBrush brush(QColor("#007430"));

    painter->setBrush(brush);
    painter->setPen(Qt::SolidLine);
    painter->setRenderHint(QPainter::Antialiasing);

    QSizeF itemSize = size();
    painter->drawRoundedRect(0, 0, itemSize.width(), itemSize.height() - 10, 10, 10);

    const QPointF points[3] = {
            QPointF(10.0, itemSize.height() - 10.0),
            QPointF(20.0, itemSize.height()),
            QPointF(30.0, itemSize.height() - 10.0),
    };
    painter->drawConvexPolygon(points, 3);
    QString fullText = this->text + this->compositionText;
    painter->drawText(this->boundingRect(), Qt::AlignLeft, fullText);
}

void TextBalloon::setText(QString text) {
    qDebug() << "setText: " << text;
    this->text = text;
    this->update();
}

void TextBalloon::appendText(QString text) {
    qDebug() << "appendText: " << text;
    this->text = this->text + text;
    this->update();
}

void TextBalloon::deleteContent() {
    qDebug() << "deleteContent";
    this->text = this->text.mid(0, this->text.length() - 1);
    this->update();
}

void TextBalloon::insertLineBreak() {
    qDebug() << "insertLineBreak";
    this->text = this->text + "\n";
    this->update();
}


void TextBalloon::setCompositionText(QString compositionEvent, QString text) {
    qDebug() << "setCompositionText: " << text;
    if (compositionEvent == "compositionstart")
        this->compositionText = "";
    else if (compositionEvent == "compositionupdate")
        this->compositionText = text;
    else if (compositionEvent == "compositionend") {
        this->compositionText = "";
        this->text = this->text + text;
    } else
        this->compositionText = "";
    this->update();
}