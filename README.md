# SysGuard

> A lightweight Linux Health & Security Auditor written in C.

![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Linux-success)
![License](https://img.shields.io/badge/License-MIT-green)

SysGuard is a command-line utility that provides system information, health monitoring, network diagnostics, security auditing, and report generation for Linux systems.

Designed as a systems programming project to demonstrate Linux internals, file parsing, and modular software development in C.

---

## Features

- System Information
  - Hostname
  - Kernel Version
  - CPU Information
  - Memory Information
  - Architecture

- Health Monitoring
  - CPU Usage
  - RAM Usage
  - Swap Usage
  - Disk Usage
  - CPU Temperature
  - Battery Status
  - Load Average

- Network Diagnostics
  - Hostname
  - Active Interface
  - IPv4 Address
  - Gateway
  - DNS Information
  - Internet Connectivity Check

- Security Audit
  - Current User Check
  - Firewall Detection
  - SSH Service Status
  - SUID File Count
  - World Writable File Check
  - Security Score

- Report Generation
  - Generate system reports
  - Save reports to the `reports/` directory

---

## Screenshots

### Main Menu

```
screenshots/menu.png
```

### System Information

```
screenshots/system-info.png
```

### Health Monitoring

```
screenshots/health-monitor.png
```

### Network Diagnostics

```
screenshots/network.png
```

### Security Audit

```
screenshots/security.png
```

### Generated Report

```
screenshots/report.png
```

---

## Project Structure

```
sysguard/
├── docs/
├── include/
├── reports/
├── screenshots/
├── src/
├── LICENSE
├── Makefile
└── README.md
```

---

## Build

Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/sysguard.git
cd sysguard
```

Compile

```bash
make
```

Run

```bash
./sysguard
```

Clean

```bash
make clean
```

---

## Technologies Used

- C (GNU11)
- POSIX APIs
- Linux `/proc`
- Linux `/sys`
- GNU Make

---

## Why this project?

This project was built to strengthen understanding of:

- Linux System Programming
- Operating System Internals
- File Parsing
- Modular C Development
- POSIX Programming
- System Monitoring
- Linux Security Basics

---

## Author

**Shaurya Singh Shekhawat**

---

## License

This project is licensed under the MIT License.