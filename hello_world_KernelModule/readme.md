


# Hello World Kernel Module

This is a simple "Hello World" kernel module for demonstration purposes.

![alt text](image-1.png)

## Table of Contents

- [Introduction](#introduction)
- [Requirements](#requirements)
- [Building the Module](#building-the-module)
- [Loading the Module](#loading-the-module)
- [Unloading the Module](#unloading-the-module)
- [License](#license)

## Introduction

This kernel module prints "Hello, World!" to the kernel log when loaded and "Goodbye, World!" when unloaded.

## Requirements

- Linux kernel headers
- GCC (GNU Compiler Collection)
- Make

## Building the Module

To build the kernel module, run the following command:

```sh
make
```

## Loading the Module

To load the kernel module, use the insmod command:

```sh
sudo insmod mymod.ko
```

You can check the kernel log to see the output:

```sh
dmesg | tail
```

## Unloading the Module

To unload the kernel module, use the rmmod command:

```sh
sudo rmmod mymod
```

Again, you can check the kernel log to see the output:

```sh
dmesg | tail
```

## License
This project is licensed under the MIT License - see the LICENSE file for details.

