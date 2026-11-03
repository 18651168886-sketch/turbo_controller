# turbo_controller

STM32F407 双板控制工程，包含原工程、参考控制板代码、中文说明模型，以及基于 MATLAB/Simulink R2025a 与 STM32CubeMX 的新版工程。

## 新版工程入口

打开 `20261030/turbo_controller.slx`；CubeMX 配置为 `20261030/turbo_f407.ioc`，`20261030/cubemx/turbo_f407/` 中还保留了 CubeMX 子工程配置。实际板级代码需由 CubeMX 生成并结合工具链验证。

- 控制逻辑保存在 Simulink 模型中，板级初始化由 CubeMX 工程承担。
- `BoardInput_输入换算与协议解析` 负责输入转换和通信解析。
- `BoardOutput_串口封装与阀门时序` 负责输出组帧及执行时序。
- 模型附有分层中文学习说明；5 处 CRC16 使用与参考工程一致的 256 项查表数据。
- CRC16 查表数据保存在模型工作区的 `CRC16_Table_Reference` 中。

模型更新检查与 CRC16 仿真对比已通过；尚未完成实际硬件编译、下载与上板功能验证。SD 卡记录配置也需要实际硬件验证。

## 其他内容

| 路径 | 内容 |
| --- | --- |
| `Code_V5.2 - doubleplate/` | 原控制板参考代码及相关库 |
| `CYS_110WP_3_Control.slx`、`CYS_110WP_3_Model_double_plate.slx` | 原始 Simulink 模型 |
| `control.slx`、`turbo_control.slx` | 此前整理的中文说明模型 |
| `control_控制流程图.html` | 控制流程学习页面 |
| `turbo_control_中英对照.csv` | 模型中英文名称对照 |
| `AutoCode/`、`*_ert_rtw/`、`NRIST/` | 旧工程相关代码和模型资源，保留供参考 |

仿真缓存、自动备份、Keil `OBJ` 目录和编译中间文件由根目录 `.gitignore` 排除；这些规则不会删除本地文件。

旧工程可能依赖历史版本工具链或 32 位 MEX 文件，请优先从 `20261030` 内的新模型开始阅读。
