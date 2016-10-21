var webpack = require('webpack')
var baseConfig = require('./webpack.config.base')
var CleanWebpackPlugin = require('clean-webpack-plugin')


module.exports = Object.assign(baseConfig, {
    
    plugins: baseConfig.plugins.concat([
        new webpack.DefinePlugin({
            'process.env':{
                'NODE_ENV': JSON.stringify('production')
            }
        }),
        new CleanWebpackPlugin(['bin', 'docs']),
        new webpack.optimize.UglifyJsPlugin(),
        new webpack.optimize.DedupePlugin()
    ])
})
