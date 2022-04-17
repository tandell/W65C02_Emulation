#include "Bus.h"

W65C02::W65C02(double Mhz) : cycles{Mhz} {
    reset();
    using CPU = W65C02;
    opCodeMatrix.reserve(256);

    opCodeMatrix =
            {
                    {&CPU::BRK, &CPU::stackB    }, {&CPU::ORA, &CPU::zeroPageIndexedIndirect }, {&CPU::XXX, &CPU::immediate         }, {&CPU::XXX, &CPU::immediate }, {&CPU::TSB, &CPU::zeroPageB   }, {&CPU::ORA, &CPU::zeroPageA  }, {&CPU::ASL, &CPU::zeroPageB  }, {&CPU::RMB0, &CPU::zeroPageC }, {&CPU::PHP, &CPU::stackE      }, {&CPU::ORA, &CPU::immediate  }, {&CPU::ASL, &CPU::accumulator    }, {&CPU::XXX, &CPU::immediate  }, {&CPU::TSB, &CPU::absoluteB                  }, {&CPU::ORA, &CPU::absoluteA  }, {&CPU::ASL, &CPU::absoluteB  }, {&CPU::BBR0, &CPU::relativeB },
                    {&CPU::BPL, &CPU::relativeA }, {&CPU::ORA, &CPU::zeroPageIndirectIndexed }, {&CPU::ORA, &CPU::zeroPageIndirect  }, {&CPU::XXX, &CPU::immediate }, {&CPU::TRB, &CPU::zeroPageB   }, {&CPU::ORA, &CPU::zeroPageXA }, {&CPU::ASL, &CPU::zeroPageXB }, {&CPU::RMB1, &CPU::zeroPageC }, {&CPU::CLC, &CPU::impliedA    }, {&CPU::ORA, &CPU::absoluteY  }, {&CPU::INC, &CPU::accumulator    }, {&CPU::XXX, &CPU::immediate  }, {&CPU::TRB, &CPU::absoluteB                  }, {&CPU::ORA, &CPU::absoluteXA }, {&CPU::ASL, &CPU::absoluteXB }, {&CPU::BBR1, &CPU::relativeB },
                    {&CPU::JSR, &CPU::absoluteD }, {&CPU::AND, &CPU::zeroPageIndexedIndirect }, {&CPU::XXX, &CPU::immediate         }, {&CPU::XXX, &CPU::immediate }, {&CPU::BIT, &CPU::zeroPageA   }, {&CPU::AND, &CPU::zeroPageA  }, {&CPU::ROL, &CPU::zeroPageB  }, {&CPU::RMB2, &CPU::zeroPageC }, {&CPU::PLP, &CPU::stackF      }, {&CPU::AND, &CPU::immediate  }, {&CPU::ROL, &CPU::accumulator    }, {&CPU::XXX, &CPU::immediate  }, {&CPU::BIT, &CPU::absoluteA                  }, {&CPU::AND, &CPU::absoluteA  }, {&CPU::ROL, &CPU::absoluteB  }, {&CPU::BBR2, &CPU::relativeB },
                    {&CPU::BMI, &CPU::relativeA }, {&CPU::AND, &CPU::zeroPageIndirectIndexed }, {&CPU::AND, &CPU::zeroPageIndirect  }, {&CPU::XXX, &CPU::immediate }, {&CPU::BIT, &CPU::zeroPageXA  }, {&CPU::AND, &CPU::zeroPageXA }, {&CPU::ROL, &CPU::zeroPageXB }, {&CPU::RMB3, &CPU::zeroPageC }, {&CPU::SEC, &CPU::impliedA    }, {&CPU::AND, &CPU::absoluteY  }, {&CPU::DEC, &CPU::accumulator    }, {&CPU::XXX, &CPU::immediate  }, {&CPU::BIT, &CPU::absoluteXA                 }, {&CPU::AND, &CPU::absoluteXA }, {&CPU::ROL, &CPU::absoluteXB }, {&CPU::BBR3, &CPU::relativeB },
                    {&CPU::RTI, &CPU::stackC    }, {&CPU::EOR, &CPU::zeroPageIndexedIndirect }, {&CPU::XXX, &CPU::immediate         }, {&CPU::XXX, &CPU::immediate }, {&CPU::XXX, &CPU::immediate   }, {&CPU::EOR, &CPU::zeroPageA  }, {&CPU::LSR, &CPU::zeroPageB  }, {&CPU::RMB4, &CPU::zeroPageC }, {&CPU::PHA, &CPU::stackE      }, {&CPU::EOR, &CPU::immediate  }, {&CPU::LSR, &CPU::accumulator    }, {&CPU::XXX, &CPU::immediate  }, {&CPU::JMP, &CPU::absoluteC                  }, {&CPU::EOR, &CPU::absoluteA  }, {&CPU::LSR, &CPU::absoluteB  }, {&CPU::BBR4, &CPU::relativeB },
                    {&CPU::BVC, &CPU::relativeA }, {&CPU::EOR, &CPU::zeroPageIndirectIndexed }, {&CPU::EOR, &CPU::zeroPageIndirect  }, {&CPU::XXX, &CPU::immediate }, {&CPU::XXX, &CPU::immediate   }, {&CPU::EOR, &CPU::zeroPageXA }, {&CPU::LSR, &CPU::zeroPageXB }, {&CPU::RMB5, &CPU::zeroPageC }, {&CPU::CLI, &CPU::impliedA    }, {&CPU::EOR, &CPU::absoluteY  }, {&CPU::PHY, &CPU::stackE         }, {&CPU::XXX, &CPU::immediate  }, {&CPU::XXX, &CPU::immediate                  }, {&CPU::EOR, &CPU::absoluteXA }, {&CPU::LSR, &CPU::absoluteXB }, {&CPU::BBR5, &CPU::relativeB },
                    {&CPU::RTS, &CPU::stackD    }, {&CPU::ADC, &CPU::zeroPageIndexedIndirect }, {&CPU::XXX, &CPU::immediate         }, {&CPU::XXX, &CPU::immediate }, {&CPU::STZ, &CPU::zeroPageA   }, {&CPU::ADC, &CPU::zeroPageA  }, {&CPU::ROR, &CPU::zeroPageB  }, {&CPU::RMB6, &CPU::zeroPageC }, {&CPU::PLA, &CPU::stackF      }, {&CPU::ADC, &CPU::immediate  }, {&CPU::ROR, &CPU::accumulator    }, {&CPU::XXX, &CPU::immediate  }, {&CPU::JMP, &CPU::absoluteIndirect           }, {&CPU::ADC, &CPU::absoluteA  }, {&CPU::ROR, &CPU::absoluteB  }, {&CPU::BBR6, &CPU::relativeB },
                    {&CPU::BVS, &CPU::relativeA }, {&CPU::ADC, &CPU::zeroPageIndirectIndexed }, {&CPU::ADC, &CPU::zeroPageIndirect  }, {&CPU::XXX, &CPU::immediate }, {&CPU::STZ, &CPU::zeroPageXA  }, {&CPU::ADC, &CPU::zeroPageXA }, {&CPU::ROR, &CPU::zeroPageXB }, {&CPU::RMB7, &CPU::zeroPageC }, {&CPU::SEI, &CPU::impliedA    }, {&CPU::ADC, &CPU::absoluteY  }, {&CPU::PLY, &CPU::stackF         }, {&CPU::XXX, &CPU::immediate  }, {&CPU::JMP, &CPU::absoluteIndexedIndirect    }, {&CPU::ADC, &CPU::absoluteXA }, {&CPU::ROR, &CPU::absoluteXB }, {&CPU::BBR7, &CPU::relativeB },
                    {&CPU::BRA, &CPU::relativeA }, {&CPU::STA, &CPU::zeroPageIndexedIndirect }, {&CPU::XXX, &CPU::immediate         }, {&CPU::XXX, &CPU::immediate }, {&CPU::STY, &CPU::zeroPageA   }, {&CPU::STA, &CPU::zeroPageA  }, {&CPU::STX, &CPU::zeroPageA  }, {&CPU::SMB0, &CPU::zeroPageC }, {&CPU::DEY, &CPU::impliedA    }, {&CPU::BIT, &CPU::immediate  }, {&CPU::TXA, &CPU::impliedA      }, {&CPU::XXX, &CPU::immediate  }, {&CPU::STY, &CPU::absoluteA                  }, {&CPU::STA, &CPU::absoluteA  }, {&CPU::STX, &CPU::absoluteA  }, {&CPU::BBS0, &CPU::relativeB},
                    {&CPU::BCC, &CPU::relativeA }, {&CPU::STA, &CPU::zeroPageIndirectIndexed }, {&CPU::STA, &CPU::zeroPageIndirect  }, {&CPU::XXX, &CPU::immediate }, {&CPU::STY, &CPU::zeroPageXA  }, {&CPU::STA, &CPU::zeroPageXA }, {&CPU::STX, &CPU::zeroPageY  }, {&CPU::SMB1, &CPU::zeroPageC }, {&CPU::TYA, &CPU::impliedA    }, {&CPU::STA, &CPU::absoluteY  }, {&CPU::TXS, &CPU::impliedA       }, {&CPU::XXX, &CPU::immediate  }, {&CPU::STZ, &CPU::absoluteA                  }, {&CPU::STA, &CPU::absoluteXA }, {&CPU::STZ, &CPU::absoluteXA }, {&CPU::BBS1, &CPU::relativeB },
                    {&CPU::LDY, &CPU::immediate }, {&CPU::LDA, &CPU::zeroPageIndexedIndirect }, {&CPU::LDX, &CPU::immediate         }, {&CPU::XXX, &CPU::immediate }, {&CPU::LDY, &CPU::zeroPageA   }, {&CPU::LDA, &CPU::zeroPageA  }, {&CPU::LDX, &CPU::zeroPageA  }, {&CPU::SMB2, &CPU::zeroPageC }, {&CPU::TAY, &CPU::impliedA    }, {&CPU::LDA, &CPU::immediate  }, {&CPU::TAX, &CPU::impliedA      }, {&CPU::XXX, &CPU::immediate  }, {&CPU::LDY, &CPU::absoluteA                  }, {&CPU::LDA, &CPU::absoluteA  }, {&CPU::LDX, &CPU::absoluteA  }, {&CPU::BBS2, &CPU::relativeB },
                    {&CPU::BCS, &CPU::relativeA }, {&CPU::LDA, &CPU::zeroPageIndirectIndexed }, {&CPU::LDA, &CPU::zeroPageIndirect  }, {&CPU::XXX, &CPU::immediate }, {&CPU::LDY, &CPU::zeroPageXA  }, {&CPU::LDA, &CPU::zeroPageXA }, {&CPU::LDX, &CPU::zeroPageY  }, {&CPU::SMB3, &CPU::zeroPageC }, {&CPU::CLV, &CPU::impliedA    }, {&CPU::LDA, &CPU::absoluteY  }, {&CPU::TSX, &CPU::impliedA       }, {&CPU::XXX, &CPU::immediate  }, {&CPU::LDY, &CPU::absoluteXA                 }, {&CPU::LDA, &CPU::absoluteXA }, {&CPU::LDX, &CPU::absoluteY  }, {&CPU::BBS3, &CPU::relativeB },
                    {&CPU::CPY, &CPU::immediate }, {&CPU::CMP, &CPU::zeroPageIndexedIndirect }, {&CPU::XXX, &CPU::zeroPageIndirect  }, {&CPU::XXX, &CPU::immediate }, {&CPU::CPY, &CPU::zeroPageA   }, {&CPU::CMP, &CPU::zeroPageA  }, {&CPU::DEC, &CPU::zeroPageB  }, {&CPU::SMB4, &CPU::zeroPageC }, {&CPU::INY, &CPU::impliedA    }, {&CPU::CMP, &CPU::immediate  }, {&CPU::DEX, &CPU::impliedA       }, {&CPU::WAI, &CPU::immediate  }, {&CPU::CPY, &CPU::absoluteA                  }, {&CPU::CMP, &CPU::absoluteA  }, {&CPU::DEC, &CPU::absoluteB  }, {&CPU::BBS4, &CPU::relativeB },
                    {&CPU::BNE, &CPU::relativeA }, {&CPU::CMP, &CPU::zeroPageIndirectIndexed }, {&CPU::CMP, &CPU::zeroPageIndirect  }, {&CPU::XXX, &CPU::immediate }, {&CPU::XXX, &CPU::immediate   }, {&CPU::CMP, &CPU::zeroPageXA }, {&CPU::DEC, &CPU::zeroPageXB }, {&CPU::SMB5, &CPU::zeroPageC }, {&CPU::CLD, &CPU::impliedA    }, {&CPU::CMP, &CPU::absoluteY  }, {&CPU::PHX, &CPU::stackE         }, {&CPU::STP, &CPU::immediate  }, {&CPU::XXX, &CPU::immediate                  }, {&CPU::CMP, &CPU::absoluteXA }, {&CPU::DEC, &CPU::absoluteXB }, {&CPU::BBS5, &CPU::relativeB },
                    {&CPU::CPX, &CPU::immediate }, {&CPU::SBC, &CPU::zeroPageIndexedIndirect }, {&CPU::XXX, &CPU::immediate         }, {&CPU::XXX, &CPU::immediate }, {&CPU::CPX, &CPU::zeroPageA   }, {&CPU::SBC, &CPU::zeroPageA  }, {&CPU::INC, &CPU::zeroPageB  }, {&CPU::SMB6, &CPU::zeroPageC }, {&CPU::INX, &CPU::impliedA    }, {&CPU::SBC, &CPU::immediate  }, {&CPU::NOP, &CPU::impliedA       }, {&CPU::XXX, &CPU::immediate  }, {&CPU::CPX, &CPU::absoluteA                  }, {&CPU::SBC, &CPU::absoluteA  }, {&CPU::INC, &CPU::absoluteB  }, {&CPU::BBS6, &CPU::relativeB },
                    {&CPU::BEQ, &CPU::relativeA }, {&CPU::SBC, &CPU::zeroPageIndirectIndexed }, {&CPU::SBC, &CPU::zeroPageIndirect  }, {&CPU::XXX, &CPU::immediate }, {&CPU::XXX, &CPU::immediate   }, {&CPU::SBC, &CPU::zeroPageXA }, {&CPU::INC, &CPU::zeroPageXB }, {&CPU::SMB7, &CPU::zeroPageC }, {&CPU::SED, &CPU::impliedA    }, {&CPU::SBC, &CPU::absoluteY  }, {&CPU::PLX, &CPU::stackF         }, {&CPU::XXX, &CPU::immediate  }, {&CPU::XXX, &CPU::immediate                  }, {&CPU::SBC, &CPU::absoluteXA }, {&CPU::INC, &CPU::absoluteXB }, {&CPU::BBS7, &CPU::relativeB },
            };
}

