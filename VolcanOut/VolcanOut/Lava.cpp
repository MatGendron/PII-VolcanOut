#include "Lava.hpp"

using namespace std;

void Lava::rise() {
	if (_clock.getElapsedTime().asMilliseconds() > _speed) {
		//_x += 6;
	}
}
