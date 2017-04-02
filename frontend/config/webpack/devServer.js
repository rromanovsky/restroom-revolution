import webpack from 'webpack';
import DevServer from 'webpack-dev-server';
import config from './dev.config';

const { host, port, ...serverConfig } = config.devServer;
const server = new DevServer(webpack(config), serverConfig);

server.listen(port, host, (error) => {
  if (error) {
    return console.error(error);
  }

  console.log(`Listening at http://${host}:${port}`);
});