/**
 * Connects the cpu to a bus by setting this->bus to the Bus* passed in
 * @param b Pointer to Bus which the cpu is to be linked to
 */
void W65C02::connectBus(Bus *b) {
    this->bus = b;
}

/**
 * resets the cpu by setting PC to 0xFFFE, SP to 0xFF, PS to 0x00, and A, X, and Y registers to 0x00
 * @param pc the value to set the PC. Default value of 0xFFFE.
 */
void W65C02::reset(word pc) {
    PC = pc;
    SP = 0xFF;
    PS.reset();
    PS.set(StatusFlags::U);
    PS.set(StatusFlags::B);
    PS.set(StatusFlags::I);
    A = X = Y = 0;
}

/**
 * Increments this->cycles and reads a byte from the bus
 * @param address The address to read from
 * @return The value at the given address
 */
byte W65C02::readByte(word address) {
    CyclesIncrementer cd(cycles);
    return bus->read(address);
}

/**
 * Calls {@link W65C02}
 * @param address
 * @return
 */
word W65C02::readWord(word address) {
    word data = readByte(address);
    return data | (readByte(address + 1) << 8);
}

byte W65C02::fetchByte() {
    return readByte(PC++);
}

word W65C02::fetchWord() {
    word data = fetchByte();
    return data | (fetchByte() << 8);
}

