太阳能户外照明灯
=========================================================

实现功能

- 通过按键1控制灯光的开与关
  - 短按-显示当前电量
    - 1. 白灯
    - 2. 黄灯
    - 3. 白黄灯
    - 4. 警示灯
  - 长按
    - 1. 关机，关闭所有功能
    - 2. 开机并显示电量
- 通过按键2控制灯光的亮度
  - 短按循环调节
    - 1. 100%
    - 2. 75%
    - 3. 50%
    - 4. 25%
  - 长按恢复默认值 100%

硬件设计
==========

- 电源模块
  - 3.3v稳压电源供电
- 组件模块
  - STC8H1K17-TSSOP20
  - 工作指示灯
  - 电池电压采样
  - 电池电量LED显示
  - 太阳能电压感应
  - USB5v电压感应
  - 

说明:
STC8H1K08与STC8H1K17相比，能支持在线仿真。
但只支持8k程序。

其它相关
AD-电压单位为毫伏(mV)

What's New
==========

This release features multiprocessing support.

Requirements
============

- NumPy

Installation and download
=========================

See the `package homepage`_ for helpful hints relating to downloading
and installing pyswarm.


Source Code
===========

The latest, bleeding-edge, but working, `code
<https://github.com/tisimst/pyDOE/tree/master/pyswarm>`_
and `documentation source
<https://github.com/tisimst/pyswarm/tree/master/doc/>`_ are
available `on GitHub <https://github.com/tisimst/pyswarm/>`_.

Contact
=======

Any feedback, questions, bug reports, or success stores should
be sent to the `author`_. I'd love to hear from you!

License
=======

This package is provided under two licenses:

1. The *BSD License*
2. Any other that the author approves (just ask!)

References
==========

- `Particle swarm optimization`_ on Wikipedia

.. _author: mailto:tisimst@gmail.com
.. _Particle swarm optimization: http://en.wikipedia.org/wiki/Particle_swarm_optimization
.. _package homepage: http://pythonhosted.org/pyswarm