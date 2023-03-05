#ifndef NEOVIM_QT_SERVER
#define NEOVIM_QT_SERVER

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

class TcpServer : public QObject {
	Q_OBJECT

public:
	explicit TcpServer(QObject *parent = nullptr);

private slots:
	void newConnection();
	void readyRead();

private:
	QTcpServer *server;
	QTcpSocket *client;
};

#endif // NEOVIM_QT_SERVER
