var path = require('path');
var webpack = require('webpack');

var devConfig = {
  devHost: '0.0.0.0',
  devPort: 3000,
  devPublicPath: '/',
};
var config = {
  debug: true,
  devtool: '#inline-source-map',
  entry: [
    'webpack-dev-server/client?http://' + devConfig.devHost + ':' + devConfig.devPort,
    'webpack/hot/only-dev-server',
    './src/index.js',
  ],
  output: {
    publicPath: 'http://' + devConfig.devHost + ':' + devConfig.devPort + devConfig.devPublicPath,
    path: path.join(__dirname, 'bin'),
    filename: 'index.bundle.js',
  },
  plugins: [
    new webpack.HotModuleReplacementPlugin(),
  ],
  module: {
    loaders: [
      {
        test: /\.js?$/,
        exclude: /node_modules/,
        loaders: ['react-hot', 'babel'],
      },
      {
        test: /\.scss$/,
        loaders: ['style', 'css?sourceMap', 'sass?sourceMap']
      },
      {
        test: /\.(otf|ttf|jpg|png)$/,
        loader: 'file',
      },
    ],
  },
  devConfig: devConfig,
};

module.exports = config;
