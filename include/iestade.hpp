#include <boost/json/src.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace iestade {

class Settings {
public:
    Settings(const std::string& config_filepath)
    {
        std::ifstream t(config_filepath);
        std::stringstream buffer;
        buffer << t.rdbuf();
        _config = boost::json::parse(buffer.str());
    };

    double field_double(const std::string& address)
    {
        return _field(address).to_number<double>();
    }

    size_t field_size_t(const std::string& address)
    {
        return _field(address).to_number<size_t>();
    }

    const std::string field_string(const std::string& address)
    {
        return _field(address).as_string().c_str();
    }

private:
    boost::json::value _config;
    const char _field_delimiter = '/';


    // field address in a format "field1/field2/field3"
    boost::json::value _field(const std::string& address)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::stringstream ss(address);
        while (getline(ss, token, _field_delimiter)) {
            tokens.push_back(token);
        }
        assert(!tokens.empty());

        boost::json::value v = _config.at(tokens[0]);
        for (size_t i = 1; i < tokens.size(); i++) {
            v = v.at(tokens[i]);
        }
        return v;
    }
};

}  // namespace iestade
