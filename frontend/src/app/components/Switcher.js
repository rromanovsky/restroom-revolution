import { Component, PropTypes } from 'react';
import Switch from 'rc-switch';
import '../styles/components/switcher.scss';

export default class extends Component {
  static propTypes = {
    onChange: PropTypes.func.isRequired,
    checked: PropTypes.bool,
    disabled: PropTypes.bool,
  };

  static defaultProps = {
    onChange: checked => console.log(checked),
    checked: false,
    disabled: false,
  };

  render() {
    return (
      <Switch
        onChange={this.props.onChange}
        //checked={this.props.checked}
        disabled={this.props.disabled}
      />
    );
  }
}
