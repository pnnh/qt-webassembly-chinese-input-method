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

    // todo 应该点击时才激活，这里是测试目的
    this->setActive();
}

TextBalloon::~TextBalloon() {
    std::cout << "~TextBalloon" << std::endl;
    if (m_nTimerId != 0)
        killTimer(m_nTimerId);
}

void TextBalloon::timerEvent(QTimerEvent *event) {
    qDebug("timer event, id %d", event->timerId());
    this->blinkCount += 1;

    this->update();
}

void TextBalloon::setActive() {
    qDebug("setActive");
    if (m_nTimerId == 0)
        m_nTimerId = startTimer(500);
}

void TextBalloon::paint(QPainter *painter) {
    QBrush brush(QColor("#FFFFFF"));

    painter->setBrush(brush);
    painter->setPen(Qt::SolidLine);
    painter->setRenderHint(QPainter::Antialiasing);

    QSizeF itemSize = size();
    painter->drawRoundedRect(0, 0, itemSize.width(), itemSize.height() - 10, 10, 10);

    QString fullText = this->text + this->compositionText;
    painter->drawText(this->boundingRect(), Qt::AlignLeft, fullText);
    if (this->blinkCount % 2 == 0) {
        auto br = painter->boundingRect(this->boundingRect(), Qt::TextWordWrap, fullText);
        auto splittedText = fullText.split("\n");
        if (splittedText.length() < 1)
            return;
        auto lastLine = splittedText[splittedText.length() - 1];
        if (lastLine.isEmpty())
            lastLine = " ";
        auto singleLineBr = painter->boundingRect(this->boundingRect(), Qt::TextSingleLine, lastLine);
        qDebug() << "blink: " << br << "|" << singleLineBr << "|" << lastLine << "|";

        auto xOffset = singleLineBr.width();
        painter->drawLine(xOffset, br.height() - singleLineBr.height(), xOffset,
                          br.height());
    }
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