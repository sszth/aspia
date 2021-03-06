//
// Aspia Project
// Copyright (C) 2020 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef BASE__CPUID_UTIL_H
#define BASE__CPUID_UTIL_H

#include "build/build_config.h"

#if defined(ARCH_CPU_X86_FAMILY)

#include <cstdint>
#if !defined(CC_MSVC)
#include <climits>
#endif

namespace base {

class CpuidUtil
{
public:
    CpuidUtil() = default;
    explicit CpuidUtil(int leaf) { get(leaf); }
    CpuidUtil(int leaf, int subleaf) { get(leaf, subleaf); }
    virtual ~CpuidUtil() = default;

    CpuidUtil(const CpuidUtil& other);
    CpuidUtil& operator=(const CpuidUtil& other);

    void get(int leaf);
    void get(int leaf, int subleaf);

    uint32_t eax() const { return static_cast<uint32_t>(cpu_info_[kEAX]); }
    uint32_t ebx() const { return static_cast<uint32_t>(cpu_info_[kEBX]); }
    uint32_t ecx() const { return static_cast<uint32_t>(cpu_info_[kECX]); }
    uint32_t edx() const { return static_cast<uint32_t>(cpu_info_[kEDX]); }

    static bool hasAesNi();

private:
    static constexpr int kEAX = 0;
    static constexpr int kEBX = 1;
    static constexpr int kECX = 2;
    static constexpr int kEDX = 3;

#if defined(CC_MSVC)
    int cpu_info_[4] = { -1, -1, -1, -1 };
#else
    unsigned int cpu_info_[4] = { UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX };
#endif // CC_MSVC
};

} // namespace base

#endif // defined(ARCH_CPU_X86_FAMILY)
#endif // BASE__CPUID_UTIL_H
