# mruby-murmurhash1

murmurhash1 digest.

```ruby
puts Murmurhash1::digest('mruby') #=> "\xdc\x1f\x3f\x3f"
```

## Installation

Write in build_config.rb

```ruby
MRuby::Build.new do |conf|
  conf.gem :github => 'ksss/mruby-murmurhash1', :branch => 'master'
end
```

and exec.

```
rake clean
rake test
rake
mruby -e 'puts Murmurhash1::digest("mruby")'
```
