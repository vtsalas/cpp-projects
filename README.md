# C++ Projects

A collection of C++ implementations from NTUA's **Programming Techniques** course.
Each project focuses on a specific concept — from recursion and OOP to templates and dynamic memory management.

---

## 📂 Projects

### 🎮 Specker's Game
A multi-player coin game implementing a full OOP architecture.
- Abstract base class `Player` with virtual `play()` method
- Four player strategies: `GreedyPlayer`, `SpartanPlayer`, `SneakyPlayer`, `RighteousPlayer`
- `Game` and `State` classes managing full game lifecycle
- Dynamic memory management, operator overloading (`<<`)

**Concepts:** Inheritance · Polymorphism · Virtual Functions · Operator Overloading · Dynamic Memory

---

### 📚 Generic Stack
A fully generic stack implementation using C++ templates.
- Copy constructor, destructor, assignment operator
- `push()`, `pop()`, `size()`, `empty()`
- Works with `int`, `double`, `char`, and any type

**Concepts:** Templates · Dynamic Memory · Rule of Three · Operator Overloading

---

### 🌐 Browser History Simulator
Simulates browser back-navigation using a dynamic array as a stack.
- `visit()`, `back()`, `printHistory()` methods
- Manual dynamic memory allocation and deallocation

**Concepts:** Dynamic Arrays · Stack Logic · Classes · Destructor

---

### 🗼 Hanoi Towers
Classic Tower of Hanoi solved recursively.
- Prints step-by-step solution for any number of disks

**Concepts:** Recursion

---

### ➗ Rational Numbers (Baby & Full)
Two versions of a Rational Number class with full arithmetic support.
- `babyratio`: method-based arithmetic (`add`, `sub`, `mul`, `div`)
- `fullratio`: operator overloading (`+`, `-`, `*`, `/`, `<<`)
- GCD simplification, negative denominator handling

**Concepts:** Classes · Operator Overloading · Friend Functions · GCD Algorithm

---

### ❌ Tic-Tac-Toe
Two-player Tic-Tac-Toe in the terminal.
- Win and draw detection
- Input validation

**Concepts:** 2D Arrays · Functions · Game Logic

---

### 🏦 ATM Bank
Simple ATM simulation with deposit and withdrawal functionality.

**Concepts:** Functions · References · Basic I/O

---

## 🛠️ How to Run

Each file is standalone. Compile with:

```bash
g++ filename.cpp -o output
./output
```

For the Rational Number projects:
```bash
g++ fullratiotest.cpp fullratio.cpp -o fullratio
./fullratio
```

---

## 📌 Notes

These projects were written as part of NTUA's Programming Techniques coursework.
All code written and understood by me — comments in Greek reflect the learning process.
