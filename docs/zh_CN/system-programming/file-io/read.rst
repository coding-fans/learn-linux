.. 文件读取
    FileName:   read.rst
    Author:     Fasion Chan
    Created:    2018-07-04 18:32:16
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: 文件读取, Linux, C语言, read, 系统调用, system call, read file

========
文件读取
========

本文通过一个精简版 `cat` 命令的实作，演示如何使用 `Linux` 系统调用读取文件内容。
精简版 `cat` 命令功能非常单一，但五脏俱全，足以用来演示。其用法如下：

.. code-block:: shell-session

    $ echo hello > foo
    $ ./cat foo
    hello

如上， `cat` 接受一个命令行参数——被读取文件路径，打开并读取文件，最后将文件内容输出到标准输出。
如果文件不存在， `cat` 命令提示错误并退出。

精简版 `cat` 命令源码如下：

.. literalinclude:: /_src/system-programming/file-io/cat/cat.c
    :caption: cat.c
    :name: system-programming/file-io/cat/cat.c
    :language: c
    :lines: 13-
    :linenos:

这是一个非常简短的程序，代码逻辑都在 `main` 函数里。

第 `10-14` 行处，先检查命令行参数。如果参数个数不符合预期，输出错误并退出。

第 `17-21` 行处，调用 `open` 系统调用打开文件。
`open` 系统调用返回一个 :doc:`file-descriptor` ，后续可以通过该描述符操作文件。

如果文件打开失败， `open` 将返回 `-1` ，程序需要对异常情况进行处理。
导致打开文件的原因又很多，例如：文件不存在；抑或权限不足等等。

注意到，我们以只读模式打开文件—— `flags` 参数为 `O_RDONLY` 。
`flags` 参数用于指定不同的访问模式，可以是以下三者之一：

- `O_RDONLY` ，只读模式
- `O_WRONLY` ，只写模式
- `O_RDWR` ，读写模式

更多关于 `open` 系统调用使用方法，请参考 `open(2) - Linux manual page`_ 。
这是一份唾手可得的编程文档：

.. code-block:: shell-session

    $ man 2 open

第 `24-44` 行，在一个循环内不停读取文件并写到标准输出，直到文件读完。

在调用 `read` 系统调用前，需要准备一个 **缓冲区** ，用于存储文件内容。
`read` 负责将文件内容从磁盘读取到缓冲区中，并返回成功读取字节数。

`read` 需要传入 `3` 个参数： **文件描述符** 、 **缓冲区地址** 以及 **读取字节数** (受缓冲区限制)。
`read` 返回值为零，意味着文件读取完毕，可以退出循环。

同样，更多关于 `read` 系统调用使用方法，请参考 `read(2) - Linux manual page`_ 。

第 `46` 行，在程序退出前，关闭文件描述符。
其实，这个步骤可以省略，因为程序退出时，内核会关闭其所有文件描述符。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `open(2) - Linux manual page`_
#. `read(2) - Linux manual page`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _open(2) - Linux manual page: http://man7.org/linux/man-pages/man2/open.2.html
.. _read(2) - Linux manual page: http://man7.org/linux/man-pages/man2/read.2.html

.. comments
    comment something out below

