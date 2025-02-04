/* This file is part of the dynarmic project.
 * Copyright (c) 2016 MerryMage
 * This software may be used and distributed according to the terms of the GNU
 * General Public License version 2 or any later version.
 */

#pragma once

#include "common/assert.h"

namespace Dynarmic::BackendA64 {

struct OpArg {
    OpArg() : type(Type::Operand), inner_operand() {}
    /* implicit */ OpArg(const Xbyak::Address& address) : type(Type::Address), inner_address(address) {}
    /* implicit */ OpArg(const Xbyak::Reg& reg) : type(Type::Reg), inner_reg(reg) {}

    Xbyak::Operand& operator*() {
        switch (type) {
        case Type::Address:
            return inner_address;
        case Type::Operand:
            return inner_operand;
        case Type::Reg:
            return inner_reg;
        }
        ASSERT_MSG(false, "Unreachable");
    }

    void setBit(int bits) {
        switch (type) {
        case Type::Address:
            inner_address.setBit(bits);
            return;
        case Type::Operand:
            inner_operand.setBit(bits);
            return;
        case Type::Reg:
            switch (bits) {
            case 8:
                inner_reg = inner_reg.cvt8();
                return;
            case 16:
                inner_reg = inner_reg.cvt16();
                return;
            case 32:
                inner_reg = inner_reg.cvt32();
                return;
            case 64:
                inner_reg = inner_reg.cvt64();
                return;
            default:
                ASSERT_MSG(false, "Invalid bits");
                return;
            }
        }
        ASSERT_MSG(false, "Unreachable");
    }

private:
    enum class Type {
        Operand,
        Address,
        Reg,
    };

    Type type;

    union {
        Xbyak::Operand inner_operand;
        Xbyak::Address inner_address;
        Xbyak::Reg inner_reg;
    };
};

} // namespace Dynarmic::BackendX64
