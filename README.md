# Calculator CLI

Calculator sederhana berbasis Command Line Interface (CLI) yang dibuat menggunakan C++.

## Features

* Penjumlahan
* Pengurangan
* Perkalian
* Pembagian
* Input angka dari terminal

## Requirements

* C++20 atau lebih baru
* CMake 3.30 atau lebih baru
* Build generator: Ninja
* C++ compiler (GCC atau Clang)

## Build

### Linux

Configure project:

```bash
cmake -B build -S . -G Ninja
```

Build:

```bash
cmake --build build
```

Run:

```bash
./build/cacl
```

### Windows

Configure project:

```powershell
cmake -B build -S . -G Ninja
```

Build:

```powershell
cmake --build build
```

Run:

```powershell
.\build\cacl.exe
```

## Development

Project ini menggunakan beberapa fitur CMake untuk mendukung workflow pengembangan:

* Ninja sebagai build generator
* C++20
* Unity build
* Export `compile_commands.json`
* Link-time optimization (LTO)
* AddressSanitizer dan LeakSanitizer
* Warning sebagai error

Unity build dan compile commands diaktifkan melalui CMake:

```cmake
set(CMAKE_UNITY_BUILD ON)
set(CMAKE_UNITY_BUILD_BATCH_SIZE 0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```
