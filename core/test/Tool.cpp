#include "Tool/Tool.h"

#include <gtest/gtest.h>

#include <memory>

#include "Common/Array.h"
#include "Common/StringHelper.h"
#include "Core.h"
#include "Graphics/CommandList.h"
#include "Graphics/Graphics.h"
#include "Graphics/RenderTexture.h"
#include "Graphics/Renderer/CullingSystem.h"
#include "Graphics/Renderer/RenderedCamera.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/Renderer.h"
#include "Math/Matrix44F.h"
#include "Math/RectF.h"
#include "System/SynchronizationContext.h"
#include "TestHelper.h"

#if !defined(_WIN32) || defined(_WIN64)

static const int LoopFrames = 60;

template <typename... Args>
std::u16string format(const std::u16string& fmt, Args... args) {
    auto fmt_ = Altseed2::utf16_to_utf8(fmt);
    size_t len = std::snprintf(nullptr, 0, fmt_.c_str(), args...);
    std::vector<char> buf(len + 1);
    std::snprintf(&buf[0], len + 1, fmt_.c_str(), args...);
    return Altseed2::utf8_to_utf16(std::string(&buf[0], &buf[0] + len));
}

static void ToolTestTemplate(const int loopCount, std::function<void(std::shared_ptr<Altseed2::Tool>)> update) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics | Altseed2::CoreModules::Tool);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Tool", 1280, 720, config));

    int count = 0;

    // Altseed2::Tool::GetInstance()->SetToolUsage(Altseed2::ToolUsage::Main);

    auto g = Altseed2::Graphics::GetInstance();
    EXPECT_TRUE(g != nullptr);

    auto t = Altseed2::Tool::GetInstance();
    EXPECT_TRUE(t != nullptr);

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(Altseed2::Vector2F(), t1->GetSize().To2F()));
    auto trans1 = Altseed2::Matrix44F();
    auto trans2 = Altseed2::Matrix44F();
    trans1.SetTranslation(200, 200, 0);
    trans2.SetRotationZ(0);
    s1->SetTransform(trans2 * trans1 * trans2);

    Altseed2::Tool::GetInstance()->AddFontFromFileTTF(u"TestData/Font/mplus-1m-regular.ttf", 14, Altseed2::ToolGlyphRange::Japanese);

    while (count++ < loopCount && g->DoEvents()) {
        Altseed2::SynchronizationContext::GetInstance()->Run();
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        trans2.SetRotationZ(count / 100.0f);
        s1->SetTransform(trans1 * trans2 * trans1.GetInverted());

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = false;
        EXPECT_TRUE(g->BeginFrame(renderPassParameter));
        Altseed2::Tool::GetInstance()->NewFrame();

        if (update != nullptr) update(t);

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);

        Altseed2::Renderer::GetInstance()->Render();
        Altseed2::Tool::GetInstance()->Render();

        EXPECT_TRUE(g->EndFrame());
    }

    Altseed2::Core::Terminate();
}

TEST(Tool, WithoutIni) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics | Altseed2::CoreModules::Tool);
    EXPECT_TRUE(config != nullptr);

    config->SetToolSettingFileName(nullptr);
    EXPECT_TRUE(Altseed2::Core::Initialize(u"Tool.WithoutIni", 1280, 720, config));
    Altseed2::Core::Terminate();
}

