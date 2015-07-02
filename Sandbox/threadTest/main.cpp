#include <iostream>
#include <vector>

#include "jbuffer_test.h"
#include "JoysticThreads.h"
#include "ComRobotLinker.h"

#include <QtCore\QCoreApplication>
#include <QtCore\qdebug.h>
 
#include <QtSerialPort\QSerialPort>
#include <QtSerialPort\QSerialPortInfo>
 
QT_USE_NAMESPACE
 
int mainExample(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
 
	QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
	for(QList<QSerialPortInfo>::iterator iter = list.begin(); iter != list.end(); iter++) {
		qDebug() << "Name : " << iter->portName();
		qDebug() << "Description : " << iter->description();
		qDebug() << "Manufacturer: " << iter->manufacturer();
 
		// Example use SerialPort
		QSerialPort serial;
		serial.setPort(*iter);
		if (serial.open(QIODevice::ReadWrite))
		serial.close();
	}
	
	return a.exec();
}


int main(int argc, char *argv[])
{

	//uncomment this to check the QtSerialPort example
	//return mainExample(argc, argv);

	Joystick* joystick = new MockJoystick();	//initializing a joystick
	JoystickBuffer* buffer = new JoystickBuffer();	
	RobotLinker* link = new ComRobotLinker();	//initializing a com-port connection

	JoystickThread* jthread = new JoystickThread(joystick, buffer);	//thread that reads joysick state and pushes it to the buffer
	RobotLinkThread* rthread = new RobotLinkThread(buffer, link);	//thread that reads the latest joystick state to a buffer and sends it via com-port

	jthread->start();
	rthread->start();

	int i;
	std::cin >> i;
	return 0;
}
