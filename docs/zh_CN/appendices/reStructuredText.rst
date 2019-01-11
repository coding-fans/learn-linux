.. reStructuredText
    FileName:   reStructuredText.rst
    Author:     Fasion Chan
    Created:    2019-01-09 19:27:52
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
    :keywords: reStructuredText, 代码块, 表格, 图片, 链接

================
reStructuredText
================

`reStructuredText`_

.. include:: _rst/titles.rst

以上是多级标题写法，标题标识用于区别不同的标题级别，逐层下降。
将 `****` 放在最前面使用则是一级标题，其他以此类推。
语法如下：

.. literalinclude:: _rst/titles.rst
    :language: ReST

源码引用
========

.. include:: _rst/literalinclude.rst

本代码块是由其中的代码定义出来的！

从 *_rst/literalinclude.rst* 文件中，展示其中第 *4-7* 行，显示行数，语法为 *ReST* 。

表格
====

.. include:: _rst/table.rst

.. literalinclude:: _rst/table.rst
    :language: ReST

本页源码
========

.. literalinclude:: reStructuredText.rst
    :language: ReST
    :linenos:

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _reStructuredText: http://docutils.sourceforge.net/docs/ref/rst/restructuredtext.html

.. comments
    comment something out below

