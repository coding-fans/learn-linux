.. Linux运维工程师必备的80个监控工具
    FileName:   80-linux-monitoring-tools.rst
    Author:     Fasion Chan
    Created:    2018-07-25 20:42:06
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
    :keywords:

=============================
Linux工程师必备的88个监控工具
=============================

.. note::

    本文是一篇译文，原文是： `80 Linux Monitoring Tools <https://blog.serverdensity.com/80-linux-monitoring-tools-know/>`_ 。

Linux性能监控及调试并不是个容易事，在 **合适的时机** 使用 **正确的工具** 却可事半功倍！

以下是史上整理最全的 `Linux` 监控工具集：

命令行工具
==========

1. top
------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/dd1012376c651ee2ffb8213857b99c14.jpg
    :width: 800px

    top

这是一个预装在很多 `Unix` 系统的小工具。
当你想要查看在系统中运行的进程或者线程时， `top` 就是一个不错的工具。
你可以用不同的方式对这些进程进行排序，默认是以 `CPU` 使用率进行排序的。

2. htop
-------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/12fc6af67dc62f0533fed55510a168d9.jpg
    :width: 800px

    htop

`htop`_ 实质上是一个增强版的 `top` 。
用它对进程进行排序更为容易。
界面看上去也更容易理解，并且已经内置了很多通用操作。
另外，它也是完全交互式的。

3. atop
-------

与 `top` 和 `htop`_ 类似， `atop`_ 也可以用来监控系统进程。
不同的是， `atop` 可以按天记录进程日志，以便长期分析。

4. apachetop
------------

`apachetop`_ 用于监视 `apache` 网络服务器的整体性能。
它主要是基于 `mytop` 。
`apachetop` 展示服务器当前读写数以及总处理请求数，非常有用。

5. ftptop
---------

`ftptop`_ 用于监控 `FTP` 服务器，提供的信息非常丰富：
当前 `FTP` **连接总数** 、 **会话总数** ( `session` )、 **上传下载总数** 以及 **登录用户** 等等。

6. mytop
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/fc755a0d3b2ba2fb222fbdcae3fe68b5.jpg
    :width: 800px

    mytop

`mytop`_ 是一个用于监控 `MySQL` 线程以及性能的小工具。
它可以让你实时查看数据库正在处理哪些请求。

7. powertop
-----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/d229d346cf4517618c932f5b24453ab3.jpg
    :width: 800px

    powertop

`powertop`_ 可以帮你诊断与 **电源消耗** 以及 **电源管理** 相关的问题。
`powertop` 也可以帮你 **试验电源管理设置** ，以达到最优。
按制表键( `Tab` )可以切换标签页。

8. iotop
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/4a24a9daef026cf4e07faaa7fb3eb2b3.jpg
    :width: 800px

    iotop

`iotop`_ 检查 `I/O` 使用情况并以一种类似 `top` 的界面展示。
它按列展示读和写的速率，每行代表一个进程。
它也展示了进程花在内存页换入( `swapping in` )以及等待 `I/O` 时间的百分比。

桌面监控
========

9. ntopng
---------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/43c5857536c2d66c781765b2a58e2fd6.jpg
    :width: 800px

    ntopng

`ntopng`_ 是 `ntop` 的升级版，通过浏览器提供了一个用于网络监控的图形用户界面。
它可以胜任的工作包括但不局限于：主机地理定位；采集网络流量；显示 `IP` 流量分布并分析。

10. iftop
---------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/27278c81dead36d5bd3dd3ed144ddd54.jpg
    :width: 800px

    iftop

`iftop`_ 命令与 `top` 类似，但与 `top` 主要用于检查 `CPU` 使用率不同，
`iftop`_ 监听 **选定网卡网络流量** 并以表格的形式展示当前使用量。
因此，它可以轻松回答像“为什么我的网络这么慢呢？”这样的问题。

11. jnettop
-----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/defddeac0190c2e492ceb5f9a25fcf26.jpg
    :width: 800px

    jnettop

`jnettop`_ 也用于监测网络流量，但比 `iftop` 更形象。
另外，它还支持自定义文本输出，以及可用于更深入分析的机器友好模式。


12. bandwidthd
--------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/971474cfbcbf236c023e285176a6c0ca.jpg
    :width: 800px

    bandwidthd

`bandwidthd`_ 追踪 `TCP/IP` 网络子网的使用情况，并通过 `png` 图片构建一个形象化 `HTML` 页面在浏览器中展示。
它由数据库系统驱动，支持搜索、过滤、多传感器以及定制化报告。

