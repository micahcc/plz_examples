#include <future>
#include <memory>
#include <vector>

struct Data {
    Data() {
        size = 1000;
        data = new int[size];
    }
    ~Data() { delete[] data; }
    size_t size;
    int* data;
};

void foo(const std::shared_ptr<Data>& mydata) {
    for (size_t i = 0; i < mydata->size; ++i) {
        mydata->data[i] = 0;
    }
};

int main() {
    std::vector<std::future<void>> futs;
    for (size_t i = 0; i < 10; ++i) {
        auto ptr = std::make_shared<Data>();
        futs.push_back(std::async([&]() { foo(ptr); }));
    }

    for (auto& fut : futs) {
        fut.wait();
    }
}
