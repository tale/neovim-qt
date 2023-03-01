#include "socket.h"

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	Socket socket;
	socket.connectToServer(argc, argv);
	return app.exec();
}
