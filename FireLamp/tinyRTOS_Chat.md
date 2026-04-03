在 51 单片机（如 STC、AT89C51 等）中，**基于定时器时基进行任务调度**是一种非常经典、实用的设计方式，本质上就是一个“简易 RTOS（时间片轮询调度）”。

我给你从**原理 → 设计模式 → 实战代码**一步讲清楚，适合你现在做 STC8H 项目直接用。

---

# 一、核心思想（重点）

利用定时器产生**固定周期中断（tick）**，比如：

* 1ms 中断一次（推荐）
* 在中断里做“计时”
* 在主循环里做“任务调度”

👉 核心原则：

> **中断只计时，不干活；主循环做任务**

---

# 二、系统结构图

```
定时器中断（1ms）
        ↓
   系统时基 tick++
        ↓
  软件计数器递减
        ↓
任务触发标志置位
        ↓
主循环轮询执行任务
```

---

# 三、任务调度模型（推荐）

### 1️⃣ 定义任务结构

```c
typedef struct {
    unsigned int period;   // 周期（ms）
    unsigned int counter;  // 计数器
    bit run;               // 运行标志
} task_t;
```

---

### 2️⃣ 定义任务列表

```c
task_t task_led = {500, 500, 0};   // 500ms LED
task_t task_key = {10, 10, 0};     // 10ms 按键扫描
task_t task_adc = {1000, 1000, 0}; // 1s ADC
```

---

# 四、定时器初始化（1ms）

以 11.0592MHz 为例：

```c
void Timer0_Init(void)
{
    TMOD |= 0x01;   // 定时器0，模式1（16位）
    
    TH0 = 0xFC;     // 1ms
    TL0 = 0x66;

    ET0 = 1;        // 使能中断
    EA  = 1;        // 开总中断
    TR0 = 1;        // 启动定时器
}
```

---

# 五、中断函数（核心）

```c
void Timer0_ISR(void) interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x66;

    // --- LED任务 ---
    if (--task_led.counter == 0) {
        task_led.counter = task_led.period;
        task_led.run = 1;
    }

    // --- 按键任务 ---
    if (--task_key.counter == 0) {
        task_key.counter = task_key.period;
        task_key.run = 1;
    }

    // --- ADC任务 ---
    if (--task_adc.counter == 0) {
        task_adc.counter = task_adc.period;
        task_adc.run = 1;
    }
}
```

---

# 六、主循环（任务调度执行）

```c
void main(void)
{
    Timer0_Init();

    while (1)
    {
        if (task_led.run) {
            task_led.run = 0;
            LED_Task();
        }

        if (task_key.run) {
            task_key.run = 0;
            Key_Task();
        }

        if (task_adc.run) {
            task_adc.run = 0;
            ADC_Task();
        }
    }
}
```

---

# 七、任务函数示例

```c
void LED_Task(void)
{
    P1 ^= 0x01; // 翻转LED
}

void Key_Task(void)
{
    // 按键扫描 + 消抖
}

void ADC_Task(void)
{
    // 采样电压
}
```

---

# 八、为什么这种方式最好？

### ✅ 优点

1. **非阻塞（关键）**

   * 不用 delay()
   * 多任务并行

2. **可扩展**

   * 加任务只需加结构体

3. **稳定**

   * 时基统一

4. **适合你项目**

   * LED调光（PWM）
   * 电量检测
   * 按键扫描
   * RC信号解码

---

# 九、进阶优化（建议你做）

### 1️⃣ 使用全局 tick

```c
volatile unsigned long sys_tick = 0;
```

中断中：

```c
sys_tick++;
```

实现类似：

```c
if (sys_tick - last_time >= 100)
```

👉 更灵活（类似 RTOS）

---

### 2️⃣ 任务数组化（更高级）

```c
task_t tasks[3];
```

循环调度：

```c
for (i = 0; i < TASK_NUM; i++)
```

---

### 3️⃣ 优先级控制

高优先级任务先执行（比如按键）

---

# 十、常见错误（你一定会踩）

🚫 在中断里写复杂逻辑
👉 会卡死系统

