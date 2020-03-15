#include "RenderedText.h"
#include "../../Math/Vector4F.h"
#include "../BuiltinShader.h"
#include "../Graphics.h"

namespace Altseed {

std::shared_ptr<RenderedText> RenderedText::Create() {
    auto t = MakeAsdShared<RenderedText>();

    auto shader = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::FontUnlitPS);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(ShaderStageType::Pixel, shader);

    t->SetMaterial(material);
    t->SetText(u"");
    t->SetColor(Color(TextureDefaultColor, TextureDefaultColor, TextureDefaultColor, TextureDefaultColor));

    return t;
}

}  // namespace Altseed