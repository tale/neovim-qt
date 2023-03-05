#include "tcpsocket.h"
#include <iostream>

TcpSocket::TcpSocket(QObject *parent) : QObject(parent) {
	socket = new QTcpSocket(this);
	connect(socket, &QAbstractSocket::errorOccurred, this, &TcpSocket::onError);
}

void TcpSocket::connectToServer(QStringList args) {
	qDebug() << "Connecting to TCP Server...";
	socket->connectToHost("localhost", 2401);

	if(socket->waitForConnected()) {
		for(int i = 0; i < args.length(); i++) {
			qDebug() << "Sending: " << args[i]; 
			socket->write(QByteArray(args[i].toUtf8()) + QByteArray("\n"));
		}

		socket->waitForBytesWritten();
		socket->close();
		exit(EXIT_SUCCESS);
	} else{
		QString filepath = QCoreApplication::applicationFilePath();
		if (!QProcess::startDetached(filepath, args)) {
			qWarning() << "Unable to fork into background";
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
	}
}

void TcpSocket::onError(QAbstractSocket::SocketError socketError) {
	if (socketError == QAbstractSocket::ConnectionRefusedError) {
		// Return early so this error is not printed;
		return;
	}

	qInfo() << "Error: " << socketError;
}

