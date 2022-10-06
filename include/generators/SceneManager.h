#pragma once

namespace gbg::generators {

class SceneManager {
public:
	SceneManager() = default;
	~SceneManager() = default;

	void generate() const;
private:
	void generateSceneManagerHeader() const;
	void generateSceneManagerSource() const;

	void generateSceneHeader() const;

	void generateMainMenuSceneHeader() const;
	void generateMainMenuSceneSource() const;
};

}
