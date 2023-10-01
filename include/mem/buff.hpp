#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <span>


namespace mem {


template<std::size_t Size>
class MemBuffer
{
    std::array<std::uint8_t, Size> m_buff;
    size_t m_written {};

public:
    MemBuffer() = default;

    MemBuffer(std::span<const char> spn)
        : m_buff(spn), m_written(spn.size())
    {}

    void append(std::span<const char> spn) {
        if (spn.size() > remaining()) return;

        std::copy(spn.begin(), spn.end(), m_buff.data() + m_written);
        m_written += spn.size();
    }

    std::uint8_t* data() {
        return m_buff.data();
    }

    size_t written() const {
        return m_written;
    }

    size_t remaining() const {
        return Size - m_written;
    }
};


} // namespace mem
