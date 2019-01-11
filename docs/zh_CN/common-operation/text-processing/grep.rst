.. grep 文本搜索
    FileName:   grep.rst
    Author:     Fasion Chan
    Created:    2018-12-03 18:40:21
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
    :keywords: grep, linux, text search

============
grep文本搜索
============

反向匹配
========

.. code-block:: shell-session

    $ grep -v

输出上下文
==========

需要输出与匹配行相邻的行，可以通过 `-C` 参数实现。
同时输出匹配行前后 `10` 行：

.. code-block:: shell-session

    $ grep -C 10

参考文献
========

#. `grep(1) - Linux manual page <http://man7.org/linux/man-pages/man1/grep.1.html>`_

.. _grep: http://man7.org/linux/man-pages/man1/grep.1.html

.. comments
    comment something out below

