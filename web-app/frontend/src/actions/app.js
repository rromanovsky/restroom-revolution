import * as apiHelper from '../helpers/api-helper';
import actionTypes from './types/app.js';
import firebaseAdapter from '../helpers/firebase-adapter';

export function fetchData() {
  return (dispatch) => {
    dispatch(loadingData());

    firebaseAdapter((data) => dispatch(gotData(data)), err => dispatch(gotError(err)));
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