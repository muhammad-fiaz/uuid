# Performance

The uuid library is optimized for high throughput.

## Benchmark Results

Run benchmarks on your machine:

```bash
cmake -B build -DUUID_BUILD_BENCHMARKS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/benchmarks/bench_uuid
```

## Typical Throughput (Linux x64, GCC 13, 100K iterations)

| Operation | Throughput | Latency |
|-----------|------------|---------|
| v4 generate | ~500K ops/sec | ~2 us/op |
| v7 generate | ~400K ops/sec | ~2.5 us/op |
| v1 generate | ~400K ops/sec | ~2.5 us/op |
| v5 generate (DNS) | ~300K ops/sec | ~3 us/op |
| parse | ~600K ops/sec | ~1.5 us/op |
| format | ~700K ops/sec | ~1.4 us/op |
| compare | ~2M ops/sec | ~0.5 us/op |
| hash | ~1M ops/sec | ~1 us/op |
| validate | ~600K ops/sec | ~1.5 us/op |

## Optimization Techniques

1. **Branchless formatting**: Hex lookup table, no branches in hot path
2. **SIMD-friendly**: UUIDs are 16-byte aligned for SIMD comparison
3. **Minimal allocations**: Only name-based UUIDs (v3, v5) allocate
4. **Platform-native random**: Uses OS-provided CSPRNG directly
5. **Thread-local state**: No locking overhead for generation

## Tips for Maximum Performance

- Use `uuid_v4()` directly instead of `uuid_v4_generate()` for thread-local state
- Use compact format for string output (no hyphens to write)
- Use `uuid_parse()` for parsing (optimized hex conversion)
- Use `uuid_compare()` directly instead of `uuid_compare_asc()` for qsort
