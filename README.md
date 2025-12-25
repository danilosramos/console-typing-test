# ⌨️ Console Typing Speed Test

> A lightweight, cross-platform CLI tool to benchmark typing speed and accuracy in real-time using **Modern C++**.

![C++](https://img.shields.io/badge/Language-C++17-00599C?style=for-the-badge&logo=c%2B%2B)
![Platform](https://img.shields.io/badge/Platform-Windows%20|%20Linux%20|%20macOS-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

## 📖 About the Project

This project is a **Command Line Interface (CLI)** application designed to measure a user's typing performance. Unlike simple input scripts, this tool features a **real-time engine** that tracks keystrokes as they happen, providing immediate visual feedback (Green/Red highlighting) and calculating metrics like **Words Per Minute (WPM)** and **Accuracy (%)** with high precision.

It demonstrates proficiency in **C++ Standard Template Library (STL)**, precise time measurement using `std::chrono`, and cross-platform development techniques.

## 🚀 Key Features

* **⚡ Real-Time Feedback:** The interface updates instantly after every word, highlighting correct words in **Green** and incorrect ones in **Red**.
* **⏱️ High-Precision Timing:** Uses `std::chrono::steady_clock` to calculate WPM down to the millisecond, ensuring fair and accurate results.
* **💻 Cross-Platform Compatibility:** The code detects the operating system (Windows via `_WIN32` or Unix-like) to handle system-specific commands like screen clearing (`cls` vs `clear`) and sleep functions (`Sleep` vs `usleep`).
* **📊 Detailed Statistics:** Displays a comprehensive report at the end, including total time, error count, final WPM, and accuracy percentage.

## 🛠️ Technologies Used

* **Language:** C++ (C++11/17)
* **Libraries:**
    * `<chrono>`: For measuring elapsed time.
    * `<vector>` & `<string>`: For efficient text processing.
    * `<iomanip>`: For formatting the output metrics.
    * System Calls: For console management.

## ⚙️ How to Run

### Prerequisites
You need a C++ compiler installed (like **g++**, **clang**, or **MSVC**).

### Compilation
Open your terminal in the project folder and run:

```bash
g++ console-typing-test.cpp -o typing-test
```

Execution
On Linux/macOS:
```bash
./typing-test
```

On Linux/macOS:
```bash
typing-test.exe
```

## 🧩 Code Logic
### The core logic is encapsulated in the `TypingTest` class:

1. Initialization: Loads the reference text into a vector.

2. Game Loop: * Captures user input word by word.

- Compares input against the reference.

- Clears the screen and redraws the text with color coding (ANSI codes) to show progress.

3. Calculation: * WPM: `(Words Typed / Time Elapsed in Minutes)`

- Accuracy: `((Total Words - Errors) / Total Words) * 100`