14. ethtool
-----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/91195036db50abff7ec2a354ea1d12da.jpg
    :width: 800px

    ethtool

`ethtool`_ 命令用于展示和修改 `网卡 <https://linux-network-programming.readthedocs.io/zh_CN/latest/protocols/ethernet.html#nic>`_ 参数。
它也可以用来诊断 `以太网 <https://linux-network-programming.readthedocs.io/zh_CN/latest/protocols/ethernet.html>`_ 设备，以获取更多统计数据。

15. NetHogs
-----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/b2fd20cebc2501342e1b2a54ea379ce6.jpg
    :width: 800px

    NetHogs

`NetHogs`_ 对网络流量安装协议或者子网进行分解，然后按进程进行分组。
因此，当网络流量猛增时，你可以使用 `NetHogs` 揪出肇事进程。

16. iptraf
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/2fb7f5e885a4b03c6f57f7763590be44.jpg
    :width: 800px

    iptraf

`iptraf` 收集不少指标： `TCP` 连 **接数据包以及字节计数** 、 **接口统计** 、 **活动指标** 、 `TCP/IP` **通信故障** 以及 **站内数据包及字节计数** 等等。

17. ngrep
---------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/1e0968ff7403c6208f64db811c3f0dbb.jpg
    :width: 800px

    ngrep

`ngrep`_ 是为网络层设计的 `grep` 。
它依赖 `pcap` ，支持通过 **正则表达式** 或 **十六进制表达式** 来匹配数据包。

18. MRTG
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/c63c11088444a34bc242b7a06f4aefee.jpg
    :width: 800px

    MRTG

`MRTG`_ 最初被开发来监控路由流量，但现在能够监控网络相关的东西。
它每五分钟采集一次数据，然后生成一个 `HTML` 页面。
它还具备发送邮件告警的能力。

19. bmon
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/23da63fe24eea4cf7688ade81b286bc0.jpg
    :width: 800px

    bmon

`bmon` 能够监控并帮你调试网络。
它捕获网络相关统计数据，并以友好的方式进行展示。
你还可以通过 `curses` 或脚本与 `bmon` 进行交互。

20. traceroute
--------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/c1360b9f4b4faebe8260cc46ba4d4e08.jpg
    :width: 800px

    traceroute

`traceroute` 是一个内置工具，用于展示路由以及测量数据包经过网络的延迟。

21. IPTState
------------

`IPTState` 可以让你观察流量通过 `iptables` 后去往何处，并根据你给定的条件进行排序。
该工具还支持从 `iptables` 表中删除状态信息。

22. darkstat
------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/7e1c748d78d7044b65536009649e0908.jpg
    :width: 800px

    traceroute

`darkstat`_ 采集网络流量并计算用量统计。
统计报告由图表组成，通过一个简单的 `HTTP` 服务器对外提供。

23. vnStat
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/1db884d11d1edaddd4998bf1520b4d92.jpg
    :width: 800px

    vnStat

`vnStat`_ 也是一个 **网络流量监控** 工具。
它直接使用内核提供的统计数据，占用系统资源更少。
由于统计数据经过 **持久化** ，机器重启后依旧可用。
另外，有艺术气质的系统管理员可以使用它提供的 **颜色选项** 。

24. netstat
-----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/0aca727c7d65ea25b4886e10c84205c5.jpg
    :width: 800px

    netstat

`netstat` 是一个系统内置工具，可以查询 `TCP` 网络连接(套接字)、路由表以及网卡信息。
它经常被用于排查网络问题。

25. ss
------

`netstat` 是一个古老的工具，现在更推荐使用 `ss` 命令。
`ss` 比 `netstat` 更能干，显示信息更全面，更重要的是速度更快。
举个例子，运行 ``ss -s`` 可以输出一个 **汇总统计** 。

26. nmap
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/f4d5462dae62bcdee5f9282fd64f67af.jpg
    :width: 800px

    nmap

`nmap`_ 是一个 **扫描工具** ，用于扫描服务器端口，探测操作系统类型。
你也可以将 `nmap` 用于 **SQL注入漏洞** ( `SQL injection vulnerabilities` )、 **网络发现** ( `network discovery` )以其他 **渗透测试** ( `penetration testing` )场景。

27. mtr
-------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/21b0293ae36bd785b090db436f059f5c.jpg
    :width: 800px

    mtr

`mtr`_ 将 `traceroute` 以及 `ping` 的功能组合起来，形成一个更强大的网络诊断工具。
使用 `mtr` 时，它会限制每个数据包的跳数( `TTL` )，然后根据过期回包判断数据包达到的位置。
它不断重复这个探测过程，每秒一次。

