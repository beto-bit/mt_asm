#include <array>
#include <cstddef>
#include <span>
#include <string_view>

int main(std::span<const std::string_view> args);

extern "C" int cpp_entry(int argc, char* argv[]) {
    const size_t span_size = static_cast<size_t>(argc);

    std::array<std::string_view, 255> args;

    for (size_t idx = 0; idx < span_size; ++idx) {
        args[idx] = std::string_view{argv[idx]};
    }

    return main({args.data(), span_size});
}
