import { Component, PropTypes } from 'react';
import { connect } from 'react-redux';
import { createStructuredSelector } from 'reselect';
import { setRoom, getFloors } from '../../redux';
import '../styles/components/floors.scss';

class Floors extends Component {
  // @TODO
  //static propTypes = {
  //  floors: PropTypes.arrayOf(
  //    PropTypes.shape({
  //      doors: PropTypes.arrayOf(
  //        PropTypes.shape({
  //          status: PropTypes.string.isRequired,
  //        }).isRequired,
  //      ).isRequired,
  //    }).isRequired,
  //  ).isRequired,
  //};

  constructor(props) {
    super(props);
    const socket = new WebSocket('ws://192.168.2.1:1880/ws/devices'); // @TODO: move it to config

    socket.onopen = (event) => {
      console.log('WebSocket OK'); // @TODO
    };

    socket.onmessage = (event) => {
      const { state, deviceId } = JSON.parse(event.data);

      this.props.setRoom({ status: state === '1' ? 'filled' : 'free', deviceId }); // @TODO
    };
  }

  renderDoorStatus = (status) => {
    let icon
    let text;

    switch (status) {
      case 'filled':
        icon = 'fa-close';
        text = 'Занято';
        break;
      case 'time-out':
        icon = 'fa-question';
        text = 'Кажется забыли выключить свет';
        break;
      default:
        icon = 'fa-check';
        text = 'Свободно';
        break;
    }

    return (
      <div className={`door ${status}`}>
        <i className={`fa ${icon}`} />{text}
      </div>
    );
  };

  render() {
    return (
      <div className="floors row">
        {
          this.props.floors.map((floor, i) => (
            <section className="floor" key={`floor${i}`}>
              <h2>{++i} этаж</h2>
              <ul className="doors">
                {
                  console.log(floor.doors.map((door, k) => console.log(door,k)))
                }
                {
                  floor.doors.map((door, k) => (
                    <li className="door-container" key={`floor${k}`}>
                      {this.renderDoorStatus(door.status)}
                    </li>
                  ))
                }
              </ul>
            </section>
          ))
        }
      </div>
    );
  }
}

const mapStateToProps = createStructuredSelector({
  floors: getFloors,
});

const mapDispatchToProps = {
  setRoom,
};

export default connect(mapStateToProps, mapDispatchToProps)(Floors);
