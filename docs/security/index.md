# Security Policy

## Supported Versions

| Version | Supported |
|---------|-----------|
| 0.1.x | Yes |

## Reporting Vulnerabilities

**Do NOT open a public GitHub issue for security vulnerabilities.**

Email: **contact@muhammadfiaz.com**

Include:
- Description of the vulnerability
- Steps to reproduce
- Potential impact
- Suggested fix (if any)

## Response Timeline

- Acknowledgment: Within 48 hours
- Assessment: Within 1 week
- Fix: Depends on severity

## Security Measures

- Zero third-party runtime dependencies
- Cryptographically secure random generation
- No global mutable state
- Thread-safe by design
- Sanitizer testing (ASAN, UBSAN, TSAN)
- Static analysis in CI
