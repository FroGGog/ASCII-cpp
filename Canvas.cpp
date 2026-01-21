#include "Canvas.hpp"
#include "CanvasIterators.hpp"
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <iostream>


namespace plotter
{

    Canvas::Canvas(int width, int height, char background_char)
        : width_(width), height_(height), background_(background_char), data_(width * height, background_char) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Canvas dimensions must be positive");
        }
    }

    Canvas::Canvas(Canvas&& other) noexcept
        : width_(other.width_), height_(other.height_), background_(other.background_), data_(std::move(other.data_)) {
        other.width_ = 0;
        other.height_ = 0;
        other.background_ = ' ';
    }

    Canvas& Canvas::operator=(const Canvas& other) {
        if (this != &other) {
            width_ = other.width_;
            height_ = other.height_;
            background_ = other.background_;
            data_ = other.data_;
        }
        return *this;
    }

    Canvas& Canvas::operator=(Canvas&& other) noexcept {
        if (this != &other) {
            width_ = other.width_;
            height_ = other.height_;
            background_ = other.background_;
            data_ = std::move(other.data_);
            other.width_ = 0;
            other.height_ = 0;
            other.background_ = ' ';
        }
        return *this;
    }

    int Canvas::Width() const noexcept { return width_; }
    int Canvas::Height() const noexcept { return height_; }
    int Canvas::Size() const noexcept { return width_ * height_; }

    bool Canvas::InBounds(int x, int y) const noexcept {
        return x >= 0 && x < width_ && y >= 0 && y < height_;
    }

    char& Canvas::at(int x, int y) {
        if (!InBounds(x, y)) {
            throw std::out_of_range("Canvas::at: out of bounds");
        }
        return data_[y * width_ + x];
    }

    const char& Canvas::at(int x, int y) const {
        if (!InBounds(x, y)) {
            throw std::out_of_range("Canvas::at: out of bounds");
        }
        return data_[y * width_ + x];
    }

    char& Canvas::operator()(int x, int y) noexcept {
        return data_[y * width_ + x];
    }

    const char& Canvas::operator()(int x, int y) const noexcept {
        return data_[y * width_ + x];
    }

    void Canvas::FillRegion(int x1, int y1, int x2, int y2, char fill_char) 
    {
        int left = std::min(x1, x2);
        int right = std::max(x1, x2);
        int top = std::min(y1, y2);
        int bottom = std::max(y1, y2);

        for (int y = top; y <= bottom; ++y) 
        {
            for (int x = left; x <= right; ++x) 
            {
                if (InBounds(x, y)) 
                {
                    (*this)(x, y) = fill_char;
                }
            }
        }
    }

    void Canvas::Render(std::ostream& os) const {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            os << data_[y * width_ + x];
        }
        os << '\n';
    }
    os.flush();
}

    void Canvas::SaveToFile(const std::filesystem::path& filepath) const 
    {
        auto parent = filepath.parent_path();
        if (!parent.empty()) {
            std::filesystem::create_directories(parent);
        }
        std::ofstream file(filepath);
        if (!file) {
            throw std::runtime_error("Cannot open file for writing: " + filepath.string());
        }
        Render(file);
    }

    void Canvas::SaveToFile(const std::string& filename) const 
    {
        SaveToFile(std::filesystem::path(filename));
    }

    void Canvas::Clear(char fill_char) 
    {
        std::fill(data_.begin(), data_.end(), fill_char);
    }

    Canvas::RowIterator Canvas::RowBegin(int row) {
    if (row < 0 || row >= height_) throw std::out_of_range("Row out of bounds");
    return RowIterator(this, row, 0);
}

    Canvas::RowIterator Canvas::RowEnd(int row) {
        if (row < 0 || row >= height_) throw std::out_of_range("Row out of bounds");
        return RowIterator(this, row, width_);
    }

    Canvas::ColumnIterator Canvas::ColBegin(int col) {
        if (col < 0 || col >= width_) throw std::out_of_range("Column out of bounds");
        return ColumnIterator(this, col, 0);
    }

    Canvas::ColumnIterator Canvas::ColEnd(int col) {
        if (col < 0 || col >= width_) throw std::out_of_range("Column out of bounds");
        return ColumnIterator(this, col, height_);
    }

    Canvas::PixelIterator Canvas::begin() {
        return PixelIterator(this, 0);
    }

    Canvas::PixelIterator Canvas::end() {
        return PixelIterator(this, static_cast<size_t>(width_ * height_));
    }


} // namespace plotter