TEST(Tool, Window) {
    auto flags = {
            // Altseed2::ToolWindowFlags::NoTitleBar,
            Altseed2::ToolWindowFlags::NoResize,
            Altseed2::ToolWindowFlags::NoMove,
            // Altseed2::ToolWindowFlags::NoScrollbar,
            Altseed2::ToolWindowFlags::NoScrollWithMouse,
            Altseed2::ToolWindowFlags::NoCollapse,
            // Altseed2::ToolWindowFlags::NoBackground,
            // Altseed2::ToolWindowFlags::NoBringToFrontOnFocus,
            // Altseed2::ToolWindowFlags::NoNav,
            // Altseed2::ToolWindowFlags::NoSavedSettings,
            // Altseed2::ToolWindowFlags::AlwaysAutoResize,
            // Altseed2::ToolWindowFlags::NoFocusOnAppearing,
    };

    int32_t _flag = 0;
    for (const auto& f : flags) {
        _flag |= static_cast<int32_t>(f);
    }

    auto flag = static_cast<Altseed2::ToolWindowFlags>(_flag);

    ToolTestTemplate(LoopFrames, [&flag](std::shared_ptr<Altseed2::Tool> t) {
        t->SetNextWindowPos(Altseed2::Vector2F());
        t->SetNextWindowSize(Altseed2::Vector2F(320, 720));
        if (t->Begin(u"Window1", NULL, flag)) {
            t->Text(u"Text");
        }
        t->End();

        t->SetNextWindowPos(Altseed2::Vector2F(320, 0));
        t->SetNextWindowSize(Altseed2::Vector2F(320, 720));
        if (t->Begin(u"Window2", NULL, flag)) {
            t->Text(u"Text");
        }
        t->End();
    });
}

TEST(Tool, Text) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"Text", NULL)) {
            t->Dummy(Altseed2::Vector2F(10, 10));
            t->Text(u"Normal Text");
            t->TextUnformatted(u"Unformatted");
            t->TextColored(Altseed2::Vector4F(0.0f, 0.0f, 1.0f, 1.0f), u"Blue Text");
            t->BulletText(u"aaaaa\n\"bb\"ccccccccccc");

            t->Indent();
            t->BulletText(u"indented");
            t->TextDisabled(u"Disabled");
            t->Unindent();

            t->Separator();
            t->TextWrapped(
                    u"Even very long sentences are automatically wrapped according to the width of the window and displayed on the next "
                    u"line");
            t->NewLine();

            t->PushTextWrapPos(200.0f);
            t->Text(u"Text between PushTextWrapPos and PopTextWrapPos is wrapped");
            t->PopTextWrapPos();
        }
        t->End();
    });
}

TEST(Tool, Japanese) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"日本語", NULL)) {
            t->Dummy(Altseed2::Vector2F(10, 10));
            t->Text(u"通常のテキスト");
            t->TextUnformatted(u"フォーマットされないテキスト");
            t->TextColored(Altseed2::Vector4F(0.0f, 0.0f, 1.0f, 1.0f), u"Blue Text");
            t->BulletText(u"あああああ\n\"括られ\"アイウエオ");

            t->Indent();
            t->BulletText(u"インデント");
            t->TextDisabled(u"無効なテキスト");
            t->Unindent();

            t->Separator();
            t->TextWrapped(u"とても長い文章でもウィンドウの横幅に応じて自動的に折り返して次の行に表示してくれます");
            t->NewLine();

            t->PushTextWrapPos(200.0f);
            t->Text(u"PushTextWrapPosからPopTextWrapPosまでの間のTextは折り返して表示されます");
            t->PopTextWrapPos();
        }
        t->End();
    });
}

TEST(Tool, Button) {
    bool isOpen = false;
    int radio = 0;
    int counter = 0;

    ToolTestTemplate(LoopFrames, [&isOpen, &radio, &counter](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"Button", NULL)) {
            if (t->Button(u"open/close##1", Altseed2::Vector2F())) {
                isOpen = !isOpen;
            }
            t->SameLine();
            t->Checkbox(u"open/close##2", &isOpen);

            for (int i = 0; i < 3; i++) {
                if (t->RadioButton(format(u"Radio Button %d", i).c_str(), &radio)) {
                    radio = i;
                }
                t->SameLine();
            }
            t->Dummy(Altseed2::Vector2F());
            t->Text(format(u"%d is selected", radio).c_str());

            t->PushButtonRepeat(true);

            if (t->ArrowButton(u"##left", Altseed2::ToolDir::Left)) {
                counter--;
            }
            t->SameLine();
            if (t->ArrowButton(u"##right", Altseed2::ToolDir::Right)) {
                counter++;
            }

            t->PopButtonRepeat();

            t->SameLine();
            t->Text(format(u"%d", counter).c_str());
        }
        t->End();

        if (isOpen) {
            if (t->Begin(u"Another Window", NULL)) {
                t->Text(u"aaaaa");
            }
            t->End();
        }
    });
}

