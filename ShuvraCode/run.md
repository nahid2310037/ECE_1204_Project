# Ticketing System in C++

This is a C++ console-based ticketing system that allows users to book **Bus, Train, and Movie tickets** with optional extra services (AC, Food, WiFi, Lounge). The program also saves buyer details in a text file and announces ticket confirmation via **Text-to-Speech**.

---

## Requirements


- Windows Speech API (`sapi.lib` and `ole32.lib`)

---

## Compile & Run


### Compile
```bash
g++ -std=c++17 main.cpp -lole32 -lsapi -o ticketing.exe
then
./ticketing.exe
