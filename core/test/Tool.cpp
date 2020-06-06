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

static const int LoopFrames = 50000;

template <typename... Args>
std::u16string format(const std::u16string& fmt, Args... args) {
    auto fmt_ = Altseed::utf16_to_utf8(fmt);
    size_t len = std::snprintf(nullptr, 0, fmt_.c_str(), args...);
    std::vector<char> buf(len + 1);
    std::snprintf(&buf[0], len + 1, fmt_.c_str(), args...);
    return Altseed::utf8_to_utf16(std::string(&buf[0], &buf[0] + len));
}

static void ToolTestTemplate(const int loopCount, std::function<void(std::shared_ptr<Altseed::Tool>)> update) {
    auto config = Altseed::Configuration::Create();
    config->SetToolEnabled(true);

    EXPECT_TRUE(Altseed::Core::Initialize(u"Tool", 1280, 720, config));

    int count = 0;

    // Altseed::Tool::GetInstance()->SetToolUsage(Altseed::ToolUsage::Main);

    auto g = Altseed::Graphics::GetInstance();
    EXPECT_TRUE(g != nullptr);

    auto t = Altseed::Tool::GetInstance();
    EXPECT_TRUE(t != nullptr);

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed::RenderedSprite::Create();
    s1->SetTexture(t1);
    s1->SetSrc(Altseed::RectF(Altseed::Vector2F(), t1->GetSize().To2F()));
    auto trans1 = Altseed::Matrix44F();
    auto trans2 = Altseed::Matrix44F();
    trans1.SetTranslation(200, 200, 0);
    trans2.SetRotationZ(0);
    s1->SetTransform(trans2 * trans1 * trans2);

    while (count++ < loopCount && g->DoEvents()) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));

        trans2.SetRotationZ(count / 100.0f);
        s1->SetTransform(trans1 * trans2 * trans1.GetInverted());

        Altseed::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = false;
        EXPECT_TRUE(g->BeginFrame(renderPassParameter));
        Altseed::Tool::GetInstance()->NewFrame();

        if (update != nullptr) update(t);

        Altseed::Renderer::GetInstance()->DrawSprite(s1);

        Altseed::Renderer::GetInstance()->Render();
        Altseed::Tool::GetInstance()->Render();

        EXPECT_TRUE(g->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Tool, Window) {
    auto flags = {
            // Altseed::ToolWindow::NoTitleBar,
            Altseed::ToolWindow::NoResize,
            Altseed::ToolWindow::NoMove,
            // Altseed::ToolWindow::NoScrollbar,
            Altseed::ToolWindow::NoScrollWithMouse,
            Altseed::ToolWindow::NoCollapse,
            // Altseed::ToolWindow::NoBackground,
            // Altseed::ToolWindow::NoBringToFrontOnFocus,
            // Altseed::ToolWindow::NoNav,
            // Altseed::ToolWindow::NoSavedSettings,
            // Altseed::ToolWindow::AlwaysAutoResize,
            // Altseed::ToolWindow::NoFocusOnAppearing,
    };

    int32_t _flag = 0;
    for (const auto& f : flags) {
        _flag |= static_cast<int32_t>(f);
    }

    auto flag = static_cast<Altseed::ToolWindow>(_flag);

    ToolTestTemplate(LoopFrames, [&flag](std::shared_ptr<Altseed::Tool> t) {
        t->SetNextWindowPos(Altseed::Vector2F());
        t->SetNextWindowSize(Altseed::Vector2F(320, 720));
        if (t->Begin(u"Window1", flag)) {
            t->Text(u"Text");
            t->End();
        }

        t->SetNextWindowPos(Altseed::Vector2F(320, 0));
        t->SetNextWindowSize(Altseed::Vector2F(320, 720));
        if (t->Begin(u"Window2", flag)) {
            t->Text(u"Text");
            t->End();
        }

        EXPECT_FALSE(t->Begin(u""));
    });
}

