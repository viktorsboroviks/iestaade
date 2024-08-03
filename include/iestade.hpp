#include <boost/json/src.hpp>
#include <fstream>
#include <sstream>
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
    const boost::json::value config = boost::json::parse(buffer.str());
    assert(!config.is_null());

    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(key_path);
    while (getline(ss, token, KEY_PATH_DELIMITER)) {
        tokens.push_back(token);
    }
    assert(!tokens.empty());

    boost::json::value v = config.at(tokens[0]);
    for (size_t i = 1; i < tokens.size(); i++) {
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
