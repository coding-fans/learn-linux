.. 文件写入
    FileName:   write.rst
    Author:     Fasion Chan
    Created:    2018-07-17 17:05:53
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: 文件写入, C语言, Linux, write, open, system call, C语言写文件

========
文件写入
========

通过 :doc:`read` 一节，相信读者已经掌握了通过 :doc:`/system-programming/syscall/index` 读取文件内容的方法。
本节，我们将更近一步，学习如何将数据写入文件。

同样，我们还是通过实现一个简单的写文件程序 `write` 来学习相关 :doc:`/system-programming/syscall/index` 的使用方法。
`write` 程序用法如下：

.. code-block:: shell-session

    $ ./write first_file.txt 'Hello, world!'
    Bytes written: 13

程序接收两个命令行参数—— **待写入文件路径** 以及 **写入内容** (字符串)。
程序负责打开待写入文件并写入指定内容，最后提示成功写入字节数。

程序源码 `write.c` 如下：

.. literalinclude:: /_src/system-programming/file-io/write/write.c
    :caption: write.c
    :name: system-programming/file-io/write/write.c
    :language: c
    :lines: 13-
    :linenos:

第 `9-12` 行，检查 **命令行参数** 是否符合预期。

第 `18-22` 行，调用 `open`_ 系统调用，打开待写入文件。
`open`_ 系统调用需要 `3` 个参数： **文件路径** ( `pathname` )、 **标志位** ( `flags` )以及 **模式位** ( `mode` )。

**标志位** 影响打开文件行为，例子中指定了 `3` 个标志：

- `O_WRONLY` ，表示 **只写打开**
- `O_CREAT` ，表示文件不存在时 **创建文件**
- `O_TRUNC` ，表示文件存在时 **清空文件**

**模式位** 指定创建文件权限，仅当 `O_CREAT` 指定时有效。
例子指定了 **所属用户** 对创建后的文件拥有 **读写权限** ：

- `S_IRUSR` ， **所属用户** 拥有 **读权限**
- `S_IWUSR` ， **所属用户** 拥有 **写权限**

第 `25-29` 行，调用 `write`_ 系统调用将数据写入文件。
同样， `write`_ 系统调用需要 `3` 个参数： :doc:`file-descriptor` ( `fd` )、
**数据缓冲区地址** ( `buf` ) 以及 **数据字节数** ( `count` )。
`write`_ 系统调用执行成功时，返回 **成功写入字节数** ；出错则返回 `-1` 。

接下来，我们运行 `make` 命令编译并执行 `write` 程序：

.. code-block:: shell-session

    $ make
    gcc -c -o write.o write.c
    gcc -o write write.o
    ./write first_file.txt 'Hello, world!'
    Bytes written: 13
    $ cat first_file.txt
    Hello, world!%

注意到， `make` 命令运行 `write` 程序往 `first_file.txt` 这个文件写入了一个字符串 ``Hello, world!`` ，
这个行为是在 `Makefile` 中定义的。
另外， `cat` 命令输出的内容末尾带着 ``%`` 符号，这代表没有换行符( `new line` )，即 ``\n`` 。

检查新创建文件 `first_file.txt` 的权限，确实是 **所属用户可读可写** ( `rw` )：

.. code-block:: shell-session

    $ ls -l first_file.txt
    -rw------- 1 fasion fasion 3 Jul 17 09:15 first_file.txt

接着，再次运行 `write` 往 `first_file.txt` 文件写入字符串 ``abc`` ：

.. code-block:: shell-session

    $ $ ./write first_file.txt abc
    Bytes written: 3
    $ cat first_file.txt
    abc%

再次写入时，行为与 `open`_ 系统调用的 `flags` 参数相关：
``O_TRUNC`` 表示当目标文件存在时，清空文件。
如果不使用该标志，那么文件内容应该是 ``abclo, world!`` (从头覆写)。
相反，如果使用 ``O_APPEND`` 标志，那么文件内容则是 ``Hello, world!abc`` (末尾追加)。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `open(2) - Linux manual page`_
#. `write(2) - Linux manual page`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _open(2) - Linux manual page: http://man7.org/linux/man-pages/man2/open.2.html
.. _write(2) - Linux manual page: http://man7.org/linux/man-pages/man2/write.2.html

.. _open: http://man7.org/linux/man-pages/man2/open.2.html
.. _write: http://man7.org/linux/man-pages/man2/write.2.html

.. comments
    comment something out below

