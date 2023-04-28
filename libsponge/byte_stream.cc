#include "byte_stream.hh"

#include <sstream>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : _capacity(capacity) { DUMMY_CODE(capacity); }

size_t ByteStream::write(const string &data) {
    DUMMY_CODE(data);
    size_t input_size{0};
    for (auto current{data.begin()}; current != data.end() && _capacity > 0;current++) {
        _buffers.push_back(*current);
        _capacity--;
        _bytes_written++;
        input_size ++;
    }

    return input_size;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    DUMMY_CODE(len);
    std::stringstream result{};
    for (auto current(_buffers.begin()); current != _buffers.end() && static_cast<size_t>(std::distance(_buffers.begin(), current)) < len; current++) {
        result << *current;
    }

    return result.str();
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    DUMMY_CODE(len);
    for (size_t remove_size{len}; remove_size > 0 && !_buffers.empty(); remove_size--, _capacity++) {
        _buffers.pop_front();
        _bytes_read++;
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    DUMMY_CODE(len);
    auto result = peek_output(len);
    pop_output(len);
    return result;
}

void ByteStream::end_input() { _is_end = true; }

bool ByteStream::input_ended() const { return _is_end; }

size_t ByteStream::buffer_size() const { return _buffers.size(); }

bool ByteStream::buffer_empty() const { return _buffers.empty(); }

bool ByteStream::eof() const { return buffer_empty() && input_ended(); }

size_t ByteStream::bytes_written() const { return _bytes_written; }

size_t ByteStream::bytes_read() const { return _bytes_read; }

size_t ByteStream::remaining_capacity() const { return _capacity; }
