#include <iostream>
#include <locale>

class MyClass {
public:
    MyClass(int num = 0):m_num(num) {};

    MyClass(const MyClass&) = delete;

    MyClass& operator = (const MyClass& other) {
        if (this != &other) {
            m_num = other.m_num;
        }
        return *this;
    }

    int ret() {
        return m_num;
    }
private:
    int m_num = 2;
};

template <class T> class UniquePtr {
public:
    UniquePtr(T*& name) :u_name(name) {
        name = nullptr;
    }

    UniquePtr(T*& name, unsigned int size) :u_name(name), u_size(size) {
        name = nullptr;
    }

    UniquePtr(const UniquePtr&) = delete;

    ~UniquePtr() {
        if (u_name != nullptr) {
            delete u_name;
            u_name = nullptr;
        }
    }

    UniquePtr& operator = (const UniquePtr&) = delete;

    T* operator * () const {
        if (u_size > 0) {
            T* name = new T[u_size]{};

            for (int i = 0; i < u_size; i++) {
                name[i] = u_name[i];
            }
            return name;
        }
        else {
            T* name = new T();
            *name = *u_name;
            return name;
        }
    }

    T* release() {
        T* name = u_name;
        u_name = nullptr;
        return name;
    }

private:
    T* u_name = nullptr;
    unsigned int u_size = 0;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    int size = 10;
    int* arr = new int[size] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    MyClass* my_class = new MyClass(5);

    std::cout << "Адрес в сыром указателе на объект в динамической памяти." << std::endl;
    std::cout << my_class << std::endl;
   
    UniquePtr ptr(my_class);
    std::cout << my_class << "\n" << std::endl;

    std::cout << "Получения объекта." << std::endl;
    auto my_cl = *ptr;
    std::cout << my_cl << std::endl;
    std::cout << my_cl->ret() << "\n" << std::endl;

    std::cout << "Освобождение владение и возвращение сырого указателя." << std::endl;
    my_class = ptr.release();
    std::cout << my_class << std::endl;
    std::cout << my_class->ret() << "\n" << std::endl;

    std::cout << "Адрес в сыром указателе на объект в динамической памяти." << std::endl;
    std::cout << arr << std::endl;

    UniquePtr myint(arr, size);
    std::cout << arr << "\n" << std::endl;
   
    std::cout << "Получения объекта." << std::endl;
    auto ar = *myint;
    std::cout << ar << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << ar[i] << " ";
    }
    std::cout << "\n" << std::endl;

    std::cout << "Освобождение владение и возвращение сырого указателя." << std::endl;
    arr = myint.release();
    std::cout << arr << std::endl;
}