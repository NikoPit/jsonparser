//
// Created by kristen on 2026/9/20.
//

export module utils;

import std;

export auto read_file(const std::string &file_path) -> std::string {
    std::ifstream ifs(file_path);
    std::ostringstream buffer;

    buffer << ifs.rdbuf();

    return buffer.str();
}

export auto panic(std::string message) {
    std::println("Panic: {}", message);
    std::abort();
}

export auto panic() {
    std::println("Panic!");
    std::abort();
}

export auto assert(bool value) {
    if (!value) panic("Assertion failed");
}