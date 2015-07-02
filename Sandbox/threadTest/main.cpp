#include <iostream>
#include <vector>

#include "jbuffer_test.h"
#include "JoysticThreads.h"

using namespace std;
int main()
{
	MockJoystick* joystick = new MockJoystick();
	JoystickBuffer* buffer = new JoystickBuffer();
	MockRobotLinker* link = new MockRobotLinker();

	JoystickThread* jthread = new JoystickThread(joystick, buffer);
	RobotLinkThread* rthread = new RobotLinkThread(buffer, link);

	jthread->start();
	rthread->start();

	int i;
	std::cin >> i;
	return 0;
}
