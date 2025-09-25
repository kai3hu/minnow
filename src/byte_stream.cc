#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

// Push data to stream, but only as much as available capacity allows.
void Writer::push( const string& data )
{
  // DUMMY_CODE(data);

  size_t writed_size = ( available_capacity() >= data.size()? data.size(): available_capacity());

  buffer_ += data.substr(0,writed_size);
  used_ += writed_size;
  total_write_ += writed_size;

}

// Signal that the stream has reached its ending. Nothing more will be written.
void Writer::close()
{
  input_end_ = true;
}

// Has the stream been closed?
bool Writer::is_closed() const
{
  return input_end_; 
}

// How many bytes can be pushed to the stream right now?
uint64_t Writer::available_capacity() const
{
  return capacity_ - used_; // Your code here.
}

// Total number of bytes cumulatively pushed to the stream
uint64_t Writer::bytes_pushed() const
{
  return total_write_;
}

// Peek at the next bytes in the buffer -- ideally as many as possible.
// It's not required to return a string_view of the *whole* buffer, but
// if the peeked string_view is only one byte at a time, it will probably force
// the caller to do a lot of extra work.
string_view Reader::peek() const
{
  return string_view(buffer_);
}

// Remove `len` bytes from the buffer.
void Reader::pop( uint64_t len )
{
  buffer_.erase(0,len);
  total_read_+= len;
  used_ -= len;
}

// Is the stream finished (closed and fully popped)?
bool Reader::is_finished() const
{
   return input_end_ && (used_ == 0);
}

// Number of bytes currently buffered (pushed and not popped)
uint64_t Reader::bytes_buffered() const
{
   return used_;
}

// Total number of bytes cumulatively popped from stream
uint64_t Reader::bytes_popped() const
{
    return total_read_;
}
