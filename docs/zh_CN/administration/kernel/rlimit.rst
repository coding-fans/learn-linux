.. 资源限制
    FileName:   rlimit.rst
    Author:     Fasion Chan
    Created:    2019-02-12 19:30:37
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
        资源限制(resourcelimit或rlimit)，是Linux内核控制用户或进程资源占用的机制。
        rlimit可控制的系统资源包括：内存、文件、锁、CPU调度、进程数等。优秀系统管理员设置合适的rlimit值，避免某个用户或某个进程占用过多系统资源而拖垮系统。
    :keywords: ulimit, rlimit, resource limit, 资源限制, RLIMIT_NOFILE, /etc/security/limits.conf

========
资源限制
========

**资源限制** ( `resource limit` 或 `rlimit` )，是 `Linux` 内核控制 **用户** 或 **进程** 资源占用的机制。

`rlimit` 可控制的系统资源包括： **内存** 、 **文件** 、 **锁** 、 **CPU调度** 、 **进程数** 等。
优秀系统管理员设置合适的 `rlimit` 值，避免某个用户或某个进程占用过多系统资源而拖垮系统。

本文介绍设置 `rlimit` 的来龙去脉，具体 `rlimit` 值属于 **系统调优** 范畴，暂不全面涉及。

ulimit命令
==========

`ulimit` 是一个 `Shell` 内置命令，由于查看、调整当前 `Shell` 进程的 `rlimit` 值。
以 `bash`_ 为例，查看所有 `rlimit` 值：

.. code-block:: shell-session

    $ ulimit -a
    core file size          (blocks, -c) 0
    data seg size           (kbytes, -d) unlimited
    scheduling priority             (-e) 0
    file size               (blocks, -f) unlimited
    pending signals                 (-i) 3709
    max locked memory       (kbytes, -l) 16384
    max memory size         (kbytes, -m) unlimited
    open files                      (-n) 1024
    pipe size            (512 bytes, -p) 8
    POSIX message queues     (bytes, -q) 819200
    real-time priority              (-r) 0
    stack size              (kbytes, -s) 8192
    cpu time               (seconds, -t) unlimited
    max user processes              (-u) 3709
    virtual memory          (kbytes, -v) unlimited
    file locks                      (-x) unlimited

.. note::

    资源项详细介绍请参考文章末尾处附录的表格。

也可以查看某项资源的限制，以进程打开 :doc:`/system-programming/file-io/file-descriptor` 数( *RLIMIT_NOFILE* )为例：

.. code-block:: shell-session

    $ ulimit -n
    1024

由此可见，当前 `Shell` 进程最多只能打开 *1024* 个 :doc:`/system-programming/file-io/file-descriptor` ，由该 `Shell` 启动的程序也是如此。
接着实现一个简单的程序，不断创建 **套接字** ( `socket` )，以验证这一点：

.. code-block:: shell-session

    $ python detect-max-fd.py
    error no: 24
    error string: Too many open files
    fd range: [3, 1023]

显然，程序无法无限地创建 **套接字** 。
当 :doc:`/system-programming/file-io/file-descriptor` 达到 `rlimit` 限制时，
相关 :doc:`/system-programming/syscall/index` 将失败，
错误码为 `EMFILE` ，即 *Too many open files* 。
成功打开的套接字文件描述符范围从 *3* 到 *1023* ，与 *1024* 的上限相吻合。

.. note::

    进程前三个文件描述符 *0* 、 *1* 、 *2* 分别是 `stdin` 、 `stdout` 以及 `stderr` 。

当然了，可以通过 `ulimit` 调整 :doc:`/system-programming/file-io/file-descriptor` 上限：

.. code-block:: shell-session

    $ ulimit -Sn 512

.. note::

    *-S* 选项指定 **软限制** ，资源软硬限制之别请见下一小节。

这时，进程能打开的 :doc:`/system-programming/file-io/file-descriptor` 变少了：

.. code-block:: shell-session

    $ python detect-max-fd.py
    error no: 24
    error string: Too many open files
    fd range: [3, 511]

.. note::

    `detect-max-fd.py <https://github.com/fasionchan/learn-linux/src/administration/kernel/rlimit/detect-max-fd.py>`_
    源码以及原理剖析请查看文章附录，位于末尾处。

软硬之分
========

资源限制有软硬之分， **软限制** ( `soft` )和 **硬限制** ( `hard` )。

**软限制** 是一般意义的资源限制， **直接作用于用户或者进程** 。
`ulimit` 默认返回软限制：

.. code-block:: shell-session

    $ ulimit -n
    1024

也可通过 `-S` 选项显式指定返回 **软限制** ：

.. code-block:: shell-session

    $ ulimit -Sn
    1024

由上一小节，我们知道用户可以将软限制调低或调高。
如果普通用户可以无限制调高， `rlimit` 将失去限制用户的意义。
为此，内核引入了 **硬限制** ，规定了软限制调整的上限。

`ulimit` 查看 **硬限制** 需要指定 *-H* 选项：

.. code-block:: shell-session

    $ ulimit -Hn
    1048576

调整 **软限制** 时，不能超出 **硬限制** ，否则报错：

.. code-block:: shell-session

    $ ulimit -Sn 10485760
    -bash: ulimit: open files: cannot modify limit: Invalid argument

同样，可以将 **硬限制** 调低：

.. code-block:: shell-session

    $ ulimit -n 1024