void W65C02::writeWord(word data, word address) {
    writeByte(data & 0xFF, address);
    writeByte(data >> 8, address + 1);
}

void W65C02::writeByte(byte data, word address) {
    bus->write(data, address);
    ++cycles;
}

void W65C02::bitInstructionSetStatus(byte value, bool immediateMode) {
    if(immediateMode) {
        PS.set(StatusFlags::Z, value == 0);
    }
    NZVSetStatus(value);

}

void W65C02::pushByteToStack(byte data) {
    writeByte(data, SPToAddress());
    --SP;
}

void W65C02::pushWordToStack(word data) {
    pushByteToStack((data & 0xFF00) >> 8);  //PCH
    return pushByteToStack(data); //PCL
}

byte W65C02::pullByteFromStack() {
    byte data = readByte(SPToAddress());
    ++SP;
    return data;
}

byte W65C02::readByteFromStack() {
    return readByte(SPToAddress());
}

word W65C02::SPToAddress() const {
    return 0x100 | SP;
}

/**
 * Computes the immediate address for the following instructions:
 * LDY, CPY, CPX, LDX, ORA, AND, EOR, ADC, BIT, LDA, CMP, SBC
 * @return The immediate address
 */
word W65C02::immediate(byte W65C02::*, const std::function<byte(byte)>&) {
    return fetchByte();
}

