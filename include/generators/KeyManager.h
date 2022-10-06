#pragma once

namespace gbg::generators {

class KeyManager {
public:
	KeyManager() = default;
	~KeyManager() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;
};

}
