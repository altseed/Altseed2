#pragma once

#include "../Graphics/Graphics.h"

namespace Altseed {

class Tool {
private:
	// command
public:
    void BeginFrame();

    void EndFrame();

	void Render();
};

}  // namespace Altseed