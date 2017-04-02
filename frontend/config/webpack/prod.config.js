import webpack from 'webpack';
import { smartStrategy } from 'webpack-merge';
import baseConfig from './base.config';

const merge = smartStrategy({
  entry: 'prepend',
});

export default merge(baseConfig, {
  plugins: [
    new webpack.optimize.UglifyJsPlugin({
      compress: {
        warnings: false,
      },
    }),
    new webpack.NoEmitOnErrorsPlugin(),
  ],
});
