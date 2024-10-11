#include <cassert>
#include <string>

#include "iestaade.hpp"

const std::string struct_csv_file_path = "examples/data_struct.csv";
const std::string vector_csv_file_path = "examples/data_vector.csv";

struct DataRow {
    size_t i;
    double in;
    double out;
};

int main()
{
    std::vector<DataRow> data_s;
    iestaade::struct_from_csv<DataRow,
                              decltype(DataRow::i),
                              decltype(DataRow::in),
                              decltype(DataRow::out)>(struct_csv_file_path,
                                                      data_s);

    assert(data_s.size() == 10000);
    assert(data_s[0].i == 0);
    assert(data_s[0].in == -3.9342264827273885);
    assert(data_s[0].out == 0.7122046146962401);
    assert(data_s[9999].i == 9999);
    assert(data_s[9999].in == 1.6940922750500942);
    assert(data_s[9999].out == 0.9924086787558186);

    std::vector<std::vector<double>> data_v;
    iestaade::vector_from_csv<double>(vector_csv_file_path, data_v);

    assert(data_v.size() == 10000);
    assert(data_v[0][0] == 0.0);
    assert(data_v[0][1] == -3.9342264827273885);
    assert(data_v[0][2] == 0.7122046146962401);
    assert(data_v[9999][0] == 9999.0);
    assert(data_v[9999][1] == 1.6940922750500942);
    assert(data_v[9999][2] == 0.9924086787558186);
    return 0;
}