/**
 * Computes the absolute address for the following instructions:
 * BIT, STY, STZ, LSY, CPY, CPX, STX, LDX, ORA, AND, EOR, ADC, STA, LDA, CMP, SBC
 * @param Register The register that the data at computed address will be writen to
 * @return The data at computed address if instruction is a read instruction or 0
 * which is a filler value if the instruction is a write instruction
 */
word W65C02::absoluteA(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    word address{fetchWord()};
    if(Register) {
        writeByte(this->*Register, address);
        return 0;
    } return readByte(address);
}

word W65C02::absoluteB(byte W65C02::*, const std::function<byte(byte)>& op) {
    word address{fetchWord()};
    byte data{readByte(address)};
    readByte(address);
    writeByte(op(data), address);
    return 0;
}

/**
 * Computes the absolute address for the following instruction:
 * JMP
 * @return The absolute address which will be the new PC
 */
word W65C02::absoluteC(byte W65C02::*, const std::function<byte(byte)>& op) {
    return fetchWord();
}

/**
 * Computes the absolute address for the following instruction:
 * JSR
 * @return The absolute address which will be the new PC
 */
word W65C02::absoluteD(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    byte subAddrLow = fetchByte();
    readByte(SPToAddress());
    pushWordToStack(PC);
    return (fetchByte() << 8) | subAddrLow;
}

/**
 * Computes the zero page address for the following instructions:
 * BIT, STZ, STY, LDY, CPY, CPX, STX, LDX, ORA, AND, EOR, ADC, STA, LDA, CMP, SBC
 * @param Register The register that the data at computed address will be writen to
 * @return The data at computed address if instruction is a read instruction or 0
 * which is a filler value if the instruction is a write instruction
 */
