# ninja-hello-world

该项目的目的：如何在Ubuntu22.04上编译gn，以及如何使用gn构建build.ninja文件，最后使用ninja编译出可执行文件。

## 编译gn

前置依赖环境：

```bash
sudo apt update
sudo apt install build-essential clang cmake curl git python3 python-is-python3
sudo apt install ninja-build
```


安装和编译gn：

```bash
git clone https://gn.googlesource.com/gn
cd gn
python build/gen.py
ninja -C out
```

## 编译项目

在 `005-ninja-hello-world` 项目下有两个文件：

- BUILD.gn: 该文件用于说明如何编译当前项目

- .gn: 该文件用于说明gn的工具链配置

编译项目：

```bash
# 添加gn目录到环境变量
export PATH="~/C/005-ninja-hello-world/gn/out:$PATH"

# 构建和编译
gn gen out
ninja -C out

# 运行可执行文件
./out/hello_world
```