# FireLamp 项目代码优化建议

本文基于当前工程的 [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c)、相关驱动文件以及现有文档进行分析，重点关注以下几个方面：

- 功能正确性
- 时序与状态机设计
- 低功耗能力
- 稳定性与可维护性
- 嵌入式实现成本

---

## 1. 总体结论

当前 `FireLamp` 工程已经具备了基础框架：

- GPIO 初始化
- Timer 1ms 节拍
- UART 调试输出
- 外部中断入口
- 电量检测和 PWM 调光的预留结构

但从实际实现来看，`main.c` 中仍存在一些关键问题，其中有几项已经不只是“可以优化”，而是会直接影响功能正确性、待机唤醒、定时逻辑和产品功耗表现。

建议优先处理：

1. 状态机与待机唤醒逻辑
2. 定时事件触发方式
3. 白灯定时关闭逻辑
4. 按键消抖参数
5. 中断中执行串口打印

---

## 2. 高优先级问题

### 2.1 待机后缺少可靠唤醒路径

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L431)
- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L752)

现象：

- 当 `cmd_Menu == CMD_None_NoDo` 时，主循环直接 `continue`
- 此时 `menuCheck()` 不再执行
- 按键轮询逻辑完全停止
- 外部中断 `INT2_ISR_Handler()` 中原本用于唤醒系统的逻辑被注释掉，只保留了一条串口打印

风险：

- 系统进入待机后可能无法通过按键恢复
- 实际使用中会表现为“关机后按键无效”或“偶发无法唤醒”

建议：

- 在待机状态下保留最低限度的唤醒检测机制
- 如果使用外部中断唤醒，则 ISR 中只置位唤醒标志，不直接做复杂逻辑
- 主循环在待机态中应判断唤醒标志，而不是直接无限空转

---

### 2.2 1 秒任务触发方式不正确

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L452)

现象：

当前代码使用：

```c
if (B_1ms_Count % 1000 == 0) {
    scanerChargingDetection();
    scanerWhiteLEDControl();
}
```

问题在于：

- `B_1ms_Count` 在 1ms 中断中递增
- 主循环在这 1ms 内会执行很多次
- 所以只要 `B_1ms_Count % 1000 == 0` 成立，这两个函数就会被重复调用很多次

风险：

- 本应 1 秒执行 1 次的逻辑，实际会在一个很短时间窗口内执行多次
- 导致白灯计时错误
- 导致充电状态检测节拍失真

建议：

- 改成“事件标志”方式
- 在 Timer1 ISR 中每累计 1000 次 1ms 中断时，置位 `flag_1s = 1`
- 主循环中检测 `flag_1s` 后执行一次任务，并立即清零

推荐思路：

```c
volatile bit flag_1s;

// ISR
if (++tick_1s >= 1000) {
    tick_1s = 0;
    flag_1s = 1;
}

// main loop
if (flag_1s) {
    flag_1s = 0;
    scanerChargingDetection();
    scanerWhiteLEDControl();
}
```

---

### 2.3 白灯定时关闭逻辑与注释不一致

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L480)

现象：

```c
LED_White_Timer_Open_S = 1000; // 10s
```

存在两个问题：

- 变量名叫 `_S`，含义像“秒”，但赋值却是 `1000`
- 由于当前 1 秒判断方式有误，递减速度远超预期

风险：

- 白灯亮灯时间不可控
- 调试过程中会出现“有时太短，有时不准”的现象

建议：

- 明确时间单位
- 如果变量是秒，10 秒就写 `10`
- 如果变量是毫秒，变量名应改成 `_ms`
- 建议统一采用“固定节拍 + 倒计时”模式

例如：

```c
u16 white_led_remain_s = 0;
```

触发时：

```c
white_led_remain_s = 10;
```

每秒处理一次：

```c
if (white_led_remain_s > 0) {
    white_led_remain_s--;
    if (white_led_remain_s == 0) {
        IO_LED_White = POW_LED_CLOSE;
    }
}
```

---

