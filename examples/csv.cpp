#include <cassert>
#include <string>

#include "iestaade.hpp"

const std::string csv_file_path = "examples/data.csv";

struct DataRow {
    size_t i;
    double in;
    double out;
};

int main()
{
    std::vector<DataRow> data;
    iestaade::vector_from_csv<DataRow,
                              decltype(DataRow::i),
                              decltype(DataRow::in),
                              decltype(DataRow::out)>(csv_file_path, data);

    assert(data.size() == 10000);
    assert(data[0].i == 0);
    assert(data[0].in == -3.9342264827273885);
    assert(data[0].out == 0.7122046146962401);
    assert(data[9999].i == 9999);
    assert(data[9999].in == 1.6940922750500942);
    assert(data[9999].out == 0.9924086787558186);

    return 0;
}
