#pragma once
#include <boost/json/src.hpp>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace iestade {

const char KEY_PATH_DELIMITER = '/';

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

bool bool_from_json(const std::string& file_path, const std::string& key_path)
{
    return value_from_json(file_path, key_path).get_bool();
}

double double_from_json(const std::string& file_path,
                        const std::string& key_path)
{
    return value_from_json(file_path, key_path).to_number<double>();
}

size_t size_t_from_json(const std::string& file_path,
                        const std::string& key_path)
{
    return value_from_json(file_path, key_path).to_number<size_t>();
}

const std::string string_from_json(const std::string& file_path,
                                   const std::string& key_path)
{
    return value_from_json(file_path, key_path).as_string().c_str();
}

}  // namespace iestade
