//https:  //github.com/altseed/Altseed/tree/master/Dev/asd_cpp/core

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <propvarutil.h>

#include <mutex>
#include <thread>
#include <vector>

#include "MediaPlayer_Impl.h"

namespace Altseed2 {

class MediaPlayer_WMV {
    Graphics* graphics = nullptr;
    File* file = nullptr;
    std::mutex mtx;
    std::thread thread_;

    uint32_t width = 0;
    uint32_t height = 0;
    float fps = 0;

    std::vector<uint8_t> internalBufferYUY;
    std::vector<uint8_t> internalBuffer;
    std::vector<uint8_t> internalBufferEditing;

    bool isPlaying = false;
    bool isThreadRequiredToJoin = false;

    int32_t currentFrame = 0;
    std::chrono::system_clock::time_point startTime;

    IMFSourceReader* reader = nullptr;

    void ThreadLoop();

public:
    MediaPlayerWMF(Graphics* graphics, File* file);

    virtual ~MediaPlayerWMF();

    bool Play(bool isLoopingMode);

    void Write(void* dst);

    bool SetSourceFromPath(const char16_t* path);

    int32_t GetWidth() const;

    int32_t GetHeight() const;

    int32_t GetCurrentFrame() const override;

    Vector2DI GetSize() const override {
        return Vector2DI(GetWidth(), GetHeight());
    }

    bool Load(const achar* path) override;

    bool WriteToTexture2D(Texture2D* target) override;
};

void MediaPlayerWMF::ThreadLoop() {
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
            if (isLoopingMode) {
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

        for (int32_t y = 0; y < height; y++) {
            for (int32_t x = 0; x < width; x += 2) {
                auto src = internalBufferYUY.data() + (x + (y * width)) * 2;

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

                internalBufferEditing[(x + y * width) * 4 + 0] = R0;
                internalBufferEditing[(x + y * width) * 4 + 1] = G0;
                internalBufferEditing[(x + y * width) * 4 + 2] = B0;
                internalBufferEditing[(x + y * width) * 4 + 3] = 255;

                internalBufferEditing[(x + 1 + y * width) * 4 + 0] = R1;
                internalBufferEditing[(x + 1 + y * width) * 4 + 1] = G1;
                internalBufferEditing[(x + 1 + y * width) * 4 + 2] = B1;
                internalBufferEditing[(x + 1 + y * width) * 4 + 3] = 255;
            }
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            internalBuffer = internalBufferEditing;
        }

        currentFrame++;
    }
}

MediaPlayerWMF::MediaPlayerWMF(Graphics* graphics, File* file) : graphics(graphics), file(file) {
    SafeAddRef(graphics);
    SafeAddRef(file);

    CoInitialize(NULL);
    MFStartup(MF_VERSION);
}

MediaPlayerWMF::~MediaPlayerWMF() {
    if (isThreadRequiredToJoin) {
        isPlaying = false;
        thread_.join();
        isThreadRequiredToJoin = false;
    }

    SafeRelease(reader);

    MFShutdown();
    CoUninitialize();

    SafeRelease(file);
    SafeRelease(graphics);
}

bool MediaPlayerWMF::Play(bool isLoopingMode) {
    if (reader == nullptr)
        return false;
    this->isLoopingMode = isLoopingMode;

    isPlaying = true;
    isThreadRequiredToJoin = true;
    startTime = std::chrono::system_clock::now();

    thread_ = std::thread([this]() -> void { this->ThreadLoop(); });

    return true;
}

void MediaPlayerWMF::Write(void* dst) {
    std::lock_guard<std::mutex> lock(mtx);
    memcpy(dst, internalBuffer.data(), internalBuffer.size());
}

bool MediaPlayerWMF::SetSourceFromPath(const char16_t* path) {
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
        asd::StaticFile* staticFile = file->CreateStaticFile(path);
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
        SafeRelease(staticFile);
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
    reader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, &mediaType);
    MFGetAttributeSize(mediaType, MF_MT_FRAME_SIZE, &width, &height);
    MFGetAttributeRatio(mediaType, MF_MT_FRAME_RATE, &nume, &denom);
    fps = (float)nume / denom;

    mediaType->Release();

    internalBufferYUY.resize(width * height * 2);
    internalBuffer.resize(width * height * 4);
    internalBufferEditing.resize(width * height * 4);

    return true;
}

int32_t MediaPlayerWMF::GetWidth() const { return width; }

int32_t MediaPlayerWMF::GetHeight() const { return height; }

int32_t MediaPlayerWMF::GetCurrentFrame() const { return currentFrame; }

bool MediaPlayerWMF::Load(const achar* path) { return SetSourceFromPath(path); }

