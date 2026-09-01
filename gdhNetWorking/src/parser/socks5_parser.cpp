#include "parser/socks5_parser.h"

#include <algorithm>

namespace MOYF::socks5 {

    namespace {
        constexpr std::size_t HEADER_SIZE = 2; // VER + NMETHODS

        bool hasSupportedMethod(const std::vector<std::uint8_t>& methods) {
            return std::find(methods.begin(), methods.end(), method::NO_AUTHENTICATION) != methods.end();
        }

        GreetingRequest extractRequest(std::span<const std::uint8_t> data, std::size_t methodsCount) {
            const auto methodsBegin = data.begin() + HEADER_SIZE;
            return {data[0], {methodsBegin, methodsBegin + methodsCount}};
        }
    }

    GreetingParseResult ParseGreetingRequest(std::span<const std::uint8_t> data) {
        if (data.size() < HEADER_SIZE) {
            return {ParseStatus::Incomplete, {}};
        }
        if (data[0] != VERSION) {
            return {ParseStatus::Invalid, {}};
        }

        const std::size_t methodsCount = data[1];
        if (methodsCount == 0) {
            return {ParseStatus::Invalid, {}};
        }
        if (data.size() < HEADER_SIZE + methodsCount) {
            return {ParseStatus::Incomplete, {}};
        }

        GreetingRequest request = extractRequest(data, methodsCount);
        const ParseStatus status = hasSupportedMethod(request.methods)
                                       ? ParseStatus::Valid
                                       : ParseStatus::NoSupportedMethod;
        return {status, std::move(request)};
    }

    std::vector<std::uint8_t> SerializeGreetingResponse(const GreetingResponse& response) {
        return {response.version, response.selectedMethod};
    }
}