.. note::

    设置 `rlimit` 限制时，未指定软硬，则同时设置。

一旦调低 **硬限制** ，便没有后悔药，无法再调高了(除非出动 *root* 用户)：

.. code-block:: shell-session

    $ ulimit -Hn 1048576
    -bash: ulimit: open files: cannot modify limit: Operation not permitted

因此，软硬限制之别可总结为以下几点：

#. **软限制** 直接起作用；
#. **软限制** 不能超出 **硬限制** ；
#. **硬限制** 只能调低；

配置文件
========

通过配置文件设置 `rlimit` 值，可永久生效，也可突破 `ulimit` 不能调高 **硬限制** 的局限。
配置文件 `limits.conf`_ 位于 `/etc/security/limits.conf` ，格式如下：

.. code-block:: text

    root    soft    nofile  1000000
    root    hard    nofile  1000000

    *       soft    nofile  1000000
    *       hard    nofile  1000000

每个配置行由 *4* 个字段组成，分别是：

- **域** ( *domain* )
- **类型** ( *type* )
- **资源项** ( *item* )
- **值** ( *value* )

其中， **域** 可以是用户或者用户组(以 *@* 开头，例如 *@admin* )， `*` 则表示任意用户；
**类型** 分为两种，分别对应 **软限制** ( `soft` )和 **硬限制** ( *hard* )；
**资源项** 列表见附录。

配置编辑完毕后，重新登录即可生效，无需重启。

.. note::

    `limits.conf`_ 是 `pam_limits.so`_ 的配置文件，
    而 `pam_limits.so`_ 是 `Linux` **插入式认证模块** ( `Pluggable Authentication Modules` 简称 `PAM` )的子模块。

    根据 `PAM` 机制，应用程序启动时，按 `/etc/pam.d` 配置加载 `pam_xxxx.so` 模块。
    `/etc/pam.d` 下包含了 `login` 、 `sshd` 、 `su` 、 `sudo` 等程序的 `PAM` 配置文件，
    因此用户重新登录时，将调用 `pam_limits.so`_ 加载 `limits.conf`_ 配置文件。

附录
====

rlimit资源项
------------

.. csv-table:: 表格-1 资源项
    :header: "项目", "ulimit选项", "含义"
    :widths: 15, 20, 65

    "as",           "-v",   "**地址空间** (虚拟内存空间)大小限制"
    "chroot",       "",     "`chroot` 目录"
    "core",         "-c",   "**核心转储文件** 大小限制"
    "cpu",          "-t",   "**CPU执行时间** 限制"
    "data",         "-d",   "**进程数据段** 大小限制"
    "fsize",        "-f",   "**文件大小** 限制"
    "locks",        "-x",   "**文件锁数量** 限制"
    "memlock",      "-l",     "**锁定内存** ( `locked-in-memory` )地址空间大小限制"
    "maxlogins",    "",     "**用户登录数** 限制"
    "maxsyslogins", "",     "**系统登录数** 限制"
    "msgqueue",     "-q",     "**消息队列内存** 限制"
    "nice",         "-e",   "nice值上限"
    "nofile",       "-n",   ":doc:`/system-programming/file-io/file-descriptor` 数量限制"
    "nproc",        "-u",   "**进程数量** 限制"
    "priority",     "",     ""
    "rss",          "-m",   "**常驻内存** ( `resident set` )大小限制"
    "rtprio",       "-r",     "**实时调度优先级**"
    "rttime",       "",     ""
    "sigpending",   "-i",   "**排队信号** ( `pending signals` )数量限制"
    "stack",        "-s",   "**进程栈大小** 限制"

detect-max-fd.py源码
--------------------

这是一个 `Python`_ 程序，循环创建套接字，促使进程打开文件描述符达到上限：

.. literalinclude:: /_src/administration/kernel/rlimit/detect-max-fd.py
    :language: python
    :linenos:
    :lines: 16-

第 *8* 行，用一个列表来存放已创建的套接字( `Python` 套接字对象)；
第 *12-13* 行，循环创建套接字并追加到列表中，直到 `OSError` 异常(系统调用出错)；
第 *15-16* 行，打印错误码；
第 *18-21* 行，打印首尾套接字的文件描述符。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `getrlimit(2) - Linux manual page <http://man7.org/linux/man-pages/man2/getrlimit.2.html>`_
#. `pam_limits(8) - Linux manual page <http://man7.org/linux/man-pages/man8/pam_limits.8.html>`_
#. `limits.conf(5) - Linux manual page <http://man7.org/linux/man-pages/man5/limits.conf.5.html>`_
#. `资源限制(RLIMIT_NOFILE)的调整细节及内部实现 <https://wweir.cc/post/%E8%B5%84%E6%BA%90%E9%99%90%E5%88%B6rlimit_nofile%E7%9A%84%E8%B0%83%E6%95%B4%E7%BB%86%E8%8A%82%E5%8F%8A%E5%86%85%E9%83%A8%E5%AE%9E%E7%8E%B0/>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _bash: http://man7.org/linux/man-pages/man1/bash.1.html
.. _getrlimit: http://man7.org/linux/man-pages/man2/getrlimit.2.html
.. _limits.conf: http://man7.org/linux/man-pages/man5/limits.conf.5.html
.. _pam_limits.so: http://man7.org/linux/man-pages/man8/pam_limits.8.html
.. _Python: https://python-book.readthedocs.io/zh_CN/latest/

.. comments
    comment something out below

