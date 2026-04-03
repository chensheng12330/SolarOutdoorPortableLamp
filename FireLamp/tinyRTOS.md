下面是一份**可直接用于项目落地与团队协作的架构设计文档**（针对 51 / STC8H 单片机，基于“定时器时基 + 任务调度 + 状态机”）。我按**核心思想 → 原理 → 设计模式 → 落地代码 → 优缺点 → 规范与注意事项**完整展开。

---

# 一、文档概述

**目标：**
构建一套在 51 单片机上可复用、可扩展、非阻塞的轻量级软件架构，用于多任务（LED、按键、电压检测等）协同运行。

**适用场景：**

* STC8 / STC89 / AT89C51 系列
* 无 RTOS 的裸机系统
* 需要多任务并发但资源有限的场景

---

# 二、核心思想（Architecture Principles）

## 2.1 三层分离

```
时间（Time）   → 定时器 + 调度器
逻辑（Logic）  → 状态机
执行（Action） → 硬件驱动
```

👉 解耦目标：

| 层级  | 责任   |
| --- | ---- |
| sys | 时间管理 |
| app | 状态控制 |
| bsp | 硬件操作 |

---

## 2.2 两大核心机制

### 1️⃣ 时基驱动（Time Base Driven）

通过定时器产生固定周期（如 1ms）：

> 所有任务基于统一时间推进

---

### 2️⃣ 状态机驱动（State Machine Driven）

系统行为由状态决定：

> “当前状态 + 输入事件 → 下一状态 + 行为”

---

## 2.3 核心设计哲学

👉 **非阻塞 + 事件驱动 + 分层解耦**

---

# 三、系统原理（How It Works）

## 3.1 时序流程

```
Timer0 中断（1ms）
        ↓
Scheduler_Tick()
        ↓
任务计数器递减
        ↓
任务触发（run=1）
        ↓
主循环 Scheduler_Run()
        ↓
执行任务（状态机）
```

---

## 3.2 关键原则

### 原则1：中断只做“时间推进”

* 禁止复杂逻辑
* 禁止 IO 操作

---

### 原则2：主循环负责所有业务

---

### 原则3：任务必须“短小可重入”

---

# 四、设计模式（Design Patterns）

---

## 4.1 软件定时器（Soft Timer）

```c
if (--task.counter == 0) {
    task.counter = task.period;
    task.run = 1;
}
```

👉 本质：**离散时间轮询**

---

## 4.2 任务调度（Cooperative Scheduler）

* 非抢占式
* 主循环轮询执行

---

## 4.3 状态机模式（State Pattern）

```c
switch(state) {
    case A: ...
}
```

👉 行为由状态决定

---

## 4.4 事件驱动（Event Driven）

```c
if (key_event) {
    state = NEXT;
}
```

👉 输入驱动状态变化

---

## 4.5 分层架构（Layered Architecture）

```
APP（逻辑）
↓
BSP（硬件）
```

---

# 五、工程结构设计（Project Layout）

```
project/
│
├── main.c
│
├── sys/
│   ├── scheduler.c
│   ├── scheduler.h
│   ├── timer.c
│
├── app/
│   ├── app_led.c
│   ├── app_key.c
│   ├── app_power.c
│
├── bsp/
│   ├── bsp_led.c
│   ├── bsp_key.c
│   ├── bsp_adc.c
```

---

# 六、核心模块设计

---

## 6.1 调度器

### 数据结构

```c
typedef struct {
    unsigned int period;
    unsigned int counter;
    bit run;
} task_t;
```

---

### Tick函数（中断中）

```c
void Scheduler_Tick(void)
{
    if (--task_led.counter == 0) {
        task_led.counter = task_led.period;
        task_led.run = 1;
    }
}
```

---

### 调度执行

```c
void Scheduler_Run(void)
{
    if (task_led.run) {
        task_led.run = 0;
        App_LED_Task();
    }
}
```

---

## 6.2 状态机（以 LED 为例）

```c
typedef enum {
    LED_OFF,
    LED_ON,
    LED_BREATH,
    LED_BLINK
} led_state_t;
```

---

### 状态机执行

