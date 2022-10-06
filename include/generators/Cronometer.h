#pragma once

namespace gbg::generators {

class Cronometer {
public:
	Cronometer() = default;
	~Cronometer() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;
};

}

