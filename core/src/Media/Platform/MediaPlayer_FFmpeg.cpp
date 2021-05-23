#include "MediaPlayer_FFmpeg.h"

#include <regex>

#include "../../Common/StringHelper.h"

namespace Altseed2 {

void MediaPlayer_FFmpeg::ThreadLoop() {
    // TODO : support padding
    int imageSize = 14 + 40 + size_.X * size_.Y * 3;
    std::vector<char> data;
    data.reserve(imageSize * 2);

    std::string command = "ffmpeg -i " + filePath_ + " -c:v bmp -f rawvideo pipe:1";

    do {
        currentFrame_ = 0;
        startTime_ = std::chrono::system_clock::now();

        std::shared_ptr<TinyProcessLib::Process> process;

        process = std::make_shared<TinyProcessLib::Process>(command.c_str(), "", [&](const char* bytes, size_t n) {
            if (!isPlaying_) {
                TinyProcessLib::Process::kill(process->get_id(), true);
                return;
            }

            const auto offset = data.size();
            data.resize(offset + n);
            memcpy(data.data() + offset, bytes, n);

            if (data.size() >= imageSize) {
                {
                    auto now = std::chrono::system_clock::now();
                    auto diff = now - startTime_;
                    auto diff_micro = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();

                    if (diff_micro + 1000 < (currentFrame_ / fps_) * 1000 * 1000) {
                        auto sleeping = (currentFrame_ / fps_) * 1000 * 1000 - diff_micro;
                        std::this_thread::sleep_for(std::chrono::microseconds((int)sleeping));
                    }
                }

                {
                    std::lock_guard<std::mutex> lock(mtx_);

                    for (size_t y = 0; y < size_.Y; y++) {
                        for (size_t x = 0; x < size_.X; x++) {
                            internalBuffer_[(x + (size_.Y - 1 - y) * size_.X) * 4 + 2] = data[(x + y * size_.X) * 3 + 0];
                            internalBuffer_[(x + (size_.Y - 1 - y) * size_.X) * 4 + 1] = data[(x + y * size_.X) * 3 + 1];
                            internalBuffer_[(x + (size_.Y - 1 - y) * size_.X) * 4 + 0] = data[(x + y * size_.X) * 3 + 2];
                            internalBuffer_[(x + (size_.Y - 1 - y) * size_.X) * 4 + 3] = 255;
                        }
                    }
                }

                data.erase(data.begin(), data.begin() + imageSize);
                currentFrame_++;
            }
        });
        auto exit_status = process->get_exit_status();
    } while (isLoopingMode_);

    isPlaying_ = false;
}

MediaPlayer_FFmpeg::MediaPlayer_FFmpeg() {
}

MediaPlayer_FFmpeg::~MediaPlayer_FFmpeg() {
    if (isThreadRequiredToJoin_) {
        isPlaying_ = false;
        thread_.join();
        isThreadRequiredToJoin_ = false;
    }
}

bool MediaPlayer_FFmpeg::Play(bool isLoopingMode) {
    isLoopingMode_ = isLoopingMode;

    isPlaying_ = true;
    isThreadRequiredToJoin_ = true;
    startTime_ = std::chrono::system_clock::now();

    thread_ = std::thread([this]() -> void { this->ThreadLoop(); });

    return true;
}

bool MediaPlayer_FFmpeg::SetSourceFromPath(const char16_t* path) {
    filePath_ = utf16_to_utf8(path);
    std::string command = "ffmpeg -i " + filePath_;
    int width = 0;
    int height = 0;
    int fps = 0;

    TinyProcessLib::Process process1(
            command, "", [](const char* bytes, size_t n) {}, [&](const char* bytes, size_t n) {
                {
                    std::regex re1("( [0-9]+x[0-9]+ )");
                    std::smatch match;
                    auto s = std::string(bytes, n);
                    if (std::regex_search(s, match, re1)) {
                        std::sscanf(match[0].str().c_str(), " %dx%d ", &width, &height);
                    }
                }

                {
                    std::regex re1("( [0-9]+x[0-9]+,)");
                    std::smatch match;
                    auto s = std::string(bytes, n);
                    if (std::regex_search(s, match, re1)) {
                        std::sscanf(match[0].str().c_str(), " %dx%d,", &width, &height);
                    }
                }

                {
                    std::regex re("( [0-9]+ fps)");
                    std::smatch match;
                    auto s = std::string(bytes, n);
                    if (std::regex_search(s, match, re)) {
                        std::sscanf(match[0].str().c_str(), " %d fps,", &fps);
                    }
                } });

    auto exit_status = process1.get_exit_status();

    if (width == 0 || height == 0) {
        return false;
    }

    fps_ = fps;
    size_.X = width;
    size_.Y = height;
    internalBuffer_.resize(width * height * 4);

    return true;
}

Vector2I MediaPlayer_FFmpeg::GetSize() const { return size_; }

int32_t MediaPlayer_FFmpeg::GetCurrentFrame() const { return currentFrame_; }

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
        std::lock_guard<std::mutex> lock(mtx_);
        memcpy(ptr, internalBuffer_.data(), internalBuffer_.size());
        native->Unlock();
        return true;
    }

    return false;
}

};  // namespace Altseed2
