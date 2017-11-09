#include <iostream>
#include <memory>

namespace {

class Object final {
public:
    explicit Object(const std::string& name) : m_name(name) {
        std::cout << "New Object[name=" << m_name << "]" << std::endl;
    }

    ~Object() {
        std::cout << "Delete Object[name=" << m_name << "]" << std::endl;
    }

    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

    std::string GetName() const {
        return m_name;
    }

private:
    std::string m_name;
};

} // unnamed namespace


int main(void) {
    {
        Object* ptr = new Object("raw");
    }
    {
        Object* ptr = new Object("smart");
        std::unique_ptr<Object> uptr(ptr);
    }
    return 0;
}
