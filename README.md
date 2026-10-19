# `ember` — starter skeleton (Lab 1)

Copy this folder to a repository of your own, `git init`, and start from **M1** of
[Lab 01](../lab-01-a-box-of-bytes.md). It builds and runs as-is.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/ember
```

## Why a skeleton exists

Lab 1 is about **bytes and types**. It is not about `while` loops, splitting a
string into words, or `std::setw` — you meet those properly in Labs 4, 5 and 7.
So the parts that need them are given to you, fully written and commented. You
read those. You write the four small things that *are* Lab 1.

## Given — read it, don't rewrite it

| File | What it does |
|---|---|
| `CMakeLists.txt` | C++17, `-Wall -Wextra -Werror`, ASan + UBSan on Debug |
| `src/main.cpp` | the prompt: read a line, split it into words, call your functions |
| `src/memory.hpp` | `Byte`, `MEM_SIZE`, `struct Memory` — the box |
| `src/dump.hpp` | the two declarations |
| `src/dump.cpp` → `dump()` | the hex dump loop |

## Yours — four `TODO(lab-01)` markers

```bash
grep -rn "TODO(lab-01)" src/
```

| # | Where | The job |
|---|---|---|
| 1 | `memory.cpp` → `mem_get` | return the byte, or 0 if the address is outside the box |
| 2 | `memory.cpp` → `mem_set` | write the byte, or return `false` if the address is outside |
| 3 | `dump.cpp` → the ASCII gutter | print the character when the byte is printable |
| 4 | `dump.cpp` → `show_byte` | one byte, four views |

When all four are done:

```txt
ember> set 0 65
ember> set 1 66
ember> get 0
65  0x41  0b01000001  'A'
ember> dump
0000  41 42 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |AB..............|
```

That is M2 and M3 of Lab 1. M4 (the three deliberate breakages) is in the lab.

Until you implement `mem_set`, `set` accepts everything and stores nothing, and
`get` prints `show_byte: not implemented yet`. That is the starting state, not a
bug.

## Later labs

You keep this repository for all eight labs. Every lab adds one `else if` branch
to the dispatcher in `main.cpp` and one or two new files next to these.

---

## Українською

Скопіюйте цю теку у свій репозиторій — вона вже збирається й запускається.

Lab 1 — про **байти й типи**, а не про цикли, розбір рядка на слова чи
форматування виводу (це Labs 4, 5, 7). Тому все, що потребує ще не пройденого,
вам **дано** — з коментарями, щоб читати. Ви пишете чотири маленькі речі, які й
є Lab 1: `mem_get`, `mem_set`, ASCII-колонку в дампі та `show_byte`.

Знайти свою роботу: `grep -rn "TODO(lab-01)" src/`.

Якщо C++ бачите вперше — спочатку
[C++ за годину](../cpp-survival-kit.notes.md), потім
[інструменти й git](../setup.notes.md).



М1
Команди
alu add 0 0
alu add 128 128
alu and 7 1
alu shl 200
Результат
result=0    Z=1 N=0 C=0    (нуль → Z=1)
result=0    Z=1 N=0 C=1    (переповнення)
result=1    Z=0 N=0 C=0
result=144  Z=0 N=1 C=1    (перенос + знаковий біт)

## Трасування програми

### Програма 1: AND (A & B)

Регістри: `reg a 7`, `reg b 1`
Пам'ять: `[0x12, 0x00]` = `[AND, HALT]`

| Крок   | PC   | mem[PC]     | Що робить     | A | Z N C |
|--------|------|-------------|---------------|---|-------|
| старт  | 0000 | 0x12 (AND)  | —             | 7 | 0 0 0 |
| step 1 | 0001 | 0x00 (HALT) | A = 7 & 1 = 1 | 1 | 0 0 0 |
| step 2 | 0002 | —           | зупинка       | 1 | 0 0 0 |

7 = `0b0000_0111`, 1 = `0b0000_0001` → AND лишає тільки спільні біти → 1.

### Програма 2: три SHL (зсув, поки не з'явиться перенесення)

Регістр: `reg a 64`
Пам'ять: `[0x16, 0x16, 0x16, 0x00]` = `[SHL, SHL, SHL, HALT]`

| Крок   | PC   | mem[PC]    | A (до → після)            | A   | Z N C |
|--------|------|------------|---------------------------|-----|-------|
| старт  | 0000 | 0x16 (SHL) | —                         | 64  | 0 0 0 |
| step 1 | 0001 | 0x16 (SHL) | 0b0100_0000 → 0b1000_0000 | 128 | 0 1 0 |
| step 2 | 0002 | 0x16 (SHL) | 0b1000_0000 → 0b0000_0000 | 0   | 1 0 1 |
| step 3 | 0003 | 0x00 (HALT)| 0b0000_0000 → 0b0000_0000 | 0   | 1 0 0 |

На кроці 2 старший біт виїхав за межу байта → потрапив у `C=1`,
а результат став нульовим → `Z=1`. Саме так працює перенесення.