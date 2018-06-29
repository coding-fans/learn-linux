.. 文件打包
    FileName:   file-baling.rst
    Author:     Fasion Chan
    Created:    2018-05-11 16:33:14
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
        文件打包有多种不同的方式(格式)，下面我们一一介绍：
        tar是Unix系统上的打包工具，可以将多个文件合并成一个文件，扩展名为.tar。
        该命令最初的设计目的是将文件备份到磁带上(tape archive)，故而得名tar。
        tar -cf dmi-python.tar dmi-python
        其中，-c参数表示创建文件包(文件归档)；-f指定目标文件名；dmi-python是待打包目录。
    :keywords: tar, tar文件打包, file-baling

========
文件打包
========

文件打包，顾名思义就是将多个文件或者目录合并一个文件包。

这个操作很常见，我们在 `Windows` 下应该都操作过：右键 -> 发送到 -> 压缩文件夹。
那么，在 `Linux` 下，如何操作呢？

文件打包有多种不同的方式(格式)，下面我们一一介绍：

tar
===

`tar` 是 `Unix` 系统上的打包工具，可以将多个文件合并成一个文件，扩展名为 ``.tar`` 。
该命令最初的设计目的是将文件备份到磁带上( ``tape archive`` )，故而得名 `tar` 。

为了节省存储空间，通常会对目标文件做进一步的压缩：

.. figure:: /_images/common-operation/file-baling/884da110489b727de6a80e90f28eaa7e.png
    :width: 512px

准确讲，文件 **打包** 和 **压缩** 是两个不同的操作。
然而现实是，这两个不同的动词经常混用。
反正大家都能理解，也就无伤大雅。

打包
----

先来看看如何打包。

进入 ``resources`` 目录，里面有一份开源项目代码 ``dmi-python`` 。
我们使用 `tar` 命令对其进行打包：

.. code-block:: shell-session

    $ cd resources
    $ tar -cf dmi-python.tar dmi-python

其中， ``-c`` 参数表示创建文件包(文件归档)； ``-f`` 指定目标文件名； ``dmi-python`` 是待打包目录。
命令执行完毕后，得到文件包 ``dmi-python.tar`` ，包含 ``dmi-python`` 目录下的所有子目录和文件。

列举
----

有时，需要知道某个文件包到底包含哪些目录和文件。
``-t`` 参数可以轻松实现：

.. code-block:: shell-session

    $ tar -tf dmi-python.tar
    dmi-python/
    dmi-python/bin/
    dmi-python/README.md
    dmi-python/.gitignore
    dmi-python/dmi/
    dmi-python/.git
    dmi-python/dmi/__init__.py
    dmi-python/dmi/fetcher/
    dmi-python/dmi/parser/
    dmi-python/dmi/parser/__init__.py
    dmi-python/dmi/parser/type.py
    dmi-python/dmi/parser/parser.py
    dmi-python/dmi/parser/type_parsers/
    dmi-python/dmi/parser/type_parsers/t3_chassis.py
    dmi-python/dmi/parser/type_parsers/t4_processor.py
    dmi-python/dmi/parser/type_parsers/t127_end_of_table.py
    dmi-python/dmi/parser/type_parsers/t11_oem_strings.py
    dmi-python/dmi/parser/type_parsers/__init__.py
    dmi-python/dmi/parser/type_parsers/all.py
    dmi-python/dmi/parser/type_parsers/t0_bios.py
    dmi-python/dmi/parser/type_parsers/t32_system_boot.py
    dmi-python/dmi/parser/type_parsers/t17_memory_device.py
    dmi-python/dmi/parser/type_parsers/t19_memory_array_mapped_address.py
    dmi-python/dmi/parser/type_parsers/t126_inactive.py
    dmi-python/dmi/parser/type_parsers/t16_physical_memory_array.py
    dmi-python/dmi/parser/type_parsers/t2_baseboard.py
    dmi-python/dmi/parser/type_parsers/base.py
    dmi-python/dmi/parser/type_parsers/t1_system.py
    dmi-python/dmi/fetcher/fake.py
    dmi-python/dmi/fetcher/__init__.py
    dmi-python/dmi/fetcher/windows.py
    dmi-python/dmi/fetcher/linux.py
    dmi-python/bin/print-dmi-jsonic.py
    dmi-python/bin/dmi

压缩
----

文件包可以进一步进行压缩，以降低存储空间消耗。
文件压缩是一个独立的操作，可以通过独立的压缩命令进行压缩。
以 `gzip` 为例：

.. code-block:: shell-session

    $ gzip dmi-python.tar

命令执行后，生成新文件 ``dmi-python.tar.gz`` ，并删除旧文件 ``dmi-python.tar`` 。
一般来说，压缩文件 ``.tar.gz`` 会比原文件 ``.tar`` 小若干甚至十倍。

当然了， ``tar`` 命令也支持打包压缩一条龙服务——在打包命令的基础上加上 ``-z`` 参数：

