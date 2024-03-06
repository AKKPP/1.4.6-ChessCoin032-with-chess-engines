#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QObject>

class OptionsModel;
class AddressTableModel;
class TransactionTableModel;
class CWallet;

QT_BEGIN_NAMESPACE
class QDateTime;
class QTimer;
QT_END_NAMESPACE

enum NumConnections {
    CONNECTIONS_NONE = 0,
    CONNECTIONS_IN = (1U << 0),
    CONNECTIONS_OUT = (1U << 1),
    CONNECTIONS_ALL = (CONNECTIONS_IN | CONNECTIONS_OUT),
};


/** Model for Bitcoin network client. */
class ClientModel : public QObject
{
    Q_OBJECT
public:
    explicit ClientModel(OptionsModel *optionsModel, QObject *parent = 0);
    ~ClientModel();

    OptionsModel *getOptionsModel();

    int getNumConnections(uint8_t flags = CONNECTIONS_ALL) const;
    int getNumBlocks() const;
    int getNumBlocksAtStartup();

    quint64 getTotalBytesRecv() const;
    quint64 getTotalBytesSent() const;

    QDateTime getLastBlockDate() const;

    //! Return true if client connected to testnet
    bool isTestNet() const;
    //! Return true if core is doing initial block download
    bool inInitialBlockDownload() const;
    //! Return conservative estimate of total number of blocks, or 0 if unknown
    int getNumBlocksOfPeers() const;
    //! Return warnings to be displayed in status bar
    QString getStatusBarWarnings() const;

    QString formatFullVersion() const;
    QString formatBuildDate() const;
    QString clientName() const;
    QString clientAgent() const;
    QString formatClientStartupTime() const;

private:
    OptionsModel *optionsModel;

    int cachedNumBlocks;
    int cachedNumBlocksOfPeers;

    int numBlocksAtStartup;

#ifdef TIMERMODE
    QTimer *pollTimer;
#else
    QThread* const pollThread;
#endif

    void subscribeToCoreSignals();
    void unsubscribeFromCoreSignals();
signals:
    void numConnectionsChanged(int count);
    void numBlocksChanged(int count, int countOfPeers);
    void bytesChanged(quint64 totalBytesIn, quint64 totalBytesOut);

    //! Asynchronous error notification
    void error(const QString &title, const QString &message, bool modal);

public slots:
#ifdef TIMERMODE
    void updateTimer();
#endif
    void updateNumConnections(int numConnections);
    void updateAlert(const QString &hash, int status);
    void updateBlocksNumber(int bestHeight, int totalBlock);
};

#endif // CLIENTMODEL_H
