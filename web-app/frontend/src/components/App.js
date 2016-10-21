import React from 'react';
import '../styles/index.scss';

class App extends React.Component {
  componentDidMount() {
    this.props.fetchData();
  }

  render() {
    return (
      <div className="app-container">
        <div className="main-section">
          <h1>Restroom Revolution</h1>
          {JSON.stringify(this.props.data)}
        </div>
      </div>
    );
  }
}

export default App;
