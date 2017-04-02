import path from 'path';
import webpack from 'webpack';
import HtmlWebpackPlugin from 'html-webpack-plugin';
import GaugePlugin from 'gauge-webpack-plugin';
import packageJSON from '../../package.json';

const rootDir = path.resolve(__dirname, '../../');
const NODE_ENV = process.env.NODE_ENV || 'development';

export default {
  context: path.join(rootDir, 'src'),

  entry: {
    vendor: [
      'babel-polyfill',
      ...Object.keys(packageJSON.dependencies),
    ],
    app: [
      './index.js',
    ],
  },

  output: {
    path: path.join(rootDir, 'dist'),
    filename: '[name].bundle.js?[hash]',
    publicPath: '/js/',
  },

  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /(node_modules)/,
        use: [
          { loader: 'babel-loader' },
        ],
      },
      {
        test: /\.scss$/,
        use: [
          { loader: 'style-loader' },
          { loader: 'css-loader' },
          { loader: 'sass-loader' },
        ],
      },
      {
        test: /\.(eot|svg|ttf|woff|woff2)$/,
        use: [
          { loader: 'url-loader?limit=100000' },
        ],
      },
      {
        test: /\.(jpe?g|png|gif)$/,
        use: [
          {
            loader: 'file-loader',
            query: {
              name: '[name].[ext]',
              //publicPath: 'images/',
            },
          },
        ],
      },
    ],
  },

  plugins: [
    new webpack.ProvidePlugin({ React: 'react' }),
    new webpack.EnvironmentPlugin({ NODE_ENV }),
    new webpack.optimize.CommonsChunkPlugin({
      name: 'vendor',
      filename: 'vendor.bundle.js',
      publicPath: '/js/',
    }),
    new HtmlWebpackPlugin({
      template: 'index.html',
    }),
    GaugePlugin(),
  ],
};