TEST(Tool, Input) {
    int current = 0;

    ToolTestTemplate(LoopFrames, [&current](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"Input", NULL)) {
            t->LabelText(u"label", u"value");

            const char16_t* items = u"AAA\tBBB\tCCC";
            t->Combo(u"DropDown List", &current, items, 3);

            t->Text(format(u"Current: %d (%s)", current, Altseed2::split(items, '\t')[current].c_str()).c_str());

            static std::u16string str0 = u"";
            auto res = t->InputText(u"InputText##1", str0.c_str(), 1024);
            if (res != nullptr) str0 = res;

            static std::u16string str1 = u"";
            res = t->InputTextWithHint(u"InputText##2", u"placeholder", str1.c_str(), 1024);
            if (res != nullptr) str1 = res;

            static std::u16string str2 = u"";
            res = t->InputTextMultiline(
                    u"InputText##3",
                    str2.c_str(),
                    1024,
                    Altseed2::Vector2F(-1, t->GetTextLineHeight() * 3),
                    Altseed2::ToolInputTextFlags::AllowTabInput);
            if (res != nullptr) str2 = res;

            static std::u16string buf2 = u"";
            res = t->InputTextWithHint(u"Input Numbers", u"only 0123456789.+-*/", buf2.c_str(), 256, Altseed2::ToolInputTextFlags::CharsDecimal);
            if (res != nullptr) buf2 = res;

            static std::u16string bufpass = u"password123";

            res = t->InputText(
                    u"Password",
                    bufpass.c_str(),
                    16,
                    static_cast<Altseed2::ToolInputTextFlags>(
                            static_cast<int32_t>(Altseed2::ToolInputTextFlags::Password) |
                            static_cast<int32_t>(Altseed2::ToolInputTextFlags::CharsNoBlank)));
            if (res != nullptr) bufpass = res;

            static int i0 = 123;
            static float f0 = 0.001f;
            static std::shared_ptr<Altseed2::FloatArray> vec3 = Altseed2::FloatArray::Create(3);

            t->InputInt(u"InputInt", &i0);
            t->InputFloat(u"InputFloat", &f0);
            t->InputFloat3(u"InputFloat3", vec3);
        }
        t->End();
    });
}

TEST(Tool, Slider) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"Slider", NULL)) {
            static int i1 = 50, i2 = 42;
            t->DragInt(u"DragInt", &i1, 1, 0, 0);
            t->DragInt(u"%", &i2, 1, 0, 100);

            t->SetNextItemWidth(100);

            static float f1 = 1.00f;
            t->DragFloat(u"DragFloat", &f1, 0.005f, 0.0f, 0.0f);

            t->SetNextItemWidth(t->GetWindowSize().X * 0.5f);

            static int i3 = 0;
            t->SliderInt(u"SliderInt", &i3, -1, 3);
            t->SetNextItemWidth(-100);

            static float f2 = 0.123f, f3 = 0.0f;
            t->SliderFloat(u"SliderFloat##1", &f2, 0.0f, 1.0f);

            static float angle = 0.0f;
            t->SliderAngle(u"Angle", &angle);  // -360から360までドラッグして変化させることができます

            static float begin = 10, end = 90;
            t->DragFloatRange2(u"range", &begin, &end, 0.2f, 0.0f, 100.0f);

            static std::shared_ptr<Altseed2::FloatArray> vec3f = Altseed2::FloatArray::Create(3);

            t->SliderFloat3(u"SliderFloat3", vec3f, 0.0f, 1.0f);

            static float x = 1.0f, y = 2.0f, z = 3.0f;
            t->PushItemWidth(70);

            t->SameLine();
            t->SliderFloat(u"X", &x, 0.0f, 5.0f);
            t->SameLine();
            t->SliderFloat(u"Y", &y, 0.0f, 5.0f);
            t->SameLine();
            t->SliderFloat(u"Z", &z, 0.0f, 5.0f);

            t->PopItemWidth();
        }
        t->End();
    });
}

