#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <string>
#include <iostream>
#include "TextBalloon.h"

#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

//EMSCRIPTEN_BINDINGS(my_module) {
//    emscripten::function("compareBig", &compareBig);
//}

emscripten::val tryCharPtr() {
    const char *str = "abc哈哈😁☺";
    return emscripten::val(str);
}

emscripten::val tryStdString() {
    std::string str = "abc哈哈O(∩_∩)O哈哈~🐶efg☺";
    return emscripten::val(str);
}

emscripten::val callComposition(const std::string &type, const std::string &data) {
    std::cout << "=====" << type << "|" << data << "====" << std::endl;

    QString text = QString::fromStdString(data);
    TextBalloon::defaultBalloon->setText(text);

    std::string str = "ok";
    return emscripten::val(str);
}

EMSCRIPTEN_BINDINGS(demo) {
    emscripten::function("tryCharPtr", &tryCharPtr);
    emscripten::function("tryStdString", &tryStdString);
    emscripten::function("callComposition", &callComposition);
}


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    // 设置全局字体，用于解决Qt for WebAssembly中文显示异常问题
    // fileName 参数不用带qrc:前缀
    int fontId = QFontDatabase::addApplicationFont(
            ":/mymod/assets/fonts/NotoSansSC/NotoSansSC-Regular.otf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    qDebug() << "fontfamilies:" << fontFamilies;
    if (!fontFamilies.empty()) {
        QFont font;
        auto fontFamilie = fontFamilies[0];
        font.setFamily(fontFamilie); // 设置全局字体
        QGuiApplication::setFont(font);
    }
    QQmlApplicationEngine engine;
    QString strUrl{"qrc:/mymod/main.qml"};

    const QUrl url(strUrl);

    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return QGuiApplication::exec();
}