TEST(Tool, Text) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"Text")) {
            t->Dummy(Altseed::Vector2F(10, 10));
            t->Text(u"Normal Text");
            t->TextUnformatted(u"Unformatted");
            t->TextColored(Altseed::Color(0.0f, 0.0f, 255.0f, 255.0f), u"Blue Text");
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
            t->End();
        }
    });
}

TEST(Tool, Japanese) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"日本語")) {
            t->Dummy(Altseed::Vector2F(10, 10));
            t->Text(u"通常のテキスト");
            t->TextUnformatted(u"フォーマットされないテキスト");
            t->TextColored(Altseed::Color(0.0f, 0.0f, 255.0f, 255.0f), u"Blue Text");
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
            t->End();
        }
    });
}

TEST(Tool, Button) {
    bool isOpen = false;
    int radio = 0;
    int counter = 0;

    ToolTestTemplate(LoopFrames, [&isOpen, &radio, &counter](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"Button")) {
            if (t->Button(u"open/close##1", Altseed::Vector2F())) {
                isOpen = !isOpen;
            }
            t->SameLine();
            t->CheckBox(u"open/close##2", &isOpen);

            for (int i = 0; i < 3; i++) {
                if (t->RadioButton(format(u"Radio Button %d", i).c_str(), &radio)) {
                    radio = i;
                }
                t->SameLine();
            }
            t->Dummy(Altseed::Vector2F());
            t->Text(format(u"%d is selected", radio).c_str());

            t->PushButtonRepeat(true);

            if (t->ArrowButton(u"##left", Altseed::ToolDir::Left)) {
                counter--;
            }
            t->SameLine();
            if (t->ArrowButton(u"##right", Altseed::ToolDir::Right)) {
                counter++;
            }

            t->PopButtonRepeat();

            t->SameLine();
            t->Text(format(u"%d", counter).c_str());

            t->End();
        }

        if (isOpen) {
            if (t->Begin(u"Another Window")) {
                t->Text(u"aaaaa");
                t->End();
            }
        }
    });
}

TEST(Tool, Input) {
    int current = 0;

    ToolTestTemplate(LoopFrames, [&current](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"Input")) {
            t->LabelText(u"label", u"value");

            const char16_t* items = u"AAA\tBBB\tCCC";
            t->Combo(u"DropDown List", &current, items, 3);

            t->Text(format(u"Current: %d (%s)", current, Altseed::split(items, '\t')[current].c_str()).c_str());

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
                    Altseed::Vector2F(-1, t->GetTextLineHeight() * 3),
                    Altseed::ToolInputText::AllowTabInput);
            if (res != nullptr) str2 = res;

            static std::u16string buf2 = u"";
            res = t->InputTextWithHint(u"Input Numbers", u"only 0123456789.+-*/", buf2.c_str(), 256, Altseed::ToolInputText::CharsDecimal);
            if (res != nullptr) buf2 = res;

            static std::u16string bufpass = u"password123";

            res = t->InputText(
                    u"Password",
                    bufpass.c_str(),
                    16,
                    static_cast<Altseed::ToolInputText>(
                            static_cast<int32_t>(Altseed::ToolInputText::Password) |
                            static_cast<int32_t>(Altseed::ToolInputText::CharsNoBlank)));
            if (res != nullptr) bufpass = res;

            static int i0 = 123;
            static float f0 = 0.001f;
            static std::shared_ptr<Altseed::FloatArray> vec3 = Altseed::FloatArray::Create(3);

            t->InputInt(u"InputInt", &i0);
            t->InputFloat(u"InputFloat", &f0);
            t->InputFloat3(u"InputFloat3", vec3);

            t->End();
        }
    });
}

