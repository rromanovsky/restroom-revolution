import React from 'react';
import classnames from 'classnames';


export default (props) => {
  const {thing, isBusy} = props;
  const classnames2 = classnames('room', {busy: isBusy});

  return <div className={classnames2}>{thing}</div>;
}

