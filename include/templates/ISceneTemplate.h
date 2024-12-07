#pragma once

auto ISCENE_H_TEMPLATE { R"(#pragma once

struct SDL_Renderer;

namespace be {

class IScene {
public:
	struct InitializationParams {
		SDL_Renderer *renderer;
	};

	IScene() = default;
	virtual ~IScene() = default;
	
	virtual void initialize(const InitializationParams &params) = 0;
	virtual void shutdown(const InitializationParams &params) = 0;
	
	virtual void update() = 0;
	virtual void render(SDL_Renderer *renderer) = 0;
};

} // namespace be
)" };