TEST(Tool, Slider) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"Slider")) {
            static int i1 = 50, i2 = 42;
            t->DragInt(u"DragInt", &i1, 1, 0, 0);
            t->DragInt(u"%", &i2, 1, 0, 100);

            t->SetNextItemWidth(100);

            static float f1 = 1.00f;
            t->DragFloat(u"DragFloat", &f1, 0.005f, 0.0f, 0.0f);

            t->SetNextItemWidth(t->GetWindowSize().X * 0.5f);

            static int i3 = 0;
            t->SliderInt(u"SliderInt", &i3, 1.0f, -1, 3);
            t->SetNextItemWidth(-100);

            static float f2 = 0.123f, f3 = 0.0f;
            t->SliderFloat(u"SliderFloat##1", &f2, 1.0f, 0.0f, 1.0f);

            static float angle = 0.0f;
            t->SliderAngle(u"Angle", &angle);  // -360から360までドラッグして変化させることができます

            static float begin = 10, end = 90;
            t->DragFloatRange2(u"range", &begin, &end, 0.2f, 0.0f, 100.0f);

            static std::shared_ptr<Altseed::FloatArray> vec3f = Altseed::FloatArray::Create(3);

            t->SliderFloat3(u"SliderFloat3", vec3f, 1.0f, 0.0f, 1.0f);

            static float x = 1.0f, y = 2.0f, z = 3.0f;
            t->PushItemWidth(70);

            t->SameLine();
            t->SliderFloat(u"X", &x, 1.0f, 0.0f, 5.0f);
            t->SameLine();
            t->SliderFloat(u"Y", &y, 1.0f, 0.0f, 5.0f);
            t->SameLine();
            t->SliderFloat(u"Z", &z, 1.0f, 0.0f, 5.0f);

            t->PopItemWidth();
            t->End();
        }
    });
}

TEST(Tool, VSlider) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"VSlider")) {
            static float values[7] = {0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f};
            for (int i = 0; i < 7; i++) {
                if (i > 0) t->SameLine();
                t->PushID(i);

                // 垂直スライダーを幅18,高さ160,最小値0,最大値1で作成します。
                t->VSliderFloat(u"##v", Altseed::Vector2F(18, 160), &values[i], 0.0f, 1.0f);

                if (t->IsItemActive() || t->IsItemHovered()) {
                    t->SetTooltip(format(u"%.3f", values[i]).c_str());
                }

                t->PopID();
            }
            t->End();
        }
    });
}

TEST(Tool, Color) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"Color")) {
            static Altseed::Color col1 = Altseed::Color(10, 20, 50, 100);
            static Altseed::Color col2 = Altseed::Color(10, 20, 50, 100);

            t->ColorEdit3(u"Color1", &col1);  // RGB
            t->ColorEdit4(u"Color2", &col2);  // RGBAのアルファ付き

            auto flag = static_cast<Altseed::ToolColorEdit>(
                    static_cast<int32_t>(Altseed::ToolColorEdit::Float) | static_cast<int32_t>(Altseed::ToolColorEdit::NoInputs) |
                    static_cast<int32_t>(Altseed::ToolColorEdit::NoLabel)

            );
            t->ColorEdit3(u"Color ID", &col1, flag);
            t->End();
        }
    });
}

TEST(Tool, ListBox) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"ListBox")) {
            const char16_t* items = u"Apple\tBanana\tCherry\tKiwi\tMango\tOrange\tPineapple\tStrawberry\tWatermelon";
            static int current = 1;

            t->ListBox(u"ListBox", &current, items, 9);

            t->End();
        }
    });
}

TEST(Tool, Selectable) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"Selectable")) {
            static bool selection[5] = {false, true, false, false, false};

            t->Selectable(u"Selectable 1", &selection[0]);
            t->Selectable(u"Selectable 2", &selection[1]);

            if (t->Selectable(u"Selectable 3", &selection[2], Altseed::ToolSelectable::AllowDoubleClick))
                if (t->IsMouseDoubleClicked(0)) selection[2] = !selection[2];

            t->Selectable(u"Selectable 5", &selection[4], Altseed::ToolSelectable::Disabled);

            t->End();
        }
    });
}

