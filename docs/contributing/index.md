# Contributing

How to contribute to the uuid library.

## Getting Started

1. Fork the repository
2. Clone your fork
3. Create a feature branch
4. Make your changes
5. Add tests
6. Run the test suite
7. Submit a pull request

## Development Setup

```bash
git clone https://github.com/your-username/uuid.git
cd uuid
cmake -B build -DUUID_BUILD_TESTS=ON -DUUID_BUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

## Code Style

- C99 standard (no compiler extensions)
- 4-space indentation
- Descriptive variable names
- Document all public API functions
- Keep functions short and focused

## Testing

- Every public API must have tests
- Tests must pass on all platforms
- Add edge case tests
- Run sanitizers before submitting

## Commit Messages

Use clear, descriptive messages:

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

## Code of Conduct

Be respectful and inclusive. See [CODE_OF_CONDUCT.md](https://github.com/muhammad-fiaz/uuid/blob/main/CODE_OF_CONDUCT.md).
