#pragma once
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include "../Graphics/Color.h"
#include "../Math/Matrix44F.h"
#include "../Math/RectF.h"
#include "../Math/RectI.h"
#include "../Math/Vector2F.h"
#include "../Math/Vector3F.h"

namespace Altseed {
class BinaryReader {
protected:
    std::vector<uint8_t> data;
    std::size_t idx;

public:
    BinaryReader(std::shared_ptr<StaticFile> file) {
        ASD_ASSERT(file != nullptr, "static file is null")
        data.resize(file->GetSize());
        memcpy(reinterpret_cast<char*>(&data[0]), file->GetData(), file->GetSize());
        idx = 0;
    }

    template <typename T>
    inline T Get() {
        assert(!"The type cannot be serializable.");
        return T();
    };

    bool IsEmpty() const { return idx >= data.size(); }

    inline std::vector<uint8_t> Get(int32_t size) {
        if (idx + size > data.size()) {
            return std::vector<uint8_t>();
        }
        std::vector<uint8_t> v(size);
        /*
        for (int i = 0; i < size; i++)
        {
                v.push_back(data.front());
                data.pop_front();
        }
        */
        std::memcpy(v.data(), data.data() + idx, size);
        idx += size;
        return v;
    }
};

template <>
inline int32_t BinaryReader::Get() {
    size_t const size = sizeof(int32_t);
    if (idx + size > data.size()) {
        assert(!"Lack of buffer (int32_t).");
        return int32_t();
    }
    int32_t v = 0;
    std::memcpy(&v, data.data() + idx, size);
    idx += size;
    return v;
}

template <>
inline int16_t BinaryReader::Get() {
    size_t const size = sizeof(int16_t);
    if (idx + size > data.size()) {
        assert(!"Lack of buffer (int16_t).");
        return int16_t();
    }
    int16_t v = 0;
    std::memcpy(&v, data.data() + idx, size);
    idx += size;
    return v;
}

template <>
inline uint16_t BinaryReader::Get() {
    size_t const size = sizeof(uint16_t);
    if (idx + size > data.size()) {
        assert(!"Lack of buffer (uint16_t).");
        return uint16_t();
    }
    uint16_t v = 0;
    std::memcpy(&v, data.data() + idx, size);
    idx += size;
    return v;
}
template <>
inline int8_t BinaryReader::Get() {
    size_t const size = sizeof(int8_t);
    if (idx + size > data.size()) {
        assert(!"Lack of buffer (int8_t).");
        return int8_t();
    }
    int8_t v = 0;
    std::memcpy(&v, data.data() + idx, size);
    idx += size;
    return v;
}

template <>
inline uint8_t BinaryReader::Get() {
    size_t const size = sizeof(uint8_t);
    if (idx + size > data.size()) {
        assert(!"Lack of buffer (uint8_t).");
        return uint8_t();
    }
    uint8_t v = 0;
    std::memcpy(&v, data.data() + idx, size);
    idx += size;
    return v;
}

template <>
inline std::u16string BinaryReader::Get() {
    int32_t const len = Get<int32_t>();
    size_t const size = sizeof(char16_t);

    if (idx + size * len > data.size()) {
        assert(!"Lack of buffer (u16string).");
        return std::u16string();
    }

    std::u16string v = std::u16string((char16_t const*)(data.data() + idx), (size_t)len);
    idx += size * len;
    return v;
}

template <>
inline float BinaryReader::Get() {
    size_t const size = sizeof(float);
    if (idx + size > data.size()) {
        assert(!"Lack of buffer (float).");
        return float();
    }
    float v = 0;
    std::memcpy(&v, data.data() + idx, size);
    idx += size;
    return v;
}

template <>
inline bool BinaryReader::Get() {
    size_t const size = sizeof(bool);
    if (idx + size > data.size()) {
        assert(!"Lack of buffer (bool).");
        return bool();
    }
    bool v = false;
    std::memcpy(&v, data.data() + idx, size);
    idx += size;
    return v;
}

template <>
inline Vector3F BinaryReader::Get() {
    Vector3F v;
    v.X = Get<float>();
    v.Y = Get<float>();
    v.Z = Get<float>();

    return v;
}

template <>
inline Vector2I BinaryReader::Get() {
    Vector2I v;
    v.X = Get<int32_t>();
    v.Y = Get<int32_t>();

    return v;
}

template <>
inline Vector2F BinaryReader::Get() {
    Vector2F v;
    v.X = Get<float>();
    v.Y = Get<float>();

    return v;
}

template <>
inline Color BinaryReader::Get() {
    Color c;
    c.R = Get<uint8_t>();
    c.G = Get<uint8_t>();
    c.B = Get<uint8_t>();
    c.A = Get<uint8_t>();

    return c;
}

template <>
inline RectI BinaryReader::Get() {
    RectI v;
    v.X = Get<int32_t>();
    v.Y = Get<int32_t>();
    v.Width = Get<int32_t>();
    v.Height = Get<int32_t>();
    return v;
}

template <>
inline RectF BinaryReader::Get() {
    RectF v;
    v.X = Get<float>();
    v.Y = Get<float>();
    v.Width = Get<float>();
    v.Height = Get<float>();
    return v;
}

template <>
inline Matrix44F BinaryReader::Get() {
    Matrix44F m;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            m.Values[j][i] = Get<float>();
        }
    }

    return m;
}

}  // namespace Altseed