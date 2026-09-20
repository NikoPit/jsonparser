import std;
import utils;
import lexer;

auto main(const int argc, const char * argv[]) -> int {
    if (argc != 2) {
        std::println("Usage: ./jsonparser <file>");
        return 1;
    }

    auto file_path = argv[1];
    auto file_content = read_file(file_path);

    auto lexer = std::make_unique<Lexer>(std::move(file_content));
    auto tokens = lexer->lex();

    std::println("{}",file_content);
}