#ifndef NEOVIM_QT_SOCKET
#define NEOVIM_QT_SOCKET

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>
#include <QProcess>

class Socket : public QObject {
	Q_OBJECT

public:
	explicit Socket(QObject *parent = nullptr);
	void connectToServer(int argc, char *argv[]);

private slots:
	void onError(QAbstractSocket::SocketError socketError);

private:
	QTcpSocket *socket;
};

#endif // NEOVIM_QT_SOCKET
