#pragma once
#include <boost/json/src.hpp>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace iestaade {

const char KEY_PATH_DELIMITER    = '/';
const bool DEFAULT_BOOL          = false;
const double DEFAULT_DOUBLE      = -1.0;
const size_t DEFAULT_SIZE_T      = SIZE_T_MAX;
const std::string DEFAULT_STRING = "undefined";

boost::json::value value_from_json(const std::string& file_path,
                                   const std::string& key_path)
{
    const std::ifstream t(file_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    boost::json::value v = boost::json::parse(buffer.str());
    assert(!v.is_null());

    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(key_path);
    while (getline(ss, token, KEY_PATH_DELIMITER)) {
        tokens.push_back(token);
    }
    assert(!tokens.empty());

    for (size_t i = 0; i < tokens.size(); i++) {
        if (!v.as_object().if_contains(tokens[i])) {
            throw std::runtime_error("field not found: \"" + key_path +
                                     "\" in \"" + file_path + "\"");
        }
        v = v.at(tokens[i]);
    }
    return v;
}

bool bool_from_json(const std::string& file_path,
                    const std::string& key_path,
                    bool optional      = false,
                    bool default_value = DEFAULT_BOOL)
{
    bool v;
    try {
        v = value_from_json(file_path, key_path).get_bool();
    }
    catch (const std::runtime_error& e) {
        if (!optional) {
            return default_value;
        }
        throw;
    }
    return v;
}

double double_from_json(const std::string& file_path,
                        const std::string& key_path,
                        bool optional        = false,
                        double default_value = DEFAULT_BOOL)
{
    double v;
    try {
        v = value_from_json(file_path, key_path).to_number<double>();
    }
    catch (const std::runtime_error& e) {
        if (optional) {
            return default_value;
        }
        throw;
    }
    return v;
}

size_t size_t_from_json(const std::string& file_path,
                        const std::string& key_path,
                        bool optional        = false,
                        size_t default_value = DEFAULT_SIZE_T)
{
    size_t v;
    try {
        v = value_from_json(file_path, key_path).to_number<size_t>();
    }
    catch (const std::runtime_error& e) {
        if (optional) {
            return default_value;
        }
        throw;
    }
    return v;
}

const std::string string_from_json(
        const std::string& file_path,
        const std::string& key_path,
        bool optional                    = false,
        const std::string& default_value = DEFAULT_STRING)
{
    std::string v;
    try {
        v = value_from_json(file_path, key_path).as_string().c_str();
    }
    catch (const std::runtime_error& e) {
        if (optional) {
            return default_value;
        }
        throw;
    }
    return v;
}

}  // namespace iestaade