28. tcpdump
-----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/31c43cde73a40feded8628de5d2d3d1d.jpg
    :width: 800px

    tcpdump

`tcpdump`_ 是一个 **抓包工具** ，根据你提供的 **条件表达式** ( `expression` )抓取匹配的 **网络数据包** ( `packet` )并展示。
你也可以将数据保存下来，做进一步分析。

29. Justniffer
--------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/3280a150a2969cc27b9078f58238f161.jpg
    :width: 800px

    Justniffer

`Justniffer`_ 是一个 `TCP` 包 **嗅探器** 。
使用该嗅探器，你可以选择嗅探 **低层数据** ( `low-level data` )还是 **高层数据** ( `high level data` )。
你也可以生成日志，格式可以自定义。
例如，你可以模仿 `apache` 的访问日志( `access log` )格式。

基础设施监控
============

30. Server Density
------------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/ed3aa0a9d782d43e8c859776ef412c75.png
    :width: 800px

    Server Density

31. OpenNMS
-----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/72e94be22fff748eb1cbd86fbca0fd7d.jpg
    :width: 800px

    OpenNMS

`OpenNMS`_ 主要有四个功能： **事件管理和通知** 、 **发现和配置** 、 **服务监控** 以及 **数据采集** 。
它支持定制化以适应不同的网络环境。

32. SysUsage
------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/38f2cb3e1e80e7ae06a02adaa7ac8b8c.jpg
    :width: 800px

    SysUsage

`SysUsage`_ 通过 `sar`_ 以及其他系统命令持续对系统进行监控。
它允许你设置告警阈值，指标超过设定值时便发送告警信息。
`SysUsage` 本身可以部署在中央服务器，所有采集到的统计数据也存在那。
它提供一个 `Web` 界面，可以查看到所有的统计数据。

33. brainypdm
-------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/ce051e3310555a769a0bc03c74f800b9.jpg
    :width: 800px

    brainypdm

`brainypdm`_ 是一个数据管理和监控工具，可以从 `nagios`_ 或者其他通用数据源收集数据并制作图表。
它是跨平台的，基于 `Web` 的图表也支持自定义。

34. PCP
-------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/497130024df76788b4704259a5ffe365.jpg
    :width: 800px

    PCP

`PCP`_ 是 `Performance Co-Pilot` 的简写。
它可以非常高效地从多台主机收集指标数据。
它提供一个编写插件的框架，借此你可以写插件采集你认为重要的指标。
你可以通过 `Web` 界面或者一个 `GUI` 界面查看数据图表。
监控大型系统， `PCP`_ 是一个不错的选择。

35. KSysGuard
-------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/fa07d02cb1405335a6ac0989c86dbd72.jpg
    :width: 800px

    kdesystemguard

`KSysGuard`_ 这个工具既是 **系统监视器** ，又是 **任务管理器** 。
通过 `KSysGuard` 你可以在一个工作表里查询多台服务器的系统指标，也可以杀死或者启动一个服务器进程。

36. Munin
---------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/0f3c311f1de38dae3f01570b280f94ff.jpg
    :width: 800px

    Munin

`Munin`_ 是一个 **网络监控** 和 **系统监控** 工具，可以为指标设置告警阈值。
它使用 `RRDtool`_ 生成图表，并提供一个 `Web` 界面来展示图表。
它主打插件扩展能力，提供了不少可用插件。

37. Nagios
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/94c68cc7e13b1140c6bd8edd3d23980d.jpg
    :width: 800px

    Nagios

`Nagios`_ 也是一个 **系统和网络监控** 工具，可以支撑监控大量服务器。
它支持在发现异常时发送告警信息，也提供了非常丰富的插件。

38. Zenoss
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/dc22534402eca6e6914fb19f3beda2fb.jpg
    :width: 800px

    Zenoss

`Zenoss`_ 支持对 **系统** 和 **网络** 指标进行监控，而且提供了 `Web` 界面。
它还支持 **网络资源** 以及 **网络配置变更** 自动发现。
它也支持告警功能，而且兼容 `Nagios`_ 插件。

39. Cacti
---------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/8a2074ab69c9569caa73c6def2dd2346.jpg
    :width: 800px

    Cacti

`Cacti` 是一个网络画图工具，使用 `RRDtool`_ 做数据存储。
它允许用户定期拉取服务指标，并以图表展示。
用户可以通过 `shell` 脚本来扩展 `Cacti` ，实现对指定资源的监控。

40. Zabbix
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/50ff46fd83fe110969bbb10ab3b03969.png
    :width: 800px

    Zabbix