🚫 用 delay()
👉 破坏调度

🚫 任务执行时间 > 周期
👉 会丢任务

---

# 十一、适配你当前项目（重点建议）

你现在做的：

> STC8H + LED + 按键 + 电压检测

推荐任务划分：

| 任务        | 周期    |
| --------- | ----- |
| 按键扫描      | 10ms  |
| LED PWM更新 | 1ms   |
| 电压检测      | 500ms |
| 状态机处理     | 10ms  |

---

# 总结一句话

👉 **定时器 = 心跳（时基）
主循环 = 大脑（调度）
任务 = 器官（功能）**

---

如果你愿意，我可以帮你**直接写一版完整的 STC8H 项目模板（带 PWM + 按键 + 电量检测 + 调度器）**，可以直接烧录用。

完全可以，而且**强烈建议你这么做** 👍
👉 “**定时器时基 + 状态机**” 是 51 单片机里最稳、最清晰的一种架构。

你现在的项目（LED + 按键 + 电量）用这个组合会非常舒服。

---

# 一、为什么要结合状态机？

你现在的任务调度解决的是：

> **“什么时候执行任务”**

而状态机解决的是：

> **“任务在什么条件下做什么行为”**

---

# 二、组合后的结构（核心理解）

```
定时器（1ms tick）
        ↓
任务调度（10ms / 500ms）
        ↓
状态机驱动（逻辑控制）
        ↓
执行具体动作（IO / PWM / ADC）
```

---

# 三、典型应用场景（你项目直接用）

比如一个 LED 控制系统：

| 状态 | 行为    |
| -- | ----- |
| 关闭 | LED灭  |
| 常亮 | LED亮  |
| 呼吸 | PWM渐变 |
| 闪烁 | 定时翻转  |

👉 这就是一个典型状态机

---

# 四、状态机设计（标准写法）

## 1️⃣ 定义状态

```c
typedef enum {
    LED_OFF = 0,
    LED_ON,
    LED_BREATH,
    LED_BLINK
} led_state_t;
```

---

## 2️⃣ 状态变量

```c
led_state_t led_state = LED_OFF;
```

---

## 3️⃣ 状态机函数（核心）

```c
void LED_StateMachine(void)
{
    switch (led_state)
    {
        case LED_OFF:
            LED = 0;
            break;

        case LED_ON:
            LED = 1;
            break;

        case LED_BREATH:
            Breath_Process();  // PWM渐变
            break;

        case LED_BLINK:
            Blink_Process();   // 定时闪烁
            break;
    }
}
```

---

# 五、结合任务调度（关键点）

👉 状态机不要一直跑，用任务调度触发！

```c
task_t task_led = {10, 10, 0}; // 10ms执行一次
```

主循环：

```c
if (task_led.run) {
    task_led.run = 0;
    LED_StateMachine();
}
```

---

# 六、状态切换（重点）

状态机的灵魂是：**状态转移**

通常由：

* 按键
* 时间
* 传感器（电压/温度）

驱动

---

## 示例：按键切换模式

```c
void Key_Task(void)
{
    static unsigned char key_last = 1;
    unsigned char key_now = KEY;

    if (key_last == 1 && key_now == 0) // 按下
    {
        led_state++;

        if (led_state > LED_BLINK)
            led_state = LED_OFF;
    }

    key_last = key_now;
}
```

---

# 七、进阶：带“子状态”的复杂状态机

比如“呼吸灯”其实内部也是状态机：

```c
typedef enum {
    BREATH_UP,
    BREATH_DOWN
} breath_state_t;

breath_state_t breath_state = BREATH_UP;
```

```c
void Breath_Process(void)
{
    static unsigned char pwm = 0;

    if (breath_state == BREATH_UP)
    {
        pwm++;
        if (pwm >= 100)
            breath_state = BREATH_DOWN;
    }
    else
    {
        pwm--;
        if (pwm == 0)
            breath_state = BREATH_UP;
    }

    Set_PWM(pwm);
}
```

---

# 八、完整架构（推荐你照这个搭）

