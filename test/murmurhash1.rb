assert 'digest mruby' do
  Murmurhash1::digest("mruby") == "\xdc\x1f\x3f\x3f"
end

assert 'digest murmur' do
  Murmurhash1::digest("murmur") == "\xa6\xeb\xbe\x44"
end
