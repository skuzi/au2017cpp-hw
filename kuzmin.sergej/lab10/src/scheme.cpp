#include "scheme.h"
#include <utility>
#include <cstddef>

Scheme::Scheme(int capacity):
    size(0), figures_(new Figure*[capacity]) {}

Scheme::~Scheme() {
    for(int i = 0; i < size; i++)
        delete figures_[i];
    delete [] figures_;
}

void Scheme::push_back_figure(Figure* fg) {
    figures_[size++] = fg;
}

void Scheme::remove_figure(int id) {
    for(int i = 0; i < size - 1; i++)
        if(figures_[i]->get_id() == id)
            std::swap(figures_[i], figures_[i + 1]);
    delete figures_[--size];
}

void Scheme::print_all_figures() {
    for(int i = 0; i < size; i++)
        figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
    for(int i = 0; i < size; i++)
        if(figures_[i]->get_id() == id)
            figures_[i]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
    for(int i = 0; i < size; i++)
        if(figures_[i]->is_inside(x, y))
            return figures_[i];
    return NULL;
}

void Scheme::move(int id, int new_x, int new_y) {
    for(int i = 0; i < size; i++)
        if(figures_[i]->get_id() == id)
            figures_[i]->move(new_x, new_y);
}
