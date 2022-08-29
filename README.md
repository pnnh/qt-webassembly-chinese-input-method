尝试实现QT WebAssembly下的中文输入

# Webassembly功能测试

## CLion下测试

```shell
# 配置了以下cmake参数
-DCMAKE_PREFIX_PATH=~/Qt/6.2.0/macos/lib/cmake
-DCMAKE_TOOLCHAIN_FILE:PATH=~/Qt/6.2.0/wasm_32/lib/cmake/Qt6/qt.toolchain.cmake
```

## 启动本机http-server服务

```shell
npm i -g http-server   # 安装工具
# 在根目录下执行
http-server --cors
```

添加一个到assets/index.html的超链接方便测试

```shell
cd cmake-build-webassembly
ln -s  ../assets/index.html index.html
```

通过window.moduleConfig可以引用到暴露出的C++方法

通过embind形式暴露的C++方法，不会出现在生成的js文件里，而是加载wasm文件编译后会出现
