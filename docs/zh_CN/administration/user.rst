.. 用户管理
    FileName:   user.rst
    Author:     Fasion Chan
    Created:    2018-03-23 19:49:40
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
        Linux 下，可以用 useradd 或者 adduser 命令进行用户管理。
        useradd命令是一个编译好的二进制程序，直接与系统打交道；
        而adduser命令在useradd之上包了一层 Perl 脚本，实现更友好的交互式操作。
    :keywords: Linux用户管理, adduser, useradd

========
用户管理
========

`Linux` 下，可以用 `useradd` 或者 `adduser` 命令进行用户管理。

`useradd` 命令是一个编译好的二进制程序，直接与系统打交道；
而 `adduser` 命令在 `useradd` 之上包了一层 `Perl` 脚本，实现更友好的交互式操作。
因此，两者在功能上并无差别，只是用法有些不同。
相对而言， `adduser` 比 `useradd` 更易用。

添加用户
========

使用 ``adduser`` 命令添加用户，带上新用户名：

.. code-block:: shell-session

    root@Ubuntu:~ $ adduser fasion
    Adding user `fasion' ...
    Adding new group `fasion' (1002) ...
    Adding new user `fasion' (1002) with group `fasion' ...
    Creating home directory `/home/fasion' ...
    Copying files from `/etc/skel' ...
    Enter new UNIX password:
    Retype new UNIX password:
    passwd: password updated successfully
    Changing the user information for fasion
    Enter the new value, or press ENTER for the default
        Full Name []: Chen Yanfei
        Room Number []: XXXX
        Work Phone []: XXXX
        Home Phone []: XXXX
        Other []:
    Is the information correct? [Y/n] y

命令运行后，根据提示输入密码、用户信息并在信息确认处按下 ``Y`` 便可完成。

.. note::

    注意，密码输入时，屏幕没有任何显示，连 ``*`` 号都没有。
    这是正常现象，确保密码正确输入并按下回车即可。

切换用户
========

切换到其他用户，只需运行 ``su`` 命令并输入密码即可：

.. code-block:: shell-session

    xxxx@Ubuntu:~ $ su fasion
    Password:

.. note::

    从 ``root`` 用户切换到其他用户不需要输入密码。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst
