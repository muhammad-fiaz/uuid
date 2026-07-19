# Contributing to uuid

Thank you for your interest in contributing to uuid! This document provides guidelines for contributing.

## How to Contribute

1. **Fork** the repository
2. **Clone** your fork: `git clone https://github.com/your-username/uuid.git`
3. **Create** a feature branch: `git checkout -b feature/my-feature`
4. **Make** your changes
5. **Add** tests for new functionality
6. **Ensure** all tests pass: `cmake -B build -DUUID_BUILD_TESTS=ON && cmake --build build && ctest --test-dir build`
7. **Commit** with a clear message
8. **Push** to your fork
9. **Open** a pull request

## Development Setup

```bash
git clone https://github.com/muhammad-fiaz/uuid.git
cd uuid
cmake -B build -DUUID_BUILD_TESTS=ON -DUUID_BUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

## Code Style

- Follow C99 standard (no compiler extensions)
- Use 4-space indentation
- Use descriptive variable names
- Document all public API functions
- Keep functions short and focused
- Prefer readability over cleverness

## Testing

- Every public API must have corresponding tests
- Tests must pass on all supported platforms
- Add edge case tests for new functionality
- Run sanitizers (ASAN, UBSAN) before submitting

## Commit Messages

- Use clear, descriptive commit messages
- Start with a verb in imperative mood
- Reference issues when applicable

Example:
```
Add UUID v7 monotonic counter overflow detection

- Added counter overflow check within same millisecond
- Returns UUID_E_OVERFLOW when counter exceeds 12 bits
- Added corresponding unit test

Closes #42
```

## Pull Request Guidelines

- Keep PRs focused on a single change
- Include tests for new features
- Update documentation if needed
- Ensure CI passes
- Be responsive to review feedback

## Reporting Bugs

Use the [bug report template](https://github.com/muhammad-fiaz/uuid/issues/new?template=bug_report.yml) when reporting bugs. Include:

- uuid version
- Compiler and version
- Operating system
- Minimal reproduction code
- Expected vs actual behavior

## Requesting Features

Use the [feature request template](https://github.com/muhammad-fiaz/uuid/issues/new?template=feature_request.yml). Describe:

- The feature you want
- Why you need it
- Proposed API (if any)

## Code of Conduct

Be respectful and inclusive. See [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
