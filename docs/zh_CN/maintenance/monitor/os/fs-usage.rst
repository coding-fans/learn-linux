.. 文件系统使用量
    FileName:   fs-usage.rst
    Author:     Fasion Chan
    Created:    2018-10-22 21:04:21
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
    :keywords:

==============
文件系统使用量
==============

**磁盘空间监控** 对于 **应对存储短缺故障** 以及 **前瞻性容量规划** 意义重大。

.. note::

    磁盘空间监控这个说法其实不太准确：
    **磁盘** 只提供底层块存储，因而只有总容量的概念；
    至于当前 **使用量** 、 **剩余可用量** 等都归 **文件系统** 管理。
    因此，正如标题所示，本文采用 **文件系统使用量** 这个说法。

除了 **存储空间** 资源，管理员还需要关注 **文件节点** 资源。
对于大部分文件系统， `inode` 节点数是固定的，也就是说能存储的文件数是固定的。
因此，在文件节点耗尽的情况下，就算存储空间还有剩余也无济于事。

指标
====

**文件系统使用量** 可以通过 `statvfs`_ :doc:`/system-programming/syscall/index` 获取，指标涵盖 **存储空间** 以及 **文件节点** ：

.. csv-table:: 文件系统使用量
    :header: "指标名", "单位", "含义"

    "total_bytes", "字节", "总存储空间"
    "free_bytes", "字节", "空闲存储空间"
    "available_bytes", "字节", "可用存储空间(非特权用户)"
    "used_bytes", "字节", "已用存储空间"
    "used_bytes_percent", "百分比", "已用存储空间占比"
    "total_files", "字节", "总文件节点数( `inode` )"
    "free_files", "字节", "空闲文件节点数"
    "available_files", "字节", "可用文件节点数(非特权用户)"
    "used_files", "字节", "已用文件节点数"
    "used_files_percent", "百分比", "已用文件节点数占比"

total_bytes
-----------

`total_bytes` 表示 **总存储空间** ，单位为 **字节** ，由 `statvfs`_ 相关字段计算而来：

.. math::

    total\_bytes = statvfs.f\_frsize * statvfs.f\_blocks

`statvfs` 结构体定义如下：

.. code-block:: c

    struct statvfs {
        unsigned long  f_bsize;    /* Filesystem block size */
        unsigned long  f_frsize;   /* Fragment size */
        fsblkcnt_t     f_blocks;   /* Size of fs in f_frsize units */
        fsblkcnt_t     f_bfree;    /* Number of free blocks */
        fsblkcnt_t     f_bavail;   /* Number of free blocks for
                                      unprivileged users */
        fsfilcnt_t     f_files;    /* Number of inodes */
        fsfilcnt_t     f_ffree;    /* Number of free inodes */
        fsfilcnt_t     f_favail;   /* Number of free inodes for
                                      unprivileged users */
        unsigned long  f_fsid;     /* Filesystem ID */
        unsigned long  f_flag;     /* Mount flags */
        unsigned long  f_namemax;  /* Maximum filename length */
    };

free_bytes
----------

`free_bytes` 表示 **空闲存储空间** ，单位为 **字节** ，同样由 `statvfs`_ 相关字段计算而来：

.. math::

    free\_bytes = statvfs.f\_frsize * statvfs.f\_bfree

available_bytes
---------------

`available_bytes` 表示 **可用存储空间** ，单位为 **字节** ，同样由 `statvfs`_ 相关字段计算而来：

.. math::

    available\_bytes = statvfs.f\_frsize * statvfs.f\_bavail

.. note::

    文件系统通常为 `root` 用户预留一部分空间，其他非特权用户不能使用。
    对 `root` 用户，可用空间是 `free_bytes` ；
    对非特权用户，可用空间是 `available_bytes` 。
    一般而言， `free_bytes` 比 `available_bytes` 大：

    .. math::

        free\_bytes > available\_bytes

used_bytes
----------

`used_bytes` 表示 **已用存储空间** ，即总存储空间减去空闲存储空间：

.. math::

    used\_bytes = total\_bytes - free\_bytes

used_bytes_percent
------------------

`used_bytes_percent` 表示 **可用存储空间百分比** ，计算公式如下：

.. math::

    used\_bytes\_percent = \frac{used\_bytes}{used\_bytes + available\_bytes} \times 100\%

读者可能觉得奇怪，为什么不是除以 `total_bytes` 呢？
——因为对于非特权用户，可用存储空间是 `available_bytes` 而不是 `free_bytes` 。
对非特权用户来说，总存储空间是：

.. math::

    total\_bytes\_for\_nonroot = used\_bytes + available\_bytes

因此，已用存储空间百分比是针对非特权用户计算的， `df`_ 命令也是采用这个口径。

文件节点系列
------------

**文件节点** 系列指标与 **存储空间** 系列类似，不再赘述。计算公式列举如下：

.. math::

    total\_files = statvfs.f\_files

.. math::

    free\_files = statvfs.f\_ffree

.. math::

    available\_files = statvfs.f\_favail

.. math::

    used\_files = total\_files - free\_files

.. math::

    used\_files\_percent = \frac{used\_files}{used\_files + available\_files} \times 100\%

采集
====

借助 `statvfs`_ :doc:`/system-programming/syscall/index` ，采集某个文件系统使用量统计毫无难度。

可问题是，如何获取所有已挂载的文件系统呢？
——答案是 `proc`_ 伪文件系统，内核将所有文件系统挂载点暴露在 `/proc/mounts` 文件中。

这是一个简单的示例程序，依次展示每个文件系统使用量统计：

.. literalinclude:: /_src/maintenance/monitor/os/fs_usage/fs_usage.py
    :caption: fs_usage.py
    :name: maintenance/monitor/os/fs_usage/fs_usage.py
    :language: py
    :lines: 16-
    :linenos:

`get_mount_points` 函数读取 `/proc/mounts` 文件，从中切分出挂载点并返回。

`get_fs_usage` 函数遍历每个文件系统挂载点，调用 `statvfs`_ 获取并计算使用量统计：

#. 第 `30` 行，循环遍历每个文件系统挂载点；
#. 第 `31` 行，跳过一些非设备文件系统，如 `procfs` 伪文件系统；
#. 第 `35-38` 行配合，跳过重复挂载点；
#. 第 `41` 行，调用 `statvfs`_ 系统调用，获取文件系统统计值；
#. 第 `46-59` 行，根据上节相关公式计算所有指标；

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `df(1) - Linux manual page <http://man7.org/linux/man-pages/man1/df.1.html>`_
#. `proc(5) - Linux manual page <http://man7.org/linux/man-pages/man5/proc.5.html>`_
#. `statvfs(2) - Linux manual page <http://man7.org/linux/man-pages/man2/statvfs.2.html>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _df: http://man7.org/linux/man-pages/man1/df.1.html
.. _proc: http://man7.org/linux/man-pages/man5/proc.5.html
.. _statvfs: http://man7.org/linux/man-pages/man2/statvfs.2.html

.. comments
    comment something out below

