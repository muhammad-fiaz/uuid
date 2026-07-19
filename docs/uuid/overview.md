# UUID Versions Overview

The uuid library implements all UUID versions defined by RFC 9562.

## Version Summary

| Version | Type | Epoch | Precision | Sortable | Random Bits |
|---------|------|-------|-----------|----------|-------------|
| v1 | Time-based | Gregorian (1582) | 100 ns | No | Clock seq + node |
| v3 | Name-based | N/A | N/A | No | MD5 hash |
| v4 | Random | N/A | N/A | No | 122 bits |
| v5 | Name-based | N/A | N/A | No | SHA-1 hash |
| v6 | Reordered time | Gregorian (1582) | 100 ns | Yes | Clock seq + node |
| v7 | Unix epoch time | Unix (1970) | 1 ms | Yes | 12 + 14 bits |
| v8 | Custom | Custom | Custom | Custom | Custom |
| Nil | Special | N/A | N/A | N/A | None |
| Max | Special | N/A | N/A | N/A | None |

## When to Use Which Version

| Use Case | Recommended Version |
|----------|-------------------|
| Unique identifier (general) | v4 |
| Database primary key (sortable) | v7 |
| Time-ordered identifier | v7 or v6 |
| Deterministic from name | v3 or v5 |
| Legacy system compatibility | v1 |
| Vendor-specific format | v8 |
| Placeholder / null | Nil |
| Sentinel / maximum | Max |

## RFC 9562 Compliance

All versions comply with RFC 9562:
- Version bits correctly set at byte 6, high nibble
- Variant bits correctly set at byte 8 (RFC 4122 variant: `10xx`)
- Timestamps use correct epoch for each version
- Name-based UUIDs use correct hash algorithms
