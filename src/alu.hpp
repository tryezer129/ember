
// alu.hpp - арифметичні та логічні операції над байтами + прапорці.
#pragma once
#include <cstdint>
#include "memory.hpp"   // Byte
#include "cpu.hpp"      // Flags

// Кожна функція бере 1 або 2 байти, повертає результат (Byte)
// і виставляє прапорці Z/N/C у переданій структурі Flags&.

Byte alu_add(Byte a, Byte b, Flags& f);
Byte alu_and(Byte a, Byte b, Flags& f);
Byte alu_shl(Byte a,       Flags& f);
Byte alu_add(Byte a, Byte b, Flags& f);
Byte alu_sub(Byte a, Byte b, Flags& f);
Byte alu_and(Byte a, Byte b, Flags& f);
Byte alu_or (Byte a, Byte b, Flags& f);
Byte alu_xor(Byte a, Byte b, Flags& f);
Byte alu_not(Byte a,         Flags& f);
Byte alu_shl(Byte a,         Flags& f);
Byte alu_shr(Byte a,         Flags& f);
Byte alu_inc(Byte a,         Flags& f);
Byte alu_dec(Byte a,         Flags& f);