`Zabbix`_ 是一个开源的 **基础设施监控** ( `infrastructure monitoring` )解决方案。
`Zabbix` 核心部分是用 `C` 实现的，前端则是 `PHP` ，数据存储部分则可以对接大部分现有数据库。
此外， `agent` 不是必要的。
如果你不想安装 `agent` ，那么 `Zabbix` 应该一个不错的选择。

41. nmon
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/7ecdd7d79b9fbd6efbfd2ffd3f66b7fc.jpg
    :width: 800px

    nmon

43. Glances
-----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/84345651b15e04e41f78361c8c1c5dc8.jpg
    :width: 800px

    Glances

44. saidar
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/0a2305246173976637dee23b110681f5.jpg
    :width: 800px

    saidar

45. RRDtool
-----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/e17cf423be979f1f9b14ad54ba5b687e.jpg
    :width: 800px

    rrdtool

46. monit
---------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/696ce21a357bbd189fdd2a99e448d6af.jpg
    :width: 800px

    monit

47. Linux进程管理器
-------------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/dd4ab2e995210c2b66e56cef61e69910.jpg
    :width: 800px

    Linux进程管理器

`Linux进程管理器`_ 与 `OSX` 活动监视器以及 `Windows` 进程管理器类似。
它的设计目标是，做比 `top` 或 `ps` 更好用的工具。
通过它，你可以查看到每个系统进程，以及它们占用了多少内存和 `CPU` 资源。

48. df
------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/86b3ada9a7c88497fe33478ae8026250.jpg
    :width: 800px

    df

`df` ( `disk free` 的缩写)，是一个用于 **查看文件系统使用量** 的内置系统工具( `Unix` 系统 )。

49. discus
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/402d1a1f8df5bd4866f6da94f95be262.jpg
    :width: 800px

    discus

51. Dstat
---------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/1b5e8ad937cc9b41782b8cb762531034.jpg
    :width: 800px

    Dstat

55. vmstat
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/7f77db054b15521a290a11a148980514.jpg
    :width: 800px

    vmstat

57. mpstat
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/d8ce917ba02f74a0d7f2d36aac237c5f.jpg
    :width: 800px

    mpstat

58. pmap
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/2fb760e717bab336d56b2a529e4314a2.jpg
    :width: 800px

    pmap

59. ps
------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/b55c93440191a340e6fcc0ae779e30fc.jpg
    :width: 800px

    ps

60. sar
-------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/e26348533d48fe0984e60d7499bc73b6.jpg
    :width: 800px

    sar

61. collectl
------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/3390e5ebdc8fe87f5198f3688c55bd56.jpg
    :width: 800px

    collectl

62. iostat
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/3060c554c3d49b95b199b5f1c5f44de8.jpg
    :width: 800px

    iostat

63. free
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/185a4e8b726d13764a642710254e9ed0.jpg
    :width: 800px

    free

64. proc伪文件系统
------------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/f68a27629e0365509b03d6ab0e3d7d59.jpg
    :width: 800px

    proc伪文件系统

66. Gnome系统监视器
-------------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/4cc14949b6f71197bd9120264b700456.jpg
    :width: 800px

    Gnome系统监视器

日志监控
========

67. GoAccess
------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/bc237c25d604515d06b57d1b9a9f29d8.jpg
    :width: 800px

    GoAccess

69. Swatch
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/008870cf0970d846349b7cf4210adcd6.jpg
    :width: 800px

    Swatch

70. MultiTail
-------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/f677a8a29a205803025b9a57c8b258b5.jpg
    :width: 800px

    MultiTail

网络监控
========

73. strace
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/7fec62b8270f1468a37147062c1751eb.jpg
    :width: 800px

    strace

74. DTrace
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/e0cc9c09300697628c95cd974d8f16c7.jpg
    :width: 800px

    DTrace

75. webmin
----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/9a0a34759c3cd642c98a701533c2f71d.jpg
    :width: 800px

    webmin

76. stat
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/70114a1a5f6f3a059995dd056cfe41b5.jpg
    :width: 800px

    stat

77. ifconfig
------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/96f80e561dd78fa2e72feb2b05e8a2c5.jpg
    :width: 800px

    ifconfig

78. unlimit
-----------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/790731a08b2e55404b767c9264767980.jpg
    :width: 800px

    unlimit

79. cpulimit
------------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/0df76f4cb64ce21f8de738fca1598c03.jpg
    :width: 800px

    cpulimit

80. lshw
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/0898e9597464f534e5a79c7fdfb61b9e.jpg
    :width: 800px

    lshw

