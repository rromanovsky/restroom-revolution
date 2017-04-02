import { Component } from 'react';
import Switcher from './Switcher';
import logo from '../assets/logo.png';
import '../styles/components/header.scss';

export default class extends Component {
  render() {
    return (
      <header>
        <div className="row">
          <section>
            <img className="logo" alt="Restroom Revolution" src={logo} />
          </section>
          <section className="info">
            <Switcher
              onChange={(checked) => console.log(checked)}
            />
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
