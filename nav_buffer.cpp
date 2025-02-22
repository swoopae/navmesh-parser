#include "nav_buffer.h"
#include <iterator>

namespace nav_mesh
{
  nav_buffer::~nav_buffer ( )
  {
    clear ( );
  }

  void nav_buffer::load_from_file ( const std::string &nav_mesh_file, std::error_code &err )
  {
    clear ( );

    std::ifstream nav_file ( nav_mesh_file.data ( ), std::istream::binary );

    if ( !nav_file.is_open ( ) )
    {
      err = std::error_code ( 1, std::system_category ( ) );
      return;
    }

    nav_file.unsetf ( std::istream::skipws );

    nav_file.seekg ( 0, std::istream::end );
    std::streampos file_size = nav_file.tellg ( );
    nav_file.seekg ( 0, std::istream::beg );

    m_nav_buffer.reserve ( file_size );
    m_nav_buffer.insert ( m_nav_buffer.begin ( ), std::istream_iterator< std::uint8_t > ( nav_file ), std::istream_iterator< std::uint8_t > ( ) );
  }

  void nav_buffer::skip ( std::size_t bytes_to_skip )
  {
    m_bytes_read += bytes_to_skip;
  }

  void nav_buffer::clear ( )
  {
    m_nav_buffer.clear ( );
  }
} // namespace nav_mesh