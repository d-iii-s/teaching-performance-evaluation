#include <pin.H>

#include <map>
#include <set>
#include <mutex>
#include <atomic>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <utility>

std::atomic<UINT64> instruction_count (0);

const char *const TRACE_PREFIX = "trace";
const size_t MINIMUM_DUMP_BYTES = 256;
const size_t DUMP_SCALE = 8;

struct TraceRecord {
    const ADDRINT original_address;
    const size_t original_size;
    std::mutex translated_addresses_lock;
    std::set<ADDRINT> translated_addresses;

    TraceRecord (ADDRINT original_address_, size_t original_size_)
        : original_address (original_address_), original_size (original_size_) {}
};

std::map<ADDRINT, TraceRecord *> trace_records;

std::string hex_address (ADDRINT value) {
    std::ostringstream out;
    out << std::hex << value;
    return out.str ();
}

void dump_trace_bytes (ADDRINT address, size_t bytes_to_dump, const std::string &path) {
    if (bytes_to_dump == 0) return;

    std::vector<UINT8> buffer (bytes_to_dump);
    const size_t copied = PIN_SafeCopy (buffer.data (), reinterpret_cast<const VOID *> (address), bytes_to_dump);
    if (copied == 0) return;

    std::ofstream output (path.c_str (), std::ios::binary);
    output.write (reinterpret_cast<const char *> (buffer.data ()), static_cast<std::streamsize> (copied));
}

std::string original_dump_path (ADDRINT original_address) {
    return std::string (TRACE_PREFIX) + "-" + hex_address (original_address) + ".bin";
}

std::string translated_dump_path (ADDRINT original_address, ADDRINT translated_address) {
    return std::string (TRACE_PREFIX) + "-" + hex_address (original_address) + "-" + hex_address (translated_address) + ".bin";
}

size_t translated_dump_size (size_t original_size) {
    return std::max (MINIMUM_DUMP_BYTES, DUMP_SCALE * original_size);
}

std::pair<TraceRecord *, bool> find_or_create_trace_record (ADDRINT original_address, size_t original_size) {
    const auto iter = trace_records.find (original_address);
    if (iter != trace_records.end ()) return std::make_pair (iter->second, false);

    TraceRecord *record = new TraceRecord (original_address, original_size);
    trace_records [original_address] = record;
    return std::make_pair (record, true);
}

VOID capture_trace (TraceRecord *record) {

    // We assume the tool code is called from the app code,
    // leaving the return address to the code cache on the stack.
    const ADDRINT translated_address = reinterpret_cast<ADDRINT> (__builtin_extract_return_addr (__builtin_return_address (0)));

    {
        std::lock_guard<std::mutex> guard (record->translated_addresses_lock);
        const auto result = record->translated_addresses.insert (translated_address);
        if (!result.second) return;
    }

    dump_trace_bytes (translated_address, translated_dump_size (record->original_size), translated_dump_path (record->original_address, translated_address));
}

VOID instrument_trace (TRACE trace, VOID *val) {

    const ADDRINT original_address = TRACE_Address (trace);
    const size_t original_size = static_cast<size_t> (TRACE_Size (trace));

    BBL first_bbl = TRACE_BblHead (trace);
    if (!BBL_Valid (first_bbl)) return;

    INS first_ins = BBL_InsHead (first_bbl);
    if (!INS_Valid (first_ins)) return;

    const IMG image = IMG_FindByAddress (original_address);
    if (!IMG_Valid (image)) return;
    if (!IMG_IsMainExecutable (image)) return;

    const std::pair<TraceRecord *, bool> record_info = find_or_create_trace_record (original_address, original_size);
    TraceRecord *record = record_info.first;

    if (record_info.second) dump_trace_bytes (original_address, original_size, original_dump_path (original_address));

    INS_InsertCall (first_ins, IPOINT_BEFORE, AFUNPTR (capture_trace), IARG_PTR, record, IARG_END);
}

VOID count_instruction () {
    instruction_count ++;
}

VOID instrument_instruction (INS ins, VOID *val) {
    INS_InsertCall (ins, IPOINT_BEFORE, AFUNPTR (count_instruction), IARG_END);
}

VOID print_results (INT32 code, VOID *val) {
    LOG ("Instruction count " + decstr (instruction_count.load ()) + "\n");
}

int main (int argc, char *argv []) {
    PIN_Init (argc, argv);

    TRACE_AddInstrumentFunction (instrument_trace, NULL);
    INS_AddInstrumentFunction (instrument_instruction, NULL);
    PIN_AddFiniFunction (print_results, NULL);
    PIN_StartProgram ();

    return (0);
}
