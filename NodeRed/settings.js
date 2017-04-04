module.exports = {
  uiPort: process.env.PORT || 1880,
  uiHost: "10.42.0.1",
  userDir: './workspace',
  flowFile: 'flows.json',
  flowFilePretty: true,

  // Node-RED scans the `nodes` directory in the install directory to find nodes.
  // The following property can be used to specify an additional directory to scan.
  //nodesDir: '/home/nol/.node-red/nodes',
}
