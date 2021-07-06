#include "MediaPlayer_WMF.h"

#include "../../IO/StaticFile.h"

#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "mfreadwrite.lib")

namespace Altseed2 {

void MediaPlayer_WMF::ThreadLoop() {
    while (isPlaying) {
        {
            auto now = std::chrono::system_clock::now();
            auto diff = now - startTime;
            auto diff_micro = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();

            if (diff_micro + 1000 < (currentFrame / fps) * 1000 * 1000) {
                auto sleeping = (currentFrame / fps) * 1000 * 1000 - diff_micro;
                std::this_thread::sleep_for(std::chrono::microseconds((int)sleeping));
            }
        }

        DWORD flags;
        IMFSample* sample;
        reader->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, NULL, &flags, NULL, &sample);
        if (sample == nullptr) {
            // Loop
            if (isLoopingMode_) {
                PROPVARIANT propvar;
                HRESULT hr = InitPropVariantFromInt64(0, &propvar);
                reader->SetCurrentPosition(GUID_NULL, propvar);
                PropVariantClear(&propvar);

                currentFrame = 0;
                startTime = std::chrono::system_clock::now();

                reader->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, NULL, &flags, NULL, &sample);
                if (sample == nullptr) {
                    isPlaying = false;
                    break;
                }
            } else {
                isPlaying = false;
                break;
            }
        }

        IMFMediaBuffer* buffer;
        sample->GetBufferByIndex(0, &buffer);

        BYTE* p;
        DWORD size;
        buffer->Lock(&p, NULL, &size);

        if (size != internalBufferYUY.size()) {
            buffer->Unlock();
            buffer->Release();
            sample->Release();

            isPlaying = false;
            break;
        }

        memcpy(internalBufferYUY.data(), p, size);
        buffer->Unlock();

        buffer->Release();
        sample->Release();

        for (int32_t y = 0; y < size_.Y; y++) {
            for (int32_t x = 0; x < size_.X; x += 2) {
                auto src = internalBufferYUY.data() + (x + (y * size_.X)) * 2;

                auto y0 = (int)src[0];
                auto u0 = (int)src[1] - 128;
                auto y1 = (int)src[2];
                auto v0 = (int)src[3] - 128;

                auto R0 = 1.000 * y0 + 1.402 * v0;
                auto G0 = 1.000 * y0 - 0.344 * u0 - 0.714 * v0;
                auto B0 = 1.000 * y0 + 1.772 * u0;

                auto R1 = 1.000 * y1 + 1.402 * v0;
                auto G1 = 1.000 * y1 - 0.344 * u0 - 0.714 * v0;
                auto B1 = 1.000 * y1 + 1.772 * u0;

                if (R0 > 255)
                    R0 = 255;
                if (G0 > 255)
                    G0 = 255;
                if (B0 > 255)
                    B0 = 255;

                if (R1 > 255)
                    R1 = 255;
                if (G1 > 255)
                    G1 = 255;
                if (B1 > 255)
                    B1 = 255;

                if (R0 < 0)
                    R0 = 0;
                if (G0 < 0)
                    G0 = 0;
                if (B0 < 0)
                    B0 = 0;

                if (R1 < 0)
                    R1 = 0;
                if (G1 < 0)
                    G1 = 0;
                if (B1 < 0)
                    B1 = 0;

                internalBufferEditing[(x + y * size_.X) * 4 + 0] = R0;
                internalBufferEditing[(x + y * size_.X) * 4 + 1] = G0;
                internalBufferEditing[(x + y * size_.X) * 4 + 2] = B0;
                internalBufferEditing[(x + y * size_.X) * 4 + 3] = 255;

                internalBufferEditing[(x + 1 + y * size_.X) * 4 + 0] = R1;
                internalBufferEditing[(x + 1 + y * size_.X) * 4 + 1] = G1;
                internalBufferEditing[(x + 1 + y * size_.X) * 4 + 2] = B1;
                internalBufferEditing[(x + 1 + y * size_.X) * 4 + 3] = 255;
            }
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            internalBuffer = internalBufferEditing;
        }

        currentFrame++;
    }
}

