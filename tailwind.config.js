/** @type {import('tailwindcss').Config} */
module.exports = {
  darkMode: 'class', // 必须是 'class'，否则 dark: 类不生效
  content: [ './frontend.html', ],// 扫描根目录的 frontend.html
  theme: { extend: {}, },
  plugins: [],
}