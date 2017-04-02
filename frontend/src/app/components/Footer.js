import { Component, PropTypes } from 'react';
import '../styles/components/footer.scss';

export default class extends Component {
  static propTypes = {
    count: PropTypes.number.isRequired,
  };

  render() {
    return (
      <footer>
        <div className="main row">
          <section>
            <div>Скачать iOS приложение</div>
          </section>
          <section>
            <div className="statistics">
              <div className="title">Количество посещений за сегодня</div>
              <div className="value">{this.props.count}</div>
            </div>
          </section>
        </div>
      </footer>
    );
  }
}
