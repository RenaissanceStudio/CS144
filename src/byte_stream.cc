#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), bytes_written( 0L ), bytes_read( 0L ) {}

bool Writer::is_closed() const
{
  return closed_;
}

void Writer::push( const string& data )
{
  const string& substr = data.substr( 0, min( (uint64_t)data.length(), available_capacity() ) );
  str += substr;
  bytes_written += (uint64_t)substr.length();
}

void Writer::close()
{
  closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - (uint64_t)str.length();
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_written;
}

bool Reader::is_finished() const
{
  return closed_ && str.empty();
}

uint64_t Reader::bytes_popped() const
{
  return bytes_read;
}

string_view Reader::peek() const
{
  return string_view( str );
}

void Reader::pop( uint64_t len )
{
  len = min( len, (uint64_t)str.length() );
  bytes_read += len;

  str = str.substr( len );
}

uint64_t Reader::bytes_buffered() const
{
  return (uint64_t)str.length();
}