TEST(Tool, VSlider) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"VSlider", NULL)) {
            static float values[7] = {0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f};
            for (int i = 0; i < 7; i++) {
                if (i > 0) t->SameLine();
                t->PushID(i);

                // 垂直スライダーを幅18,高さ160,最小値0,最大値1で作成します。
                t->VSliderFloat(u"##v", Altseed2::Vector2F(18, 160), &values[i], 0.0f, 1.0f);

                if (t->IsItemActive() || t->IsItemHovered()) {
                    t->SetTooltip(format(u"%.3f", values[i]).c_str());
                }

                t->PopID();
            }
        }
        t->End();
    });
}

TEST(Tool, Color) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"Color", NULL)) {
            static Altseed2::Color col1 = Altseed2::Color(10, 20, 50, 100);
            static Altseed2::Color col2 = Altseed2::Color(10, 20, 50, 100);

            t->ColorEdit3(u"Color1", &col1);  // RGB
            t->ColorEdit4(u"Color2", &col2);  // RGBAのアルファ付き

            auto flag = static_cast<Altseed2::ToolColorEditFlags>(
                    static_cast<int32_t>(Altseed2::ToolColorEditFlags::Float) | static_cast<int32_t>(Altseed2::ToolColorEditFlags::NoInputs) |
                    static_cast<int32_t>(Altseed2::ToolColorEditFlags::NoLabel)

            );
            t->ColorEdit3(u"Color ID", &col1, flag);
        }
        t->End();
    });
}

TEST(Tool, ListBox) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"ListBox", NULL)) {
            const char16_t* items = u"Apple\tBanana\tCherry\tKiwi\tMango\tOrange\tPineapple\tStrawberry\tWatermelon";
            static int current = 1;

            t->ListBox(u"ListBox", &current, items, 9);
        }
        t->End();
    });
}

TEST(Tool, Selectable) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"Selectable", NULL)) {
            static bool selection[5] = {false, true, false, false, false};

            t->Selectable(u"Selectable 1", &selection[0]);
            t->Selectable(u"Selectable 2", &selection[1]);

            if (t->Selectable(u"Selectable 3", &selection[2], Altseed2::ToolSelectableFlags::AllowDoubleClick))
                if (t->IsMouseDoubleClicked(Altseed2::ToolMouseButton::Left)) selection[2] = !selection[2];

            t->Selectable(u"Selectable 5", &selection[4], Altseed2::ToolSelectableFlags::Disabled);
        }
        t->End();
    });
}

TEST(Tool, Table) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"Table", NULL)) {
            t->Columns(3, NULL, true);
            static bool selected[12] = {};
            for (int i = 0; i < 12; i++) {
                if (t->Selectable(format(u"Item %d", i).c_str(), &selected[i])) {
                    std::cout << i << std::endl;
                }
                t->NextColumn();
            }
            t->Columns(1, NULL, false);
            t->Separator();

            t->Columns(4, u"columnListID");
            t->Separator();

            t->Text(u"ID");
            t->NextColumn();
            t->Text(u"Name");
            t->NextColumn();
            t->Text(u"Path");
            t->NextColumn();
            t->Text(u"Hovered");
            t->NextColumn();

            t->Separator();
            const char* names[3] = {"One", "Two", "Three"};
            const char* paths[3] = {"/path/one", "/path/two", "/path/three"};
            static int select = -1;
            for (int i = 0; i < 3; i++) {
                bool x = select == i;
                if (t->Selectable(format(u"%04d", i).c_str(), &x, Altseed2::ToolSelectableFlags::SpanAllColumns)) {
                    select = i;
                }

                bool hovered = t->IsItemHovered();
                t->NextColumn();
                t->Text(format(u"%s", names[i]).c_str());
                t->NextColumn();
                t->Text(format(u"%s", paths[i]).c_str());
                t->NextColumn();
                t->Text(format(u"%d", hovered).c_str());
                t->NextColumn();
            }
            t->Columns(1, NULL, false);
        }
        t->End();
    });
}

