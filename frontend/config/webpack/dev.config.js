import { HotModuleReplacementPlugin } from 'webpack';
import { smartStrategy } from 'webpack-merge';
import baseConfig from './base.config';

const port = 3000;
const host = '0.0.0.0';

const merge = smartStrategy({
  entry: 'prepend',
});

export default merge(baseConfig, {
  entry: {
    app: [
      'react-hot-loader/patch',
      `webpack-dev-server/client?http://${host}:${port}/`,
      'webpack/hot/only-dev-server',
    ],
  },

  output: {
    publicPath: `http://${host}:3000/`,
  },

  plugins: [
    new HotModuleReplacementPlugin(),
  ],

  module: {
    rules: [
      {
        test: /\.scss$/,
        use: [
          {
            loader: 'css-loader',
            options: {
              sourceMap: true,
            },
          },
        ],
      },
    ],
  },

  devServer: {
    host,
    port,
    hot: true,
    noInfo: true,
  },

  devtool: 'source-map',
});