82. lsof
--------

.. figure:: /_images/maintenance/monitor/tools/80-linux-monitoring-tools/7dd77451ab3aaa5b2917725ee40f54e3.jpg
    :width: 800px

    lsof

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `80 Linux Monitoring Tools <https://blog.serverdensity.com/80-linux-monitoring-tools-know/>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _acct: http://www.gnu.org/software/acct/
.. _apachetop: https://github.com/JeremyJones/Apachetop
.. _atop: http://www.atoptool.nl/
.. _bandwidthd: http://bandwidthd.sourceforge.net/
.. _bmon: https://github.com/tgraf/bmon/
.. _brainypdm: http://sourceforge.net/projects/brainypdm/
.. _Cacti: http://www.cacti.net/
.. _collectd: https://collectd.org/
.. _collectl: http://collectl.sourceforge.net/
.. _conky: http://conky.sourceforge.net/
.. _cpulimit: https://github.com/opsengine/cpulimit
.. _darkstat: https://unix4lyfe.org/darkstat/
.. _discus: http://packages.ubuntu.com/lucid/utils/discus
.. _Dstat: http://dag.wiee.rs/home-made/dstat/
.. _DTrace: http://dtrace.org/blogs/about/
.. _ethtool: https://www.kernel.org/pub/software/network/ethtool/
.. _ftptop: http://www.proftpd.org/docs/howto/Scoreboard.html
.. _GKrellM: http://members.dslextreme.com/users/billw/gkrellm/gkrellm.html
.. _Glances: https://github.com/nicolargo/glances
.. _Gnome系统监视器: http://freecode.com/projects/gnome-system-monitor
.. _GoAccess: http://goaccess.io/
.. _htop: http://hisham.hm/htop/
.. _iftop: http://www.ex-parrot.com/pdw/iftop/
.. _incron: http://inotify.aiken.cz/?section=incron&page=about&lang=en
.. _iostat: http://sebastien.godard.pagesperso-orange.fr/
.. _iotop: http://guichaz.free.fr/iotop/
.. _IPTState: http://www.phildev.net/iptstate/index.shtml
.. _iptraf: http://iptraf.seul.org/
.. _jnettop: http://jnettop.kubs.info/wiki/
.. _Justniffer: http://justniffer.sourceforge.net/
.. _KSysGuard: https://userbase.kde.org/KSysGuard
.. _Linux进程管理器: http://sourceforge.net/projects/procexp/
.. _Logwatch: http://sourceforge.net/projects/logwatch/
.. _MobaXterm: http://mobaxterm.mobatek.net/
.. _monit: http://mmonit.com/monit
.. _monitorix: http://www.monitorix.org/
.. _MRTG: http://oss.oetiker.ch/mrtg/
.. _mtr: http://www.bitwizard.nl/mtr/
.. _Munin: http://munin-monitoring.org/
.. _MultiTail: http://www.vanheusden.com/multitail/
.. _mytop: http://jeremy.zawodny.com/mysql/mytop/
.. _Nagios: http://www.nagios.org/
.. _NetHogs: http://nethogs.sourceforge.net/
.. _Net-SNMP: http://www.net-snmp.org/
.. _ngrep: http://ngrep.sourceforge.net/
.. _nmap: http://nmap.org/
.. _nmon: http://nmon.sourceforge.net/pmwiki.php
.. _ntopng: http://www.ntop.org/products/ntop/
.. _Observium: http://www.observium.org/
.. _OpenNMS: http://www.opennms.org/
.. _PCP: http://www.pcp.io/
.. _powertop: https://01.org/powertop
.. _RRDtool: http://oss.oetiker.ch/rrdtool/
.. _saidar: https://packages.debian.org/sid/utils/saidar
.. _sar: http://sebastien.godard.pagesperso-orange.fr/
.. _Shinken monitoring: http://www.shinken-monitoring.org/
.. _SmokePing: http://oss.oetiker.ch/smokeping/
.. _strace: http://sourceforge.net/projects/strace/
.. _Swatch: http://sourceforge.net/projects/swatch/
.. _SysUsage: http://sysusage.darold.net/
.. _tcpdump: http://www.tcpdump.org/
.. _ulimit: http://ss64.com/bash/ulimit.html
.. _vnStat: http://humdi.net/vnstat/
.. _webmin: http://www.webmin.com/
.. _whowatch: http://whowatch.sourceforge.net/
.. _xosview: http://www.pogo.org.uk/~mark/xosview/
.. _Zabbix: http://www.zabbix.com/
.. _Zenoss: http://www.zenoss.com/

.. comments
    comment something out below

