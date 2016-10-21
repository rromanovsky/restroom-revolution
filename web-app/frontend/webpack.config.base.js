var path = require('path');
var WebpackShellPlugin = require('webpack-shell-plugin');

module.exports = {
  entry: ['whatwg-fetch', './src/index'],
  output: {
    path: path.join(__dirname, 'bin'),
    filename: 'index.bundle.js',
  },
  module: {
    loaders: [
      {
        test: /\.js$/,
        loader: 'babel',
        exclude: /node_modules/,
        query: {
          presets: ['es2015', 'stage-0', 'react'],
        },
      },
      {
        test: /\.scss$/,
        loaders: ['style', 'css', 'sass'],
      },
      {
        test: /\.(otf|ttf|jpg|png)$/,
        loader: 'file',
      },
    ],
  },
  plugins: [
    new WebpackShellPlugin({
      onBuildStart: ['npm install; npm prune'],
    }),
  ],
};
