#pragma once

const auto VULKAN_ISCENE_H_TEMPLATE { R"(#pragma once

namespace be {

class IScene {
public:
	IScene() = default;
	virtual ~IScene() = default;
	
	virtual void initialize() = 0;
	virtual void shutdown() = 0;
	
	virtual void update() = 0;
	virtual void render() = 0;
};

} // namespace be
)" };