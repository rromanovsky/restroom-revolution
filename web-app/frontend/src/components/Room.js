import React from 'react';
import classnames from 'classnames';
import icon from '../images/wc.png';

export default (props) => {
  const {thing, isBusy} = props;
  const classnames2 = classnames('room', {busy: isBusy});

  return (
    <div className={classnames2}>
      <div className="title">
        {thing}
      </div>
      <div className="image">
        <img src={icon}/>
      </div>
    </div>
  );
}

