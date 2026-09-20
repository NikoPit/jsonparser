//
// Created by kristen on 2026/9/20.
//

export module lexer;

import std;
import utils;

export namespace token {
        struct LeftBrace {};
        struct RightBrace {};
    struct LeftSquareBracket {};
    struct RightSquareBracket {};
        struct Colon {};
    struct Comma {};

        struct Number { std::size_t number; };
        struct String { std::string value; };
}

using Token = std::variant<token::LeftBrace, token::RightBrace, token::Colon, token::Comma,
    token::LeftSquareBracket, token::RightSquareBracket,
    token::Number, token::String>;

export class Lexer {
    private:
    std::string json;
    std::vector<Token> tokens;
    std::size_t pos;

    auto peek() -> std::optional<char> {
        if (this->pos >= this->json.size()) return std::nullopt;
        return this->json[this->pos];
    }

    auto consume() -> char {
        return json[this->pos++]; /* Returns the current FIRST, THEN increment */
    }

    auto consume_and_emplace(Token token) {
        this->consume();
        this->tokens.emplace_back(token);
    }

    auto lex_number() -> std::size_t {
        std::string number_str;

        while (true) {
            char next;

            if (this->peek().has_value()) {
                next = this->peek().value();
            } else {
                break;
            }

            if (!std::isdigit(next)) {
                break;
            }

            number_str.push_back(this->consume());
        }

        return std::stoull(number_str);
    }

    auto lex_string() -> std::string {
        std::string str;

        /* Expect left quotation mark */
        assert(this->peek().has_value());
        assert(this->consume() == '"');

        while (true) {
            char next;

            if (this->peek().has_value()) {
                next = this->peek().value();
            } else {
                break;
            }

            if (next == '"') {
                this->consume();
                break;
            }

            str.push_back(this->consume());
        }

        return str;
    }

    public:
    Lexer(std::string&& json) {
        this->json = std::move(json);
        this->pos = 0;
    }


    auto lex() -> std::vector<Token> {
        while (true) {
            char next;

           if (this->peek().has_value()) {
                next = this->peek().value();
            } else {
                break;
            }

            switch (next) {
                case '{':
                    this->consume_and_emplace(token::LeftBrace {});
                    break;
                case '}':
                    this->consume_and_emplace(token::RightBrace {});
                    break;
                case ':':
                    this->consume_and_emplace(token::Colon {});
                    break;
                case ',':
                    this->consume_and_emplace(token::Comma {});
                    break;
                case '[':
                    this->consume_and_emplace(token::LeftSquareBracket {});
                    break;
                case ']':
                    this->consume_and_emplace(token::RightSquareBracket {});
                    break;
                case '"':
                    this->tokens.emplace_back(token::String { .value = this->lex_string() } );
                    break;
                case ' ':
                case '\t':
                case '\n':
                case '\r':
                    this->consume(); /* Skip white space / useless characters */
                    break;
                default:
                    if (std::isdigit(static_cast<unsigned char>(next))) {
                        this->tokens.emplace_back(token::Number { .number = this->lex_number() } );
                    } else {
                        panic("Unknown token");
                    }
            }
        }

        return this->tokens;
    }
};
