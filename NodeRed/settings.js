module.exports = {
  uiPort: process.env.PORT || 1880,
  uiHost: "127.0.0.1",
  userDir: './workspace',

  // The file containing the flows. If not set, it defaults to flows_<hostname>.json
  //flowFile: 'flows.json',


  // Node-RED scans the `nodes` directory in the install directory to find nodes.
  // The following property can be used to specify an additional directory to scan.
  //nodesDir: '/home/nol/.node-red/nodes',
}
