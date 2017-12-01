#ifndef SINGLETON_H
#define SINGLETON_H


class Singleton{
public:
    static Singleton& get_instance(){
        static Singleton instance;
        return instance;
    }
private:
    Singleton() = default;
    //
public:
    //Singleton();
    Singleton(const Singleton& s) = delete;
    Singleton& operator=(const Singleton& s) = delete;
    ~Singleton();
};
#endif // SINGLETON_H
