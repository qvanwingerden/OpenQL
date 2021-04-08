/** \file
 * Utilities for writing report files.
 *
 * \see report.cc
 */

#pragma once

#include "ql/utils/opt.h"
#include "ql/utils/str.h"
#include "ql/utils/vec.h"
#include "ql/utils/filesystem.h"
#include "ql/plat/platform.h"
#include "ql/ir/ir.h"

namespace ql {

/**
 * Wraps OutFile such that the file is only created and written if the
 * write_report_files option is set.
 */
class ReportFile {
private:
    utils::Opt<utils::OutFile> of;
public:
    ReportFile(
        const ir::ProgramRef &program,
        const utils::Str &in_or_out,
        const utils::Str &pass_name
    );
    void write(const utils::Str &content);
    void write_kernel_statistics(
        const ir::KernelRef &kernel,
        const utils::Str &line_prefix=""
    );
    void write_totals_statistics(
        const ir::ProgramRef &program,
        const utils::Str &line_prefix=""
    );
    void close();
    template <typename T>
    ReportFile &operator<<(T &&rhs) {
        if (of) {
            *of << std::forward<T>(rhs);
        }
        return *this;
    }
};

/**
 * write qasm
 * in a file with a name that contains the program unique name and an extension defined by the pass_name
 */
void write_qasm(
    const ir::ProgramRef &program,
    const plat::PlatformRef &platform,
    const utils::Str &pass_name
);

void write_c(
    const ir::ProgramRef &program,
    const plat::PlatformRef &platform,
    const utils::Str &pass_name
);

/**
 * reports qasm
 * in a file with a name that contains the program unique name and the place from where the report is done
 */
void report_qasm(
    const ir::ProgramRef &program,
    const plat::PlatformRef &platform,
    const utils::Str &in_or_out,
    const utils::Str &pass_name
);

/**
 * report given string which is assumed to be closed by an endl by the caller
 */
void report_string(
    std::ostream &os,
    const utils::Str &s
);

/**
 * report statistics of the circuit of the given kernel
 */
void report_kernel_statistics(
    std::ostream &os,
    const ir::KernelRef &kernel,
    const utils::Str &line_prefix = ""
);

/**
 * reports only the totals of the statistics of the circuits of the given kernels
 */
void report_totals_statistics(
    std::ostream &os,
    const ir::ProgramRef &program,
    const utils::Str &line_prefix = ""
);

/**
 * reports the statistics of the circuits of the given kernels individually and in total
 * by appending them to the report file of the given program and place from where the report is done;
 * this report file is first created/truncated
 *
 * report_statistics is used in the cases where there is no pass specific data to report
 * otherwise, the sequence of calls in here has to be copied and supplemented by some report_string calls
 */
void report_statistics(
    const ir::ProgramRef &program,
    const plat::PlatformRef &platform,
    const utils::Str &in_or_out,
    const utils::Str &pass_name,
    const utils::Str &comment_prefix,
    const utils::Str &additionalStatistics = ""
);

} // namespace ql