word W65C02::zeroPageA(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    byte zeroPage{fetchByte()};
    if(Register) {
        writeByte(this->*Register, zeroPage);
        return 0;
    } return readByte(zeroPage);
}

word W65C02::zeroPageB(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    byte zeroPage{fetchByte()};
    byte data{readByte(zeroPage)};
    readByte(zeroPage);
    writeByte(op(data), zeroPage);
    return 0;
}

word W65C02::zeroPageC(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    byte zeroPage{fetchByte()};
    byte data{readByte(zeroPage)};
    readByte(zeroPage);
    writeByte(op(data), zeroPage);
    return 0;
}

word W65C02::accumulator(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    this->*Register = op(this->*Register);
    return readByte(PC);
}

/**
 * Computes the implied address for the following instructions:
 * DEY, INY, INX, DEX, NOP, TYA, TAY, TXA, TXS, TAX, CLC, SEC, CLI, SEI, CLV, CLD, SED
 * @return
 */
word W65C02::impliedA(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    return readByte(PC);
}

//TODO - wait for interupt
word W65C02::impliedB(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    return 0;
}

//TODO - stop the clock
word W65C02::impliedC(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    return 0;
}

word W65C02::zeroPageIndirectIndexed(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    byte zpAddress = fetchByte();
    word address = readByte(zpAddress) | (readByte(static_cast<byte>(zpAddress + 1)) << 8);
    if(((address & 0xFF) + Y) > 0xFF and !Register)
        readByte(static_cast<byte>(zpAddress + 1));
    if(Register) {
        readByte(static_cast<byte>(zpAddress + 1));
        writeByte(this->*Register, address + Y);
        return 0;
    } return readByte(address + Y);
}

word W65C02::zeroPageIndexedIndirect(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    byte zeroPage{readByte(PC)};
    fetchByte();
    word effectiveAddress = readByte(static_cast<byte>(zeroPage + X)) | (readByte(static_cast<byte>(zeroPage + X + 1)) << 8);
    if(Register) {
        writeByte(this->*Register, effectiveAddress);
        return 0;
    } return readByte(effectiveAddress);
}

word W65C02::zeroPageXA(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    byte address{fetchByte()};
    byte effectiveAddress = address + X;
    readByte(PC - 1);
    if(Register) {
        writeByte(this->*Register, effectiveAddress);
        return 0;
    } return readByte(effectiveAddress);
}

word W65C02::zeroPageXB(byte W65C02::*, const std::function<byte(byte)>& op) {
    byte zeroPage{readByte(PC)};
    byte effectiveAddress = zeroPage + X;
    fetchByte();
    byte data{readByte(effectiveAddress)};
    readByte(effectiveAddress);
    writeByte(op(data), effectiveAddress);
    return 0;
}

word W65C02::zeroPageY(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    byte address{fetchByte()};
    byte effectiveAddress = address + Y;
    readByte(PC - 1);
    cycles += (address + Y > 0xFF);
    if(Register) {
        writeByte(this->*Register, effectiveAddress);
        return 0;
    } else return readByte(effectiveAddress);
}

word W65C02::absoluteXA(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    word address = fetchWord();
    dword effectiveAddress = address + X;
    if(Register) {
        if(((address & 0xFF) + X) > 0xFF) {
            readByte(PC - 1);
            writeByte(this->*Register, effectiveAddress);
        } else {
            readByte(effectiveAddress);
            writeByte(this->*Register, effectiveAddress);
        }
    }
    else if(((address & 0xFF) + X) > 0xFF) {
        readByte(PC - 1);
        return readByte(effectiveAddress);
    } else return readByte(effectiveAddress);
    return 0;
}

word W65C02::absoluteXB(byte W65C02::*, const std::function<byte(byte)>& op) {
    auto ins = opcode.instruction;
    word address{fetchWord()};
    word effectiveAddress = address + X;
    if(((address & 0xFF) + X) > 0xFF)
        readByte(PC - 1);
    else if(ins != &W65C02::ASL && ins != &W65C02::LSR && ins != &W65C02::ROL && ins != &W65C02::ROR)
        readByte(effectiveAddress);
    readByte(effectiveAddress);
    byte data{readByte(effectiveAddress)};
    writeByte(op(data), effectiveAddress);
    return 0;
}

word W65C02::absoluteY(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    word address = fetchWord();
    dword effectiveAddress = address + Y;
    if(Register) {
        if(((address & 0xFF) + Y) > 0xFF) {
            readByte(PC - 1);
            writeByte(this->*Register, effectiveAddress);
        } else {
            readByte(effectiveAddress);
            writeByte(this->*Register, effectiveAddress);
        }
    }
    else if(((address & 0xFF) + Y) > 0xFF) {
        readByte(PC - 1);
        return readByte(effectiveAddress);
    } else return readByte(effectiveAddress);
    return 0;
}