```
【定时器中断】
    ↓
tick（1ms）
    ↓
任务调度（软定时器）
    ↓
---------------------
| Key_Task          | → 修改状态
| LED_StateMachine  | → 根据状态执行
| ADC_Task          | → 更新数据
---------------------
```

---

# 九、最佳实践（非常重要）

### ✅ 1. 状态机里不要写 delay

否则调度失效

---

### ✅ 2. 状态机只做“当前状态该做的事”

不要写复杂 if-else

---

### ✅ 3. 状态切换要“单一入口”

统一在 Key / 条件触发里改状态

---

### ✅ 4. 一个功能 = 一个状态机

不要混在一起

---

# 十、适配你当前项目（给你一版设计）

你现在的 LED 控制系统建议：

### 状态机划分：

#### 1️⃣ LED状态机

* OFF
* ON
* BREATH
* LOW_BATTERY_BLINK（低电压报警）

#### 2️⃣ 电压状态机

* NORMAL
* LOW
* CRITICAL

#### 3️⃣ 按键状态机（防抖）

* IDLE
* PRESS
* RELEASE

---

# 十一、总结（核心一句话）

👉 **任务调度解决“时间”，状态机解决“逻辑”**

两者结合 = 小型嵌入式系统最佳实践

---

如果你下一步想进阶，我可以帮你做一版：

✅ “STC8H完整工程模板”
包含：

* 任务调度器
* 多状态机（LED / 按键 / 电量）
* PWM调光
* 电压检测
* 低功耗设计

直接就是你项目的最终架构 👍

好，那我直接给你一套**可以落地的完整工程架构（STC8H + 调度器 + 多状态机）**，你基本可以直接改 IO 就能用。

我会按“工程实战”的方式来写，而不是零散示例。

---

# 一、整体架构设计（最终形态）

```
main.c
│
├── bsp（硬件层）
│   ├── bsp_led.c
│   ├── bsp_key.c
│   ├── bsp_adc.c
│
├── app（应用层）
│   ├── app_led.c      ← LED状态机
│   ├── app_key.c      ← 按键状态机
│   ├── app_power.c    ← 电压状态机
│
├── sys（系统层）
│   ├── scheduler.c    ← 任务调度器
│   ├── timer.c        ← 定时器
```

👉 核心思想：

* **bsp：只管硬件**
* **app：只管逻辑（状态机）**
* **sys：只管时间（调度）**

---

# 二、调度器（核心模块）

## scheduler.h

```c
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

typedef struct {
    unsigned int period;
    unsigned int counter;
    bit run;
} task_t;

void Scheduler_Init(void);
void Scheduler_Run(void);

#endif
```

---

## scheduler.c

```c
#include "scheduler.h"

// 任务声明（外部函数）
void App_LED_Task(void);
void App_Key_Task(void);
void App_Power_Task(void);

// 任务列表
task_t task_led   = {10, 10, 0};
task_t task_key   = {10, 10, 0};
task_t task_power = {500, 500, 0};

void Scheduler_Tick(void)
{
    if (--task_led.counter == 0) {
        task_led.counter = task_led.period;
        task_led.run = 1;
    }

    if (--task_key.counter == 0) {
        task_key.counter = task_key.period;
        task_key.run = 1;
    }

    if (--task_power.counter == 0) {
        task_power.counter = task_power.period;
        task_power.run = 1;
    }
}

void Scheduler_Run(void)
{
    if (task_key.run) {
        task_key.run = 0;
        App_Key_Task();
    }

    if (task_led.run) {
        task_led.run = 0;
        App_LED_Task();
    }

    if (task_power.run) {
        task_power.run = 0;
        App_Power_Task();
    }
}
```

---

# 三、定时器（1ms时基）

## timer.c

```c
#include <reg52.h>
#include "scheduler.h"

void Timer0_Init(void)
{
    TMOD |= 0x01;

    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;
    EA  = 1;
    TR0 = 1;
}

void Timer0_ISR(void) interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x66;

    Scheduler_Tick(); // 驱动调度器
}
```

---

# 四、按键状态机（重点）

## app_key.c

