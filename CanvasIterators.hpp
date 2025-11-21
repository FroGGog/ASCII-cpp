#pragma once
#include "Canvas.hpp"

namespace plotter
{

class Canvas::RowIterator
{
public:
    // Реализуйте методы класса

private:
    Canvas* canvas_;
    int row_;
    int col_;
};

class Canvas::ColumnIterator
{
public:
    // Реализуйте методы класса

private:
    Canvas* canvas_;
    int col_;
    int row_;
};

class Canvas::PixelIterator
{
public:
    // Реализуйте методы класса

private:
    Canvas* canvas_;
    size_t pos_;
};


} // namespace plotter