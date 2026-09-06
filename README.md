# STM32 排线导通检测器

一款基于 STM32C031C6T6 的 50 路排线导通检测工具。

连接待测排线后，使用表笔逐路检测。检测到导通时，数码管显示对应线号，并由蜂鸣器发出提示音。

## 功能

- 支持 50 路排线导通检测
- 显示当前导通线路的编号
- 导通时蜂鸣提示
- 支持多路导通异常检测
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

## 项目状态

项目正在开发中。目前已完成硬件设计及 STM32CubeMX 基础工程，检测、显示和蜂鸣功能尚待实现与实物验证。

## 许可证

Copyright © 2026 NewStorm

- 硬件设计文件（`DT 2026.eprj2`、`SCH_YY.json`、`PCB_YY.json` 和 `BOM_YY.csv`）采用 [CERN-OHL-S-2.0](LICENSE) 强互惠许可证。
- NewStorm 编写的固件代码采用 [MIT License](code/LICENSE)。STM32Cube HAL、CMSIS 及其他带有独立版权或许可证声明的第三方文件仍适用其各自许可证。
