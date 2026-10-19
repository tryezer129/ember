
#include "cpu.hpp"
#include "alu.hpp"

#include <iostream>
#include <iomanip>

void step(CPU& cpu) {
    if (cpu.halted) {
        std::cout << "halted\n";
        return;
    }

    Byte op = mem_get(*cpu.mem, cpu.pc);

    // M4:
    Byte group = (op >> 4) & 0x0F;   //  зсув + маска
    Byte index = op & 0x0F;

    switch (group) {

    // 0x0_
    case 0x0:
        switch (index) {
        case 0x0:  // HALT
            cpu.halted = true;
            cpu.pc += 1;
            break;
        case 0x1:  // NOP
            cpu.pc += 1;
            break;
        default:
            cpu.pc += 1;
            break;
        }
        break;

    case 0x1:
        switch (op) {   // всередині групи зручніше за повним опкодом
        case OP_ADD: cpu.a = alu_add(cpu.a, cpu.b, cpu.f); break;
        case OP_SUB: cpu.a = alu_sub(cpu.a, cpu.b, cpu.f); break;
        case OP_AND: cpu.a = alu_and(cpu.a, cpu.b, cpu.f); break;
        case OP_OR: cpu.a = alu_or(cpu.a, cpu.b, cpu.f); break;
        case OP_XOR: cpu.a = alu_xor(cpu.a, cpu.b, cpu.f); break;
        case OP_NOT: cpu.a = alu_not(cpu.a, cpu.f); break;
        case OP_SHL: cpu.a = alu_shl(cpu.a, cpu.f); break;
        case OP_SHR: cpu.a = alu_shr(cpu.a, cpu.f); break;
        case OP_INC: cpu.a = alu_inc(cpu.a, cpu.f); break;
        case OP_DEC: cpu.a = alu_dec(cpu.a, cpu.f); break;
        default: break;
        }
        cpu.pc += 1;
        break;

    default:
        cpu.pc += 1;
        break;
    }
}

void dump_regs(const CPU& cpu) {
    std::cout << "PC=" << std::hex << std::setw(4) << std::setfill('0')
              << cpu.pc << std::dec << std::setfill(' ')
              << "  A=" << (int)cpu.a
              << "  B=" << (int)cpu.b
              << "  Z=" << cpu.f.z
              << "  N=" << cpu.f.n
              << "  C=" << cpu.f.c
              << '\n';
}
