#include <Cashe.hpp>
int main() {
    Cashe my_cache;
    my_cache.Cdirect();
    my_cache.print_experiments(my_cache, cout);
    my_cache.Creverse();
    my_cache.print_experiments(my_cache, cout);
    my_cache.Crandom();
    my_cache.print_experiments(my_cache, cout);
}