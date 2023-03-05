#ifndef NEOVIM_QT_SERVER
#define NEOVIM_QT_SERVER

#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

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
