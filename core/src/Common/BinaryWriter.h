#pragma once
#include <climits>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include "../Graphics/Color.h"
#include "../Math/Matrix44F.h"
#include "../Math/Vector2F.h"
#include "../Math/Vector3F.h"
#include "../Math/RectI.h"
#include "../Math/RectF.h"

namespace Altseed {
class BinaryWriter {
protected:
    std::vector<int8_t> m_data;

public:
    void Reserve(size_t size) { m_data.reserve(size); }
    std::vector<int8_t> const& Get() const { return m_data; }

    void Push(int32_t content) {
        int8_t* pc = static_cast<int8_t*>(static_cast<void*>(&content));
        for (int i = 0; i < 4; i++) {
            m_data.push_back(pc[i]);
        }
    }

    void Push(int16_t content) {
        int8_t* pc = static_cast<int8_t*>(static_cast<void*>(&content));
        for (int i = 0; i < 2; i++) {
            m_data.push_back(pc[i]);
        }
    }

    void Push(uint16_t content) {
        int8_t* pc = static_cast<int8_t*>(static_cast<void*>(&content));
        for (int i = 0; i < 2; i++) {
            m_data.push_back(pc[i]);
        }
    }

    void Push(int8_t content) { m_data.push_back(content); }

    void Push(uint8_t content) { m_data.push_back(*((uint8_t*)(&content))); }

    void Push(std::u16string const& content) {
        int32_t l = (int32_t)content.length();

        int8_t* pc = static_cast<int8_t*>(static_cast<void*>(&l));
        for (int i = 0; i < 4; i++) {
            m_data.push_back(pc[i]);
        }
        for (int32_t i = 0; i < l; i++) {
            m_data.push_back(static_cast<int8_t>(content.at(i)));
        }
    }

    void Push(bool content) {
        int8_t* pc = static_cast<int8_t*>(static_cast<void*>(&content));
        for (int i = 0; i < sizeof(bool); i++) {
            m_data.push_back(pc[i]);
        }
    }

    void Push(float content) {
        int8_t* pc = static_cast<int8_t*>(static_cast<void*>(&content));
        for (int i = 0; i < 4; i++) {
            m_data.push_back(pc[i]);
        }
    }

    void Push(Vector3F const& content) {
        Push(content.X);
        Push(content.Y);
        Push(content.Z);
    }

	void Push(Vector2I const& content) {
        Push(content.X);
        Push(content.Y);
    }

    void Push(Vector2F const& content) {
        Push(content.X);
        Push(content.Y);
    }

    void Push(Color const& content) {
        Push(content.R);
        Push(content.G);
        Push(content.B);
        Push(content.A);
    }

	void Push(RectI const& content) {
        Push(content.X);
        Push(content.Y);
        Push(content.Width);
        Push(content.Height);
    }

	void Push(RectF const& content) {
        Push(content.X);
        Push(content.Y);
        Push(content.Width);
        Push(content.Height);
    }

    void Push(Matrix44F const& content) {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                Push(content.Values[j][i]);
            }
        }
    }

    bool WriteOut(std::ostream& os) const {
        if (!os) {
            return false;
        }
        for (auto itr = m_data.cbegin(); itr != m_data.cend(); itr++) {
            os << *itr;
        }
        return true;
    }
    virtual ~BinaryWriter() {}
};
}  // namespace Altseed