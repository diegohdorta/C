#include "thread.h"
#include "utils.h"
#include <QDebug>

Thread::Thread(QString s) : name(s) { }

void Thread::run()
{
        QThread::sleep(2);

        qDebug() << this->name;

        Utils u;

        std::cerr << "bar: " << u.bar << '\n';

        u.get_github_info();

        QThread::sleep(2);


}
