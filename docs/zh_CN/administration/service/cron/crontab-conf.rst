.. Crontab配置
    FileName:   crontab-conf.rst
    Author:     Fasion Chan
    Created:    2018-07-18 20:46:33
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: crontab配置

============
crontab 配置
============

**用户定时任务配置文件** 存放于 `/var/spool/cron` 目录下，以用户名命名。
`crontab` 命令其实就是通过操作这些配置文件，实现对 **定时任务** 的管理。

.. note::

    注意，用户定时任务配置文件目录可能因系统而异。在 `Ubuntu` ，该目录是 `/var/spool/cron/crontabs` 。

格式详解
========

想要掌握定时任务配置，全面了解 `crontab` 配置文件格式是必须的。

一个典型的 `crontab` 用户配置如下：

.. code-block:: text

    # Edit this file to introduce tasks to be run by cron.
    #
    # Each task to run has to be defined through a single line
    # indicating with different fields when the task will be run
    # and what command to run for the task
    #
    # To define the time you can provide concrete values for
    # minute (m), hour (h), day of month (dom), month (mon),
    # and day of week (dow) or use '*' in these fields (for 'any').#
    # Notice that tasks will be started based on the cron's system
    # daemon's notion of time and timezones.
    #
    # Output of the crontab jobs (including errors) is sent through
    # email to the user the crontab file belongs to (unless redirected).
    #
    # For example, you can run a backup of all your user accounts
    # at 5 a.m every week with:
    # 0 5 * * 1 tar -zcf /var/backups/home.tgz /home/
    #
    # For more information see the manual pages of crontab(5) and cron(8)
    #
    # m h  dom mon dow   command
    * * * * * /usr/local/gse/agent/bin/gsectl watch

以 **井号** ( `#` )开头的行是 **注释** 。
可以看到，例子中大部分内容都是注释。
仔细看注释，原来是在说明如何编写 `crontab` 配置呢！

在 `crontab` 配置中，一个有效的配置行便定义一个定时任务。
每个配置行由 `6` 个字段组成，描述定时任务的执行要素：

#. **分** ， `0-59`
#. **时** ， `0-23`
#. **日** ， `1-31`
#. **月** ， `1-12`
#. **星期** ， `0-7` ( `0` 和 `7` 均表示星期天 )
#. **执行命令**

配置字段分成两类，定义运行时间的 **时间字段** (前 `5` 个字段均是)以及 **命令字段** 。

时间字段定义执行时间，以字段 **分** 为例：

- ``0`` ，表示第 `0` 分钟执行；
- ``0,30`` 表示第 `0` 分以及第 `30` 分钟执行；
- ``*/5`` ，表示每个整 `5` 分钟执行，即第 `0` 、 `5` 、 `10` 、 `15` ，以此类推；
- ``*`` ，表示每分钟执行；
- ``0-30`` ，表示 `0-30` 分钟，每分钟执行以此；

**命令字段** 是定时任务执行的命令定义，只要是一行合法的 `shell` 命令即可。

配置实例
========

每分钟执行脚本：

.. code-block:: text

    * * * * * /path/to/my/script

每小时第 `3` 和第 `15` 分钟执行脚本：

.. code-block:: text

    3,15 * * * * /path/to/my/script

上午 `8` 时到 `11` 时的第 `3` 和 `15` 分钟执行脚本：

.. code-block:: text

    3,15 8-11 * * * /path/to/my/script

每隔两天上午 `8` 时到 `11` 时的第 `3` 和 `15` 分钟执行脚本：

.. code-block:: text

    3,15 8-11 */2 * * /path/to/my/script

每周一上午 `8` 时到 `11` 时的第 `3` 和 `15` 分钟执行脚本：

.. code-block:: text

    3,15 8-11 * * 1 /path/to/my/script

每晚 `21:30` 执行脚本：

.. code-block:: text

    30 21 * * * /path/to/my/script

每月 `1` 、 `10` 、 `22` 日的 `4:45` 执行脚本：

.. code-block:: text

    45 4 1,10,22 * * /path/to/my/script

每周六、周日的 `1:10` 执行脚本：

.. code-block:: text

    10 1 * * 6,0 /path/to/my/script

每天 `18` 时到 `23` 时之间，每隔 `30` 分钟执行脚本：

.. code-block:: text

    0,30 18-23 * * * /path/to/my/script

每周六 `23` 时执行脚本：

.. code-block:: text

    0 23 * * 6 /path/to/my/script

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. comments
    comment something out below