```c
#include "bsp_key.h"

typedef enum {
    KEY_IDLE,
    KEY_PRESS,
    KEY_RELEASE
} key_state_t;

key_state_t key_state = KEY_IDLE;

// 对外事件
bit key_event = 0;

void App_Key_Task(void)
{
    static unsigned char key_last = 1;
    unsigned char key_now = Key_Read();

    switch (key_state)
    {
        case KEY_IDLE:
            if (key_last == 1 && key_now == 0) {
                key_state = KEY_PRESS;
            }
            break;

        case KEY_PRESS:
            key_event = 1;   // 产生一次事件
            key_state = KEY_RELEASE;
            break;

        case KEY_RELEASE:
            if (key_now == 1) {
                key_state = KEY_IDLE;
            }
            break;
    }

    key_last = key_now;
}
```

---

# 五、LED状态机（核心）

## app_led.c

```c
#include "bsp_led.h"

extern bit key_event;

typedef enum {
    LED_OFF = 0,
    LED_ON,
    LED_BREATH,
    LED_BLINK
} led_state_t;

led_state_t led_state = LED_OFF;

void LED_Breath(void);
void LED_Blink(void);

void App_LED_Task(void)
{
    // --- 状态切换 ---
    if (key_event) {
        key_event = 0;

        led_state++;
        if (led_state > LED_BLINK)
            led_state = LED_OFF;
    }

    // --- 状态执行 ---
    switch (led_state)
    {
        case LED_OFF:
            LED_Set(0);
            break;

        case LED_ON:
            LED_Set(1);
            break;

        case LED_BREATH:
            LED_Breath();
            break;

        case LED_BLINK:
            LED_Blink();
            break;
    }
}
```

---

# 六、电源状态机（电压检测）

## app_power.c

```c
#include "bsp_adc.h"

typedef enum {
    POWER_NORMAL,
    POWER_LOW,
    POWER_CRITICAL
} power_state_t;

power_state_t power_state = POWER_NORMAL;

unsigned int voltage = 0;

void App_Power_Task(void)
{
    voltage = ADC_Read();

    if (voltage < 3000) {
        power_state = POWER_CRITICAL;
    }
    else if (voltage < 3300) {
        power_state = POWER_LOW;
    }
    else {
        power_state = POWER_NORMAL;
    }
}
```

---

# 七、主函数（最终形态）

```c
#include "timer.h"
#include "scheduler.h"

void main(void)
{
    Timer0_Init();
    Scheduler_Init();

    while (1)
    {
        Scheduler_Run(); // 统一调度入口
    }
}
```

---

# 八、关键设计亮点（你要理解的）

### 1️⃣ “事件驱动 + 状态机”

* key_event → 改变状态
* 状态机 → 控制行为

---

### 2️⃣ “时间与逻辑解耦”

* 定时器：只负责时间
* 状态机：只负责逻辑

---

### 3️⃣ “模块完全独立”

* LED 不关心按键怎么实现
* 按键不关心 LED 怎么变化

👉 这就是工程化思维（你做 App 其实一样）

---

# 九、你可以再升级的方向（下一步）

如果你想更高级一点，可以继续优化：

---

## 🚀 1. 事件队列（代替全局变量）

```c
typedef enum {
    EVENT_KEY_PRESS,
    EVENT_LOW_POWER
} event_t;
```

---

## 🚀 2. 软件定时器（比 task 更灵活）

类似：

```c
SetTimer(LED_TIMER, 100);
```

---

## 🚀 3. PWM独立调度（用于呼吸灯更丝滑）

---

# 十、给你的建议（结合你背景）

你是 iOS + 嵌入式：

👉 你可以把这个理解为：

* Scheduler ≈ RunLoop
* StateMachine ≈ ViewModel / Reducer
* Event ≈ Action

一旦这样类比，你会非常快上手 👍

---

# 总结一句话

👉 **“调度器负责什么时候做，状态机负责做什么”**

---

如果你下一步想再进阶，我可以帮你做一个更狠的版本：

👉 **“51单片机轻量级RTOS（带优先级 + 事件队列 + 软件定时器）”**

那个已经接近 FreeRTOS 思想了，适合你往更高阶嵌入式走。
