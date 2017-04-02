import { Component, PropTypes } from 'react';
import '../styles/components/floors.scss';

export default class extends Component {
  static propTypes = {
    floors: PropTypes.arrayOf(
      PropTypes.shape({
        doors: PropTypes.arrayOf(
          PropTypes.shape({
            status: PropTypes.string.isRequired,
          }).isRequired,
        ).isRequired,
      }).isRequired,
    ).isRequired,
  };

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
