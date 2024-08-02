#include <boost/json/src.hpp>
#include <string>

// notes
#if 0
// boost usage example
std::ifstream t(config_path);
std::stringstream buffer;
buffer << t.rdbuf();
boost::json::value config = boost::json::parse(buffer.str());

g_init_p_acceptance = config.at("run_engine")
                                .at("simulated_annealing")
                                .at("init_p_acceptance")
                                .to_number<double>();

g_init_t_log_len = config.at("run_engine")
                            .at("simulated_annealing")
                            .at("init_t_log_len")
                            .to_number<size_t>();

g_stats_filename = config.at("run_engine")
                            .at("context")
                            .at("stats_filename")
                            .as_string()
                            .c_str();

// interface example
class Child : public Settings
{
    const double max_value;
    const size_t special_value;
    const std::string another_value;

    Child(bool instead_generate_jsons = true) :
        max_value(_field_double("path/to/field/max", min, max));
        special_value(_field_size_t("path/to/field/special", min, max));
        another_value(_field_string("path/to/field/another"));
}
#endif

namespace iestade {

class Settings {
public:

    Settings(const std::string& json_filepath = "", const std::string& json_schema_filepath = "") :
        _json_filepath(json_filepath),
        _json_schema_filepath(json_schema_filepath){};

    void generate_json() {}

    void generate_json_schema_template() {}

    const double max_value;

private:
    const std::string _json_filepath;
    const std::string _json_schema_filepath;

    template <typename T>
    const T _read_from_json(const std::string& json_path)
    {
    }
};

}  // namespace iestade
