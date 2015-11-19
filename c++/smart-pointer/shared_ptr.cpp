#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

namespace {

class Book final {
public:
    explicit Book(const std::string& name)
            : m_name(name) {
        std::cout << "New Book[name=" << m_name << "]" << std::endl;
    }

    ~Book() {
        std::cout << "Delete Book[name=" << m_name << "]" << std::endl;
    }

    std::string GetName() const {
        return m_name;
    }

private:
    std::string m_name;

    Book(const Book&);
    void operator=(const Book&);
};

} // unnamed namespace

static void readBook(const std::shared_ptr<Book>& book) {
    std::cout << "Read Book[name=" << book->GetName() << "]" << std::endl;
}

static void readBook(const Book* book) {
    std::cout << "Read Book[name=" << book->GetName() << "]" << std::endl;
}

int main(void) {
    std::shared_ptr<Book> book = std::make_shared<Book>("foo");
    readBook(book);
    readBook(book.get());
    return 0;
}