MediaPlayer_WMF::MediaPlayer_WMF() {
    CoInitialize(NULL);
    MFStartup(MF_VERSION);
}

MediaPlayer_WMF::~MediaPlayer_WMF() {
    if (isThreadRequiredToJoin) {
        isPlaying = false;
        thread_.join();
        isThreadRequiredToJoin = false;
    }

    MFShutdown();
    CoUninitialize();
}

bool MediaPlayer_WMF::Play(bool isLoopingMode) {
    if (reader == nullptr)
        return false;
    isLoopingMode_ = isLoopingMode;

    isPlaying = true;
    isThreadRequiredToJoin = true;
    startTime = std::chrono::system_clock::now();

    thread_ = std::thread([this]() -> void { this->ThreadLoop(); });

    return true;
}

bool MediaPlayer_WMF::SetSourceFromPath(const char16_t* path) {
    HRESULT hr;

    // load directry?
    FILE* fp = nullptr;
    _wfopen_s(&fp, (const wchar_t*)path, L"rb");

    if (fp != nullptr) {
        // load directry
        fclose(fp);

        hr = MFCreateSourceReaderFromURL((const wchar_t*)path, NULL, &reader);
        if (FAILED(hr)) {
            return false;
        }
    } else {
        auto staticFile = StaticFile::Create(path);

        if (staticFile == nullptr) {
            return false;
        }

        IMFByteStream* byteStream = nullptr;
        hr = MFCreateTempFile(MF_FILE_ACCESSMODE::MF_ACCESSMODE_READWRITE, MF_FILE_OPENMODE::MF_OPENMODE_FAIL_IF_EXIST, MF_FILE_FLAGS::MF_FILEFLAGS_NONE, &byteStream);
        if (FAILED(hr)) {
            staticFile->Release();
            return false;
        }

        ULONG t;
        hr = byteStream->Write((BYTE*)staticFile->GetData(), (ULONG)staticFile->GetSize(), &t);

        if (FAILED(hr)) {
            byteStream->Close();
            return false;
        }

        byteStream->Seek(MFBYTESTREAM_SEEK_ORIGIN::msoBegin, 0, 0, NULL);
        if (FAILED(hr)) {
            byteStream->Close();
            return false;
        }

        hr = MFCreateSourceReaderFromByteStream(byteStream, NULL, &reader);
        if (FAILED(hr)) {
            return false;
        }
    }

    IMFMediaType* mediaType = nullptr;
    MFCreateMediaType(&mediaType);
    mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    mediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_YUY2);
    hr = reader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, mediaType);

    if (FAILED(hr)) {
        reader->Release();
        reader = nullptr;
        mediaType->Release();
        return false;
    }

    uint32_t nume, denom;
    UINT32 width, height;
    reader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, &mediaType);
    MFGetAttributeSize(mediaType, MF_MT_FRAME_SIZE, &width, &height);
    MFGetAttributeRatio(mediaType, MF_MT_FRAME_RATE, &nume, &denom);
    fps = (float)nume / denom;

    mediaType->Release();

    size_.X = width;
    size_.Y = height;

    internalBufferYUY.resize(width * height * 2);
    internalBuffer.resize(width * height * 4);
    internalBufferEditing.resize(width * height * 4);

    return true;
}

Vector2I MediaPlayer_WMF::GetSize() const { return size_; }

int32_t MediaPlayer_WMF::GetCurrentFrame() const { return currentFrame; }

bool MediaPlayer_WMF::WriteToTexture2D(std::shared_ptr<RenderTexture> target) {
    if (target == nullptr)
        return false;
    if (target->GetSize() != GetSize())
        return false;
    if (!(target->GetFormat() == TextureFormatType::R8G8B8A8_UNORM || target->GetFormat() == TextureFormatType::R8G8B8A8_UNORM_SRGB))
        return false;

    auto& native = target->GetNativeTexture();

    auto ptr = native->Lock();
    if (native != nullptr) {
        std::lock_guard<std::mutex> lock(mtx);
        memcpy(ptr, internalBuffer.data(), internalBuffer.size());
        native->Unlock();
        return true;
    }

    return false;
}

};  // namespace Altseed2
