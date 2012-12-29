#include <assert.h>
#include <stdint.h>

//
// dynamic buffer implementation
//
class DBuf {

public:

  DBuf(size_t initial_capa) {
    _data = (char*)malloc(initial_capa);
    assert(_data);
    _capa = initial_capa;
    if (_capa < 16) _capa = 16;
    _size = 0;
  }

  ~DBuf() {
    assert(_data);
    free(_data);
    _data = NULL;
  }

  void append(const void *data, size_t sz) {
    if (_size + sz > _capa) {
      resize(_size + sz);
    }
    assert(_size + sz <= _capa);
    memcpy(_data + _size, data, sz);
    _size += sz;
  }

  void append(const char *str) {
    append(str, strlen(str));
  }

  void append_num(uint64_t num) {
    char buf[21]; // 2**64 < 10**20 (+ 1 NUL byte)
    int sz = snprintf(buf, 21, "%ld", num);
    assert(sz > 0 && sz < 21);
    append(buf, sz);
  }

  void reset() {
    _size = 0;
  }

  char* data() { return _data; }
  size_t size() { return _size; }

  void operator <<(const char *str) {
    append(str);
  }

  //
  // Eleminate the first n elements in the buffer.
  // Reduces size by n.
  //
  void shift_left(size_t n) {
    assert(n <= _size);
    if (n == 0) return;
    _size -= n;
    memmove(_data, _data+n, _size);
  }

  /*
   * Make sure that there is enough capacity for "more" bytes in the buffer. 
   */
  void reserve_more(size_t more) {
    resize(_size + more);
  }

  void resize_if_full() {
    if (_size == _capa) {
      resize(_capa * 2);
    }
  }

  char* end_ptr() {
    return _data + _size;
  }

  size_t free_capa() {
    return _capa - _size;
  }

  void increase_size(size_t sz) {
    assert(_size + sz <= _capa);
    _size += sz;
  }

private:

  char  *_data;
  size_t _capa;
  size_t _size;

  void resize(size_t at_least) {
    if (_capa >= at_least) return;
    while (_capa < at_least) _capa *= 2;
    assert(_capa >= at_least);
    _data = (char*) realloc(_data, _capa);
    assert(_data);
  }

};
