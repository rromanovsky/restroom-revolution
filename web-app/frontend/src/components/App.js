import React from 'react';
import '../styles/index.scss';
import Room from './Room';

export default class App extends React.Component {

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

    const things = this.props.things;

    if (_.isEmpty(things)) {
      return <div className="room">No WC found</div>
    }

    return Object.keys(things).map(thing => {
      return <Room key={thing} {...things[thing]} />
    });
  }

  render() {
    return (
      <div className="app-container">
        <div className="main-section">
          <h1>WC Rooms</h1>

          <div className="rooms">
            {this.renderContent()}
          </div>

        </div>
      </div>
    );
  }
}