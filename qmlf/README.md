# Qt文档链接修复工具（Qtdoc Markdown Link Fixer)

本工具为[ Qt 中文文档项目](https://github.com/QtDocumentCN/QtDocumentCN)的专用工具，用于将 Qt 官网的文档经typora转化后的 Markdown 中原链接修复为根据 Qt 中文文档项目的链接规范定义的链接。

# 原因

Qt 文档在含有大量的链接，[ Qt 中文文档项目贡献规范](https://github.com/QtDocumentCN/QtDocumentCN/blob/master/CONTRIBUTING.md#%E5%BC%95%E7%94%A8%E9%93%BE%E6%8E%A5)中要求使用的 markdown 跳转规则相对复杂，尤其是外部链接。首先需要手动拼接出类的翻译文档在项目中的路径，再，跳转到对应类页面，找到函数名，再通过规则获得函数标题的链接。例如 [Container Classes](https://doc.qt.io/qt-5/containers.html) 一文中，有大量的外部函数跳转，以 [QMap::value()](https://doc.qt.io/qt-5/containers.html#:~:text=QMap%3A%3Avalue) 为例，我要作如下处理：

1. 确定QMap类在[ Qt 中文文档项目](https://github.com/QtDocumentCN/QtDocumentCN)的相对路径。为`../../M/QMap/QMap.md`。
2. 跳转至 Qt 文档的 QMap 页面，找到 `value` 方法的函数原型，为`const T QMap::value(const Key &key, const T &defaultValue = T()) const`。
3. 按照规则转化为 Markdown 跳转链接。为`const-t-qmapvalueconst-key-key,-const-t-defaultvalue--t-const`。
4. 拼接。最终得到`../../M/QMap/QMap.md#const-t-qmapvalueconst-key-key,-const-t-defaultvalue--t-const`。整个过程耗时约30s。

整个翻译过程中，这里产生了大量的无意义事件浪费，于是开发了这个小工具自动化地完成这些事。

# 安装

1. pip3 install git+https://github.com/xyz1001/qmlf.git

# 使用

1. 复制待翻译的 Qt 文档页面内容
2. 粘贴至 Typora 中，自动转换为 Markdown，保存（注意文件名需规范）
3. 执行`qmlf <文档网页链接> <markdown 文件名>`自动修复链接
4. 手动调整部分无法自动修复的链接。
