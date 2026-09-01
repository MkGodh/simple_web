#pragma once

#include <cstdint>
#include <span>
#include <vector>

#include "protocol/socks5.h"

namespace MOYF::socks5 {

    enum class ParseStatus {
        Incomplete,
        Invalid,
        Valid,
        NoSupportedMethod,
    };

    struct GreetingParseResult {
        ParseStatus status {ParseStatus::Incomplete};
        GreetingRequest request {};
    };

    GreetingParseResult ParseGreetingRequest(std::span<const std::uint8_t> data);

    std::vector<std::uint8_t> SerializeGreetingResponse(const GreetingResponse& response);
}
