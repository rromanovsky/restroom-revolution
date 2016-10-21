import React from 'react';
import '../styles/index.scss';

class App extends React.Component {

  componentDidMount() {
    this.props.fetchData();
  }

  renderContent() {
    if (this.props.error) {
      return <p className="error-msg">{this.props.error}</p>
    }
    if (this.props.loading) {
      return <h4>Loading data... Please wait for another hour...</h4>
    }

    return JSON.stringify(this.props.data)
  }

  render() {
    return (
      <div className="app-container">
        <div className="main-section">
          <h1>Restroom Revolution</h1>


          <div className="rooms">
            <div className="room">1</div>
            <div className="room">2</div>
            <div className="room">3</div>
          </div>

          <div>{this.renderContent()}</div>

        </div>
      </div>
    );
  }
}

export default App;
