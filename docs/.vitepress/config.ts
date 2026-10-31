import { defineConfig } from 'vitepress'
import llmstxt from 'vitepress-plugin-llms'

const siteName = 'uuid'
const siteDescription = 'Production-grade UUID library for C/C++ implementing RFC 9562'
const siteUrl = 'https://muhammad-fiaz.github.io'
const siteBase = '/uuid/'
const defaultOgImage = `${siteUrl}${siteBase}logo.svg`

function toDocPath(relativePath: string): string {
  const normalized = relativePath.replace(/\\/g, '/').replace(/\.md$/, '')
  if (normalized === '' || normalized === 'index') return ''
  if (normalized.endsWith('/index')) return normalized.slice(0, -'index'.length)
  return normalized
}

function toCanonicalUrl(relativePath: string): string {
  const docPath = toDocPath(relativePath)
  if (!docPath) return `${siteUrl}${siteBase}`
  // cleanUrls is disabled: regular pages are published as .html files while
  // directory index pages keep their trailing slash.
  return docPath.endsWith('/')
    ? `${siteUrl}${siteBase}${docPath}`
    : `${siteUrl}${siteBase}${docPath}.html`
}

function toAbsoluteUrl(pathOrUrl: string): string {
  if (/^https?:\/\//i.test(pathOrUrl)) return pathOrUrl
  const cleaned = pathOrUrl.startsWith('/') ? pathOrUrl.slice(1) : pathOrUrl
  return `${siteUrl}${siteBase}${cleaned}`
}

function toBreadcrumbHead(pageData: { relativePath: string; title?: string | null }): any[] {
  if (pageData.relativePath === '404.md') return []
  const docPath = toDocPath(pageData.relativePath)
  const parts = docPath.split('/').filter(Boolean)
  if (parts.length === 0) return []

  return [
    [
      'script',
      { type: 'application/ld+json' },
      JSON.stringify({
        '@context': 'https://schema.org',
        '@type': 'BreadcrumbList',
        itemListElement: [
          { '@type': 'ListItem', position: 1, name: 'Home', item: `${siteUrl}${siteBase}` },
          {
            '@type': 'ListItem',
            position: 2,
            name: pageData.title || parts[parts.length - 1],
            item: toCanonicalUrl(pageData.relativePath),
          },
        ],
      }),
    ],
  ]
}

export default defineConfig({
    title: siteName,
    description: siteDescription,
    lang: 'en-US',
    base: siteBase,

    srcDir: '.',

    lastUpdated: true,
    cleanUrls: false,

    vite: {
      plugins: [llmstxt()]
    },

    head: [
      ['meta', { name: 'author', content: 'Muhammad Fiaz' }],
      [
        'meta',
        {
          name: 'keywords',
          content:
            'uuid, GUID, C, C++, RFC 9562, RFC 4122, UUID generation, UUID v1, UUID v4, UUID v7'
        }
      ],
      ['meta', { name: 'robots', content: 'index, follow' }],

      // Favicon
      ['link', { rel: 'icon', type: 'image/svg+xml', href: `${siteBase}favicon.svg` }],
      ['link', { rel: 'manifest', href: `${siteBase}manifest.json` }],
      ['meta', { name: 'theme-color', content: '#2563eb' }],

      // Open Graph
      ['meta', { property: 'og:type', content: 'website' }],
      ['meta', { property: 'og:site_name', content: siteName }],

      // Twitter Card
      ['meta', { name: 'twitter:card', content: 'summary_large_image' }],
      ['meta', { name: 'twitter:site', content: '@muhammadfiaz_' }],
      ['meta', { name: 'twitter:creator', content: '@muhammadfiaz_' }],

      // Google Analytics
      [
        'script',
        {
          async: 'true',
          src: 'https://www.googletagmanager.com/gtag/js?id=G-6BVYCRK57P'
        }
      ],
      [
        'script',
        {},
        `window.dataLayer = window.dataLayer || [];
function gtag(){dataLayer.push(arguments);}
gtag('js', new Date());
gtag('config', 'G-6BVYCRK57P');`
      ],

      // Google Tag Manager
      [
        'script',
        {},
        `(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
})(window,document,'script','dataLayer','GTM-P4M9T8ZR');`
      ],

      // Google AdSense
      [
        'script',
        {
          async: 'true',
          src: 'https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js?client=ca-pub-2040560600290490',
          crossorigin: 'anonymous'
        }
      ],

      // Microsoft Clarity
      [
        'script',
        {},
        `(function(c,l,a,r,i,t,y){
          c[a]=c[a]||function(){(c[a].q=c[a].q||[]).push(arguments)};
          t=l.createElement(r);t.async=1;t.src="https://www.clarity.ms/tag/"+i;
          y=l.getElementsByTagName(r)[0];y.parentNode.insertBefore(t,y);
        })(window, document, "clarity", "script", "z5vdzih779");`
      ],

      // JSON-LD Structured Data
      [
        'script',
        { type: 'application/ld+json' },
        JSON.stringify({
          '@context': 'https://schema.org',
          '@type': 'SoftwareSourceCode',
          name: siteName,
          description: siteDescription,
          url: `${siteUrl}${siteBase}`,
          codeRepository: 'https://github.com/muhammad-fiaz/uuid',
          author: {
            '@type': 'Person',
            name: 'Muhammad Fiaz',
            url: 'https://muhammadfiaz.com',
            sameAs: [
              'https://github.com/muhammad-fiaz',
              'https://linkedin.com/in/muhammad-fiaz-',
              'https://x.com/muhammadfiaz_'
            ]
          },
          programmingLanguage: ['C', 'C++'],
          license: 'https://opensource.org/licenses/MIT',
          keywords: [
            'uuid',
            'GUID',
            'RFC 9562',
            'UUID generation',
            'C library'
          ]
        })
      ]
    ],
    transformHead: ({ pageData }) => {
      const frontmatterTitle = typeof pageData.frontmatter.title === 'string'
        ? pageData.frontmatter.title
        : ''
      const title = frontmatterTitle || pageData.title || siteName
      const description = typeof pageData.description === 'string' && pageData.description
        ? pageData.description
        : siteDescription
      const canonical = toCanonicalUrl(pageData.relativePath)
      const frontmatterOgImage = typeof pageData.frontmatter.ogImage === 'string'
        ? pageData.frontmatter.ogImage
        : ''
      const ogImage = frontmatterOgImage ? toAbsoluteUrl(frontmatterOgImage) : defaultOgImage
      const ogTitle = title === siteName ? siteName : `${title} | ${siteName}`

      return [
        ...(pageData.relativePath === '404.md'
          ? []
          : [['link', { rel: 'canonical', href: canonical }]]),
        ['meta', { property: 'og:title', content: ogTitle }],
        ['meta', { property: 'og:description', content: description }],
        ['meta', { property: 'og:url', content: canonical }],
        ['meta', { property: 'og:image', content: ogImage }],
        ['meta', { name: 'twitter:title', content: ogTitle }],
        ['meta', { name: 'twitter:description', content: description }],
        ['meta', { name: 'twitter:image', content: ogImage }],
        ...toBreadcrumbHead(pageData)
      ]
    },

    transformHtml(html) {
      const noscript = `<noscript><iframe src="https://www.googletagmanager.com/ns.html?id=GTM-P4M9T8ZR" height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>`
      return html.replace(/<body([^>]*)>/, `<body$1>\n    ${noscript}`)
    },

    themeConfig: {
      logo: '/logo.svg',
      siteTitle: 'uuid',

      nav: [
        { text: 'Home', link: '/' },
        { text: 'Guide', link: '/guide/getting-started' },
        { text: 'API', link: '/api/overview' },
        { text: 'Examples', link: '/examples/' },
        {
          text: 'Support',
          items: [
            {
              text: 'Sponsor',
              link: 'https://github.com/sponsors/muhammad-fiaz'
            },
            {
              text: 'Donate',
              link: 'https://buymeacoffee.com/muhammadfiaz'
            }
          ]
        },
        {
          text: 'v0.1.0',
          items: []
        }
      ],

      sidebar: [
        {
          text: 'Introduction',
          items: [
            { text: 'Getting Started', link: '/guide/getting-started' },
            { text: 'Installation', link: '/guide/installation' },
            { text: 'Quick Start', link: '/guide/quick-start' }
          ]
        },
        {
          text: 'Guide',
          items: [
            { text: 'Overview', link: '/guide/overview' },
            { text: 'C++ Compatibility', link: '/guide/cpp-compat' },
            { text: 'Thread Safety', link: '/guide/thread-safety' },
            { text: 'Memory Model', link: '/guide/memory' },
            { text: 'Platforms', link: '/guide/platforms' },
            { text: 'Performance', link: '/guide/performance' },
            { text: 'Advanced Usage', link: '/guide/advanced' }
          ]
        },
        {
          text: 'UUID Versions',
          items: [
            { text: 'Overview', link: '/uuid/overview' },
            { text: 'Nil & Max UUID', link: '/uuid/special' },
            { text: 'UUID v1 (Time-based)', link: '/uuid/v1' },
            { text: 'UUID v3 (MD5 Name-based)', link: '/uuid/v3' },
            { text: 'UUID v4 (Random)', link: '/uuid/v4' },
            { text: 'UUID v5 (SHA-1 Name-based)', link: '/uuid/v5' },
            { text: 'UUID v6 (Reordered Time)', link: '/uuid/v6' },
            { text: 'UUID v7 (Unix Epoch Time)', link: '/uuid/v7' },
            { text: 'UUID v8 (Custom)', link: '/uuid/v8' },
            { text: 'Namespaces', link: '/uuid/namespaces' }
          ]
        },
        {
          text: 'API Reference',
          items: [
            { text: 'Overview', link: '/api/overview' },
            { text: 'Initialization', link: '/api/initialization' },
            { text: 'Generation', link: '/api/generation' },
            { text: 'Parsing', link: '/api/parsing' },
            { text: 'Formatting', link: '/api/formatting' },
            { text: 'Validation', link: '/api/validation' },
            { text: 'Comparison', link: '/api/comparison' },
            { text: 'Sorting', link: '/api/sorting' },
            { text: 'Hashing', link: '/api/hashing' },
            { text: 'Byte Access', link: '/api/byte-access' },
            { text: 'Serialization', link: '/api/serialization' },
            { text: 'Namespaces', link: '/api/namespaces' },
            { text: 'Errors', link: '/api/errors' },
            { text: 'Version Info', link: '/api/version' }
          ]
        },
        {
          text: 'Examples',
          items: [
            { text: 'Overview', link: '/examples/' },
            { text: 'Basic Usage', link: '/examples/basic' },
            { text: 'UUID v1', link: '/examples/v1' },
            { text: 'UUID v3', link: '/examples/v3' },
            { text: 'UUID v4', link: '/examples/v4' },
            { text: 'UUID v5', link: '/examples/v5' },
            { text: 'UUID v6', link: '/examples/v6' },
            { text: 'UUID v7', link: '/examples/v7' },
            { text: 'UUID v8', link: '/examples/v8' },
            { text: 'Parsing', link: '/examples/parsing' },
            { text: 'Formatting', link: '/examples/formatting' },
            { text: 'Validation', link: '/examples/validation' },
            { text: 'Comparison & Sorting', link: '/examples/comparison' },
            { text: 'Serialization', link: '/examples/serialization' },
            { text: 'Thread Safety', link: '/examples/threading' },
            { text: 'Error Handling', link: '/examples/error-handling' },
            { text: 'Custom UUID', link: '/examples/custom-uuid' },
            { text: 'Binary Conversion', link: '/examples/binary-conversion' }
          ]
        },
        {
          text: 'Resources',
          items: [
            { text: 'FAQ', link: '/faq/' },
            { text: 'Contributing', link: '/contributing/' },
            { text: 'Security', link: '/security/' }
          ]
        }
      ],

      socialLinks: [
        { icon: 'github', link: 'https://github.com/muhammad-fiaz/uuid' },
        { icon: 'linkedin', link: 'https://linkedin.com/in/muhammad-fiaz-' },
        { icon: 'x', link: 'https://x.com/muhammadfiaz_' }
      ],

      editLink: {
        pattern:
          'https://github.com/muhammad-fiaz/uuid/edit/main/docs/:path',
        text: 'Edit this page on GitHub'
      },

      footer: {
        message: 'Released under the MIT License.',
        copyright: 'Copyright © 2026 Muhammad Fiaz'
      },

      search: {
        provider: 'local'
      }
    },

    sitemap: {
      hostname: 'https://muhammad-fiaz.github.io/uuid/'
    }
  })
