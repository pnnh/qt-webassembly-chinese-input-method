cmake_minimum_required(VERSION 3.15)

project(qt-wasm-input-method VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_program(CCACHE ccache)
if (CCACHE)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif (CCACHE)

find_package(Qt6 COMPONENTS Core Gui Quick QuickLayouts QuickControls2
        QuickTemplates2 Network REQUIRED)

qt_add_executable(qt-wasm-input-method MANUAL_FINALIZATION
        src/main.cpp)

target_link_libraries(qt-wasm-input-method
        PRIVATE Qt6::Core Qt6::Gui Qt6::Quick Qt6::QuickControls2 Qt6::Network)
set_target_properties(qt-wasm-input-method PROPERTIES LINK_FLAGS "--bind")

# 当编译WebAssembly时修改链接参数，否则会报初始内存太小错误
if (EMSCRIPTEN)
    set(QT_WASM_INITIAL_MEMORY 96MB)
    set(QT_WASM_TOTAL_MEMORY 128MB)
endif ()

qt_import_qml_plugins(qt-wasm-input-method)
qt_finalize_executable(qt-wasm-input-method)

qt_add_qml_module(qt-wasm-input-method
        URI static
        VERSION 1.0
        QML_FILES
        assets/qml/Main.qml
        RESOURCES
        assets/fonts/NotoSansSC/NotoSansSC-Regular.otf)