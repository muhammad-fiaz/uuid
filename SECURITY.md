# Security Policy

## Supported Versions

| Version | Supported          |
|---------|--------------------|
| 0.1.x   | :white_check_mark: |

## Reporting a Vulnerability

If you discover a security vulnerability in uuid, please report it responsibly.

**Do NOT open a public GitHub issue for security vulnerabilities.**

Instead, please email: **contact@muhammadfiaz.com**

Include:
- Description of the vulnerability
- Steps to reproduce
- Potential impact
- Suggested fix (if any)

## Response Timeline

- **Acknowledgment**: Within 48 hours
- **Assessment**: Within 1 week
- **Fix**: Depends on severity (critical fixes within 1 week)

## Security Measures

- Zero third-party runtime dependencies
- Cryptographically secure random number generation (getrandom, BCryptGenRandom, arc4random_buf)
- No global mutable state
- Thread-safe by design
- No undefined behavior
- Extensive sanitizer testing (ASAN, UBSAN, TSAN)
- Static analysis in CI

## Disclosure Policy

We follow coordinated disclosure. Please give us reasonable time to address the issue before public disclosure.