TEST(Tool, Sortable) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"Sortable", NULL)) {
            static const char16_t* item_names[] = {u"Sortable 1", u"Sortable 2", u"Sortable 3", u"Sortable 4", u"Sortable 5"};
            static const char16_t* item_current = item_names[0];
            for (int n = 0; n < 5; n++) {
                const char16_t* item = item_names[n];
                bool is_selected = (item_current == item_names[n]);
                if (t->Selectable(item, &is_selected)) item_current = item_names[n];
                if (t->IsItemActive() && !t->IsItemHovered()) {
                    int n_next = n + (t->GetMouseDragDelta(Altseed2::ToolMouseButton::Left).Y < 0.f ? -1 : 1);
                    if (n_next >= 0 && n_next < 5) {
                        item_names[n] = item_names[n_next];
                        item_names[n_next] = item;
                        t->ResetMouseDragDelta(Altseed2::ToolMouseButton::Left);
                    }
                }
            }
            t->Text(format(u"%s is selected", item_current).c_str());
        }
        t->End();
    });
}

TEST(Tool, CollapsingHeader) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"CollapsingHeader", NULL)) {
            if (t->CollapsingHeader(u"open/close field")) {
                if (t->TreeNode(u"TreeNode A")) {
                    t->Text(u"hogehoge");
                    t->TreePop();
                }

                t->SetNextItemOpen(true, Altseed2::ToolCond::Once);
                if (t->TreeNode(u"TreeNode B")) {
                    t->Text(u"TreeNode B is opened");
                    t->TreePop();
                }
            }
        }
        t->End();
    });
}
TEST(Tool, Tooltip) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"Tooltip", NULL)) {
            t->TextDisabled(u"(?)");
            if (t->IsItemHovered()) {
                t->BeginTooltip();
                t->PushTextWrapPos(t->GetFontSize() * 35.0f);
                t->TextUnformatted(u"Tooltip Text");
                t->PopTextWrapPos();
                t->EndTooltip();
            }
        }
        t->End();
    });
}

TEST(Tool, Popup) {
    bool isOpen = true;
    ToolTestTemplate(LoopFrames, [&isOpen](std::shared_ptr<Altseed2::Tool> t) {
        if (t->Begin(u"Popup", NULL)) {
            const char16_t* names[] = {u"AAA", u"BBB", u"CCC", u"DDD"};
            static int selected = -1;
            if (t->Button(u"Select..", Altseed2::Vector2F())) {
                t->OpenPopup(u"popupID");
            }
            t->SameLine();
            t->TextUnformatted(selected == -1 ? u"Unselected" : names[selected]);

            if (t->BeginPopup(u"popupID")) {
                t->Text(u"Selectable Items");
                t->Separator();
                for (int i = 0; i < 4; i++)
                    if (t->Selectable(names[i], &isOpen)) selected = i;
                t->EndPopup();
            }
        }
        t->End();
    });
}

TEST(Tool, SaveDialog) {
    return;

    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics | Altseed2::CoreModules::Tool);
    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    Altseed2::Tool::GetInstance()->OpenDialog(u"png;jpg,jpeg", u"");

    Altseed2::Core::Terminate();
}

TEST(Tool, Image) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed2::Tool> t) {
        static auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
        EXPECT_TRUE(t1 != nullptr);
        static auto s1 = Altseed2::RenderedSprite::Create();
        s1->SetTexture(t1);

        static auto rt = Altseed2::RenderTexture::Create(Altseed2::Vector2I(200, 200));
        static auto camera = Altseed2::RenderedCamera::Create();

        static auto matView = Altseed2::Matrix44F();
        matView.SetTranslation(640, 360, 0);

        camera->SetTargetTexture(rt);
        camera->SetViewMatrix(matView.GetInverted());

        Altseed2::Renderer::GetInstance()->SetCamera(camera);
        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->Render();

        if (t->Begin(u"Image", NULL)) {
            t->Image(t1, Altseed2::Vector2F(100, 100));
            t->ImageButton(t1, Altseed2::Vector2F(100, 100));
            t->ImageButton(rt, Altseed2::Vector2F(100, 100));
            t->ImageButton(t1, Altseed2::Vector2F(100, 100));
        }
        t->End();
    });
}

#endif