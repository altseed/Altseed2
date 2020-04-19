#pragma once

#include <vector>
#include <array>
#include <codecvt>
#include <locale>
#include <string>

namespace Altseed {

// http://hasenpfote36.blogspot.jp/2016/09/stdcodecvt.html
static constexpr std::codecvt_mode mode = std::codecvt_mode::little_endian;

static std::string utf16_to_utf8(const std::u16string& s) {
#if defined(_MSC_VER)
    std::wstring_convert<std::codecvt_utf8_utf16<std::uint16_t, 0x10ffff, mode>, std::uint16_t> conv;
    auto p = reinterpret_cast<const std::uint16_t*>(s.c_str());
    return conv.to_bytes(p, p + s.length());
#else
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, mode>, char16_t> conv;
    return conv.to_bytes(s);
#endif
}

static bool IsU8LaterByte(char ch) { return 0x80 <= uint8_t(ch) && uint8_t(ch) < 0xC0; }

static int GetU8ByteCount(char ch) {
    if (0 <= uint8_t(ch) && uint8_t(ch) < 0x80) {
        return 1;
    }
    if (0xC2 <= uint8_t(ch) && uint8_t(ch) < 0xE0) {
        return 2;
    }
    if (0xE0 <= uint8_t(ch) && uint8_t(ch) < 0xF0) {
        return 3;
    }
    if (0xF0 <= uint8_t(ch) && uint8_t(ch) < 0xF8) {
        return 4;
    }
    return 0;
}

static bool ConvChU8ToU32(const std::array<char, 4>& u8Ch, char32_t& u32Ch) {
    int numBytes = GetU8ByteCount(u8Ch[0]);
    if (numBytes == 0) {
        return false;
    }
    switch (numBytes) {
        case 1:
            u32Ch = char32_t(uint8_t(u8Ch[0]));
            break;
        case 2:
            if (!IsU8LaterByte(u8Ch[1])) {
                return false;
            }
            if ((uint8_t(u8Ch[0]) & 0x1E) == 0) {
                return false;
            }

            u32Ch = char32_t(u8Ch[0] & 0x1F) << 6;
            u32Ch |= char32_t(u8Ch[1] & 0x3F);
            break;
        case 3:
            if (!IsU8LaterByte(u8Ch[1]) || !IsU8LaterByte(u8Ch[2])) {
                return false;
            }
            if ((uint8_t(u8Ch[0]) & 0x0F) == 0 && (uint8_t(u8Ch[1]) & 0x20) == 0) {
                return false;
            }

            u32Ch = char32_t(u8Ch[0] & 0x0F) << 12;
            u32Ch |= char32_t(u8Ch[1] & 0x3F) << 6;
            u32Ch |= char32_t(u8Ch[2] & 0x3F);
            break;
        case 4:
            if (!IsU8LaterByte(u8Ch[1]) || !IsU8LaterByte(u8Ch[2]) || !IsU8LaterByte(u8Ch[3])) {
                return false;
            }
            if ((uint8_t(u8Ch[0]) & 0x07) == 0 && (uint8_t(u8Ch[1]) & 0x30) == 0) {
                return false;
            }

            u32Ch = char32_t(u8Ch[0] & 0x07) << 18;
            u32Ch |= char32_t(u8Ch[1] & 0x3F) << 12;
            u32Ch |= char32_t(u8Ch[2] & 0x3F) << 6;
            u32Ch |= char32_t(u8Ch[3] & 0x3F);
            break;
        default:
            return false;
    }

    return true;
}

static bool ConvChU32ToU16(const char32_t u32Ch, std::array<char16_t, 2>& u16Ch) {
    if (u32Ch > 0x10FFFF) {
        return false;
    }

    if (u32Ch < 0x10000) {
        u16Ch[0] = char16_t(u32Ch);
        u16Ch[1] = 0;
    } else {
        u16Ch[0] = char16_t((u32Ch - 0x10000) / 0x400 + 0xD800);
        u16Ch[1] = char16_t((u32Ch - 0x10000) % 0x400 + 0xDC00);
    }

    return true;
}

static bool ConvChU8ToU16(const std::array<char, 4>& u8Ch, std::array<char16_t, 2>& u16Ch) {
    char32_t u32Ch;
    if (!ConvChU8ToU32(u8Ch, u32Ch)) {
        return false;
    }
    if (!ConvChU32ToU16(u32Ch, u16Ch)) {
        return false;
    }
    return true;
}

static std::u16string utf8_to_utf16(const std::string& u8Str) {
    std::u16string u16Str;
    for (auto u8It = u8Str.begin(); u8It != u8Str.end(); ++u8It) {
        auto numBytes = GetU8ByteCount((*u8It));
        if (numBytes == 0) {
            return std::u16string();
        }

        std::array<char, 4> u8Ch;
        u8Ch[0] = (*u8It);
        for (int i = 1; i < numBytes; i++) {
            ++u8It;
            if (u8It == u8Str.end()) {
                return std::u16string();
            }
            u8Ch[i] = (*u8It);
        }

        std::array<char16_t, 2> u16Ch;
        if (!ConvChU8ToU16(u8Ch, u16Ch)) {
            return std::u16string();
        }

        u16Str.push_back(u16Ch[0]);
        if (u16Ch[1] != 0) {
            u16Str.push_back(u16Ch[1]);
        }
    }
    return u16Str;
}

static bool IsU16HighSurrogate(char16_t ch) { return 0xD800 <= ch && ch < 0xDC00; }

static bool IsU16LowSurrogate(char16_t ch) { return 0xDC00 <= ch && ch < 0xE000; }

static bool ConvChU16ToU32(const std::array<char16_t, 2>& u16Ch, char32_t& u32Ch) {
    if (IsU16HighSurrogate(u16Ch[0])) {
        if (IsU16LowSurrogate(u16Ch[1])) {
            u32Ch = 0x10000 + (char32_t(u16Ch[0]) - 0xD800) * 0x400 + (char32_t(u16Ch[1]) - 0xDC00);
        } else if (u16Ch[1] == 0) {
            u32Ch = u16Ch[0];
        } else {
            return false;
        }
    } else if (IsU16LowSurrogate(u16Ch[0])) {
        if (u16Ch[1] == 0) {
            u32Ch = u16Ch[0];
        } else {
            return false;
        }
    } else {
        u32Ch = u16Ch[0];
    }

    return true;
}

static std::u16string ToString(int32_t v) {
    auto str = std::to_string(v);

    std::u16string s;
    s.reserve(str.size());

    for (auto c : str) {
        s += static_cast<char16_t>(c);
    }

    return s;
}

static std::vector<std::u16string> split(const std::u16string& s, char16_t delim) {
    std::vector<std::u16string> elems;
    std::u16string item;
    for (char16_t ch : s) {
        if (ch == delim) {
            if (!item.empty()) elems.push_back(item);
            item.clear();
        } else {
            item += ch;
        }
    }
    if (!item.empty()) elems.push_back(item);
    return elems;
}

}  // namespace Altseed