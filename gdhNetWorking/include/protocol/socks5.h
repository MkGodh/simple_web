#pragma once

#include <cstdint>
#include <vector>

namespace MOYF::socks5 {

    inline constexpr std::uint8_t VERSION = 0x05;

    namespace method {
        inline constexpr std::uint8_t NO_AUTHENTICATION = 0x00;
        inline constexpr std::uint8_t USERNAME_PASSWORD = 0x02;
        inline constexpr std::uint8_t NO_ACCEPTABLE = 0xFF;
    }

    // Wire format: VER | NMETHODS | METHODS (NMETHODS bytes)
    struct GreetingRequest {
        std::uint8_t version {};
        std::vector<std::uint8_t> methods {};
    };

    // Wire format: VER | METHOD
    struct GreetingResponse {
        std::uint8_t version {VERSION};
        std::uint8_t selectedMethod {method::NO_ACCEPTABLE};
    };
}
