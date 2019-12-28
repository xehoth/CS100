if [ -d tmp ]; then
  rm -r tmp
fi
if [ -d bin ]; then
  rm -r bin
fi
mkdir tmp && mkdir bin && cd tmp && cmake .. -DCMAKE_BUILD_TYPE=Release && make -j4 && cd .. && cp tmp/test/test_* bin/ && rm -r tmp
