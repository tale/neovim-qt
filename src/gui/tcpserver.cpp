#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent) {
	server = new QTcpServer(this);
	windows = QList<MultiWindowState>();

	connect(server, &QTcpServer::newConnection, this, &TcpServer::newConnection);

	if(!server->listen(QHostAddress::LocalHost, 2401)) {
		qDebug() << "Failed to start TCP Server";
	} else {
		qDebug() << "TCP Server started";
	}
}

void TcpServer::registerWindow(QCommandLineParser &parser, NeovimQt::MainWindow *window) {
	MultiWindowState state = {
		parser.positionalArguments().at(0),
		window
	};

	windows.append(state);
	qDebug() << "Tracking: " << windows.length() << " windows";
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

	QStringList arguments;
	for (int i = 0; i < argc; ++i) {
		arguments << QString::fromLocal8Bit(list[i].data());
	}

	QCommandLineParser parser;
	NeovimQt::App::processCommandlineOptions(parser, arguments);

	// Search for already existing windows
	for (int i = 0; i < windows.size(); i++) {
		if (windows[i].path == parser.positionalArguments().at(0)) {
			// Window already exists so we should focus it
			windows[i].window->activateWindow();
			windows[i].window->raise();

			qDebug() << "Found existing window for path: " << windows[i].path;
			client->disconnectFromHost();
			client->disconnect();
			return;
		}
	}

	NeovimQt::MainWindow *window = NeovimQt::App::openWindowFromCommandLine(parser);
	qDebug() << "Opened new window for path: " << parser.positionalArguments().at(0);

	registerWindow(parser, window);
	client->disconnectFromHost();
	client->disconnect();
}
