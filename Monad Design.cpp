#include "monad.h"


template <typename T> struct Maybe;

template<typename T> Maybe<T> maybe(T* context){
    return Maybe<T>(context);
}

template<typename T> struct Maybe{
    T* context;
    explicit Maybe(T* const context):context{context}{}

    template <typename Func>
    auto With(Func evaluator){
        if(context == nullptr)
        {
           return Maybe<typename remove_pointer<decltype(evaluator(context))>::type>(nullptr);
        }
        else
        {
            return maybe(evaluator(context));
        }
    }

    template <typename Func>
     auto Do(Func action){
        if(context != nullptr) action(context);
        return *this;
    }
};

void monad::print_house_name(Person* p){

    //HOW NOT TO

    /*if(p != nullptr && p->address != nullptr && p->address->house_name != nullptr)
    qDebug() << *p->address->house_name;*/

    //HOW TO DO IT
    maybe(p)
            .With([](auto x) { return x-> address; })
            .With([](auto x) { return x-> house_name; })
            .Do([] (auto x) { qDebug() << *x});
}
