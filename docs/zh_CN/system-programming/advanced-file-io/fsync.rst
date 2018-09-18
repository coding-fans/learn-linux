.. 存储介质同步
    FileName:   fsync.rst
    Author:     Fasion Chan
    Created:    2018-07-18 21:08:00
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: fsync, system call

============
存储介质同步
============

内核为了提升 `IO` 性能，在内存中维护了一些 **缓冲页** ( `buffer cache pages` )，用于缓存磁盘 **数据块** ( `data blocks` )。

读取文件时，如果相关缓冲页已经存在，则直接从内存中复制数据。
这样便避免了慢速的磁盘 `IO` ，要知道内存速度一般要比外部存储快至少一个数量级！

写入文件时，则是先写到缓冲区(内存)，内核在合适的时刻将缓冲区刷到磁盘，完成持久化。
这样做好处不少：

- **合并写操作** ——将多个 `IO` 写操作合并成一个
- **优化写操作调度** ——调整 `IO` 写操作实际执行顺序

然而，有得必有失——由于写入不同步，存在 **丢数据** 的风险。
试想，你写一个文件，数据刚写入内存缓存页，内核还没来得及刷盘，机器便断电了！

应用程序调用 `write`_ 系统调用后， **内核只保证数据拷贝到内核缓冲区** 。
至于数据是否成功落盘，应用程序一无所知！

好在，通过 `fsync`_ 系统调用，应用程序也可以确保数据成功写入到磁盘中。

看看下面这个例子：

.. literalinclude:: /_src/system-programming/advanced-file-io/fsync/append.c
    :caption: append.c
    :name: system-programming/advanced-file-io/fsync/append.c
    :language: c
    :lines: 13-
    :linenos:

例子与普通的 :doc:`/system-programming/file-io/write` 区别不大，
只不过紧跟 `write`_ 系统调用之后，使用 `fsync`_ 系统调用确保数据刷到磁盘：

第 `32-36` 行，调用 `fsync` 系统调用，将数据刷到磁盘。

`fsync`_ 成功返回则意味着数据已经写入磁盘，此后，就算机器断电，数据也不会丢失。

接下来， 编译该程序：

.. code-block:: shell-session

    $ make
    gcc -c -o append.o append.c
    gcc -o append append.o

往 `lines.txt` 文件追加一行，内容为 ``first line`` ：

.. code-block:: shell-session

    $ ./append lines.txt 'first line
    > '
    Bytes appended: 11
    $ cat lines.txt
    first line

注意到，追加的行是带换行符( ``\n`` )的。

继续追加：

.. code-block:: shell-session

    $ ./append lines.txt 'another line
    > '
    Bytes appended: 13
    $ cat lines.txt
    first line
    another line
    $ ./append lines.txt 'third line
    > '
    Bytes appended: 11
    $ cat lines.txt
    first line
    another line
    third line

加上 `fsync`_ 系统调用之后，只要 `append` 命令运行成功，数据 **一定落到磁盘** 。

如果不带 `fsync`_ 系统调用，就算命令成功退出，也不能保证数据成功写入磁盘。
内核会在合适的时间内同步数据，最终还是成功落盘。
尽管如此，在系统异常的情况下，存在 **丢失数据** 的可能性。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `fsync(2) - Linux manual page <http://man7.org/linux/man-pages/man2/fsync.2.html>`_
#. `open(2) - Linux manual page <http://man7.org/linux/man-pages/man2/open.2.html>`_
#. `write(2) - Linux manual page <http://man7.org/linux/man-pages/man2/write.2.html>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _fsync: http://man7.org/linux/man-pages/man2/fsync.2.html
.. _write: http://man7.org/linux/man-pages/man2/write.2.html

.. comments
    comment something out below

