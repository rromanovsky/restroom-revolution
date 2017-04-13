import { Component, PropTypes } from 'react';
import reactCookie from 'react-cookie';
import Switcher from './Switcher';
import logo from '../assets/logo.png';

export default class extends Component {
  static propTypes = {
    setNotifications: PropTypes.func.isRequired,
    notifications: PropTypes.bool.isRequired,
  };

  handleSwitcher = (value) => {
    reactCookie.save('notifications', value);
    this.props.setNotifications(value);
  };

  render() {
    return (
      <header>
        <div className="row">
          <section>
            <img className="logo" alt="Restroom Revolution" src={logo} />
          </section>
          <section className="info">
            <Switcher onChange={this.handleSwitcher} checked={this.props.notifications} />
            <div className="description">
              <h3>Включить уведомления</h3>
              Уведомления отправляются только при открытой вкладке
            </div>
          </section>
        </div>
      </header>
    );
  }
}
