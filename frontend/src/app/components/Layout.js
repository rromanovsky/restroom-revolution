import { Component, PropTypes } from 'react';
import { connect } from 'react-redux';
import { createStructuredSelector } from 'reselect';
import reactCookie from 'react-cookie';
import Header from './Header';
import Floors from './Floors';
import Footer from './Footer';
import { getNotifications, setNotifications, getFloors, setRoom } from '../../redux';
import '../styles/components/layout.scss';

class Layout extends Component {
  static propTypes = {
    notifications: PropTypes.bool.isRequired,
    setNotifications: PropTypes.func.isRequired,
    floors: PropTypes.array.isRequired,
    setRoom: PropTypes.func.isRequired,
  };

  constructor(props) {
    super(props);
    this.props.setNotifications(reactCookie.load('notifications') === 'true');
  }

  render() {
    const counter = 89;
    const { notifications, setNotifications, floors, setRoom } = this.props;

    return (
      <div className="layout">
        <Header notifications={notifications} setNotifications={setNotifications} />
        <Floors notifications={notifications} floors={floors} setRoom={setRoom} />
        <Footer counter={counter} />
      </div>
    );
  }
}

const mapStateToProps = createStructuredSelector({
  notifications: getNotifications,
  floors: getFloors,
});

const mapDispatchToProps = {
  setNotifications,
  setRoom,
};

export default connect(mapStateToProps, mapDispatchToProps)(Layout);
