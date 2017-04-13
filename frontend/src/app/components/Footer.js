import { Component, PropTypes } from 'react';

export default class extends Component {
  static propTypes = {
    counter: PropTypes.number.isRequired,
  };

  render() {
    return (
      <footer>
        <div className="main row">
          <section>
            {/*<div>Скачать iOS приложение</div>*/}
          </section>
          <section>
            <div className="statistics">
              {/*<div className="title">Количество посещений за сегодня</div>*/}
              {/*<div className="value">{this.props.counter}</div>*/}
            </div>
          </section>
        </div>
      </footer>
    );
  }
}
