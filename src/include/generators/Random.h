#pragma once

namespace gbg::generators {

class Random
{
public:
	Random() = default;
	~Random() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;
};

}
