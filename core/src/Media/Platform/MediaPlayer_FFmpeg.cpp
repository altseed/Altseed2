#include "MediaPlayer_FFmpeg.h"

#include <regex>

#include "../../Common/StringHelper.h"

namespace Altseed2 {

void MediaPlayer_FFmpeg::ThreadLoop() {
    // TODO : support padding
    int imageSize = 14 + 40 + size_.X * size_.Y * 3;
    std::vector<char> data;
    data.reserve(imageSize * 2);

    do {
        currentFrame = 0;
        startTime = std::chrono::system_clock::now();

        std::shared_ptr<TinyProcessLib::Process> process;

        process = std::make_shared<TinyProcessLib::Process>("ffmpeg -i input.mp4 -c:v bmp -f rawvideo pipe:1", "", [&](const char* bytes, size_t n) {

            if (!isPlaying) {
                TinyProcessLib::Process::kill(process->get_id(), true);
                return;
            }

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

                    for (size_t y = 0; y < size_.Y; y++) {
                        for (size_t x = 0; x < size_.X; x++) {
                            internalBuffer[(x + y * size_.X) * 4 + 0] = data[(x + y * size_.X) * 3 + 0];
                            internalBuffer[(x + y * size_.X) * 4 + 1] = data[(x + y * size_.X) * 3 + 1];
                            internalBuffer[(x + y * size_.X) * 4 + 2] = data[(x + y * size_.X) * 3 + 2];
                            internalBuffer[(x + y * size_.X) * 4 + 3] = 255;
                        }
                    }
                }

                data.erase(data.begin(), data.begin() + imageSize);
                currentFrame++;
            }
        });
        auto exit_status = process->get_exit_status();
    } while (isLoopingMode_);

    isPlaying = false;
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
