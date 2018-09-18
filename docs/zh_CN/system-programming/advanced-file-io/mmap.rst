.. 内存映射
    FileName:   mmap.rst
    Author:     Fasion Chan
    Created:    2018-07-18 20:21:05
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: 内存映射IO, mmap, 只读映射, 读写映射

========
内存映射
========

通过 `mmap`_ 系统调用，可以将文件映射到进程地址空间进行读写。

.. figure:: /_images/system-programming/advanced-file-io/mmap/d5ea69f80807e1989e714246c1289a8f.png
    :width: 401px

这样一来，文件读写就跟内存操作一样直观，无需繁琐的 `IO` 操作代码。
内核负责在内存和磁盘之间同步数据，应用程序开发者完全不用关心其中的细节。
此外，`IO` 系统调用的避免，或多或少提高了程序的执行效率。

接下来，我们以文件存储结构体为例，演示 `mmap` 系统调用的用法。

结构体定义如下：

.. literalinclude:: /_src/system-programming/advanced-file-io/mmap/mmio.c
    :caption: student_info
    :name: system-programming/advanced-file-io/mmap/mmio.c/student_info
    :language: c
    :lines: 21-28
    :linenos:

读写映射
========

例子代码是一个函数，将结构体写入到给定文件中，文件路径以及结构体字段均由函数参数给出：

.. literalinclude:: /_src/system-programming/advanced-file-io/mmap/mmio.c
    :caption: write_info
    :name: system-programming/advanced-file-io/mmap/mmio.c/write_info
    :language: c
    :lines: 113-164
    :linenos:

该函数先调用 `open`_ 系统调用以 **读写模式** 打开文件并清空(第 `14` 行处)，文件不存在则创建，权限位为 `644` 。

然后调用 `expand_file` 函数扩展文件长度，确保至少能容纳一个 `student_info` 结构体( 第 `25` 行处 )。
`expand_file` 设计细节不再深入讨论，
请自行查看代码：`mmio.c <https://github.com/fasionchan/learn-linux/blob/master/src/system-programming/advanced-file-io/mmap/mmio.c>`_

接着调用 `mmap`_ 系统调用将文件映射进内存中(第 `30` 行处)。 `mmap` 各个参数说明如下：

- `addr` ，内存起始地址，指定为 ``NULL`` 则由内核自行分配；
- `len` ，内存映射区区长度；
- `prot` ，内存区访问权限；
- `flags` ， **映射类型** 标志位；
- `fd` ，被映射文件描述符；
- `offset` ，被映射文件偏移量；

其中，内存区访问权限可以是以下值的或操作组合：

- ``PROT_NONE`` ，内存页 **不可访问** ；
- ``PROT_READ`` ，内存页 **可读** ；
- ``PROT_WRITE`` ，内存页 **可写** ；
- ``PROT_EXEC`` ，内存页 **可执行** ；

**映射类型** 决定内存区修改是否对其他进程可见，以及是否应用至原文件：

- ``MAP_SHARED`` ，修改对其他进程可见，并同步到文件；
- ``MAP_PRIVATE`` ，创建 **私有写复制** ( `copy-on-write` )映射，因此修改对其他进程不可见，也不同步至文件；

映射完毕后，对结构体的操作将被应用到文件(第 `44-49` 行)。

只读映射
========

只读映射与读写映射类似：

.. literalinclude:: /_src/system-programming/advanced-file-io/mmap/mmio.c
    :caption: mmio.c
    :name: system-programming/advanced-file-io/mmap/mmio.c
    :language: c
    :lines: 73-111
    :linenos:

不同的地方在于：

1. 文件可以以只读模式打开(第 `13` 行处)；
2. `mmap` 系统调用 `prot` 参数指定为 ``PROT_READ`` ；

文件映射完毕后，即可直接访问结构体字段并输出，非常直观、便捷！

程序演示
========

下面，运行 `mmio` 程序，以读写模式映射文件并写入数据记录：

.. code-block:: shell-session

    $ ./mmio fasion.data 'Fasion Chan' 28 8

注意到，当前目录确实出现了我们写入的文件：

.. code-block:: shell-session

    $ ls
    fasion.data  mmio  mmio.c

运行 `hexdump` 命令查看文件内容：

.. code-block:: shell-session

    $ hexdump -C fasion.data
    00000000  46 61 73 69 6f 6e 20 43  68 61 6e 00 00 00 00 00  |Fasion Chan.....|
    00000010  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
    00000020  1c 00 00 00 08 00 00 00                           |........|
    00000028

前两行为 `name` 字段，总共 `32` 字节，为以 `\0` 结尾的字符串；
最后一行为 `age` 以及 `score` 字段，均是 `4` 字节长整型，二进制内容表明这正是我们写入的。

接着，我们运行 `mmio` 程序，以只读模式映射文件并输出内容：

.. code-block:: shell-session

    $ ./mmio fasion.data
    Name: Fasion Chan
    Age: 28
    Score: 8

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `mmap(2) - Linux manual page <http://man7.org/linux/man-pages/man2/mmap.2.html>`_
#. `open(2) - Linux manual page <http://man7.org/linux/man-pages/man2/open.2.html>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _mmap: http://man7.org/linux/man-pages/man2/mmap.2.html
.. _open: http://man7.org/linux/man-pages/man2/open.2.html

.. comments
    comment something out below

