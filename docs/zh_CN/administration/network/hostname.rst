.. 机器名管理
    FileName:   hostname.rst
    Author:     Fasion Chan
    Created:    2018-10-17 21:10:25
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: 机器名设置, hostname, 即刻生效, 永久生效, sysctl, gethostname, sethostname

==========
机器名管理
==========

hostname命令
============

`Linux` 提供了一个专门用于设置机器名的命令： `hostname`_ ，用法非常简单。

查看当前机器名：

.. code-block:: shell-session

    $ hostname
    bee

设置机器名：

.. code-block:: shell-session

    $ hostname ant

确认机器名已经修改完毕：

.. code-block:: shell-session

    $ hostname
    ant

`hostname`_ 命令其实是通过 `gethostname`_ 以及 `sethostname`_ :doc:`../../system-programming/syscall/index` 设置机器名的。
如果需要在程序中管理机器名，可以直接调用这两个 :doc:`../../system-programming/syscall/index` 。
关于系统调用用法，请查看 `man` 手册页：

.. code-block:: shell-session

    $ man 2 gethostname

`hostname`_ 命令修改机器名 **即刻生效，但重启后失效** 。

sysctl命令
==========

机器名其实是一个内核参数，因此可以用 `sysctl`_ 命令设置。查看当前机器名：

.. code-block:: shell-session

    $ sysctl kernel.hostname
    kernel.hostname = bee

设置机器名：

.. code-block:: shell-session

    $ sysctl kernel.hostname=ant
    kernel.hostname = ant

确认机器名已经修改完毕：

.. code-block:: shell-session

    $ sysctl kernel.hostname
    kernel.hostname = ant

同样，`sysctl`_ 命令修改机器名 **即刻生效，但重启后失效** 。

proc伪文件系统
==============

`Linux` 将内核参数暴露在 `proc`_ 伪文件系统，因此可以通过读写文件来操作。

查看当前机器名：

.. code-block:: shell-session

    $ cat /proc/sys/kernel/hostname
    bee

设置机器名：

.. code-block:: shell-session

    $ echo 'ant' > /proc/sys/kernel/hostname

确认机器名已经修改完毕：

.. code-block:: shell-session

    $ cat /proc/sys/kernel/hostname
    ant


同样，这种设置方式 **即刻生效，但重启后失效** 。

配置文件
========

前面介绍的三种方法都 **即刻生效，重启失效** ，因为这些方法本质都是 **修改内核参数** 。
那么，有办法做到重启不失效吗？

这就需要思考一个问题：内核参数从何而来？——答案是 **配置文件** 。
`Linux` 下，机器名一般写在配置文件里，系统启动后，从配置文件读取并设置对应的内核参数。

不同的 `Linux` 发行版，配置文件略有区别。以 `Debian` 系列为例，只需修改 `/etc/hostname` 文件即可：

.. code-block:: shell-session

    $ echo 'bee' > /etc/hostname

修改完毕后，重启机器即可永久生效：

.. code-block:: shell-session

    $ reboot

当然了，用前几种即刻生效的方法设置一下便达到目的，毕竟重启这个动作有些大。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _gethostname: https://linux.die.net/man/2/gethostname
.. _hostname: https://linux.die.net/man/1/hostname
.. _proc: https://linux.die.net/man/5/proc
.. _sethostname: https://linux.die.net/man/2/sethostname
.. _sysctl: https://linux.die.net/man/8/sysctl

.. comments
    comment something out below

    **机器名** ( `hostname` )，又译作 **主机名** ，相当于机器的名字，用以唯一区分一台机器。
    机器还有另一种名字， `DNS` 域名( `dns domain name` )，据此可通过 `DNS` 服务器解析到机器的 `IP` 地址。

    机器名经常是 `DNS` 名的一部分，举个例子：某台机器 `DNS` 名为 ``ursula.example.com`` ，机器名为 ``ursula`` 。
    ``example.com`` 则是域名，定义机器所在的域。
    因此，可以将 `DNS` 域名理解成全称，机器名则是简称。

    .. note::

        修改机器 `DNS` 域名，带上 `-f` 选项即可，不再赘述： `hostname -f ant` 。