### 2.4 按键消抖参数明显过大

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L672)
- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L680)
- [`key.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/key.c#L236)

现象：

当前代码：

```c
if (Key1_cnt >= 500)
```

而 `KeyScan()` 是在 1ms 节拍里执行的，这意味着短按需要稳定按下 500ms 才能触发。

风险：

- 用户按键响应非常迟钝
- 会给人“按键不灵敏”的感觉
- 与注释中的 50ms 防抖不一致

建议：

- 普通短按消抖一般用 20ms 到 50ms
- 推荐先调整为 50ms
- 长按和短按应拆分定义，避免语义混乱

建议定义：

```c
#define KEY_DEBOUNCE_MS   50
#define KEY_LONGPRESS_MS 1000
```

---

### 2.5 中断中直接打印串口日志，存在卡死风险

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L752)
- [`STC8G_H_UART.h`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/STC8G_H_UART.h#L54)
- [`STC8G_H_UART.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/STC8G_H_UART.c#L260)
- [`STC8G_H_UART_Isr.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/STC8G_H_UART_Isr.c#L34)

现象：

`INT2_ISR_Handler()` 里执行：

```c
PrintString1("INT2 \r\n");
```

而当前串口发送模式为：

```c
#define UART_QUEUE_MODE 0
```

即阻塞发送模式。

风险：

- 中断里执行阻塞发送非常危险
- 如果发送完成依赖 UART 中断，而当前又处于中断上下文，容易造成死锁或长时间阻塞
- 会影响系统实时性

建议：

- ISR 中只置位标志，例如 `key_wakeup_flag = 1`
- 串口打印放到主循环中执行
- 如果确实需要高频日志，建议改为队列发送模式，但仍不建议在外部中断中直接格式化打印

---

## 3. 中优先级问题

### 3.1 电量档位判断存在边界漏洞

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L605)

现象：

当前区间判断方式如下：

```c
else if (inVol > 3.8 && inVol < 4.0)
else if (inVol > 3.6 && inVol < 3.8)
else if (inVol > 3.4 && inVol < 3.6)
```

风险：

- `3.8`、`3.6`、`3.4` 这些边界值会落不到任何预期区间
- 电量显示可能出现跳档或错误档位

建议：

- 使用连续闭区间或半开区间
- 例如从高到低统一写成 `>=`

示例：

```c
if (inVol >= 4.0f) level = 4;
else if (inVol >= 3.8f) level = 3;
else if (inVol >= 3.6f) level = 2;
else if (inVol >= 3.4f) level = 1;
else level = 0;
```

---

### 3.2 ADC 配置、注释和换算公式不统一

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L326)
- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L353)
- [`STC8G_H_ADC.h`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/STC8G_H_ADC.h#L29)
- [`STC8G_H_ADC.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/STC8G_H_ADC.c#L55)

现象：

- 当前 `ADC_RES_12BIT` 配置为 `0`
- 表示当前按 10 位 ADC 使用
- 但注释和公式中混用了 1024、4096、2.5V、4.2V 等多种口径

风险：

- 电量换算结果不可信
- 后续如果接入真实电池分压，显示会明显偏差

建议：

- 统一以下几个参数
  - ADC 分辨率
  - 参考电压
  - 分压比
  - 输入对应真实电池电压
- 用“毫伏整数”计算，避免浮点

示例思路：

```c
battery_mv = adc_val * ADC_REF_MV * DIV_RATIO_NUM / ADC_MAX / DIV_RATIO_DEN;
```

---

### 3.3 ADC 功能目前实际上未启用

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L417)
- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L450)

现象：

- `ADC_config()` 被注释
- `scanerBatterVoltage()` 也未在主循环中启用

风险：

- 从代码结构上看似支持电量检测
- 但运行时实际上并不会采样
- 容易造成调试误判

建议：

- 如果当前版本不打算启用 ADC，建议明确标注为“预留功能”
- 如果准备启用，应同时打开：
  - ADC 初始化
  - 周期采样逻辑
  - 电量显示逻辑

---

### 3.4 中断与主循环共享变量未统一使用 `volatile`

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L120)
- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L768)

典型变量：

- `B_1ms`
- `B_1ms_Count`
- `LED_WORKLED_50ms`
- `ADC_Timer_ms`
- `Key1_Function`

风险：

- 编译优化开启后，主循环可能读取到寄存器缓存值
- 出现“偶发没反应”“有时生效有时失效”的隐蔽 bug

建议：

- 所有在 ISR 中修改、主循环中访问的状态变量都应评估是否加 `volatile`
- 多字节变量如 `u16/u32` 若被 ISR 与主循环同时访问，还应考虑临界区保护

---

### 3.5 `SysClose()` 逻辑不完整，低功耗收益有限

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L716)
- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L740)

现象：

- `SysClose()` 里大部分真正关闭外设的代码被注释掉
- `Sysleep()` 也没有真正调用

风险：

- 名义上“关机”，实际上系统仍在运行
- 会持续消耗电池电量
- 对太阳能灯这类产品影响较大

建议：

- 明确区分“逻辑关闭”和“低功耗休眠”
- 真正关闭不必要外设：
  - UART 接收
  - ADC
  - PWM
  - 不需要的定时器
- 在满足唤醒条件的前提下进入 sleep 模式

---