word W65C02::relativeA(byte W65C02::*, const std::function<byte(byte)>& op) {
    byte value{fetchByte()};
    if(op(0)) {     //Then we should branch. the value passed to op is garbage. It isn't needed.
        readByte(PC);
        auto svalue = (sbyte)value;
        if((PC & 0xFF) + svalue < 0 || (PC & 0xFF) + svalue > 0xFF)
            readByte(PC);
        return PC + svalue;
    }
    return PC;
}

//TODO - test the correctness of this function it is gautenteed to be wrong.
word W65C02::relativeB(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    byte value{fetchByte()};
    byte zeroPage{fetchByte()};
    readByte(zeroPage);
    readByte(zeroPage);
    readByte(zeroPage);
    if(op(0)) {     //Then we should branch. the value passed to op is garbage. It isn't needed.
        readByte(PC);
        auto svalue = (sbyte)value;
        if((PC & 0xFF) + svalue < 0 || (PC & 0xFF) + svalue > 0xFF)
            readByte(PC);
        return PC + svalue;
    }
    return PC;
}

word W65C02::absoluteIndirect(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    word address{fetchWord()};
    readByte(--PC);
    return readByte(address) | (readByte(address + 1) << 8);
}

word W65C02::stackA(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    readByte(PC);
    readByte(PC);
    pushWordToStack(SPToAddress());
    return 0;
}

word W65C02::stackB(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    return 0;
}

word W65C02::stackC(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    return 0;
}

word W65C02::stackD(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    readByte(PC);
    pullByteFromStack();
    byte PCL = pullByteFromStack();
    byte PCH = readByteFromStack();
    PC = (PCH << 8) | PCL;
    readByte(PC);
    return PC + 1;
}

word W65C02::stackE(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    readByte(PC);
    pushByteToStack(this->*Register);
    return 0;
}

word W65C02::stackF(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    readByte(PC);
    pullByteFromStack();
    return readByte(SPToAddress());
}

word W65C02::absoluteIndexedIndirect(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    word address{fetchWord()};
    readByte(--PC);
    return readByte(address + X) | (readByte(address + X + 1) << 8);
}

word W65C02::zeroPageIndirect(byte W65C02::* Register, const std::function<byte(byte)>& op) {
    byte ZPAddr = fetchByte();
    word effectiveAddress = readByte(ZPAddr) | (readByte((byte)(ZPAddr + 1)) << 8);
    if(Register) {
        writeByte(this->*Register, effectiveAddress);
        return 0;
    } else return readByte(effectiveAddress);
}

void W65C02::execute(uint64_t numInstructionsToExecute) {
    while(numInstructionsToExecute--) {
        opcode = opCodeMatrix[fetchByte()];
        (this->*(opcode.instruction))(opcode.addrMode);
    }
}

void W65C02::ADC(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    byte value = (this->*addrMode)(nullptr, nullptr);
    word result = (word)A + (word)value + (word)PS.test(StatusFlags::C);
    bool SB1 = A >> SIGN_BIT_POS, SB2 = value >> SIGN_BIT_POS, SBR = (result & SIGN_BIT_MASK) >> SIGN_BIT_POS;
    PS.set(StatusFlags::V, !(SB1 ^ SB2) && (SB2 ^ SBR));
    PS.set(StatusFlags::C, result >> CARRY_BIT_POS);
    loadRegister(A, (byte)(result & MAX_BYTE));
}

void W65C02::AND(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    loadRegister(A, A & (this->*addrMode)(nullptr, nullptr));
}

void W65C02::ASL(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::A, [this](byte a) {
        PS.set(StatusFlags::C, a & 0X80);
        NZSetStatus(a << 1);
        return a << 1;
    });
}

void W65C02::BBR0(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return !(data & 0b00000001);
    });
}

void W65C02::BBR1(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return !(data & 0b00000010);
    });
}

void W65C02::BBR2(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return !(data & 0b00000100);
    });
}

void W65C02::BBR3(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return !(data & 0b00001000);
    });
}

void W65C02::BBR4(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return !(data & 0b00010000);
    });
}

void W65C02::BBR5(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return !(data & 0b00100000);
    });
}

void W65C02::BBR6(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return !(data & 0b01000000);
    });
}

void W65C02::BBR7(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return !(data & 0b10000000);
});

}

void W65C02::BBS0(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return (data & 0b00000001);
    });
}

void W65C02::BBS1(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return (data & 0b00000010);
    });
}

void W65C02::BBS2(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return (data & 0b00000100);
    });
}

void W65C02::BBS3(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return (data & 0b00001000);
    });
}

void W65C02::BBS4(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return (data & 0b00010000);
    });
}

void W65C02::BBS5(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return (data & 0b00100000);
    });
}

void W65C02::BBS6(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return (data & 0b01000000);
    });
}

void W65C02::BBS7(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte data) {
        return (data & 0b10000000);
    });
}

void W65C02::BCC(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [this](byte) {
        return !PS.test(StatusFlags::C);    //return true for should branch false otherwise
    });
}

