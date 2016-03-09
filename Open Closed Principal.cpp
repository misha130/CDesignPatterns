#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QDebug>

enum class Color{Red,Green,Blue,Yellow};
enum class Size{Big, Medium, Small};

struct Product{
    QString name;
    Color color;
    Size size;
};

template <typename T> struct ISpecification
{
    virtual bool is_satisfied(T* item) = 0;
};

template <typename T> struct IFilter
{
    virtual QVector<T*> filter(QVector<T*> items, ISpecification<T> &spec) =0;
};

 struct Filter: IFilter<Product>
{
   typedef QVector<Product*> Products;

      QVector<Product*> filter(QVector<Product*> items, ISpecification<Product> &spec) override
      {
        Products prods;
        foreach(Product* item, items){
            if(spec.is_satisfied(item))
                prods << item;
        }
        return prods;
      }
};

 struct ColorSpecification: ISpecification<Product>
{
    Color color;
    explicit ColorSpecification(const Color color)
        :color{color}{
    }
    bool is_satisfied(Product* item) override{
        return item->color == color;
    }
};
struct SizeSpecification: ISpecification<Product>
{
    Size size;
    explicit SizeSpecification(const Size size)
        :size{size}{
    }
    bool is_satisfied(Product* item) override{
        return item->size == size;
    }
};
template <typename T> struct AndSpecification: ISpecification<T>
{
    ISpecification<T> &first;
    ISpecification<T> &second;

    AndSpecification(ISpecification<T> &first, ISpecification<T> &second):
        first{first},
        second{second}{
    }
    bool is_satisfied(T* item) override{
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Product apple{"Apple", Color::Green, Size::Small};
    Product orange{"Orange", Color::Yellow, Size::Small};
    Product pineapple{"Pineapple", Color::Yellow, Size::Medium};
    QVector<Product*> prods{ &apple ,&orange , &pineapple};
    Filter bf;
    ColorSpecification cs(Color::Yellow);
    SizeSpecification ss(Size::Small);
    AndSpecification<Product> yellow_and_small{cs,ss};
    QVector<Product*> filterProducts = bf.filter(prods,yellow_and_small);

    foreach(Product* item, filterProducts){
      qDebug() << "Product:" << item->name;
    }

    return a.exec();
}
