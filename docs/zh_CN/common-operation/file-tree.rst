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

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. comments
    comment something out below