void W65C02::BCS(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [this](byte) {
        return PS.test(StatusFlags::C) ? 1 : 0;    //return true for should branch false otherwise
    });
}

void W65C02::BEQ(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [this](byte) {
        return PS.test(StatusFlags::Z);    //return true for should branch false otherwise
    });
}

void W65C02::BIT(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    byte memVal = (this->*addrMode)(nullptr, nullptr);
    byte result = A & memVal;
    PS.set(StatusFlags::Z, result == 0);
    if(addrMode != &W65C02::immediate) {
        PS.set(StatusFlags::N, (bool)(memVal & 0x80));
        PS.set(StatusFlags::V, (bool)(memVal & 0x40));
    }
}

void W65C02::BMI(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [this](byte) {
        return PS.test(StatusFlags::N);    //return true for should branch false otherwise
    });
}

//I dont dare to say that this is clean code. This is dirty code but sometimes if you try to find the ultimate
//solution to every problem you spin your wheels for ages. It works. The end.
void W65C02::BNE(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [this](byte) {
        return !PS.test(StatusFlags::Z);    //return true for should branch false otherwise
    });
}

void W65C02::BPL(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [this](byte) {
        return !PS.test(StatusFlags::N);    //return true for should branch false otherwise
    });
}

void W65C02::BRA(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [](byte) {
        return 1;    //branch always
    });
}

void W65C02::BRK(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {

}

void W65C02::BVC(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [this](byte) {
        return !PS.test(StatusFlags::V);    //return true for should branch false otherwise
    });
}

void W65C02::BVS(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, [this](byte) {
        return PS.test(StatusFlags::V);    //return true for should branch false otherwise
    });
}

void W65C02::CLC(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    PS.reset(StatusFlags::C);
}

void W65C02::CLD(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    PS.reset(StatusFlags::D);
}

void W65C02::CLI(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    PS.reset(StatusFlags::I);
}

void W65C02::CLV(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    PS.reset(StatusFlags::V);
}

void W65C02::CMP(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    byte value = (this->*addrMode)(nullptr, nullptr);
    PS.set(StatusFlags::C, A >= value);
    PS.set(StatusFlags::Z, A == value);
    PS.set(StatusFlags::N, ((byte)(A - value)) >> 7);
}

void W65C02::CPX(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    byte value = (this->*addrMode)(nullptr, nullptr);
    PS.set(StatusFlags::C, X >= value);
    PS.set(StatusFlags::Z, X == value);
    PS.set(StatusFlags::N, ((byte)(X - value)) >> 7);
}

void W65C02::CPY(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    byte value = (this->*addrMode)(nullptr, nullptr);
    PS.set(StatusFlags::C, Y >= value);
    PS.set(StatusFlags::Z, Y == value);
    PS.set(StatusFlags::N, ((byte)(Y - value)) >> 7);
}

void W65C02::DEC(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::A, [this](byte a) {
        NZSetStatus(a - 1);
        return a - 1;
    });
}

void W65C02::DEX(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    loadRegister(X, X - 1);
}

void W65C02::DEY(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    loadRegister(Y, Y - 1);
}

void W65C02::EOR(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    loadRegister(A, A ^ (this->*addrMode)(nullptr, nullptr));
}

void W65C02::INC(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::A, [this](byte a) {
        NZSetStatus(a + 1);
        return a + 1;
    });
}

void W65C02::INX(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    loadRegister(X, X + 1);
}

void W65C02::INY(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    loadRegister(Y, Y + 1);
}

void W65C02::JMP(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, nullptr);
}

void W65C02::JSR(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, nullptr);
}

void W65C02::LDA(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    loadRegister(A, (this->*addrMode)(nullptr, nullptr));
}

void W65C02::LDX(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    loadRegister(X, (this->*addrMode)(nullptr, nullptr));
}

void W65C02::LDY(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    loadRegister(Y, (this->*addrMode)(nullptr, nullptr));
}

void W65C02::LSR(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::A, [this](byte a) {
        PS.set(StatusFlags::C, a & 0x01);
        NZSetStatus(a >> 1);
        return a >> 1;
    });
}

void W65C02::NOP(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    readByte(PC);
}

void W65C02::ORA(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    loadRegister(A, A | (this->*addrMode)(nullptr, nullptr));
}

void W65C02::PHA(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::A, nullptr);
}

void W65C02::PHP(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PS.set(StatusFlags::B);
    PS_byte = PS.to_ulong();
    (this->*addrMode)(&W65C02::PS_byte, nullptr);
}

void W65C02::PHX(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::X, nullptr);
}

void W65C02::PHY(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::Y, nullptr);
}

void W65C02::PLA(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    loadRegister(A, (this->*addrMode)(nullptr, nullptr));
}

void W65C02::PLP(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PS = (this->*addrMode)(nullptr, nullptr);
}

void W65C02::PLX(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    loadRegister(X, (this->*addrMode)(nullptr, nullptr));
}