```c
void App_LED_Task(void)
{
    switch (led_state)
    {
        case LED_OFF: LED_Set(0); break;
        case LED_ON:  LED_Set(1); break;
        case LED_BREATH: Breath(); break;
    }
}
```

---

## 6.3 状态切换（事件驱动）

```c
if (key_event) {
    led_state++;
}
```

---

## 6.4 定时器驱动

```c
void Timer0_ISR(void) interrupt 1
{
    Scheduler_Tick();
}
```

---

# 七、落地代码示例（最小可运行模板）

```c
void main(void)
{
    Timer0_Init();

    while (1)
    {
        Scheduler_Run();
    }
}
```

---

# 八、优点与缺点分析

---

## ✅ 优点

### 1. 非阻塞

* 不使用 delay
* 多任务并行

---

### 2. 可扩展

* 新任务只需增加结构体

---

### 3. 可维护

* 分层清晰

---

### 4. 资源占用低

* 无 RTOS
* RAM/ROM 极小

---

### 5. 易调试

* 单线程逻辑

---

## ❌ 缺点

### 1. 非抢占式

* 长任务会阻塞系统

---

### 2. 实时性有限

* 精度取决于 tick

---

### 3. 任务依赖人工管理

* 无优先级调度

---

### 4. 状态复杂时容易膨胀

* 需要良好设计

---

# 九、项目实践注意事项（非常重要）

---

## 9.1 时间相关

### ✅ 推荐

* tick = 1ms
* 任务周期 ≥ 5ms

### ❌ 禁止

* 长时间任务（>1ms）

---

## 9.2 中断规范

### 禁止：

* printf
* 延时
* ADC读取
* 复杂判断

---

## 9.3 状态机规范

### 必须：

* 单一职责
* 状态清晰
* 状态切换集中

---

## 9.4 全局变量规范

### 建议：

```c
volatile bit key_event;
```

---

## 9.5 命名规范（推荐）

| 类型 | 示例           |
| -- | ------------ |
| 任务 | App_LED_Task |
| 状态 | LED_BREATH   |
| 驱动 | BSP_LED_On   |

---

## 9.6 任务设计规范

👉 每个任务必须：

* 可重入
* 无阻塞
* 执行时间短

---

## 9.7 防抖设计

按键必须：

* ≥10ms 扫描
* 状态机处理

---

## 9.8 ADC采样

建议：

* 低频（≥100ms）
* 滤波处理

---

# 十、常见错误（踩坑总结）

---

### ❌ 在任务中使用 delay

→ 系统卡死

---

### ❌ 在中断中写业务逻辑

→ 难调试 + 不稳定

---

### ❌ 任务执行时间过长

→ 丢任务

---

### ❌ 状态机嵌套混乱

→ 不可维护

---

# 十一、扩展方向（进阶）

---

## 🚀 1. 事件队列

替代全局变量：

```c
PushEvent(EVENT_KEY);
```

---

## 🚀 2. 优先级调度

关键任务优先执行

---

## 🚀 3. 软件定时器抽象

类似：

```c
Timer_Start(id, 100);
```

---

## 🚀 4. 轻量级 RTOS 化

* 多任务
* 消息机制

---

# 十二、总结

👉 本架构本质是：

> **“用定时器模拟时间，用调度器分配时间，用状态机控制行为”**

---

# 十三、给你的建议（结合你背景）

你是 iOS 工程师，可以这样理解：

| 嵌入式          | iOS       |
| ------------ | --------- |
| Scheduler    | RunLoop   |
| StateMachine | ViewModel |
| Event        | Action    |

👉 一旦这样理解，你可以很快把复杂项目结构化 👍

---

# 如果你要继续优化

我可以帮你下一步做：

* ✅ **完整 STC8H 工程源码（可编译）**
* ✅ 加入 **PWM驱动（呼吸灯平滑版）**
* ✅ 加入 **低功耗模式（Idle/PowerDown）**
* ✅ 或升级为 **轻量RTOS架构**

---

如果你有具体项目（比如 RC 遥控车 / LED 控制器），我可以**按你的真实需求帮你裁剪这套架构**，做到直接量产级代码。
