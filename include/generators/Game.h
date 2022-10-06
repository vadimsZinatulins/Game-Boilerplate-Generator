#pragma once

namespace gbg::generators {

class Game {
public:
	Game() = default;
	~Game() = default;

	void generate() const;
	void setWithSDL2ImageExtra(bool flag);
private:
	void generateHeader() const;

	bool m_withSDL2ImageExtra { false };
};

}
