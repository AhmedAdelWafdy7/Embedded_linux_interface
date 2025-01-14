# Embedded Linux Interfaces for Tiny Projects

This repository contains a collection of small projects and examples demonstrating how to interface with the Linux kernel using C++ applications and tiny kernel modules. These examples are designed for embedded systems and lightweight projects, providing a starting point for developers looking to interact with the Linux kernel at a low level.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Projects](#projects)
- [Getting Started](#getting-started)
- [Dependencies](#dependencies)


## Introduction

This repository is intended for developers working on embedded Linux systems who need to interact with the kernel using C++ applications or create small kernel modules. The examples provided here are minimalistic and focus on core concepts, making them suitable for tiny projects or learning purposes.

## Features

- **Kernel Module Examples**: Simple kernel modules demonstrating basic interactions with the Linux kernel.
- **C++ Applications**: User-space applications that interface with kernel modules or use kernel APIs.
- **Embedded Focus**: Lightweight and optimized for resource-constrained environments.
- **Cross-Platform**: Designed to work on ARM, x86, and other architectures supported by Linux.

## Projects

Here are the projects included in this repository:

1. **Hello World Kernel Module**: A basic kernel module that prints "Hello, World!" to the kernel log.
2. **Character Device Driver**: A simple character device driver that allows user-space applications to read/write data.
3. **GPIO Interface**: A kernel module and C++ application to interact with GPIO pins on an embedded board.
4. **I2C Communication**: Example of interfacing with an I2C device using a kernel module and user-space application.
5. **Kernel Thread Example**: Demonstrates how to create and manage kernel threads.
6. **Sysfs Interface**: A kernel module that exposes a sysfs interface for user-space interaction.

## Getting Started

To get started with the projects in this repository, clone the repo and follow the instructions in each project's directory.

```bash
git clone https://github.com/yourusername/embedded-linux-interfaces.git
cd embedded-linux-interfaces
```

## Dependencies

- **Linux Kernel Headers**: Required for building kernel modules.
- **GCC**: C++ compiler for building user-space applications.
- **Make**: Build tool for compiling kernel modules and applications.
- **Cross-Compiler**: If targeting an embedded platform, ensure you have the appropriate cross-compiler installed.

Install dependencies on a Debian-based system:

```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)
```

