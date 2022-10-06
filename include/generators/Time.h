#pragma once

namespace gbg::generators {

class Time
{
public:
	Time() = default;
	~Time() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;
};

}
