#include <injeqt/injector.h>
#include <injeqt/module.h>
#include <QCoreApplication>
#include <QtCore/QObject>
#include <iostream>
#include <memory>

class ILogger:public QObject{

    Q_OBJECT
    public:
    virtual ~ILogger();

    virtual void Log(const QString &s) = 0;
};
class ConsoleLogger :ILogger
{
public:
    void Log(const QString &s) override{
        std::cout << s.toStdString() << std::endl;
    }

};

class Engine:public QObject{
    Q_OBJECT

    float volume = 5;
    int horse_power = 400;


public:
    int execute(){
        return volume * horse_power;
    }
};


class Engine_Factory:public QObject{
    Q_OBJECT


  public:
      Q_INVOKABLE Engine_Factory() {}
      virtual ~Engine_Factory() {}

      Q_INVOKABLE Engine * create_service()
      {
          return new Engine{};
      }
};
class world_service : public QObject
{
    Q_OBJECT

public:
    world_service() {}
    virtual ~world_service() {}

    std::string say_world() const
    {
        return {"Ready"};
    }
};
class Car:public QObject{
    Q_OBJECT

public:
    Q_INVOKABLE  Car():
        _l{nullptr}, _e{nullptr} {
        _l->Log("Created car");
    }
    void drive()
       {
          int locationDrove = location + _e->execute();
          std::cout << "Car drove from" << location << " To " << locationDrove << std::endl;
          location = locationDrove;
       }
    virtual ~Car();

private slots:
    INJEQT_INIT void init()
    {
        std::cerr << "all services set" << std::endl;
    }

    INJEQT_DONE void done()
    {
        std::cerr << "ready for destruction" << std::endl;
    }

    INJEQT_SET void set_engine(Engine *e)
    {
        _e = e;
    }

    INJEQT_SET void set_logger(ILogger *l)
    {
        _l = l;
    }
    private:
        Engine *_e;
        ILogger *_l;
        int location = 0;
};

class module : public injeqt::module
{
public:
    explicit module()
    {
        _w = std::unique_ptr<world_service>{new world_service{}};
        add_type<Car>();
        add_type<Engine_Factory>();
        add_factory<Engine, Engine_Factory>();
        add_ready_object<world_service>(_w.get());
    }

    virtual ~module() { return;};

private:
    std::unique_ptr<world_service> _w;
};
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
       auto modules = std::vector<std::unique_ptr<injeqt::module>>{};
       modules.emplace_back(std::unique_ptr<injeqt::module>{new module{}});

      auto injector = injeqt::injector{std::move(modules)};
      auto client = injector.get<Car>();
      client->drive();
    return a.exec();
}
