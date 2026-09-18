# STM32 排线导通检测器

一款基于 STM32C031C6T6 的 50 路排线导通检测工具。

连接待测排线后，使用表笔逐路检测。检测到导通时，数码管显示对应线号，并由蜂鸣器发出提示音。

## 功能

- 支持 50 路排线导通检测
- 单路导通时显示对应线号 `01`～`50`，并持续蜂鸣提示
- 无导通时显示 `--`，蜂鸣器保持静音
- 多路导通异常时显示 `EE`，蜂鸣器保持静音
- 对完整检测结果进行非阻塞软件防抖
- 支持 SWD 下载和调试

## 硬件

- STM32C031C6T6 主控
- 7 片 74HC165 输入扩展
- TM1637 两位数码管驱动
- USB Type-C 供电
- 2×25P 排线接口
- 有源蜂鸣器

## 仓库内容

- `code/`：STM32 固件工程
- `DT 2026.eprj2`：嘉立创 EDA 工程文件
- `SCH_YY.json`：嘉立创 EDA 原理图数据
- `PCB_YY.json`：嘉立创 EDA PCB 数据
- `BOM_YY.csv`：元器件清单

## 使用方法

1. 为检测板连接 USB Type-C 电源。
2. 将待测排线连接至 2×25P 接口。
3. 将万用表黑表线插入板载测试插座。
4. 使用红表笔接触待测线路。
5. 导通时查看数码管显示的线号。

## 固件

固件工程位于 `code/`，由 STM32CubeMX 生成，采用 STM32 HAL 和 CMake 构建。

推荐使用 VS Code，并安装 STMicroelectronics 官方 STM32 VS Code Extension。工程不依赖特定编辑器，也可以直接通过命令行构建。

如需修改芯片、时钟或引脚配置，请使用 STM32CubeMX 打开 `code/yy.ioc`。重新生成代码时，仅保证保留 `USER CODE` 区域内的修改，应用代码建议放在独立的源文件中。

构建环境：

- CMake 3.22+
- Ninja
- GNU Arm Embedded Toolchain

```bash
cd code
cmake --preset Debug
cmake --build --preset Debug
```

发布构建使用对应的 Release 预设：

```bash
cmake --preset Release
cmake --build --preset Release
```

## 项目状态

目前已完成硬件设计，以及 74HC165 输入采集、50 路导通解析、TM1637 显示、蜂鸣器控制和检测结果防抖等固件功能。Debug 与 Release 构建均已通过，当前版本可用于上板测试。

HC165 实际位序、数码管显示方向、防抖时间及蜂鸣器行为仍需结合实物验证，当前版本不视为已经完成硬件验证的稳定版本。

## 许可证

Copyright © 2026 NewStorm

- 硬件设计文件（`DT 2026.eprj2`、`SCH_YY.json`、`PCB_YY.json` 和 `BOM_YY.csv`）采用 [CERN-OHL-S-2.0](LICENSE) 强互惠许可证。
- NewStorm 编写的固件代码采用 [MIT License](code/LICENSE)。STM32Cube HAL、CMSIS 及其他带有独立版权或许可证声明的第三方文件仍适用其各自许可证。
