#pragma once

namespace gbg::generators {

class MouseManager {
public:
	MouseManager() = default;
	~MouseManager() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;
};

}
