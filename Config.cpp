#include "Config.hpp"
#include "json.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace plotter {

std::vector<char> Config::ParsePalette(const std::string& palette_str) {
    return std::vector<char>(palette_str.begin(), palette_str.end());
}

bool Config::ValidateConfig(const PlotterConfig& config) {
    if (config.width <= 0 || config.height <= 0) return false;
    if (config.plotter_type != "basic" && config.plotter_type != "grayscale") return false;
    return true;
}

PlotterConfig Config::LoadFromString(std::istream& json_str) {
    auto doc = Load(json_str);
    const auto& root = doc.GetRoot();

    PlotterConfig config;
    config.width = root.AsMap().at("width").AsInt();
    config.height = root.AsMap().at("height").AsInt();
    config.background_char = root.AsMap().at("background_char").AsString()[0];
    config.plotter_type = root.AsMap().at("plotter_type").AsString();

    if (root.AsMap().count("palette")) {
        config.palette = ParsePalette(root.AsMap().at("palette").AsString());
    } else {
        config.palette.clear();
    }

    if (!ValidateConfig(config)) {
        throw std::runtime_error("Invalid config");
    }
    return config;
}

PlotterConfig Config::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Cannot open config file: " + filename);
    }
    return LoadFromString(file);
}

PlotterConfig Config::DefaultConfig() {
    return {
        .width = 80,
        .height = 25,
        .background_char = ' ',
        .palette = {},
        .plotter_type = "basic"
    };
}

} // namespace plotter