#!/usr/bin/env python
# -*- coding: utf-8 -*-

from setuptools import setup, find_packages

setup(
    name='qmlf',
    version="1.0.0",
    description="Qt文档链接修复工具",
    long_description="""用于将 Qt 官网的文档经typora转化后的 Markdown 中原链接链接修复为正确的链接""",
    keywords='Qtdoc MarkDown Linker Fixer',
    author='xyz1001',
    author_email='zgzf1001@gmail.com',
    url='https://github.com/xyz1001/qmlf',
    license='MIT',
    py_modules=['qt_link_modifier', 'qmlf'],
    include_package_data=True,
    zip_safe=False,
    install_requires=['BeautifulSoup4', 'docopt'],
    classifiers=[
        'Programming Language :: Python :: 3',
    ],
    entry_points={'console_scripts': [
        'qmlf = qmlf:main',
    ]},
)
