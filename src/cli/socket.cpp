#include "socket.h"
#include <iostream>

Socket::Socket(QObject *parent) : QObject(parent) {
	socket = new QTcpSocket(this);

	connect(socket, &QAbstractSocket::errorOccurred, this, &Socket::onError);
}

void Socket::connectToServer(int argc, char *argv[]) {
	qDebug() << "Connecting to TCP Server...";
	socket->connectToHost("localhost", 2401);


	if(socket->waitForConnected()) {
		for(int i = 0; i < argc; i++) {
			qDebug() << "Sending: " << argv[i]; 
			socket->write(QByteArray(argv[i]) + QByteArray("\n"));
		}

		socket->waitForBytesWritten();
		socket->close();
		exit(EXIT_SUCCESS);
	} else{
		QString filepath = QCoreApplication::applicationDirPath() + "/nvim-qt";
		QStringList args;

		if (!QFileInfo::exists(filepath)) {
			qWarning() << "Unable to find nvim-qt binary";
			exit(EXIT_FAILURE);
		}

		for(int i = 1; i < argc; i++) {
			args << argv[i];
		}

		if (!QProcess::startDetached(filepath, args)) {
			qWarning() << "Unable to fork into background";
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
	}
}

void Socket::onError(QAbstractSocket::SocketError socketError) {
	qDebug() << "Error: " << socketError;
}
