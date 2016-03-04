#include <iostream>
#include <memory>

static void func(const std::shared_ptr<int> sptr_int) {
    std::cout << "func: " << *sptr_int.get() << std::endl;
}

int main(void) {
    std::unique_ptr<int> uptr_int(new int(1));
    std::shared_ptr<int> sptr_int = std::move(uptr_int);
    std::cout << "main: " << *sptr_int.get() << std::endl;
    func(sptr_int);
    return 0;
}
