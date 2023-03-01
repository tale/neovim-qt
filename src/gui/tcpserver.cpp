#include "tcpserver.h"
#include "app.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QFileInfo>

TcpServer::TcpServer(QObject *parent) : QObject(parent) {
	server = new QTcpServer(this);
	connect(server, &QTcpServer::newConnection, this, &TcpServer::newConnection);

	if(!server->listen(QHostAddress::LocalHost, 2401)) {
		qDebug() << "Failed to start TCP Server";
	} else {
		qDebug() << "TCP Server started";
	}
}

void TcpServer::newConnection() {
	qDebug() << "New Connection";
	client = server->nextPendingConnection();

	connect(client, &QAbstractSocket::disconnected, client, &QObject::deleteLater);
	connect(client, &QAbstractSocket::readyRead, this, &TcpServer::readyRead);
}

void TcpServer::readyRead() {
	QByteArray data = client->readAll();
	QList<QByteArray> list = data.split('\n');
	int argc = list.size();

	char *argv[argc];
	for (int i = 0; i < argc; i++) {
		argv[i] = list[i].data();
	}

	NeovimQt::App::openWindowFromCommandLine(argc, argv);
	client->disconnectFromHost();
	client->disconnect();
}
