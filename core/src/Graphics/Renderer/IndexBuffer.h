#pragma once

namespace Altseed2 {

struct IndexBuffer_C;

struct IndexBuffer {
    int Index1;
    int Index2;
    int Index3;

    IndexBuffer();
    IndexBuffer(int index1, int index2, int index3);

    bool operator==(const IndexBuffer& other) const;
    bool operator!=(const IndexBuffer& other) const;

    operator IndexBuffer_C() const;
};

struct IndexBuffer_C {
    int Index1;
    int Index2;
    int Index3;

    operator IndexBuffer() const;
};

}  // namespace Altseed2