project('uuid', 'c',
    version: '0.1.0',
    license: 'MIT',
    description: 'Production-grade UUID library for C/C++ (RFC 9562)',
    default_options: [
        'c_std=c99',
        'warning_level=3',
        'werror=true',
    ],
)

# Sources
uuid_sources = files('src/uuid.c')

# Include directories
uuid_inc = include_directories('include')

# Static library
uuid_static = static_library('uuid',
    uuid_sources,
    include_directories: uuid_inc,
    install: true,
)

# Shared library
uuid_shared = shared_library('uuid',
    uuid_sources,
    include_directories: uuid_inc,
    install: true,
    version: '0.1.0',
    soversion: '0',
)

# Dependency declaration
uuid_dep = declare_dependency(
    include_directories: uuid_inc,
    link_with: uuid_static,
)

# Install headers
install_headers('include/uuid/uuid.h', subdir: 'uuid')

# pkg-config
pkg = import('pkgconfig')
pkg.generate(uuid_static,
    name: 'uuid',
    description: meson.project_description(),
    url: 'https://github.com/muhammad-fiaz/uuid',
)

# Tests
if get_option('tests')
    test_uuid = executable('test_uuid',
        'tests/test_uuid.c',
        include_directories: uuid_inc,
        link_with: uuid_static,
    )
    test('uuid_tests', test_uuid)
endif

# Examples
if get_option('examples')
    foreach ex : ['basic', 'v1', 'v3', 'v4', 'v5', 'v6', 'v7', 'v8', 'parsing', 'formatting', 'validation', 'comparison', 'serialization', 'threading', 'error_handling', 'custom_uuid', 'binary_conversion']
        executable('example_' + ex,
            'examples/' + ex + '.c',
            include_directories: uuid_inc,
            link_with: uuid_static,
        )
    endforeach
endif

# Benchmarks
if get_option('benchmarks')
    executable('bench_uuid',
        'benchmarks/bench_uuid.c',
        include_directories: uuid_inc,
        link_with: uuid_static,
    )
endif