.. code-block:: shell-session

    $ tar -zcf dmi-python.tar.gz dmi-python

这个命令操作等同于以下两个独立的命令：

.. code-block:: shell-session

    $ tar -cf dmi-python.tar dmi-python
    $ gzip dmi-python.tar

注意到，压缩文件包扩展名分成两部分，后部分表明压缩方式，前部分表明原文件类型。
当然了，对于压缩文件包，扩展名可以进行精简，形成短扩展名：

.. csv-table:: 表格-1 文件包扩展名
    :header: "长扩展名", "短扩展名"

    ".tar.bz2", ".tb2, .tbz, .tbz2"
    ".tar.gz", ".tgz"
    ".tar.lz"
    ".tar.lzma", ".tlz"
    ".tar.xz", ".txz"
    ".tar.Z", ".tZ"

解包
----

从文件包还原被合并文件的过程称为解包，使用 ``-x`` 参数进行：

.. code-block:: shell-session

    $ tar -xf dmi-python.tar

对于压缩过的文件包，也是如此：

.. code-block:: shell-session

    $ tar -xf dmi-python.tar.gz

对于一些比较老旧的系统，你可能需要分成两步进行操作——先解压缩，再解包：

.. code-block:: shell-session

    $ gunzip dmi-python.tar.gz
    $ tar -xf dmi-python.tar

rar
===

`RAR` 是另一种文件归档压缩格式， 在 `Windows` 平台上较为多见。
`Linux` 管理员也需要学习 `RAR` 基本操作，以备不时之需。

安装
----

`Linux` 系统一般没有 `rar` 命名，需要通过包管理工具进行安装，安装方法因发行版而异。

`Debian` / `Ubuntu` :

.. code-block:: shell-session

    $ apt install rar

打包
----

执行 ``a`` 命令将文件或目录添加到压缩包：

.. code-block:: shell-session

    $ rar a dmi-python.rar dmi-python

列举
----

与 `tar` 命令类似， `rar` 命令也可以列举压缩包包含的目录和文件( ``l`` 命令 )：

.. code-block:: shell-session

    $ rar l dmi-python.rar

解包
----

解包一般采用 ``x`` 命令，该命令将压缩包内的目录及文件原封不动地解到当前目录：

.. code-block:: shell-session

    $ rar x dmi-python.rar

还可以用 ``e`` 命令解包，这种方式不保留目录结构，只将文件解到当前目录。
如果不同目录下存在同名文件则产生冲突，需要通过覆盖或者忽略解决：

.. code-block:: shell-session

    $ rar e dmi-python.rar

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `tar (computing) - Wikipedia <https://en.wikipedia.org/wiki/Tar_(computing)>`_
#. `RAR - ArchWiki <https://wiki.archlinux.org/index.php/RAR>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. comments
    comment something out below

    $ rar l dmi-python.rar

    RAR 5.50   Copyright (c) 1993-2017 Alexander Roshal   11 Aug 2017
    Trial version             Type 'rar -?' for help

    Archive: dmi-python.rar
    Details: RAR 5

     Attributes      Size     Date    Time   Name
    ----------- ---------  ---------- -----  ----
     -rwxr-xr-x       242  2018-05-13 09:11  dmi-python/bin/print-dmi-jsonic.py
     -rw-r--r--       485  2018-05-13 09:11  dmi-python/bin/dmi/__init__.py
     -rw-r--r--       241  2018-05-13 09:11  dmi-python/bin/dmi/fetcher/fake.py
     -rw-r--r--       429  2018-05-13 09:11  dmi-python/bin/dmi/fetcher/__init__.py
     -rw-r--r--      1175  2018-05-13 09:11  dmi-python/bin/dmi/fetcher/windows.py
     -rw-r--r--      2095  2018-05-13 09:11  dmi-python/bin/dmi/fetcher/linux.py
     ...
     drwxr-xr-x         0  2018-05-13 09:11  dmi-python/dmi
     drwxr-xr-x         0  2018-05-13 09:11  dmi-python
    ----------- ---------  ---------- -----  ----
                    48507                    60


    $ rar a dmi-python.rar dmi-python

    RAR 5.50   Copyright (c) 1993-2017 Alexander Roshal   11 Aug 2017
    Trial version             Type 'rar -?' for help

    Evaluation copy. Please register.

    Creating archive dmi-python.rar

    Adding    dmi-python/bin/print-dmi-jsonic.py                          OK
    Adding    dmi-python/bin/dmi/__init__.py                              OK
    Adding    dmi-python/bin/dmi/fetcher/fake.py                          OK
    Adding    dmi-python/bin/dmi/fetcher/__init__.py                      OK
    Adding    dmi-python/bin/dmi/fetcher/windows.py                       OK
    ...
    Adding    dmi-python/bin                                              OK
    Adding    dmi-python/dmi                                              OK
    Adding    dmi-python                                                  OK
    Done
