#pragma once

namespace gbg::generators {

class TextureManager {
public:
	TextureManager() = default;
	~TextureManager() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;
};

}
