#include <iostream>

template <class T> class UniquePtr {

public:

    UniquePtr(T* name) : u_name(name) {}

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept {

        std::swap(u_name, other.u_name);
    }

    ~UniquePtr() {

        if (u_name != nullptr) {

            delete u_name;
            u_name = nullptr;
        }
    }

    UniquePtr& operator = (const UniquePtr&) = delete;

    UniquePtr& operator = (UniquePtr&& other) noexcept {

        if (this != other) {
            std::swap(u_name, other, u_name);
            return *this;
        }
    }

    void operator = (T symbol) {

        *u_name = symbol;
    }

    UniquePtr& operator * () {

       return *this;
    }

    const T operator * () const {

        return *u_name;
    }

    T* release() {

        T* name = u_name;
        u_name = nullptr;
        return *name;
    }

    friend std::ostream& operator << (std::ostream&, const UniquePtr& symbol) {

        return std::cout << *symbol.u_name;
    }

private:

    T* u_name = nullptr;
    unsigned int u_size = 0;
};

int main()
{
    UniquePtr<int> unique_int(new int);
    *unique_int = 5;
    std::cout << *unique_int << std::endl;

    const UniquePtr<int> CONST_VALUE(new int(2));
    std::cout << *CONST_VALUE << std::endl;
}