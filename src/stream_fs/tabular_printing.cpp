#include <iomanip>
#include "tabular_printing.h"

void cppchallenge::stream_fs::print_processes(std::ostream &out, std::vector<cppchallenge::stream_fs::Proc> proc_list) {
    std::sort(proc_list.begin(), proc_list.end(), [](const auto& proc1, const auto& proc2) {
        return proc1.name < proc2.name;
    });

    const char FILL(' ');

    static const int SMALL_COLUMN(10);
    static const int MEDIUM_COLUMN(15);
    static const int LARGE_COLUMN(25);

    for (auto& proc : proc_list) {
        out << std::left << std::setw(LARGE_COLUMN) << std::setfill(FILL) << proc.name;
        out << std::left << std::setw(SMALL_COLUMN) << std::setfill(FILL) << proc.id;
        out << std::left << std::setw(SMALL_COLUMN) << std::setfill(FILL) << Proc::status_to_text(proc.status);
        out << std::left << std::setw(MEDIUM_COLUMN) << std::setfill(FILL) << proc.account;
        out << std::right << std::setw(SMALL_COLUMN) << std::setfill(FILL) << proc.mem_size / 1024;
        out << std::setw(SMALL_COLUMN) << Proc::platform_to_text(proc.platform);
        out << '\n';
    }
}
