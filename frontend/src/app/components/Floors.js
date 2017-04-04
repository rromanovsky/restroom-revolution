import { Component, PropTypes } from 'react';
import { connect } from 'react-redux';
import { createStructuredSelector } from 'reselect';
import { setRoom, getFloors } from '../../redux';
import '../styles/components/floors.scss';

class Floors extends Component {
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
    const socket = new WebSocket('ws://127.0.0.1:1880/ws/devices');

    socket.onopen = (event) => {
      console.log('WebSocket OK');
    };

    socket.onmessage = (event) => {
      console.log('event.data', event.data);
      const { status, deviceId } = event.data;

      //this.props.setRoom({ status: 'filled', deviceId: 1 });
      this.props.setRoom({ status, deviceId });
    }
  }

  renderDoorStatus(status) {
    let text;

    switch (status) {
      case 'filled':
        text = 'Занято';
        break;
      case 'time-out':
        text = 'Кажется забыли выключить свет';
        break;
      default:
        text = 'Свободно';
        break;
    }

    return (
      <div className={`door ${status}`}>
        <i></i>{text}
      </div>
    );
  };

  render() {
    return (
      <div className="floors row">
        {
          this.props.floors.map((floor, i) => (
            <section className="floor" key={`floor${i}`}>
              {/*<h2>{++i} этаж</h2>*/}
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
