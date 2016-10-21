var webpack = require('webpack');
var WebpackDevServer = require('webpack-dev-server');
var config = require('./webpack.config.dev.js');

new WebpackDevServer(
  webpack(config),
  {
    publicPath: config.devConfig.devPublicPath,
    hot: true,
    quiet: false,
    noInfo: false,
    historyApiFallback: true,
    stats: {
      colors: true,
      chunks: false,
      version: false,
      assets: false,
    }
  }
).listen(config.devConfig.devPort, config.devConfig.devHost, function (err, result) {
  if (err) {
    console.log(err);
  }

  console.log('Starting server at ' + config.devConfig.devHost + ':' + config.devConfig.devPort + '...');
  console.log('Application is available here: http://' + config.devConfig.devHost + ':' + config.devConfig.devPort + config.devConfig.devPublicPath + 'index.html\n');
});