bool MediaPlayerWMF::WriteToTexture2D(Texture2D* target) {
    if (target == nullptr)
        return false;
    if (target->GetSize() != GetSize())
        return false;
    if (!(target->GetFormat() == TextureFormat::R8G8B8A8_UNORM || target->GetFormat() == TextureFormat::R8G8B8A8_UNORM_SRGB))
        return false;

    TextureLockInfomation l;

    if (target->Lock(&l)) {
        Write(l.GetPixels());

        target->Unlock();
        return true;
    }

    return false;
}

};  // namespace Altseed2


/*
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#include <chrono>
#include <mutex>
#include <thread>

#include "../asd.MediaPlayer.h"
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "mfreadwrite.lib")

namespace asd {

class MediaPlayerWMF
	: public MediaPlayer
{
private:
	Graphics* graphics = nullptr;
	File* file = nullptr;
	std::mutex mtx;
	std::thread thread_;

	uint32_t width = 0;
	uint32_t height = 0;
	float fps = 0;

	std::vector<uint8_t> internalBufferYUY;
	std::vector<uint8_t> internalBuffer;
	std::vector<uint8_t> internalBufferEditing;

	bool isPlaying = false;
	bool isThreadRequiredToJoin = false;

	int32_t currentFrame = 0;
	std::chrono::system_clock::time_point startTime;

	IMFSourceReader* reader = nullptr;

	void ThreadLoop();
public:

	MediaPlayerWMF(Graphics* graphics, File *file);

	virtual ~MediaPlayerWMF();

	bool Play(bool isLoopingMode);

	void Write(void* dst);

	bool SetSourceFromPath(const char16_t* path);

	int32_t GetWidth() const;

	int32_t GetHeight() const;

	int32_t GetCurrentFrame() const override;

	Vector2DI GetSize() const override
	{
		return Vector2DI(GetWidth(), GetHeight());
	}

	bool Load(const achar* path) override;

	bool WriteToTexture2D(Texture2D* target) override;
};

}
*/

