#!/usr/bin/env python


'''
Qt文档链接修复工具(Qtdoc Markdown Link Fixer)，用于将 Qt 官网的文档经typora转化后的 Markdown 中原链接链接修复为正确的链接

Usage:
    qmlf <website> <filename>

Arguments:
    website 待翻译的 Qt5 官方文档页面网址，需以https://doc.qt.io/qt-5开头
    filename Typora 转化后的 markdown 文档名，转换后该文件将会被覆盖写入

Options:
    -h --help
'''

from docopt import docopt
import os.path
import qt_link_modifier


def _fix(website, filename):
    if not website.startswith("https://doc.qt.io/qt-5/"):
        print(__doc__)
        return None
    if not filename.endswith(".md"):
        filename = filename + ".md"
    if not os.path.exists(filename):
        return None

    print("Read from %s" % filename)
    with open(filename) as fin:
        markdown = fin.read()

    print("Fix links in markdown")
    return qt_link_modifier.modify_qt_link(
        website, filename, markdown)


def main():
    args = docopt(__doc__)
    website = args["<website>"]
    filename = args["<filename>"]

    markdown = _fix(website, filename)

    if markdown is None:
        print("error!")
        return

    print("Write to %s" % filename)
    with open(filename, "w") as fin:
        fin.write(markdown)


if __name__ == "__main__":
    main()
