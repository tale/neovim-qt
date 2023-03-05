#ifndef NEOVIM_QT_SOCKET
#define NEOVIM_QT_SOCKET

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>

class TcpSocket : public QObject {
	Q_OBJECT

public:
	explicit TcpSocket(QObject *parent = nullptr);
	void connectToServer(QStringList args);

private slots:
	void onError(QAbstractSocket::SocketError socketError);

private:
	QTcpSocket *socket;
};

#endif // NEOVIM_QT_SOCKET

