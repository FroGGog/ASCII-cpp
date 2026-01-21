#pragma once
#include "Canvas.hpp"

namespace plotter
{

    class Canvas::RowIterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char*;
        using reference = char&;
        using iterator_category = std::random_access_iterator_tag;

        RowIterator(Canvas* canvas, int row, int col) : canvas_(canvas), row_(row), col_(col) {}

        reference operator*() { return (*canvas_)(col_, row_); }
        pointer operator->() { return &(*canvas_)(col_, row_); }
        reference operator[](difference_type n) { return (*canvas_)(col_ + n, row_); }

        RowIterator& operator++() { ++col_; return *this; }
        RowIterator operator++(int) { auto tmp = *this; ++(*this); return tmp; }
        RowIterator& operator--() { --col_; return *this; }
        RowIterator operator--(int) { auto tmp = *this; --(*this); return tmp; }
        RowIterator& operator+=(difference_type n) { col_ += n; return *this; }
        RowIterator& operator-=(difference_type n) { col_ -= n; return *this; }
        RowIterator operator+(difference_type n) const { return RowIterator(canvas_, row_, col_ + n); }
        RowIterator operator-(difference_type n) const { return RowIterator(canvas_, row_, col_ - n); }
        difference_type operator-(const RowIterator& other) const { return col_ - other.col_; }

        bool operator==(const RowIterator& other) const { return row_ == other.row_ && col_ == other.col_; }
        bool operator!=(const RowIterator& other) const { return !(*this == other); }

        bool operator<(const RowIterator& other) const { return col_ < other.col_; }
        // остальные сравнения — аналогично

    private:
        Canvas* canvas_;
        int row_;
        int col_;
    };

    class Canvas::ColumnIterator 
    {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = char;
            using pointer = char*;
            using reference = char&;
            using iterator_category = std::random_access_iterator_tag;

            ColumnIterator(Canvas* canvas, int col, int row) : canvas_(canvas), col_(col), row_(row) {}

            reference operator*() { return (*canvas_)(col_, row_); }
            pointer operator->() { return &(*canvas_)(col_, row_); }
            reference operator[](difference_type n) { return (*canvas_)(col_, row_ + n); }

            ColumnIterator& operator++() { ++row_; return *this; }
            ColumnIterator operator++(int) { auto tmp = *this; ++(*this); return tmp; }
            // ... остальные операторы аналогично RowIterator

            bool operator==(const ColumnIterator& other) const { return col_ == other.col_ && row_ == other.row_; }
            bool operator!=(const ColumnIterator& other) const { return !(*this == other); }

        private:
            Canvas* canvas_;
            int col_;
            int row_;
    };

    class Canvas::PixelIterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char*;
        using reference = char&;
        using iterator_category = std::random_access_iterator_tag;

        PixelIterator(Canvas* canvas, size_t pos) : canvas_(canvas), pos_(pos) {}

        reference operator*() { return canvas_->data_[pos_]; }
        pointer operator->() { return &canvas_->data_[pos_]; }
        reference operator[](difference_type n) { return canvas_->data_[pos_ + n]; }

        PixelIterator& operator++() { ++pos_; return *this; }
        PixelIterator operator++(int) { auto tmp = *this; ++(*this); return tmp; }
        PixelIterator& operator--() { --pos_; return *this; }
        PixelIterator operator--(int) { auto tmp = *this; --(*this); return tmp; }
        PixelIterator& operator+=(difference_type n) { pos_ += n; return *this; }
        PixelIterator& operator-=(difference_type n) { pos_ -= n; return *this; }
        PixelIterator operator+(difference_type n) const { return PixelIterator(canvas_, pos_ + n); }
        PixelIterator operator-(difference_type n) const { return PixelIterator(canvas_, pos_ - n); }
        difference_type operator-(const PixelIterator& other) const { return pos_ - other.pos_; }

        bool operator==(const PixelIterator& other) const { return pos_ == other.pos_; }
        bool operator!=(const PixelIterator& other) const { return !(*this == other); }

        bool operator<(const PixelIterator& other) const { return pos_ < other.pos_; }
        bool operator<=(const PixelIterator& other) const { return pos_ <= other.pos_; }
        bool operator>(const PixelIterator& other) const { return pos_ > other.pos_; }
        bool operator>=(const PixelIterator& other) const { return pos_ >= other.pos_; }

    private:
        Canvas* canvas_;
        size_t pos_;
    };


} // namespace plotter