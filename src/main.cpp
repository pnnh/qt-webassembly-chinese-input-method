#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <string>
#include <iostream>

using namespace std;

float compareBig(int a, int b) {
    return a > b ? a : b;
}

#ifdef __EMSCRIPTEN__

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

emscripten::val callComposition(const int event, const std::string &content) {
    std::cout << event << "|" << content << std::endl;
    std::string str = "ok";
    return emscripten::val(str);
}

EMSCRIPTEN_BINDINGS(demo) {
    emscripten::function("tryCharPtr", &tryCharPtr);
    emscripten::function("tryStdString", &tryStdString);
    emscripten::function("callComposition", &callComposition);
}

extern "C" {

EMSCRIPTEN_KEEPALIVE int myFunction() {
    printf("我的函数已被调用\n");
    return 0;
}

EMSCRIPTEN_KEEPALIVE int set_data_demo(char *data, int len) {
    printf("我的函数已被调用2\n");
    //auto str = QString::fromUtf8(data, len);
    string str = data;
    //qInfo() << "received:" << str;
    //QByteArray ba = str.toLocal8Bit();
    const char *c_str2 = str.c_str();
    printf("str2: %s", c_str2);
    return strlen(data);
}

}
#endif


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    // 设置全局字体，用于解决Qt for WebAssembly中文显示异常问题
    // fileName 参数不用带qrc:前缀
    int fontId = QFontDatabase::addApplicationFont(
            ":/static/assets/fonts/NotoSansSC/NotoSansSC-Regular.otf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    qDebug() << "fontfamilies:" << fontFamilies;
    if (!fontFamilies.empty()) {
        QFont font;
        auto fontFamilie = fontFamilies[0];
        font.setFamily(fontFamilie); // 设置全局字体
        QGuiApplication::setFont(font);
    }
    QQmlApplicationEngine engine;
    QString strUrl{"qrc:/static/assets/qml/Main.qml"};

    const QUrl url(strUrl);

    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return QGuiApplication::exec();
}
