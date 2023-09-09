#pragma once

auto ISCENE_H_TEMPLATE { R"(#pragma once

struct SDL_Renderer;

namespace be {

class IScene {
public:
	IScene() = default;
	virtual ~IScene() = default;
	
	virtual void initialize() = 0;
	virtual void shutdown() = 0;
	
	virtual void update() = 0;
	virtual void render(SDL_Renderer *renderer) = 0;
};

} // namespace be
)" };