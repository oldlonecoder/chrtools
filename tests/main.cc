#include <chrtools/strbrk.h>


int main()
{

    strbrk::config_data data={"/Id/", "/", strbrk::keep};
    std::cout << "strbrk: " << '\n';
    strbrk words;
    auto count = words(data);
    std::cout << "count = " << count << "\n";
    for(auto const& w : data.words)
        std::cout << "[" << w() << "]\n";

    return 0;
}
