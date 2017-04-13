import { Component, PropTypes } from 'react';
import icon1 from '../assets/icon1.png';

export default class extends Component {
  static propTypes = {
    notifications: PropTypes.bool.isRequired,
    floors: PropTypes.array.isRequired,
    setRoom: PropTypes.func.isRequired,
  };

  constructor(props) {
    super(props);
    const socket = new WebSocket('ws://192.168.2.1:1880/ws/devices'); // @TODO: move it to config

    socket.onopen = (event) => {
      console.log('WebSocket OK'); // @TODO
    };
    socket.onmessage = (event) => {
      const { state, deviceId } = JSON.parse(event.data);

      this.props.setRoom({ status: state === '1' ? 'occupied' : 'free', deviceId }); // @TODO
    };
  }

  componentWillReceiveProps(nextProps) {
    // @TODO
    const prev = this.props.floors[0].doors[0].status;
    const next = nextProps.floors[0].doors[0].status;

    if (this.props.notifications && prev === 'occupied' && next === 'free') {
      if ('Notification' in window) {
        Notification.requestPermission((permission) => {
          if (permission !== 'granted') {
            return;
          }

          const notification = new Notification('Свободно!', {
            body: 'Go go gooo!',
            icon: icon1,
            tag: 'status',
          });

          notification.onclick = () => {
            notification.close();
          };
          setTimeout(() => {
            notification.close();
          }, 1500);
        });
      }
    }
  }

  renderDoorStatus = (status) => {
    let icon;
    let text;

    switch (status) {
      case 'occupied':
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
