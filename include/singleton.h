#ifndef SINGLETON_H_
#define SINGLETON_H_


class Singleton {
public:
    static Singleton& get_instance() {
        static Singleton instance;
        return instance;
    }
private:
    Singleton() = default;
    //
public:
    Singleton(const Singleton& s) = delete;
    Singleton& operator=(const Singleton& s) = delete;
    ~Singleton();
};

#endif // SINGLETON_H_
