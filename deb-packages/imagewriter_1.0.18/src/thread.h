#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QString>

class Thread : public QThread
{
public:

    explicit Thread(QString s);

    void run();

private:
    QString name;

};

#endif // THREAD_H
