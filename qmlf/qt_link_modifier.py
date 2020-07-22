#!/usr/bin/env python

import re
import sys
import urllib.request
from bs4 import BeautifulSoup

WebPageCache = {}
QtWebUrlPrefix = "https://doc.qt.io/qt-5/"


def _convert_function_title_to_url(title):
    # remove link in title
    title = re.sub(r"\[(.*?)\]\(.*?\)", r"\1", title)
    title = " ".join(title.split())
    title = re.sub(r"[^a-zA-Z0-9 ]", '', title)
    title = title.strip().lower()
    title = title.replace(" ", "-")
    return title


def _load_html(url):
    if url in WebPageCache:
        html = WebPageCache[url]
    else:
        print("Load webpage %s" % url)
        with urllib.request.urlopen(url) as f:
            html = f.read().decode('utf-8')
            WebPageCache[url] = html
    return html


def _find_link_title(link):
    url = link.split("#")[0]
    href = link.split("#")[1]
    html = _load_html(url)

    soup = BeautifulSoup(html, 'html.parser')
    title = soup.find(id=href)

    if title is None:
        return None
    return title.getText()


def _find_class_name(link):
    url = link.split("#")[0]
    html = _load_html(url)

    soup = BeautifulSoup(html, 'html.parser')
    title = soup.find("h1", {"class": "title"})
    if title is None:
        return None

    fields = title.getText().split(" ")
    # not a Qt class page
    if len(fields) <= 1 or fields[1] != "Class":
        return None
    # not a Qt class page
    class_name = fields[0]
    if class_name[0] != "Q" or not class_name[1].isupper():
        return None
    return class_name


def _fix_qt_class_link(markdown, links):
    left_links = []
    for link in links:
        lst = link[1:-1].split("](")
        text = lst[0]
        url = lst[1].lower()
        if text[0] != "Q" or "%s%s.html" % (QtWebUrlPrefix, text.lower()) != url:
            left_links.append(link)
            continue
        actual_url = "../../%s/%s/%s.md" % (text[1], text, text)
        actual_link = link.replace(url, actual_url)
        print("Fix %s -> %s" % (link, actual_link))
        markdown = markdown.replace(link, actual_link)
    return markdown, left_links


def _fix_qt_function_link(website, markdown_name, markdown, links):
    left_links = []
    for link in links:
        lst = link[1:-1].split("](")
        url = lst[1]

        if ".html#" not in url:
            left_links.append(link)
            continue

        title = _find_link_title(url)

        if title is None:
            left_links.append(link)
            continue

        if(url.split("#")[0] == website):
            filepath = markdown_name
        else:
            class_name = _find_class_name(url)
            if class_name is None:
                left_links.append(link)
                continue
            filepath = "../../%s/%s/%s.md" % (
                class_name[1], class_name, class_name)
        actual_url = "%s#%s" % (
            filepath, _convert_function_title_to_url(title))
        actual_link = link.replace(url, actual_url)
        print("Fix %s -> %s" % (link, actual_link))
        markdown = markdown.replace(link, actual_link)

    return markdown, left_links


def _find_links(markdown):
    matchs = re.findall(r"\[[^\[]+?\]\(.*?\)", markdown)
    links = list(dict.fromkeys(matchs))
    return links


def modify_qt_link(website, filename, markdown):
    markdown_name = filename.split("/")[-1]

    links = _find_links(markdown)
    markdown, links = _fix_qt_class_link(markdown, links)
    markdown, links = _fix_qt_function_link(
        website, markdown_name, markdown, links)
    print("---------Not fix links----------")
    print(*links, sep="\n")
    print("--------------------------------")
    return markdown


if __name__ == "__main__":
    with open(sys.argv[1], 'r') as fin:
        markdown = fin.read()
        links = _find_links(markdown)
        markdown, links = _fix_qt_class_link(markdown, links)
        markdown, links = _fix_qt_function_link(markdown, links)
        print(markdown)
