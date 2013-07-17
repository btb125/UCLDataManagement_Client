#ifndef SERVERINFORMATION_H
#define SERVERINFORMATION_H

#include <QObject>

#include <string>

#include <QTcpSocket>

class ServerInformation : public QObject
{
    Q_OBJECT
public:
    static ServerInformation* getInstance() ;

    QTcpSocket* getSocket() ;
    std::string getIPAddress() ;
    int getPort() ;

signals:

public slots:

private:
    explicit ServerInformation(QObject *parent = 0) ;
    ServerInformation(ServerInformation&) ;

    static ServerInformation* _instance ;

    QTcpSocket *socket ;
    std::string ipAddress ;
    int port ;

private slots:

};

#endif // SERVERINFORMATION_H
