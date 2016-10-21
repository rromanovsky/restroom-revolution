import * as apiHelper from '../helpers/api-helper';
import actionTypes from './types/app.js';

export function fetchData() {
  return (dispatch, getState) => {
    apiHelper.fetchData().then((data) => {
      return dispatch(gotData(data));
    }).catch((err) => {
      return dispatch(gotError(err));
      console.error(err);
    });
  };
}

export function gotData(data) {
  return {
    type: actionTypes.GOT_DATA,
    data: data
  }
}

export function gotError(err) {
  return {
    type: actionTypes.GOT_ERROR,
    err: err
  }
}