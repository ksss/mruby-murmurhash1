#include <mruby.h>
#include <mruby/string.h>

#define MURMURHASH_MAGIC 0x5bd1e995

static inline size_t
murmur1(uint32_t h, const uint8_t r)
{
  const uint32_t m = MURMURHASH_MAGIC;
  h *= m;
  h ^= h >> r;
  return h;
}

static uint32_t
murmur_hash_process1(char *str, int length)
{
  const uint32_t m = MURMURHASH_MAGIC;
  const uint8_t r = 16;
  uint32_t h;
  const char* p;

  p = str;
  h = length * m;

  while (4 <= length) {
    h += *(uint32_t*)p;
    h = murmur1(h, r);
    p += 4;
    length -= 4;
  }

  switch (length) {
    case 3:
      h += p[2] << 16;
    case 2:
      h += p[1] << 8;
    case 1:
      h += p[0];
      h = murmur1(h, r);
  }

  h = murmur1(h, 10);
  h = murmur1(h, 17);

  return h;
}

static mrb_value
mrb_murmurhash1_digest(mrb_state *mrb, mrb_value self)
{
  mrb_value str;
  uint32_t value;
  uint8_t digest[4];

  mrb_get_args(mrb, "S", &str);
  value = murmur_hash_process1(RSTRING_PTR(str), RSTRING_LEN(str));

  digest[0] = value >> 24;
  digest[1] = value >> 16;
  digest[2] = value >> 8;
  digest[3] = value;

  return mrb_str_new(mrb, (char*) digest, 4);
}

void
mrb_mruby_murmurhash1_gem_init(mrb_state *mrb)
{
  struct RClass *mMurmurhash1 = mrb_define_module(mrb, "Murmurhash1");
  mrb_define_class_method(mrb, mMurmurhash1, "digest", mrb_murmurhash1_digest, ARGS_REQ(1));
}

void
mrb_mruby_murmurhash1_gem_final(mrb_state *mrb)
{
}
