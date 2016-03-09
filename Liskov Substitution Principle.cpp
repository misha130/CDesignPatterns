#include <QCoreApplication>
#include <QDebug>


class Rectangle{
protected:
    int width,height;
public:
    Rectangle(const int width, const int height):
        width{width},
        height{height}{}
    virtual int GetWidth() const
    {
        return width;
    }

    virtual void SetWidth(const int width){
        this->width = width;
    }

    virtual int GetHeight() const
    {
        return height;
    }

    virtual void SetHeight(const int height){
       this->height = height;
    }

    int Area() const {return width* height;}
};

class Square: public Rectangle{ //this class violates the liskov substituion
public:
    Square(int size):Rectangle{size,size}{}
    void SetWidth(const int width) override{
        this->width = height = width;
    }
    void SetHeight(const int height) override{
        this->height = width = height;
    }
    //Instead it is advised to use set sized:
    void SetSize(const int size){
        this->height = width = size;
    }
};

void process(Rectangle& r){
    int w = r.GetWidth();
    r.SetHeight(10);
    qDebug() << "Area of rectangle is " << w * 10;
    qDebug() << "we got :" << r.Area();
}

struct RectangelFactory{ //better approach
    static Rectangle CreateRectangle(int w,int h);
    static Rectangle CreateSquare(int size);
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Rectangle r{5,5};
    Square s{5}; //NEVER HAVE A SQUARE CLASS AT ALL
    process(s);
    return a.exec();
}
