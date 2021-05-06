#include "MediaPlayer_FFmpeg.h"

#include <regex>

#include "../../Common/StringHelper.h"

namespace Altseed2 {

void MediaPlayer_FFmpeg::ThreadLoop() {
    // TODO : support padding
    int imageSize = 14 + 40 + size_.X * size_.Y * 3;
    std::vector<char> data;
    data.reserve(imageSize * 2);

    TinyProcessLib::Process process("ffmpeg -i input.mp4 -c:v bmp -f rawvideo pipe:1", "", [&](const char* bytes, size_t n) {
        const auto offset = data.size();
        data.resize(offset + n);
        memcpy(data.data() + offset, bytes, n);

        if (data.size() >= imageSize) {
            {
                auto now = std::chrono::system_clock::now();
                auto diff = now - startTime;
                auto diff_micro = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();

                if (diff_micro + 1000 < (currentFrame / fps) * 1000 * 1000) {
                    auto sleeping = (currentFrame / fps) * 1000 * 1000 - diff_micro;
                    std::this_thread::sleep_for(std::chrono::microseconds((int)sleeping));
                }
            }

            {
                std::lock_guard<std::mutex> lock(mtx);
                internalBuffer = data;
            }

            data.erase(data.begin(), data.begin() + imageSize);
            currentFrame++;
        }

       
    });
    auto exit_status = process.get_exit_status();

    while (isPlaying) {
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
    }
}

MediaPlayer_FFmpeg::MediaPlayer_FFmpeg() {
}

MediaPlayer_FFmpeg::~MediaPlayer_FFmpeg() {
    if (isThreadRequiredToJoin) {
        isPlaying = false;
        thread_.join();
        isThreadRequiredToJoin = false;
    }
}

bool MediaPlayer_FFmpeg::Play(bool isLoopingMode) {
    if (process_ == nullptr)
        return false;
    isLoopingMode_ = isLoopingMode;

    isPlaying = true;
    isThreadRequiredToJoin = true;
    startTime = std::chrono::system_clock::now();

    thread_ = std::thread([this]() -> void { this->ThreadLoop(); });

    return true;
}

bool MediaPlayer_FFmpeg::SetSourceFromPath(const char16_t* path) {
    std::string command = "ffmpeg -i " + utf16_to_utf8(path);
    int width = 0;
    int height = 0;

    TinyProcessLib::Process process1(
            command, "", [](const char* bytes, size_t n) {}, [&](const char* bytes, size_t n) {


				std::regex re("( [0-9]+x[0-9]+ )");
				std::smatch match;
				auto s = std::string(bytes, n);
				std::cout << s << std::endl;
				if (std::regex_search(s, match, re))
				{
					std::sscanf(match[0].str().c_str(), " %dx%d ", &width, &height);
				} });
    auto exit_status = process1.get_exit_status();
    if (exit_status != 0) {
        return false;
    }

    // TODO fps
    fps = 30;
    size_.X = width;
    size_.Y = height;
    internalBuffer.resize(width * height * 4);

    return true;
}

Vector2I MediaPlayer_FFmpeg::GetSize() const { return size_; }

int32_t MediaPlayer_FFmpeg::GetCurrentFrame() const { return currentFrame; }

bool MediaPlayer_FFmpeg::WriteToTexture2D(std::shared_ptr<Texture2D> target) {
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
