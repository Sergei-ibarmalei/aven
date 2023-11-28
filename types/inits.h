#pragma once

class Init
{
protected:
	bool init_ok = true;

public:
	bool Init_ok() const { return init_ok; }
	void Negate() {init_ok = false;}
	void Set(bool condition) {init_ok = condition;}
};
