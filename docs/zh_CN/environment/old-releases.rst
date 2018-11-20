.. 旧发行版
    FileName:   old-releases.rst
    Author:     Fasion Chan
    Created:    2018-11-19 19:47:51
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
        某些场景需要使用旧版本的 Linux ，有时不太好找。
        本文以Ubuntu为例，介绍如何下载旧版本安装镜像以及解决软件源问题。
    :keywords: old linux, old linux releases, apt old releases

========
旧发行版
========

某些场景需要使用旧版本的 `Linux` ，有时不太好找。

笔者最近在做一个 `agent` 程序，以二进制程序分发，需要在尽量老的 `Linux` 系统上编译。
老系统不太好找了，只能自己建虚拟机。
花了些时间找 **镜像** 、以及解 **决软件源** 问题，谨记以防不时之需。

.. note::

    发布二进制代码， `libc` 兼容性是一个比较棘手的问题。
    如果版本不兼容，编译出来的程序便不能执行。

    `Linux` `libc` 是 **向下** 兼容的，也就是说在老系统编译的程序在新系统一定是可以运行的！
    因此，为了提供程序的适用范围，需要在比较老的系统进行编译。

Ubuntu
======

旧版本 `Ubuntu` 发行版可以在官网上找到： `Ubuntu旧发行版列表 <http://old-releases.ubuntu.com/releases/>`_ 。
截止本文撰稿时，还可以找到并下载 `Ubuntu 4.10` (这是十几年前的发行版了)。

从列表找到所需版本并下载镜像，最后 :doc:`install` 。
安装系统时，注意 **不要安装额外软件包** ！
因为默认的源配置很可能已经失效，而导致安装会失败。

`Ubuntu` 将就版本软件源维护在 ``old-releases.ubuntu.com`` ，以供下载。
如果发现 `apt` 源失效，将源配置调整到 ``old-releases.ubuntu.com`` 即可。

登录进新装系统后，编辑 `/etc/apt/sources.list` 配置文件，将所有软件源域名替换成 ``old-releases.ubuntu.com`` ：

.. code-block:: shell-session

    $ sudo sed -i -re 's/([a-z]{2}\.)?archive.ubuntu.com|security.ubuntu.com/old-releases.ubuntu.com/g' /etc/apt/sources.list

修改完毕后，运行 `apt` 命令更新配置：

.. code-block:: shell-session

    $ sudo apt-get update

- `Ubuntu旧发行版列表 <http://old-releases.ubuntu.com/releases/>`_
- 旧 `apt` 源： ``old-releases.ubuntu.com``

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/disqus.rst

.. include:: /_fragments/wechat-reward.rst

.. comments
    comment something out below
