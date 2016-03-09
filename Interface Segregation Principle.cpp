#include <QCoreApplication>
#include <QDebug>
#include <QVector>
struct Document;
/*
struct IMachine {
    virtual void print(QVector<Document*> docs) = 0;
    virtual void scan(QVector<Document*> docs) = 0;
    virtual void fax(QVector<Document*> docs) = 0;
};

struct MFP: IMachine{
     void print(QVector<Document*> docs) override;
     void scan(QVector<Document*> docs) override;
     void fax(QVector<Document*> docs) override;
};
*/

struct IPrinter{
    virtual void print(QVector<Document*> docs) = 0;
};

struct IScanner{
    virtual void scan(QVector<Document*> docs) = 0;
};

struct Printer: IPrinter{
    void print(QVector<Document *> docs) override;
};

struct Scanner: IScanner{
    void scan(QVector<Document *> docs) override;
};

struct IMachine: IPrinter, IScanner{

};

struct Machine: IMachine{
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter& printer, IScanner& scanner):
        printer{printer}, scanner{scanner}{}

    void print(QVector<Document*> docs) override{
        printer.print(docs);
    }
    void scan(QVector<Document*> docs) override{
        scanner.scan(docs);
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
