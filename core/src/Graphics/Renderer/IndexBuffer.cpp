#include "IndexBuffer.h"

namespace Altseed2 {
IndexBuffer::IndexBuffer() : Index1(0), Index2(0), Index3(0) {}

IndexBuffer::IndexBuffer(int index1, int index2, int index3) : Index1(index1), Index2(index2), Index3(index3) {}

bool IndexBuffer::operator==(const IndexBuffer& other) const { return Index1 == other.Index1 && Index2 == other.Index2 && Index3 == other.Index3; }
bool IndexBuffer::operator!=(const IndexBuffer& other) const { return Index1 != other.Index1 || Index2 != other.Index2 || Index3 != other.Index3; }

IndexBuffer::operator IndexBuffer_C() const { return IndexBuffer_C{Index1, Index2, Index3}; }

IndexBuffer_C::operator IndexBuffer() const { return IndexBuffer(Index1, Index2, Index3); }
}  // namespace Altseed2