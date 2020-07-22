# QList Class

template <typename T> class QList

The QList class is a template class that provides lists. [More...](QList.md#detailed-description)

| Header:       | #include <QList>                                             |
| ------------- | ------------------------------------------------------------ |
| qmake:        | QT += core                                                   |
| Inherited By: | [QByteArrayList](../../B/QByteArrayList/QByteArrayList.md), [QItemSelection](../../I/QItemSelection/QItemSelection.md), [QQueue](../../Q/QQueue/QQueue.md), and [QStringList](../../S/QStringList/QStringList.md) |

- [List of all members, including inherited members](https://doc.qt.io/qt-5/qlist-members.html)
- [Obsolete members](https://doc.qt.io/qt-5/qlist-obsolete.html)

**Note:** All functions in this class are [reentrant](https://doc.qt.io/qt-5/threads-reentrancy.html).



## Public Types

| class   | **[const_iterator](https://doc.qt.io/qt-5/qlist-const-iterator.html)** |
| ------- | ------------------------------------------------------------ |
| class   | **[iterator](https://doc.qt.io/qt-5/qlist-iterator.html)**   |
| typedef | **[ConstIterator](QList.md#typedef-qlistconstiterator)** |
| typedef | **[Iterator](QList.md#typedef-qlistiterator)** |
| typedef | **[const_pointer](QList.md#typedef-qlistconstpointer)** |
| typedef | **[const_reference](QList.md#typedef-qlistconstreference)** |
| typedef | **[const_reverse_iterator](QList.md#typedef-qlistconstreverseiterator)** |
| typedef | **[difference_type](QList.md#typedef-qlistdifferencetype)** |
| typedef | **[pointer](QList.md#typedef-qlistpointer)** |
| typedef | **[reference](QList.md#typedef-qlistreference)** |
| typedef | **[reverse_iterator](QList.md#typedef-qlistreverseiterator)** |
| typedef | **[size_type](QList.md#typedef-qlistsizetype)** |
| typedef | **[value_type](QList.md#typedef-qlistvaluetype)** |



## Public Functions

|                               | **[QList](QList.md#template-typename-inputiterator-qlistqlistinputiterator-first-inputiterator-last)**(InputIterator *first*, InputIterator *last*) |
| ----------------------------- | ------------------------------------------------------------ |
|                               | **[QList](QList.md#qlistqliststdinitializerlistt-args)**(std::initializer_list<T> *args*) |
|                               | **[QList](QList.md#qlistqlistqlistt-other)**(QList<T> &&*other*) |
|                               | **[QList](QList.md#qlistqlistconst-qlistt-other)**(const QList<T> &*other*) |
|                               | **[QList](QList.md#qlistqlist)**()       |
| QList<T> &                    | **[operator=](QList.md#qlistt-qlistoperatorqlistt-other)**(QList<T> &&*other*) |
| QList<T> &                    | **[operator=](QList.md#qlistt-qlistoperatorconst-qlistt-other)**(const QList<T> &*other*) |
|                               | **[~QList](QList.md#qlistqlist)**() |
| void                          | **[append](QList.md#void-qlistappendconst-t-value)**(const T &*value*) |
| void                          | **[append](QList.md#void-qlistappendconst-qlistt-value)**(const QList<T> &*value*) |
| const T &                     | **[at](QList.md#const-t-qlistatint-i-const)**(int *i*) const |
| T &                           | **[back](QList.md#t-qlistback)**()         |
| const T &                     | **[back](QList.md#const-t-qlistback-const)**() const |
| QList::iterator               | **[begin](QList.md#qlistiterator-qlistbegin)**()       |
| QList::const_iterator         | **[begin](QList.md#qlistconstiterator-qlistbegin-const)**() const |
| QList::const_iterator         | **[cbegin](QList.md#qlistconstiterator-qlistcbegin-const)**() const |
| QList::const_iterator         | **[cend](QList.md#qlistconstiterator-qlistcend-const)**() const   |
| void                          | **[clear](QList.md#void-qlistclear)**()       |
| QList::const_iterator         | **[constBegin](QList.md#qlistconstiterator-qlistconstbegin-const)**() const |
| QList::const_iterator         | **[constEnd](QList.md#qlistconstiterator-qlistconstend-const)**() const |
| const T &                     | **[constFirst](QList.md#const-t-qlistconstfirst-const)**() const |
| const T &                     | **[constLast](QList.md#const-t-qlistconstlast-const)**() const |
| bool                          | **[contains](QList.md#bool-qlistcontainsconst-t-value-const)**(const T &*value*) const |
| int                           | **[count](QList.md#int-qlistcountconst-t-value-const)**(const T &*value*) const |
| int                           | **[count](QList.md#int-qlistcount-const)**() const |
| QList::const_reverse_iterator | **[crbegin](QList.md#qlistconstreverseiterator-qlistcrbegin-const)**() const |
| QList::const_reverse_iterator | **[crend](QList.md#qlistconstreverseiterator-qlistcrend-const)**() const |
| bool                          | **[empty](QList.md#bool-qlistempty-const)**() const |
| QList::iterator               | **[end](QList.md#qlistiterator-qlistend)**()           |
| QList::const_iterator         | **[end](QList.md#qlistconstiterator-qlistend-const)**() const   |
| bool                          | **[endsWith](QList.md#bool-qlistendswithconst-t-value-const)**(const T &*value*) const |
| QList::iterator               | **[erase](QList.md#qlistiterator-qlisteraseqlistiterator-pos)**(QList::iterator *pos*) |
| QList::iterator               | **[erase](QList.md#qlistiterator-qlisteraseqlistiterator-begin-qlistiterator-end)**(QList::iterator *begin*, QList::iterator *end*) |
| T &                           | **[first](QList.md#t-qlistfirst)**()       |
| const T &                     | **[first](QList.md#const-t-qlistfirst-const)**() const |
| T &                           | **[front](QList.md#t-qlistfront)**()       |
| const T &                     | **[front](QList.md#const-t-qlistfront-const)**() const |
| int                           | **[indexOf](QList.md#int-qlistindexofconst-t-value-int-from--0-const)**(const T &*value*, int *from* = 0) const |
| void                          | **[insert](QList.md#void-qlistinsertint-i-const-t-value)**(int *i*, const T &*value*) |
| QList::iterator               | **[insert](QList.md#qlistiterator-qlistinsertqlistiterator-before-const-t-value)**(QList::iterator *before*, const T &*value*) |
| bool                          | **[isEmpty](QList.md#bool-qlistisempty-const)**() const |
| T &                           | **[last](QList.md#t-qlistlast)**()         |
| const T &                     | **[last](QList.md#const-t-qlistlast-const)**() const |
| int                           | **[lastIndexOf](QList.md#int-qlistlastindexofconst-t-value-int-from--1-const)**(const T &*value*, int *from* = -1) const |
| int                           | **[length](QList.md#int-qlistlength-const)**() const |
| QList<T>                      | **[mid](QList.md#qlistt-qlistmidint-pos-int-length--1-const)**(int *pos*, int *length* = -1) const |
| void                          | **[move](QList.md#void-qlistmoveint-from-int-to)**(int *from*, int *to*) |
| void                          | **[pop_back](QList.md#void-qlistpopback)**() |
| void                          | **[pop_front](QList.md#void-qlistpopfront)**() |
| void                          | **[prepend](QList.md#void-qlistprependconst-t-value)**(const T &*value*) |
| void                          | **[push_back](QList.md#void-qlistpushbackconst-t-value)**(const T &*value*) |
| void                          | **[push_front](QList.md#void-qlistpushfrontconst-t-value)**(const T &*value*) |
| QList::reverse_iterator       | **[rbegin](QList.md#qlistreverseiterator-qlistrbegin)**()     |
| QList::const_reverse_iterator | **[rbegin](QList.md#qlistconstreverseiterator-qlistrbegin-const)**() const |
| int                           | **[removeAll](QList.md#int-qlistremoveallconst-t-value)**(const T &*value*) |
| void                          | **[removeAt](QList.md#void-qlistremoveatint-i)**(int *i*) |
| void                          | **[removeFirst](QList.md#void-qlistremovefirst)**() |
| void                          | **[removeLast](QList.md#void-qlistremovelast)**() |
| bool                          | **[removeOne](QList.md#bool-qlistremoveoneconst-t-value)**(const T &*value*) |
| QList::reverse_iterator       | **[rend](QList.md#qlistreverseiterator-qlistrend)**()         |
| QList::const_reverse_iterator | **[rend](QList.md#qlistconstreverseiterator-qlistrend-const)**() const |
| void                          | **[replace](QList.md#void-qlistreplaceint-i-const-t-value)**(int *i*, const T &*value*) |
| void                          | **[reserve](QList.md#void-qlistreserveint-alloc)**(int *alloc*) |
| int                           | **[size](QList.md#int-qlistsize-const)**() const   |
| bool                          | **[startsWith](QList.md#bool-qliststartswithconst-t-value-const)**(const T &*value*) const |
| void                          | **[swap](QList.md#void-qlistswapqlistt-other)**(QList<T> &*other*) |
| void                          | **[swapItemsAt](QList.md#void-qlistswapitemsatint-i-int-j)**(int *i*, int *j*) |
| T                             | **[takeAt](QList.md#t-qlisttakeatint-i)**(int *i*) |
| T                             | **[takeFirst](QList.md#t-qlisttakefirst)**() |
| T                             | **[takeLast](QList.md#t-qlisttakelast)**() |
| QSet<T>                       | **[toSet](QList.md#qsett-qlisttoset-const)**() const |
| std::list<T>                  | **[toStdList](QList.md#stdlistt-qlisttostdlist-const)**() const |
| QVector<T>                    | **[toVector](QList.md#qvectort-qlisttovector-const)**() const |
| T                             | **[value](QList.md#t-qlistvalueint-i-const)**(int *i*) const |
| T                             | **[value](QList.md#t-qlistvalueint-i-const-t-defaultvalue-const)**(int *i*, const T &*defaultValue*) const |
| bool                          | **[operator!=](QList.md#bool-qlistoperatorconst-qlistt-other-const)**(const QList<T> &*other*) const |
| QList<T>                      | **[operator+](QList.md#qlistt-qlistoperatorconst-qlistt-other-const)**(const QList<T> &*other*) const |
| QList<T> &                    | **[operator+=](QList.md#qlistt-qlistoperatorconst-qlistt-other)**(const QList<T> &*other*) |
| QList<T> &                    | **[operator+=](QList.md#qlistt-qlistoperatorconst-t-value)**(const T &*value*) |
| QList<T> &                    | **[operator<<](QList.md#qlistt-qlistoperatorconst-qlistt-other)**(const QList<T> &*other*) |
| QList<T> &                    | **[operator<<](QList.md#qlistt-qlistoperatorconst-t-value)**(const T &*value*) |
| bool                          | **[operator==](QList.md#bool-qlistoperatorconst-qlistt-other-const)**(const QList<T> &*other*) const |
| T &                           | **[operator[\]](QList.md#t-qlistoperator)**(int *i*) |
| const T &                     | **[operator[\]](QList.md#const-t-qlistoperator-const)**(int *i*) const |



## Static Public Members

| QList<T> | **[fromSet](QList.md#static-qlistt-qlistfromsetconst-qsett-set)**(const QSet<T> &*set*) |
| -------- | ------------------------------------------------------------ |
| QList<T> | **[fromStdList](QList.md#static-qlistt-qlistfromstdlistconst-stdlistt-list)**(const std::list<T> &*list*) |
| QList<T> | **[fromVector](QList.md#static-qlistt-qlistfromvectorconst-qvectort-vector)**(const QVector<T> &*vector*) |



## Related Non-Members

| uint          | **[qHash](QList.md#template-typename-t-uint-qhashconst-qlistt-key-uint-seed--0)**(const QList<T> &*key*, uint *seed* = 0) |
| ------------- | ------------------------------------------------------------ |
| bool          | **[operator<](QList.md#template-typename-t-bool-operatorconst-qlistt-lhs-const-qlistt-rhs)**(const QList<T> &*lhs*, const QList<T> &*rhs*) |
| QDataStream & | **[operator<<](QList.md#template-typename-t-qdatastream-operatorqdatastream-out-const-qlistt-list)**(QDataStream &*out*, const QList<T> &*list*) |
| bool          | **[operator<=](QList.md#template-typename-t-bool-operatorconst-qlistt-lhs-const-qlistt-rhs)**(const QList<T> &*lhs*, const QList<T> &*rhs*) |
| bool          | **[operator>](QList.md#template-typename-t-bool-operatorconst-qlistt-lhs-const-qlistt-rhs)**(const QList<T> &*lhs*, const QList<T> &*rhs*) |
| bool          | **[operator>=](QList.md#template-typename-t-bool-operatorconst-qlistt-lhs-const-qlistt-rhs)**(const QList<T> &*lhs*, const QList<T> &*rhs*) |
| QDataStream & | **[operator>>](QList.md#template-typename-t-qdatastream-operatorqdatastream-in-qlistt-list)**(QDataStream &*in*, QList<T> &*list*) |



## Detailed Description

QList<T> is one of Qt's generic [container classes](https://doc.qt.io/qt-5/containers.html). It stores items in a list that provides fast index-based access and index-based insertions and removals.

QList<T>, QLinkedList<T>, and [QVector](../../V/QVector/QVector.md)<T> provide similar APIs and functionality. They are often interchangeable, but there are performance consequences. Here is an overview of use cases:

- [QVector](../../V/QVector/QVector.md) should be your default first choice. [QVector](../../V/QVector/QVector.md)<T> will usually give better performance than QList<T>, because [QVector](../../V/QVector/QVector.md)<T> always stores its items sequentially in memory, where QList<T> will allocate its items on the heap unless `sizeof(T) <= sizeof(void*)` and T has been declared to be either a `Q_MOVABLE_TYPE` or a `Q_PRIMITIVE_TYPE` using [Q_DECLARE_TYPEINFO](https://doc.qt.io/qt-5/qtglobal.html#Q_DECLARE_TYPEINFO). See the [Pros and Cons of Using QList](http://marcmutz.wordpress.com/effective-qt/containers/#containers-qlist) for an explanation.
- However, QList is used throughout the Qt APIs for passing parameters and for returning values. Use QList to interface with those APIs.
- If you need a real linked list, which guarantees [constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity) insertions mid-list and uses iterators to items rather than indexes, use QLinkedList.

**Note:** [QVector](../../V/QVector/QVector.md) and [QVarLengthArray](../../V/QVarLengthArray/QVarLengthArray.md) both guarantee C-compatible array layout. QList does not. This might be important if your application must interface with a C API.

**Note:** Iterators into a QLinkedList and references into heap-allocating QLists remain valid as long as the referenced items remain in the container. This is not true for iterators and references into a [QVector](../../V/QVector/QVector.md) and non-heap-allocating QLists.

Internally, QList<T> is represented as an array of T if `sizeof(T) <= sizeof(void*)` and T has been declared to be either a `Q_MOVABLE_TYPE` or a `Q_PRIMITIVE_TYPE` using [Q_DECLARE_TYPEINFO](https://doc.qt.io/qt-5/qtglobal.html#Q_DECLARE_TYPEINFO). Otherwise, QList<T> is represented as an array of T* and the items are allocated on the heap.

The array representation allows very fast insertions and index-based access. The [prepend](QList.md#void-qlistprependconst-t-value)() and [append](QList.md#void-qlistappendconst-t-value)() operations are also very fast because QList preallocates memory at both ends of its internal array. (See [Algorithmic Complexity](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity) for details.

Note, however, that when the conditions specified above are not met, each append or insert of a new item requires allocating the new item on the heap, and this per item allocation will make [QVector](../../V/QVector/QVector.md) a better choice for use cases that do a lot of appending or inserting, because [QVector](../../V/QVector/QVector.md) can allocate memory for many items in a single heap allocation.

Note that the internal array only ever gets bigger over the life of the list. It never shrinks. The internal array is deallocated by the destructor and by the assignment operator, when one list is assigned to another.

Here's an example of a QList that stores integers and a QList that stores [QDate](../../D/QDate/QDate.md) values:

```
QList<int> integerList;
QList<QDate> dateList;
```

Qt includes a [QStringList](../../S/QStringList/QStringList.md) class that inherits QList<[QString](../../S/QString/QString.md)> and adds a few convenience functions, such as [QStringList::join](../../S/QStringList/QStringList.md#qstring-qstringlistjoinconst-qstring-separator-const)() and [QStringList::filter](../../S/QStringList/QStringList.md#qstringlist-qstringlistfilterconst-qstring-str-qtcasesensitivity-cs--qtcasesensitive-const)(). [QString::split](../../S/QString/QString.md#qstringlist-qstringsplitconst-qstring-sep-qtsplitbehavior-behavior--qtkeepemptyparts-qtcasesensitivity-cs--qtcasesensitive-const)() creates QStringLists from strings.

QList stores a list of items. The default constructor creates an empty list. You can use the initializer-list constructor to create a list with elements:

```
QList<QString> list = { "one", "two", "three" };
```

QList provides these basic functions to add, move, and remove items: [insert](QList.md#void-qlistinsertint-i-const-t-value)(), [replace](QList.md#void-qlistreplaceint-i-const-t-value)(), [removeAt](QList.md#void-qlistremoveatint-i)(), [move](QList.md#void-qlistmoveint-from-int-to)(), and [swap](QList.md#void-qlistswapqlistt-other)(). In addition, it provides the following convenience functions: [append](QList.md#void-qlistappendconst-t-value)(), [operator<<](QList.md#qlistt-qlistoperatorconst-qlistt-other)(), [operator+=](QList.md#qlistt-qlistoperatorconst-qlistt-other)(), [prepend](QList.md#void-qlistprependconst-t-value)(), [removeFirst](QList.md#void-qlistremovefirst)(), and [removeLast](QList.md#void-qlistremovelast)().

[operator<<](QList.md#qlistt-qlistoperatorconst-qlistt-other)() allows to conveniently add multiple elements to a list:

```
list << "four" << "five";
```

QList uses 0-based indexes, just like C++ arrays. To access the item at a particular index position, you can use operator[](). On non-const lists, operator[]() returns a reference to the item and can be used on the left side of an assignment:

```
if (list[0] == "Bob")
    list[0] = "Robert";
```

Because QList is implemented as an array of pointers for types that are larger than a pointer or are not movable, this operation requires ([constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity)). For read-only access, an alternative syntax is to use [at](QList.md#const-t-qlistatint-i-const)():

```
for (int i = 0; i < list.size(); ++i) {
    if (list.at(i) == "Jane")
        cout << "Found Jane at position " << i << Qt::endl;
}
```

[at](QList.md#const-t-qlistatint-i-const)() can be faster than operator[](), because it never causes a [deep copy](https://doc.qt.io/qt-5/implicit-sharing.html#deep-copy) to occur.

A common requirement is to remove an item from a list and do something with it. For this, QList provides [takeAt](QList.md#t-qlisttakeatint-i)(), [takeFirst](QList.md#t-qlisttakefirst)(), and [takeLast](QList.md#t-qlisttakelast)(). Here's a loop that removes the items from a list one at a time and calls `delete` on them:

```
QList<QWidget *> list;
...
while (!list.isEmpty())
    delete list.takeFirst();
```

Inserting and removing items at either end of the list is very fast ([constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity) in most cases), because QList preallocates extra space on both sides of its internal buffer to allow for fast growth at both ends of the list.

If you want to find all occurrences of a particular value in a list, use [indexOf](QList.md#int-qlistindexofconst-t-value-int-from--0-const)() or [lastIndexOf](QList.md#int-qlistlastindexofconst-t-value-int-from--1-const)(). The former searches forward starting from a given index position, the latter searches backward. Both return the index of a matching item if they find it; otherwise, they return -1. For example:

```
int i = list.indexOf("Jane");
if (i != -1)
    cout << "First occurrence of Jane is at position " << i << Qt::endl;
```

If you simply want to check whether a list contains a particular value, use [contains](QList.md#bool-qlistcontainsconst-t-value-const)(). If you want to find out how many times a particular value occurs in the list, use [count](QList.md#int-qlistcount-const)(). If you want to replace all occurrences of a particular value with another, use [replace](QList.md#void-qlistreplaceint-i-const-t-value)().

QList's value type must be an [assignable data type](https://doc.qt.io/qt-5/containers.html#assignable-data-type). This covers most data types that are commonly used, but the compiler won't let you, for example, store a [QWidget](../../W/QWidget/QWidget.md) as a value; instead, store a [QWidget](../../W/QWidget/QWidget.md) *. A few functions have additional requirements; for example, [indexOf](QList.md#int-qlistindexofconst-t-value-int-from--0-const)() and [lastIndexOf](QList.md#int-qlistlastindexofconst-t-value-int-from--1-const)() expect the value type to support `operator==()`. These requirements are documented on a per-function basis.

Like the other container classes, QList provides [Java-style iterators](https://doc.qt.io/qt-5/containers.html#java-style-iterators) ([QListIterator](../../L/QListIterator/QListIterator.md) and [QMutableListIterator](../../M/QMutableListIterator/QMutableListIterator.md)) and [STL-style iterators](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) ([QList::const_iterator](https://doc.qt.io/qt-5/qlist-const-iterator.html) and [QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html)). In practice, these are rarely used, because you can use indexes into the QList. QList is implemented in such a way that direct index-based access is just as fast as using iterators.

QList does *not* support inserting, prepending, appending or replacing with references to its own values. Doing so will cause your application to abort with an error message.

To make QList as efficient as possible, its member functions don't validate their input before using it. Except for [isEmpty](QList.md#bool-qlistisempty-const)(), member functions always assume the list is *not* empty. Member functions that take index values as parameters always assume their index value parameters are in the valid range. This means QList member functions can fail. If you define QT_NO_DEBUG when you compile, failures will not be detected. If you *don't* define QT_NO_DEBUG, failures will be detected using [Q_ASSERT](https://doc.qt.io/qt-5/qtglobal.html#Q_ASSERT)() or [Q_ASSERT_X](https://doc.qt.io/qt-5/qtglobal.html#Q_ASSERT_X)() with an appropriate message.

To avoid failures when your list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling other member functions. If you must pass an index value that might not be in the valid range, check that it is less than the value returned by [size](QList.md#int-qlistsize-const)() but *not* less than 0.



### More Members

If T is a [QByteArray](../../B/QByteArray/QByteArray.md), this class has a couple more members that can be used. See the documentation for [QByteArrayList](../../B/QByteArrayList/QByteArrayList.md) for more information.

If T is [QString](../../S/QString/QString.md), this class has the following additional members: [filter](../../S/QStringList/QStringList.md#qstringlist-qstringlistfilterconst-qstring-str-qtcasesensitivity-cs--qtcasesensitive-const), [join](../../S/QStringList/QStringList.md#qstring-qstringlistjoinconst-qstring-separator-const), [removeDuplicates](../../S/QStringList/QStringList.md#int-qstringlistremoveduplicates), [sort](../../S/QStringList/QStringList.md#void-qstringlistsortqtcasesensitivity-cs--qtcasesensitive).



### More Information on Using Qt Containers

For a detailed discussion comparing Qt containers with each other and with STL containers, see [Understand the Qt Containers](http://marcmutz.wordpress.com/effective-qt/containers/).

**See also** [QListIterator](../../L/QListIterator/QListIterator.md), [QMutableListIterator](../../M/QMutableListIterator/QMutableListIterator.md), [QLinkedList](../../L/QLinkedList/QLinkedList.md), and [QVector](../../V/QVector/QVector.md).

## Member Type Documentation

### typedef QList::ConstIterator

Qt-style synonym for [QList::const_iterator](https://doc.qt.io/qt-5/qlist-const-iterator.html).

### typedef QList::Iterator

Qt-style synonym for [QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html).

### typedef QList::const_pointer

Typedef for const T *. Provided for STL compatibility.

### typedef QList::const_reference

Typedef for const T &. Provided for STL compatibility.

### typedef QList::const_reverse_iterator

The QList::const_reverse_iterator typedef provides an STL-style const reverse iterator for [QList](../../L/QList/QList.md).

It is simply a typedef for `std::reverse_iterator<const_iterator>`.

**Warning:** Iterators on implicitly shared containers do not work exactly like STL-iterators. You should avoid copying a container while iterators are active on that container. For more information, read [Implicit sharing iterator problem](https://doc.qt.io/qt-5/containers.html#implicit-sharing-iterator-problem).

This typedef was introduced in Qt 5.6.

**See also** [QList::rbegin](QList.md#qlistreverseiterator-qlistrbegin)(), [QList::rend](QList.md#qlistreverseiterator-qlistrend)(), [QList::reverse_iterator](QList.md#typedef-qlistreverseiterator), and [QList::const_iterator](https://doc.qt.io/qt-5/qlist-const-iterator.html).

### typedef QList::difference_type

Typedef for ptrdiff_t. Provided for STL compatibility.

### typedef QList::pointer

Typedef for T *. Provided for STL compatibility.

### typedef QList::reference

Typedef for T &. Provided for STL compatibility.

### typedef QList::reverse_iterator

The QList::reverse_iterator typedef provides an STL-style non-const reverse iterator for [QList](../../L/QList/QList.md).

It is simply a typedef for `std::reverse_iterator<iterator>`.

**Warning:** Iterators on implicitly shared containers do not work exactly like STL-iterators. You should avoid copying a container while iterators are active on that container. For more information, read [Implicit sharing iterator problem](https://doc.qt.io/qt-5/containers.html#implicit-sharing-iterator-problem).

This typedef was introduced in Qt 5.6.

**See also** [QList::rbegin](QList.md#qlistreverseiterator-qlistrbegin)(), [QList::rend](QList.md#qlistreverseiterator-qlistrend)(), [QList::const_reverse_iterator](QList.md#typedef-qlistconstreverseiterator), and [QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html).

### typedef QList::size_type

Typedef for int. Provided for STL compatibility.

### typedef QList::value_type

Typedef for T. Provided for STL compatibility.

## Member Function Documentation

### template <typename InputIterator> QList::QList(InputIterator *first*, InputIterator *last*)

Constructs a QList with the contents in the iterator range [*first*, *last*).

The value type of `InputIterator` must be convertible to `T`.

This function was introduced in Qt 5.14.

### QList::QList(std::initializer_list<T> *args*)

Construct a list from the std::initializer_list specified by *args*.

This constructor is only enabled if the compiler supports C++11 initializer lists.

This function was introduced in Qt 4.8.

### QList::QList([QList](QList.md#qlistqlist)<T> &&*other*)

Move-constructs a QList instance, making it point at the same object that *other* was pointing to.

This function was introduced in Qt 5.2.

### QList::QList(const [QList](QList.md#qlistqlist)<T> &*other*)

Constructs a copy of *other*.

This operation takes [constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity), because QList is [implicitly shared](https://doc.qt.io/qt-5/implicit-sharing.html). This makes returning a QList from a function very fast. If a shared instance is modified, it will be copied (copy-on-write), and that takes [linear time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity).

**See also** [operator=](QList.md#qlistt-qlistoperatorconst-qlistt-other)().

### QList::QList()

Constructs an empty list.

### [QList](QList.md#qlistqlist)<T> &QList::operator=([QList](QList.md#qlistqlist)<T> &&*other*)

Move-assigns *other* to this [QList](../../L/QList/QList.md) instance.

This function was introduced in Qt 5.2.

### [QList](QList.md#qlistqlist)<T> &QList::operator=(const [QList](QList.md#qlistqlist)<T> &*other*)

Assigns *other* to this list and returns a reference to this list.

### QList::~QList()

Destroys the list. References to the values in the list and all iterators of this list become invalid.

### void QList::append(const T &*value*)

Inserts *value* at the end of the list.

Example:

```
QList<QString> list;
list.append("one");
list.append("two");
list.append("three");
// list: ["one", "two", "three"]
```

This is the same as list.insert([size](QList.md#int-qlistsize-const)(), *value*).

If this list is not shared, this operation is typically very fast (amortized [constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity)), because [QList](../../L/QList/QList.md) preallocates extra space on both sides of its internal buffer to allow for fast growth at both ends of the list.

**See also** [operator<<](QList.md#qlistt-qlistoperatorconst-qlistt-other)(), [prepend](QList.md#void-qlistprependconst-t-value)(), and [insert](QList.md#void-qlistinsertint-i-const-t-value)().

### void QList::append(const [QList](QList.md#qlistqlist)<T> &*value*)

This is an overloaded function.

Appends the items of the *value* list to this list.

This function was introduced in Qt 4.5.

**See also** [operator<<](QList.md#qlistt-qlistoperatorconst-qlistt-other)() and [operator+=](QList.md#qlistt-qlistoperatorconst-qlistt-other)().

### const T &QList::at(int *i*) const

Returns the item at index position *i* in the list. *i* must be a valid index position in the list (i.e., 0 <= *i* < [size](QList.md#int-qlistsize-const)()).

This function is very fast ([constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity)).

**See also** [value](QList.md#t-qlistvalueint-i-const)() and [operator[\]](QList.md#t-qlistoperator)().

### T &QList::back()

This function is provided for STL compatibility. It is equivalent to [last](QList.md#t-qlistlast)(). The list must not be empty. If the list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

### const T &QList::back() const

This is an overloaded function.

### [QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html) QList::begin()

Returns an [STL-style iterator](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) pointing to the first item in the list.

**See also** [constBegin](QList.md#qlistconstiterator-qlistconstbegin-const)() and [end](QList.md#qlistiterator-qlistend)().

### [QList::const_iterator](https://doc.qt.io/qt-5/qlist-const-iterator.html) QList::begin() const

This is an overloaded function.

### [QList::const_iterator](https://doc.qt.io/qt-5/qlist-const-iterator.html) QList::cbegin() const

Returns a const [STL-style iterator](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) pointing to the first item in the list.

This function was introduced in Qt 5.0.

**See also** [begin](QList.md#qlistiterator-qlistbegin)() and [cend](QList.md#qlistconstiterator-qlistcend-const)().

### [QList::const_iterator](https://doc.qt.io/qt-5/qlist-const-iterator.html) QList::cend() const

Returns a const [STL-style iterator](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) pointing to the imaginary item after the last item in the list.

This function was introduced in Qt 5.0.

**See also** [cbegin](QList.md#qlistconstiterator-qlistcbegin-const)() and [end](QList.md#qlistiterator-qlistend)().

### void QList::clear()

Removes all items from the list.

**See also** [removeAll](QList.md#int-qlistremoveallconst-t-value)().

### [QList::const_iterator](https://doc.qt.io/qt-5/qlist-const-iterator.html) QList::constBegin() const

Returns a const [STL-style iterator](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) pointing to the first item in the list.

**See also** [begin](QList.md#qlistiterator-qlistbegin)() and [constEnd](QList.md#qlistconstiterator-qlistconstend-const)().

### [QList::const_iterator](https://doc.qt.io/qt-5/qlist-const-iterator.html) QList::constEnd() const

Returns a const [STL-style iterator](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) pointing to the imaginary item after the last item in the list.

**See also** [constBegin](QList.md#qlistconstiterator-qlistconstbegin-const)() and [end](QList.md#qlistiterator-qlistend)().

### const T &QList::constFirst() const

Returns a const reference to the first item in the list. The list must not be empty. If the list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

This function was introduced in Qt 5.6.

**See also** [constLast](QList.md#const-t-qlistconstlast-const)(), [isEmpty](QList.md#bool-qlistisempty-const)(), and [first](QList.md#t-qlistfirst)().

### const T &QList::constLast() const

Returns a reference to the last item in the list. The list must not be empty. If the list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

This function was introduced in Qt 5.6.

**See also** [constFirst](QList.md#const-t-qlistconstfirst-const)(), [isEmpty](QList.md#bool-qlistisempty-const)(), and [last](QList.md#t-qlistlast)().

### bool QList::contains(const T &*value*) const

Returns `true` if the list contains an occurrence of *value*; otherwise returns `false`.

This function requires the value type to have an implementation of `operator==()`.

**See also** [indexOf](QList.md#int-qlistindexofconst-t-value-int-from--0-const)() and [count](QList.md#int-qlistcount-const)().

### int QList::count(const T &*value*) const

Returns the number of occurrences of *value* in the list.

This function requires the value type to have an implementation of `operator==()`.

**See also** [contains](QList.md#bool-qlistcontainsconst-t-value-const)() and [indexOf](QList.md#int-qlistindexofconst-t-value-int-from--0-const)().

### int QList::count() const

Returns the number of items in the list. This is effectively the same as [size](QList.md#int-qlistsize-const)().

### [QList::const_reverse_iterator](QList.md#typedef-qlistconstreverseiterator) QList::crbegin() const

Returns a const [STL-style](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) reverse iterator pointing to the first item in the list, in reverse order.

This function was introduced in Qt 5.6.

**See also** [begin](QList.md#qlistiterator-qlistbegin)(), [rbegin](QList.md#qlistreverseiterator-qlistrbegin)(), and [rend](QList.md#qlistreverseiterator-qlistrend)().

### [QList::const_reverse_iterator](QList.md#typedef-qlistconstreverseiterator) QList::crend() const

Returns a const [STL-style](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) reverse iterator pointing to one past the last item in the list, in reverse order.

This function was introduced in Qt 5.6.

**See also** [end](QList.md#qlistiterator-qlistend)(), [rend](QList.md#qlistreverseiterator-qlistrend)(), and [rbegin](QList.md#qlistreverseiterator-qlistrbegin)().

### bool QList::empty() const

This function is provided for STL compatibility. It is equivalent to [isEmpty](QList.md#bool-qlistisempty-const)() and returns `true` if the list is empty.

### [QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html) QList::end()

Returns an [STL-style iterator](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) pointing to the imaginary item after the last item in the list.

**See also** [begin](QList.md#qlistiterator-qlistbegin)() and [constEnd](QList.md#qlistconstiterator-qlistconstend-const)().

### [QList::const_iterator](https://doc.qt.io/qt-5/qlist-const-iterator.html) QList::end() const

This is an overloaded function.

### bool QList::endsWith(const T &*value*) const

Returns `true` if this list is not empty and its last item is equal to *value*; otherwise returns `false`.

This function was introduced in Qt 4.5.

**See also** [isEmpty](QList.md#bool-qlistisempty-const)() and [contains](QList.md#bool-qlistcontainsconst-t-value-const)().

### [QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html) QList::erase([QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html) *pos*)

Removes the item associated with the iterator *pos* from the list, and returns an iterator to the next item in the list (which may be [end](QList.md#qlistiterator-qlistend)()).

**See also** [insert](QList.md#void-qlistinsertint-i-const-t-value)() and [removeAt](QList.md#void-qlistremoveatint-i)().

### [QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html) QList::erase([QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html) *begin*, [QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html) *end*)

This is an overloaded function.

Removes all the items from *begin* up to (but not including) *end*. Returns an iterator to the same item that *end* referred to before the call.

### T &QList::first()

Returns a reference to the first item in the list. The list must not be empty. If the list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

**See also** [constFirst](QList.md#const-t-qlistconstfirst-const)(), [last](QList.md#t-qlistlast)(), and [isEmpty](QList.md#bool-qlistisempty-const)().

### const T &QList::first() const

This is an overloaded function.

### `[static]`[QList](QList.md#qlistqlist)<T> QList::fromSet(const [QSet](../../S/QSet/QSet.md)<T> &*set*)

Returns a [QList](../../L/QList/QList.md) object with the data contained in *set*. The order of the elements in the [QList](../../L/QList/QList.md) is undefined.

Example:

```
QSet<int> set;
set << 20 << 30 << 40 << ... << 70;

QList<int> list = QList<int>::fromSet(set);
std::sort(list.begin(), list.end());
```

**Note:** Since Qt 5.14, range constructors are available for Qt's generic [container classes](https://doc.qt.io/qt-5/containers.html) and should be used in place of this method.

**See also** [fromVector](QList.md#static-qlistt-qlistfromvectorconst-qvectort-vector)(), [toSet](QList.md#qsett-qlisttoset-const)(), and [QSet::toList](../../S/QSet/QSet.md#qlistt-qsettolist-const)().

### `[static]`[QList](QList.md#qlistqlist)<T> QList::fromStdList(const std::list<T> &*list*)

Returns a [QList](../../L/QList/QList.md) object with the data contained in *list*. The order of the elements in the [QList](../../L/QList/QList.md) is the same as in *list*.

Example:

```
std::list<double> stdlist;
list.push_back(1.2);
list.push_back(0.5);
list.push_back(3.14);

QList<double> list = QList<double>::fromStdList(stdlist);
```

**Note:** Since Qt 5.14, range constructors are available for Qt's generic [container classes](https://doc.qt.io/qt-5/containers.html) and should be used in place of this method.

**See also** [toStdList](QList.md#stdlistt-qlisttostdlist-const)() and [QVector::fromStdVector](../../V/QVector/QVector.md#static-qvectort-qvectorfromstdvectorconst-stdvectort-vector)().

### `[static]`[QList](QList.md#qlistqlist)<T> QList::fromVector(const [QVector](../../V/QVector/QVector.md)<T> &*vector*)

Returns a [QList](../../L/QList/QList.md) object with the data contained in *vector*.

Example:

```
QVector<double> vect;
vect << 20.0 << 30.0 << 40.0 << 50.0;

QList<double> list = QVector<T>::fromVector(vect);
// list: [20.0, 30.0, 40.0, 50.0]
```

**Note:** Since Qt 5.14, range constructors are available for Qt's generic [container classes](https://doc.qt.io/qt-5/containers.html) and should be used in place of this method.

**See also** [fromSet](QList.md#static-qlistt-qlistfromsetconst-qsett-set)(), [toVector](QList.md#qvectort-qlisttovector-const)(), and [QVector::toList](../../V/QVector/QVector.md#qlistt-qvectortolist-const)().

### T &QList::front()

This function is provided for STL compatibility. It is equivalent to [first](QList.md#t-qlistfirst)(). The list must not be empty. If the list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

### const T &QList::front() const

This is an overloaded function.

### int QList::indexOf(const T &*value*, int *from* = 0) const

Returns the index position of the first occurrence of *value* in the list, searching forward from index position *from*. Returns -1 if no item matched.

Example:

```
QList<QString> list;
list << "A" << "B" << "C" << "B" << "A";
list.indexOf("B");          // returns 1
list.indexOf("B", 1);       // returns 1
list.indexOf("B", 2);       // returns 3
list.indexOf("X");          // returns -1
```

This function requires the value type to have an implementation of `operator==()`.

Note that [QList](../../L/QList/QList.md) uses 0-based indexes, just like C++ arrays. Negative indexes are not supported with the exception of the value mentioned above.

**See also** [lastIndexOf](QList.md#int-qlistlastindexofconst-t-value-int-from--1-const)() and [contains](QList.md#bool-qlistcontainsconst-t-value-const)().

### void QList::insert(int *i*, const T &*value*)

Inserts *value* at index position *i* in the list.

If *i* == 0, the value is prepended to the list. If *i* == [size](QList.md#int-qlistsize-const)(), the value is appended to the list.

Example:

```
QList<QString> list;
list << "alpha" << "beta" << "delta";
list.insert(2, "gamma");
// list: ["alpha", "beta", "gamma", "delta"]
```

**See also** [append](QList.md#void-qlistappendconst-t-value)(), [prepend](QList.md#void-qlistprependconst-t-value)(), [replace](QList.md#void-qlistreplaceint-i-const-t-value)(), and [removeAt](QList.md#void-qlistremoveatint-i)().

### [QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html) QList::insert([QList::iterator](https://doc.qt.io/qt-5/qlist-iterator.html) *before*, const T &*value*)

This is an overloaded function.

Inserts *value* in front of the item pointed to by the iterator *before*. Returns an iterator pointing at the inserted item. Note that the iterator passed to the function will be invalid after the call; the returned iterator should be used instead.

### bool QList::isEmpty() const

Returns `true` if the list contains no items; otherwise returns false.

**See also** [size](QList.md#int-qlistsize-const)().

### T &QList::last()

Returns a reference to the last item in the list. The list must not be empty. If the list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

**See also** [constLast](QList.md#const-t-qlistconstlast-const)(), [first](QList.md#t-qlistfirst)(), and [isEmpty](QList.md#bool-qlistisempty-const)().

### const T &QList::last() const

This is an overloaded function.

### int QList::lastIndexOf(const T &*value*, int *from* = -1) const

Returns the index position of the last occurrence of *value* in the list, searching backward from index position *from*. If *from* is -1 (the default), the search starts at the last item. Returns -1 if no item matched.

Example:

```
QList<QString> list;
list << "A" << "B" << "C" << "B" << "A";
list.lastIndexOf("B");      // returns 3
list.lastIndexOf("B", 3);   // returns 3
list.lastIndexOf("B", 2);   // returns 1
list.lastIndexOf("X");      // returns -1
```

This function requires the value type to have an implementation of `operator==()`.

Note that [QList](../../L/QList/QList.md) uses 0-based indexes, just like C++ arrays. Negative indexes are not supported with the exception of the value mentioned above.

**See also** [indexOf](QList.md#int-qlistindexofconst-t-value-int-from--0-const)().

### int QList::length() const

This function is identical to [count](QList.md#int-qlistcount-const)().

This function was introduced in Qt 4.5.

**See also** [count](QList.md#int-qlistcount-const)().

### [QList](QList.md#qlistqlist)<T> QList::mid(int *pos*, int *length* = -1) const

Returns a sub-list which includes elements from this list, starting at position *pos*. If *length* is -1 (the default), all elements from *pos* are included; otherwise *length* elements (or all remaining elements if there are less than *length* elements) are included.

### void QList::move(int *from*, int *to*)

Moves the item at index position *from* to index position *to*.

Example:

```
QList<QString> list;
list << "A" << "B" << "C" << "D" << "E" << "F";
list.move(1, 4);
// list: ["A", "C", "D", "E", "B", "F"]
```

This is the same as insert(*to*, [takeAt](QList.md#t-qlisttakeatint-i)(*from*)).This function assumes that both *from* and *to* are at least 0 but less than [size](QList.md#int-qlistsize-const)(). To avoid failure, test that both *from* and *to* are at least 0 and less than [size](QList.md#int-qlistsize-const)().

**See also** [swap](QList.md#void-qlistswapqlistt-other)(), [insert](QList.md#void-qlistinsertint-i-const-t-value)(), and [takeAt](QList.md#t-qlisttakeatint-i)().

### void QList::pop_back()

This function is provided for STL compatibility. It is equivalent to [removeLast](QList.md#void-qlistremovelast)(). The list must not be empty. If the list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

### void QList::pop_front()

This function is provided for STL compatibility. It is equivalent to [removeFirst](QList.md#void-qlistremovefirst)(). The list must not be empty. If the list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

### void QList::prepend(const T &*value*)

Inserts *value* at the beginning of the list.

Example:

```
QList<QString> list;
list.prepend("one");
list.prepend("two");
list.prepend("three");
// list: ["three", "two", "one"]
```

This is the same as list.insert(0, *value*).

If this list is not shared, this operation is typically very fast (amortized [constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity)), because [QList](../../L/QList/QList.md) preallocates extra space on both sides of its internal buffer to allow for fast growth at both ends of the list.

**See also** [append](QList.md#void-qlistappendconst-t-value)() and [insert](QList.md#void-qlistinsertint-i-const-t-value)().

### void QList::push_back(const T &*value*)

This function is provided for STL compatibility. It is equivalent to [append](QList.md#void-qlistappendconst-t-value)(*value*).

### void QList::push_front(const T &*value*)

This function is provided for STL compatibility. It is equivalent to [prepend](QList.md#void-qlistprependconst-t-value)(*value*).

### [QList::reverse_iterator](QList.md#typedef-qlistreverseiterator) QList::rbegin()

Returns a [STL-style](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) reverse iterator pointing to the first item in the list, in reverse order.

This function was introduced in Qt 5.6.

**See also** [begin](QList.md#qlistiterator-qlistbegin)(), [crbegin](QList.md#qlistconstreverseiterator-qlistcrbegin-const)(), and [rend](QList.md#qlistreverseiterator-qlistrend)().

### [QList::const_reverse_iterator](QList.md#typedef-qlistconstreverseiterator) QList::rbegin() const

This is an overloaded function.

This function was introduced in Qt 5.6.

### int QList::removeAll(const T &*value*)

Removes all occurrences of *value* in the list and returns the number of entries removed.

Example:

```
QList<QString> list;
list << "sun" << "cloud" << "sun" << "rain";
list.removeAll("sun");
// list: ["cloud", "rain"]
```

This function requires the value type to have an implementation of `operator==()`.

**See also** [removeOne](QList.md#bool-qlistremoveoneconst-t-value)(), [removeAt](QList.md#void-qlistremoveatint-i)(), [takeAt](QList.md#t-qlisttakeatint-i)(), and [replace](QList.md#void-qlistreplaceint-i-const-t-value)().

### void QList::removeAt(int *i*)

Removes the item at index position *i*. *i* must be a valid index position in the list (i.e., 0 <= *i* < [size](QList.md#int-qlistsize-const)()).

**See also** [takeAt](QList.md#t-qlisttakeatint-i)(), [removeFirst](QList.md#void-qlistremovefirst)(), [removeLast](QList.md#void-qlistremovelast)(), and [removeOne](QList.md#bool-qlistremoveoneconst-t-value)().

### void QList::removeFirst()

Removes the first item in the list. Calling this function is equivalent to calling [removeAt](QList.md#void-qlistremoveatint-i)(0). The list must not be empty. If the list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

**See also** [removeAt](QList.md#void-qlistremoveatint-i)() and [takeFirst](QList.md#t-qlisttakefirst)().

### void QList::removeLast()

Removes the last item in the list. Calling this function is equivalent to calling [removeAt](QList.md#void-qlistremoveatint-i)([size](QList.md#int-qlistsize-const)() - 1). The list must not be empty. If the list can be empty, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

**See also** [removeAt](QList.md#void-qlistremoveatint-i)() and [takeLast](QList.md#t-qlisttakelast)().

### bool QList::removeOne(const T &*value*)

Removes the first occurrence of *value* in the list and returns true on success; otherwise returns `false`.

Example:

```
QList<QString> list;
list << "sun" << "cloud" << "sun" << "rain";
list.removeOne("sun");
// list: ["cloud", "sun", "rain"]
```

This function requires the value type to have an implementation of `operator==()`.

This function was introduced in Qt 4.4.

**See also** [removeAll](QList.md#int-qlistremoveallconst-t-value)(), [removeAt](QList.md#void-qlistremoveatint-i)(), [takeAt](QList.md#t-qlisttakeatint-i)(), and [replace](QList.md#void-qlistreplaceint-i-const-t-value)().

### [QList::reverse_iterator](QList.md#typedef-qlistreverseiterator) QList::rend()

Returns a [STL-style](https://doc.qt.io/qt-5/containers.html#stl-style-iterators) reverse iterator pointing to one past the last item in the list, in reverse order.

This function was introduced in Qt 5.6.

**See also** [end](QList.md#qlistiterator-qlistend)(), [crend](QList.md#qlistconstreverseiterator-qlistcrend-const)(), and [rbegin](QList.md#qlistreverseiterator-qlistrbegin)().

### [QList::const_reverse_iterator](QList.md#typedef-qlistconstreverseiterator) QList::rend() const

This is an overloaded function.

This function was introduced in Qt 5.6.

### void QList::replace(int *i*, const T &*value*)

Replaces the item at index position *i* with *value*. *i* must be a valid index position in the list (i.e., 0 <= *i* < [size](QList.md#int-qlistsize-const)()).

**See also** [operator[\]](QList.md#t-qlistoperator)() and [removeAt](QList.md#void-qlistremoveatint-i)().

### void QList::reserve(int *alloc*)

Reserve space for *alloc* elements.

If *alloc* is smaller than the current size of the list, nothing will happen.

Use this function to avoid repetetive reallocation of [QList](../../L/QList/QList.md)'s internal data if you can predict how many elements will be appended. Note that the reservation applies only to the internal pointer array.

This function was introduced in Qt 4.7.

### int QList::size() const

Returns the number of items in the list.

**See also** [isEmpty](QList.md#bool-qlistisempty-const)() and [count](QList.md#int-qlistcount-const)().

### bool QList::startsWith(const T &*value*) const

Returns `true` if this list is not empty and its first item is equal to *value*; otherwise returns `false`.

This function was introduced in Qt 4.5.

**See also** [isEmpty](QList.md#bool-qlistisempty-const)() and [contains](QList.md#bool-qlistcontainsconst-t-value-const)().

### void QList::swap([QList](QList.md#qlistqlist)<T> &*other*)

Swaps list *other* with this list. This operation is very fast and never fails.

This function was introduced in Qt 4.8.

### void QList::swapItemsAt(int *i*, int *j*)

Exchange the item at index position *i* with the item at index position *j*. This function assumes that both *i* and *j* are at least 0 but less than [size](QList.md#int-qlistsize-const)(). To avoid failure, test that both *i* and *j* are at least 0 and less than [size](QList.md#int-qlistsize-const)().

Example:

```
QList<QString> list;
list << "A" << "B" << "C" << "D" << "E" << "F";
list.swapItemsAt(1, 4);
// list: ["A", "E", "C", "D", "B", "F"]
```

This function was introduced in Qt 5.13.

**See also** [move](QList.md#void-qlistmoveint-from-int-to)().

### T QList::takeAt(int *i*)

Removes the item at index position *i* and returns it. *i* must be a valid index position in the list (i.e., 0 <= *i* < [size](QList.md#int-qlistsize-const)()).

If you don't use the return value, [removeAt](QList.md#void-qlistremoveatint-i)() is more efficient.

**See also** [removeAt](QList.md#void-qlistremoveatint-i)(), [takeFirst](QList.md#t-qlisttakefirst)(), and [takeLast](QList.md#t-qlisttakelast)().

### T QList::takeFirst()

Removes the first item in the list and returns it. This is the same as [takeAt](QList.md#t-qlisttakeatint-i)(0). This function assumes the list is not empty. To avoid failure, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

If this list is not shared, this operation takes [constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity).

If you don't use the return value, [removeFirst](QList.md#void-qlistremovefirst)() is more efficient.

**See also** [takeLast](QList.md#t-qlisttakelast)(), [takeAt](QList.md#t-qlisttakeatint-i)(), and [removeFirst](QList.md#void-qlistremovefirst)().

### T QList::takeLast()

Removes the last item in the list and returns it. This is the same as [takeAt](QList.md#t-qlisttakeatint-i)([size](QList.md#int-qlistsize-const)() - 1). This function assumes the list is not empty. To avoid failure, call [isEmpty](QList.md#bool-qlistisempty-const)() before calling this function.

If this list is not shared, this operation takes [constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity).

If you don't use the return value, [removeLast](QList.md#void-qlistremovelast)() is more efficient.

**See also** [takeFirst](QList.md#t-qlisttakefirst)(), [takeAt](QList.md#t-qlisttakeatint-i)(), and [removeLast](QList.md#void-qlistremovelast)().

### [QSet](../../S/QSet/QSet.md)<T> QList::toSet() const

Returns a [QSet](../../S/QSet/QSet.md) object with the data contained in this [QList](../../L/QList/QList.md). Since [QSet](../../S/QSet/QSet.md) doesn't allow duplicates, the resulting [QSet](../../S/QSet/QSet.md) might be smaller than the original list was.

Example:

```
QStringList list;
list << "Julia" << "Mike" << "Mike" << "Julia" << "Julia";

QSet<QString> set = list.toSet();
set.contains("Julia");  // returns true
set.contains("Mike");   // returns true
set.size();             // returns 2
```

**Note:** Since Qt 5.14, range constructors are available for Qt's generic [container classes](https://doc.qt.io/qt-5/containers.html) and should be used in place of this method.

**See also** [toVector](QList.md#qvectort-qlisttovector-const)(), [fromSet](QList.md#static-qlistt-qlistfromsetconst-qsett-set)(), and [QSet::fromList](../../S/QSet/QSet.md#static-qsett-qsetfromlistconst-qlistt-list)().

### std::list<T> QList::toStdList() const

Returns a std::list object with the data contained in this [QList](../../L/QList/QList.md). Example:

```
QList<double> list;
list << 1.2 << 0.5 << 3.14;

std::list<double> stdlist = list.toStdList();
```

**Note:** Since Qt 5.14, range constructors are available for Qt's generic [container classes](https://doc.qt.io/qt-5/containers.html) and should be used in place of this method.

**See also** [fromStdList](QList.md#static-qlistt-qlistfromstdlistconst-stdlistt-list)() and [QVector::toStdVector](../../V/QVector/QVector.md#stdvectort-qvectortostdvector-const)().

### [QVector](../../V/QVector/QVector.md)<T> QList::toVector() const

Returns a [QVector](../../V/QVector/QVector.md) object with the data contained in this [QList](../../L/QList/QList.md).

Example:

```
QStringList list;
list << "Sven" << "Kim" << "Ola";

QVector<QString> vect = list.toVector();
// vect: ["Sven", "Kim", "Ola"]
```

**Note:** Since Qt 5.14, range constructors are available for Qt's generic [container classes](https://doc.qt.io/qt-5/containers.html) and should be used in place of this method.

**See also** [toSet](QList.md#qsett-qlisttoset-const)(), [fromVector](QList.md#static-qlistt-qlistfromvectorconst-qvectort-vector)(), and [QVector::fromList](../../V/QVector/QVector.md#static-qvectort-qvectorfromlistconst-qlistt-list)().

### T QList::value(int *i*) const

Returns the value at index position *i* in the list.

If the index *i* is out of bounds, the function returns a [default-constructed value](https://doc.qt.io/qt-5/containers.html#default-constructed-value). If you are certain that the index is going to be within bounds, you can use [at](QList.md#const-t-qlistatint-i-const)() instead, which is slightly faster.

**See also** [at](QList.md#const-t-qlistatint-i-const)() and [operator[\]](QList.md#t-qlistoperator)().

### T QList::value(int *i*, const T &*defaultValue*) const

This is an overloaded function.

If the index *i* is out of bounds, the function returns *defaultValue*.

### bool QList::operator!=(const [QList](QList.md#qlistqlist)<T> &*other*) const

Returns `true` if *other* is not equal to this list; otherwise returns `false`.

Two lists are considered equal if they contain the same values in the same order.

This function requires the value type to have an implementation of `operator==()`.

**See also** [operator==](QList.md#bool-qlistoperatorconst-qlistt-other-const)().

### [QList](QList.md#qlistqlist)<T> QList::operator+(const [QList](QList.md#qlistqlist)<T> &*other*) const

Returns a list that contains all the items in this list followed by all the items in the *other* list.

**See also** [operator+=](QList.md#qlistt-qlistoperatorconst-qlistt-other)().

### [QList](QList.md#qlistqlist)<T> &QList::operator+=(const [QList](QList.md#qlistqlist)<T> &*other*)

Appends the items of the *other* list to this list and returns a reference to this list.

**See also** [operator+](QList.md#qlistt-qlistoperatorconst-qlistt-other-const)() and [append](QList.md#void-qlistappendconst-t-value)().

### [QList](QList.md#qlistqlist)<T> &QList::operator+=(const T &*value*)

This is an overloaded function.

Appends *value* to the list.

**See also** [append](QList.md#void-qlistappendconst-t-value)() and [operator<<](QList.md#qlistt-qlistoperatorconst-qlistt-other)().

### [QList](QList.md#qlistqlist)<T> &QList::operator<<(const [QList](QList.md#qlistqlist)<T> &*other*)

Appends the items of the *other* list to this list and returns a reference to this list.

**See also** [operator+=](QList.md#qlistt-qlistoperatorconst-qlistt-other)() and [append](QList.md#void-qlistappendconst-t-value)().

### [QList](QList.md#qlistqlist)<T> &QList::operator<<(const T &*value*)

This is an overloaded function.

Appends *value* to the list.

### bool QList::operator==(const [QList](QList.md#qlistqlist)<T> &*other*) const

Returns `true` if *other* is equal to this list; otherwise returns false.

Two lists are considered equal if they contain the same values in the same order.

This function requires the value type to have an implementation of `operator==()`.

**See also** [operator!=](QList.md#bool-qlistoperatorconst-qlistt-other-const)().

### T &QList::operator[](int *i*)

Returns the item at index position *i* as a modifiable reference. *i* must be a valid index position in the list (i.e., 0 <= *i* < [size](QList.md#int-qlistsize-const)()).

If this function is called on a list that is currently being shared, it will trigger a copy of all elements. Otherwise, this function runs in [constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity). If you do not want to modify the list you should use [QList::at](QList.md#const-t-qlistatint-i-const)().

**See also** [at](QList.md#const-t-qlistatint-i-const)() and [value](QList.md#t-qlistvalueint-i-const)().

### const T &QList::operator[](int *i*) const

This is an overloaded function.

Same as [at](QList.md#const-t-qlistatint-i-const)(). This function runs in [constant time](https://doc.qt.io/qt-5/containers.html#algorithmic-complexity).

## Related Non-Members

### template <typename T> [uint](https://doc.qt.io/qt-5/qtglobal.html#uint-typedef) qHash(const [QList](QList.md#qlistqlist)<T> &*key*, [uint](https://doc.qt.io/qt-5/qtglobal.html#uint-typedef) *seed* = 0)

Returns the hash value for *key*, using *seed* to seed the calculation.

This function requires qHash() to be overloaded for the value type `T`.

This function was introduced in Qt 5.6.

### template <typename T> bool operator<(const [QList](QList.md#qlistqlist)<T> &*lhs*, const [QList](QList.md#qlistqlist)<T> &*rhs*)

Returns `true` if list *lhs* is [lexicographically less than](http://en.cppreference.com/w/cpp/algorithm/lexicographical_compare) *rhs*; otherwise returns `false`.

This function requires the value type to have an implementation of `operator<()`.

This function was introduced in Qt 5.6.

### template <typename T> [QDataStream](../../D/QDataStream/QDataStream.md) &operator<<([QDataStream](../../D/QDataStream/QDataStream.md) &*out*, const [QList](QList.md#qlistqlist)<T> &*list*)

Writes the list *list* to stream *out*.

This function requires the value type to implement `operator<<()`.

**See also** [Format of the QDataStream operators](https://doc.qt.io/qt-5/datastreamformat.html).

### template <typename T> bool operator<=(const [QList](QList.md#qlistqlist)<T> &*lhs*, const [QList](QList.md#qlistqlist)<T> &*rhs*)

Returns `true` if list *lhs* is [lexicographically less than or equal to](http://en.cppreference.com/w/cpp/algorithm/lexicographical_compare) *rhs*; otherwise returns `false`.

This function requires the value type to have an implementation of `operator<()`.

This function was introduced in Qt 5.6.

### template <typename T> bool operator>(const [QList](QList.md#qlistqlist)<T> &*lhs*, const [QList](QList.md#qlistqlist)<T> &*rhs*)

Returns `true` if list *lhs* is [lexicographically greater than](http://en.cppreference.com/w/cpp/algorithm/lexicographical_compare) *rhs*; otherwise returns `false`.

This function requires the value type to have an implementation of `operator<()`.

This function was introduced in Qt 5.6.

### template <typename T> bool operator>=(const [QList](QList.md#qlistqlist)<T> &*lhs*, const [QList](QList.md#qlistqlist)<T> &*rhs*)

Returns `true` if list *lhs* is [lexicographically greater than or equal to](http://en.cppreference.com/w/cpp/algorithm/lexicographical_compare) *rhs*; otherwise returns `false`.

This function requires the value type to have an implementation of `operator<()`.

This function was introduced in Qt 5.6.

### template <typename T> [QDataStream](../../D/QDataStream/QDataStream.md) &operator>>([QDataStream](../../D/QDataStream/QDataStream.md) &*in*, [QList](QList.md#qlistqlist)<T> &*list*)

Reads a list from stream *in* into *list*.

This function requires the value type to implement `operator>>()`.

**See also** [Format of the QDataStream operators](https://doc.qt.io/qt-5/datastreamformat.html).