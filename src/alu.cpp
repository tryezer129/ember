//
// Created by user on 18.10.2026.
//
// alu.cpp — реалізація операцій ALU.
#include "alu.hpp"

// Допоміжна: виставити Z і N за результатом.
// Z — результат нульовий, N — старший біт результату одиниця.
static void set_zn(Byte r, Flags& f) {
    f.z = (r == 0);
    f.n = (r & 0x80) != 0;
}

Byte alu_add(Byte a, Byte b, Flags& f) {
    // Рахуємо у ширшому типі, щоб побачити перенесення.
    unsigned sum = (unsigned)a + (unsigned)b;
    Byte r = (Byte)sum;          // обрізаємо до байта
    f.c = (sum > 0xFF);          // було перенесення за межу восьми?
    set_zn(r, f);
    return r;
}

Byte alu_and(Byte a, Byte b, Flags& f) {
    Byte r = a & b;
    f.c = false;                 // AND не дає перенесення
    set_zn(r, f);
    return r;
}

Byte alu_shl(Byte a, Flags& f) {
    // Старший біт виїжджає вправо → у C.
    f.c = (a & 0x80) != 0;
    Byte r = (Byte)(a << 1);     // a << 1 лишаємо в байті
    set_zn(r, f);
    return r;
}
Byte alu_sub(Byte a, Byte b, Flags& f) {
    unsigned diff = (unsigned)a - (unsigned)b;
    Byte r = (Byte)diff;
    f.c = (a < b);               // позика: C якщо a менше b
    set_zn(r, f);
    return r;
}

Byte alu_or(Byte a, Byte b, Flags& f) {
    Byte r = a | b;
    f.c = false;                 // логіка не дає перенесення
    set_zn(r, f);
    return r;
}

Byte alu_xor(Byte a, Byte b, Flags& f) {
    Byte r = a ^ b;
    f.c = false;
    set_zn(r, f);
    return r;
}

Byte alu_not(Byte a, Flags& f) {
    Byte r = ~a;                 // перевернути всі біти
    f.c = false;
    set_zn(r, f);
    return r;
}

Byte alu_shr(Byte a, Flags& f) {
    f.c = (a & 0x01) != 0;       // молодший біт виїжджає → C
    Byte r = (Byte)(a >> 1);
    set_zn(r, f);
    return r;
}

Byte alu_inc(Byte a, Flags& f) {
    Byte r = (Byte)(a + 1);
    // C НЕ чіпаємо! (ISA §5: INC виставляє тільки Z N)
    set_zn(r, f);
    return r;
}

Byte alu_dec(Byte a, Flags& f) {
    Byte r = (Byte)(a - 1);
    // C НЕ чіпаємо!
    set_zn(r, f);
    return r;
}
