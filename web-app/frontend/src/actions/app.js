import * as apiHelper from '../helpers/api-helper';
import actionTypes from './types/app.js';

export function fetchData() {
  return (dispatch) => {
    dispatch(loadingData());

    return apiHelper.fetchData().then((data) => {
      return dispatch(gotData(data));
    }).catch((err) => {
      console.error(err);
      return dispatch(gotError(err));
    });
  };
}

export function loadingData() {
  return {
    type: actionTypes.LOADING_DATA
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