void W65C02::PLY(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    loadRegister(Y, (this->*addrMode)(nullptr, nullptr));
}

void W65C02::RMB0(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a & 0b11111110;
    });
}

void W65C02::RMB1(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a & 0b11111101;
    });
}

void W65C02::RMB2(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a & 0b11111011;
    });
}

void W65C02::RMB3(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a & 0b11110111;
    });
}

void W65C02::RMB4(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a & 0b11101111;
    });
}

void W65C02::RMB5(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a & 0b11011111;
    });
}

void W65C02::RMB6(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a & 0b10111111;
    });
}

void W65C02::RMB7(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a & 0b01111111;
    });
}

void W65C02::ROL(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::A, [this](byte a) {
        byte result = (a << 1) | PS.test(StatusFlags::C);
        PS.set(StatusFlags::C, a & 0X80);
        NZSetStatus(result);
        return result;
    });
}

void W65C02::ROR(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::A, [this](byte a) {
        byte result = (a >> 1) | (PS.test(StatusFlags::C) << SIGN_BIT_POS);
        PS.set(StatusFlags::C, a & 0x01);
        NZSetStatus(result);
        return result;
    });
}

void W65C02::RTI(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {

}

void W65C02::RTS(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    PC = (this->*addrMode)(nullptr, nullptr);
}

void W65C02::SBC(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    byte value = (this->*addrMode)(nullptr, nullptr);
    word result = (word)A + (word)~value + (word)(PS.test(StatusFlags::C));
    bool SB1 = A >> SIGN_BIT_POS, SB2 = value >> SIGN_BIT_POS, SBR = (result & SIGN_BIT_MASK) >> SIGN_BIT_POS;
    PS.set(StatusFlags::V, (SB1 ^ SB2) && !(SB2 ^ SBR));
    PS.set(StatusFlags::C, !(result >> CARRY_BIT_POS));
    loadRegister(A, (byte)(result & MAX_BYTE));
}

void W65C02::SEC(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    PS.set(StatusFlags::C);
}

void W65C02::SED(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    PS.set(StatusFlags::D);
}

void W65C02::SEI(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    PS.set(StatusFlags::I);
}

void W65C02::SMB0(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a | 0b00000001;
    });
}

void W65C02::SMB1(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a | 0b00000010;
    });
}

void W65C02::SMB2(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a | 0b00000100;
    });
}

void W65C02::SMB3(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a | 0b00001000;
    });
}

void W65C02::SMB4(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a | 0b00010000;
    });
}

void W65C02::SMB5(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a | 0b00100000;
    });
}

void W65C02::SMB6(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a | 0b01000000;
    });
}

void W65C02::SMB7(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, [](byte a) {
        return a | 0b10000000;
    });
}

void W65C02::STA(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::A, nullptr);
}

void W65C02::STP(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {

}

void W65C02::STX(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::X, nullptr);
}

void W65C02::STY(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::Y, nullptr);
}

void W65C02::STZ(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::ZERO, nullptr);
}

void W65C02::TAX(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    loadRegister(X, A);
}

void W65C02::TAY(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    loadRegister(Y, A);
}

void W65C02::TRB(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::A, [this](byte a) {
        PS.set(StatusFlags::Z, (A & a) == 0);
        return ~A & a;
    });
}

void W65C02::TSB(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(&W65C02::A, [this](byte a) {
        PS.set(StatusFlags::Z, (A & a) == 0);
        return A | a;
    });
}

void W65C02::TSX(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    loadRegister(X, SP);
}

void W65C02::TXA(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    loadRegister(A, X);
}

void W65C02::TXS(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    SP = X;
}

void W65C02::TYA(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    (this->*addrMode)(nullptr, nullptr);
    loadRegister(A, Y);
}

void W65C02::WAI(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {

}

void W65C02::XXX(word (W65C02::* addrMode)(byte W65C02::*, const std::function<byte(byte)>&)) {
    //NOP(addrMode);
    exit(-1);
}

void W65C02::NZSetStatus(byte value) {
    PS.set(StatusFlags::Z, value == 0);
    PS.set(StatusFlags::N , value >> SIGN_BIT_POS);
}

void W65C02::NZCSetStatus(byte value) {
    NZSetStatus(value);
    PS.set(StatusFlags::C, value >> CARRY_BIT_POS);
}

void W65C02::NZVSetStatus(byte value) {
    PS.set(StatusFlags::Z, value == 0);
    PS.set(StatusFlags::N , value >> SIGN_BIT_POS);
    PS.set(StatusFlags::V, (value & OVERFLOW_BIT_MASK) >> OVERFLOW_BIT_POS);
}

void W65C02::loadRegister(byte& Register, byte value) {
    Register = value;
    NZSetStatus(value);
}

void W65C02::setCycleDuration(double Mhz) {
    cycles.setCycleDuration(Mhz);
}





