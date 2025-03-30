# 耿德飙跑酷

一个基于SFML引擎开发的跑酷类游戏，由果园工作室出品。

## 项目简介

**耿德飙跑酷**是一款实验性质的跑酷游戏，由初中生开发者上古米歇尔（GY-GZW）主导开发。游戏使用SFML 2.5.1引擎构建，目前处于**0.5(beta)**版本阶段。虽然游戏仍处于早期开发状态，但已具备基本的跑酷机制和玩法。

## 技术信息

- **游戏引擎**: SFML 2.5.1
- **游戏版本**: 0.5(beta)
- **开发语言**: C++
- **开源协议**: MIT开源协议

## 使用说明

### 环境准备

1. **依赖库**: 确保已安装SFML 2.5.1库。
2. **编译器**: 推荐使用支持C++17标准的编译器（如GCC或Clang）。

### 编译步骤

```bash
g++ -std=c++17 -g *.cpp -o <程序名> \
    -I <SFML_INCLUDE_DIR> \
    -L <SFML_LIB_DIR> \
    -lsfml-graphics \
    -lsfml-window \
    -lsfml-system \
    -lsfml-audio
```

- `<程序名>`: 替换为您希望生成的可执行文件名称。
- `<SFML_INCLUDE_DIR>`: 替换为SFML头文件的安装路径。
- `<SFML_LIB_DIR>`: 替换为SFML库文件的安装路径。

### 运行

编译完成后，运行生成的可执行文件即可启动游戏。

## 项目状态

- **当前状态**: 开发中
- **已知问题**:
  - 性能问题较为严重
  - `checkCollisionDirection`功能完全无法使用
- **更新频率**: 可能较慢（作者为学生，BUG修复时间有限）

## 联系方式

- **作者**: 上古米歇尔
- **Bilibili**: [上古米歇尔-果园工作室](https://space.bilibili.com/)
- **GitHub**: [GY-GZW](https://github.com/GY-GZW)
- **个人主页**: [https://gy-gzw.github.io/my](https://gy-gzw.github.io/my)
- **QQ**: 2373460868
- **邮箱**:
  - 2373460868@qq.com
  - guoyuan.gzw@gmail.com

## 开源协议

本项目遵循MIT开源协议。您可以自由使用、修改和分发代码，但需遵守协议条款。

## 贡献指南

如果您发现BUG或希望贡献代码，请提交Pull Request或在GitHub Issues中报告问题。我们欢迎任何形式的贡献！

## 注意事项

- 由于作者时间有限，BUG修复可能较慢，请您谅解
- 游戏仍处于早期开发阶段，体验可能不够完善