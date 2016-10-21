var webpack = require('webpack');
var baseConfig = require('./webpack.config.base');

module.exports = Object.assign(baseConfig, {
  debug: true,
  devtool: '#cheap-module-eval-source-map',
  output: Object.assign({}, baseConfig.output, {
    pathinfo: true
  })
});
