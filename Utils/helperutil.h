#ifndef HELPERUTIL_H
#define HELPERUTIL_H

#include <string>
#include <vector>

#include <QProcess>
#include <QMap>

#define FALLOUT4_HARDCODE

namespace hu {

inline
QString appendQuotes(const QString& string) {
    return "\"" + string + "\"";
}

inline
QString nativeArguments(const QStringList& stringList) {
    QString out = "/c ";
    out += appendQuotes(stringList.join(" "));
    return out;
}

}
namespace overload_set {

template <typename... F>
struct overload_set : public F ... {
    using F::operator() ...;
};

template <typename... F>
overload_set(F&&... f) -> overload_set<F... >;


template <typename... Types>
struct Visitor;

template <typename T>
struct Visitor<T> { virtual void visit(T* t) = 0; };

template <typename T, typename... Types>
struct Visitor<T, Types...> : public Visitor<Types...> { // Recursive
    using Visitor<Types...>::visit;
    virtual void visit(T* t) = 0;
};

template <typename Base, typename...>
struct LambdaVisitor;

template <typename Base,
          typename T1, typename... T,
          typename F1, typename... F>
struct LambdaVisitor<Base, Visitor<T1, T...>, F1, F...>;

template <typename Base,
          typename T1, typename... T,
          typename F1, typename... F>
struct LambdaVisitor<Base, Visitor<T1, T...>, F1, F...>
        : private F1, public LambdaVisitor<Base, Visitor<T...>, F...>
{
  LambdaVisitor(F1&& f1, F&&... f)
    : F1(std::move(f1)),
      LambdaVisitor<Base, Visitor<T...>, F...>(std::forward<F>(f)...) {}
  void visit (T1* t1) override {return F1::operator()(t1); }
};

template<typename Base, typename T1, typename F1>
struct LambdaVisitor<Base, Visitor<T1>, F1> : private F1, public Base
{
    LambdaVisitor(F1&& f1) : F1(std::move(f1)) {}
    void visit(T1* t1) override { return F1::operator()(t1); }
};

class Bar;
class Baz;

using FooVisitor = Visitor<class Bar, class Baz>;

class Foo {
    std::string string_;
public:
    Foo(const std::string& string) : string_(string) {}
    std::string& string() { return string_; }
    virtual ~Foo() = default;
    virtual void accept(FooVisitor &v) = 0;
};

template <typename Derived>
class Visitable : public Foo {
public:
    using Foo::Foo;
    void accept(FooVisitor &v) { v.visit(static_cast<Derived*>(this)); }
};

class Bar : public Visitable<Bar> {
public:
    using Visitable<Bar>::Visitable;
    //Bar(const std::string& string) : Visitable<Bar>(string) {}
};

class Baz : public Visitable<Baz> {
public:
    using Visitable<Baz>::Visitable;
    //Baz(const std::string& string) : Visitable<Baz>(string) {}
};

using FooVisitor = Visitor<class Bar, class Baz>;

}

namespace vector_recycling {
using namespace std;

template <typename T>
struct number_list {
    number_list() {
        static size_t X = 10;
        if (recycling.empty())
            numbers.reserve(X);
        else {
            numbers = move(recycling.back());
            recycling.pop_back();
        }
    }
    number_list(const number_list& rhs)
        : number_list()
    {
        numbers = rhs.numbers;
    }
    ~number_list() {
        numbers.clear();
        recycling.push_back(move(numbers));
    }
    vector<T> numbers;
    static vector<vector<T>> recycling;
};
}

template<typename S = std::string>
inline
auto addQuotes(const S& s)
{
    return S{ S{"\""} + s + S{"\""} };
}

using ba2_map = QMap<QString, QString>;

#endif // HELPERUTIL_H