/*
#include "asd.MediaPlayerWMF.h"

#ifdef _WIN32

#include <propvarutil.h>

#include "../../asd.Graphics.h"
#include "../../asd.Graphics_Imp.h"

namespace asd
{
void MediaPlayerWMF::ThreadLoop()
{
	while (isPlaying)
	{
		{
			auto now = std::chrono::system_clock::now();
			auto diff = now - startTime;
			auto diff_micro = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();

			if (diff_micro + 1000 < (currentFrame / fps) * 1000 * 1000)
			{
				auto sleeping = (currentFrame / fps) * 1000 * 1000 - diff_micro;
				std::this_thread::sleep_for(std::chrono::microseconds((int)sleeping));
			}
		}

		DWORD flags;
		IMFSample* sample;
		reader->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, NULL, &flags, NULL, &sample);
		if (sample == nullptr)
		{
			// Loop
			if (isLoopingMode)
			{
				PROPVARIANT propvar;
				HRESULT hr = InitPropVariantFromInt64(0, &propvar);
				reader->SetCurrentPosition(GUID_NULL, propvar);
				PropVariantClear(&propvar);

				currentFrame = 0;
				startTime = std::chrono::system_clock::now();

				reader->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, NULL, &flags, NULL, &sample);
				if (sample == nullptr)
				{
					isPlaying = false;
					break;
				}
			}
			else
			{
				isPlaying = false;
				break;
			}
		}

		IMFMediaBuffer* buffer;
		sample->GetBufferByIndex(0, &buffer);

		BYTE* p;
		DWORD size;
		buffer->Lock(&p, NULL, &size);

		if (size != internalBufferYUY.size())
		{
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

		for (int32_t y = 0; y < height; y++)
		{
			for (int32_t x = 0; x < width; x += 2)
			{
				auto src = internalBufferYUY.data() + (x + (y * width)) * 2;

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

				internalBufferEditing[(x + y * width) * 4 + 0] = R0;
				internalBufferEditing[(x + y * width) * 4 + 1] = G0;
				internalBufferEditing[(x + y * width) * 4 + 2] = B0;
				internalBufferEditing[(x + y * width) * 4 + 3] = 255;

				internalBufferEditing[(x + 1 + y * width) * 4 + 0] = R1;
				internalBufferEditing[(x + 1 + y * width) * 4 + 1] = G1;
				internalBufferEditing[(x + 1 + y * width) * 4 + 2] = B1;
				internalBufferEditing[(x + 1 + y * width) * 4 + 3] = 255;
			}
		}

		{
			std::lock_guard<std::mutex> lock(mtx);
			internalBuffer = internalBufferEditing;
		}

		currentFrame++;
	}
}

MediaPlayerWMF::MediaPlayerWMF(Graphics* graphics, File* file) : graphics(graphics), file(file)
{
	SafeAddRef(graphics);
	SafeAddRef(file);

	CoInitialize(NULL);
	MFStartup(MF_VERSION);
}

MediaPlayerWMF::~MediaPlayerWMF()
{
	if (isThreadRequiredToJoin)
	{
		isPlaying = false;
		thread_.join();
		isThreadRequiredToJoin = false;
	}

	SafeRelease(reader);

	MFShutdown();
	CoUninitialize();

	SafeRelease(file);
	SafeRelease(graphics);
}

bool MediaPlayerWMF::Play(bool isLoopingMode)
{
	if (reader == nullptr)
		return false;
	this->isLoopingMode = isLoopingMode;

	isPlaying = true;
	isThreadRequiredToJoin = true;
	startTime = std::chrono::system_clock::now();

	thread_ = std::thread([this]() -> void { this->ThreadLoop(); });

	return true;
}

void MediaPlayerWMF::Write(void* dst)
{
	std::lock_guard<std::mutex> lock(mtx);
	memcpy(dst, internalBuffer.data(), internalBuffer.size());
}

bool MediaPlayerWMF::SetSourceFromPath(const char16_t* path)
{
	HRESULT hr;

	// load directry?
	FILE* fp = nullptr;
	_wfopen_s(&fp, (const wchar_t*)path, L"rb");

	if (fp != nullptr)
	{
		// load directry
		fclose(fp);

		hr = MFCreateSourceReaderFromURL((const wchar_t*)path, NULL, &reader);
		if (FAILED(hr))
		{
			return false;
		}
	}
	else
	{
		asd::StaticFile* staticFile = file->CreateStaticFile(path);
		if (staticFile == nullptr)
		{
			return false;
		}

		IMFByteStream* byteStream = nullptr;
		hr = MFCreateTempFile(MF_FILE_ACCESSMODE::MF_ACCESSMODE_READWRITE,
							  MF_FILE_OPENMODE::MF_OPENMODE_FAIL_IF_EXIST,
							  MF_FILE_FLAGS::MF_FILEFLAGS_NONE,
							  &byteStream);
		if (FAILED(hr))
		{
			staticFile->Release();
			return false;
		}

		ULONG t;
		hr = byteStream->Write((BYTE*)staticFile->GetData(), (ULONG)staticFile->GetSize(), &t);
		SafeRelease(staticFile);
		if (FAILED(hr))
		{
			byteStream->Close();
			return false;
		}

		byteStream->Seek(MFBYTESTREAM_SEEK_ORIGIN::msoBegin, 0, 0, NULL);
		if (FAILED(hr))
		{
			byteStream->Close();
			return false;
		}

		hr = MFCreateSourceReaderFromByteStream(byteStream, NULL, &reader);
		if (FAILED(hr))
		{
			return false;
		}
	}

	IMFMediaType* mediaType = nullptr;
	MFCreateMediaType(&mediaType);
	mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
	mediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_YUY2);
	hr = reader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, mediaType);

	if (FAILED(hr))
	{
		reader->Release();
		reader = nullptr;
		mediaType->Release();
		return false;
	}

	uint32_t nume, denom;
	reader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, &mediaType);
	MFGetAttributeSize(mediaType, MF_MT_FRAME_SIZE, &width, &height);
	MFGetAttributeRatio(mediaType, MF_MT_FRAME_RATE, &nume, &denom);
	fps = (float)nume / denom;

	mediaType->Release();

	internalBufferYUY.resize(width * height * 2);
	internalBuffer.resize(width * height * 4);
	internalBufferEditing.resize(width * height * 4);

	return true;
}

int32_t MediaPlayerWMF::GetWidth() const { return width; }

int32_t MediaPlayerWMF::GetHeight() const { return height; }

int32_t MediaPlayerWMF::GetCurrentFrame() const { return currentFrame; }

bool MediaPlayerWMF::Load(const achar* path) { return SetSourceFromPath(path); }

bool MediaPlayerWMF::WriteToTexture2D(Texture2D* target)
{
	if (target == nullptr)
		return false;
	if (target->GetSize() != GetSize())
		return false;
	if (!(target->GetFormat() == TextureFormat::R8G8B8A8_UNORM || target->GetFormat() == TextureFormat::R8G8B8A8_UNORM_SRGB))
		return false;

	TextureLockInfomation l;

	if (target->Lock(&l))
	{
		Write(l.GetPixels());

		target->Unlock();
		return true;
	}

	return false;
}
} // namespace asd

#endif
*/