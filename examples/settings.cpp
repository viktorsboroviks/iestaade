#include <string>

#include "iestade.hpp"

class MySettings : public iestade::Settings {
public:
    const double init_p_acceptance;
    const size_t data_size;
    const std::string date_format;

    MySettings(const std::string& config_filepath) :
        Settings(config_filepath),
        init_p_acceptance(field_double("run_engine/"
                                       "simulated_annealing/"
                                       "init_p_acceptance")),
        data_size(field_size_t("run_engine/"
                               "state/"
                               "data_size")),
        date_format(field_string("run_engine/"
                                 "report/"
                                 "date_format"))
    {
    }
};

int main()
{
    MySettings s("examples/config.json");
    assert(s.init_p_acceptance == 0.97);
    assert(s.data_size == 200);
    assert(s.date_format == "%F");
    return 0;
}
