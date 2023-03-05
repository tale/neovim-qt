#ifndef NEOVIM_QT_SERVER
#define NEOVIM_QT_SERVER

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

#include "app.h"

struct MultiWindowState {
	QString path;
	NeovimQt::MainWindow *window;
};

class TcpServer : public QObject {
	Q_OBJECT

public:
	explicit TcpServer(QObject *parent = nullptr);
	void registerWindow(QCommandLineParser &parser, NeovimQt::MainWindow *window);

private slots:
	void newConnection();
	void readyRead();

private:
	QTcpServer *server;
	QTcpSocket *client;
	QList<MultiWindowState> windows;
};

#endif // NEOVIM_QT_SERVER
