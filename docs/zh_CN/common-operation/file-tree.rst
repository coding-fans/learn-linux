.. 文件目录树
    FileName:   file-tree.rst
    Author:     Fasion Chan
    Created:    2018-05-13 16:59:13
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
        在Linux终端中，有办法显示文件目录树吗？
        答案是肯定的——tree命令就可以完美地做到这一点：
        如果系统未安装tree命令，需要先通过包管理工具进行安装。
        sudo apt install tree
    :keywords: tree, file tree, 文件树, tree命令, 目录树, 文件目录树

==========
文件目录树
==========

文件系统通过目录可以组织成比较复杂的树形结构。

通过文件树，用户可以快速了解某个目录的基本结构。
不少图形软件(如 ``IDE`` )，提供了文件目录树的功能，使用非常方便。

那么，在 `Linux` 终端中，有办法显示文件目录树吗？

答案是肯定的—— `tree` 命令就可以完美地做到这一点：

tree
====

如果系统未安装 `tree` 命令，需要先通过包管理工具进行安装。
以 Ubuntu 为例：

.. code-block:: shell-session

    $ sudo apt install tree

我们在代码仓库中内置了一个开源项目代码用于演示，位于 ``resources/dmi-python`` 。

接下来，进入该目录并运行 `tree` 命令显示目录树：

.. code-block:: shell-session

    $ cd resources/dmi-python
    $ tree
    .
    ├── README.md
    ├── bin
    │   ├── dmi -> ../dmi
    │   └── print-dmi-jsonic.py
    └── dmi
        ├── __init__.py
        ├── fetcher
        │   ├── __init__.py
        │   ├── fake.py
        │   ├── linux.py
        │   └── windows.py
        └── parser
            ├── __init__.py
            ├── parser.py
            ├── type.py
            └── type_parsers
                ├── __init__.py
                ├── all.py
                ├── base.py
                ├── t0_bios.py
                ├── t11_oem_strings.py
                ├── t126_inactive.py
                ├── t127_end_of_table.py
                ├── t16_physical_memory_array.py
                ├── t17_memory_device.py
                ├── t19_memory_array_mapped_address.py
                ├── t1_system.py
                ├── t2_baseboard.py
                ├── t32_system_boot.py
                ├── t3_chassis.py
                └── t4_processor.py

这样，整个项目的代码结构就清晰呈现在眼前了！

`tree` 命令显示中文目录或文件名会有乱码：

.. code-block:: shell-session

    $ tree
    .
    ├── Blog
    ├── Linux
    │   ├── Linux�\200\232�\224�IO模�\236\213.md
    │   └── Linux�\226\207�\234��\204�\220\206.md
    ├── Network
    │   ├── �\221�\234�\203�\202�\215\217议�\213�\211��\220\206�\202.md
    │   └── �\232�\212��\205��\201\224�\205�系�\207\207�\233\206�\200�\217\221�\226\207档.md
    ├── Python
    │   ├── Python�\205饰�\231��\230级�\224��\225.md
    │   └── 使�\224�gdb�\203�\225Python�\213�\217.md
    └── 常�\224�.md

    4 directories, 7 files

这时只需加上 `-N` 选项即可：

.. code-block:: shell-session

    $ tree -N
    .
    ├── Blog
    ├── Linux
    │   ├── Linux通用IO模型.md
    │   └── Linux文本处理.md
    ├── Network
    │   ├── 网络七层协议之物理层.md
    │   └── 业务关联关系采集开发文档.md
    ├── Python
    │   ├── Python装饰器高级用法.md
    │   └── 使用gdb调试Python程序.md
    └── 常用.md

    4 directories, 7 files

.. note::

    根据 :doc:`/command-manual/man` 手册， *-N* 选项作用为：

    *Print non-printable characters as is instead of as escaped octal numbers.*

    意思是不对不可打印的 `ASCII` 字符进行转义。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. comments
    comment something out below

