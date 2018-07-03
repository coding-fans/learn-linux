.. 设备管理
    FileName:   device.rst
    Author:     Fasion Chan
    Created:    2018-03-23 20:56:31
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
        终端运行 ip link 命令，即可看到系统所有网卡的详细信息。
        运行 ip addr 可以查看所有网卡设置的地址。
    :keywords: Linux网络管理, Linux网卡, ip link, ip addr

========
设备管理
========

网卡
====

罗列
----

终端运行 ``ip link`` 命令，即可看到系统所有网卡的详细信息：

.. code-block:: shell-session

    $ ip link
    1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default
        link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAULT group default qlen 1000
        link/ether 08:00:27:31:1f:2a brd ff:ff:ff:ff:ff:ff
    3: eth1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state DOWN mode DEFAULT group default qlen 1000
        link/ether 08:00:27:f4:74:b8 brd ff:ff:ff:ff:ff:ff

启停
----

启用网卡，请运行以下命名：

.. code-block:: shell-session

    $ ip link set eth1 up

命令成功执行后，网卡即处于活跃(工作)状态。

相应地，停用网卡则是：

.. code-block:: shell-session

    $ ip link set eth1 down

地址设置
--------

运行 ``ip addr`` 可以查看所有网卡设置的地址：

.. code-block:: shell-session

    $ ip addr
    1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default
        link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
        inet 127.0.0.1/8 scope host lo
           valid_lft forever preferred_lft forever
        inet6 ::1/128 scope host
           valid_lft forever preferred_lft forever
    2: eth0: <BROADCAST,MULTICAST> mtu 1500 qdisc pfifo_fast state DOWN group default qlen 1000
        link/ether 08:00:27:31:1f:2a brd ff:ff:ff:ff:ff:ff
        inet 10.0.2.15/24 brd 10.0.2.255 scope global eth0
           valid_lft forever preferred_lft forever
    3: eth1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
        link/ether 08:00:27:f4:74:b8 brd ff:ff:ff:ff:ff:ff
        inet 192.168.56.3/24 brd 192.168.56.255 scope global eth1
           valid_lft forever preferred_lft forever
        inet6 fe80::a00:27ff:fef4:74b8/64 scope link
           valid_lft forever preferred_lft forever

其中， ``link`` 一行是数据链路层地址，也就是 ``MAC`` 地址(或者称为物理地址)；
``inet`` 一行是网络层地址( `IPv4` )，也就是我们所熟知的 ``IP`` 地址；
``inet6`` 一行也是网络层地址( `IPv6` )，目前应用还不广。

如果只想显示某个网卡，可以在命令后面指定：

.. code-block:: shell-session

    $ ip addr show dev eth0
    2: eth0: <BROADCAST,MULTICAST> mtu 1500 qdisc pfifo_fast state DOWN group default qlen 1000
        link/ether 08:00:27:31:1f:2a brd ff:ff:ff:ff:ff:ff
        inet 10.0.2.15/24 brd 10.0.2.255 scope global eth0
           valid_lft forever preferred_lft forever

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. comments
    comment something out below