## 4. 低优先级但建议尽快整理的问题

### 4.1 浮点运算和 `%f` 打印不适合 8051

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L330)
- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L356)

风险：

- 增加代码体积
- 增加运行时间
- 对小资源 MCU 不友好

建议：

- 全部改成整数毫伏计算
- 打印时用整数拆分显示，如 `3720mV` 或 `3.72V`

---

### 4.2 `vsprintf` 存在缓冲区溢出风险

相关位置：

- [`STC8G_H_UART.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/STC8G_H_UART.c#L272)

现象：

```c
char buffer[128];
vsprintf(buffer, fmt, args);
```

风险：

- 长字符串输出可能写爆缓冲区
- 会造成内存破坏和异常行为

建议：

- 若工具链支持，改用 `vsnprintf`
- 若不支持，尽量限制格式化输出长度，并统一封装日志接口

---

### 4.3 命名、注释和实现不一致

典型问题：

- `LED_WORKLED_50ms` 实际每 1ms 就置位
- `ADC10S_Count >= 60000` 看起来更接近 60 秒
- 注释中有 UART2，代码实际初始化的是 UART1

相关位置：

- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L132)
- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L336)
- [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c#L242)

风险：

- 后续维护难度增加
- 调试时容易误判问题来源

建议：

- 统一命名中的时间单位
- 统一串口编号描述
- 删除失效注释，保留当前真实设计意图

---

### 4.4 根目录文档内容混入无关信息

相关位置：

- [`readme.md`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/readme.md#L44)

现象：

- 根目录 README 后半段混入了明显与当前 MCU 项目无关的 Python/pyswarm 内容

风险：

- 降低项目可读性
- 对外协作或后续交接不友好

建议：

- 清理 README
- 保留当前项目目标、硬件说明、工程结构、编译方式和功能说明

---

## 5. 推荐优化顺序

建议按下面顺序推进，这样收益最高、风险最低。

### 第一阶段：先修正确性

1. 修复待机和唤醒逻辑
2. 修复 1 秒节拍触发方式
3. 修复白灯 10 秒定时逻辑
4. 修复按键防抖时间
5. 去掉中断中的串口打印

### 第二阶段：补足功能链路

1. 整理 ADC 初始化
2. 启用周期采样
3. 修正电压换算公式
4. 修正电量分档区间

### 第三阶段：提升稳定性与功耗

1. ISR 共享变量补 `volatile`
2. 真正关闭无用外设
3. 进入低功耗模式
4. 清理日志输出策略

### 第四阶段：提升维护性

1. 统一命名与注释
2. 清理无效代码和注释代码块
3. 更新设计文档和 README

---

## 6. 可落地的重构方向

如果后续准备继续演进这个工程，建议逐步把主逻辑整理为下面的结构：

### 6.1 统一事件标志

例如：

```c
volatile bit flag_1ms;
volatile bit flag_10ms;
volatile bit flag_100ms;
volatile bit flag_1s;
volatile bit flag_key_wakeup;
volatile bit flag_charge_changed;
```

好处：

- 定时任务调度更清晰
- 主循环职责明确
- 避免用 `%` 判断时间窗口

### 6.2 拆分业务状态

建议将当前状态拆成：

- 系统电源状态
- 白灯状态
- 充电状态
- 电量显示状态
- 按键事件状态

这样比单独依赖 `cmd_Menu` 更容易维护。

### 6.3 把“硬件动作”和“业务判断”分离

例如：

- `white_led_on()`
- `white_led_off()`
- `battery_led_show(level)`
- `system_enter_sleep()`
- `system_wakeup()`

好处：

- 减少重复代码
- 硬件变更时修改范围更小
- 便于单独测试每个动作

---

## 7. 最终结论

`FireLamp` 当前代码的主要问题不在“有没有功能框架”，而在以下几点：

- 时间驱动方式不够严谨
- 状态机闭环不完整
- 待机和唤醒逻辑存在断点
- 部分参数和注释不一致
- 低功耗和稳定性细节还没有收口

如果只是做实验验证，这份代码已经可以继续迭代。  
如果目标是做成稳定可用的产品固件，建议优先修复本文列出的高优先级问题，再继续扩展 ADC、电量显示和 PWM 调光。

---

## 8. 后续可继续支持的工作

后续如果需要，可以继续做下面几项：

1. 直接重构 [`main.c`](/d:/DataSpace/HardWork/GitHubRepo/SolarOutdoorPortableLamp/FireLamp/main.c)，修复高优先级问题
2. 补一版“事件驱动 + 低功耗”结构的精简实现
3. 整理一份更清晰的 `README`
4. 补充状态机流程图和模块关系图

