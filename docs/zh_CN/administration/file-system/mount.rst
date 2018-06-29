.. 挂载文件系统
    FileName:   mount.rst
    Author:     Fasion Chan
    Created:    2018-06-27 17:40:17
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

============
挂载文件系统
============

挂载目录
========

.. code-block:: shell-session

    $ mkdir /data
    $ mkdir /data2
    $ mount --bind /data2 /data

.. code-block:: shell-session

    $ touch /data2/foo
    $ ls /data2
    foo
    $ ls /data
    foo

.. code-block:: text

    /data2 /data none defaults,bind 0 0

.. comments
    comment something out below

    .. meta::
        :description lang=zh:
        :keywords:

