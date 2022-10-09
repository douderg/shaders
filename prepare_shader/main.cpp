#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 3) {
        return EXIT_FAILURE;
    }

    std::string target = argv[1];

    std::ifstream input(argv[2], std::ios::binary | std::ios::in);
    std::fstream source(target + ".cpp", std::ios::out);
    
    source << "#include <" << target << ".hpp>\n\nalignas(sizeof(uint32_t)) uint32_t " << target << "_data[] = {\n";
    uint32_t word;
    char* addr = reinterpret_cast<char*>(&word);
    if (input.read(addr, 4)) {
        source << "0x" << std::hex << word;
    }

    size_t count = 1;
    while (input.read(addr, 4)) {
        source << ", 0x" << std::hex << word;
        ++count;
    }

    source << "\n};\nsize_t " << target << "_size = " << std::dec << 4 * count << ";\n";

    std::fstream header(target + ".hpp", std::ios::out);
    header << "#pragma once\n\n#include <cinttypes>\n\nalignas(sizeof(uint32_t)) uint32_t " << target << "_data[];\n"
        << "extern size_t " << target << "_size;\n";

    return EXIT_SUCCESS;
}