TEST(Tool, Table) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"Table")) {
            t->Columns(3, true);
            static bool selected[12] = {};
            for (int i = 0; i < 12; i++) {
                if (t->Selectable(format(u"Item %d", i).c_str(), &selected[i])) {
                    std::cout << i << std::endl;
                }
                t->NextColumn();
            }
            t->Columns(1, false);
            t->Separator();

            t->Columns(4, "columnListID");
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
                if (t->Selectable(format(u"%04d", i).c_str(), &x, Altseed::ToolSelectable::SpanAllColumns)) {
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
            t->Columns(1, false);

            t->End();
        }
    });
}

TEST(Tool, Sortable) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"Sortable")) {
            static const char16_t* item_names[] = {u"Sortable 1", u"Sortable 2", u"Sortable 3", u"Sortable 4", u"Sortable 5"};
            static const char16_t* item_current = item_names[0];
            for (int n = 0; n < 5; n++) {
                const char16_t* item = item_names[n];
                bool is_selected = (item_current == item_names[n]);
                if (t->Selectable(item, &is_selected)) item_current = item_names[n];
                if (t->IsItemActive() && !t->IsItemHovered()) {
                    int n_next = n + (t->GetMouseDragDelta(0).Y < 0.f ? -1 : 1);
                    if (n_next >= 0 && n_next < 5) {
                        item_names[n] = item_names[n_next];
                        item_names[n_next] = item;
                        t->ResetMouseDragDelta(0);
                    }
                }
            }
            t->Text(format(u"%s is selected", item_current).c_str());

            t->End();
        }
    });
}

TEST(Tool, CollapsingHeader) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"CollapsingHeader")) {
            if (t->CollapsingHeader(u"open/close field")) {
                if (t->TreeNode(u"TreeNode A")) {
                    t->Text(u"hogehoge");
                    t->TreePop();
                }

                t->SetNextItemOpen(true, Altseed::ToolCond::Once);
                if (t->TreeNode(u"TreeNode B")) {
                    t->Text(u"TreeNode B is opened");
                    t->TreePop();
                }
            }

            t->End();
        }
    });
}
TEST(Tool, Tooltip) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"Tooltip")) {
            t->TextDisabled(u"(?)");
            if (t->IsItemHovered()) {
                t->BeginTooltip();
                t->PushTextWrapPos(t->GetFontSize() * 35.0f);
                t->TextUnformatted(u"Tooltip Text");
                t->PopTextWrapPos();
                t->EndTooltip();
            }

            t->End();
        }
    });
}

TEST(Tool, Popup) {
    bool isOpen = true;
    ToolTestTemplate(LoopFrames, [&isOpen](std::shared_ptr<Altseed::Tool> t) {
        if (t->Begin(u"Popup")) {
            const char16_t* names[] = {u"AAA", u"BBB", u"CCC", u"DDD"};
            static int selected = -1;
            if (t->Button(u"Select..", Altseed::Vector2F())) {
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

            t->End();
        }
    });
}

TEST(Tool, SaveDialog) {
    auto config = Altseed::Configuration::Create();
    config->SetToolEnabled(true);
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, config));

    Altseed::Tool::GetInstance()->OpenDialog(u"png;jpg,jpeg", u"");

    Altseed::Core::Terminate();
}

TEST(Tool, Image) {
    ToolTestTemplate(LoopFrames, [](std::shared_ptr<Altseed::Tool> t) {
        static auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
        EXPECT_TRUE(t1 != nullptr);
        static auto s1 = Altseed::RenderedSprite::Create();
        s1->SetTexture(t1);

        static auto rt = Altseed::RenderTexture::Create(Altseed::Vector2I(200, 200));
        static auto camera = Altseed::RenderedCamera::Create();

        camera->SetTargetTexture(rt);

        Altseed::Renderer::GetInstance()->SetCamera(camera);
        Altseed::Renderer::GetInstance()->DrawSprite(s1);
        Altseed::Renderer::GetInstance()->Render();

        if (t->Begin(u"Image")) {
            t->Image(t1, Altseed::Vector2F(100, 100));
            t->ImageButton(t1, Altseed::Vector2F(100, 100));
            t->ImageButton(rt, Altseed::Vector2F(100, 100));
            t->ImageButton(t1, Altseed::Vector2F(100, 100));
            t->End();
        }
    });
}
